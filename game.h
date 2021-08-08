#ifndef _Game_
#define _Game_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include<iostream>
#include "math.h"
#include "defaultVar.h"
#include <vector>



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
    private:
        enum Game_States
        {
            START_SCREEN=0,
            SELECT_SCREEN,
            GAME_SCREEN,
            INSTRUCTIONS_SCREEN,
            PAUSE_SCREEN,
            EXIT_SCREEN
        };
        SDL_Window* pWindow;
        SDL_Renderer* pRenderer;

        // pointer variables for different classes
        class Player* player;
        class Background* back;
        class collider* pCollider;
        class collider* tCollider;
        class StartScreen* startScreen;
        class SelectScreen* selectScreen;
        class InstructionScreen* controls;
        class PauseScreen* paused;

        float dt = 0;
        bool runGame;
        int tileNum;
        vec offset;
        int tilesOfCollidedRow[WindowWidth/TileWidth];
        bool tileFlag;
        bool breakflag=false;
        int playerXpos;
        Game_States currentGameState;
        vec mousePos;
};


#endif