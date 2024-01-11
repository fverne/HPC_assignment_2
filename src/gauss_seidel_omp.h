/* gauss_seidel.h - Poisson problem omp
 *
 */
#ifndef _GAUSS_SEIDEL_OMP_H
#define _GAUSS_SEIDEL_OMP_H
#include "util.h"

int gauss_seidel_omp(double ***u_curr, double ***u_prev, double ***f, int N,
                 int max_iterations, double tolerance);

#endif
