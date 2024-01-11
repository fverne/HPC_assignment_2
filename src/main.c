/* main.c - Poisson problem in 3D
 *
 */
#include "alloc3d.h"
#include "print.h"
#include "util.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _JACOBI
#include "jacobi.h"
#endif

#ifdef _GAUSS_SEIDEL
#include "gauss_seidel.h"
#endif

#ifdef _GAUSS_SEIDEL_OMP
#include "gauss_seidel_omp.h"
#endif

#define N_DEFAULT 100

int main(int argc, char *argv[]) {

  int N = N_DEFAULT;
  int iter = 0;
  int iter_max = 1000;
  double tolerance;
  double start_T;
  int output_type = 0;
  char *output_prefix;
  char *output_ext = "";
  char output_filename[FILENAME_MAX];
  double ***u_curr = NULL;
  double ***u_prev = NULL;
  double ***f = NULL;
  double itime, ftime, exec_time;
  /* get the parameters from the command line */
  N = atoi(argv[1]);         /* grid size, the number of total */
                             /* grid points in one dimension */
  iter_max = atoi(argv[2]);  /* max. no. of iterations */
  tolerance = atof(argv[3]); /* tolerance */
  start_T = atof(argv[4]);   /* start T for all inner grid points */
  if (argc == 6) {
    output_type = atoi(argv[5]); /* ouput type */
  }
  /* allocate memory */
  if ((u_curr = malloc_3d(N, N, N)) == NULL) {
    perror("array u: allocation failed");
    exit(-1);
  }
  if ((u_prev = malloc_3d(N, N, N)) == NULL) {
    perror("array u: allocation failed");
    exit(-1);
  }
  if ((f = malloc_3d(N, N, N)) == NULL) {
    perror("array u: allocation failed");
    exit(-1);
  }

  /* Initialize the arrays */
  initialize_u(u_curr, N, start_T);
  initialize_f(f, N);

/* initialize prev for jacobi as well */
#ifdef _JACOBI
  initialize_u(u_prev, N, start_T);
#endif
  /* start the timing for the functions */
  itime = omp_get_wtime();

#ifdef _JACOBI
  iter = jacobi(u_curr, u_prev, f, N, iter_max, tolerance);
#endif

#ifdef _GAUSS_SEIDEL
  iter = gauss_seidel(u_curr, f, N, iter_max, tolerance);
#endif

#ifdef _GAUSS_SEIDEL_OMP
  iter = gauss_seidel_omp(u_curr, f, N, iter_max, tolerance);
  // iter = gauss_seidel_omp_block(u_curr, f, N, iter_max, tolerance);
#endif

  ftime = omp_get_wtime();
  exec_time = ftime - itime;

#ifdef _JACOBI
  output_prefix = "jacobi";
  free_3d(u_prev);
#endif

#ifdef _GAUSS_SEIDEL
  output_prefix = "gauss_seidel";
#endif

#ifdef _JACOBI_OMP
  output_prefix = "jacobi_omp";
#endif

#ifdef _GAUSS_SEIDEL_OMP
  output_prefix = "gauss_seidel_omp";
#endif

  printf("=====================Info=====================\n");
  printf("N:\t\t\t\t\t%d\n", N);
  printf("Tolerance:\t\t\t\t%f\n", tolerance);
  printf("Max iterations:\t\t\t\t%d\n", iter_max);
  printf("Time:\t\t\t\t\t%f\n", exec_time);
  printf("Number of iterations:\t\t\t%d\n", iter);
  printf("Number of iterations per second:\t%f\n", iter / exec_time);

#if defined(_JACOBI_OMP) || defined(_GAUSS_SEIDEL_OMP)
  // Number of threads here (take value from make or smth)
#pragma omp parallel
  {
    int num_threads = omp_get_num_threads();
#pragma omp master
    { printf("Number of threads:\t\t\t%d\n", num_threads); }
  }

#endif

  switch (output_type) {
  case 0:
    break;
  case 3:
    output_ext = ".bin";
    sprintf(output_filename, "%s_N%d_T%.8f_I%d%s", output_prefix, N, tolerance,
            iter_max, output_ext);
    fprintf(stderr, "Wrote binary dump to %s\n.", output_filename);
    print_binary(output_filename, N, u_curr);
    break;
  case 4:
    output_ext = ".vtk";
    sprintf(output_filename, "%s_N%d_T%.8f_I%d%s", output_prefix, N, tolerance,
            iter_max, output_ext);
    fprintf(stderr, "Wrote VTK file to %s.\n", output_filename);
    print_vtk(output_filename, N, u_curr);
    break;
  default:
    fprintf(stderr, "Non-supported output type!\n");
    break;
  }

  /* de-allocate memory */
  free_3d(u_curr);
  free_3d(f);

  return (0);
}
