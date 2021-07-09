#pragma once
#include "Character.h"
#include <SDL2/SDL.h>

class Player : public Character
{
    public:
        Player(SDL_Renderer* renderer);

        void update() override;
        void render() override;
        void handleInput(SDL_Event& e, float deltaTime);

    private:
        int mlives = 3;
        float dt = 0;
        bool mAlive = true;
        bool jumpFlag = false;
        int gravity = 30;
        const int imp = 900;
};