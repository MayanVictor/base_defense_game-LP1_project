#include "game.hpp"
#include <string>

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