/* jacobi.c - Poisson problem in 3d
 *
 */
#include <math.h>
#include "jacobi.h"


#define pow2(x) (x)*(x)


int jacobi(double ***u_curr, double ***u_prev, double ***f, int N,
           int max_iterations, double tolerance) {
  int iter = 0;
  double delta = 1.0 / N;
  double distance = 0;
  do {
    for (int i = 1; i < N; i++)
      for (int j = 1; j < N; j++)
        for (int k = 1; k < N; k++) {
          u_curr[i][j][k] =
              (1.0 / 6) *
              (u_prev[i - 1][j][k] + u_prev[i + 1][j][k] + u_prev[i][j - 1][k] +
               u_prev[i][j + 1][k] + u_prev[i][j][k - 1] + u_prev[i][j][k + 1] +
               pow2(delta) * f[i][j][k]);
          // distance
          distance += pow2(fabs(u_prev[i][j][k] - u_curr[i][j][k]));
          // copy
          u_prev[i][j][k] = u_curr[i][j][k];
        }
    ++iter;
    distance = sqrt(distance);
  } while (iter < max_iterations || distance > tolerance);

  return iter;
}
