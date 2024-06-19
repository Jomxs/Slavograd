#include <graphics.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <locale.h>

using namespace std;

const char *Names_Sex[2][10];

void initializeNamesSex() {
    Names_Sex[0][0] = "Alice";
    Names_Sex[0][1] = "Emma";
    Names_Sex[0][2] = "Olivia";
    Names_Sex[0][3] = "Sophia";
    Names_Sex[0][4] = "Isabella";
    Names_Sex[0][5] = "Mia";
    Names_Sex[0][6] = "Ava";
    Names_Sex[0][7] = "Charlotte";
    Names_Sex[0][8] = "Amelia";
    Names_Sex[0][9] = "Evelyn";

    Names_Sex[1][0] = "Liam";
    Names_Sex[1][1] = "Noah";
    Names_Sex[1][2] = "Oliver";
    Names_Sex[1][3] = "William";
    Names_Sex[1][4] = "Elijah";
    Names_Sex[1][5] = "James";
    Names_Sex[1][6] = "Benjamin";
    Names_Sex[1][7] = "Lucas";
    Names_Sex[1][8] = "Henry";
    Names_Sex[1][9] = "Alexander";

    Names_Sex[2][0] = "F";
    Names_Sex[2][1] = "M";
}

void displayMenu() {
    cleardevice();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(YELLOW);
    outtextxy(300, 100, "Slavograd");
    setcolor(WHITE);
    outtextxy(100, 150, "Aperte algo para começar...");
}



int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    srand(time(NULL));



    unsigned short int tipo = rand() % 2;
    unsigned short int quantidade = rand() % 3 + 1;
    for (int i = 0; i < quantidade; ++i) {
        unsigned short int mentira = rand() % 8 + 1;

    }

    //falso ====================================================//
    if (tipo == 0) {
    initializeNamesSex();
    }
    //falso ====================================================//
    //verdade ====================================================//
    else if (tipo == 1) {
    initializeNamesSex();
    }
    //verdade ====================================================//
    initwindow(getmaxwidth(), getmaxheight(), "Slavograd");

    displayMenu();

    getch();

    return 0;
}
