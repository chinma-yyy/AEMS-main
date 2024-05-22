#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 256
#define HEIGHT 256
#define PI 3.14159265358979323846

void applyDCT(unsigned char *input, float *output, int width, int height) {
    int u, v, x, y;
    float Cu, Cv, sum;
    
    for (u = 0; u < height; u++) {
        for (v = 0; v < width; v++) {
            sum = 0.0;
            
            for (x = 0; x < height; x++) {
                for (y = 0; y < width; y++) {
                    sum += input[x * width + y] * 
                           cos((2 * x + 1) * u * PI / (2 * height)) * 
                           cos((2 * y + 1) * v * PI / (2 * width));
                }
            }
            
            Cu = (u == 0) ? sqrt(1.0 / height) : sqrt(2.0 / height);
            Cv = (v == 0) ? sqrt(1.0 / width) : sqrt(2.0 / width);
            output[u * width + v] = Cu * Cv * sum;
        }
    }
}

int main() {
    FILE *inputFile, *outputFile;
    unsigned char *inputImage;
    float *outputImage;

    inputFile = fopen("image2.raw", "rb");
    if (inputFile == NULL) {
        fprintf(stderr, "Cannot open input file\n");
        return 1;
    }

    outputFile = fopen("output_dct.raw", "wb");
    if (outputFile == NULL) {
        fprintf(stderr, "Cannot open output file\n");
        fclose(inputFile);
        return 1;
    }

    inputImage = (unsigned char *)malloc(WIDTH * HEIGHT);
    outputImage = (float *)malloc(WIDTH * HEIGHT * sizeof(float));

    fread(inputImage, sizeof(unsigned char), WIDTH * HEIGHT, inputFile);
    fclose(inputFile);

    applyDCT(inputImage, outputImage, WIDTH, HEIGHT);

    fwrite(outputImage, sizeof(float), WIDTH * HEIGHT, outputFile);
    fclose(outputFile);

    free(inputImage);
    free(outputImage);

    printf("DCT applied and output saved to output_dct.raw\n");

    return 0;
}
