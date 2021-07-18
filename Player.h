#pragma once
#include "Character.h"
#include <SDL2/SDL.h>
#include "defaultVar.h"

class Player : public Character
{
    public:
        Player(SDL_Renderer* renderer);

        void update(int playerXpos,int tileRow[]=NULL) override;
        void render() override;
        void handleInput(SDL_Event& e, float deltaTime);
        void CollisionUpdate (vec offset,int nextTile={0},vec tile={0,0});

    private:
        int mlives = 3;
        float dt = 0;
        bool mAlive = true;
        bool jumpFlag = false;
        int gravity = 30;
        const int imp = 900;
        const int fall = 0;
        bool falling=false;
        int tileRowPlayerClass[TotalTilesRow];
        int count=0;
};