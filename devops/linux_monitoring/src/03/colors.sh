#!/bin/bash

function set_color() {
	case $1 in
		"1") echo 7 ;; #white
		"2") echo 1 ;; #red
		"3") echo 2 ;; #green
		"4") echo 4 ;; #blue
		"5") echo 5 ;; #purple
		"6") echo 0 ;; #black
	esac
}

bg1="\e[4$(set_color "$1")m"
fg1="\e[3$(set_color "$2")m"
bg2="\e[4$(set_color "$3")m"
fg2="\e[3$(set_color "$4")m"
