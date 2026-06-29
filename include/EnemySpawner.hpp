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
        Vector2 getRandomBorderPosition();
};
