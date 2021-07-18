// #pragma once
#ifndef COLLIDER_H
#define COLLIDER_H
#include "SDL2/SDL.h"
#include "math.h"
#include <iostream>

class collider
{
    public:
        collider(){};
        ~collider(){};

        bool checkCollision(collider& other, float push);
        int GetPositionX() {return body.x;}
        int GetPositionY() {return body.y;}
        vec GetPosition() {return vec{body.x,body.y};}
        vec GetHalfSize() {return vec{body.w/2,body.h/2};}
        void setRect(SDL_Rect& body1) {body=body1;}
        void move(float dx,float dy) {body.x+=dx;body.y+=dy;} //not used
        vec update(){return vec{body.x,body.y};}
        vec getOffset(){return intersect;}

        //testing
        vec off(){return offset;}
    private:
        SDL_Rect body;
        vec intersect;
        vec offset;
};

#endif

// collider::collider(SDL_Rect& body) : body(body) {}

