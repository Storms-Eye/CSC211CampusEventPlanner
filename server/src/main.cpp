#include "event.h"
#include "json-repository.h"
#include <crow.h>

using json = nlohmann::json;

int main()
{
    crow::SimpleApp app;

    JsonRepository repo("./data.json", "../user.json");

    // Server Frontend
    CROW_ROUTE(app, "/")([]()
    {
        return crow::response("<html><body><h1>Welcome to Super Awesome Team Name's Final Project</h1></body></html>");
        // this will not be the final display, btw
        // unless we want it to be
        // but I would think we'd want it to be a little more official
    });

    EventManager::registerEventRoutes(app, repo);

    // TODO: Move these routes into their own managers (user manager, event manager, etc).

    // GET waitlist of users waiting for their registration to be accepted
    CROW_ROUTE(app, "/userWaitlist")
        .methods("GET"_method)([&repo]()
    {
        return crow::response(repo.getUserWaitlist().dump(4));
    });

    // GET list of all transactions in the database
    CROW_ROUTE(app, "/transactions")
        .methods("GET"_method)([&repo]()
    {
        return crow::response(repo.getAllTransactions().dump(4));
    });

    // GET records of event attendance
    CROW_ROUTE(app, "/attendance")
        .methods("GET"_method)([&repo]()
    {
        return crow::response(repo.getAttendance().dump(4));
    });

    // GET records of event history
    CROW_ROUTE(app, "/eventHistory")
        .methods("GET"_method)([&repo]()
    {
        return crow::response(repo.getEventHistory().dump(4));
    });

    // GET records of user history
    CROW_ROUTE(app, "/userHistory")
        .methods("GET"_method)([&repo]()
    {
        return crow::response(repo.getUserHistory().dump(4));
    });

    // REGISTRATION FUNCTION - also not my particular field, just showing how capacity limit will be enforced
    // URL may need to be adjusted
    CROW_ROUTE(app, "/register/<int>")
        .methods("PATCH"_method)([&repo](const crow::request &req, int id)
    {
        // all of what the other team members will add...

        // ...

        bool isEventFull(id, item["Capacity"].get<int>(), item["totalUsers"].get<int>());

        // UPDATE FOR APRIL 10th WEEKLY CHECK-IN
        // Changing what exact this method returns
        // if the event is full, bar more students from checking into the event
        // if it is not full, let them check into the event
        if (isEventFull)
        {
            return crow::response(400, "Event is full. You cannot check into this event");
        }
        else
        {
            return crow::response(200, "Successfully checked into event.");
        }
    });

    app.port(18080).multithreaded().run();
}
