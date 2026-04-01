#include <crow.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using json = nlohmann::json;

class JsonRepository {
	private:
		std::string filename;
		std::string userfilename;
		json database;
		json users;
	public:
		JsonRepository(const std::string& file, const std::string& userFile)
		:filename(file), userfilename(userFile) 
		{
			load();
		}

		void load(){
			std::ifstream in(filename);
			if(in.good()){
				in>>database;
			} 
			else 
			{
				// Initialize if file missing
				database = {
					{"meta",
						{
							{"availableIndexes": json::array()},
							{"nextPendingEventID", 1},
							{"nextApprovedEventId", 1},
							{"nextUserId", 1},
							{"nextTransactionId", 1}
						}
					},
					{"eventWaitlist", json::array()},
					{"userWaitlist", json::array()},
					{"approvedEvents", json::array()},
					{"eventHistory", json::array()},
					{"transactions", json::array()},
					{"attendance", json::array()}
				};
				save();
			}
			//after the else
			std::ifstream userIn(userfilename);
			if(userIn.good())
			{
				userIn >> users;
			}
			else
			{
				//empty array
				users = json::array();
			}
		}

		void save(){
			std::ofstream out(filename);
			out << database.dump(4);
		}

        void saveUsers()
        {
			std::ofstream out(userfilename);
			out << users.dump(4);
		}
		
		json getEventWaitlist(){
			return database.value("eventWaitList", json::array());
		}
		json getUserWaitlist(){
			return database.value("userWaitList", json::array());
		}
		json getApprovedEvents(){
			return database.value("approvedEvents", json::array());
		}
		json getEventHistory(){
			return database.value("eventHistory", json::array());
		}
		json getAllTransactions(){
			return database.value("transactions", json::array());
		}
		json getAttendance(){
			return database.value("attendance", json::array());
		}
		json& getValueById(json& dataset, std::string reference, int id)
		{
			for(auto& value : dataset)
			{
				if(value[reference] == id)
				{
					return value;
				}
			}
			return json(); //maybe this doesn't need for loop?
		}
		json getValuesByFunction(json& dataset, auto func, int variable);
		json getValuesByFunction(json& dataset, auto func, std::string variable);

        void eventHistoryUpdate(int eventID)
        {
			json event;
            for(auto& data : database["approvedEvents"])
            {
                if(data["EventId"] == eventID)
                {
                    event = data;
                }
            }

            int capacity = event["Capacity"];
            for(auto& data : event["Waitlist"])
            {
                if(capacity > 0)
                {
                    data["attendance"] = "Attended";
                    capacity--;
                }

                else
                {
                    data["attendance"] = "Waitlisted";
                }
                
            }

            for(auto& data : event["Waitlist"])
            {
                userHistoryUpdate(data["userId"], eventID);
            }
            
            auto& events = database["approvedEvents"];

            // Remove event from approved events
            for(auto it = events.begin(); it != events.end(); ++it)
            {
                if((*it)["EventId"] == eventID)
                {
                    events.erase(it);
                    save();
                }
            }
            
            database["eventHistory"].push_back(event);
            save();
        }

        void userHistoryUpdate(int userID, int eventID)
        {
            json event;
            for(auto& data : database["approvedEvents"])
            {
                if(data["EventId"] == eventID)
                {
                    event = data;
                }
            }
            
            json user = getValueById(users, "id", userID);
            user["events"].push_back(event);
            saveUsers();
        }
};

//----------------------------
//main routing

int main() {
	crow::SimpleApp app;

	JsonRepository repo("./data.json", "../user.json");
	
	//Server Frontend
	CROW_ROUTE(app, "/")([](){
		return crow::response("<html><body><h1>Welcome to Super Awesome Team Name's Final Project</h1></body></html>"); 
		// this will not be the final display, btw
		// unless we want it to be
		// but I would think we'd want it to be a little more official
	});
	
	// GET waitlist of events waiting to be approved or denied
	CROW_ROUTE(app, "/eventWaitlist")
		.methods("GET"_method)
	([&repo]() {
		return crow::response(repo.getEventWaitlist().dump(4));
	});
	
	// GET waitlist of users waiting for their registration to be accepted
	CROW_ROUTE(app, "/userWaitlist")
		.methods("GET"_method)
	([&repo]() {
		return crow::response(repo.getUserWaitlist().dump(4));
	});
	
	// GET list of currently approved events
	CROW_ROUTE(app, "/approvedEvents")
		.methods("GET"_method)
	([&repo]() {
		return crow::response(repo.getApprovedEvents().dump(4));
	});

	// GET list of all past events
	CROW_ROUTE(app, "/eventHistory")
		.methods("GET"_method)
	([&repo]() {
		return crow::response(repo.getEventHistory().dump(4));
	});
	
	// GET list of all transactions in the database
	CROW_ROUTE(app, "/transactions")
		.methods("GET"_method)
	([&repo]() {
		return crow::response(repo.getAllTransactions().dump(4));
	});
	
	// GET records of event attendance
	CROW_ROUTE(app, "/attendance")
		.methods("GET"_method)
	([&repo]() {
		return crow::response(repo.getAttendance().dump(4));
	});
    
    // POST to update eventHistory
	CROW_ROUTE(app, "/updateEventHistory/<int>")
		.methods("POST"_method)
	([&repo](int eventID) {
        eventHistoryUpdate(eventID);
        return crow::response(200, "Event history updated");
        
	});
	
	app.port(18080).multithreaded().run();
}
