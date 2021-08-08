#include "StartScreen.h"

StartScreen::StartScreen(SDL_Renderer* pRenderer)
{
    para = new TextureWrapper(pRenderer);
    para->loadFromFile("assets/start_screen.png");
    source = {0,0,para->getWidth(),para->getHeight()};
    destination = {0,0,WindowWidth,WindowHeight};
    
}

void StartScreen::render()
{
    para->render(source,destination);
}

StartScreen::~StartScreen()
{
    delete para;
}