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

            if (!repo.isAdmin(user))
            {
                crow::response res(403);
                res.set_header("Content-Type", "application/json");
                res.write(json({{"error", "Forbidden: Admin access required"}}).dump());
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
        // GET waitlist of events waiting to be approved or denied
        CROW_ROUTE(app, "/eventWaitlist").methods("GET"_method)([&repo]()
        {
            return crow::response(repo.getEventWaitlist().dump(4));
        });

		// PATCH existing event to be either Approved or Denied
        CROW_ROUTE(app, "/events/<int>").methods("PATCH"_method)([&repo](const crow::request &req, int id)
        {
            json user = loginHelper(req, repo);
            if (user.is_null())
            {
                crow::response res(403);
                res.set_header("Content-Type", "application/json");
                res.write(json({{"error", "Unauthorized login attempt"}}).dump());
                return res;
            }

            if (!repo.isAdmin(user))
            {
                crow::response res(403);
                res.set_header("Content-Type", "application/json");
                res.write(json({{"error", "Forbidden: Admin access required"}}).dump());
                return res;
            }

            if (id == 0)
            {
                return crow::response(400, "Events start at ID 1");
            }

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

        CROW_ROUTE(app, "/createEvent").methods("POST"_method)([&repo](const crow::request &req)
        {
            json user = loginHelper(req, repo);
            if (user.is_null())
            {
                crow::response res(403);
                res.set_header("Content-Type", "application/json");
                res.write(json({{"error", "Unauthorized login attempt"}}).dump());
                return res;
            }

            if (!repo.isModerator(user))
            {
                return crow::response(403, "Forbidden: Only moderators can create events.");
            }

            json body;
            body = json::parse(req.body);
						std::string name = body["name"];
            int userId = body["user_id"];
            int capacity = body["capacity"];
            std::string description = body["description"];
            std::string date = body["date"];

            bool success = repo.createNewEvent(user, name, capacity, description, date);
            if (success)
            {
                return crow::response(200, "Event created and sent to waitlist");
            }
            else
            {
                return crow::response(500, "Failed to link event to user account");
            }
        });

        CROW_ROUTE(app, "/events/<int>/register").methods("PATCH"_method)([&repo](const crow::request &req, int eventID)
        {
            json user = loginHelper(req, repo);
            if (user.is_null())
            {
                crow::response res(403);
                res.set_header("Content-Type", "application/json");
                res.write(json({{"error", "Unauthorized login attempt"}}).dump());
                return res;
            }

            std::string userId = user["id"];
            json result = studentRegister(repo, eventID, userId);
            int responseCode = result.value("success", false) ? 200 : 400;
            crow::response res(responseCode);
            res.set_header("Content-Type", "application/json");
            res.write(result.dump(4));
            return res;
        });

        CROW_ROUTE(app, "/events/<int>/deregister").methods("PATCH"_method)([&repo](const crow::request &req, int eventID)
        {
            json user = loginHelper(req, repo);
            if (user.is_null())
            {
                crow::response res(403);
                res.set_header("Content-Type", "application/json");
                res.write(json({{"error", "Unauthorized login attempt"}}).dump());
                return res;
            }

            std::string userId = user["id"];
            json result = studentDeregister(repo, eventID, userId);
            int responseCode = result.value("success", false) ? 200 : 400;
            crow::response res(responseCode);
            res.set_header("Content-Type", "application/json");
            res.write(result.dump(4));
            return res;
        });
    }

    json studentRegister(JsonRepository &repo, int eventID, const std::string &userId)
    {
        std::string message;
        bool success = repo.registerStudentForEvent(eventID, userId, message);
        return json({{"success", success}, {"message", message}});
    }

    json studentDeregister(JsonRepository &repo, int eventID, const std::string &userId)
    {
        std::string message;
        bool success = repo.deregisterStudentFromEvent(eventID, userId, message);
        return json({{"success", success}, {"message", message}});
    }
}
