#include "Player.h"

Player::Player(SDL_Renderer* renderer)
{

    mTexture = new TextureWrapper(renderer);
    
    mTexture->loadFromFile("graphics/spriteSheet/player_tilesheet.png");

    //Set initial position
    setPosition(100, 300);
    setVelocity(5, -1);
    setAccleration(0, 0);

    flip =SDL_FLIP_NONE;
    falling = true;

}

void Player::CollisionUpdate(vec offset,int tileRow[],int tiles)
{
    for (int i{0};i<tiles;i++)
    {
        tileRowPlayerClass[i]=tileRow[i];
    }
    if  (abs(offset.y) >= TileHeight)
    {
        offset.y=0;
    }
    if  (abs(offset.x) >= TileWidth)
    {
        offset.x=0;
    }
    if (abs(offset.x) == mVel.x)
    {
        mVel.y = -30;
        isJumping = false;
        falling = false;
    }
    else if(offset.x== 0)
    {
        mVel.x =5;
        isJumping=false;
        falling = false;
        mVel.y = imp;
        mAcc.y = 0;
        mPos.y += (offset.y);
    }
    // std::cout << offset.x << "  " <<offset.y <<std::endl;
    // if(abs(offset.x)!=mVel.x){mPos.x += offset.x;}
    mPos.x += offset.x;
}


void Player::update()
{
    if (tileRowPlayerClass[((mPos.x)/TileWidth)]>-1 || tileRowPlayerClass[((mPos.x+40)/TileWidth)]>-1) {falling=false;}
    else if (tileRowPlayerClass[(mPos.x)/TileWidth]==-1)
    {
        if(mVel.y>0){mVel.y=fall;}
        falling=true;
    }

    if(falling)
    {
        for (int i{0};i<62;i++){tileRowPlayerClass[i]=-2;}
        mVel.y = (mVel.y - gravity);
        if (mVel.y>0){mPos.y -= mVel.y * dt; }
        else {mPos.y -= 2*mVel.y * dt; }
    }
    if(mAcc.y == 1) 
    {
        falling=false;
        for (int i{0};i<62;i++){tileRowPlayerClass[i]=-2;}
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
    }
    else if(state[SDL_SCANCODE_LEFT])
    {
        mAcc.x = -1;
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
}


void Player::animate()
{
    if (abs(mAcc.x) == 1 && !isJumping)
    {
        currentFrame.x = (int) ((SDL_GetTicks()/200)%2);
        currentFrame.y = 1;
    }
    else if (isJumping && mVel.y > 0)
    {
        currentFrame.x = 1;
        currentFrame.y = 0;
    }
    else if (falling && mVel.y < 0)
    {
        currentFrame.x = 2;
        currentFrame.y = 0;
    }
    else if (mAcc.x == 0 && mAcc.y == 0)
    {
        currentFrame.x = 0;
        currentFrame.y = 0;
    }

}