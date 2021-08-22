#include "Enemy2.h"
#include "defaultVar.h"

Enemy2::Enemy2(SDL_Renderer* renderer, vec pos)
{
    ePos = pos;

    eTexture = new TextureWrapper(renderer);
    if(!eTexture->loadFromFile("graphics/spriteSheet/zombie2.png"))
    {
        std::cout << "Failed to load enemy.\n";
    }

    dead = false;
    stopRendering = false;
}


int Enemy2::update(vec pPos, SDL_Rect Bullet) //2 for collsion with bullet
{
    if(!dead)
    {
        SDL_Rect pRect = {pPos.x, pPos.y, playerWidth, playerHeight};
        SDL_Rect eRect = {ePos.x, ePos.y, eTexture->getWidth()/6, eTexture->getHeight()};

        if(!(pRect.x < (eRect.x + eRect.w) && (pRect.x + pRect.w) > eRect.x &&
            pRect.y < (eRect.y + eRect.h) && (pRect.y + pRect.h) > eRect.y))
        {
            //Shoot
            float dsquare = (pPos.x-ePos.x)*(pPos.x-ePos.x) + (pPos.y-ePos.y)*(pPos.y-ePos.y);
            if(dsquare <= 1000)
            {
                return 1;
            }
        }
        if (Bullet.x < (eRect.x + eRect.w) && (Bullet.x + Bullet.w)> eRect.x &&
            Bullet.y < (eRect.y + eRect.h) && (Bullet.y + Bullet.h) > eRect.y)
        {
            dead = true;
            return 2;
        }
    }

    return 0;
}

void Enemy2::render(SDL_Rect camera)
{
    // SDL_RendererFlip flip = eVel.x > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    // int num = (int) ((SDL_GetTicks()/100)%6);
    // SDL_Rect src = {num* eTexture->getWidth()/6 + 4, 0 , eTexture->getWidth()/6, eTexture->getHeight()};
    // SDL_Rect dest = {ePos.x - camera.x , ePos.y - camera.y , eTexture->getWidth()/6 , eTexture->getHeight()};
    // if (dead && !stopRendering)
    // {
    //     int time = SDL_GetTicks()/1000;
    //     int num = (int) ((SDL_GetTicks()/100)%3);
    //     SDL_Rect src = {num* e2Texture->getWidth()/3 , 0 , e2Texture->getWidth()/3, e2Texture->getHeight()};
    //     SDL_Rect dest = {ePos.x - camera.x , ePos.y - camera.y , e2Texture->getWidth()/3 , e2Texture->getHeight()};
    //     e2Texture->render(src,dest);
    //     if (time > 7)
    //     {
    //         stopRendering = true;
    //     }
    // }
    // else if(!dead)
    // {
    //     eTexture->render(src, dest, 0.0, flip);
    // }
}

Enemy2::~Enemy2()
{
    // delete eTexture;
    // delete e2Texture;
}