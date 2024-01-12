#!/bin/bash 

TOLERANCE_VALUES=(
  0.001
  0.0001
  0.00001
  0.000001
)

GRID_VALUES=(
  10
  20
  30
  40
  50
  75
  100
  # 200
  # 300
  # 400
)

THREAD_VALUES=(
  1
  2
  4
  8
  12
  16
  20
  24
)

# go to source dir
cd src
# remove any non useful files from previous runs
rm -f *.bin *.vtk *.log
# create directories if they doesn't exist
mkdir -p "output/logs"
mkdir -p "output/bsub"
mkdir -p "output/vtk"
mkdir -p "output/bin"
mkdir -p "output/zip"
# remove previous results (they are already cleaned up)
rm -f "output/logs/*.log"
rm -f "output/vtk/*.bin"
rm -f "output/bin/*.vtk"
# no real meaning behind these values for now
ITERATIONS_DEF=10000
TOLERANCE_DEF=0.0001
GRID_DEF=50 # temporary, change me

for THREAD in "${THREAD_VALUES[@]}"; do
  export OMP_NUM_THREADS=${THREAD:-1}
  bsub -J jomp -q hpcintro  -W 30  -R "rusage[mem=512MB]"  -R "span[hosts=1]"  -n 24  -o "output/bsub/"$THREAD"threads_jomp" ./poisson_jomp $GRID_DEF $ITERATIONS_DEF $TOLERANCE_DEF 0.0 4 >>"output/logs/threads_jomp.log"
  bsub -J gsomp -q hpcintro  -W 30  -R "rusage[mem=512MB]"  -R "span[hosts=1]"  -n 24  -o "output/bsub/"$THREAD"threads_gsomp" ./poisson_gsomp $GRID_DEF $ITERATIONS_DEF $TOLERANCE_DEF 0.0 4 >>"output/logs/threads_gsomp.log"
  export OMP_NUM_THREADS=1
done

for GRID in "${GRID_VALUES[@]}"; do
  bsub -J jgrid -q hpcintro  -W 30  -R "rusage[mem=512MB]"  -R "span[hosts=1]"  -n 24  -o "output/bsub/"$GRID"poisson_j" ./poisson_j $GRID $ITERATIONS_DEF $TOLERANCE_DEF 0.0 4 >>"output/logs/grid_j.log"
  bsub -J gsgrid -q hpcintro  -W 30  -R "rusage[mem=512MB]"  -R "span[hosts=1]"  -n 24  -o "output/bsub/"$GRID"poisson_gs" ./poisson_gs $GRID $ITERATIONS_DEF $TOLERANCE_DEF 0.0 4 >>"output/logs/grid_gs.log"
done

for TOLERANCE in "${TOLERANCE_VALUES[@]}"; do
  bsub -J jtolerance -q hpcintro  -W 30  -R "rusage[mem=512MB]"  -R "span[hosts=1]"  -n 24  -o "output/bsub/"$TOLERANCE"tolerance_j" ./poisson_j $GRID_DEF $ITERATIONS_DEF $TOLERANCE 0.0 4 >>"logs/tolerance_j.log"
  bsub -J gstolerance -q hpcintro  -W 30  -R "rusage[mem=512MB]"  -R "span[hosts=1]"  -n 24  -o "output/bsub/"$TOLERANCE"tolerance_gs" ./poisson_gs $GRID_DEF $ITERATIONS_DEF $TOLERANCE 0.0 4 >>"logs/tolerance_gs.log"
done
