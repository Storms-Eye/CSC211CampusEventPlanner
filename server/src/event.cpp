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