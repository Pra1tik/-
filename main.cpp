#include "game.h"
Game* pGame=0;
int main(int argc,char* argv[])
{
    const int FPS=60;
    Uint32 framestart,frameTime;
    const int frameDelay=1000/FPS;
    pGame= new Game();
    int count=0;
    pGame->init("Chapter1",100,100,WindowWidth,WindowHeight,false);
    while(pGame->running())
    {
        framestart=SDL_GetTicks();
        pGame->handleEvents();
        pGame->update();
        pGame->render();
        frameTime=SDL_GetTicks()-framestart;
        if (frameDelay>frameTime){
            SDL_Delay(frameDelay-frameTime);
        }
    }
    pGame->clean();
    return 0;
}
