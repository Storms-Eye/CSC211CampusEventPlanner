#pragma once

#include "json-repository.h"
#include <crow.h>
#include <iostream>

using json = nlohmann::json;

inline json loginHelper(const crow::request &req, JsonRepository &repo)
{
    std::string userID = req.get_header_value("X-User-ID");
    std::string pin = req.get_header_value("X-User-Pin");

    // If the headers are missing, Crow returns an empty string
    if (userID.empty() || pin.empty())
    {
        return json(); 
    }
    
    return repo.authenticateUser(userID, pin);
}
