#pragma once
#include <crow.h>
#include "json-repository.h"

using json = nlohmann::json;

namespace EventManager
{
    void registerEventRoutes(crow::SimpleApp &app, JsonRepository &repo);

    json createEvent(int userId, int capacity, std::string description, std::string date);
}
