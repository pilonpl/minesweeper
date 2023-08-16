#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Array2D {
    int width;
    int height;
    int size;
    int data[];
} Array2D;

Array2D* Array2D_new(int width, int height) {
    Array2D* array = malloc(sizeof(Array2D) + width * height * sizeof(int));
    array->width = width;
    array->height = height;
    array->size = width * height;
    for (int i=0;i<array->size;i++) {
        array->data[i] = 0;
    }
    return array;
}

int Array2D_size(Array2D* array) {
    return sizeof(Array2D) + array->width*array->height;
}


int* Array2D_cell(int x, int y, Array2D* array) {
    return &array->data[y + x*array->height];
}

void Array2D_print(Array2D* array) {
    for (int y=array->height-1;y>=0;y--) {
        for (int x=0;x<array->width;x++) {
            printf(" %d", *Array2D_cell(x, y, array));
        }
        printf("\n");
    }
}

void neighbours(int x, int y, int* array[], Array2D* array2d) {
    array[0] = Array2D_cell(x-1, y+1, array2d);
    array[1] = Array2D_cell(x, y+1, array2d);
    array[2] = Array2D_cell(x+1, y+1, array2d);
    array[3] = Array2D_cell(x-1, y-1, array2d);
    array[4] = Array2D_cell(x, y-1, array2d);
    array[5] = Array2D_cell(x+1, y-1, array2d);
    
    array[6] = Array2D_cell(x-1, y, array2d);
    array[7] = Array2D_cell(x+1, y, array2d);
}

// MineSweeper
typedef struct MS {
    int mines;
    int width;
    int height;
    Array2D* visual;
    Array2D* board;
} MS;

MS* MS_new(int width, int height, int mines, int px, int py) {
    Array2D* visual = Array2D_new(width + 2, height + 2);
    Array2D* board = Array2D_new(width + 2, height + 2);
    srand(14);
    int count = 0;
    while (count < mines) {
        int x = rand()%width + 1;
        int y = rand()%height + 1;
        if (x == px+1 || y == py+1) {
            continue;
        }
        if (*Array2D_cell(x, y, board)==9) {
            continue;
        }
        *Array2D_cell(x, y, board) = 9;
        count++;
    }
    for (int x=1;x<=width;x++) {
        for (int y=1;y<=height;y++) {
            int* nei[8];
            int count = 0;
            neighbours(x, y, nei, board);
            for (int i=0;i<8;i++) {
                if (*nei[i] == 9) {
                    count++;
                }
            }
            if (*Array2D_cell(x, y, board) != 9) {
                *Array2D_cell(x, y, board) = count;
            }
        }
    }
    MS* ms = (MS*)malloc(sizeof(MS));
    ms->mines = mines;
    ms->width = width;
    ms->height = height;
    ms->visual = visual;
    ms->board = board;
    return ms;
}

int MS_is_edge(int x, int y, MS* ms) {
    if (x == 0 || y == 0) {
        return 1;
    }
    if (x == ms->width-1 || y == ms->height-1) {
        return 1;
    }
    return 0;
}

void MS_discover(int x, int y, MS* ms) {
    int bx = x + 1;
    int by = y + 1;
    if (*Array2D_cell(bx, by, ms->visual) == 1) {
        return;
    }
    
    if (bx <= 0 || by <= 0) {
        return;
    }
    if (bx >= ms->width+1 || by >= ms->height+1) {
        return;
    }
    
    *Array2D_cell(bx, by, ms->visual) = 1;
    if (*Array2D_cell(bx, by, ms->board) == 0) {
        MS_discover(x-1, y+1, ms);
        MS_discover(x, y+1, ms);
        MS_discover(x+1, y+1, ms);
        MS_discover(x-1, y-1, ms);
        MS_discover(x, y-1, ms);
        MS_discover(x+1, y-1, ms);
        
        MS_discover(x-1, y, ms);
        MS_discover(x+1, y, ms);
    }
}

void MS_print(MS* ms) {
    printf("Board:\n");
    Array2D_print(ms->board);
    printf("Visual:\n");
    Array2D* array = ms->visual;
    for (int y=array->height-1;y>=0;y--) {
        for (int x=0;x<array->width;x++) {
            int cell = *Array2D_cell(x, y, array);
            if (cell == 0) {
                printf(" #");
            } else {
                printf(" %d", *Array2D_cell(x, y, ms->board));
            }
        }
        printf("\n");
    }
}