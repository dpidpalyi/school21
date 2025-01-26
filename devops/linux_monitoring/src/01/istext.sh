#!/bin/bash

if [[ $1 =~ ^[+-]?[0-9]+([.][0-9]+)?$ ]]; then
	echo "Invalid input. Text is needed."
else
	echo $1
fi
