#include "Player.h"

Player::Player(SDL_Renderer* renderer)
{

    mTexture = new TextureWrapper(renderer);
    
    mTexture->loadFromFile("assets/player.png");

    //Set initial position
    setPosition(100, 00);
    setVelocity(10, imp);
    setAccleration(0, 0);


}

void Player::CollisionUpdate(vec offset,int nextTile, vec tile)
{

    if(offset.x==0)
    {
        
        mVel.y = imp;
        mAcc.y = 0;
        mPos.y += (offset.y);
    }

    // if(offset.y ==0)
    // {
    //     mVel.y = imp;
    //     mAcc.y = 0;
    //     mPos.y = 600;
    // }

    mPos.x += offset.x;
}


void Player::update(int playerXpos,int tileRow[TotalTilesRow])
{
    // for (int i{0};i<TotalTilesRow;i++){std::cout<< tileRowPlayerClass[i]<<"  ";} std::cout<<"\n";
    if (tileRow!=NULL) {for (int i{0};i<TotalTilesRow;i++){tileRowPlayerClass[i]=tileRow[i];}}
    if (tileRowPlayerClass[((playerXpos)/TileWidth)%16]==1 || tileRowPlayerClass[((playerXpos+40)/TileWidth)%16]==1) {falling=false;}
    else if (tileRowPlayerClass[((playerXpos)/TileWidth)%16]==2)
    {
        if(mVel.y>0){mVel.y=fall;}
        falling=true;
    }

    if(falling)
    {
        mVel.y = (mVel.y - gravity);
        mPos.y -= mVel.y * dt;
        // if (mVel.y<0) {falling=false; mVel.y=imp;}
    }
    if(mAcc.y == 1) 
    {
        falling=false;
        for (int i{0};i<TotalTilesRow;i++){tileRowPlayerClass[i]=0;}
        mVel.y = (mVel.y - gravity);
        mPos.y -= mVel.y * dt; 
    }

    // if(mPos.y > 600)  //uncomment if want to put a base level
    // {
    //     mVel.y = imp;
    //     mAcc.y = 0;
    //     mPos.y = 600;
    //     falling=false;
    // }

    mPos.x += mAcc.x * mVel.x;
}


void Player::render()
{
    //render the texture
    mTexture->render(mPos.x, mPos.y);
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
    }
    else if(!state[SDL_SCANCODE_SPACE])
    {
        jumpFlag = false;
    }
}