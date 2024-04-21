#include <complex>
#include <vector>
#include <iostream>
#include <omp.h>

// Function to compute whether a point belongs to the Mandelbrot set
int mandelbrot(int max_iter, std::complex<double> c) {
    std::complex<double> z = 0;
    int n = 0;
    while (abs(z) <= 2 && n < max_iter) {
        z = z * z + c;
        n++;
    }
    return n;
}

// Generate Mandelbrot fractal
void generateFractal(int width, int height, int max_iter) {
    std::vector<std::vector<int>> output(height, std::vector<int>(width));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double x = (double)j / width * 4.0 - 2.0;
            double y = (double)i / height * 4.0 - 2.0;
            std::complex<double> c(x, y);
            output[i][j] = mandelbrot(max_iter, c);
        }
    }
}


void generateFractalParallel(int width, int height, int max_iter) {
    std::vector<std::vector<int>> output(height, std::vector<int>(width));
    #pragma omp parallel for
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double x = (double)j / width * 4.0 - 2.0;
            double y = (double)i / height * 4.0 - 2.0;
            std::complex<double> c(x, y);
            output[i][j] = mandelbrot(max_iter, c);
        }
    }
}