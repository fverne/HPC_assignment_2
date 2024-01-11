#!/bin/zsh

# TODO:
# - Add bsub
# - Add bigger numbers

TOLERANCE_VALUES=(
  0.0000001
  0.000001
  0.0001
  0.001
)

GRID_VALUES=(
  10
  20
  30
  40
  50
  100
)

# go to source dir
cd "src"
# create logs dir if doesn't exist
mkdir -p "logs"
# remove previous logs
rm -f "logs/*.log"

# no real meaning behind these values for now
ITERATIONS_DEF=10000
TOLERANCE_DEF=0.00001
GRID_DEF=50

for GRID in "${GRID_VALUES[@]}"; do
  ./poisson_j $GRID $ITERATIONS_DEF $TOLERANCE_DEF 0.0 4 >>"logs/grid_j.log"
  ./poisson_gs $GRID $ITERATIONS_DEF $TOLERANCE_DEF 0.0 4 >>"logs/grid_gs.log"
  ./poisson_j $GRID $ITERATIONS_DEF $TOLERANCE_DEF 0.0 3 >/dev/null 2>&1
  ./poisson_gs $GRID $ITERATIONS_DEF $TOLERANCE_DEF 0.0 3 >/dev/null 2>&1
done

for TOLERANCE in "${TOLERANCE_VALUES[@]}"; do
  ./poisson_j  $GRID_DEF $ITERATIONS_DEF $TOLERANCE 0.0 4 >>"logs/tolerance_j.log"
  ./poisson_gs $GRID_DEF $ITERATIONS_DEF $TOLERANCE 0.0 4 >>"logs/tolerance_gs.log"
  ./poisson_gs $GRID_DEF $ITERATIONS_DEF $TOLERANCE 0.0 3 >/dev/null 2>&1
  ./poisson_gs $GRID_DEF $ITERATIONS_DEF $TOLERANCE 0.0 3 >/dev/null 2>&1
done

# zip logs
zip -r "logs_$(date +'%Y%m%d_%H%M%S').zip" logs

echo "$(pwd)"
# create output dirs
mkdir -p "ouput/vtk"
mkdir -p "ouput/bin"
mkdir -p "ouput/zip"

# move output files to the output dirs

mv $(fd .zip) "$(pwd)output/zip"
mv $(fd .bin) "$(pwd)/output/bin"
mv $(fd .vtk) "$(pwd)/output/vtk"

# check sequential with bin version!
# UNIQ=$(md5sum *.bin | uniq -c | wc -l)
# ALL=$(ls *.bin | wc -l)
# echo -e "Unique files: ${UNIQ}"
# echo -e "Total files: ${ALL}"
