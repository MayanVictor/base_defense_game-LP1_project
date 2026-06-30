
#include <raylib.h>
#include <raymath.h>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Constants.hpp"
#include "Base.hpp"
#include "EnemySpawner.hpp"
#include "items.hpp"
#include <vector>
#include <string>

int main()
{
    Player hero;
    EnemySpawner enemySpawn;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    std::vector<DropItem> items;
    Base base(200);
    bool pause = false;
    float respawnTimer = 0.0f;
    float respawnDelay = 3.0f;
    bool gameOver = false;

    InitWindow(screenwidth, screenheight, "Base Defense"); // Create a window with 960 widht and 600 height with the title "Base Defense"
    SetTargetFPS(60);
    

    while (!WindowShouldClose()) // Checks if the window should be closed by the user (for example if they click the X buttom)
    {
        // Event Handling
        if(IsKeyPressed(KEY_P)) {
            pause = !pause;
        }
        if(!pause) {    
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                hero.getDestiny(GetMousePosition());  
            }
            if(IsKeyPressed(KEY_Q) && hero.canShoot()) {
                hero.shooting();

                bullets.push_back(
                    Bullet(hero.getPosition(), GetMousePosition(),BulletOwner::PLAYER));
            }
        }
        if(gameOver && IsKeyPressed(KEY_R))
        {
            hero = Player();
            base = Base(200);
            enemies.clear();
            bullets.clear();
            items.clear();
            gameOver = false;
        }

        // Updating Position 
        
        if(!gameOver && !pause) {
            hero.update();

            enemySpawn.update(enemies);

            for(Enemy& enemy : enemies)
            {
                enemy.update(hero.getPosition());
            }    

            base.update();

            if(!hero.isAlive()) {
                respawnTimer += GetFrameTime();
                if(respawnTimer >= respawnDelay) {
                    hero.Respawn();
                    respawnTimer = 0.0f;
                }
            }

            for(Bullet& bullet : bullets){
                bullet.update();
            }

            for(Enemy& enemy : enemies) {
                enemy.enemyShootTimer += GetFrameTime();
                
                if(enemy.isAlive() && enemy.enemyShootTimer >= enemy.enemyShootCooldown) {
                
                    if(enemy.enemyShootTimer >= enemy.enemyShootCooldown)
                    {
                        bullets.push_back(
                            Bullet( enemy.getPosition(), hero.getPosition(), BulletOwner::ENEMY)
                        );

                        enemy.enemyShootTimer = 0.0f;
                    }
                }
            }

            for(Bullet& bullet : bullets)
            {
                if(!bullet.isActive()) {
                    continue;
                }
                for(Enemy& enemy : enemies) {  
                    if(!enemy.isAlive()) {
                        continue;
                    }
                    
                    if(bullet.getOwner() == BulletOwner::PLAYER) {
                        if(CheckCollisionCircles(bullet.getPosition(), 5, enemy.getPosition(), 20))
                        {
                            enemy.receiveDamage(bullet.getDamage());
                            bullet.bulletDestroy();
                            if(!enemy.isAlive()) {
                                hero.addKill();
                                
                                int chance = GetRandomValue(1, 2);
                                if(chance == 2) {
                                    int dropType = GetRandomValue(1, 3);
                                    if(dropType == 1) {
                                        items.push_back(DropItem(enemy.getPosition(), ItemType::AMMO, GetRandomValue(5, 15)));
                                    }
                                    else if(dropType == 2) {
                                        items.push_back(DropItem(enemy.getPosition(), ItemType::HEALTH, GetRandomValue(5, 20)));
                                    }
                                    else if(dropType == 3) {
                                        items.push_back(DropItem(enemy.getPosition(), ItemType::AMMO, GetRandomValue(5, 15)));

                                        Vector2 healthPos = enemy.getPosition();
                                        healthPos.x += 30;

                                        items.push_back(DropItem(healthPos, ItemType::HEALTH, GetRandomValue(5, 20)));
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
                if(bullet.getOwner() == BulletOwner::ENEMY) {
                    if(CheckCollisionCircles(bullet.getPosition(), 5, hero.getPosition(), 20)) {
                        hero.receiveDamage(bullet.getDamage());
                        bullet.bulletDestroy();
                    } else if(CheckCollisionCircleRec(bullet.getPosition(), 5, base.getRectangle())) {
                        base.receiveDamage(bullet.getDamage());
                        bullet.bulletDestroy();
                    }
                }
            }

            for(Enemy& enemy : enemies) {
                if(enemy.isAlive() && CheckCollisionCircleRec(enemy.getPosition(), 20, base.getRectangle())) {
                    enemy.enemyDestroy();
                    base.receiveDamage(20);
                }
            }
            if(base.isDestroyed())
            {
                gameOver = true;
            }
            
            for(DropItem& item : items) {
                if(item.isActive() && CheckCollisionCircleRec(hero.getPosition(), 20, item.getRectangle())) {
                    item.itemDestroy();
                        if(item.getType() == ItemType::AMMO) {
                            hero.receiveAmmo(item.getAmmount());
                        } else if(item.getType() == ItemType::HEALTH) {
                            hero.receiveHealth(item.getAmmount());
                        }
                }
            }
        }

        // drawing

        BeginDrawing(); // Start the process of drawing
            
            ClearBackground(RAYWHITE); // Clear the screen with the color white
            base.draw();
            for(Bullet& bullet : bullets){
                bullet.draw();
            }

            for(Enemy& enemy : enemies){
                enemy.draw();
            }
            for(DropItem& item : items) {
                item.draw();
            }

            hero.draw();
            hero.printPlayerInfo();
            base.printBaseInfo();
            if(pause) {
                Color Blank_Gray {189, 189, 189, 100};
                DrawRectangle(0, 0, screenwidth, screenheight, Blank_Gray);
                DrawText("PAUSED", screenwidth / 2 - 80, screenheight / 2, 40, DARKGRAY);
            }
            if(!hero.isAlive()) {
                std::string TimerText = "revival: " + std::to_string((respawnDelay - respawnTimer));
                DrawText(TimerText.c_str(), screenwidth / 2 - 80, screenheight / 2, 40, DARKGRAY);
            }
            if(gameOver)
            {
                DrawText("GAME OVER", screenwidth / 2 - 130, screenheight / 2 - 40, 50, RED);
                DrawText("Press R to restart", screenwidth / 2 - 120, screenheight / 2 + 20, 25, DARKGRAY);
            }

        EndDrawing(); // Finish the process of drawing
    }

    CloseWindow(); // Close the window and free the allocated resouces
    return 0;
}