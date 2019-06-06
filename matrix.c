#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double get_time()
{
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main(int argc, char** argv)
{
   int n;
   FILE *fp;

   if((fp = fopen("matrix_c.txt", "w")) == NULL){
      printf("error in opening file!!\n");
      exit(-1);
   }

   fprintf(fp, "no.| time\n");

   for(n = 1; n <= 250; n++){

      double* a = (double*)malloc(n * n * sizeof(double)); // Matrix A
      double* b = (double*)malloc(n * n * sizeof(double)); // Matrix B
      double* c = (double*)malloc(n * n * sizeof(double)); // Matrix C

      // Initialize the matrices to some values.
      int i, j, k;
      for (i = 0; i < n; i++) {
         for (j = 0; j < n; j++) {
            a[i * n + j] = i * n + j; // A[i][j]
            b[i * n + j] = j * n + i; // B[i][j]
            c[i * n + j] = 0; // C[i][j]
         }
      }


      double begin = get_time();

      //Multiplication
      for (i = 0; i < n; i++) {
         for (j = 0; j < n; j++) {
            for(k = 0; k < n; k++) {
               c[i * n + j] += a[i * n + k] * b[k * n + j];
            }
         }
      }

      double end = get_time();

      // Print C for debugging. Comment out the print before measuring the execution time.
      double sum = 0;
      for (i = 0; i < n; i++) {
         for (j = 0; j < n; j++) {
            sum += c[i * n + j];
            // printf("c[%d][%d]=%lf\n", i, j, c[i * n + j]);
         }
      }
      // Print out the sum of all values in C.
      // This should be 450 for N=3, 3680 for N=4, and 18250 for N=5.
      fprintf(fp, "%3d %.6lf\n", n, end - begin);

      free(a);
      free(b);
      free(c);
   }


   return 0;
}
