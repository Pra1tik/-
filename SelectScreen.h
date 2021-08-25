#pragma once
#include "GameStateManager.h"
#include "Texture.h"
#include "defaultVar.h"
#include "math.h"
#include <SDL2/SDL_ttf.h>

class SelectScreen : public GameStateManager
{
    private:
        SDL_Rect playButton;
        SDL_Rect instructionButton;
        SDL_Rect exitButton;
        TextureWrapper* playText;
        TextureWrapper* exitText;
        TextureWrapper* instructionText;
        SDL_Surface* pB;
        SDL_Surface* eB;
        SDL_Renderer* cRenderer;
        TTF_Font* pTTF;
    public:
        SelectScreen (SDL_Renderer* pRenderer);
        ~SelectScreen ();
        void render() override;
        bool isInsidePlay(vec mousePos);
        bool isInsideExit(vec mousePos);
        bool isInsideInstruction(vec mousePos);
};