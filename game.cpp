#include "game.h"
#include "Player.h"
#include "collider.h"
#include "StartScreen.h"
#include "SelectScreen.h"
#include "InstructionScreen.h"
#include "PauseScreen.h"
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
                level = new Level("graphics/level1.txt", pRenderer, 1);


            }
            else{
                std::cout << "Error " <<SDL_GetError()<<std::endl;
                return false;
            }
            if (TTF_Init() == -1)
            {
                std::cout << "Error initializing ttf" << TTF_GetError() << std::endl;
                return false;
            }
        }
        else{
            return false;
        }
        pCollider= new collider();
        tCollider= new collider();
        startScreen = new StartScreen(pRenderer);
        selectScreen = new SelectScreen(pRenderer);
        controls = new InstructionScreen(pRenderer);
        paused = new PauseScreen(pRenderer);
        runGame= true;
        currentGameState = START_SCREEN;

        //For enemy
        enemies = new Enemy(pRenderer);

        //For bullet
        playerBullet = new bullet;
        bulletTexture = new TextureWrapper(pRenderer);
        bulletTexture->loadFromFile("graphics/newBullet.png");

        return true;
    }

    return false;
}
void Game::render()
{
    enemyDead = enemies->dead;
    SDL_RenderClear(pRenderer);
    switch (currentGameState)
    {
        case START_SCREEN:
            startScreen->render();
            break;
        case GAME_SCREEN:
            level->render();
            player->render(level->camera);
            // if (!enemyDead)
            // {
            //     enemies->render(level->camera);
            // }
            enemies->render(level->camera);

            if(playerBullet->bulletAlive)
            {
                bulletTexture->render(playerBullet->bulletPos.x - level->camera.x, playerBullet->bulletPos.y - level->camera.y);
            }

            break;
        case SELECT_SCREEN:
            selectScreen->render();
            break;
        case INSTRUCTIONS_SCREEN:
            controls->render();
            break;
        case PAUSE_SCREEN:
            paused->render();
            break;
        default:
            break;
    };
    SDL_RenderPresent(pRenderer);
}

void Game::update()
{
    enemyDead = enemies->dead;
    switch (currentGameState)
    {
        case (GAME_SCREEN):
            player->animate();
            player->update();
            level->update(player->getPosition(),player->getTexture());
            // if (!enemyDead)
            // {
            //     enemies->update(player->getPosition());
            // }
            // else
            // {
            //     enemies->~Enemy();
            // }
            if (player->shake)
            {
                level->shake = true;
            }
            else
            {
                level->shake = false;
            }
            enemies->update(player->getPosition());

            //For bullet
            if(playerBullet->bulletAlive)
            {
                playerBullet->bulletPos = {playerBullet->bulletPos.x+playerBullet->bulletVel.x, playerBullet->bulletPos.y};
                //mBulletTexture.render(pBullet.bulletPos.x - camera.x, pBullet.bulletPos.y - camera.y);

                if(playerBullet->bulletPos.x > level->camera.x + WindowWidth)
                {
                    playerBullet->bulletAlive = false;
                } 
                else
                {
                    int bulletX = playerBullet->bulletPos.x / (level->tileWidth * level->scale);
                    int bulletY = playerBullet->bulletPos.y / (level->tileHeight * level->scale);
                    SDL_Rect bulletRect = {playerBullet->bulletPos.x, playerBullet->bulletPos.y, bulletTexture->getWidth(), bulletTexture->getHeight()};
                    
                    for(int i = 0; i < 1; i++)
                    {
                        for(int j = 0; j < 2; j++)
                        {
                            if(bulletY+i < level->mRow && bulletX+j < level->mCol)
                            {
                                if(level->mTileMatrix[bulletY+i][bulletX+j] != -1)
                                {
                                    SDL_Rect tile = {(bulletX+i)*level->tileWidth*level->scale, (bulletY+j)*level->tileHeight*level->scale, level->tileWidth*level->scale, level->tileHeight*level->scale};

                                    if(bulletRect.x < (tile.x + tile.w) && (bulletRect.x + bulletRect.w) > tile.x &&
                                            bulletRect.y < (tile.y + tile.h) && (bulletRect.y + bulletRect.h) > tile.y )
                                    {
                                        playerBullet->bulletAlive = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            break;
        case (START_SCREEN):
            break;
        case (SELECT_SCREEN):
            break;
        case (PAUSE_SCREEN):
            break;
        default:
            break;
    }
}

void Game::clean()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}
void Game::handleEvents(float deltaTime)
{
    SDL_GetMouseState(&mousePos.x,&mousePos.y);
    dt = deltaTime;
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT || currentGameState == EXIT_SCREEN)
        {

            runGame=false;
        }
        else if (event.key.keysym.sym== SDLK_SPACE && currentGameState == START_SCREEN)
        {

            currentGameState = SELECT_SCREEN;
        }
        else if(currentGameState == SELECT_SCREEN && selectScreen->isInsidePlay(mousePos))
        {
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
    
                currentGameState = GAME_SCREEN;
            }
        }
        else if(currentGameState == SELECT_SCREEN && selectScreen->isInsideExit(mousePos))
        {
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
    
                currentGameState = EXIT_SCREEN;
            }
        }
        else if(currentGameState == SELECT_SCREEN && selectScreen->isInsideInstruction(mousePos))
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
    
                currentGameState = INSTRUCTIONS_SCREEN;
            }
        }
        else if(currentGameState == INSTRUCTIONS_SCREEN && controls->isInsideReturn(mousePos))
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
    
                currentGameState = SELECT_SCREEN;
            }
        }
        else if (currentGameState == GAME_SCREEN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            currentGameState = PAUSE_SCREEN;
        }
        else if (currentGameState ==  PAUSE_SCREEN && paused->isInsideResume(mousePos))
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                currentGameState = GAME_SCREEN;
            }
        }
        else if (currentGameState ==  PAUSE_SCREEN && paused->isInsideExit(mousePos))
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                currentGameState = EXIT_SCREEN;
            }
        }
        else if (currentGameState == GAME_SCREEN)
        {

            player->handleInput(event, dt);
            
            //For shooting
            const Uint8* state = SDL_GetKeyboardState(NULL);
            
            if(state[SDL_SCANCODE_LSHIFT] && !playerBullet->shootFlag && !playerBullet->bulletAlive)
            {
                playerBullet->bulletAlive = true;
                playerBullet->shootFlag = true;

                vec bulletSpawnPos;

                if (player->rightFacing)
                {
                    bulletSpawnPos = {player->getPosition().x +playerWidth , player->getPosition().y + 55};
                }
                else
                {
                    bulletSpawnPos = {player->getPosition().x , player->getPosition().y + 55};
                }
                playerBullet->bulletPos = bulletSpawnPos;
                playerBullet->bulletVel.x = (player->leftFacing ? -12 : 12);
            }
            else if(!state[SDL_SCANCODE_LCTRL])
            {
                playerBullet->shootFlag = false;
            }
        }
    }
    if (currentGameState == GAME_SCREEN)
    {
        Collider(player,level);

    }
}

void Game::Collider(Player* player,Level* level)
{
    vec player1=player->getPosition();
    SDL_Rect pCol{player1.x,player1.y,80,110};
    pCollider->setRect(pCol);
    int FirstRow = ((player->getPosition().y)/64 - 1) > 0 ? (player->getPosition().y)/64 - 1 : 0;
    int LastRow = FirstRow + 4 >= level->mRow - 1 ? level->mRow - 1 : FirstRow+4;
    int FirstColumn = (player->getPosition().x)/64 - 2 > 0 ? (player->getPosition().x)/64 - 2 : 0;
    int LastColumn = FirstColumn + 5 >= level->mCol - 1 ? level->mCol - 1 : FirstColumn + 5;
    for (int row = LastRow;row>=FirstRow;row--)
    {
        for ( int column = FirstColumn; column < LastColumn; column++)
        {
            SDL_Rect pTil{column  * 64,row * 64 -25,64,64};  // y is subtracted by the half of tilewidth to make player stay on the top of tile
            tCollider->setRect(pTil);
            // std::cout<<back->getPosYTiles(row,column)<<std::endl;
            if (level->mTileMatrix[row][column]>=0)
            {
                if(pCollider->checkCollision(*tCollider,0.0f))
                {

                    // int initTileMember = (FirstColumn-10) > 0 ? FirstColumn-10 : 0;
                    for (int i=0;i<level->mCol;i++){tilesOfCollidedRow[i]=level->mTileMatrix[row][i];}
                    vec offset=pCollider->getOffset();
                    if (pCollider->GetPositionX()>tCollider->GetPositionX()){offset.x*=-1;}
                    // if (pCollider->GetPositionX()>tCollider->GetPositionX()+50){offset.x/=2;}
                    if (pCollider->GetPositionX()<tCollider->GetPositionX() && pCollider->GetPositionX()+80>tCollider->GetPositionX()+TileWidth){offset.x=0;}
                    if (pCollider->GetPositionX()>tCollider->GetPositionX() && pCollider->GetPositionX()<tCollider->GetPositionX()+TileWidth){offset.x=0;}
                    if (pCollider->GetPositionY()>tCollider->GetPositionY())
                    {
                        offset.y*=-1;
                        for (int i{0};i<level->mCol;i++){tilesOfCollidedRow[i]= -1;} //while jumping make the tiles as open space
                    }
                    player->CollisionUpdate(offset,tilesOfCollidedRow, level->mCol);
                    breakflag= true;
                    break;
                }
            }     
        }
        if (breakflag)
        {
            breakflag = false;
            break;
        }
    }
}
