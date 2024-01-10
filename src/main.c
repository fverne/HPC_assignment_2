/* main.c - Poisson problem in 3D
 *
 */
#include "alloc3d.h"
#include "print.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _JACOBI
#include "jacobi.h"
#endif

#ifdef _GAUSS_SEIDEL
#include "gauss_seidel.h"
#endif

#define N_DEFAULT 100

int main(int argc, char *argv[]) {

  int N = N_DEFAULT;
  int iter_max = 1000;
  double tolerance;
  double start_T;
  int output_type = 0;
  char *output_prefix = "poisson_res";
  char *output_ext = "";
  char output_filename[FILENAME_MAX];
  double ***u_curr = NULL;
  double ***u_prev = NULL;
  double ***f = NULL;
  /* get the paramters from the command line */
  N = atoi(argv[1]);         // grid size
  iter_max = atoi(argv[2]);  // max. no. of iterations
  tolerance = atof(argv[3]); // tolerance
  start_T = atof(argv[4]);   // start T for all inner grid points
  if (argc == 6) {
    output_type = atoi(argv[5]); // ouput type
  }
  // allocate memory
  if ((u_curr = malloc_3d(N, N, N)) == NULL) {
    perror("array u: allocation failed");
    exit(-1);
  }
  if ((u_prev = malloc_3d(N, N, N)) == NULL) {
    perror("array u: allocation failed");
    exit(-1);
  }
  // Initialize the arrays
  initialize_u(u_curr, N, start_T);
  initialize_u(u_prev, N, start_T);
  initialize_f(f);

  // call the jacobi here

  // dump  results if wanted
  switch (output_type) {
  case 0:
    // no output at all
    break;
  case 3:
    output_ext = ".bin";
    sprintf(output_filename, "%s_%d%s", output_prefix, N, output_ext);
    fprintf(stderr, "Write binary dump to %s: ", output_filename);
    print_binary(output_filename, N, u);
    break;
  case 4:
    output_ext = ".vtk";
    sprintf(output_filename, "%s_%d%s", output_prefix, N, output_ext);
    fprintf(stderr, "Write VTK file to %s: ", output_filename);
    print_vtk(output_filename, N, u);
    break;
  default:
    fprintf(stderr, "Non-supported output type!\n");
    break;
  }

  // de-allocate memory
  free_3d(u_curr);
  free_3d(u_prev);

  return (0);
}
