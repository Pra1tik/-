#ifndef _Game_
#define _Game_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "math.h"
#include "defaultVar.h"
#include <vector>
#include "Level.h"
#include "Enemy.h"
#include "Enemy2.h"
#include <vector>


class Game{
    public:
        Game(){}
        ~Game(){}
        bool init(const char* title,int xpos, int ypos, int height, int width, bool isFullscreen);
        void update();
        void render();
        void handleEvents(float deltaTime);
        void clean();
        bool running(){return runGame;}
        void Collider(class Player*, class Level*);

        struct enemyCoordinates
        {
            int levelNum;
            vec pos;
            vec range;
        };

        struct bullet
        {
            vec bulletPos;
            vec bulletVel = {10, 2};
            bool shootFlag = false;
            bool bulletAlive = false;
        };
    private:
        enum Game_States
        {
            START_SCREEN=0,
            SELECT_SCREEN,
            GAME_SCREEN,
            INSTRUCTIONS_SCREEN,
            PAUSE_SCREEN,
            EXIT_SCREEN
        };
        SDL_Window* pWindow;
        SDL_Renderer* pRenderer;

        // pointer variables for different classes
        class Player* player;
        class Background* back;
        class collider* pCollider;
        class collider* tCollider;
        class StartScreen* startScreen;
        class SelectScreen* selectScreen;
        class InstructionScreen* controls;
        class PauseScreen* paused;

        class Level* currentLevel;
        class Level* level1;
        class Level* level2;
        int killCount = 0;
        const int TOTAL_ENEMIES = 1;
        int levelNum = 1;

        float dt = 0;
        bool runGame;
        int tileNum;
        vec offset;
        int tilesOfCollidedRow[62];
        bool tileFlag;
        bool breakflag=false;
        int playerXpos;
        Game_States currentGameState;
        vec mousePos;

        //
        enemyCoordinates* enemyLocation;
        bullet* playerBullet;
        bullet* enemyBullet;
        Enemy* enemies;
        std::vector<Enemy*> enemy1;
        std::vector<Enemy*> enemy2;
        std::vector<Enemy2*> enemy1a;
        std::vector<Enemy2*> enemy2a;

        TextureWrapper* bulletTexture;

        bool enemyDead = false;

        //For health bar
        TextureWrapper* healthTexture;
        SDL_Color color = {0,0,0,255};
        TextureWrapper* levelCompleteTexture;
        TextureWrapper* killCountTexture;

};


#endif