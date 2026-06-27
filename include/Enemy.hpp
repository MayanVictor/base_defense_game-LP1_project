#pragma once
#include <raylib.h>

class Enemy {
    public:   
        Enemy(Vector2 startPosition);

        void update(Vector2 playerPosition);
        void draw();
        void receiveDamage(int damage);
        Vector2 getPosition();
        int getLife();
        float enemyShootTimer = 0.0f;
        float enemyShootCooldown = 2.0f;

        bool isAlive();
    private:
        Vector2 position;
        Vector2 direction;
        int life;
        float speed;
        
        bool alive;
};