#!/bin/bash

# aditional data processing commands here.

gnuplot << EOP

set terminal jpeg size 640,480
set output "spectr.jpg"

plot "spectr.txt"  with lines

EOP
