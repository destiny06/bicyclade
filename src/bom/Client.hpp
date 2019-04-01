#pragma once

#include <string>
using namespace std;

class Client {
public:

    string name;
    int id;
    Client(int id);
    Client(int id, string name);
	Client() = default;
};
