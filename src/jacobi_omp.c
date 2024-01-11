/* jacobi.c - Poisson problem in 3d with omp
 *
 */
#include <math.h>
#include <omp.h>
#include "jacobi.h"
#include "util.h"

int jacobi_omp(
  double ***u_curr, double ***u_prev, double ***f, 
  int N, int iter_max, double tolerance) {
  int iter = 0;
  double delta = 2.0 / (N - 1);
  double distance;
  double t;
  do {
    distance = 0;
    #pragma omp parallel for private(t) reduction(+:distance) 
    for (int i = 1; i < N - 1; i++)
      for (int j = 1; j < N - 1; j++)
        for (int k = 1; k < N - 1; k++) {
          double update_value =
              (1.0 / 6) *
              (u_prev[i - 1][j][k] + u_prev[i + 1][j][k] + u_prev[i][j - 1][k] +
               u_prev[i][j + 1][k] + u_prev[i][j][k - 1] + u_prev[i][j][k + 1] +
               pow2(delta) * f[i][j][k]);
          u_curr[i][j][k] = update_value;
          t = pow2(u_prev[i][j][k] - update_value);
          distance += t;
    } // Parallel region ends here

    double ***tmp = u_prev;           
    u_prev = u_curr;
    u_curr = tmp;

    ++iter;
    distance = sqrt(distance);
  } while (iter < iter_max && distance > tolerance);

  // check the odd/even of iterations
  if (iter % 2 == 0) {
    double ***tmp = u_prev;           
    u_prev = u_curr;
    u_curr = tmp;
  }  

  return iter;
}