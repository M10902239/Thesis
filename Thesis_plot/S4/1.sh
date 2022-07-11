#!/bin/bash

python3 1_thr.py NC_15ms 6
python3 1_thr.py PD_15ms 6
python3 1_thr.py PD 6
python3 1_thr_cotag.py Cotag 6
cd ./plot
python b-thr.py
python b-latency.py
