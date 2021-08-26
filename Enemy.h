#pragma once
#include "enemyBase.h"

class Enemy : public EnemyBase
{
    public:
        Enemy(SDL_Renderer* renderer, vec pos, vec range);
        ~Enemy();

        int update(vec pPos) override;
        bool bulletEnemyCollision(const SDL_Rect& Bullet) override;
        void render(const SDL_Rect& camera, vec pPos = vec{0,0}) override;


    private:
        vec xRange, yRange;
        TextureWrapper* eTexture;
        TextureWrapper* e2Texture;      
};


