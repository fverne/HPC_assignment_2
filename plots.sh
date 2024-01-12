python3 convergeplot.py \
    "src/data/tolerance_j_thno4.dat" \
    "src/data/tolerance_gs_thno4.dat" \
    -l \
    "jacobi" \
    "gauss" \
    -n plots/convergeplot.png \
    -t "Convergence Comparison" \
  

python3 iterationspersecplot.py \
    "src/data/grid_j_thno4.dat" \
    "src/data/grid_gs_thno4.dat" \
    -l \
    "jacobi" \
    "gauss" \
    -n plots/iterationspersecplot.png \
    -t "Iterations Per Seconds, Whole Grid"
