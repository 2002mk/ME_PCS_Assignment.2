#include<stdio.h> 
#include<omp.h> 
void say_hello(void) 
{ 
int myrank=omp_get_thread_num(); 
int threadcount=omp_get_num_threads(); 
printf("Hello from thread %d of %d\n", myrank,threadcount); 
} 
int main(void) 
{ 
#pragma omp parallel 
printf("Threads:%d, Max:%d\n",omp_get_num_threads(), omp_get_max_threads()); say_hello(); 
return 0; 
} 
