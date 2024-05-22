#include<stdio.h>
#include<math.h>

#define SIZE 8

void fdct_8x8(int data[SIZE][SIZE], int output[SIZE][SIZE]) {
    int u, v, x, y;
    float cu, cv, sum;

    for (u = 0; u < SIZE; u++) {
        for (v = 0; v < SIZE; v++) {
            sum = 0.0;
            cu = (u == 0) ? 1.0 / sqrt(2.0) : 1.0;
            cv = (v == 0) ? 1.0 / sqrt(2.0) : 1.0;

            for (x = 0; x < SIZE; x++) {
                for (y = 0; y < SIZE; y++) {
                    sum += data[x][y] * cos((2 * x + 1) * u * 3.141 / (2.0 * SIZE)) *
                                       cos((2 * y + 1) * v * 3.141 / (2.0 * SIZE));
                }
            }

            output[u][v] = (1.0/sqrt(2.0 * SIZE)) * cu * cv * sum;
        }
    }
}

int main() {
    int input[SIZE][SIZE] = {
        {12, 16, 19, 12, 11, 27, 51, 47},
        {16, 24, 12, 19, 12, 20, 39, 51},
        {24, 27, 8, 39, 35, 34, 24, 44},
        {40, 17, 28, 32, 24, 27, 8, 32},
        {34, 20, 28, 20, 12, 8, 19, 34},
        {19, 39, 12, 27, 27, 12, 8, 34},
        {8, 28, -5, 39, 34, 16, 12, 19},
        {20, 27, 8, 27, 24, 19, 19, 8}
    };
    int output[SIZE][SIZE];

    fdct_8x8(input, output);

    printf("DCT Coefficients:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d\t", output[i][j]);
        }
        printf("\n");
    }

    return 0;
}
