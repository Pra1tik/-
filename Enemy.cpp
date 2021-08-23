#include "Enemy.h"
#include "defaultVar.h"

Enemy::Enemy(SDL_Renderer* renderer, vec pos, vec range)
{
    //ePos = {64, 1536 - 52};
    //xRange = {64, 640};
    ePos = pos;
    xRange = range;
    eVel = {2, 0};

    eTexture = new TextureWrapper(renderer);
    e2Texture = new TextureWrapper(renderer);
    //eTexture->loadFromFile("graphics/char.png");
    if(!eTexture->loadFromFile("graphics/spriteSheet/zombie2.png"))
    {
        std::cout << "Failed to load enemy.\n";
    }
    e2Texture->loadFromFile("graphics/spriteSheet/zombie_die.png");

    dead = false;

    stopRendering = false;
}


int Enemy::update(vec pPos) //2 for collsion with bullet
{
    if(!dead)
    {
        SDL_Rect pRect = {pPos.x, pPos.y, playerWidth, playerHeight};
        SDL_Rect eRect = {ePos.x, ePos.y, eTexture->getWidth()/6, eTexture->getHeight()};

        // if(bulletAlive)
        // {
        //     if (Bullet.x < (eRect.x + eRect.w) && (Bullet.x + Bullet.w)> eRect.x &&
        //         Bullet.y < (eRect.y + eRect.h) && (Bullet.y + Bullet.h) > eRect.y)
        //     {
        //         dead = true;
        //         return 2;
        //     }
        // }
        

        if(!(pRect.x < (eRect.x + eRect.w) && (pRect.x + pRect.w) > eRect.x &&
            pRect.y < (eRect.y + eRect.h) && (pRect.y + pRect.h) > eRect.y))
        {
            if(ePos.x < xRange.x || ePos.x + eTexture->getWidth()/6 > xRange.y)
            {
                eVel.x *= -1;
            }

            ePos.x += eVel.x;

        }
        else
        {
            //collision with player
            return 3;
        }
        
    }

    return 0;
}

bool Enemy::bulletEnemyCollision(SDL_Rect Bullet)
{
    SDL_Rect eRect = {ePos.x, ePos.y, eTexture->getWidth()/6, eTexture->getHeight()};
    
   if(Bullet.x < (eRect.x + eRect.w) && (Bullet.x + Bullet.w)> eRect.x &&
            Bullet.y < (eRect.y + eRect.h) && (Bullet.y + Bullet.h) > eRect.y)
    {
        dead = true;
        return true;
    }

    return false;
}

void Enemy::render(SDL_Rect camera)
{
    SDL_RendererFlip flip = eVel.x > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    int num = (int) ((SDL_GetTicks()/100)%6);
    SDL_Rect src = {num* eTexture->getWidth()/6 + 4, 0 , eTexture->getWidth()/6, eTexture->getHeight()};
    SDL_Rect dest = {ePos.x - camera.x , ePos.y - camera.y , eTexture->getWidth()/6 , eTexture->getHeight()};
    if (dead && !stopRendering)
    {
        int time = SDL_GetTicks()/1000;
        int num = (int) ((SDL_GetTicks()/100)%3);
        SDL_Rect src = {num* e2Texture->getWidth()/3 , 0 , e2Texture->getWidth()/3, e2Texture->getHeight()};
        SDL_Rect dest = {ePos.x - camera.x , ePos.y - camera.y , e2Texture->getWidth()/3 , e2Texture->getHeight()};
        e2Texture->render(src,dest);
        if (time > 7)
        {
            stopRendering = true;
        }
    }
    else if(!dead)
    {
        eTexture->render(src, dest, 0.0, flip);
    }
}

Enemy::~Enemy()
{
    // delete eTexture;
    // delete e2Texture;
}