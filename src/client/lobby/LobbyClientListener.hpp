#pragma once

#include "../../bom/Client.hpp"

/**
 * Events from the lobby, see ClientApplication design.
 */
class LobbyClientListener {
public:
	LobbyClientListener(){}
	virtual ~LobbyClientListener(){}

	virtual void onJoin(Client& client) = 0;
	virtual void onQuit(Client& client) = 0;
	virtual void onRename(Client& client, std::string newName) = 0;
	virtual void onChat(Client& client, std::string message) = 0;
};
