
#include <raylib.h>
#include <iostream>


int main()
{
    const int screenwidth = 900;
    const int screenheight = 600;
    const int rectanglewidth = 300;
    const int rectangleheight = 250;
    const int ballradius = 30;

    InitWindow(screenwidth, screenheight, "Base Defense"); // Cria uma janela com largura 800, altura 600 e título "Base Defense"

    Vector2 ballposition = { (float)screenwidth / 2, (float)screenheight / 2} ; // Define a posição inicial da bola no centro da tela

    while (!WindowShouldClose()) // Verifica se a janela deve ser fechada (por exemplo, se o usuário clicar no botão de fechar)
    {
        if(IsKeyDown(KEY_RIGHT)) ballposition.x += 0.2f; // Move a bola para a direita se a tecla de seta direita estiver pressionada
        if(IsKeyDown(KEY_LEFT)) ballposition.x -= 0.2f; // Move a bola para a esquerda se a tecla de seta esquerda estiver pressionada
        if(IsKeyDown(KEY_UP)) ballposition.y -= 0.2f;
        if(IsKeyDown(KEY_DOWN)) ballposition.y += 0.2f;

        BeginDrawing(); // Inicia o processo de desenho
            ClearBackground(RAYWHITE); // Limpa a tela com a cor branca
            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY); // Desenha um texto na posição (10, 10) com tamanho de fonte 20 e cor cinza escuro
            DrawRectangle(screenwidth / 2 - rectanglewidth /2, screenheight / 2 - rectangleheight / 2, rectanglewidth, rectangleheight, MAROON);
            DrawRectangle(screenwidth / 2 - (rectanglewidth - 20) /2, screenheight / 2 - (rectangleheight - 20) / 2, rectanglewidth - 20, rectangleheight - 20, WHITE);
            DrawCircleV(ballposition, ballradius, BLUE); // Desenha um círculo preenchido na posição da bola com raio 30 e cor marrom
        EndDrawing(); // Finaliza o processo de desenho e apresenta o conteúdo na janela
    }

    CloseWindow(); // Fecha a janela e libera os recursos alocados
    return 0;
}