#!/bin/bash

begin=$(date +%s)

if [[ $# > 1 ]]; then
	echo "Too many parameters found. Needed 1."
	exit 1
fi

if [[ $# < 1 ]]; then
	echo "Not enough parameters found. Needed 1."
	exit 1
fi

if [[ ! $1 =~ .*\/$ ]]; then
	echo "The path should end with '/'."
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "Wrong parameter. $1 directory doesn't exist."
	exit 1
fi

. info.sh
. prnt.sh

end=$(date +%s)
printf "Script execution time (in seconds) = $(($end - $begin))\n"
