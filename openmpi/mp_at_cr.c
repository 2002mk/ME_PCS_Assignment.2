#include <stdio.h> 
#include <omp.h> 
int main() { 
 const int numIterations = 1000000; 
 int sharedVar = 0; 
 #pragma omp parallel for 
 for (int i = 0; i < numIterations; ++i) { 
 #pragma omp atomic 
 sharedVar++; // Atomic operation to increment sharedVar safely 
 // Use of 'if' construct to conditionally increment sharedVar
 #pragma omp critical 
 if (i % 2 == 0) 
 sharedVar++; 
 } 
 printf("Final value of sharedVar: %d\n", sharedVar); 
 return 0; 
} 
