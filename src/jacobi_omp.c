/* jacobi.c - Poisson problem in 3d with omp
 *
 */
#include <math.h>
#include <omp.h>

int jacobi_omp(
    double ***u_curr, double ***u_prev, double ***f, 
    int N, int iter_max, double tolerance) {
  int iter = 0;
  double delta = 2.0 / (N - 1);
  double distance;
  do {
    distance = 0;
    for (int i = 1; i < N - 1; i++)
      for (int j = 1; j < N - 1; j++)
        for (int k = 1; k < N - 1; k++) {
          u_curr[i][j][k] =
              (1.0 / 6) *
              (u_prev[i - 1][j][k] + u_prev[i + 1][j][k] + u_prev[i][j - 1][k] +
               u_prev[i][j + 1][k] + u_prev[i][j][k - 1] + u_prev[i][j][k + 1] +
               pow2(delta) * f[i][j][k]);
          // distance
          distance += pow2(u_prev[i][j][k] - u_curr[i][j][k]);
          // copy
          u_prev[i][j][k] = u_curr[i][j][k];
        }
    ++iter;
    distance = sqrt(distance);
  } while (iter < iter_max && distance > tolerance);

  return iter;
}