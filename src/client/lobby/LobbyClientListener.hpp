#pragma once

class LobbyClientListener {
public:
	LobbyClientListener(){}
	virtual ~LobbyClientListener(){}

	virtual void onJoin() = 0;
	virtual void onQuit() = 0;
	virtual void onRename() = 0;
	virtual void onChat() = 0;
};
