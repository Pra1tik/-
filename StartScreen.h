#pragma once
#include "Texture.h"
#include "defaultVar.h"


class StartScreen
{
    private:
        SDL_Rect source,destination;
        TextureWrapper* para;
    public:
        StartScreen (SDL_Renderer* pRenderer);
        ~StartScreen ();
        void render();
};