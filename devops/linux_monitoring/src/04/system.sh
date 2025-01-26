#!/bin/bash

hostname=$HOSTNAME
timezone="$(timedatectl | grep 'Time zone: ' | sed -e 's/,//' -e 's/0//' -e 's/(//' | awk '{printf "%s UTC %s", $3, $4}')"
user=$(whoami)
os=$(cat /etc/issue | sed -e 's/ \\n \\l//')
Date=$(date '+%d %B %Y %H:%M:%S')
up=$(uptime -p | sed -e 's/up //')
up_sec=$(awk '{printf "%d", $1}' /proc/uptime)
ip_=$(ip -f inet addr show | awk -v ORS=" " '/inet/ {print $2}')
#ip_=$(hostname --all-ip-addresses)
mask=$(ifconfig | awk -v ORS=" " '/netmask/ {print $2, $4}')
gateway=$(ip r | awk '/default/ {print $3}')
ram_total=$(free -m | awk '/Mem:/ {printf "%.3f GB", $2/1024}')
ram_used=$(free -m | awk '/Mem:/ {printf "%.3f GB", $3/1024}')
ram_free=$(free -m | awk '/Mem:/ {printf "%.3f GB", $4/1024}')
space_root=$(df | awk '/\/$/ {printf "%.2f MB", $2/1024}')
space_root=$(df | awk '/\/$/ {printf "%.2f MB", $2/1024}')
space_root_used=$(df | awk '/\/$/ {printf "%.2f MB", $3/1024}')
space_root_free=$(df | awk '/\/$/ {printf "%.2f MB", $4/1024}')
