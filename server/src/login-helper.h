#pragma once

#include "json-repository.h"
#include <crow.h>
#include <iostream>

using json = nlohmann::json;

inline json loginHelper(const crow::request &req, JsonRepository &repo)
{
    json body;
    try
    {
        body = json::parse(req.body);
    }
    catch (...)
    {
        std::cerr << "Invalid JSON" << std::endl;
        return json();
    }

    if (!body.contains("user_id") || !body.contains("pin"))
    {
        std::cerr << "Missing credentials" << std::endl;
        return json();
    }

    std::string userID = body["user_id"];
    std::string pin = body["pin"];

    json user = repo.authenticateUser(userID, pin);
    if (user.is_null())
    {
        std::cerr << "Invalid credentials" << std::endl;
        return json();
    }

    return user;
}
