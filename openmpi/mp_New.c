#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        printf("Hello from thread %d\n", threadID);
    }

    return 0;
}
