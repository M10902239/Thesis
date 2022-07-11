#!/bin/bash

for ((i=1;i<=8;i++))
do
	g++ fix_parameter_S3.cpp -o fix_parameter_S3.out -Wall
	./fix_parameter_S3.out
done



