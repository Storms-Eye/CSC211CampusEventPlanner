#include <crow.h>
#include "json-repository.h"
#include "event.h"

using json = nlohmann::json;

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

	EventManager::registerEventRoutes(app, repo);


	// TODO: Move these routes into their own managers (user manager, event manager, etc).
	
	// GET waitlist of users waiting for their registration to be accepted
	CROW_ROUTE(app, "/userWaitlist")
		.methods("GET"_method)
	([&repo]() {
		return crow::response(repo.getUserWaitlist().dump(4));
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
	
	app.port(18080).multithreaded().run();
}
