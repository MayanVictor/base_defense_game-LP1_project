#include "Base.hpp"
#include <raylib.h>
#include <string>
#include "Constants.hpp"
/* ================= 
      Base Methods 
   ================= */

Base::Base(int baseLife) {
    life = baseLife;
    maxLife = baseLife;

    hitBox = {screenwidth / 2 - 150, screenheight / 2 - 125, 300, 250};

    destroyed = false;
}

void Base::draw() {
    const int rectanglewidth = 300;
    const int rectangleheight = 250;
    DrawRectangleRec(hitBox, MAROON);
    DrawRectangle(hitBox.x +10, hitBox.y + 10, hitBox.width - 20, hitBox.height - 20, WHITE);
  
}

Rectangle Base::getRectangle() {
    return hitBox;
}

void Base::receiveDamage(int damage) {
    life -= damage;
    if(life <= 0) {
        destroyed = true;
    }
    if(life < 0) {
        life = 0;
    }
    timeSinceLastHit = 0.0f;
    regenTimer = 0.0f;
}

void Base::regenLife() {
    timeSinceLastHit += GetFrameTime();

    if(timeSinceLastHit >= 3.0f) {
        regenTimer += GetFrameTime();

        if(regenTimer >= 1.0f) {
            life += maxLife * 0.05f;
            regenTimer = 0.0f;
        }
        if(life > maxLife) {
            life = maxLife;
        }
    }
}

void Base::update() {
    regenLife();
}
void Base::printBaseInfo() {
    std::string LifeText = "Base: " + std::to_string(life);
    DrawText(LifeText.c_str(), 10, 70, 20, DARKGRAY);
}
bool Base::isDestroyed() {
    return destroyed;
}