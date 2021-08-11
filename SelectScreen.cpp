#include "SelectScreen.h"

SelectScreen::SelectScreen(SDL_Renderer* pRenderer)
{
    cRenderer = pRenderer;
    pTTF = TTF_OpenFont("graphics/Fonts/pacifico/Pacifico.ttf",60);
    playText = new TextureWrapper(pRenderer,pTTF);
    exitText = new TextureWrapper(pRenderer,pTTF);
    instructionText = new TextureWrapper(pRenderer,pTTF);
    SDL_Color color = {0,0,0};
    playText->loadFromRenderedText("PLAY",color);
    exitText->loadFromRenderedText("EXIT",color);
    instructionText->loadFromRenderedText("INSTRUCTION",color);
    playButton = {WindowWidth/2-playText->getWidth()/2, 210, playText->getWidth(), playText->getHeight()};
    instructionButton = {WindowWidth/2-instructionText->getWidth()/2, 360, instructionText->getWidth(), instructionText->getHeight()};
    exitButton = {WindowWidth/2-exitText->getWidth()/2, 510, exitText->getWidth(), exitText->getHeight()};
}

void SelectScreen::render()
{

    //render rects
    
    SDL_SetRenderDrawColor(cRenderer,0,255,0,255);
    SDL_RenderFillRect(cRenderer,&playButton);
    SDL_SetRenderDrawColor(cRenderer,255,0,0,255);
    SDL_RenderFillRect(cRenderer,&exitButton);
    SDL_SetRenderDrawColor(cRenderer,255,255,0,255);
    SDL_RenderFillRect(cRenderer,&instructionButton);

    //render texts

    playText->render(playButton.x,playButton.y);
    exitText->render(exitButton.x,exitButton.y);
    instructionText->render(instructionButton.x,instructionButton.y);
    SDL_SetRenderDrawColor(cRenderer,0,0,255,255);
}

bool SelectScreen::isInsidePlay(vec mousePos)
{
    if (mousePos.x >= playButton.x && mousePos.x < playButton.x+playButton.w && mousePos.y >= playButton.y && mousePos.y < playButton.y+playButton.h)
    {
        return true;
    }
    return false;
}

bool SelectScreen::isInsideExit(vec mousePos)
{
    if (mousePos.x >= exitButton.x && mousePos.x < exitButton.x+exitButton.w && mousePos.y >= exitButton.y && mousePos.y < exitButton.y+exitButton.h)
    {
        return true;
    }
    return false;
}

bool SelectScreen::isInsideInstruction(vec mousePos)
{
    if (mousePos.x >= instructionButton.x && mousePos.x < instructionButton.x+instructionButton.w && mousePos.y >= instructionButton.y && mousePos.y < instructionButton.y+instructionButton.h)
    {
        return true;
    }
    return false;
}