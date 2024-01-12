python3 convergeplot.py \
    "src/data/tolerance_j.dat" \
    "src/data/tolerance_gs.dat" \
    -l \
    "Jacobi" \
    "Gauss-Seidel" \
    -n plots/convergeplot.png \
    -t "Convergence Comparison (N=100)" \
  

python3 iterationspersecplot.py \
    "src/data/grid_j.dat" \
    "src/data/grid_gs.dat" \
    -l \
    "Jacobi" \
    "Gauss-Seidel" \
    -n plots/iterationspersecplot.png \
    -t "Iterations Per Seconds, Whole Grid"

python3 iterationsplot.py \
    "src/data/grid_j.dat" \
    "src/data/grid_gs.dat" \
    -l \
    "Jacobi" \
    "Gauss-Seidel" \
    -n plots/iterationsplot.png \
    -t "Iterations Comparison"

python3 iterationsjplot.py \
    "src/data/grid_j.dat" \
    -l \
    "Jacobi" \
    -n plots/iterationsjplot.png \
    -t "Iterations and Gridsize Comparison"

python3 speedupplot.py \
    "src/data/threads_jomp.dat" \
    "src/data/threads_gsomp.dat" \
    -l \
    "Jacobi (OMP)" \
    "Gauss-Seidel (OMP)" \
    -n plots/speedupplot.png \
    -t "Speedup Comparison (N = 100)"

python3 speedupjplot.py \
    "src/data/threads_jomp.dat" \
    -l \
    "Jacobi (OMP)" \
    -n plots/speedupjplot.png \
    -t "Speedup Comparison (N = 100)"

python3 speedupgsplot.py \
    "src/data/threads_gsomp.dat" \
    -l \
    "Gauss-Seidel (OMP)" \
    -n plots/speedupgsplot.png \
    -t "Speedup Comparison (N = 100)"

python3 speedupcompilerplot.py \
    "src/data/rawO0.dat" \
    "src/data/rawO3.dat" \
    "src/data/rawOfast.dat" \
    -l \
    "-O0 " \
    "-O3 " \
    "-Ofast -funroll-loops " \
    -n plots/speedupcompilerplot.png \
    -t "Compiler Options Comparison"