#!/bin/bash
cd ../../
source setup.sh
cd -
export PLOTTER_WORKING_DIR=`pwd`
export FILE_PATH=$PLOTTER_WORKING_DIR/rootfiles/
export PLOT_PATH=/home/jskim/Dropbox/MuonHLT/
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$PLOTTER_WORKING_DIR/include/:$PLOTTER_WORKING_DIR/src/:$KP_INCLUDE_PATH:../
