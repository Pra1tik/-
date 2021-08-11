#include "PauseScreen.h"
#include <SDL2/SDL_ttf.h>

PauseScreen::PauseScreen(SDL_Renderer* pRenderer)
{
    cRenderer = pRenderer;
    TTF_Font* font=TTF_OpenFont("graphics/Fonts/pacifico/Pacifico.ttf",50);

    resume = new TextureWrapper(pRenderer,font);
    exit = new TextureWrapper(pRenderer, font);

    SDL_Color color = {0,0,0};

    resume->loadFromRenderedText("RESUME",color);
    exit->loadFromRenderedText("EXIT",color);

    destination1 = {WindowWidth/2-resume->getWidth()/2,300,resume->getWidth(),resume->getHeight()};
    destination2 = {WindowWidth/2-exit->getWidth()/2,500,exit->getWidth(),exit->getHeight()};
}


bool PauseScreen::isInsideExit(vec mousePos)
{
    if (mousePos.x >= destination2.x && mousePos.x < destination2.x+destination2.w && mousePos.y >= destination2.y && mousePos.y < destination2.y+destination2.h)
    {
        return true;
    }
    return false;
}


bool PauseScreen::isInsideResume(vec mousePos)
{
    if (mousePos.x >= destination1.x && mousePos.x < destination1.x+destination1.w && mousePos.y >= destination1.y && mousePos.y < destination1.y+destination1.h)
    {
        return true;
    }
    return false;
}

void PauseScreen::render()
{
    SDL_SetRenderDrawColor(cRenderer,0,255,0,255);
    SDL_RenderFillRect(cRenderer,&destination1);
    SDL_SetRenderDrawColor(cRenderer,255,0,0,255);
    SDL_RenderFillRect(cRenderer,&destination2);
    resume->render(destination1.x,destination1.y);
    exit->render(destination2.x,destination2.y);
    SDL_SetRenderDrawColor(cRenderer,0,0,255,255);
}