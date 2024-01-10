#include "util.h"

#define f(x, y, z)                                                             \
  ((1 <= x && x <= (-3.0 / 8) && 1 <= y && y <= (-1.0 / 2) &&                  \
    (-2.0 / 3) <= z && z <= 0)                                                 \
       ? 200                                                                   \
       : 0)

inline double u_value(int x, int y, int z, double start_T) {
  double value;
  if (x == 1 || x == -1 || y == 1 || z == 1 || z == -1)
    value = 20.0;
  else if (y == -1)
    value = 0.0;
  else
    value = start_T;
  return value;
}

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
  double delta = 1.0 / (N - 1);
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
  double delta = 1.0 / (N - 1);
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; k++) {
        double x = -1 + i * delta;
        double y = -1 + j * delta;
        double z = -1 + k * delta;
        // maybe also this as a macro
        u[i][j][k] = u_value(start_T, x, y, z);
      }
}