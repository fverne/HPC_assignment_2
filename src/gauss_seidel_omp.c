/* gauss_seidel.c - Poisson problem in 3d with omp
 *
 */
#include "gauss_seidel.h"

int gauss_seidel_omp(double ***u_curr, double ***f, int N, int max_iterations, double tolerance) {
    double delta = 2.0 / (N - 1);
    double fraction = (1.0 / 6);
    double delta_2 = pow2(delta);
    int iter;

    for (iter = 0; iter < max_iterations; iter++) {
        int i, j, k;
        #pragma omp for ordered(2) schedule(static, 1) private(i, j, k)
        // #pragma omp for schedule(static, 1) private(i, j, k)
        for (i = 1; i < N - 1; i++) {
            for (j = 1; j < N - 1; j++) {
                #pragma omp ordered depend(sink: i-1, j) depend(sink: i, j-1) 
                for (k = 1; k < N - 1; k++) {
                    // depend(sink: i, j, k-1) pragma omp ordered depend(sink: i-1, j, k) \
                    depend(sink: i, j-1, k)
                    u_curr[i][j][k] = fraction * (u_curr[i - 1][j][k] + u_curr[i + 1][j][k] +
                                                  u_curr[i][j - 1][k] + u_curr[i][j + 1][k] +
                                                  u_curr[i][j][k - 1] + u_curr[i][j][k + 1] +
                                                  delta_2 * f[i][j][k]);
                    #pragma omp ordered depend(source)
                }
            }
        }
    }
    return iter;
}

// This was a try to implement the block implementation

// int gauss_seidel_omp_block(double ***u_curr, double ***f, int N, int max_iterations,
//                      double tolerance) {
//   int iter = 0;
//   double delta = 2.0 / (N - 1);
//   double fraction = (1.0 / 6);
//   double delta_2 = pow2(delta);
//   // Arbitrary size for the blocks (we have to think what's a good block size)
//   int TS = 8;

//   for (iter = 0; iter < max_iterations; iter++) {23
//     int jj, kk, ii; 
//     int i, j, k;
//     #pragma omp for schedule(static, 1) private(ii, jj, kk, i, j, k)
//     // #pragma omp parallel
//     for (ii = 1; ii < N - 1; ii += TS) {
//       for (jj = 1; jj < N - 1; jj += TS) {
//         for (kk = 1; kk < N - 1; kk += TS) {
//           int imax = ((ii + TS) < N - 1) ? (ii + TS) : (N - 1);
//           int jmax = ((jj + TS) < N - 1) ? (jj + TS) : (N - 1);
//           int kmax = ((kk + TS) < N - 1) ? (kk + TS) : (N - 1);
//           // int i, j, k;
//           // #pragma omp for ordered(3) private(i, j, k)
//           for (i = ii; i < imax; ++i) {
//             for (j = jj; j < jmax; ++j) {
//               for (k = kk; k < kmax; ++k) {
//                 // #pragma omp ordered depend(sink: i-1, j, k) \
//                 // depend(sink: i, j-1, k) \
//                 // depend(sink: i, j, k-1) 
//                 u_curr[i][j][k] =
//                     fraction * (u_curr[i - 1][j][k] + u_curr[i + 1][j][k] +
//                                 u_curr[i][j - 1][k] + u_curr[i][j + 1][k] +
//                                 u_curr[i][j][k - 1] + u_curr[i][j][k + 1] +
//                                 delta_2 * f[i][j][k]);
//                 // #pragma omp ordered depend(source)
//               }
//             }
//           }
//         }
//       }
//     }
//   }
//   return iter;
// }

/* #pragma omp task firstprivate(ii, jj, kk) \ */
/*     depend(inout \ */
/*            : u_curr [ii:imax] [jj:jmax] [kk:kmax]) \ */
/*         depend(in \ */
/*                : u_curr [ii - imax:imax] [jj:jmax] [kk:kmax], \ */
/*                  u_curr [ii + imax:imax] [jj:jmax] [kk:kmax], \ */
/*                  u_curr [ii:imax] [jj - jmax:jmax] [kk:kmax], \ */
/*                  u_curr [ii:imax] [jj + jmax:jmax] [kk:kmax], \ */
/*                  u_curr [ii:imax] [jj:jmax] [kk - kmax:kmax], \ */
/*                  u_curr [ii:imax] [jj:jmax] [kk + kmax:kmax]) */