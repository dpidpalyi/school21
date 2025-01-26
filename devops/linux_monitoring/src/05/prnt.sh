#!/bin/bash

printf "Total number of folders (including all nested ones) = $total_folders\n"
printf "TOP 5 folders of maximus size arranged in descending order (path and size)\n"
printf "$top_folders\n"
printf "Total number of files = $total_files\n"
printf "Number of:\n"
printf "Configuration files (with the .conf extension) = $conf_files\n"
printf "Text files = $text_files\n"
printf "Executable files = $exec_files\n"
printf "Log files (with the extension .log) = $log_files\n"
printf "Archive files = $arch_files\n"
printf "Symbolic links = $link_files\n"
printf "TOP 10 files of maximum size arranged in descending order (path, size and type):\n"
printf "$top_files\n"
printf "TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file)\n"
top_exec_files $1
