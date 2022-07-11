#!/bin/bash

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=10" ./waf --run scratch/scenario_1_delay_single
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done


for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=15" ./waf --run scratch/scenario_1_delay_single
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done


for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=20" ./waf --run scratch/scenario_1_delay_single
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

