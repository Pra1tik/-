#include "game.h"
#include "player.h"
#include "Character.h"

player* play;

bool Game::init(const char* title,int xpos, int ypos, int height, int width, bool flags)
{
    Uint32 windowState;
    if (!flags)
    {
        windowState=SDL_WINDOW_SHOWN;
    }
    else
    {
        height = SDL_WINDOW_FULLSCREEN;
        width = SDL_WINDOW_FULLSCREEN;
        windowState=SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING)>=0){
        pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,windowState);
        if(pWindow!=0){
            pRenderer=SDL_CreateRenderer(pWindow,-1,0);
            if (pRenderer!=0){
                SDL_SetRenderDrawColor(pRenderer,0,0,255,255);
            }
            else{
                std::cout << "Error " <<SDL_GetError()<<std::endl;
                return false;
            }
        }
        else{
            return false;
        }
        play= new player("assets/player.png","Player1");
        runGame= true;
        return true;
    }
    return false;
}
void Game::render()
{
    SDL_RenderClear(pRenderer);
    play->render();
    SDL_RenderPresent(pRenderer);
}
void Game::update()
{
    play->update();
}
void Game::clean()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}
void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            runGame=false;
        }
    }
}