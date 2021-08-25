#pragma once
#include "GameStateManager.h"
#include "Texture.h"
#include "defaultVar.h"
#include "math.h"


class PauseScreen : public GameStateManager
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
        void render() override;
        bool isInsideExit(vec mousePos);
        bool isInsideResume(vec mousePos);
};