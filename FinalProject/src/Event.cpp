#include <crow.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

namespace Event
{
	json createEvent(int userId, int capacity, std::string description)
	{
		json& user = database.getUserById(userId);
		if(user.isModerator())
		{
			int eventId = database["nextPendingEventId"];
			json event = 
			{
				"Description": description,
				"Waitlist": json::array(),
				"Capaicty": capacity,
				"EventId": eventId
			};
			json userEvent = 
			{
				"eventId": eventId,
				"status": "Pending"
			};
			user["events"].push_back(userEvent)
			database["eventWaitList"].push_back(event)
		}
	}
}
