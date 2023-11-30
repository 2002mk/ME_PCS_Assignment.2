#include <stdio.h>
#include <omp.h>

double computeTrapezoidArea(double a, double b, int n, double h);

double measureTime(void (*func)(double, double, int, double), double a, double b, int n, double h);

int main() {
    double a = 0.0; // Lower limit of integration
    double b = 1.0; // Upper limit of integration
    int n = 1000000; // Number of subdivisions
    double h = (b - a) / n; // Width of each trapezoid

    double result = computeTrapezoidArea(a, b, n, h);

    printf("Trapezoid area: %lf\n", result);

    double elapsed_time = measureTime(computeTrapezoidArea, a, b, n, h);
    printf("Elapsed time: %lf seconds\n", elapsed_time);

    return 0;
}

double computeTrapezoidArea(double a, double b, int n, double h) {
    double area = 0.0;

    #pragma omp parallel for reduction(+:area)
    for (int i = 1; i < n; i++) {
        double x_i = a + i * h;
        double f_x_i = x_i * x_i; // Example function: x_i * x_i
        area += f_x_i;
    }

    area = h * (0.5 * (a * a) + area + 0.5 * (b * b));
    return area;
}

double measureTime(void (*func)(double, double, int, double), double a, double b, int n, double h) {
    double start_time = omp_get_wtime();
    func(a, b, n, h);
    double end_time = omp_get_wtime();

    return end_time - start_time;
}
