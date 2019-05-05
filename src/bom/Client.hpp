#pragma once

#include <string>

class Client {
public:

    std::string name;
    int id;
    Client(int id);
    Client(int id, std::string name);
	Client() = default;
};
