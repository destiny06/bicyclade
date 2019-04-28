#pragma once

class GameClientListener {
public:
    GameClientListener(){}
    virtual ~GameClientListener(){}

    virtual void onUpdateCoins() = 0;
};
