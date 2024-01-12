#!/bin/bash
#BSUB -J 4cores
#BSUB -o src/output/1node4cores.out
#BSUB -q hpcintro
#BSUB -W 30
#BSUB -R "rusage[mem=512MB]"
#BSUB -R "span[hosts=1]"
#BSUB -n 24

THREAD_NUMS="2 4 8 12 16 20 24"
COMPILER_OPTIONS=(
    # "-O0"
    # "-O3 -funroll-loops"
    "-Ofast -funroll-loops"
)

BINARY="./src/poisson_jomp"
GRID_SIZE=100
MAX_ITERATIONS=10000
TOLERANCE=0.0001

# list CPU info
lscpu
dir="data_${LSB_JOBNAME}_${LSB_JOBID}"
mkdir -p ${dir}

RAW="${dir}/raw.log"
>${RAW}

for OPTION in "${COMPILER_OPTIONS[@]}"; do
    cd src
    echo -e "Option: $OPTION"
    module load gcc
    make OPT=" -g $OPTION -fopenmp" -B
    cd ..
    for THREAD_NUM in $THREAD_NUMS; do
        export OMP_NUM_THREADS=$THREAD_NUM
        echo "OMP_NUM_THREADS=$OMP_NUM_THREADS"
        ${BINARY} ${GRID_SIZE} ${MAX_ITERATIONS} ${TOLERANCE} 0 >>${RAW}_"${OPTION}"
    done

done

# extract data
TIME="${dir}/time.dat"

python3 extractdata.py ${RAW} "Number of threads" "Number of iterations per second" >${TIME}