#include "Enemy.hpp"
#include <raymath.h>

/* ================= 
    Enemy Methods 
   ================= */

Enemy::Enemy(Vector2 startPosition, EnemyType type) {
    position = startPosition;
    alive = true;
    enemyType = type;
    if(type == EnemyType::SHOOTER) {
        enemyShootCooldown = 2.0f;
        life = 20;
        damage = 20;
        speed = 1.2f;
    } else if(type == EnemyType::TANK) {
        enemyShootCooldown = 9999.0f;
        life = 60;
        damage = 60;
        speed = 0.8f;
    }
    shooterSprite = LoadTexture("graphics/alienShooter.png");
    tankSprite = LoadTexture("graphics/alientank.png");
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
void Enemy::draw(Vector2 playerPosition) {
    if(!alive) {
        return;
    }
    Vector2 direction = Vector2Subtract(playerPosition, position);
    float angle = atan2(direction.y, direction.x) * RAD2DEG;

    Texture2D& sprite =
        (enemyType == EnemyType::SHOOTER) ? shooterSprite : tankSprite;

    Rectangle source = {0, 0, (float)sprite.width, (float)sprite.height};

    Rectangle dest = {position.x, position.y, 64, 64};

    Vector2 origin = {dest.width / 2, dest.height / 2};

    DrawTexturePro(sprite, source, dest, origin, angle + 90,WHITE);
}
void Enemy::receiveDamage(int damage) {
    life -= damage;
    if(life <= 0) {
        alive = false;
    }
}
void Enemy::loadTexture() {
    if(enemyType == EnemyType::SHOOTER) {
        shooterSprite = LoadTexture("graphics/alienShooter.png");
    } else if(enemyType == EnemyType::TANK) {
        tankSprite = LoadTexture("graphics/alientank.png");
    }
}
void Enemy::unloadTexture() {
    if(enemyType == EnemyType::SHOOTER) {
        UnloadTexture(shooterSprite);
    } else if(enemyType == EnemyType::TANK) {
        UnloadTexture(tankSprite);
    }
}

bool Enemy::isAlive() {
    return alive;
}
Vector2 Enemy::getPosition() {
    return position;
}
int Enemy::getDamage() { 
    return damage; 
}
EnemyType Enemy::getType() { 
    return enemyType; 
}
void Enemy::enemyDestroy() {
    alive = false;
}