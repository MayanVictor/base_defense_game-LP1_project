#include "Player.hpp"
#include <string>
#include <raymath.h>

/*  ================== 
      Player Methods 
    ==================    */
Player::Player() {
    life = 100;
    score = 0;

    speed = 2.0f;

    alive = true;

    targetposition = position;
}

void Player::receiveDamage(int amount) { 

    life -= amount;
    if(life <= 0) {
        alive = false;
    }
    if(life < 0) {
        life = 0;
    }
}
  
void Player::printPlayerInfo() {
    
    std::string lifeText = "life: " + std::to_string(life); 
    std::string scoreText = "score: " + std::to_string(score);       
    DrawText(lifeText.c_str(), 10, 10, 20, DARKGRAY); 
    DrawText(scoreText.c_str(), 10, 40, 20, DARKGRAY);
}
void Player::update() {
    Vector2 direction = Vector2Subtract(targetposition, position);
    float distance = Vector2Length(direction);
    if (distance > 1.0f)
    {
        
        direction = Vector2Normalize(direction);

        position.x += direction.x * speed;
        position.y += direction.y * speed;
    }
}

void Player::getDestiny(Vector2 destiny) {
    targetposition = destiny;
}
void Player::draw() {
    if(!alive) {
        return;
    }
    DrawCircleV(position, 20, BLUE);
}
bool Player::isAlive() {
    return alive;
}
Vector2 Player::getPosition() {
    return position;
}

