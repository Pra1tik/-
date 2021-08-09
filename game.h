#ifndef _Game_
#define _Game_
//#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "math.h"
#include "defaultVar.h"
#include <vector>
#include "Level.h"


class Game{
    public:
        Game(){}
        ~Game(){}
        bool init(const char* title,int xpos, int ypos, int height, int width, bool isFullscreen);
        void update();
        void render();
        void handleEvents(float deltaTime);
        void clean();
        bool running(){return runGame;}
        void Collider(class Player*, class Background*);
        class Player* getPlayer() { return player; }
        class Level* getLevel() { return level; }
    private:
        SDL_Window* pWindow;
        SDL_Renderer* pRenderer;

        // pointer variables for different classes
        class Player* player;
        class Background* back;
        class collider* pCollider;
        class collider* tCollider;

        class Level* level;

        float dt = 0;
        bool runGame;
        int tileNum;
        vec offset;
        int tilesOfCollidedRow[WindowWidth/TileWidth];
        bool tileFlag;
        int playerXpos;
};


#endif