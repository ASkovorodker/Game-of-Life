#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define HEIGHT 25
#define WIDHT 80

int input(int field[HEIGHT][WIDHT]);
int check_cell(int field[HEIGHT][WIDHT], int y, int x);
int make_new_field(int new_field[HEIGHT][WIDHT], int field[HEIGHT][WIDHT]);
int output(int new_field[HEIGHT][WIDHT]);
void update_field(int field[HEIGHT][WIDHT], int new_field[HEIGHT][WIDHT]);

int main() {
    int field[HEIGHT][WIDHT] = {0};
    int new_field[HEIGHT][WIDHT] = {0};
    int delay = 100000;
    int cfc = 0;

    input(field);

    if (freopen("/dev/tty", "r", stdin) == NULL) {
        perror("Error reopening stdin");
        exit(EXIT_FAILURE);  // Завершите программу или обработайте ошибку
    }

    printf("Выберите скорость игры от 1 до 5, где 1 - медленно, 5 - быстро:\n");
    if (scanf("%d", &cfc) == 1) {
        if (cfc == 1)
            delay = delay * 5;
        else if (cfc == 2)
            delay = delay * 4;
        else if (cfc == 3)
            delay = delay * 3;
        else if (cfc == 4)
            delay = delay * 2;
        else if (cfc == 5)
            delay = delay * 1;
    } else {
        printf("Неверный ввод. Введите число от 1 до 5");
        return 0;
    }

    while (1) {
        make_new_field(new_field, field);
        output(new_field);
        update_field(field, new_field);
        usleep(delay);
        system("clear");
    }
}

int input(int field[HEIGHT][WIDHT]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDHT; j++) scanf("%d", &field[i][j]);
    }
    return 0;
}

int check_cell(int field[HEIGHT][WIDHT], int y, int x) {
    int count = 0;
    int flag;
    for (int i = y - 1; i <= y + 1; i++)  // Подсчет живых соседей
        for (int j = x - 1; j <= x + 1; j++)
            if (field[(i + HEIGHT) % HEIGHT][(j + WIDHT) % WIDHT] == 1)
                count += 1;  // Тороидальные границы - проверка соседей на
                             // противоположных концах поля

    if (field[y][x] == 1) {  // Корректировка счетчика - клектка не считается
                             // своим собственным соседом
        count -= 1;
        if (count == 2 || count == 3)
            flag = 1;  // Определение новового состояния клетки
        else
            flag = 0;
    } else {
        if (count == 3)
            flag = 1;
        else
            flag = 0;
    }
    return flag;
}

int make_new_field(int new_field[HEIGHT][WIDHT], int field[HEIGHT][WIDHT]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDHT; j++) {
            new_field[i][j] = check_cell(field, i, j);
        }
    }
    return 0;
}

int output(int new_field[HEIGHT][WIDHT]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDHT; j++) {
            if (new_field[i][j] == 0) {
                if (j != WIDHT - 1)
                    printf(". ");
                else
                    printf(".");
            } else {
                if (j != WIDHT - 1)
                    printf("X ");
                else
                    printf("X");
            }
        }
        if (i != WIDHT - 1) printf("\n");
    }

    return 0;
}

void update_field(int field[HEIGHT][WIDHT], int new_field[HEIGHT][WIDHT]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDHT; j++) {
            field[i][j] = new_field[i][j];
        }
    }
}
