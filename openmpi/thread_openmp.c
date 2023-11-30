#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 4

int main() {
    int n = 100; // Replace with the desired number of even elements
    int numbers[n];

    // Initialize array with first n even numbers
    for (int i = 0; i < n; i++) {
        numbers[i] = 2 * (i + 1); // Generate even numbers (2, 4, 6, ...)
    }

    long long totalSum = 0;

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

    printf("Sum of first %d even numbers: %lld\n", n, totalSum);

    return 0;
}
