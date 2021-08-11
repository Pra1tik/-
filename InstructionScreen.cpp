#include "InstructionScreen.h"
#include "defaultVar.h"
#include <SDL2/SDL_ttf.h>

InstructionScreen::InstructionScreen(SDL_Renderer* pRenderer)
{
    cRenderer = pRenderer;
    TTF_Font* font = TTF_OpenFont("graphics/Fonts/pacifico/Pacifico.ttf",50);
    SDL_Color color = {0,0,0};
    Instruction = new TextureWrapper(pRenderer);
    returnText = new TextureWrapper(pRenderer,font);
    Instruction->loadFromFile("graphics/intro.jpg");
    returnText->loadFromRenderedText("RETURN",color);
    source = {0,0,Instruction->getWidth(),Instruction->getHeight()};
    destination = {0,0,WindowWidth,WindowHeight};
    text = {WindowWidth/2-returnText->getWidth()/2,WindowHeight-returnText->getHeight()-50,returnText->getWidth(),returnText->getHeight()};
}

void InstructionScreen::render()
{
    Instruction->render(source,destination);
    SDL_SetRenderDrawColor(cRenderer,0,255,255,255);
    SDL_RenderFillRect(cRenderer,&text);
    returnText->render(text.x,text.y);
    SDL_SetRenderDrawColor(cRenderer,0,0,255,255);
}

bool InstructionScreen::isInsideReturn(vec mousePos)
{
    if (mousePos.x >= text.x && mousePos.x < text.x+text.w && mousePos.y >= text.y && mousePos.y < text.y+text.h)
    {
        return true;
    }
    return false;
}

InstructionScreen::~InstructionScreen()
{
    delete Instruction;
}