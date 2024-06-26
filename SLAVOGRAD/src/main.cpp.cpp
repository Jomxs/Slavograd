#include "raylib.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <locale.h>

using namespace std;

const char *Names_Sex[2][10];

void initializeNamesSex() {
    Names_Sex[0][0] = "Hilda";
    Names_Sex[0][1] = "Astrid";
    Names_Sex[0][2] = "Freya";
    Names_Sex[0][3] = "Solveig";
    Names_Sex[0][4] = "Sigrid";
    Names_Sex[0][5] = "Ingrid";
    Names_Sex[0][6] = "Ava";
    Names_Sex[0][7] = "Lagertha";
    Names_Sex[0][8] = "Aslaug";
    Names_Sex[0][9] = "Frida";

    Names_Sex[1][0] = "Ragnar";
    Names_Sex[1][1] = "Bjorn";
    Names_Sex[1][2] = "Ivor";
    Names_Sex[1][3] = "Arne";
    Names_Sex[1][4] = "Elijah";
    Names_Sex[1][5] = "Thor";
    Names_Sex[1][6] = "Frode";
    Names_Sex[1][7] = "Leif";
    Names_Sex[1][8] = "Trygve";
    Names_Sex[1][9] = "Tyr";
}

void displayMenu() {
    ClearBackground(BLACK);
    DrawText("Slavograd", 450, 100, 80, RED);
    DrawText("Aperte a tecla ENTER para comecar...", 460, 250, 20, WHITE);
}

void displayGame() {
    ClearBackground(RAYWHITE);
    DrawText("Bem-vindo a Slavograd!", 420, 100, 40, BLACK);
    DrawText("-------------------------------------------------------------------------", 60, 200, 30, BLACK);

    DrawText("aperte ENTER novamente para seguir...", 18, 600, 20, BLACK);
}

void displayNextPhase() {
    ClearBackground(BLACK);
    DrawText("aqui a gente faz o trem!", 100, 100, 40, WHITE);
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    srand(time(NULL));

    unsigned short int tipo = rand() % 2;
    unsigned short int quantidade = rand() % 3 + 1;
    for (int i = 0; i < quantidade; ++i) {
        unsigned short int mentira = rand() % 8 + 1;
    }

    if (tipo == 0 || tipo == 1) {
        initializeNamesSex();
    }

    InitWindow(1280, 720, "Slavograd");

    SetTargetFPS(60);

    int currentPhase = 0;

    while (!WindowShouldClose()) {
        if (currentPhase == 0 && IsKeyPressed(KEY_ENTER)) {
            currentPhase = 1;  // Vai mudar para a historia
        } else if (currentPhase == 1 && IsKeyPressed(KEY_ENTER)) {
            currentPhase = 2;  // Vai pro jogo em si
        }

        BeginDrawing();
        if (currentPhase == 0) {
            displayMenu();
        } else if (currentPhase == 1) {
            displayGame();
        } else if (currentPhase == 2) {
            displayNextPhase();
        }
        EndDrawing();
    }



    CloseWindow();

    return 0;
}
