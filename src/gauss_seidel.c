/* gauss_seidel.c - Poisson problem in 3d
 *
 */
#include "gauss_seidel.h"
#include <math.h>

int gauss_seidel(double ***u_curr, double ***u_prev, double ***f, int N,
                 int max_iterations, double tolerance) {
  int iter = 0;
  double delta = 2.0 / (N - 1);
  double fraction = (1.0 / 6);
  double delta_2 = pow2(delta);
  double distance;
  do {
    distance = 0;
    for (int i = 1; i < N - 1; i++)
      for (int j = 1; j < N - 1; j++)
        for (int k = 1; k < N - 1; k++) {
          u_curr[i][j][k] =
              fraction *
              (u_curr[i - 1][j][k] + u_prev[i + 1][j][k] + u_curr[i][j -
              1][k] +
               u_prev[i][j + 1][k] + u_curr[i][j][k - 1] + u_prev[i][j][k +
               1] + delta_2 * f[i][j][k]);
              // (u_curr[i - 1][j][k] + u_curr[i + 1][j][k] + u_curr[i][j - 1][k] +
              //  u_curr[i][j + 1][k] + u_curr[i][j][k - 1] + u_curr[i][j][k + 1] +
              //  delta_2 * f[i][j][k]);
          // distance
          distance += pow2(u_prev[i][j][k] - u_curr[i][j][k]);
          // copy
          u_prev[i][j][k] = u_curr[i][j][k];
        }
    ++iter;
    distance = sqrt(distance);
  } while (iter < max_iterations && distance > tolerance);

  return iter;
}
