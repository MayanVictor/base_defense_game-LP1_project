#include "game.hpp"
#include <string>
#include <raymath.h>

// === Player Methods ===

void Player::receiveDamage(int amount) { 

    life -= amount;
}
  
void Player::printPlayerInfo() {
    std::string lifeText = "life: " + std::to_string(life); 
    std::string scoreText = "score: " + std::to_string(score);       
    DrawText(lifeText.c_str(), 10, 10, 20, DARKGRAY); 
    DrawText(scoreText.c_str(), 10, 40, 20, DARKGRAY);
}
float Player::PlayerSpeed() {
            return speed;
}
Vector2 Player::getDestiny() {
    return targetposition = GetMousePosition();
}

// === Bullet Methods ===

Bullet::Bullet(Vector2 startPosition, Vector2 targetPosition) {
    position = startPosition;

    direction = Vector2Subtract(targetPosition, startPosition);
    direction = Vector2Normalize(direction);

    speed = 5.0f;

    distanceTravelled = 0.0f;
    maxDistance = 500.0f;

    active = true;
}
void Bullet::update(){
    if(!active) {
        return;
    }
    position.x += direction.x * speed;
    position.y += direction.y * speed;

    distanceTravelled += speed;

    if(distanceTravelled >= maxDistance) {
        active = false;
    }
}
void Bullet::draw() {
    if(!active) {
        return;
    }
    DrawCircleV(position, 5, RED);
}
bool Bullet::isActive() {
    return active;
}

