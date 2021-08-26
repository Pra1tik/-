#pragma once
#include "Texture.h"
#include "Player.h"
#include "math.h"
#include "game.h"
#include <cstdio>

float random_float(const float min, const float max);


class Level
{
    private:
        int mLevelNum;
        int mLWidth, mLHeight;
        int mRow, mCol;
        int tileWidth, tileHeight;
        int scale = 1;
        SDL_Rect* clips;
        int** mTileMatrix;
        TextureWrapper* mTexture;
        SDL_Renderer* mRenderer;
        SDL_Rect camera;
        bool shake = false;
        
    public:
        Level(const char filename[], SDL_Renderer* renderer, int levelNum);
        ~Level();

        void update(vec pPos, TextureWrapper* pTexture);
        void render();
        friend class Game; 

};