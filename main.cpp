#include "game.h"
#include <time.h>

Game* pGame = NULL;

int main(int argc,char* argv[])
{
    srand(time(NULL));
    const float FPS=60.f;
    Uint32 currentTime, lastTime = 0;
    const float frameDelay=1000/FPS;
    pGame= new Game();
    

    pGame->init("The Game",100,100,WindowWidth,WindowHeight,false);

    while(pGame->running())
    {
        currentTime = SDL_GetTicks();
        if((currentTime - lastTime) < frameDelay)
        {
            Uint32 delay = frameDelay - (currentTime - lastTime);
            SDL_Delay(delay);
        }

        currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.f;
        lastTime = currentTime;
        

        pGame->handleEvents(deltaTime);


        pGame->update();
        pGame->render();
        

    }
    
    pGame->clean();
    return 0;
}
