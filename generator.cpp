#include "stdio.h"
#include "string.h"

int main (void) {

    FILE *out = fopen ("com.txt", "w");

    int max_x = 100;
    int max_y = 100;

    int x_c = max_x / 2;
    int y_c = max_y / 2;

    char buf[max_y][max_x] = {};

    for (int i = 0; i < max_y; ++i) {

        for (int j = 0; j < max_x; ++j) {

            int y = i - y_c;
            int x = j - x_c;

            if (x * x + y * y <= (max_x / 4) * (max_x / 4))
                buf[i][j] = '1';
            else        
                buf[i][j] = '\0';
        }
    }

        for (int i = 0; i < max_y; ++i) {

        for (int j = 0; j < max_x; ++j)
            fprintf (out, "%c", buf[i][j]);

        fputs ("\n", out);
        }

    fclose (out);
    return 0;
}