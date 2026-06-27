#include "Enemy.hpp"
#include <raymath.h>

/* ================= 
    Enemy Methods 
   ================= */

Enemy::Enemy(Vector2 startPosition) {
    position = startPosition;

    speed = 0.8f;
    life = 10;
    alive = true;
}
void Enemy::update(Vector2 playerPosition){
    if(!alive) {
        return;
    }
    Vector2 direction = Vector2Subtract(playerPosition, position);

    direction = Vector2Normalize(direction);
    
    position = Vector2Add(position,Vector2Scale(direction, speed));
}
int Enemy::getLife() {
    return life;
}
void Enemy::draw() {
    if(!alive) {
        return;
    }
    DrawCircleV(position, 20, DARKBROWN);
}
void Enemy::receiveDamage(int damage) {
    life -= damage;
    if(life <= 0) {
        alive = false;
    }
}

bool Enemy::isAlive() {
    return alive;
}
Vector2 Enemy::getPosition() {
    return position;
}