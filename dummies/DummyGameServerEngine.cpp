//
// Created by patates on 7/17/18.
//

#include "DummyGameServerEngine.h"
#include "DummyGame.h"
#include "../packets.hpp"

Command * DummyGameServerEngine::doHandshake() {
    Command *command = static_cast<Command *>(malloc(MAX_PAYLOAD));
    int ret;

    listGames();// sending game lists here
    ret = networkModule->recvData(command, MAX_PAYLOAD);

    if(ret != command->length){
        cout << "something wrong with received data";
    }

    return command;
}

Game *DummyGameServerEngine::createGame(GameCreateCommand_t command) {
    Game *game;
    Command *join_cmd;
    GameJoinCommand_t *joinPacket;
    cout << "requested options are : " << command.maxPlayer << " : " <<
         command.gameName << " : " << endl;
    game = new DummyGame(generateUniqueId(), command.maxPlayer, command.gameName);

    // getSenderTopicName
    // send
    // getReceiverTopicName
    // send

    startGameIntoThread(game);
    insertNewGame(game);
    join_cmd = static_cast<Command *>(malloc(sizeof(Command) + sizeof(GameJoinCommand_t)));
    joinPacket = reinterpret_cast<GameJoinCommand_t *>(join_cmd->context);

    networkModule->recvData(join_cmd,sizeof(Command) + sizeof(GameJoinCommand_t));

//    joinGame(*joinPacket);

    return game;
}
