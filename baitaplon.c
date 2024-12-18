#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>

enum stage {MENU = 0, GAME, SETTING, GAMEOVER, INFO} current_stage;

int positionSnake[10000];
int speed = 5000;
int fruit = 12011;
int toaDoDiChuyenX = 1, toaDoDiChuyenY = 0;
int lengthSnake;
int score = 0;

void menu() {
    system("cls");
    printf("\033[32m============MENU==========\n\n");
    printf("\033[32m1. Choi game\n");
    printf("\033[32m2. Huong dan\n");
    printf("\033[32m3. Chon do kho\n");
    printf("\033[32m4. Thoat\n");
    printf("\n\033[32mLua chon: ");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            current_stage = GAME;
            break;
        case 2:
            current_stage = INFO;
            break;
        case 3:
            current_stage = SETTING;
            break;
        case 4:
            exit(0);
        default:
            printf("\033[32mLua chon khong hop le!\n");
            Sleep(1000);
    }
}

int random(int a, int b) {
    return a + rand() % (b - a + 1);
}

void randomFruit() {
    int flag = 0, i;
    for (;;) {
        fruit = 10000 + random(1, 77) * 100;
        fruit += random(1, 21);
        for (int j = 0; j < lengthSnake; j++) {
            if (fruit == positionSnake[i]) {
                flag = 1;
            }
        }
        if (!flag == 1) {
            break;
        }
    }
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void bodySnake() {
    lengthSnake = 1;
    positionSnake[0] = 11010;
}

void printScore() {
    gotoxy(90, 15);
    printf("\033[31mScore: %d", score);
}

void drawBoard() {
    for (int i = 0; i < 79; i++) {
        printf("\033[34m+");
    }
    for (int j = 0; j < 22; j++) {
        printf("\n");
        for (int i = 0; i < 79; i++) {
            if (i == 0 || i == 78) {
                printf("\033[34m+");
            } else {
                printf(" ");
            }
        }
    }
    printf("\n");
    for (int i = 0; i < 79; i++) {
        printf("\033[34m+");
    }
}

int X(int x) {
    return (x - 10000) / 100;
}

int Y(int y) {
    return y % 100;
}

void playGame() {
    system("cls");
    int key = 0;
    bodySnake();
    drawBoard();
    gotoxy(X(positionSnake[0]), Y(positionSnake[0]));
    printf("\033[32m+");
    randomFruit();
    while (current_stage == GAME) {
        if (kbhit()) {
            key = getch();
            switch (key) {
                case 'w':
                    if (toaDoDiChuyenX != 0) {
                        toaDoDiChuyenY = -1;
                        toaDoDiChuyenX = 0;
                    }
                    break;
                case 'a':
                    if (toaDoDiChuyenY != 0) {
                        toaDoDiChuyenY = 0;
                        toaDoDiChuyenX = -1;
                    }
                    break;
                case 's':
                    if (toaDoDiChuyenX != 0) {
                        toaDoDiChuyenY = 1;
                        toaDoDiChuyenX = 0;
                    }
                    break;
                case 'd':
                    if (toaDoDiChuyenY != 0) {
                        toaDoDiChuyenY = 0;
                        toaDoDiChuyenX = 1;
                    }
                    break;
            }
        }
        if (speed % 5000 == 0) {
            gotoxy(X(positionSnake[lengthSnake - 1]), Y(positionSnake[lengthSnake - 1]));
            printf(" ");
            for (int i = lengthSnake - 1; i > 0; i--) {
                positionSnake[i] = positionSnake[i - 1];
            }
            positionSnake[0] += toaDoDiChuyenY;
            positionSnake[0] += toaDoDiChuyenX * 100;
            if (Y(positionSnake[0]) == 0) current_stage = GAMEOVER;
            if (Y(positionSnake[0]) == 24) current_stage = GAMEOVER;
            if (X(positionSnake[0]) == 0) current_stage = GAMEOVER;
            if (X(positionSnake[0]) == 78) current_stage = GAMEOVER;
            if (positionSnake[0] == fruit) {
                gotoxy(X(fruit), Y(fruit));
                printf("\033[32mo");
                lengthSnake++;
                score++;
                randomFruit();
            }
            printScore();
            gotoxy(X(positionSnake[0]), Y(positionSnake[0]));
            printf("\033[32m+");
            gotoxy(X(fruit), Y(fruit));
            printf("\033[33m0");
            for (int i = 1; i < lengthSnake; i++) {
                if (positionSnake[0] == positionSnake[i]) {
                    current_stage = GAMEOVER;
                }
            }
        }
        speed++;
    }
}

void setting() {
    system("cls");
    printf("\n\033[33mChon do kho:\n");
    printf("\033[33m1. De\n");
    printf("\033[33m2. Trung binh\n");
    printf("\033[33m3. Kho\n");
    printf("\nLua chon: ");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            speed = 8000;
            break;
        case 2:
            speed = 5000;
            break;
        case 3:
            speed = 2000;
            break;
        default:
            printf("\033[33mLua chon khong hop le!\n");
    }
    current_stage = MENU;
}

void gameover() {
    system("cls");
    printf("\033[31mGAMEOVER\n");
    printf("\033[31mScore cua ban la: %d\n", score);
    printf("\033[31mNhan phim bat ky de quay lai menu...\n");
    getch();
    current_stage = MENU;
}

void info() {
    system("cls");
    printf("\n\033[33mHuong dan choi:\n");
    printf("\033[33m- Su dung cac nut A,W,D,S de di chuyen.\n");
    printf("\033[33m- An thuc an de tang diem.\n");
    printf("\033[33m- Khong duoc dung vao tuong hay vao chinh minh.\n");
    printf("\n\033[33mNhan phim bat ky de quay lai menu...\n");
    getch();
    current_stage = MENU;
}

int main() {
    current_stage = MENU;

    while (1) {
        switch (current_stage) {
            case MENU:
                menu();
                break;
            case GAME:
                playGame();
                break;
            case SETTING:
                setting();
                break;
            case GAMEOVER:
                gameover();
                break;
            case INFO:
                info();
                break;
        }
    }
    return 0;
}
