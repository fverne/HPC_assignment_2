/* jacobi.c - Poisson problem in 3d with omp
 *
 */
#include <math.h>
#include <omp.h>

int jacobi_omp(
    double ***u_curr, double ***u_prev, double ***f, 
    int N, int iter_max, double tolerance) {

}