#include "Tilemap.h"

void Background::load()
{
    dirt->loadFromFile("assets/dirt.png");
    water->loadFromFile("assets/water.png");
}
void Background::loadMap(int arr[TotalTilesColumn][TotalTilesRow])
{
    for (int i=0;i<TotalTilesColumn;i++)
    {
        for(int j=0;j<TotalTilesRow;j++)
        {
            map[i][j]=arr[i][j];
        }
    }
}

void Background::render()
{
    SDL_Rect* clip;
    SDL_Rect sth={1,1,16,16}; // removing the border of tile
    // clip->w=16;
    // clip->h=16;
    // clip->x=clip->y=1;
    clip=&sth;
    for (int i=0;i<TotalTilesColumn;i++)
    {
        setDrectY(i*TileHeight+WindowHeight/2,i);
        for(int j=0;j<TotalTilesRow;j++)
        {
            posXTiles[i][j]=j*TileWidth;
            posYTiles[i][j]=i*TileHeight+WindowHeight/2-100;
            int type=map[i][j];
            switch (type)
            {
                case 0:
                    water->render(posXTiles[i][j],posYTiles[i][j],clip,3);
                    break;
                case 1:
                    dirt->render(posXTiles[i][j],posYTiles[i][j],clip,3);
                    break;
                default:
                    break;
            }
        }
    }
}