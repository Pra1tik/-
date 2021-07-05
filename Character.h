#pragma once
#include"Texture.h"

class Character
{
    public:
        Character() {};

        virtual void update() {};
        virtual void render() {};

        void setPosition(int x, int y) { mPosX = x; mPosY = y; }
        void setVelocity(int x, int y) { mVelX = x; mVelY = y; }
        int getPositionX() {return mPosX; }
        int getPositionY() {return mPosY; }
        int getVelocityX() {return mVelX; }
        int getVelocityY() {return mVelY; }

    private:
        int mPosX, mPosY;
        int mVelX, mVelY;
        TextureWrapper* mTexture;
};