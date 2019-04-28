#pragma once

#include <string>

class LobbyClientController {
public:
    LobbyClientController(){}
    virtual ~LobbyClientController(){}

    virtual void join() = 0;
    virtual void quit() = 0;
    virtual void rename(std::string& name) = 0;
    virtual void chat(std::string& message) = 0;
};
