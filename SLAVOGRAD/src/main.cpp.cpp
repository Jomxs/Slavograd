#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#define MAX_INPUT_CHARS 24

void gerarDados() {
    unsigned short int tipo = rand() % 2;
    unsigned short int quantidade = rand() % 3 + 1;

    printf("Tipo: %hu\n", tipo);
    printf("Quantidade: %hu\n", quantidade);

    for (int i = 0; i < quantidade; ++i) {
        unsigned short int mentira = rand() % 8 + 1;
        printf("Mentira %d: %hu\n", i + 1, mentira);
    }
}

const char* Names_Sex[2][10];

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

unsigned short int age[2][70];

void initializeAge() {
    for (int i = 0; i < 70; ++i) {
        age[0][i] = 18 + i;
    }
    age[1][0] = 17;
    age[1][1] = 16;
    age[1][2] = 15;
}

void generateRandomRG(char rg[2]) {
    srand(time(NULL));
    for (int i = 0; i < 8; ++i) {
        if (rand() % 2 == 0) {
            rg[0] = '0' + (rand() % 10);
        } else {
            rg[0] = 'A' + (rand() % 26);
        }
    }
}

int main() {
    InitWindow(1280, 720, "Menu");
    Font BMmini = LoadFont("./BMmini.ttf");
    Texture2D logo = LoadTexture("./logo.png");

    bool startGame = false;
    bool showMessagem = false;
    char message[MAX_INPUT_CHARS + 1] = "";
    Rectangle playButtonBounds = { 540, 520, 200, 50 };
    Rectangle messageButtonBounds = { 540, 590, 200, 50 };
    Color playButtonColor = BLUE;
    Color messageButtonColor = BLUE;
    bool playButtonHover = false;
    bool messageButtonHover = false;

    while (!WindowShouldClose()) {
        if (CheckCollisionPointRec(GetMousePosition(), playButtonBounds)) {
            playButtonColor = LIGHTGRAY;
            playButtonHover = true;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                startGame = true;
                break;
            }
        } else {
            playButtonColor = BLUE;
            playButtonHover = false;
        }

        if (CheckCollisionPointRec(GetMousePosition(), messageButtonBounds)) {
            messageButtonColor = LIGHTGRAY;
            messageButtonHover = true;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                showMessagem = true;
            }
        } else {
            messageButtonColor = BLUE;
            messageButtonHover = false;
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);

        DrawTexture(logo, 315, 100, WHITE);
        DrawRectangleRec(playButtonBounds, playButtonHover ? DARKGRAY : playButtonColor);
        DrawTextEx(BMmini, "JOGAR", { playButtonBounds.x + 51, playButtonBounds.y + 15 }, 30, 1, WHITE);

        DrawRectangleRec(messageButtonBounds, messageButtonHover ? DARKGRAY : messageButtonColor);
        DrawTextEx(BMmini, "CREDITOS", { messageButtonBounds.x + 25, messageButtonBounds.y + 15 }, 30, 1, WHITE);

        if (showMessagem) {
            DrawRectangle(200, 520, 880, 180, GRAY);
            DrawRectangleLines(200, 520, 880, 180, DARKGRAY);
            DrawTextEx(BMmini, "PROJETO REALIZADO PELOS ALUNOS:", { 250, 530 }, 30, 1, WHITE);
            DrawTextEx(BMmini, "KALLED;    DESIGN/CODIGO-FONTE", { 235, 570 }, 30, 1, DARKGRAY);
            DrawTextEx(BMmini, "JOSE;       LOGICA/CODIGO-FONTE"  , { 238, 610 }, 30, 1, BLACK);
            DrawTextEx(BMmini, "DAVI;       LOGICA/CODIGO-FONTE", { 240, 650 }, 30, 1, LIGHTGRAY);
            DrawTextEx(BMmini, "aperte ENTER para voltar ao Menu", { 780, 680 }, 14, 1, WHITE);

            DrawTextEx(BMmini, message, { 250, 300 }, 30, 1, WHITE);

            if (IsKeyPressed(KEY_ENTER)) {
                showMessagem = false;
                for (int i = 0; i < MAX_INPUT_CHARS + 1; i++) message[i] = '\0';
            }
        }

        EndDrawing();
    }

    UnloadFont(BMmini);
    UnloadTexture(logo);
    CloseWindow();

    if (startGame) {
        InitWindow(1280, 720, "Slavograd");

        Texture2D sprite = LoadTexture("./sprite.png");
        float posX = 0.f;

        BMmini = LoadFont("./BMmini.ttf");

        initializeNamesSex();
        initializeAge();
        gerarDados();
        char rg[2];
        generateRandomRG(rg);

        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(DARKBLUE);

            Vector2 position = { 440, 600 };
            DrawTextEx(BMmini, "aperte ENTER para comecar!", position, 30, 1, WHITE);
            DrawText(",", 860, 602, 30, WHITE);
            DrawText("--------------------------", 480, 630, 30, WHITE);
            DrawTexture(sprite, posX, 720 - sprite.height, WHITE);

            EndDrawing();
        }

        UnloadFont(BMmini);
        UnloadTexture(sprite);
        CloseWindow();
    }

    return 0;
}
