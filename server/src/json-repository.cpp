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

json JsonRepository::getEventWaitlist()
{
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