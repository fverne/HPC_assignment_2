#!/bin/sh
### General options
### -- set the job Name --
#BSUB -J OpenMPjob
### -- ask for number of cores (default: 1) --
#BSUB -n 32
### -- specify that the cores MUST BE on a single host! It's a SMP job! --
#BSUB -R "span[hosts=1]"
### -- set walltime limit: hh:mm --
#BSUB -W 16:00 
### -- specify CPU model
##BSUB -R "select[model == XeonE5_2660v4]"
### -- specify that we need 4GB of memory per core/slot -- 
#BSUB -R "rusage[mem=4GB]"
### -- set the email address --
# please uncomment the following line and put in your e-mail address,
# if you want to receive e-mail notifications on a non-default address
#BSUB -u s232242@dtu.dk
### -- send notification at start --
#BSUB -B
### -- send notification at completion--
#BSUB -N
### -- Specify the output and error file. %J is the job-id -- 
### -- -o and -e mean append, -oo and -eo mean overwrite -- 
#BSUB -o ./data_%J/Output.out
#BSUB -e ./data_%J/Output.err 

# set OMP_NUM_THREADS _and_ export! 
# OMP_NUM_THREADS=$LSB_DJOB_NUMPROC 
# export OMP_NUM_THREADS 
# ------------------------------- Program_name_and_options 

THRED_NUMS="1 2 4 8 16 32" 
BINARY="./src/poisson_jomp"
GRID_SIZE=20
MAX_ITERATIONS=10000
TOLERANCE=0.00001
GRID_DEF=5

# list CPU info
lscpu
mkdir -p "data_${LSB_JOBID}"

RAW="data_${LSB_JOBID}/raw.log"
> ${RAW}

for THRED_NUM in $THRED_NUMS
do 
    export OMP_NUM_THREADS=$THRED_NUM 
    echo "OMP_NUM_THREADS=$OMP_NUM_THREADS" 
    ${BINARY} ${GRID_SIZE} ${MAX_ITERATIONS} ${TOLERANCE} 0 >> ${RAW}
done

# extract data
TIME="data_${LSB_JOBID}/time.dat"
> ${TIME}
while read line; do
    if [[ " $line " =~ "Number of threads:" ]] 
        then
            value=${line##*N:}
            value=$(echo "$value" | awk '{print $1}')
            echo "$value" >> "${TIME}"
            echo -e "\t" >> "${TIME}"
    elif [[ " $line " =~ "Time:" ]] 
        then
            value=${line##*Time:}
            value=$(echo "$value" | awk '{print $1}')
            echo "$value" >> "${TIME}"
            echo -e "\n" >> "${TIME}"
    fi
done <${RAW}


