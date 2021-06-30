#ifndef _Game_
#define _Game_

#include <SDL2/SDL.h>
#include<iostream>

#define WindowWidth 800
#define WindowHeight 600

class Game{
    public:
        Game(){}
        ~Game(){}
        bool init(const char* title,int xpos, int ypos, int height, int width, bool isFullscreen);
        void update(){};
        void render();
        void handleEvents();
        void clean();
        bool running(){return runGame;}
    private:
        SDL_Window* pWindow;
        SDL_Renderer* pRenderer;
        bool runGame;
};

// typedef Game NewGame;

#endif