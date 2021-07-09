#include "game.h"
#include "Player.h"

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
                player = new Player(pRenderer);

            }
            else{
                std::cout << "Error " <<SDL_GetError()<<std::endl;
                return false;
            }
        }
        else{
            return false;
        }
        runGame= true;
        return true;
    }

    return false;
}
void Game::render()
{
    SDL_RenderClear(pRenderer);
    player->render();
    SDL_RenderPresent(pRenderer);
}

void Game::update()
{
    player->update();
}

void Game::clean()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}
void Game::handleEvents(float deltaTime)
{
    dt = deltaTime;
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            runGame=false;
        }
        else
        {
           
            player->handleInput(event, dt);

        }
    }

}