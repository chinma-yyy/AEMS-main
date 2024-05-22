#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 256
#define HEIGHT 256

void applySobelFilter(unsigned char *input, unsigned char *output, int width, int height) {
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    
    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    int i, j, x, y;
    for (i = 1; i < height - 1; i++) {
        for (j = 1; j < width - 1; j++) {
            int sumX = 0;
            int sumY = 0;

            for (x = -1; x <= 1; x++) {
                for (y = -1; y <= 1; y++) {
                    sumX += input[(i + x) * width + (j + y)] * Gx[x + 1][y + 1];
                    sumY += input[(i + x) * width + (j + y)] * Gy[x + 1][y + 1];
                }
            }

            int magnitude = (int)sqrt((sumX * sumX) + (sumY * sumY));
            if (magnitude > 255) {
                magnitude = 255;
            } else if (magnitude < 0) {
                magnitude = 0;
            }

            output[i * width + j] = (unsigned char)magnitude;
        }
    }
}

int main() {
    FILE *inputFile, *outputFile;
    unsigned char *inputImage, *outputImage;

    inputFile = fopen("image1.raw", "rb");
    if (inputFile == NULL) {
        fprintf(stderr, "Cannot open input file\n");
        return 1;
    }

    outputFile = fopen("output_sobel.raw", "wb");
    if (outputFile == NULL) {
        fprintf(stderr, "Cannot open output file\n");
        fclose(inputFile);
        return 1;
    }

    inputImage = (unsigned char *)malloc(WIDTH * HEIGHT);
    outputImage = (unsigned char *)malloc(WIDTH * HEIGHT);

    fread(inputImage, sizeof(unsigned char), WIDTH * HEIGHT, inputFile);
    fclose(inputFile);

    applySobelFilter(inputImage, outputImage, WIDTH, HEIGHT);

    fwrite(outputImage, sizeof(unsigned char), WIDTH * HEIGHT, outputFile);
    fclose(outputFile);

    free(inputImage);
    free(outputImage);

    printf("Sobel filter applied and output saved to output_sobel.raw\n");

    return 0;
}
