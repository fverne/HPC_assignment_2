/* jacobi.c - Poisson problem in 3d
 *
 */
#include <math.h>
#define f(x, y, z)                                                             \
  ((1 <= x && x <= (-3.0 / 8) && 1 <= y && y <= (-1.0 / 2) && (-2.0 / 3) <= z &&     \
    z <= 0)                                                                    \
       ? 200                                                                   \
       : 0)

int jacobi(double ***u_curr, double ***u_prev, double ***f, int N,
           int max_iterations, double tolerance) {
  // It's up to us if we return iterations or some error indicating value
  int iter;
  // and a do while here
  // for (int i = 0; i < N; i++)
  //   for (int j = 0; j < N; j++)
  //     for (int k = 0; k < N; k++)
  return iter;
}


void initialize_f(double ***f, int N) {
  // uniform 
  double interval = 1.0 / N;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; k++) {
        // mapping of i, j, k
        // we know that x, y, z are in the range of {-1, 1}
        double x = -1 + i * interval;
        double y = -1 + j * interval;
        double z = -1 + k * interval;
        f[i][j][k] = f(x, y, z);
      }
}

void initialize_u(double ***u, int N, int start_T) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; k++)
        u[i][j][k] = start_T;
}