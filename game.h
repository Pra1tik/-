#ifndef _Game_
#define _Game_
//#pragma once
#include <SDL2/SDL.h>
#include<iostream>

#define WindowWidth 1200
#define WindowHeight 1200

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
    private:
        SDL_Window* pWindow;
        SDL_Renderer* pRenderer;
        float dt = 0;
        bool runGame;
        class Player* player;
};

// typedef Game NewGame;

#endif