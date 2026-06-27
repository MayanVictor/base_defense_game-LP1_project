#pragma once
#include <raylib.h>
#include "Constants.hpp"

class Player {
    public:
        Player();
        void receiveDamage(int damage);
        Vector2 getPosition();
        
        void draw();
        void printPlayerInfo();
        void update();
        
        void getDestiny(Vector2 destiny);
        
        bool isAlive();
    private: 
        Vector2 position = { (float)screenwidth / 2, (float)screenheight / 2} ; // Define a posição inicial da bola no centro da tela
        Vector2 targetposition;
        
        int life = 100;
        int score = 0;
        float speed = 2.0f;
        int ammo;

        bool alive;
};
