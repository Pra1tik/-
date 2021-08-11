#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>



class TextureWrapper
{
    public:
        //Initializes variables
        TextureWrapper(SDL_Renderer* renderer, TTF_Font* font = NULL);

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

        //Renders with source and destination rect
        void render(SDL_Rect src, SDL_Rect dest, double angle=0.0, SDL_RendererFlip flip=SDL_FLIP_NONE);

        //Gets image dimension
        int getWidth();
        int getHeight();

    private:
        SDL_Renderer* mRenderer = NULL;
        TTF_Font* mFont = NULL;
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth, mHeight;
};



