#pragma once
#include <raylib.h>

enum class EnemyType {SHOOTER, TANK};

class Enemy {
    public:   
        Enemy(Vector2 startPosition, EnemyType type);

        void update(Vector2 playerPosition);
        void draw(Vector2 playerPosition);
        void receiveDamage(int damage);
        void loadTexture();
        void unloadTexture();
        Vector2 getPosition();
        int getLife();
        int getDamage();
        EnemyType getType();
        void enemyDestroy();
        float enemyShootTimer;
        float enemyShootCooldown ;

        bool isAlive();
    private:
        Vector2 position;
        Vector2 direction;
        int life;
        int damage;
        float speed;
        EnemyType enemyType;
        Texture2D shooterSprite;
        Texture2D tankSprite;
        
        bool alive;
};