#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include <string.h>

#define MAX_INPUT_CHARS 24

int tipo, quantidade;
int mentira0, mentira01, mentira02;
int idade_saida, idade_saida01;
const char *saida_sexo;
char saida_Nome[20];
char saida_pais[30];
//Fiz como eu disse na apresentação e coloquei os nomes aqui, so tinha deixando pois achei que não faria diferença, mas juro que não usei o chat_gpt apenas queria testar mais as funçoes.
const char *Nomes_e_sexo[3][10] = {
    {"Hilda", "Astrid", "Freya", "Solveig", "Sigrid", "Ingrid", "Ava", "Lagertha", "Aslaug", "Frida"},
    {"Ragnar", "Bjorn", "Ivor", "Arne", "Elijah", "Thor", "Frode", "Leif", "Trygve", "Tyr"},
    {"M", "F"}
};
int age[2][70];
char rg1[9], rg2[9];
char documento[20];
int erro_nome, erro_sexo;

typedef struct {
    Rectangle bounds;
    Color color;
    bool hover;
    const char* label;
    int action;
} Button;

void Iniciar_idade() {
    for (int i = 0; i < 70; ++i) {
        age[0][i] = 18 + i;
    }
    age[1][0] = 17;
    age[1][1] = 16;
    age[1][2] = 567;
}

void gerar_Dados() {
    srand(time(NULL));
    tipo = rand() % 2;
    quantidade = rand() % 4 + 1;

    mentira0 = rand() % 4 + 1;
    mentira01 = (quantidade > 2) ? rand() % 4 + 1 : 0;
    mentira02 = (quantidade > 3) ? rand() % 4 + 1 : 0;

    erro_nome = 0;
    erro_sexo = 0;

    if (tipo == 1 && (mentira0 == 1 || mentira01 == 1 || mentira02 == 1)) {
        erro_nome = 1;
    }

    if (strcmp(saida_pais, "Slavograd") == 0) {
        if (mentira0 == 4) mentira0 = rand() % 3 + 1;
        if (mentira01 == 4) mentira01 = rand() % 3 + 1;
        if (mentira02 == 4) mentira02 = rand() % 3 + 1;
    }
}

void gerar_Sexo_E_Nome() {
    int saida_sexo01 = rand() % 2;
    saida_sexo = (saida_sexo01 == 0) ? "F" : "M";

    int saida_sexo02 = rand() % 10;

    if (erro_nome == 1) {
        if (saida_sexo01 == 0) {
            strcpy(saida_Nome, Nomes_e_sexo[1][saida_sexo02]);
        } else {
            strcpy(saida_Nome, Nomes_e_sexo[0][saida_sexo02]);
        }
    } else {

        if (saida_sexo01 == 0) {
            strcpy(saida_Nome, Nomes_e_sexo[0][saida_sexo02]);
        } else {
            strcpy(saida_Nome, Nomes_e_sexo[1][saida_sexo02]);
        }
    }

    if (erro_sexo == 1) {
        saida_sexo = (saida_sexo[0] == 'F') ? "M" : "F";
    }
}

void gerar_Idade() {
    if (tipo == 1 && (mentira0 == 2 || mentira01 == 2 || mentira02 == 2)) {
        idade_saida01 = rand() % 3;
        idade_saida = age[1][idade_saida01];
    } else {
        idade_saida01 = rand() % 70;
        idade_saida = age[0][idade_saida01];
    }
}

void gerar_Pais() {
    srand(time(NULL));
    int pais01 = rand() % 5;
    char paises[10][20] = {
        "Nordlandia", "Fjordberg", "Glacierholm", "Aurorania", "Slavograd"
    };
    strcpy(saida_pais, paises[pais01]);
}

void verificar_Documentos() {
    if (tipo == 0 ) {
        strcpy(documento, "Tem passe");
    } else if (tipo == 1 && (mentira0 == 4 || mentira01 == 4 || mentira02 == 4)) {
        strcpy(documento, "Sem passe");
    }
}

void gerar_RG() {
    for (int i = 0; i < 8; ++i) {
        if (rand() % 2 == 0) {
            rg1[i] = '0' + (rand() % 10);
        } else {
            rg1[i] = 'A' + (rand() % 26);
        }
    }
    rg1[8] = '\0';

    if (tipo == 1 && (mentira0 == 3 || mentira01 == 3 || mentira02 == 3)) {
        for (int i = 0; i < 8; ++i) {
            if (rand() % 2 == 0) {
                rg2[i] = '0' + (rand() % 10);
            } else {
                rg2[i] = 'A' + (rand() % 26);
            }
        }
        rg2[8] = '\0';
    } else {
        strcpy(rg2, rg1);
    }
}
//mudei a logica dos botões para usarem um switch case, se tivesse mais tempo colocaria um menu ao apertar esc usando o switch break também.
void acao_do_botao(int action, char* resultMessage, bool* showResult, bool* gameStart) {
    switch (action) {
        case 1:
            if (tipo == 0) {
                strcpy(resultMessage, "Voce acertou!");
            } else {
                strcpy(resultMessage, "Voce errou!");
            }
            *showResult = true;
            *gameStart = false;
            break;
        case 2:
            if (tipo == 1) {
                strcpy(resultMessage, "Voce acertou!");
            } else {
                strcpy(resultMessage, "Voce errou!");
            }
            *showResult = true;
            *gameStart = false;
            break;
        default:
            break;
    }
}

int main() {
    InitWindow(1280, 720, "Menu");
    Font BMmini = LoadFont("./BMmini.ttf");
    Texture2D logo = LoadTexture("./logo.png");

    bool startGame = false;
    bool showMessage = false;
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
                showMessage = true;
            }
        } else {
            messageButtonColor = BLUE;
            messageButtonHover = false;
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);

        DrawTexture(logo, 315, 100, WHITE);
        DrawRectangleRec(playButtonBounds, playButtonHover ? DARKGRAY : playButtonColor);
        DrawTextEx(BMmini, "JOGAR", (Vector2){ playButtonBounds.x + 51, playButtonBounds.y + 15 }, 30, 1, WHITE);

        DrawRectangleRec(messageButtonBounds, messageButtonHover ? DARKGRAY : messageButtonColor);
        DrawTextEx(BMmini, "CREDITOS", (Vector2){ messageButtonBounds.x + 25, messageButtonBounds.y + 15 }, 30, 1, WHITE);

        if (showMessage) {
            DrawRectangle(200, 520, 880, 180, BLACK);
            DrawRectangleLines(200, 520, 880, 180, BLACK);
            DrawTextEx(BMmini, "PROJETO REALIZADO PELOS ALUNOS:", (Vector2){ 220, 530 }, 30, 1, GRAY);
            DrawTextEx(BMmini, "KALLED;    DESIGN/CODIGO-FONTE", (Vector2){ 220, 570 }, 30, 1, WHITE);
            DrawTextEx(BMmini, "JOSE;       LOGICA/CODIGO-FONTE", (Vector2){ 220, 610 }, 30, 1, WHITE);
            DrawTextEx(BMmini, "DAVI;       LOGICA/CODIGO-FONTE", (Vector2){ 220, 650 }, 30, 1, WHITE);
            DrawTextEx(BMmini, "V para voltar ao Menu", (Vector2){ 800, 670 }, 22, 1, YELLOW);

            if (IsKeyPressed(KEY_V)) {
                showMessage = false;
                memset(message, 0, sizeof(message));
            }
        }

        EndDrawing();
    }

    UnloadFont(BMmini);
    UnloadTexture(logo);
    CloseWindow();

    if (startGame) {

        InitWindow(1280, 720, "Slavograd");
        BMmini = LoadFont("./BMmini.ttf");
        Texture2D sprite = LoadTexture("./sprite.png");
        Texture2D fundo = LoadTexture("./fundo.png");
        Texture2D alea = LoadTexture("./alea.png");
        Texture2D casa = LoadTexture("./casa.png");
        Texture2D familia = LoadTexture("./familia.png");
        Texture2D errado = LoadTexture("./errado.png");
        Texture2D certo = LoadTexture("./certo.png");

        bool mostrarSprite = true;
        bool gameStart = false;
        bool showResult = false;
        char resultMessage[30] = "";

        Button correctButton = { { 540, 520, 200, 50 }, GREEN, false, "", 1 };
        Button incorrectButton = { { 540, 590, 200, 50 }, RED, false, "", 2 };

        while (!WindowShouldClose()) {
            if (IsKeyPressed(KEY_C)) {
                mostrarSprite = false;
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            if(mostrarSprite){
                DrawTexture(sprite, 0, 720 - sprite.height, WHITE);
            } else {
                DrawTexture(fundo, 0, 0, WHITE);
                DrawTexture(alea, 960, 300, WHITE);
                DrawTexture(casa, 800, 10, WHITE);
                DrawTexture(familia, 60, 580, WHITE);
            }

            if (CheckCollisionPointRec(GetMousePosition(), correctButton.bounds)) {
                correctButton.color = LIGHTGRAY;
                correctButton.hover = true;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                   acao_do_botao(correctButton.action, resultMessage, &showResult, &gameStart);
                }
            } else {
                correctButton.color = GREEN;
                correctButton.hover = false;
            }

            if (CheckCollisionPointRec(GetMousePosition(), incorrectButton.bounds)) {
                incorrectButton.color = LIGHTGRAY;
                incorrectButton.hover = true;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    acao_do_botao(incorrectButton.action, resultMessage, &showResult, &gameStart);
                }
            } else {
                incorrectButton.color = RED;
                incorrectButton.hover = false;
            }

            BeginDrawing();
            ClearBackground(DARKBLUE);

            if (!gameStart && !showResult) {
                DrawTextEx(BMmini, "aperte C para iniciar!", (Vector2){ 480, 610 }, 30, 1, WHITE);

                if (IsKeyPressed(KEY_C)) {
                    gameStart = true;
                    Iniciar_idade();
                    gerar_Dados();
                    gerar_Sexo_E_Nome();
                    gerar_Idade();
                    gerar_RG();
                    gerar_Pais();
                    verificar_Documentos();//por algum motivo de vez enquanto,  ao começar o código o passe não e mostrando, então eu pedi pra pedir duas vezes na primeira vez que é pedido.
                    verificar_Documentos();//se voce poder me explicar porque isso aconteçe ficaria muito feliz.Mas ele esta funcionando assim.
                }
            } else if (gameStart) {
                ClearBackground(RAYWHITE);

                DrawTextEx(BMmini, "Sexo: ", (Vector2){ 20, 20 }, 40, 1, GRAY);
                DrawText(saida_sexo, 150, 20, 35, ORANGE);

                DrawTextEx(BMmini, "Nome: ", (Vector2){ 20, 100 }, 40, 1, GRAY);
                DrawText(saida_Nome, 160, 100, 35, ORANGE);

                DrawTextEx(BMmini, "Idade: ", (Vector2){ 20, 140 }, 40, 1, GRAY);
                DrawText(TextFormat("%d", idade_saida), 180, 140, 35, ORANGE);

                DrawTextEx(BMmini, "RG1: ", (Vector2){ 20, 240 }, 40, 1, GRAY);
                DrawText(rg1, 120, 240, 30, ORANGE);

                DrawTextEx(BMmini, "RG2: ", (Vector2){ 20, 280 }, 40, 1, GRAY);
                DrawText(rg2, 120, 280, 30, ORANGE);

                DrawTextEx(BMmini, "Pais: ", (Vector2){ 20, 400 }, 40, 1, GRAY);
                DrawText(saida_pais, 130, 402, 30, ORANGE);

                DrawTextEx(BMmini, "Passe: ", (Vector2){ 20, 450 }, 40, 1, GRAY);
                DrawText(documento, 170, 452, 30, ORANGE);

                DrawRectangleRec(correctButton.bounds, correctButton.hover ? DARKGRAY : correctButton.color);
                DrawTextEx(BMmini, "", (Vector2){ correctButton.bounds.x + 28, correctButton.bounds.y + 15 }, 30, 1, WHITE);
                DrawTexture(certo, 605, 505, WHITE);

                DrawRectangleRec(incorrectButton.bounds, incorrectButton.hover ? DARKGRAY : incorrectButton.color);
                DrawTextEx(BMmini, "", (Vector2){ incorrectButton.bounds.x + 32, incorrectButton.bounds.y + 15 }, 30, 1, WHITE);
                DrawTexture(errado, 605, 580, WHITE);
            } else if (showResult) {
                DrawTextEx(BMmini, resultMessage, (Vector2){ 104, 230 }, 25, 1, WHITE);
                DrawTextEx(BMmini, "R PARA REINICIAR...", (Vector2){ 48, 260 }, 30, 1, MAROON);
                DrawTextEx(BMmini, "-", (Vector2){ 47, 270 }, 40, 1, MAROON);

                if (IsKeyPressed(KEY_R)) {
                    showResult = false;
                    gameStart = true;

                    Iniciar_idade();
                    gerar_Dados();
                    gerar_Sexo_E_Nome();
                    gerar_Idade();
                    gerar_RG();
                    gerar_Pais();
                    verificar_Documentos();
                }
            }
            EndDrawing();
        }
        UnloadFont(BMmini);
        UnloadTexture(sprite);
        UnloadTexture(fundo);
        UnloadTexture(alea);
        UnloadTexture(familia);
        UnloadTexture(casa);
        CloseWindow();
    }
    return 0;
}
