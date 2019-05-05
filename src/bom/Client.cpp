#include "Client.hpp"

Client::Client(int id) {
    this->id = id;
}

Client::Client(int id, string name) {
    this->id = id;
    this->name = name;
}
