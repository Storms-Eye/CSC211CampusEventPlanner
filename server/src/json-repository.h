#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

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

    void load();
    void save();
    void saveUsers();
    void eventHistoryUpdate(int eventID);
    void userHistoryUpdate(int userID, int eventID);

    json getEventWaitlist();
    json getUserWaitlist();
    json getApprovedEvents();
    json getEventHistory();
    json getAllTransactions();
    json getAttendance();
    json getValueById(json &dataset, std::string reference, int id);

    // Not yet written.
    json getValuesByFunction(json &dataset, auto func, int variable);
    json getValuesByFunction(json &dataset, auto func, std::string variable);
};