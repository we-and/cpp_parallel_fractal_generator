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

// Generate Mandelbrot fractal in parallel
void generateFractalParallel(int width, int height, int max_iter, std::vector<std::vector<int>>& output) {
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double x = (double)j / width * 4.0 - 2.0; // Scale x to fit the view
            double y = (double)i / height * 4.0 - 2.0; // Scale y to fit the view
            std::complex<double> c(x, y);
            output[i][j] = mandelbrot(max_iter, c);
        }
    }
}
int main() {
    int width = 800;  // width of the image
    int height = 600; // height of the image
    int max_iter = 1000; // maximum iterations
    std::vector<std::vector<int>> output(height, std::vector<int>(width));

    // Generating the fractal
    std::cout << "Generating fractal..." << std::endl;
    generateFractalParallel(width, height, max_iter, output);
    std::cout << "Fractal generation completed." << std::endl;

    // Add here your code to save/display the fractal image if needed

    return 0;
}