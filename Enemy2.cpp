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
    arrowTexture->loadFromFile("graphics/Arrow.png");

    dead = false;
    stopRendering = false;
    currentFrame = 0;
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

            if(abs(arrow1.arrowtPos.x - pPos.x) >= WindowWidth)
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
            if(!arrow1.arrowAlive && dx <= WindowWidth && dy <= playerHeight)
            {
                animate();
                arrow1.arrowAlive = true;
                arrow1.arrowtPos = {ePos.x, ePos.y+eTexture->getHeight()/2 - 20};

                arrow1.arrowVel.x = (pPos.x >= ePos.x ? 8 : -8);
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
        
        arrow1.arrowAlive = false;
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
    SDL_Rect src = {currentFrame * eTexture->getWidth()/22 , 0 , eTexture->getWidth()/22, eTexture->getHeight()};
    SDL_Rect dest = {ePos.x - camera.x , ePos.y - camera.y , eTexture->getWidth()/11 , eTexture->getHeight()};
    if(!dead)
    {
        eTexture->render(src, dest, 0.0, flip);
    }
    else if (dead && !stopRendering)
    {
        double angle;
        flip = SDL_FLIP_HORIZONTAL ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
        if (flip ==  SDL_FLIP_VERTICAL)
        {
            angle =  270;
        }
        else
        {
            angle = 90;
        }
        counter++;
        eTexture->render(src,{dest.x , dest.y+30,dest.w, dest.h}, angle, flip);
        if (counter > 120)
        {
            stopRendering = true;
        }
    }

    if(arrow1.arrowAlive)
    {
        double angle = ePos.x > pPos.x ? 180.0 : 0.0;
        arrowTexture->render(arrow1.arrowtPos.x-camera.x, arrow1.arrowtPos.y-camera.y, NULL, 1,angle);
    }
}

void Enemy2::animate()
{
    currentFrame += 2;
    if (currentFrame >= 5)
    {
        currentFrame = 0;
    }
    if (dead)
    {
        currentFrame = 0;
    }
}

Enemy2::~Enemy2()
{
    // delete eTexture;
    // delete e2Texture;
}