#pragma once
#include <raylib.h>

enum class BulletOwner {PLAYER, ENEMY}; 

class Bullet {
    public: 
        Bullet(Vector2 startPosition, Vector2 targetPosition, BulletOwner Owner);

        void update();
        void draw();
        
        Vector2 getPosition();
        void bulletDestroy();
        int getDamage();
        
        BulletOwner getOwner();
        
        bool isActive();
    private:  
        Vector2 position;
        Vector2 direction; 
        BulletOwner bulletOwner;

        float speed;
        float distanceTravelled;
        float maxDistance;
        int damage;

        bool active;
};