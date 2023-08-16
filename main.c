#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "minesweeper.h"
#include "raylib.h"
#include "raymath.h"

const Color BG = { 34, 34, 34, 255 };
const Color FG = { 17, 17, 17, 255 };

void drawMinesweeper(MS* ms, int x, int y, int size, int spacing) {
    for (int tiley = ms->height;tiley >= 1;tiley--) {
        for (int tilex = 1;tilex < ms->width + 1;tilex++) {
            int cx = x + (tilex - 1) * (size + spacing);
            int cy = y + (tiley - 1) * (size + spacing);
            int tile = *Array2D_cell(tilex, tiley, ms->board);
            DrawRectangle(cx, cy, size, size, FG);
            
            if (tile == 9) {
                DrawText("#", cx, cy, 40, WHITE);
            }
            else {
                DrawText(TextFormat("%d", tile), cx, cy, 40, WHITE);
            }

        }
    }
}

Vector2 getCords(int x, int y, int size, int spacing) {
    Vector2 mousePos = GetMousePosition();
    Vector2 pos = { x, y };
    Vector2 diff = Vector2Subtract(mousePos, pos);
    int tx = (int)diff.x / (size + spacing);
    int ty = (int)diff.y / (size + spacing);
    Vector2 out = { tx, ty };
    return out;
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 800, "Minesweeper");
    SetTargetFPS(60);

    MS* ms = MS_new(10, 10, 10, 0, 0);
    int size = 50;
    int spacing = 5;
    MS_print(ms);
    size = (GetScreenHeight() / ms->height) - spacing;
    int x = (GetScreenWidth() / 2) - (ms->width * size + spacing * (ms->width - 1)) / 2;
    int y = spacing / 2;
    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 c = getCords(x, y, size, spacing);
            printf("cords: %f, %f\n", c.x, c.y);
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {

        }

        BeginDrawing();
        ClearBackground(BG);
        
        drawMinesweeper(ms, x, y, size, spacing);
        EndDrawing();
    }

    CloseWindow();
/*
    const int width = 8;
    const int height = 8;
    //Array2D* array = Array2D_new(width, height);
    //Array2D_print(array);
    MS* ms = MS_new(width, height, 10, 0, 5);
    //Array2D_print(ms->board);
    clock_t t1 = clock();
    MS_discover(0, 5, ms);
    clock_t t2 = clock();
    printf("clock: %ld\n", t2-t1);
    printf("seconds: %f\n", (double)t2/CLOCKS_PER_SEC-(double)t1/CLOCKS_PER_SEC);
    MS_print(ms);
    return 0;
*/
}