#!/bin/bash

if [[ $# > 0 ]]; then
	echo "No parameters allowed."
	exit 1
fi

. system.sh
. colors.sh
. prnt.sh
