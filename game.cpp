#include "game.h"
#include "Player.h"
#include "Tilemap.h"
#include "collider.h"
#include "Level.h"

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

                //Level object
                level = new Level("graphics/lv1.txt", pRenderer, 1);


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

    level->render();
    SDL_RenderPresent(pRenderer);
}

void Game::update()
{
    for(int i(0);i<TotalTilesRow;i++){if (tilesOfCollidedRow[i]>0){tileFlag=true;break;} }
    if (tileFlag) {player->update(playerXpos,tilesOfCollidedRow);}
    else {player->update(playerXpos,NULL);}
    for (int i{0};i<TotalTilesRow;i++){tilesOfCollidedRow[i]=0;}
    tileFlag=false;

    level->update(player->getPosition(), player->getTexture());
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
    ///*  
    vec player1=player->getPosition();
    SDL_Rect pCol{player1.x,player1.y,80,110};
    pCollider->setRect(pCol);
    
    for (int row {0};row<TotalTilesColumn;row++)
    {
        for ( int column{0};column<TotalTilesRow;column++)
        {
            SDL_Rect pTil{back->getPosXTiles(row,column),back->getPosYTiles(row,column)-25,50,50};  // y is subtracted by the half of tilewidth to make player stay on the top of tile
            tCollider->setRect(pTil);
            // std::cout<<back->getPosYTiles(row,column)<<std::endl;
            if (back->getTileNum(row,column)==1)
            {
            if(pCollider->checkCollision(*tCollider,0.0f))
            {
                for (int i{0};i<TotalTilesRow;i++){tilesOfCollidedRow[i]=(back->getTileNum(row,i));}
                vec offset=pCollider->getOffset();
                if (pCollider->GetPositionX()>tCollider->GetPositionX()){offset.x*=-1;}
                // if (pCollider->GetPositionX()>tCollider->GetPositionX()+50){offset.x/=2;}
                if (pCollider->GetPositionX()<tCollider->GetPositionX() && pCollider->GetPositionX()+80>tCollider->GetPositionX()+48){offset.x=0;}
                if (pCollider->GetPositionX()>tCollider->GetPositionX() && pCollider->GetPositionX()<tCollider->GetPositionX()+48){offset.x=0;}
                if (pCollider->GetPositionY()>tCollider->GetPositionY())
                {
                    offset.y*=-1;
                    for (int i{0};i<TotalTilesRow;i++){tilesOfCollidedRow[i]= 2;} //while jumping make the tiles as open space
                }
                
                player->CollisionUpdate(offset);
                break;
            }
            else
            {
                playerXpos=pCollider->GetPositionX();
            }
            }     
        }
    }
    //*/
}
