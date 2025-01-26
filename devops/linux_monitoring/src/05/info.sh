#!/bin/bash

total_folders="$(find $1 -type d | wc -l)"
top_folders="$(du -Sh $1 | sort -rh | head -5 | cat -n | awk '{printf "%s - %s, %s\n", $1, $3, $2}')"
total_files="$(find $1 -type f | wc -l)"
conf_files="$(find $1 -type f -name "*.conf" | wc -l)"
text_files="$(find $1 -type f -name "*.txt" | wc -l)"
exec_files="$(find $1 -type f -executable | wc -l)"
log_files="$(find $1 -type f -name "*.log" | wc -l)"
arch_files="$(find $1 -regex '.*\(tar\|zip\|gz\|rar\)' | wc -l)"
link_files="$(find $1 -type l | wc -l)"
top_files="$(find $1 -type f -exec du -h {} + | sort -rh | head -10 | cat -n | awk '{printf "%s - %s, %s\n", $1, $3, $2}')"
function top_exec_files() {
  find "$1" -type f -executable | while read -r file; do
    size=$(du -h "$file" | awk '{print $1}')
    md5=$(md5sum "$file" | awk '{print $1}')
    echo "$file, $size, $md5"
  done | sort -hrk 2 | head -10 | awk '{print NR " - " $1 " " $2 " " $3}'
}
