/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int a1,a2,a3,a4,a5,a6,a7,a8;
    if(N == 32){
        for(int i = 0;i < 4;i++){
            for(int j = 0;j < 4;j++){
                for(int k = (i << 3); k < ((i + 1) << 3);k++){
                    int h = j << 3;
                    a1 = A[k][h];
                    a2 = A[k][h + 1];
                    a3 = A[k][h + 2];
                    a4 = A[k][h + 3];
                    a5 = A[k][h + 4];
                    a6 = A[k][h + 5];
                    a7 = A[k][h + 6];
                    a8 = A[k][h + 7];
                    
                    B[h][k] = a1;
                    B[h + 1][k] = a2;
                    B[h + 2][k] = a3;
                    B[h + 3][k] = a4;
                    B[h + 4][k] = a5;
                    B[h + 5][k] = a6;
                    B[h + 6][k] = a7;
                    B[h + 7][k] = a8;
                }
            }
        }
    }
    else if(N == 64){
        for(int i = 0;i < 64;i += 8){
            for(int j = 0;j < 64;j += 8){
                for(int k = j;k < j + 4;k++){
                    a1 = A[k][i];
                    a2 = A[k][i + 1];
                    a3 = A[k][i + 2];
                    a4 = A[k][i + 3];
                    a5 = A[k][i + 4];
                    a6 = A[k][i + 5];
                    a7 = A[k][i + 6];
                    a8 = A[k][i + 7];

                    B[i][k] = a1;
                    B[i][k + 4] = a5;
                    B[i + 1][k] = a2;
                    B[i + 1][k + 4] = a6;
                    B[i + 2][k] = a3;
                    B[i + 2][k + 4] = a7;
                    B[i + 3][k] = a4;
                    B[i + 3][k + 4] = a8;
                }
                for(int k = i;k < i + 4;k++){
                    a1 = B[k][j + 4];
                    a2 = B[k][j + 5];
                    a3 = B[k][j + 6];
                    a4 = B[k][j + 7];
                    a5 = A[j + 4][k];
                    a6 = A[j + 5][k];
                    a7 = A[j + 6][k];
                    a8 = A[j + 7][k];

                    B[k][j + 4] = a5;
                    B[k][j + 5] = a6;
                    B[k][j + 6] = a7;
                    B[k][j + 7] = a8;
                    B[k + 4][j] = a1;
                    B[k + 4][j + 1] = a2;
                    B[k + 4][j + 2] = a3;
                    B[k + 4][j + 3] = a4;
                }
                for(int k = i + 4;k < i + 8;k++){
                     a1 = A[j + 4][k];
                     a2 = A[j + 5][k];
                     a3 = A[j + 6][k];
                     a4 = A[j + 7][k];

                     B[k][j + 4] = a1;
                     B[k][j + 5] = a2;
                     B[k][j + 6] = a3;
                     B[k][j + 7] = a4;
                }
            }
        }
    }
    else{
        for(int i = 0;i < N;i += 8){
            for(int j = 0;j < M;j++){
                if(i + 8 <= N && j < M){
                    a1 = A[i][j];
                    a2 = A[i + 1][j];
                    a3 = A[i + 2][j];
                    a4 = A[i + 3][j];
                    a5 = A[i + 4][j];
                    a6 = A[i + 5][j];
                    a7 = A[i + 6][j];
                    a8 = A[i + 7][j];
                    
                    B[j][i] = a1;
                    B[j][i + 1] = a2;
                    B[j][i + 2] = a3;
                    B[j][i + 3] = a4;
                    B[j][i + 4] = a5;
                    B[j][i + 5] = a6;
                    B[j][i + 6] = a7;
                    B[j][i + 7] = a8;
                }
                else{
                    for(int k = i; k < i + 8 && k < N; k++){
                        B[j][k] = A[k][j];
                    }
                }
            }
        }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}


