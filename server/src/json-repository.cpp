#include "json-repository.h"

JsonRepository::JsonRepository(const std::string &file, const std::string &userFile)
    : filename(file), userfilename(userFile)
{
    load();
}

void JsonRepository::load()
{
    std::ifstream in(filename);
    if (in.good())
    {
        in >> database;
    }
    else
    {
        // Initialize if file missing
        database = {
            {"meta",
             {{"availableIndexes", json::array()},
              {"nextPendingEventID", 1},
              {"nextApprovedEventId", 1},
              {"nextUserId", 1},
              {"nextTransactionId", 1}}},
            {"eventWaitlist", json::array()},
            {"userWaitlist", json::array()},
            {"approvedEvents", json::array()},
            {"eventHistory", json::array()},
            {"transactions", json::array()},
            {"attendance", json::array()}
        };
        save();
    }
    // after the else
    std::ifstream userIn(userfilename);
    if (userIn.good())
    {
        userIn >> users;
    }
    else
    {
        // empty array
        users = json::array();
    }
}

void JsonRepository::save()
{
    std::ofstream out(filename);
    out << database.dump(4);
}

void JsonRepository::saveUsers()
{
    std::ofstream out(userfilename);
    out << users.dump(4);
}

bool JsonRepository::validID(const std::string &userID)
{
    // if the ID is not 7 digits long, it is not valid
    if (userID.length() != 7)
    {
        return false;
    }
    // if it contains any letters or special characters, it is not valid
    for (char c : userID)
    {
        if (!std::isdigit(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }
    return true;
}

// Uses both user's ID and pin to authenticate them
json JsonRepository::authenticateUser(const std::string &userID, const std::string &pin)
{
    // if the ID is not valid, return empty json
    if (!validID(userID))
    {
        return json();
    }
    for (auto &user : users)
    {
        // Pin and ID must belong to the same user
        if (user["id"] == userID && user["pin"] == pin)
        {
            return user;
        }
    }
    return json();
}

// checking if the user is a moderator in order to be able to POST events
bool JsonRepository::isModerator(const json &user)
{
    if (user.is_null())
    {
        return false;
    }
    std::string role = user["role"];
    return role == "moderator";
}

// checking if the user is an admin
bool JsonRepository::isAdmin(const json &user)
{
    if (user.is_null())
    {
        return false;
    }
    std::string role = user["role"];
    return role == "admin";
}

// checks if an event has been approved or denied by an admin
// if approved, delete the item from "eventWaitlist" and add to "approvedEvents"
// if denied, delete the item from "eventWaitlist" and add to "eventHistory"
json JsonRepository::approvalFunc(int id, bool isApproved)
{
    auto &eventWaitlist = database["eventWaitlist"];
    auto &approvedEvents = database["approvedEvents"];
    auto &eventHistory = database["eventHistory"];

    // search through the eventWaitlist for the event
    for (auto &item : eventWaitlist)
    {
        if (item["id"] == id)
        {
            // if the admin has approved the event, send it to "approvedEvents"
            if (isApproved)
            {
                json newEvent = item;
                approvedEvents.push_back(newEvent);
                eventWaitlist.erase(item);
                save();
                return {
                    {"success", true},
                    {"message", "\nEvent has been approved\n"}
                };
            }
            // otherwise, put the event in "eventHistory"
            else
            {
                json newEvent =
                    {
                        {"Description", item["Description"]},
                        {"Status", "denied"},
                        {"Capacity", 0},
                        {"EventID", item["EventId"]}
                    };
                eventHistory.push_back(newEvent);
                eventWaitlist.erase(item);
                save();
                return {
                    {"success", true},
                    {"message", "\nEvent has been denied\n"}
                };
            }
        }
        return {
            {"success", false},
            {"message", "\nAn event matching this ID does not exist\n"}
        };
    }
}

// check if an event if at capacity when a student is added
// if it is, return "true", which will cause the student to be waitlisted
// if not, return "false", which will allow the student to be added as an attendee
bool JsonRepository::isEventFull(int eventId, int capacity, int totalUsers)
{
    auto &attendance = database["approvedEvents"]["Waitlist"];
    int counter = 0;

    for (auto &item : attendance)
    {
        if (item["attendance"] == "Attending")
        {
            // Counts how many students in the event are listed as attending
            counter++;
        }
    }

    // if the amount of students attending is equal to the capacity, bar more students from checking in
    if (counter == capacity)
    {
        return true;
    }
    // Othwerwise, let them check in to the event
    return false;
}

json JsonRepository::getEventWaitlist()
{
    // if(database.isStudent()) return NULL or something as the functino doesn't exist
    return database.value("eventWaitlist", json::array());
}

json JsonRepository::getUserWaitlist()
{
    return database.value("userWaitlist", json::array());
}

json JsonRepository::getApprovedEvents()
{
    return database.value("approvedEvents", json::array());
}

json JsonRepository::getEventHistory()
{
    return database.value("eventHistory", json::array());
}

json JsonRepository::getUserHistory()
{
    return users.value("events", json::array());
}

json JsonRepository::getAllTransactions()
{
    return database.value("transactions", json::array());
}

json JsonRepository::getAttendance()
{
    return database.value("attendance", json::array());
}

json JsonRepository::getValueById(json &dataset, std::string reference, int id)
{
    for (auto &value : dataset)
    {
        if (value[reference] == id)
        {
            return value;
        }
    }
    return json(); // maybe this doesn't need for loop?
}

void JsonRepository::eventHistoryUpdate(int eventID)
{
    json event;

    // Search for event
    for (auto &data : database["approvedEvents"])
    {
        if (data["EventId"] == eventID)
        {
            event = data;
        }
    }

    // Change capacity
    int capacity = event["Capacity"];
    for (auto &data : event["Waitlist"])
    {
        if (capacity > 0)
        {
            data["attendance"] = "Attended";
            capacity--;
        }

        else
        {
            data["attendance"] = "Waitlisted";
        }
    }

    // Update the user history alongside change
    for (auto &data : event["Waitlist"])
    {
        userHistoryUpdate(data["userId"], eventID);
    }

    auto &events = database["approvedEvents"];

    // Remove event from approved events
    for (auto it = events.begin(); it != events.end(); ++it)
    {
        if ((*it)["EventId"] == eventID)
        {
            events.erase(it);
            save();
            break;
        }
    }

    database["eventHistory"].push_back(event);
    save();
}

void JsonRepository::userHistoryUpdate(int userID, int eventID)
{
    json event;
    for (auto &data : database["approvedEvents"])
    {
        if (data["EventId"] == eventID)
        {
            event = data;
        }
    }

    json user = getValueById(users, "id", userID);
    user["events"].push_back(event);
    saveUsers();
}
