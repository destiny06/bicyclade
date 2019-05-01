#pragma once

/**
 * Interactions with the game, see ClientApplication design.
 */
class GameClientController {
public:
    GameClientController(){}
    virtual ~GameClientController(){}

    virtual void putOfferingMarker() = 0;
};
