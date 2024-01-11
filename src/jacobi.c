/* jacobi.c - Poisson problem in 3d
 *
 */
#include "jacobi.h"
#include <math.h>

int jacobi(double ***u_curr, double ***u_prev, double ***f, int N,
           int max_iterations, double tolerance) {
  int iter = 0;
  double delta = 2.0 / (N - 1);
  double fraction = (1.0 / 6);
  double delta_2 = pow2(delta);
  double distance;
  double u_prev_value;
  do {
    distance = 0;
    for (int i = 1; i < N - 1; i++)
      for (int j = 1; j < N - 1; j++)
        for (int k = 1; k < N - 1; k++) {
          u_curr[i][j][k] =
              fraction *
              (u_prev[i - 1][j][k] + u_prev[i + 1][j][k] + u_prev[i][j - 1][k] +
               u_prev[i][j + 1][k] + u_prev[i][j][k - 1] + u_prev[i][j][k + 1] +
               delta_2 * f[i][j][k]);
          // distance
          distance += pow2(u_prev[i][j][k] - u_curr[i][j][k]);
          // swap pointers
        }
    double ***temp = u_prev;
    u_prev = u_curr;
    u_curr = temp;

    ++iter;
    distance = sqrt(distance);
  } while (iter < max_iterations && distance > tolerance);

  if (iter % 2 == 0) {
    double ***temp = u_prev;
    u_prev = u_curr;
    u_curr = temp;
  }
  return iter;
}
