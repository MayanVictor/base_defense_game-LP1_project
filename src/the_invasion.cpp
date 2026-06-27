
#include <raylib.h>
#include <raymath.h>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Constants.hpp"
#include "Base.hpp"
#include <vector>


int main()
{
    Player hero;
    std::vector<Bullet> bullets;
    Enemy minion({0, 0});
    Base base(200);

    InitWindow(screenwidth, screenheight, "Base Defense"); // Create a window with 960 widht and 600 height with the title "Base Defense"
    SetTargetFPS(60);
    

    while (!WindowShouldClose()) // Checks if the window should be closed by the user (for example if they click the X buttom)
    {
        //event handling
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            hero.getDestiny(GetMousePosition());  
        }
        if(IsKeyPressed(KEY_Q)) {
                bullets.push_back(Bullet( hero.getPosition(), GetMousePosition(), BulletOwner::PLAYER));
        }
        
        // updating position 
        hero.update();    
        minion.update(hero.getPosition());
        base.regenLife();
        for(Bullet& bullet : bullets){
            bullet.update();
        }
        
        minion.enemyShootTimer += GetFrameTime();
        
        if(minion.isAlive() && minion.enemyShootTimer >= minion.enemyShootCooldown) {
        
            if(minion.enemyShootTimer >= minion.enemyShootCooldown)
            {
                bullets.push_back(
                    Bullet( minion.getPosition(), hero.getPosition(), BulletOwner::ENEMY)
                );

                minion.enemyShootTimer = 0.0f;
            }
        }

        for(Bullet& bullet : bullets)
        {
            if(!bullet.isActive()) {
                continue;
            }
            
            if(bullet.getOwner() == BulletOwner::PLAYER) {
                if(CheckCollisionCircles(bullet.getPosition(), 5, minion.getPosition(), 20))
                {
                    minion.receiveDamage(bullet.getDamage());
                    bullet.bulletDestroy();
                }
            }
                if(bullet.getOwner() ==BulletOwner::ENEMY) {
                    if(CheckCollisionCircles(bullet.getPosition(), 5, hero.getPosition(), 20)) {
                        hero.receiveDamage(bullet.getDamage());
                        bullet.bulletDestroy();
                    } else if(CheckCollisionCircleRec(bullet.getPosition(), 5, base.getRectangle())) {
                        base.receiveDamage(bullet.getDamage());
                        bullet.bulletDestroy();
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
            minion.draw();
            hero.draw();
            hero.printPlayerInfo();
            base.printBaseInfo();
        EndDrawing(); // Finish the process of drawing
    }

    CloseWindow(); // Close the window and free the allocated resouces
    return 0;
}