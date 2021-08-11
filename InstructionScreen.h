#pragma once
#include "Texture.h"
#include "math.h"

class InstructionScreen
{
    private:
        TextureWrapper* Instruction;
        TextureWrapper* returnText;
        SDL_Rect source,destination;
        SDL_Rect text;
        SDL_Renderer* cRenderer;
    public:
        InstructionScreen(SDL_Renderer* pRenderer);
        ~InstructionScreen();
        void render();
        bool isInsideReturn(vec mousePos);
};