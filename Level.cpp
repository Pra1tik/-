#include "Level.h"
#include "defaultVar.h"

float random_float(const float min, const float max)
{
    if (max == min) return min;
    else if (min < max) return (max - min) * ((float)rand() / RAND_MAX) + min;

    // return 0 if min > max
    return 0;
}

Level::Level(const char fileName[], SDL_Renderer* renderer, int levelNum)
{
    mRenderer = renderer;
    mLevelNum = levelNum;
    camera.w = WindowWidth;
    camera.h = WindowHeight;
    camera.y = 0;
    camera.x = 0;
    
    //Load level info file
    int info[4]; //Order col, row, level width, level height

    FILE* fp;
    fp = fopen(fileName, "r");
    
    if(fp == NULL)
    {
        std::cout << "Failed to open file" << std::endl;
    }
    else
    {
        int count = 0;

        while(count != 4) ////
        {
            char data[10];

            fscanf(fp, "%s", data);
            info[count] = atoi(data);
            count++;
        }
    }

    //Assign values loaded from info file to member variables
    mCol = info[0];
    mRow = info[1];
    mLWidth = info[2];
    mLHeight = info[3];

    //Load the level
    mTileMatrix = new int*[mRow];

    for(int i = 0; i < mRow; i++)
    {
        mTileMatrix[i] = new int[mCol];
    }

    int rowCount = 0, colCount = 0;
    char data[5];
    while(fscanf(fp, "%s", data) != EOF)
    {
        mTileMatrix[rowCount][colCount] = atoi(data);
    
        colCount++;
        if(colCount >= mCol)
        {
            colCount = 0;
            rowCount++;
        }
    }
    fclose(fp);

    //Create a texture wrapper object
    mTexture = new TextureWrapper(renderer);
    mTexture->loadFromFile("graphics/spriteSheet/tileSheet.png");

    //Create clips from the texture

    const int numCols = 4, numRows = 2;
    tileWidth = 64, tileHeight = 64;
    int index = 0;

    clips = new SDL_Rect[numCols * numRows];

    for(int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            clips[index] = {j * tileWidth, i * tileHeight, tileWidth, tileHeight};
            
            index++;
        }
    }
}


Level::~Level()
{
    for(int i = 0; i < mRow; i++)
    {
        delete[] mTileMatrix[i];
    }

    delete[] mTileMatrix;
    delete mTexture;
    delete[] clips;
}


void Level::update(vec pPos, TextureWrapper* pTexture)
{
    //Update camera
    vec playerTexture = {pTexture->getWidth(), pTexture->getHeight()};
    vec playerPos = pPos;

    camera.x += ((playerPos.x + playerTexture.x / 2) - camera.x) * 0.1 - 80;
    camera.y = (playerPos.y + playerTexture.y / 2) - WindowHeight / 2;
    
    //Shake
    if(shake)
    {
        float maxOffset = 10.f, shake = 2.f;

        float offSetX = maxOffset * shake * random_float(-1.f, 1.f);
        float offSetY = maxOffset * shake * random_float(-1.f, 1.f);

        camera.x += offSetX;
        camera.y += offSetY;
    }

    //Check boundary
    if(camera.x > mLWidth - camera.w)
    {
        camera.x = mLWidth - camera.w;
    }
    if(camera.y > mLHeight - camera.h)
    {
        camera.y = mLHeight - camera.h;
    }
    if(camera.x < 0)
    {
        camera.x = 0;
    }
    if(camera.y < 0)
    {
        camera.y = 0;
    }
}

void Level::render()
{
    int xStart = camera.x / (tileWidth * scale);
    int yStart = camera.y / (tileHeight * scale);

    int xEnd = (camera.x + camera.w) / (tileWidth * scale);
    int yEnd = (camera.y + camera.h) / (tileHeight * scale);


    yStart = (yStart > 0 ? yStart-1 : yStart);
    xStart = (xStart > 0 ? xStart-1 : xStart);
    yEnd++; xEnd++;
    yEnd = (yEnd >= mRow ? mRow-1 : yEnd);
    xEnd = (xEnd >= mCol ? mCol-1 : xEnd);


    //Render the tiles
   
    
    for(int i = yStart; i <= yEnd; i++)
    {
        for(int j = xStart; j <= xEnd; j++)
        {
            int tile = mTileMatrix[i][j];

            if(tile != -1)
                mTexture->render(j*tileWidth*scale - camera.x, i*tileHeight*scale - camera.y, &clips[tile], scale);
        }
    
    }
}