#include "event.h"

namespace EventManager
{
    void registerEventRoutes(crow::SimpleApp &app, JsonRepository &repo)
    {
        // POST to update eventHistory
        CROW_ROUTE(app, "/updateEventHistory/<int>")
            .methods("POST"_method)([&repo](int eventID)
        {
            repo.eventHistoryUpdate(eventID);
            return crow::response(200, "Event history updated");
        });

        // GET list of currently approved events
        CROW_ROUTE(app, "/approvedEvents")
            .methods("GET"_method)([&repo]()
        {
            return crow::response(repo.getApprovedEvents().dump(4));
        });

        // GET list of all past events
        CROW_ROUTE(app, "/eventHistory")
            .methods("GET"_method)([&repo]()
        {
            return crow::response(repo.getEventHistory().dump(4));
        });

        // GET waitlist of events waiting to be approved or denied
        CROW_ROUTE(app, "/eventWaitlist")
            .methods("GET"_method)([&repo]()
        {
            return crow::response(repo.getEventWaitlist().dump(4));
        });

        // EVENT APPROVAL/DENIAL FUNCTION (first draft)
        CROW_ROUTE(app, "/events/<id>")
            .methods("POST"_method)([&repo](const crow::request &req, int id)
        {
            json body;
            try
            {
                body = json::parse(req.body);
            }
            catch
            {
                ...
            }
            {
                return crow::response(400, "Invalid JSON");
            }

            if (id == 0)
            {
                return crow::response(400, "Events start at ID 1");
            }

            if (body.empty())
            {
                return crow::response(400, "The request cannot be empty");
            }

            // checks here for making sure the body contains all it is supposed to
            // should contain user ID, pin, and approval status (either true or false)

            // check if the user is an admin, the only person who should be able to approve or deny events
            std::string userID = body["user_id"];
            std::string pin = body["pin"];
            bool isApproved = body["approved"];

            auto user = repo.authenticateUser(user);

            if (user.is_null())
            {
                return crow::response(403, "Invalid credentials");
            }
            if (!repo.isAdmin(user))
            {
                return crow::response(403, "\nNot authorized\n");
            }
            auto result = approvalFunc(id, isApproved);

            if (result.contains("success") && result["success"] == true)
            {
                res.code = 200;
                // what information is required of the logTransaction function will be decided later
                repo.logTransaction(...);
            }
            else
            {
                res.code = 400;
            }
            // display the contents of the "message" portion of the "result" item
            res.write(result["message"].get<std::string>());
            return res;
        });
    }

    json EventManager::createEvent(int userId, int capacity, std::string description, std::string date)
    {
        // TODO: Add jsonrepo to createevent parameters, as we no longer have a global variable for jsonrepo.
        json &user = database.getUserById(userId);
        if (user.isModerator())
        {
            int eventId = database["nextPendingEventId"];
            json event =
                {
                    "Description" : description,
                    "Waitlist" : json::array(),
                    "Capaicty" : capacity,
                    "EventId" : eventId
                };
            json userEvent =
                {
                    "eventId" : eventId,
                    "status" : "Pending"
                };
            user["events"].push_back(userEvent)
                database["eventWaitList"]
                    .push_back(event)
        }
    }
}
