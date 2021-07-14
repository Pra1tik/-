#include "game.h"
#include "Player.h"
#include "Tilemap.h"
#include "collider.h"

bool Game::init(const char* title,int xpos, int ypos, int height, int width, bool flags)
{
   
    Uint32 windowState;
    if (!flags)
    {
        windowState=SDL_WINDOW_SHOWN;
    }
    else
    {
        height = SDL_WINDOW_FULLSCREEN;
        width = SDL_WINDOW_FULLSCREEN;
        windowState=SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING)>=0){
        pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,windowState);
        if(pWindow!=0){
            pRenderer=SDL_CreateRenderer(pWindow,-1,0);
            if (pRenderer!=0){
                SDL_SetRenderDrawColor(pRenderer,0,0,255,255);
                player = new Player(pRenderer);

            }
            else{
                std::cout << "Error " <<SDL_GetError()<<std::endl;
                return false;
            }
        }
        else{
            return false;
        }
        back = new Background(pRenderer);
        back->load();
        pCollider= new collider();
        tCollider= new collider();
        runGame= true;
        return true;
    }

    return false;
}
void Game::render()
{
    SDL_RenderClear(pRenderer);
    back->render();
    player->render();
    SDL_RenderPresent(pRenderer);
}

void Game::update()
{
   if(!(colX&&colY)) {player->update(tileBelow);}
//    else if (colX&&colY) {player->CollisionUpdate(offsetValue);}
}

void Game::clean()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}
void Game::handleEvents(float deltaTime)
{
    dt = deltaTime;
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            runGame=false;
        }
        else
        {
           
            player->handleInput(event, dt);

        }
    }
    Collider(player,back);

}

void Game::Collider(Player* player,Background* back)
{   
    // vec collidedTile;
    vec player1=player->getPosition();
    SDL_Rect pCol{player1.x,player1.y,80,110};
    pCollider->setRect(pCol);
    
    for (int row {0};row<12;row++)
    {
        for ( int column{0};column<16;column++)
        {
            SDL_Rect pTil{back->getPosXTiles(row,column),back->getPosYTiles(row,column),48,48};
            tCollider->setRect(pTil);
            vec tile={column,row};
            // std::cout<<back->getPosYTiles(row,column)<<std::endl;
            if (back->getTileNum(row,column)==1)
            {
            if(pCollider->checkCollision(*tCollider,0.0f))
            {
                
                colY=true;
                colX=true;
                // std::cout << tCollider->GetPositionY()<<"   "<<row<<std::endl;
                // collidedTile.y=row;
                // collidedTile.x=column;
                vec offset=pCollider->getOffset();
                if (pCollider->GetPositionX()>tCollider->GetPositionX()){offset.x*=-1;}
                if (pCollider->GetPositionX()<tCollider->GetPositionX() && pCollider->GetPositionX()+80>tCollider->GetPositionX()+48){offset.x=0;}
                if (pCollider->GetPositionX()>tCollider->GetPositionX() && pCollider->GetPositionX()<tCollider->GetPositionX()+48){offset.x=0;}
                // if (pCollider->GetPositionY()>tCollider->GetPositionY() && pCollider->GetPositionY()<tCollider->GetPositionY()+48){offset.y=0;}
                if (pCollider->GetPositionY()>tCollider->GetPositionY()){offset.y*=-1;}
                // if (pCollider->GetPositionY()<tCollider->GetPositionY()+48){offset.y=0;}
                // std::cout << "collision detected in y-axis with tile "<<column<<"   "<<row<<"     "<<count++<<std::endl;
                player->CollisionUpdate(offset,tile);
                break;
            }
            else
            {
                tileBelow=back->getTileNum(row+1,column);
                colY=false;
                colX=false;
            }
            // if(player1.x+80>=TileX && TileX+48>=player1.x )
            // {
            //     colXPos=true;
            //     collidedTileX=column;
            //     std::cout << "collision detected in x-axis with tile "<<row<<"   "<<column<<"     "<<count++<<std::endl;
            //     break;
            // }
            // else{
            //     colXPos=false;
            // }
            }     
        }
    }
}
