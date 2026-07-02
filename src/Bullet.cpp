#include "Bullet.hpp"
#include <raylib.h>
#include <raymath.h>

/* ================= 
    Bullet Methods 
   ================= */

Bullet::Bullet(Vector2 startPosition, Vector2 targetPosition, BulletOwner Owner) {
    position = startPosition;

    direction = Vector2Subtract(targetPosition, startPosition);
    direction = Vector2Normalize(direction);

    bulletOwner = Owner;

    speed = 8.0f;
    damage = 10;

    distanceTravelled = 0.0f;
    maxDistance = 800.0f;

    active = true;
}

BulletOwner Bullet::getOwner()
{
    return bulletOwner;
}
void Bullet::update(){
    if(!active) return;

    position.x += direction.x * speed;
    position.y += direction.y * speed;

    distanceTravelled += speed;

    if(distanceTravelled >= maxDistance) {
        active = false;
    }
}
void Bullet::draw() {
    if(!active) return;

    DrawCircleV(position, 5, RED);
}
bool Bullet::isActive() {
    return active;
}
Vector2 Bullet::getPosition() {
    return position;
}
int Bullet::getDamage() {
        return damage;
   
}
void Bullet::bulletDestroy() {
    active = false;
}