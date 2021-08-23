#pragma once
#include "Texture.h"
#include "math.h"

class Enemy2
{
    public:
        Enemy2(SDL_Renderer* renderer, vec pos);
        ~Enemy2();

        int update(vec pPos);
        void render(SDL_Rect camera, vec pPos);
        bool bulletEnemyCollision(const SDL_Rect& Bullet);
        bool arrowPlayerCollision(const SDL_Rect& player);

        vec ePos;
        TextureWrapper* eTexture;
        bool dead;
        int nextShot = 0;

        struct arrow
        {
            vec arrowtPos;
            vec arrowVel = {10, 2};
            bool shootFlag = false;
            bool arrowAlive = false;
        };
        arrow arrow1;
        
    private:
        bool stopRendering;
        TextureWrapper* arrowTexture;  
};


