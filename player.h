#pragma once

#include "Character.h"
#include "game.h"
#include "Texture.h"

class player : public Character
{
    public:
        player(const char* filename);
        void update();
        void render();
    private:
        SDL_Renderer* renderer;
        // SDL_Rect sRect={0,0,80,110},dRect={0,0,80,110};
        int count =0;

};

player::player(const char* filename)
{
    TextureWrapper::Instance()->loadFromFile(filename);
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
    TextureWrapper::Instance()->render(count,100,NULL,1,0,NULL,SDL_FLIP_NONE);
}