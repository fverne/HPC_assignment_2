/* jacobi.h - Poisson problem
 *
 * $Id: jacobi.h,v 1.1 2006/09/28 10:12:58 bd Exp bd $
 */

#ifndef _JACOBI_OMP_H
#define _JACOBI_OMP_H

int jacobi_omp(
    double ***u_curr, double ***u_prev, double ***f, 
    int N, int iter_max, double tolerance);

#endif
