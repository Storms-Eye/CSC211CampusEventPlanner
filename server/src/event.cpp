#include "event.h"
#include "login-helper.h"

namespace EventManager
{
    void registerEventRoutes(crow::SimpleApp &app, JsonRepository &repo)
    {
        // POST to update eventHistory
        CROW_ROUTE(app, "/updateEventHistory/<int>").methods("POST"_method)([&repo](const crow::request &req, int eventID)
        {
            json user = loginHelper(req, repo);
            if (user.is_null())
            {
                crow::response res(403);
                res.set_header("Content-Type", "application/json");
                res.write(json({{"error", "Unauthorized login attempt"}}).dump());
                return res;
            }

            repo.eventHistoryUpdate(eventID);
            return crow::response(200, "Event history updated");
        });

        // GET list of currently approved events
        CROW_ROUTE(app, "/approvedEvents").methods("GET"_method)([&repo]()
        {
            return crow::response(repo.getApprovedEvents().dump(4));
        });

        // GET list of all past events
        CROW_ROUTE(app, "/eventHistory").methods("GET"_method)([&repo]()
        {
            return crow::response(repo.getEventHistory().dump(4));
        });

        // GET waitlist of events waiting to be approved or denied
        CROW_ROUTE(app, "/eventWaitlist").methods("GET"_method)([&repo]()
        {
            return crow::response(repo.getEventWaitlist().dump(4));
        });

        // EVENT APPROVAL/DENIAL FUNCTION (first draft)
        CROW_ROUTE(app, "/events/<int>").methods("POST"_method)([&repo](const crow::request &req, int id)
        {
            json user = loginHelper(req, repo);
            if (user.is_null())
            {
                crow::response res(403);
                res.set_header("Content-Type", "application/json");
                res.write(json({{"error", "Unauthorized login attempt"}}).dump());
                return res;
            }

            if (id == 0)
            {
                return crow::response(400, "Events start at ID 1");
            }

            // checks here for making sure the body contains all it is supposed to
            // should contain user ID, pin, and approval status (either true or false)

            // check if the user is an admin, the only person who should be able to approve or deny events
            json body;
            body = json::parse(req.body);

            std::string userID = body["user_id"];
            std::string pin = body["pin"];
            bool isApproved = body["approved"];
            auto result = repo.approvalFunc(id, isApproved);

            crow::response res;
            if (result.contains("success") && result["success"] == true)
            {
                res.code = 200;
                // what information is required of the logTransaction function will be decided later
                // repo.logTransaction(...);
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

    json createEvent(JsonRepository &repo, int userId, int capacity, std::string description, std::string date)
    {
        /* JsonRepository needs more functions before this will compile.
        // TODO: Add jsonrepo to createevent parameters, as we no longer have a global variable for jsonrepo.
        json &user = repo.getUserById(userId);
        if (user.isModerator())
        {
            int eventId = database["nextPendingEventId"];
            json event =
                {
                    {"Description", description},
                    {"Waitlist", json::array()},
                    {"Capacity", capacity},
                    {"EventId", eventId}
                };
            json userEvent =
                {
                    {"eventId", eventId},
                    {"status", "Pending"}
                };
            user["events"].push_back(userEvent);

            database["eventWaitList"].push_back(event);
        }
        */
        return json();
    }
}
