#!/bin/bash

awk -F, '{printf "%f %d^%d line: %d\n",$2*log($1), $1, $2, NR}' < p099_base_exp.txt | sort | tail -n1
