#!/bin/bash

echo "Executed at: $(date '+%Y-%m-%d %H:%M:%S')"
echo "Hostname : $(hostname)"
echo "Number of users: $(who | wc -l)"

echo "CPU: $(ps -A -o %cpu | awk '{s+=$1} END {printf "%.1f", s}')% usage"


vm_stat | awk '
/page size of/ {pagesize=$8}
/Pages active/ {active=$3}
/Pages wired down/ {wired=$4}
/Pages free/ {free=$3}
END {
  total=active+wired+free;
  used=active+wired;
  printf "Used: %.2f MB\nTotal: %.2f MB\n", used*4096/1048576, total*4096/1048576
}'

df -H | awk '$1 ~ /^\/dev\// {printf "%-20s %-10s %-s\n", $1, $4, $6}'
# $1 name of the disk
# $4 Free space
# $6 Where the disk is mounted

echo -e "\ntop 5 most CPU-consuming processes"
ps -Arcwwwxo pid,comm,%cpu | head -6
# pid process id
# comm command name
#%cpu cpu usage in percentage
# --sort =-%cpu sorts from the highest to the lowest cpu percentage


echo -e "\ntop 5 most RAM-consuming processes"
ps -Arcwwwxo pid,comm,%mem | head -6
#%mem memory usage in percentage

