#pragma once

#include "common/Util.hpp"
#include "Client.hpp"

class Player : public Client {
public:

    int coins;
    Colour colour;
    Player(Client& c);

};
