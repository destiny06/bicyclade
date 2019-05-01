#pragma once

#include "../lobby/LobbyClientController.hpp"
#include "../lobby/LobbyClientListener.hpp"
#include "../game/GameClientController.hpp"
#include "../game/GameClientListener.hpp"
#include "../network/SocketClient.hpp"

/**
 * ClientApplication is the interface that describe a Bicyclades client as seen
 * from the outside.
 *
 * Every program that run a Bicyclades client will have to interact with this
 * interface. This is the case for `CommandLineClient` and `SimulatedClientSample`
 * for instance.
 *
 * The actual implementation of the ClientApplication does not need to be known
 * by the program when using it.
 *
 * A Factory (ClientApplicationFactory) is available and allow to instantiate a
 * functional implementation of a ClientApplication that can be used by our
 * program.
 *
 * The following design describe all the things that a program using a
 * ClientApplication needs to understand in order to use it. Every other aspects
 * that are not described here are only implementation details.
 *
 * - LobbyClientListener and GameClientListener are two listeners of events
 * happening when the ClientApplication is running. Their implementations are
 * are the responsibility of the program using the ClientApplication.
 * For instance, they can be used to trigger some callback on a GUI when some
 * game events happen.
 * It is important to note that both listeners are optional here. A
 * ClientApplication can run without any external listeners.
 *
 * - LobbyClientController and GameClientController are the two controllers
 * that execute interactions with the lobby and the game (e.g. send a message to
 * other players, play your turn, etc.)
 *
 *   +-----------------------+           +-----------------------+
 *   | LobbyClientListener   |           | GameClientListener    |
 *   |-----------------------|           |-----------------------|
 *   |- onJoin(client)       |           |- onSoldierMove(...)   |
 *   |- onQuit(client)       |           |- onFleetMove(...)     |
 *   |- onChat(client, msg)  |           |- onPortBuilding(...)  |
 *   |- ...                  |           |- ...                  |
 *   |                       |           |                       |
 *   |                       |           |                       |
 *   +-----------------------+           +-----------------------+
 *              ^                                   ^
 *              |                                   |
 *              |     +-----------------------+     |
 *              |     |         main          |     |
 *              |     |-----------------------|     |
 *              |     |                       |     |
 *              |     +-----------------------+     |  ================================
 *              |                 |                 |  === EXTERNAL WORLD           ===
 *              |                 |                 |  ================================
 * - - - - - - -|- - - - - - - - -|- - - - - - - - -|- - - - - - - - - - - - - - - - -
 *              |                 |                 |  ================================
 *              |                 V                 |  === CLIENT APPLICATION WORLD ===
 *              |     +-----------------------+     |  ================================
 *              |     |   ClientApplication   |     |
 *              |     |-----------------------|     |
 *              |     |- start()              |     |
 *              +-----|- stop()               |-----+
 *                    |- setLobbyListener()   |
 *                    |- setGameListener()    |
 *                    |- getLobbyController() |
 *                    |- getGameController()  |
 *                    |- ...                  |
 *                    +-----------------------+
 *                              |   |
 *              +---------------+   +---------------+
 *              |                                   |
 *   +-----------------------+           +-----------------------+
 *   | LobbyClientController |           | GameClientController  |
 *   |-----------------------|           |-----------------------|
 *   |- join()               |           |- recruitSoldier(...)  |
 *   |- quit()               |           |- moveSoldier(...)     |
 *   |- rename(name)         |           |- buildTemple(...)     |
 *   |- chat(msg)            |           |- hirePriest()         |
 *   |- ...                  |           |- ...                  |
 *   |                       |           |                       |
 *   +-----------------------+           +-----------------------+
 *
 */
class ClientApplication {
public:
    ClientApplication(){}
    virtual ~ClientApplication(){}

    virtual void start() = 0;
    virtual void stop() = 0;

    /**
     * @return The controller returned can be NULL if the client cannot access
     * to any lobby (usually if the connection with the server has failed).
     */
    virtual LobbyClientController* getLobbyController() = 0;

    /**
     * @return The controller returned can be NULL if the client has not joined
     * the game yet.
     */
    virtual GameClientController* getGameController() = 0;

    /**
     * External SocketClientListener can be set, essentially for debug purpose.
     */
    virtual void setExternalSocketListener(SocketClientListener* listener) = 0;
    virtual void setExternalLobbyListener(LobbyClientListener* listener) = 0;
    virtual void setExternalGameListener(GameClientListener* listener) = 0;
};
