#pragma once
#include "enemyBase.h"

class Enemy2 : public EnemyBase
{
    public:
        Enemy2(SDL_Renderer* renderer, vec pos);
        ~Enemy2();

        int update(vec pPos) override;
        void render(const SDL_Rect& camera, vec pPos = vec{0,0}) override;
        bool bulletEnemyCollision(const SDL_Rect& Bullet) override;
        bool arrowPlayerCollision(const SDL_Rect& player);
        void animate();

        
        TextureWrapper* eTexture;
        

        struct arrow
        {
            vec arrowtPos;
            vec arrowVel = {10, 2};
            bool shootFlag = false;
            bool arrowAlive = false;
        };
        arrow arrow1;
        TextureWrapper* arrowTexture;  
        
    private:       
        int currentFrame;
        int time;
        SDL_RendererFlip arrFlip;
};


