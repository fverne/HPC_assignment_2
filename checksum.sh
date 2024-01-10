#!/bin/bash


# How to use:
# Give the two files as arguments, and it will output if they are the same
cmp --silent $1 $2 && echo "files are the same" || echo "files are different"