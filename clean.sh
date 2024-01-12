#!/bin/bash

# go to src directory
cd src
# zip the logs
zip -r "logs_$(date +'%Y%m%d_%H%M%S').zip" "output/logs"
zip -r "bsub_$(date +'%Y%m%d_%H%M%S').zip" "output/bsub"
zip -r "bin_$(date +'%Y%m%d_%H%M%S').zip" "output/bin"
zip -r "vtk_$(date +'%Y%m%d_%H%M%S').zip" "output/vtk"

# create output dirs
mkdir -p "output/logs"
mkdir -p "output/bsub"
mkdir -p "output/vtk"
mkdir -p "output/bin"
mkdir -p "output/zip"

# move files
mv *.zip "output/zip"
mv *.bin "output/bin"
mv *.vtk "output/vtk"
