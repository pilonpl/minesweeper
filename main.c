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
            int tile = 0;
            if (ms->board != NULL) {
                tile = *Array2D_cell(tilex, tiley, ms->board);
            }
            int visual = *Array2D_cell(tilex, tiley, ms->visual);
            if (visual == 0) {
                DrawRectangle(cx, cy, size, size, FG);
                continue;
            } else {
                DrawRectangle(cx, cy, size, size, FG);
            }
            
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

    MS* ms = MS_new(20, 20, 10);
    
    int size = 50;
    int spacing = 5;
    
    while (!WindowShouldClose()) {
        size = (fmin(GetScreenHeight(), GetScreenWidth()) / fmin(ms->height, ms->width)) - spacing;
        int x = (GetScreenWidth() / 2) - (ms->width * size + spacing * (ms->width - 1)) / 2;
        int y = spacing / 2;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 c = getCords(x, y, size, spacing);
            if (ms->board == NULL) {
                MS_generate(ms, c.x, c.y);
            }
            printf("cords: %f, %f\n", c.x, c.y);
            MS_discover(c.x, c.y, ms);
            if (*Array2D_cell(c.x + 1, c.y + 1, ms->board) == 9) {
                printf("You stepped on a mine\n");
            } else if (MS_is_won(ms)) {
                printf("You win\n");
            }
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {

        }

        BeginDrawing();
        ClearBackground(BG);
        
        drawMinesweeper(ms, x, y, size, spacing);
        EndDrawing();
    }

    CloseWindow();
}