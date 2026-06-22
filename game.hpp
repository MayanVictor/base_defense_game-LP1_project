#pragma once
#include <raylib.h>

const int screenwidth = 900;
const int screenheight = 600;


class Player {
    public:
        void receiveDamage(int amount);
        Vector2 ballposition = { (float)screenwidth / 2, (float)screenheight / 2} ; // Define a posição inicial da bola no centro da tela
        Vector2 targetposition = ballposition; // Obtém a posição do mouse
        void printPlayerInfo();
        float PlayerSpeed();
        Vector2 getDestiny();
    private: 
        int life = 100;
        int score = 0;
        float speed = 2.0f;
};
