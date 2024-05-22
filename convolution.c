#include <stdio.h>
#include <stdlib.h>

#define WIDTH 256
#define HEIGHT 256

void applyConvolution(unsigned char *input, unsigned char *output, int width, int height, float kernel[3][3]) {
    int i, j, k, l;
    int kernelSize = 3;
    int offset = kernelSize / 2;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            float pixelValue = 0.0;

            for (k = 0; k < kernelSize; k++) {
                for (l = 0; l < kernelSize; l++) {
                    int x = j + l - offset;
                    int y = i + k - offset;
                    if (x >= 0 && x < width && y >= 0 && y < height) {
                        pixelValue += input[y * width + x] * kernel[k][l];
                    }
                }
            }

            // Clip the result to [0, 255]
            if (pixelValue > 255) {
                pixelValue = 255;
            } else if (pixelValue < 0) {
                pixelValue = 0;
            }

            output[i * width + j] = (unsigned char)pixelValue;
        }
    }
}

int main() {
    FILE *inputFile, *outputFile;
    unsigned char *inputImage, *outputImage;
    float kernel[3][3] = {
        {0, -1, 0},
        {-1, 4, -1},
        {0, -1, 0}
    };

    inputFile = fopen("image1.raw", "rb");
    if (inputFile == NULL) {
        fprintf(stderr, "Cannot open input file\n");
        return 1;
    }

    outputFile = fopen("output.raw", "wb");
    if (outputFile == NULL) {
        fprintf(stderr, "Cannot open output file\n");
        fclose(inputFile);
        return 1;
    }

    inputImage = (unsigned char *)malloc(WIDTH * HEIGHT);
    outputImage = (unsigned char *)malloc(WIDTH * HEIGHT);

    fread(inputImage, sizeof(unsigned char), WIDTH * HEIGHT, inputFile);
    fclose(inputFile);

    applyConvolution(inputImage, outputImage, WIDTH, HEIGHT, kernel);

    fwrite(outputImage, sizeof(unsigned char), WIDTH * HEIGHT, outputFile);
    fclose(outputFile);

    free(inputImage);
    free(outputImage);

    printf("Convolution applied and output saved to output.raw\n");

    return 0;
}
