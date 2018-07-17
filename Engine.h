//
// Created by patates on 7/16/18.
//
#include <vector>
#include <iostream>
#include "Game.h"

#ifndef BLINDGAME_ENGINE_H
#define BLINDGAME_ENGINE_H

using namespace std;



class Engine {
protected:
    NetworkModule *networkModule;

private:

public:
    virtual struct Command doHandshake() = 0;
};


class GameServerEngine : public Engine{
private:
    vector<Game*> gamelist;
    int uid = 0;

    struct Command doHandshake();
    bool listGame();
    bool joinGame(int gameid, char *playerName);
    Game *createGame(int maxPlayer, string gameName);
    bool observeGame(int gameid);

public:
    GameServerEngine(){
        networkModule = new ServerNetworkModule();
        networkModule->init();
    }
    bool startServer();

    virtual Game* gameObjCreator() = 0;

};



/*
void *gameManger(void* g){
    Game *game;
    game = (Game*) g;
}
*/
#endif //BLINDGAME_ENGINE_H
