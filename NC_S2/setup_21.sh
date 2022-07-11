#!/bin/bash

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=5" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=10" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=15" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=20" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=25" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=30" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=35" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=40" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=45" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=50" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=55" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=60" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=65" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=70" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=75" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=80" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=85" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=90" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=95" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=100" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=105" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=110" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=115" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=120" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=125" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=130" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=135" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=140" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=145" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done

for ((i=1;i<=21;i++))
do
	./waf clean
	./waf configure --disable-examples --disable-tests --disable-python --enable-modules='core','applications','wifi','spectrum','flow-monitor','point-to-point','buildings','srnc' --enable-static -d optimized
	NS_GLOBAL_VALUE="RngRun=150" ./waf --run scratch/scenario_1_delay
	g++ fix_parameter.cpp -o fix_parameter.out -Wall
	./fix_parameter.out
done




