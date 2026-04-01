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
		return crow::response(repo.getEventWaitlist().dump());
	});
	
	// GET waitlist of users waiting for their registration to be accepted
	CROW_ROUTE(app, "/userWaitlist")
		.methods("GET"_method)
	([&repo]() {
		return crow::response(repo.getUserWaitlist().dump());
	});
	
	// GET list of currently approved events
	CROW_ROUTE(app, "/approvedEvents")
		.methods("GET"_method)
	([&repo]() {
		return crow::response(repo.getApprovedEvents().dump());
	});

	// GET list of all past events
	CROW_ROUTE(app, "/eventHistory")
		.methods("GET"_method)
	([&repo]() {
		return crow::response(repo.getEventHistory().dump());
	});
	
	// GET list of all transactions in the database
	CROW_ROUTE(app, "/transactions")
		.methods("GET"_method)
	([&repo]() {
		return crow::response(repo.getAllTransactions().dump());
	});
	
	// GET records of event attendance
	CROW_ROUTE(app, "/attendance")
		.methods("GET"_method)
	([&repo]() {
		return crow::response(repo.getAttendance().dump());
	});
	
	app.port(18080).multithreaded().run();
}
