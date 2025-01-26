#!/bin/bash

if [[ $# > 4 ]]; then
	echo "Too many parameters found. Needed 4."
	exit 1
fi

if [[ $# < 4 ]]; then
	echo "Not enough parameters found. Needed 4."
	exit 1
fi

for arg in "$@"; do
	if [[ ! $arg =~ ^[1-6]$ ]]; then
		echo "$arg is invalid parameter"
		exit 1
	fi
done

if [[ $1 == $2 || $3 == $4 ]]; then
	echo "Wrong colors. Choose different colors for background and foreground."
	exit 1
fi

. system.sh
. colors.sh
. prnt.sh
