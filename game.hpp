#pragma once
#include <raylib.h>

const int screenwidth = 960;
const int screenheight = 600;


class Player {
    public:
        void receiveDamage(int amount);
        Vector2 position = { (float)screenwidth / 2, (float)screenheight / 2} ; // Define a posição inicial da bola no centro da tela
        Vector2 targetposition = position; // Obtém a posição do mouse
        void printPlayerInfo();
        float PlayerSpeed();
        int Getlife();
        Vector2 getDestiny();
    private: 
        int life;
        int score = 0;
        float speed;
};
class Gun {
    public:
        int damage;
        int ammo;
};
class Bullet : public Gun {
    public:
        Bullet(Vector2 startPosition, Vector2 targetPosition);

        void update();
        void draw();

        bool isActive();
    private:  
        Vector2 position;
        Vector2 direction;  
        float speed;
        float distanceTravelled;
        float maxDistance;

        bool active;
};

