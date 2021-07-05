#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

//Remove it later
//SDL objects
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;


class TextureWrapper
{
    public:
        //Initializes variables
        TextureWrapper();

        //Deallocates memory
        ~TextureWrapper();

        //Loads image at specified path
        bool loadFromFile(std::string path);

        //Creates image from font string
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

        //Deallocates textures
        void free();


        //Renders texture at any given point
        void render(int x, int y, SDL_Rect* clip = NULL, int scale = 1, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        //Gets image dimension
        int getWidth();
        int getHeight();

    private:
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth, mHeight;
};



TextureWrapper::TextureWrapper()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

TextureWrapper::~TextureWrapper()
{
    free();
}


bool TextureWrapper::loadFromFile(std::string path)
{
    //Get rid of prexisting textures
    free();

    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        std::cout << "Unable to load image: " << IMG_GetError() << std::endl;
    }
    else
    {
        //Color key image
        //Makes the given pixel of surface transparent
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format,0, 255, 255));
    }

    //Create texture
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if(newTexture == NULL)
    {
        std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
    }
    else
    {
        //Get image dimension
        mWidth = loadedSurface->w;
        mHeight = loadedSurface->h;
    }

    //Get rid of surface
    SDL_FreeSurface(loadedSurface);

    mTexture = newTexture;
    return mTexture != NULL;
}


bool TextureWrapper::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    //Get rid of previous textures
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if(textSurface == NULL)
    {
        std::cout << "Failed to create surface: " << TTF_GetError() << std::endl;
    }
    else
    {
        //Create texture
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if(mTexture == NULL)
        {
            std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    } 

    return mTexture != NULL;
}


void TextureWrapper::free()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}



void TextureWrapper::render(int x, int y, SDL_Rect* clip, int scale, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, mWidth * scale, mHeight * scale};

    //Set clip rendering dimension
    if(clip != NULL)
    {
        renderQuad.w = clip->w * scale;
        renderQuad.h = clip->h * scale;
    }
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}


int TextureWrapper::getWidth()
{
    return mWidth;
}


int TextureWrapper::getHeight()
{
    return mHeight;
}