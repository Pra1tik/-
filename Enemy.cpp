#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer)
{
    ePos = {64, 1536};
    eVel = {2, 0};
    xRange = {64, 640};

    eTexture = new TextureWrapper(renderer);
    //eTexture->loadFromFile("graphics/char.png");
    if(!eTexture->loadFromFile("graphics/char.png"))
    {
        std::cout << "Failed to load enemy.\n";
    }
    dead = false;
}


int Enemy::update(vec pPos)
{
    if(!dead)
    {
        SDL_Rect pRect = {pPos.x, pPos.y, 64, 64};
        SDL_Rect eRect = {ePos.x, ePos.y, eTexture->getWidth(), eTexture->getHeight()};

        if(!(pRect.x < (eRect.x + eRect.w) && (pRect.x + pRect.w) > eRect.x &&
            pRect.y < (eRect.y + eRect.h) && (pRect.y + pRect.h) > eRect.y))
        {
            if(ePos.x < xRange.x || ePos.x + eTexture->getWidth() > xRange.y)
            {
                eVel.x *= -1;
            }

            ePos.x += eVel.x;

            //Shoot
            float dsquare = (pPos.x-ePos.x)*(pPos.x-ePos.x) + (pPos.y-ePos.y)*(pPos.y-ePos.y);
            if(dsquare <= 1000)
            {
                return 1;
            }
        }
    }

    return 0;
}

void Enemy::render(SDL_Rect camera)
{
    if(!dead)
    {
        eTexture->render(ePos.x - camera.x, ePos.y - camera.y);
    }
}