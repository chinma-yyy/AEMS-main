#include <stdio.h>
#include <stdlib.h>

#define WIDTH 256
#define HEIGHT 256

void applyQuantization(unsigned char *input, unsigned char *output, int width, int height, unsigned char quantizationMatrix[8][8]) {
    int i, j;
    for (i = 0; i < height; i += 8) {
        for (j = 0; j < width; j += 8) {
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    int pixel = input[(i + x) * width + (j + y)];
                    int quantized = (pixel + (quantizationMatrix[x][y] / 2)) / quantizationMatrix[x][y];
                    output[(i + x) * width + (j + y)] = (unsigned char)quantized;
                }
            }
        }
    }
}

int main() {
    FILE *inputFile, *outputFile;
    unsigned char *inputImage, *outputImage;
    unsigned char quantizationMatrix[8][8] = {
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68, 109, 103, 77},
        {24, 35, 55, 64, 81, 104, 113, 92},
        {49, 64, 78, 87, 103, 121, 120, 101},
        {72, 92, 95, 98, 112, 100, 103, 99}
    };

    inputFile = fopen("image1.raw", "rb");
    if (inputFile == NULL) {
        fprintf(stderr, "Cannot open input file\n");
        return 1;
    }

    outputFile = fopen("output_quantized.raw", "wb");
    if (outputFile == NULL) {
        fprintf(stderr, "Cannot open output file\n");
        fclose(inputFile);
        return 1;
    }

    inputImage = (unsigned char *)malloc(WIDTH * HEIGHT);
    outputImage = (unsigned char *)malloc(WIDTH * HEIGHT);

    fread(inputImage, sizeof(unsigned char), WIDTH * HEIGHT, inputFile);
    fclose(inputFile);

    applyQuantization(inputImage, outputImage, WIDTH, HEIGHT, quantizationMatrix);

    fwrite(outputImage, sizeof(unsigned char), WIDTH * HEIGHT, outputFile);
    fclose(outputFile);

    free(inputImage);
    free(outputImage);

    printf("Quantization applied and output saved to output_quantized.raw\n");

    return 0;
}
