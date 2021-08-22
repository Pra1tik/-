#pragma once
#include "Texture.h"
#include "Player.h"
#include "math.h"
#include "game.h"
#include <cstdio>

class Level
{
    public:
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
        //class Game* mGame = NULL;
    public:
        Level(const char filename[], SDL_Renderer* renderer, int levelNum);
        ~Level();

        void update(vec pPos, TextureWrapper* pTexture);
        void render();
       // void setGame(class Game* game) { mGame = game; }

};