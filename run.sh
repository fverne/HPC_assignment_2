#!/bin/bash
#BSUB -J 4cores
#BSUB -o src/output/1node4cores.out
#BSUB -q hpcintro
#BSUB -W 30
#BSUB -R "rusage[mem=512MB]"
#BSUB -R "span[hosts=1]"
#BSUB -n 24

export OMP_NUM_THREADS=1


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
cd "src"
# remove any trash from other runs
rm -f *.bin *.vtk
# create logs dir if doesn't exist
mkdir -p "logs"
# remove previous logs
rm -f logs/*.log

# no real meaning behind these values for now
ITERATIONS_DEF=10000
TOLERANCE_DEF=0.0001
GRID_DEF=50 # temporary, change me

for THREAD in "${THREAD_VALUES[@]}"; do
  export OMP_NUM_THREADS=${THREAD:-1}
  ./poisson_jomp $GRID_DEF $ITERATIONS_DEF $TOLERANCE_DEF 0.0 4 >>"logs/threads_jomp.log"
  ./poisson_gsomp $GRID_DEF $ITERATIONS_DEF $TOLERANCE_DEF 0.0 4 >>"logs/threads_gsomp.log"
  export OMP_NUM_THREADS=1
done

for GRID in "${GRID_VALUES[@]}"; do
  ./poisson_j $GRID $ITERATIONS_DEF $TOLERANCE_DEF 0.0 4 >>"logs/grid_j.log"
  ./poisson_gs $GRID $ITERATIONS_DEF $TOLERANCE_DEF 0.0 4 >>"logs/grid_gs.log"
done

for TOLERANCE in "${TOLERANCE_VALUES[@]}"; do
  ./poisson_j $GRID_DEF $ITERATIONS_DEF $TOLERANCE 0.0 4 >>"logs/tolerance_j.log"
  ./poisson_gs $GRID_DEF $ITERATIONS_DEF $TOLERANCE 0.0 4 >>"logs/tolerance_gs.log"
done

# zip logs
zip -r "logs_$(date +'%Y%m%d_%H%M%S').zip" logs

echo "$(pwd)"
# create output dirs
mkdir -p "output/vtk"
mkdir -p "output/bin"
mkdir -p "output/zip"

# move output files to the output dirs
mv *.zip "output/zip"
mv *.bin "output/bin"
mv *.vtk "output/vtk"

# check sequential with bin version!
# UNIQ=$(md5sum *.bin | uniq -c | wc -l)
# ALL=$(ls *.bin | wc -l)
# echo -e "Unique files: ${UNIQ}"
# echo -e "Total files: ${ALL}"