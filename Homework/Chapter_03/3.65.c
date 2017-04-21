#define M 15

void transpose(long A[M][M]) {
  long i, j;
  for (i = 0; i < M; i++)
    for (j = 0; j < i; j++) {
      long t = A[i][j];
      A[i][j] = A[j][i];
      A[j][i] = t;
    }
}

