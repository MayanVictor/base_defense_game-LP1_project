
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
    float& respawnTimer,
    bool& victory,
    float& gameTimer
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
    float gameTimer = 0.0f;
    float victoryTime = 120.0f;
    bool victory = false;


    InitWindow(screenwidth, screenheight, "Base Defense"); // Create a window with 960 widht and 600 height with the title "Base Defense"
    InitAudioDevice();
    SetTargetFPS(60);
    Texture2D image = LoadTexture("graphics/return_arrow.png");
    
    Music menuMusic = LoadMusicStream("music/song18.mp3");
    Music gameplayMusic = LoadMusicStream("music/gameplay_song.mp3");

    Sound shootSound = LoadSound("sounds/shoot.wav");
    Sound hitSound = LoadSound("sounds/hit_sound.wav");
    Sound itemSound = LoadSound("sounds/take_item.mp3");

    PlayMusicStream(menuMusic);

    while (!WindowShouldClose()) // Checks if the window should be closed by the user (for example if they click the X buttom)
    {
        if(gamestate == GameState::MENU || gamestate == GameState::TUTORIAL)
        {
            UpdateMusicStream(menuMusic);
        }
        if(gamestate == GameState::PLAYING)
        {
            UpdateMusicStream(gameplayMusic);
        }

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
                resetGame(hero, base, enemySpawn, enemies, bullets, items, pause, gameOver, respawnTimer, victory, gameTimer);
                gamestate = GameState::PLAYING;
                StopMusicStream(menuMusic);
                PlayMusicStream(gameplayMusic);
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
                resetGame(hero, base, enemySpawn, enemies, bullets, items, pause, gameOver, respawnTimer, victory, gameTimer);
                gamestate = GameState::MENU;
            }
            if(!pause && !gameOver && !victory && hero.isAlive()) {    
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    hero.getDestiny(GetMousePosition());  
                }
                if(IsKeyPressed(KEY_Q) && hero.canShoot()) {
                    hero.shooting();

                    bullets.push_back(
                        Bullet(hero.getPosition(), GetMousePosition(),BulletOwner::PLAYER));

                    PlaySound(shootSound);
                }
            }
            if(gameOver && IsKeyPressed(KEY_R))
            {
                resetGame(hero, base, enemySpawn, enemies, bullets, items, pause, gameOver, respawnTimer, victory, gameTimer);
            } else if(gameOver && IsKeyPressed(KEY_O)) {
                resetGame(hero, base, enemySpawn, enemies, bullets, items, pause, gameOver, respawnTimer, victory, gameTimer);
                gamestate = GameState::MENU;
            }
            
            if(victory && IsKeyPressed(KEY_O)) {
                resetGame(hero, base, enemySpawn, enemies, bullets, items, pause, gameOver, respawnTimer, victory, gameTimer);
                gamestate = GameState::MENU;
            } else if (victory && IsKeyPressed(KEY_R)) {
                resetGame(hero, base, enemySpawn, enemies, bullets, items, pause, gameOver, respawnTimer, victory, gameTimer);
            }

            // Updating Position 

            if(!gameOver && !pause && !victory) {
                hero.update();

                enemySpawn.update(enemies);

                for(Enemy& enemy : enemies)
                {
                    enemy.update(hero.getPosition());
                }    

                base.update();
                gameTimer += GetFrameTime();

                if(gameTimer >= victoryTime)
                {
                    victory = true;
                }

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
                            PlaySound(shootSound);
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
                                enemy.receiveDamage(hero.getDamage());
                                bullet.bulletDestroy();
                                PlaySound(hitSound);
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
                    if(bullet.getOwner() == BulletOwner::ENEMY)
                    {
                        if(CheckCollisionCircles(bullet.getPosition(), 5, hero.getPosition(), 20))
                        {
                            hero.receiveDamage(bullet.getDamage());
                            PlaySound(hitSound);
                            bullet.bulletDestroy();
                        }
                        else if(CheckCollisionCircleRec(bullet.getPosition(), 5, base.getRectangle()))
                        {
                            base.receiveDamage(bullet.getDamage());
                            PlaySound(hitSound);
                            bullet.bulletDestroy();
                        }
                    }
                }

                for(Enemy& enemy : enemies) {
                    if(enemy.isAlive() && CheckCollisionCircleRec(enemy.getPosition(), 20, base.getRectangle())) {
                        enemy.enemyDestroy();
                        base.receiveDamage(enemy.getDamage());
                        PlaySound(hitSound);
                    } else if(enemy.isAlive() && CheckCollisionCircles(enemy.getPosition(), 20, hero.getPosition(), 20)) {
                        enemy.enemyDestroy();
                        hero.receiveDamage(enemy.getDamage());
                        PlaySound(hitSound);
                    }
                }
                if(base.isDestroyed())
                {
                    gameOver = true;
                }
                
                for(DropItem& item : items) {
                    if(item.isActive() && CheckCollisionCircleRec(hero.getPosition(), 20, item.getRectangle())) {
                        item.itemDestroy();
                        PlaySound(itemSound);
                            if(item.getType() == ItemType::AMMO) {
                                hero.receiveAmmo(item.getAmmount());
                            } else if(item.getType() == ItemType::HEALTH) {
                                hero.receiveHealth(item.getAmmount());
                            }
                    }
                }
            }

            float timeLeft = victoryTime - gameTimer;

            int totalSeconds = (int)timeLeft;
            int minutes = totalSeconds / 60;
            int seconds = totalSeconds % 60;

            if(timeLeft < 0)
            {
                timeLeft = 0;
            }

            // drawing

            BeginDrawing(); // Start the process of drawing
                
                ClearBackground(RAYWHITE); // Clear the screen with the color white
                base.draw();
                for(Bullet& bullet : bullets){
                    bullet.draw();
                }

                for(Enemy& enemy : enemies){
                    enemy.draw(hero.getPosition());
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
                std::string timerText = std::to_string(minutes) + ":" +
                (seconds < 10 ? "0" : "") +
                std::to_string(seconds);

                DrawText(timerText.c_str(), screenwidth / 2 - 40, 10, 30, DARKGRAY);
                if(gameOver)
                {
                    DrawText("GAME OVER", screenwidth / 2 - 130, screenheight / 2 - 40, 50, RED);
                    DrawText("Press R to restart", screenwidth / 2 - 120, screenheight / 2 + 20, 25, DARKGRAY);
                    DrawText("Press O to go to menu", screenwidth / 2 - 120, screenheight / 2 + 50, 25, DARKGRAY);
                }
                if(victory == true) {
                    Color back_green { 0, 228, 48, 100 };
                    DrawRectangle(0, 0, screenwidth, screenheight, back_green);
                    DrawText("YOU WIN!", screenwidth / 2 - 120, screenheight / 2 - 40, 50, RED);
                    DrawText("Press O to return.", screenwidth / 2 - 150, screenheight / 2 - 120, 30, RED);
                    DrawText("Press R to restart.", screenwidth / 2 - 150, screenheight / 2 - 160, 30, RED);
                }

            EndDrawing(); // Finish the process of drawing
        }
    }
    hero.unloadTexture();
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(gameplayMusic);
    UnloadSound(shootSound);
    UnloadSound(hitSound);
    CloseAudioDevice();
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
    float& respawnTimer,
    bool& victory,
    float& gameTimer
)
{
    base = Base(200);
    enemySpawn = EnemySpawner();

    enemies.clear();
    bullets.clear();
    items.clear();

    pause = false;
    gameOver = false;
    victory = false;
    respawnTimer = 0.0f;
    gameTimer = 0.0f;
    hero = Player();
    hero.loadTexture();
}