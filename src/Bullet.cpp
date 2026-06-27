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

    speed = 5.0f;

    distanceTravelled = 0.0f;
    maxDistance = 500.0f;

    active = true;
}
int Bullet::getDamage() {
    return damage = 10;
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
void Bullet::bulletDestroy() {
    active = false;
}