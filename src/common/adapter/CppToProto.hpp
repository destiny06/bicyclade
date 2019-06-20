#pragma once

#include "bom/Player.hpp"
#include <map>

namespace proto {
	class PContainer;
}

typedef std::map<int, Player*> playerMapType;

class CppToProto {
public:
	proto::PContainer buildStartGame(playerMapType* playersList);
};
