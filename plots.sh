python3 convergeplot.py \
    "src/data/tolerance_j.dat" \
    "src/data/tolerance_gs.dat" \
    -l \
    "jacobi" \
    "gauss" \
    -n plots/convergeplot.png \
    -t "Convergence Comparison (N=100)" \
  

python3 iterationspersecplot.py \
    "src/data/grid_j.dat" \
    "src/data/grid_gs.dat" \
    -l \
    "jacobi" \
    "gauss" \
    -n plots/iterationspersecplot.png \
    -t "Iterations Per Seconds, Whole Grid"

python3 speedupplot.py \
    "src/data/threads_jomp.dat" \
    "src/data/threads_gsomp.dat" \
    -l \
    "jacobi (OMP) Baseline" \
    "gauss-seidel (OMP) Baseline" \
    -n plots/speedupplot.png \
    -t "Speedup Comparison (N = 100)"
