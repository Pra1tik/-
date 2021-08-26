#pragma once
#include "Texture.h"
#include "math.h"

class EnemyBase
{
    public:
        virtual int update(vec pPos) = 0;
        virtual bool bulletEnemyCollision(const SDL_Rect& Bullet) = 0;
        virtual void render(const SDL_Rect& camera, vec pPos = vec{0, 0}) = 0;
     
        bool dead;
        
    protected:
        vec ePos, eVel;
        int nextShot = 0;
        int deadFrame;
        bool stopRendering;
        int counter = 0;  
};