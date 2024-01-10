#include "util.h"

#define f(x, y, z)                                                             \
  ((1 <= x && x <= (-3.0 / 8) && 1 <= y && y <= (-1.0 / 2) &&                  \
    (-2.0 / 3) <= z && z <= 0)                                                 \
       ? 200                                                                   \
       : 0)

void* emalloc(size_t size)
{
  void *ptr;
  if ((ptr = malloc(sizeof(size))) == NULL)
  {
    perror("Error: Allocating memory failed.");
    exit(EXIT_FAILURE);
  }
  return ptr;
}

void initialize_f(double ***f, int N) {
  double delta = 1.0 / N;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; k++) {
        // mapping of i, j, k
        // we know that x, y, z are in the range of {-1, 1}
        double x = -1 + i * delta;
        double y = -1 + j * delta;
        double z = -1 + k * delta;
        f[i][j][k] = f(x, y, z);
      }
}

void initialize_u(double ***u, int N, int start_T) {
  double delta = 1.0 / N;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; k++) {
        double x = -1 + i * delta;
        double y = -1 + j * delta;
        double z = -1 + k * delta;
        // maybe also this as a macro
        if (x == 1 || x == -1 || y == 1 || z == 1 || z == -1)
          u[i][j][k] = 20;
        else if (y == -1)
          u[i][j][k] = 0;
        else
          u[i][j][k] = start_T;
      }
}