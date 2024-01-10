/* gauss_seidel.h - Poisson problem
 *
 */
#ifndef _GAUSS_SEIDEL_H
#define _GAUSS_SEIDEL_H

// define your function prototype here
// gauss_seidel(...);

int gauss_seidel(double ***u_curr, double ***u_prev, double ***f, int N,
                 int max_iterations, double tolerance);

#endif
