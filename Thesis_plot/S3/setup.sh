#!/bin/bash

python3 1_thr.py NC_15ms 7
python3 1_thr.py NC_15ms 11
python3 1_thr.py NC_15ms 15
python3 1_thr.py NC_15ms 19
python3 1_thr.py NC_15ms 23

python3 1_thr.py PD_15ms 7
python3 1_thr.py PD_15ms 11
python3 1_thr.py PD_15ms 15
python3 1_thr.py PD_15ms 19
python3 1_thr.py PD_15ms 23

python3 2_thr_settle.py NC_15ms 7
python3 2_thr_settle.py NC_15ms 11
python3 2_thr_settle.py NC_15ms 15
python3 2_thr_settle.py NC_15ms 19
python3 2_thr_settle.py NC_15ms 23

python3 2_thr_settle.py PD_15ms 7
python3 2_thr_settle.py PD_15ms 11
python3 2_thr_settle.py PD_15ms 15
python3 2_thr_settle.py PD_15ms 19
python3 2_thr_settle.py PD_15ms 23

python3 3_packet_latency.py NC_15ms 7
python3 3_packet_latency.py NC_15ms 11
python3 3_packet_latency.py NC_15ms 15
python3 3_packet_latency.py NC_15ms 19
python3 3_packet_latency.py NC_15ms 23

python3 3_packet_latency.py PD_15ms 7
python3 3_packet_latency.py PD_15ms 11
python3 3_packet_latency.py PD_15ms 15
python3 3_packet_latency.py PD_15ms 19
python3 3_packet_latency.py PD_15ms 23

python3 1_thr_8.py NC_15ms 7
python3 1_thr_8.py NC_15ms 11
python3 1_thr_8.py NC_15ms 15
python3 1_thr_8.py NC_15ms 19
python3 1_thr_8.py NC_15ms 23

python3 1_thr_8.py PD_15ms 7
python3 1_thr_8.py PD_15ms 11
python3 1_thr_8.py PD_15ms 15
python3 1_thr_8.py PD_15ms 19
python3 1_thr_8.py PD_15ms 23

python3 2_thr_settle_8.py NC_15ms 7
python3 2_thr_settle_8.py NC_15ms 11
python3 2_thr_settle_8.py NC_15ms 15
python3 2_thr_settle_8.py NC_15ms 19
python3 2_thr_settle_8.py NC_15ms 23

python3 2_thr_settle_8.py PD_15ms 7
python3 2_thr_settle_8.py PD_15ms 11
python3 2_thr_settle_8.py PD_15ms 15
python3 2_thr_settle_8.py PD_15ms 19
python3 2_thr_settle_8.py PD_15ms 23

python3 3_packet_latency_8.py NC_15ms 7
python3 3_packet_latency_8.py NC_15ms 11
python3 3_packet_latency_8.py NC_15ms 15
python3 3_packet_latency_8.py NC_15ms 19
python3 3_packet_latency_8.py NC_15ms 23

python3 3_packet_latency_8.py PD_15ms 7
python3 3_packet_latency_8.py PD_15ms 11
python3 3_packet_latency_8.py PD_15ms 15
python3 3_packet_latency_8.py PD_15ms 19
python3 3_packet_latency_8.py PD_15ms 23


