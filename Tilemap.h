#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Texture.h"
#include "defaultVar.h"




static int level1[TotalTilesColumn][TotalTilesRow]={
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};


class Background
{
    private:
        // SDL_Texture* land;
        TextureWrapper* dirt;
        TextureWrapper* water;
        SDL_Renderer* renderer;
        int map[TotalTilesColumn][TotalTilesRow];
        int dRectY[TotalTilesRow];
        int posXTiles[TotalTilesColumn][TotalTilesRow];
        int posYTiles[TotalTilesColumn][TotalTilesRow];

    public:
        Background(SDL_Renderer* renderer)
        {
            dirt= new TextureWrapper(renderer);
            water= new TextureWrapper(renderer);
            loadMap(level1);
        }
        void loadMap(int arr[TotalTilesColumn][TotalTilesRow]);
        void load();
        void render();
        SDL_Rect getTileRect(int i,int j){return SDL_Rect{(i*50+50),(j*50+50),50,50};}
        int getTileNum(int i,int j){return map[i][j];}
        int getPosXTiles(int i,int j){return posXTiles[i][j];} 
        int getPosYTiles(int i,int j){return posYTiles[i][j];}
        void setDrectY(int x,int index){dRectY[index]=x;}
        int getDrectY(int index) {return dRectY[index];}
};

