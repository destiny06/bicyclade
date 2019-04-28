#pragma once

class GameClientController {
public:
    GameClientController(){}
    virtual ~GameClientController(){}

    virtual void putOfferingMarker() = 0;
};
