#include <stdio.h>
#include <stdlib.h>

#include "minesweeper.h"
#include "raylib.h"
#include "raymath.h"

const Color BG = { 34, 34, 34, 255 };
const Color FG = { 17, 17, 17, 255 };

MS* ms;
int MS_spacing = 5;
int MS_size;
int MS_x;
int MS_y;

Texture2D tiles[11];

void drawMinesweeper() {
    for (int tiley = ms->height;tiley >= 1;tiley--) {
        for (int tilex = 1;tilex < ms->width + 1;tilex++) {
            int cx = MS_x + (tilex - 1) * (MS_size + MS_spacing);
            int cy = MS_y + (tiley - 1) * (MS_size + MS_spacing);
            int tile = 0;
            if (ms->board != NULL) {
                tile = *Array2D_cell(tilex, tiley, ms->board);
            }
            int visual = *Array2D_cell(tilex, tiley, ms->visual);
            if (visual == 0) {
                DrawRectangle(cx, cy, MS_size, MS_size, FG);
                continue;
            } else {
                DrawRectangle(cx, cy, MS_size, MS_size, FG);
            }
            
            Rectangle source = {0.0, 0.0, tiles[tile].width, tiles[tile].height};
            Rectangle dest = {cx, cy, MS_size, MS_size};
            DrawTexturePro(tiles[tile], source, dest, (Vector2){0.0, 0.0}, 0.0, WHITE);
        }
    }
}

Vector2 getCords() {
    Vector2 mousePos = GetMousePosition();
    Vector2 pos = { MS_x, MS_y };
    Vector2 diff = Vector2Subtract(mousePos, pos);
    int tx = (int)diff.x / (MS_size + MS_spacing);
    int ty = (int)diff.y / (MS_size + MS_spacing);
    Vector2 out = { tx, ty };
    return out;
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 800, "Minesweeper");
    SetTargetFPS(60);

    tiles[0] = LoadTexture("resources/tiles_0.png");
    tiles[1] = LoadTexture("resources/tiles_1.png");
    tiles[2] = LoadTexture("resources/tiles_2.png");
    tiles[3] = LoadTexture("resources/tiles_3.png");
    tiles[4] = LoadTexture("resources/tiles_4.png");
    tiles[5] = LoadTexture("resources/tiles_5.png");
    tiles[6] = LoadTexture("resources/tiles_6.png");
    tiles[7] = LoadTexture("resources/tiles_7.png");
    tiles[8] = LoadTexture("resources/tiles_8.png");
    tiles[9] = LoadTexture("resources/tiles_mine.png");
    tiles[10] = LoadTexture("resources/tiles_flag.png");

    ms = MS_new(20, 20, 89);
    
    while (!WindowShouldClose()) {
        MS_spacing = fmin(GetScreenHeight(), GetScreenWidth())/200;
        MS_size = (fmin(GetScreenHeight(), GetScreenWidth()) / fmax(ms->height, ms->width)) - MS_spacing;
        MS_x = (GetScreenWidth() / 2) - (ms->width * MS_size + MS_spacing * (ms->width - 1)) / 2;
        MS_y = MS_spacing / 2;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 cords = getCords();
            if (ms->board == NULL) {
                MS_generate(ms, cords.x, cords.y);
            }
            printf("cords: %f, %f\n", cords.x, cords.y);
            MS_discover(cords.x, cords.y, ms);
            if (*Array2D_cell(cords.x + 1, cords.y + 1, ms->board) == 9) {
                printf("You stepped on a mine\n");
            } else if (MS_is_won(ms)) {
                printf("You win\n");
            }
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {

        }

        BeginDrawing();
        ClearBackground(BG);
        
        drawMinesweeper();
        EndDrawing();
    }

    CloseWindow();
}