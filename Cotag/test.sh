#!/bin/bash

for ((i=1;i<=15;i++))
do
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done



