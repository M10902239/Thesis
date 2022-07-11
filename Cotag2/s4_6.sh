#!/bin/bash

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=80" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=85" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=90" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=95" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=100" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=105" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=110" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=115" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=120" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=125" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=130" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=135" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=140" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=145" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done

for ((i=1;i<=1;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=150" ./waf --run scratch/S4
	g++ fix_parameter_S4.cpp -o fix_parameter_S4.out -Wall
	./fix_parameter_S4.out
done







