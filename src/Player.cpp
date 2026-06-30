#include "Player.hpp"
#include <string>
#include <raymath.h>

/*  ================== 
      Player Methods 
    ==================    */
Player::Player() {
    life = 100;
    kills = 0;

    speed = 3.0f;
    ammo = 100;

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
    std::string killsText = "score: " + std::to_string(kills); 
    std::string ammoText = "ammo: " + std::to_string(ammo);
    DrawText(lifeText.c_str(), 10, 10, 20, DARKGRAY); 
    DrawText(killsText.c_str(), 10, 40, 20, DARKGRAY);
    DrawText(ammoText.c_str(), 10, 100, 20, DARKGRAY);
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
void Player::Respawn() {
    alive = true;
    life = 100;

    position = {(float)screenwidth / 2, (float)screenheight / 2};
    targetposition = position;
}

Vector2 Player::getPosition() {
    return position;
}

void Player::shooting() {
    if(ammo > 0) {
        ammo--;
    } 
}

void Player::addKill() {
        kills++;
}

bool Player::canShoot() {
    return ammo > 0;
}

void Player::receiveAmmo(int ammount) {
    ammo += ammount;
}
void Player::receiveHealth(int HP){
    life += HP;
}

bool Player::isAlive() {
    return alive;
}


