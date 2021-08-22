#pragma once
#include "Texture.h"
#include "math.h"

class Enemy
{
    public:
        Enemy(){}
        Enemy(SDL_Renderer* renderer, vec pos, vec range);
        ~Enemy();

        void init(SDL_Renderer* renderer, vec pos, vec range);
        int update(vec pPos, SDL_Rect Bullet);
        void render(SDL_Rect camera);


        vec ePos, eVel;
        vec xRange, yRange;
        TextureWrapper* eTexture;
        TextureWrapper* e2Texture;
        bool dead;
        int nextShot = 0;
        bool die = false;
    private:
        bool stopRendering;  
};


