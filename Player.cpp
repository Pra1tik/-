#include "Player.h"

Player::Player(SDL_Renderer* renderer)
{

    mTexture = new TextureWrapper(renderer);
    
    mTexture->loadFromFile("graphics/spriteSheet/player_tilesheet.png");

    //Set initial position
    setPosition(500, 100);
    setVelocity(5, -1);
    setAccleration(0, 0);

    flip =SDL_FLIP_NONE;
    falling = true;

    for (int i=0; i<100; i++)
    {
        tileRowPlayerClass[i] = -1;
    }

}

void Player::CollisionUpdate(vec offset,int tileRow[],int tiles)
{
    pTiles = tiles;
    for (int i{0};i<tiles;i++)
    {
        tileRowPlayerClass[i]=tileRow[i];
    }
    if  (abs(offset.y) >= (TileHeight - 1))
    {
        offset.y=0;
    }
    if  (abs(offset.x) >= 0.2*TileWidth)
    {
        offset.x=0;
    }
    // std::cout << "same" <<std::endl;
    if (abs(offset.x) == mVel.x)
    {
        mVel.y = 1;
        if (previousOffset.x == offset.x && previousOffset.y == offset.y)
        {
            mPos.y += offset.y;
            isJumping = false;
            falling = false;
        }
    }
    else if(offset.x== 0)
    {
        mVel.x =5;
        isJumping=false;
        falling = false;
        mVel.y = imp;
        mAcc.y = 0;
        mPos.y += offset.y;
    }
    std::cout << offset.x << "  " <<offset.y <<std::endl;
    // if(abs(offset.x)!=mVel.x){mPos.x += offset.x;}
    mPos.x += offset.x;
    previousOffset = {offset.x , offset.y};
}


void Player::update()
{
    if (tileRowPlayerClass[((mPos.x)/TileWidth)]>-1 || tileRowPlayerClass[((mPos.x+60)/TileWidth)]>-1) {falling=false;}
    else if (tileRowPlayerClass[(mPos.x)/TileWidth]==-1)
    {
        if(mVel.y>0){mVel.y=fall;}
        falling=true;
    }

    if(falling)
    {
        for (int i{0};i<pTiles;i++){tileRowPlayerClass[i]=-2;}
        mVel.y = (mVel.y - gravity);
        if (mVel.y>0){mPos.y -= mVel.y * dt; }
        else {mPos.y -= 2*mVel.y * dt; }
    }
    if(mAcc.y == 1) 
    {
        falling=false;
        for (int i{0};i<pTiles;i++){tileRowPlayerClass[i]=-2;}
        mVel.y = (mVel.y - gravity);
        if (mVel.y>0){mPos.y -= mVel.y * dt; }
        else {mPos.y -= 2*mVel.y * dt; }
    }


    mPos.x += mAcc.x * mVel.x;
}



void Player::render(SDL_Rect rect)
{
    //select frame and flipstate
    if (mAcc.x == 1)
    {
        flip = SDL_FLIP_NONE;
    }
    else if (mAcc.x == -1)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    double angle = 0.0;
    SDL_Rect source = {currentFrame.x * playerWidth, currentFrame.y *playerHeight,playerWidth,playerHeight};
    SDL_Rect dest = {mPos.x-rect.x,mPos.y-rect.y,playerWidth,playerHeight};
    //render the texture
    mTexture->render(source,dest,angle,flip);
}


void Player::handleInput(SDL_Event& e, float deltaTime)
{

    dt = deltaTime;

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if(state[SDL_SCANCODE_RIGHT])
    {
        mAcc.x = 1;
        rightFacing = true;
        leftFacing = false;
    }
    else if(state[SDL_SCANCODE_LEFT])
    {
        mAcc.x = -1;
        rightFacing = false;
        leftFacing = true;
    }
    else if(!state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT])
    {
        mAcc.x = 0;
    }


    if(jumpFlag == false && state[SDL_SCANCODE_SPACE])
    {
        mAcc.y = 1;
        jumpFlag = true;
        isJumping = true;
    }
    else if(!state[SDL_SCANCODE_SPACE])
    {
        jumpFlag = false;
    }

    if (isShooting == false && state[SDL_SCANCODE_LSHIFT])
    {
        isShooting = true;
    }
    else if (!state[SDL_SCANCODE_LSHIFT])
    {
        isShooting = false;
    }

    if (e.key.keysym.sym == SDLK_r && e.key.repeat == 0)
    {
        mPos.x = 500;
        mPos.y = 100;
        falling = true;
    }
}


void Player::animate()
{
    if (isJumping && !falling)
    {
        currentFrame.x = 1;
        currentFrame.y = 0;
    }
    else if (abs(mAcc.x) == 1 && (!isJumping || falling))
    {
        currentFrame.x = (int) ((SDL_GetTicks()/200)%2);
        currentFrame.y = 1;
    }
    else if (falling)
    {
        currentFrame.x = 2;
        currentFrame.y = 0;
    }
    else if (isShooting)
    {
        currentFrame.x = 2;
        currentFrame.y = 1;
    }
    else if (mAcc.x == 0 && mAcc.y == 0)
    {
        currentFrame.x = 0;
        currentFrame.y = 0;
    }

}