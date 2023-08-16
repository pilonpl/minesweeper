
typedef struct Array2D {
    int width;
    int height;
    int size;
    int data[];
} Array2D;
int* Array2D_cell(int x, int y, Array2D* array);
typedef struct MS {
    int mines;
    int width;
    int height;
    Array2D* visual;
    Array2D* board;
} MS;
MS* MS_new(int width, int height, int mines, int px, int py);
void MS_discover(int x, int y, MS* ms);
void MS_print(MS* ms);