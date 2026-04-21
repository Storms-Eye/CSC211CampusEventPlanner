#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <mutex>

using json = nlohmann::json;

class JsonRepository
{
private:
    std::string filename;
    std::string userfilename;
    json database;
    json users;

public:
    JsonRepository(const std::string &file, const std::string &userFile);
		mutable std::mutex mtx;
    void load();
    void save();
    void saveUsers();
    void eventHistoryUpdate(int eventID);
    void userHistoryUpdate(int userID, int eventID);

    bool createNewEvent(json &user,std::string name, int capacity, std::string description, std::string date);

    json authenticateUser(const std::string &userID, const std::string &pin);
    json approvalFunc(int id, bool isApproved);

    bool validID(const std::string &userID);
    bool isModerator(const json &user);
    bool isAdmin(const json &user);
    bool isEventFull(int eventId, int capacity, int totalUsers);

    json getEventWaitlist();
    json getUserWaitlist();
    json getApprovedEvents();
    json getEventHistory();
    json getUserHistory();
    json getAllTransactions();
    json getAttendance();
    json getValueById(json &dataset, std::string reference, int id);

    // Not yet written.
    json getValuesByFunction(json &dataset, auto func, int variable);
    json getValuesByFunction(json &dataset, auto func, std::string variable);
};
