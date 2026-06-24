
#include <raylib.h>
#include <raymath.h>
#include "game.hpp"

int main()
{
    const int screenwidth = 960;
    const int screenheight = 600;
    const int rectanglewidth = 300;
    const int rectangleheight = 250;
    const int ballradius = 20;
    Player hero;
    Gun pistol;
    Bullet* bullet = nullptr;

    InitWindow(screenwidth, screenheight, "Base Defense"); // Create a window with 960 widht and 600 height with the title "Base Defense"
    SetTargetFPS(60);
    

    while (!WindowShouldClose()) // Checks if the window should be closed by the user (for example if they click the X buttom)
    {
        //event handling
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            hero.getDestiny();
               
        }
        if(IsKeyPressed(KEY_Q)) {
            delete bullet; //create a single bullet and delete if you press Q again (this will be improved soon)

            bullet = new Bullet( 
                hero.position,
                GetMousePosition()
            );
        }
        
        // updating position
        Vector2 direction = Vector2Subtract(hero.targetposition, hero.position);
        float velocity = hero.PlayerSpeed();
            float distance = Vector2Length(direction);

            if (distance > 1.0f)
            {
                direction = Vector2Normalize(direction);

                hero.position.x += direction.x * velocity;
                hero.position.y += direction.y * velocity;
            }
        
        // drawing
        BeginDrawing(); // Start the process of drawing
            ClearBackground(RAYWHITE); // Clear the screen with the color white
            DrawRectangle(screenwidth / 2 - rectanglewidth /2, screenheight / 2 - rectangleheight / 2, 
                rectanglewidth, rectangleheight, MAROON);
            DrawRectangle(screenwidth / 2 - (rectanglewidth - 20) /2,
             screenheight / 2 - (rectangleheight - 20) / 2, rectanglewidth - 20, rectangleheight - 20, WHITE);
            if (bullet != nullptr){
                bullet->update();
                bullet->draw();
            }
            DrawCircleV(hero.position, ballradius, BLUE); // 
            hero.printPlayerInfo();
        EndDrawing(); // Finish the process of drawing
    }

    CloseWindow(); // Close the window and free the allocated resouces
    return 0;
}