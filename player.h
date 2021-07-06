#pragma once

#include "Character.h"
#include "game.h"
#include "Texture.h"
#include "SDL2/SDL_ttf.h"

class player : public Character
{
    public:
        player(const char* filename,const char* ID);
        void update();
        void render();
    private:
        SDL_Renderer* renderer;
        // SDL_Rect sRect={0,0,80,110},dRect={0,0,80,110};
        int count =0;
        TextureWrapper* mTexture;
        TTF_Font* ttf;

};

player::player(const char* filename,const char* ID)
{
    // TextureWrapper::Instance()->loadFromFile(filename);
    mTexture= new TextureWrapper(renderer,ttf);
    mTexture->loadFromFile(filename);
}

// void player::load()
// {
//     TextureWrapper::Instance()->loadFromFile("assets/player_tilesheet.png");
// }

void player::update()
{
    count++;
}

void player::render()
{
    // TextureWrapper::Instance()->render(count,100,NULL,1,0,NULL,SDL_FLIP_NONE);
    mTexture->render(count,100,NULL,1,20,NULL,SDL_FLIP_NONE);
}