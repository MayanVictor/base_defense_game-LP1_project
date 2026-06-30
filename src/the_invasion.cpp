
#include <raylib.h>
#include <raymath.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Constants.hpp"
#include "Base.hpp"
#include "EnemySpawner.hpp"
#include "items.hpp"

void resetGame(
    Player& hero,
    Base& base,
    EnemySpawner& enemySpawn,
    std::vector<Enemy>& enemies,
    std::vector<Bullet>& bullets,
    std::vector<DropItem>& items,
    bool& pause,
    bool& gameOver,
    float& respawnTimer
);

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
    enum class GameState {MENU, PLAYING, TUTORIAL};
    GameState gamestate;
    gamestate = GameState::MENU;


    InitWindow(screenwidth, screenheight, "Base Defense"); // Create a window with 960 widht and 600 height with the title "Base Defense"
    SetTargetFPS(60);
    Texture2D image = LoadTexture("graphics/return_arrow.png");

    while (!WindowShouldClose()) // Checks if the window should be closed by the user (for example if they click the X buttom)
    {
        if(gamestate == GameState::MENU) {
            Vector2 MousePosition = { -100.0f, -100.0f };
            Rectangle TitleRec = {100, 80, 1080, 200};
            Rectangle ButtonStart {screenwidth / 2 - 160, 320, 360, 60};
            Rectangle ButtonTutorial {screenwidth / 2 - 160, 410, 360, 60};
            Rectangle ButtonExit {screenwidth / 2 - 160, 500, 360, 60};
            
            // Event Handling
            MousePosition = GetMousePosition();
            
            // updating
            if(CheckCollisionPointRec(MousePosition, ButtonStart) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                resetGame(hero, base, enemySpawn, enemies, bullets, items, pause, gameOver, respawnTimer);
                gamestate = GameState::PLAYING;
            }
            if(CheckCollisionPointRec(MousePosition, ButtonTutorial) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                gamestate = GameState::TUTORIAL;
            }
            if(CheckCollisionPointRec(MousePosition, ButtonExit) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
            }
            // Drawing
            BeginDrawing();    
                ClearBackground(RAYWHITE);
                DrawRectangleRec(TitleRec, DARKGRAY);
                DrawRectangleRec(ButtonStart, DARKGRAY);
                DrawRectangleRec(ButtonTutorial, DARKGRAY);
                DrawRectangleRec(ButtonExit, DARKGRAY);
                if(CheckCollisionPointRec(MousePosition, ButtonStart)) {
                    DrawRectangleLinesEx(ButtonStart, 10.0, RED);
                } 
                if(CheckCollisionPointRec(MousePosition, ButtonTutorial)){
                    DrawRectangleLinesEx(ButtonTutorial, 10.0, RED);
                }
                if(CheckCollisionPointRec(MousePosition, ButtonExit)){
                    DrawRectangleLinesEx(ButtonExit, 10.0, RED);
                }
                DrawText("THE INVASION", 170, 120, 75, RED);
                DrawText("Start", (screenwidth / 2) - 75, 330, 30, BLUE);
                DrawText("Tutorial", (screenwidth / 2) - 120, 420, 30, BLUE);
                DrawText("Exit", (screenwidth / 2) - 60, 510, 30, BLUE);
            EndDrawing();
        }

        if(gamestate == GameState::TUTORIAL) {
            Rectangle MenuButton {30, 30, 20, 20};
            Vector2 MousePosition = { -100.0f, -100.0f };
            Color Transp_Red = { 230, 41, 55, 55 };
            // event handling
            MousePosition = GetMousePosition();
            //update
            if(CheckCollisionPointRec(MousePosition, MenuButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                gamestate = GameState::MENU;
            }
            //drawing
            BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawTexture(image, 30, 30, WHITE);
                DrawText("Move: Click in some spot in the map and the character walk", 30, 80, 30, DARKGRAY);
                DrawText("Shoot: Aim with the mouse and press the Key Q to shoot", 30, 155, 30, DARKGRAY);
                DrawText("Pause: Press the Key P to pause", 30, 230, 30, DARKGRAY);
                DrawText("Respawn: If you die, you revive in three seconds", 30, 295, 30, DARKGRAY);
                DrawText("Defend the Base: Stop the enemies from destroying your base.", 30, 370, 30, DARKGRAY);
                if(CheckCollisionPointRec(MousePosition, MenuButton)) {
                    DrawRectangleRec(MenuButton, Transp_Red );
                }

            EndDrawing();
        }

        if(gamestate == GameState::PLAYING) {
        // Event Handling
            if(IsKeyPressed(KEY_P)) {
                pause = !pause;
            }
            if(pause && IsKeyPressed(KEY_O)) {
                resetGame(hero, base, enemySpawn, enemies, bullets, items, pause, gameOver, respawnTimer);
                gamestate = GameState::MENU;
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
            } else if(gameOver && IsKeyPressed(KEY_O)) {
                resetGame(hero, base, enemySpawn, enemies, bullets, items, pause, gameOver, respawnTimer);
                gamestate = GameState::MENU;
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
                    } else if(enemy.isAlive() && CheckCollisionCircles(enemy.getPosition(), 20, hero.getPosition(), 20)) {
                        enemy.enemyDestroy();
                        hero.receiveDamage(20);
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
                    DrawText("Press P to unpause", screenwidth / 2 - 160, screenheight / 2 + 60, 40, DARKGRAY);
                    DrawText("Press O to go to Menu", screenwidth / 2 - 160, screenheight / 2 + 120, 40, DARKGRAY);
                }
                if(!hero.isAlive()) {
                    std::ostringstream oss;

                    oss << std::fixed << std::setprecision(1) << (respawnDelay - respawnTimer);
                    
                    std::string TimerText = "revival: " + oss.str();
                    DrawText(TimerText.c_str(), screenwidth / 2 - 120, screenheight / 2 - 20, 40, DARKGRAY);
                }
                if(gameOver)
                {
                    DrawText("GAME OVER", screenwidth / 2 - 130, screenheight / 2 - 40, 50, RED);
                    DrawText("Press R to restart", screenwidth / 2 - 120, screenheight / 2 + 20, 25, DARKGRAY);
                    DrawText("Press O to go to menu", screenwidth / 2 - 120, screenheight / 2 + 50, 25, DARKGRAY);
                }

            EndDrawing(); // Finish the process of drawing
        }
    }
    UnloadTexture(image);
    CloseWindow(); // Close the window and free the allocated resouces
    return 0;
}

void resetGame(
    Player& hero,
    Base& base,
    EnemySpawner& enemySpawn,
    std::vector<Enemy>& enemies,
    std::vector<Bullet>& bullets,
    std::vector<DropItem>& items,
    bool& pause,
    bool& gameOver,
    float& respawnTimer
)
{
    hero = Player();
    base = Base(200);
    enemySpawn = EnemySpawner();

    enemies.clear();
    bullets.clear();
    items.clear();

    pause = false;
    gameOver = false;
    respawnTimer = 0.0f;
}