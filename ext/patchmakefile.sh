#!/bin/bash

# Switch the default compiler (ifort) in the CAMB Makefile to gfortran

makefile=camb/Makefile

sed -i~ -e 's/\(F90C.*ifort.*\)/#\1/'       \
    -e 's/\(FFLAGS.*-openmp.*\)/#\1/'       \
    -e 's/#\(.*F90C.*gfortran.*\)/\1/'      \
    -e 's/#\(.*FFLAGS.*-fopenmp*\)/\1/'     \
    $makefile
