#pragma once
#include <raylib.h>

class Base {
    public:
        Base(int baseLife);
        void receiveDamage(int damage);
        void regenLife();
        void draw();
        void update();
        Rectangle getRectangle();
        void printBaseInfo();

        bool isDestroyed();
    private:    
        int life;
        int maxLife;

        float timeSinceLastHit;
        float regenTimer;
        float regenDelay;
        float regenPercent;
        Rectangle hitBox;

        bool destroyed;

};