#pragma once
#include "Texture.h"
#include "defaultVar.h"
#include "math.h"


class PauseScreen
{
    private:
        SDL_Rect destination1,destination2;
        TextureWrapper* para;
        SDL_Renderer* cRenderer;
        TextureWrapper* resume;
        TextureWrapper* exit;
    public:
        PauseScreen (SDL_Renderer* pRenderer);
        ~PauseScreen ();
        void render();
        bool isInsideExit(vec mousePos);
        bool isInsideResume(vec mousePos);
};