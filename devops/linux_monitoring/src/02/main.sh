#!/bin/bash

if [[ $# > 0 ]]; then
	echo "No parameters needed."
	exit 1
fi

. system.sh
. prnt.sh

read -p 'Write the data to a file? (Y/N) ' user_input
if [[ $user_input == Y || $user_input == y ]]; then
	. prnt.sh > "$(date +"%d_%m_%y_%H_%M_%S").status"
fi
