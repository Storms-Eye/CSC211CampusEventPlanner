#pragma once
#include <crow.h>
#include "json-repository.h"

using json = nlohmann::json;

namespace EventManager
{
    void registerEventRoutes(crow::SimpleApp &app, JsonRepository &repo);

    json createEvent(JsonRepository &repo, int userId, int capacity, std::string description, std::string date);
    json studentRegister(JsonRepository &repo, int eventID, const std::string &userId);
    json studentDeregister(JsonRepository &repo, int eventID, const std::string &userId);
}
