#include "game.h"
Game* pGame=0;
int main(int argc,char* argv[])
{
    pGame= new Game();
    pGame->init("Chapter1",100,100,WindowWidth,WindowHeight,true);
    while(pGame->running())
    {
        pGame->handleEvents();
        pGame->update();
        pGame->render();
    }
    pGame->clean();
    return 0;
}