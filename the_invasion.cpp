
#include <raylib.h>
#include <raymath.h>
#include "game.hpp"

int main()
{
    const int screenwidth = 900;
    const int screenheight = 600;
    const int rectanglewidth = 300;
    const int rectangleheight = 250;
    const int ballradius = 30;
    Player hero;

    InitWindow(screenwidth, screenheight, "Base Defense"); // Cria uma janela com largura 800, altura 600 e título "Base Defense"
    SetTargetFPS(60);
    

    while (!WindowShouldClose()) // Verifica se a janela deve ser fechada (por exemplo, se o usuário clicar no botão de fechar)
    {
        //event handling
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            hero.getDestiny();
               
        }
        
        // updating position
        Vector2 direction = Vector2Subtract(hero.targetposition, hero.ballposition);
        float velocity = hero.PlayerSpeed();
            float distance = Vector2Length(direction);

            if (distance > 1.0f)
            {
                direction = Vector2Normalize(direction);

                hero.ballposition.x += direction.x * velocity;
                hero.ballposition.y += direction.y * velocity;
            }
        
        // drawing
        BeginDrawing(); // Inicia o processo de desenho
            ClearBackground(RAYWHITE); // Limpa a tela com a cor branca
            DrawRectangle(screenwidth / 2 - rectanglewidth /2, screenheight / 2 - rectangleheight / 2, rectanglewidth, rectangleheight, MAROON);
            DrawRectangle(screenwidth / 2 - (rectanglewidth - 20) /2, screenheight / 2 - (rectangleheight - 20) / 2, rectanglewidth - 20, rectangleheight - 20, WHITE);
            DrawCircleV(hero.ballposition, ballradius, BLUE); // Desenha um círculo preenchido na posição da bola com raio 30 e cor azul
            hero.printPlayerInfo();
        EndDrawing(); // Finaliza o processo de desenho e apresenta o conteúdo na janela
    }

    CloseWindow(); // Fecha a janela e libera os recursos alocados
    return 0;
}