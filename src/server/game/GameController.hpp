#pragma once

#include "bom/Player.hpp"
#include "common/Util.hpp"

#include <map>

using namespace std;

typedef std::map<int, Player*> playerMapType;

class GameController {
private:

    playerMapType* playersMap;

public:

void startGame(playerMapType* playerMap);

};
