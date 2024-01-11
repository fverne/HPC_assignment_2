#!/bin/bash

# go to source dir
cd "src"
# create output/data dir if doesn't exist
mkdir -p "data"
# remove previous data
rm -f data/*.dat

LOGFILE_J="logs/grid_j.log"
LOGFILE_GS="logs/grid_gs.log"

while read line; do
    if [[ " $line " =~ "N:" ]] 
        then
            value=${line##*N:}
            echo -n "$value" >> "data/grid_j.dat"
    elif [[ " $line " =~ "Time:" ]] 
        then
            value=${line##*Time:}
            echo "$value" >> "data/grid_j.dat"
    fi
done <$LOGFILE_J

while read line; do
    if [[ " $line " =~ "N:" ]] 
        then
            value=${line##*N:}
            echo -n "$value" >> "data/grid_gs.dat"
    elif [[ " $line " =~ "Time:" ]] 
        then
            value=${line##*Time:}
            echo "$value" >> "data/grid_gs.dat"
    fi
done <$LOGFILE_GS