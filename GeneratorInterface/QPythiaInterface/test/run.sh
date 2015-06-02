#!/bin/sh

for run in `seq $1 $2`
do
  mkdir $run
  cp tmp/* $run
  cd $run
  cmsRun testQPythiaDijet.py >& log &
  cd ..
  sleep 5  
done
        