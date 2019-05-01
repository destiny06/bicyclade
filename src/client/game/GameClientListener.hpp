#pragma once

/**
 * Events from the game, see ClientApplication design.
 */
class GameClientListener {
public:
    GameClientListener(){}
    virtual ~GameClientListener(){}

    virtual void onUpdateCoins() = 0;
};
