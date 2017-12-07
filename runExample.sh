#!/bin/sh

runFile="./bin/WordStatistics"

if [ ! -f "$runFile" ]; then
  make
  $runFile ./example/Cabbages_and_Kings.txt
  if [ -f "output.json" ]; then
    rm output.json
    make clean
  fi
else
  $runFile ./example/Cabbages_and_Kings.txt
  if [ -f "output.json" ]; then
    rm output.json
  fi
fi