#pragma once
#include "Character.h"
#include <SDL2/SDL.h>
#include "defaultVar.h"

class Player : public Character
{
    public:
        Player(SDL_Renderer* renderer);

        void update() override;
        void render(SDL_Rect rect) override;
        void handleInput(SDL_Event& e, float deltaTime);
        void CollisionUpdate (vec offset,int tileRow[], int tiles);
        void animate();

        bool leftFacing = false, rightFacing = true;

    private:
        int mlives = 3;
        float dt = 0;
        bool mAlive = true;
        bool jumpFlag = false;
        bool isJumping = false;
        bool isShooting = false;
        int gravity = 30;
        const int imp = 900;
        const int fall = 0;
        bool falling=false;
        int tileRowPlayerClass[100];
        int count=0;
        vec previousOffset {0,0};
        vec currentFrame{0,0};
        SDL_RendererFlip flip;
        int pTiles;
};