#include "EnemySpawner.hpp"
#include "Enemy.hpp"
#include "Constants.hpp"
#include <vector>

EnemySpawner::EnemySpawner() {
    spawnTimer = 0.0f;
    spawnCooldown = 4.5f;
    
    difficultyTimer = 0.0f;
    difficultyInterval = 4.0f;
    minSpawnCooldown = 1.0f;

}
void EnemySpawner::update(std::vector<Enemy>& enemies) {
    spawnTimer += GetFrameTime();
    difficultyTimer += GetFrameTime();

    if(difficultyTimer >= difficultyInterval) {
        spawnCooldown -= 0.1f;
        if(spawnCooldown < minSpawnCooldown) spawnCooldown = minSpawnCooldown;

        difficultyTimer = 0.0f;
    }

    if(spawnTimer >= spawnCooldown)
    {
        int enemyType = GetRandomValue(1, 100);

        if(enemyType <= 75)
        {
            enemies.push_back(Enemy(getRandomBorderPosition(), EnemyType::SHOOTER));
        }
        else
        {
            enemies.push_back(Enemy(getRandomBorderPosition(), EnemyType::TANK));
        }

        spawnTimer = 0.0f;
    }
    
}
Vector2 EnemySpawner::getRandomBorderPosition() {
    int side = GetRandomValue(0, 3);
        Vector2 pos;

        if(side == 0) pos = {0, (float)GetRandomValue(0, screenheight)};
        if(side == 1) pos = {(float)screenwidth, (float)GetRandomValue(0, screenheight)};
        if(side == 2) pos = {(float)GetRandomValue(0, screenwidth), 0};
        if(side == 3) pos = {(float)GetRandomValue(0, screenwidth), (float)screenheight};
    return pos;
}
