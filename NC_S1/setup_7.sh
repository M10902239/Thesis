#!/bin/bash

for ((i=1;i<=24;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=95" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=24;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=100" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=24;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=105" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

