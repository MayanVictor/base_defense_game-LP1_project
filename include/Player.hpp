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
        void shooting();
        void addKill();
        bool canShoot();
        void receiveAmmo(int ammount);
        void receiveHealth(int HP);
        
        void getDestiny(Vector2 destiny);
        
        bool isAlive();
    private: 
        Vector2 position = { (float)screenwidth / 2, (float)screenheight / 2} ; // Define a posição inicial da bola no centro da tela
        Vector2 targetposition;
        
        int life;
        int kills;
        float speed;
        int ammo;

        bool alive;
};
