#pragma once
#include <raylib.h>
#include "Enemy.hpp"
#include <vector>

class EnemySpawner {
    public:
        EnemySpawner();

        void update(std::vector<Enemy>& enemies);
        
    private:
        float spawnTimer;
        float spawnCooldown;
        float difficultyTimer;
        float difficultyInterval;
        float minSpawnCooldown;
        Vector2 getRandomBorderPosition();
};
