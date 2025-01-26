#!/bin/bash

if [[ $# == 0 ]]; then
	echo "No parameters found."
	exit 1
fi

if [[ $# > 1 ]]; then
	echo "Too many parameters found."else 
	exit 1
fi

. istext.sh
