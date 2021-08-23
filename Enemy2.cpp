#include "Enemy2.h"
#include "defaultVar.h"

Enemy2::Enemy2(SDL_Renderer* renderer, vec pos)
{
    ePos = pos;

    eTexture = new TextureWrapper(renderer);
    if(!eTexture->loadFromFile("graphics/spriteSheet/archer112.png"))
    {
        std::cout << "Failed to load enemy.\n";
    }

    arrowTexture = new TextureWrapper(renderer);
    arrowTexture->loadFromFile("graphics/newBullet.png");

    dead = false;
    stopRendering = false;
}


int Enemy2::update(vec pPos) 
{
    if(!dead)
    {
        SDL_Rect pRect = {pPos.x, pPos.y, playerWidth, playerHeight};
        SDL_Rect eRect = {ePos.x, ePos.y, eTexture->getWidth()/6, eTexture->getHeight()};

        if(arrow1.arrowAlive)
        {
            arrow1.arrowtPos.x += arrow1.arrowVel.x;

            if(abs(arrow1.arrowtPos.x - pPos.x) >= 500)
            {
                arrow1.arrowAlive = false;
            }
        }

        
        if(!(pRect.x < (eRect.x + eRect.w) && (pRect.x + pRect.w) > eRect.x &&
            pRect.y < (eRect.y + eRect.h) && (pRect.y + pRect.h) > eRect.y))
        {
           //Shoot the player
            int dx = abs(pPos.x-ePos.x);
            int dy = abs(pPos.y - ePos.y);
            if(!arrow1.arrowAlive && dx <= 3000 && dy <= playerHeight)
            {
                //std::cout << "SHoot" << std::endl;
                arrow1.arrowAlive = true;
                arrow1.arrowtPos = {ePos.x, ePos.y+eTexture->getHeight()/2};

                arrow1.arrowVel.x = (pPos.x >= ePos.x ? 10 : -10);
            }
                
        }
        else
        {
            return 3;
        }
        
    }

    return 0;
}

bool Enemy2::bulletEnemyCollision(const SDL_Rect& Bullet)
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

bool Enemy2::arrowPlayerCollision(const SDL_Rect& playerRect)
{
    if(arrow1.arrowAlive)
    {
        SDL_Rect arrowRect = {arrow1.arrowtPos.x, arrow1.arrowtPos.y, arrowTexture->getWidth(), arrowTexture->getHeight()};
    
        if(arrowRect.x < (playerRect.x + playerRect.w) && (arrowRect.x + arrowRect.w)> playerRect.x &&
                    arrowRect.y < (playerRect.y + playerRect.h) && (arrowRect.y + arrowRect.h) > playerRect.y)
        {
            //std::cout << "Collide" << std::endl;
            arrow1.arrowAlive = false;
            return true;
        }
    }

    return false;
}

void Enemy2::render(SDL_Rect camera, vec pPos)
{
    SDL_RendererFlip flip = ePos.x > pPos.x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    int num = (int) ((SDL_GetTicks()/100)%11);
    SDL_Rect src = {/*(num2+1)*/eTexture->getWidth()/22 , 0 , eTexture->getWidth()/22, eTexture->getHeight()};
    SDL_Rect dest = {ePos.x - camera.x , ePos.y - camera.y , eTexture->getWidth()/11 , eTexture->getHeight()};
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
    if(!dead)
    {
        eTexture->render(src, dest, 0.0, flip);
    }

    if(arrow1.arrowAlive)
    {
        arrowTexture->render(arrow1.arrowtPos.x-camera.x, arrow1.arrowtPos.y-camera.y);
    }
}

Enemy2::~Enemy2()
{
    // delete eTexture;
    // delete e2Texture;
}