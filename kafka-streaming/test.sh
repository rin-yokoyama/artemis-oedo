#!/bin/bash
pids=[]
stream_artemis steering/chksrppac_kafka.yaml calib 10290 & pids[0]=$!
stream_artemis steering/chksrppac_kafka.yaml calib 10291 & pids[1]=$!
stream_artemis steering/chksrppac_kafka.yaml calib 10292 & pids[2]=$!
stream_artemis steering/chksrppac_kafka.yaml calib 10293 & pids[3]=$!
stream_artemis steering/chksrppac_kafka.yaml calib 10294 & pids[4]=$!
stream_artemis steering/chksrppac_kafka.yaml calib 10295 & pids[5]=$!
stream_artemis steering/chksrppac_kafka.yaml calib 10296 & pids[6]=$!
stream_artemis steering/chksrppac_kafka.yaml calib 10297 & pids[7]=$!
stream_artemis steering/chksrppac_kafka.yaml calib 10298 & pids[8]=$!
stream_artemis steering/chksrppac_kafka.yaml calib 10299 & pids[9]=$!

sleep 10

ridfFile2Stream ridf/calib1029.ridf shfs02:9092 10000

for pid in ${pids[*]}; do
    wait $pid
done