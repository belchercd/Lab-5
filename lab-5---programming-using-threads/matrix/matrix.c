#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
 
//int MAX
#define MAX 3
int matA[MAX][MAX]; 
int matB[MAX][MAX]; 

int matSumResult[MAX][MAX];
int matDiffResult[MAX][MAX]; 
int matProductResult[MAX][MAX]; 

//int MAX;

void fillMatrix(int matrix[MAX][MAX]) {
    for(int i = 0; i<MAX; i++) {
        for(int j = 0; j<MAX; j++) {
            matrix[i][j] = rand()%10+1;
        }
    }
}

void printMatrix(int matrix[MAX][MAX]) {
    for(int i = 0; i<MAX; i++) {
        for(int j = 0; j<MAX; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the sum of the
// values at the coordinates of matA and matB.
void* computeSum(void* args) { // pass in the number of the ith thread
  int cell = *((int *) args);
  
  int i;
  for(i = 0; i < MAX; i++){
    matSumResult[cell][i] = matA[cell][i] + matB[cell][i];
  }
  
  return NULL;
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the difference of the
// values at the coordinates of matA and matB.
void* computeDiff(void* args) { // pass in the number of the ith thread
  int cell = *((int *) args);  
  
  int i;
  for(i = 0; i < MAX; i++){
    matDiffResult[cell][i] = matA[cell][i] - matB[cell][i];;
  }
  
  return NULL;
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the inner product
// of matA and matB.
void* computeProduct(void* args) { // pass in the number of the ith thread
  int cell = *((int *) args);  
  
  int i;
  int j;
  for(i = 0; i < MAX; i++){
    for(j = 0; j < MAX; j++){
      matProductResult[cell][i] += matA[cell][j] * matB[j][i];
    }
  }  
  return NULL;
}

// Spawn a thread to fill each cell in each result matrix.
// How many threads will you spawn?
int main() {
  srand(time(0));  // Do Not Remove. Just ignore and continue below.
  
  // 0. Get the matrix size from the command line and assign it to MAX
  /*printf("Enter matrix size: \n");
  scanf("%d", &max);
  MAX = max;
  //MAX = atoi(argv[1]);*/
  
  // 1. Fill the matrices (matA and matB) with random values.
  fillMatrix(matA);
  fillMatrix(matB);
  
  // 2. Print the initial matrices.
  printf("Matrix A:\n");
  printMatrix(matA);
  printf("Matrix B:\n");
  printMatrix(matB);
    
  // 3. Create pthread_t objects for our threads.
  pthread_t objects[MAX];
    
  // 4. Create a thread for each cell of each matrix operation

  // You'll need to pass in the coordinates of the cell you want the thread
  // to compute.
  
  // One way to do this is to malloc memory for the thread number i, populate the coordinates
  // into that space, and pass that address to the thread. The thread will use that number to calcuate 
  // its portion of the matrix. The thread will then have to free that space when it's done with what's in that memory.
  
  for(int i = 0; i < MAX; i++){
    int *arg = malloc(sizeof(arg));
    *arg = i;
    
    pthread_create(&objects[0], NULL, computeSum, arg);
    pthread_create(&objects[1], NULL, computeDiff, arg);
    pthread_create(&objects[2], NULL, computeProduct, arg);
    
    // 5. Wait for all threads to finish.
    pthread_join(objects[0], NULL);
    pthread_join(objects[1], NULL);
    pthread_join(objects[2], NULL);
  }
  
  /*// 5. Wait for all threads to finish.
  for(int i = 0; i < MAX; i++){
    int *arg = malloc(sizeof(arg));
    *arg = i;
    
    pthread_join(objects[0], NULL);
    pthread_join(objects[1], NULL);
    pthread_join(objects[2], NULL);
  }*/
    
    // 6. Print the results.
    printf("Results:\n");
    printf("Sum:\n");
    printMatrix(matSumResult);
    printf("Difference:\n");
    printMatrix(matDiffResult);
    printf("Product:\n");
    printMatrix(matProductResult);
    
  return 0;
  
}