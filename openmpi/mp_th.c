#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 4

double calculateSumTime(int n, int *numbers) {
    long long totalSum = 0;
    double start_time = omp_get_wtime();

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int threadID = omp_get_thread_num();
        int chunkSize = n / NUM_THREADS;
        int remainder = n % NUM_THREADS;

        int start = threadID * chunkSize;
        int end = (threadID == NUM_THREADS - 1) ? (threadID + 1) * chunkSize + remainder : (threadID + 1) * chunkSize;

        long long localSum = 0;

        // Calculate local sum for each thread
        for (int i = start; i < end; i++) {
            localSum += numbers[i];
        }

        // Use critical section to update totalSum
        #pragma omp critical
        {
            totalSum += localSum;
        }
    }

    double end_time = omp_get_wtime();
    printf("Sum of first %d even numbers: %lld\n", n, totalSum);
    printf("Elapsed time: %lf seconds\n", end_time - start_time);

    return end_time - start_time;
}

int main() {
    int n = 1000000; // Replace with the desired number of even elements
    int *numbers = (int *)malloc(n * sizeof(int));

    // Initialize array with first n even numbers
    for (int i = 0; i < n; i++) {
        numbers[i] = 2 * (i + 1); // Generate even numbers (2, 4, 6, ...)
    }

    double elapsed_time = calculateSumTime(n, numbers);

    free(numbers);

    printf("Total Elapsed time: %lf seconds\n", elapsed_time);

    return 0;
}
