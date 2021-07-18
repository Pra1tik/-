#pragma once
#include "Texture.h"
#include "math.h"
#include "collider.h"

class Character
{
    public:
        Character() {};

        virtual void update(int playereXpos,int tileRow[]) {};
        virtual void render() {};

        void setPosition(int x, int y) { mPos.x = x; mPos.y = y; }
        void setVelocity(int x, int y) { mVel.x = x; mVel.y = y; }
        void setAccleration(int x, int y) {mAcc.x = x; mAcc.y = y; }
        vec getPosition() { return mPos; }
        vec getVelocity() { return mVel; }
        vec getAccleration() { return mAcc; }
        void setTexture(TextureWrapper* texture) { mTexture = texture; }
        TextureWrapper* getTexture() { return mTexture; }
        // collider GetCollider() {return collider(mPos);}

    protected:
        vec mPos;
        vec mVel;
        vec mAcc;
        TextureWrapper* mTexture = NULL;
        Uint32 flipState;
};