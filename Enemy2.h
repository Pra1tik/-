#pragma once
#include "Texture.h"
#include "math.h"

class Enemy2
{
    public:
        Enemy2(SDL_Renderer* renderer, vec pos);
        ~Enemy2();

        int update(vec pPos, SDL_Rect Bullet);
        void render(SDL_Rect camera, vec pPos);


        vec ePos;
        TextureWrapper* eTexture;
        bool dead;
        int nextShot = 0;
    private:
        bool stopRendering;  
};


