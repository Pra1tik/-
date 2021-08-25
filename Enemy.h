#pragma once
#include "Texture.h"
#include "math.h"

class Enemy
{
    public:
        Enemy(SDL_Renderer* renderer, vec pos, vec range);
        ~Enemy();

        int update(vec pPos);
        bool bulletEnemyCollision(SDL_Rect Bullet);
        void render(SDL_Rect camera);

        int getDeadEnemies() {return deadEnemies;}

        vec ePos, eVel;
        vec xRange, yRange;
        TextureWrapper* eTexture;
        TextureWrapper* e2Texture;
        bool dead;
        int nextShot = 0;
        bool die = false;
        int deadFrame;
        int deadEnemies;
    private:
        bool stopRendering;
        int counter = 0;  
};


