#include "event.h"
#include "json-repository.h"
#include "login-helper.h"
#include <crow.h>

using json = nlohmann::json;

int main()
{
    crow::SimpleApp app;

    JsonRepository repo("./data.json", "./user.json");

    EventManager::registerEventRoutes(app, repo);

    CROW_ROUTE(app, "/login").methods("POST"_method)([&repo](const crow::request &req)
    {
        json user = loginHelper(req, repo);
        if (user.is_null())
        {
            crow::response res(403);
            res.set_header("Content-Type", "application/json");
            res.write(json({{"error", "Unauthorized login attempt"}}).dump());
            return res;
        }

        // Idk if we need this, but it was in the old framework we made in class.
        json results = {
            {"success", true},
            {"user_id", user["id"]},
            {"name", user["name"]},
            {"role", user["role"]}
        };

        crow::response res(200);
        res.set_header("Content-Type", "application/json");
        res.write(results.dump());
        return res;
    });

    // TODO: Move these routes into their own managers (user manager, event manager, etc).
    // GET waitlist of users waiting for their registration to be accepted
    CROW_ROUTE(app, "/userWaitlist").methods("GET"_method)([&repo](const crow::request &req)
    {
        json user = loginHelper(req, repo);
        if (user.is_null())
        {
            crow::response res(403);
            res.set_header("Content-Type", "application/json");
            res.write(json({{"error", "Unauthorized login attempt"}}).dump());
            return res;
        }

        if (!repo.isAdmin(user) && !repo.isModerator(user))
        {
            crow::response res(403);
            res.set_header("Content-Type", "application/json");
            res.write(json({{"error", "Forbidden: Admin or moderator access required"}}).dump());
            return res;
        }
        
        return crow::response(repo.getUserWaitlist().dump(4));
    });

    // GET list of all transactions in the database
    CROW_ROUTE(app, "/transactions").methods("GET"_method)([&repo]()
    {
        return crow::response(repo.getAllTransactions().dump(4));
    });

    // GET records of event attendance. Only moderator and admins can see this.
    CROW_ROUTE(app, "/attendance").methods("GET"_method)([&repo](const crow::request &req)
    {
        json user = loginHelper(req, repo);
        if (user.is_null())
        {
            crow::response res(403);
            res.set_header("Content-Type", "application/json");
            res.write(json({{"error", "Unauthorized login attempt"}}).dump());
            return res;
        }

        if (!repo.isAdmin(user) && !repo.isModerator(user))
        {
            crow::response res(403);
            res.set_header("Content-Type", "application/json");
            res.write(json({{"error", "Forbidden: Admin or moderator access required"}}).dump());
            return res;
        }

        return crow::response(repo.getAttendance().dump(4));
    });

    // GET records of event history. Only admin can see this.
    CROW_ROUTE(app, "/eventHistory").methods("GET"_method)([&repo](const crow::request &req)
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
            res.write(json({{"error", "Forbidden: Admin or moderator access required"}}).dump());
            return res;
        }

        return crow::response(repo.getEventHistory().dump(4));
    });

    // GET records of user history
    CROW_ROUTE(app, "/userHistory").methods("GET"_method)([&repo]()
    {
        return crow::response(repo.getUserHistory().dump(4));
    });

    // Registration route for students. Path preserved for compatibility.
    CROW_ROUTE(app, "/register/<int>").methods("PATCH"_method)([&repo](const crow::request &req, int id)
    {
        json user = loginHelper(req, repo);
        if (user.is_null())
        {
            crow::response res(403);
            res.set_header("Content-Type", "application/json");
            res.write(json({{"error", "Unauthorized login attempt"}}).dump());
            return res;
        }

        // all of what the other team members will add...
        json approvedEvents = repo.getApprovedEvents();
        auto item = repo.getValueById(approvedEvents, "EventId", id);

        bool status = repo.isEventFull(id, item["Capacity"].get<int>(), item["totalUsers"].get<int>());

        // UPDATE FOR APRIL 10th WEEKLY CHECK-IN
        // Changing what exact this method returns
        // if the event is full, bar more students from checking into the event
        // if it is not full, let them check into the event
        if (status)
        {
            return crow::response(400, "Event is full. You cannot check into this event");
        }
        else
        {
            item["id"]["attended"] = "attended";
            return crow::response(200, "Successfully checked into event.");
        }
    });

    app.port(18080).multithreaded().run();

}
