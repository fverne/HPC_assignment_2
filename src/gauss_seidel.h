/* gauss_seidel.h - Poisson problem
 *
 */
#ifndef _GAUSS_SEIDEL_H
#define _GAUSS_SEIDEL_H
#include "util.h"

int gauss_seidel(double ***u_curr, double ***u_prev, double ***f, int N,
                 int max_iterations, double tolerance);

#endif
