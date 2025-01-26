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

function set_name() {
	case $1 in
		"1") echo "white" ;;
		"2") echo "red" ;;
		"3") echo "green" ;;
		"4") echo "blue" ;;
		"5") echo "purple" ;;
		"6") echo "black" ;;
	esac
}

default_color_bg1="1"
default_color_fg1="2"
default_color_bg2="3"
default_color_fg2="4"

conf_file="color.cfg"
if [[ -f "$conf_file" ]]; then
	while IFS='=' read -r var val; do
		if [[ ! -z "$var" && ! -z "$val" ]]; then
			case $var in
				"column1_background") color_bg1="$val" ;;
				"column1_font_color") color_fg1="$val" ;;
				"column2_background") color_bg2="$val" ;;
				"column2_font_color") color_fg2="$val" ;;
			esac
		fi
	done < $conf_file
fi

flag_default=0

if [[ -z "$color_bg1" ]] || [[ -z "$color_fg1" ]] || [[ -z "$color_bg2" ]] || [[ -z "$color_fg2" ]]; then
	color_bg1=$default_color_bg1
	color_fg1=$default_color_fg1
	color_bg2=$default_color_bg2
	color_fg2=$default_color_fg2
	flag_default=1
fi

bg1="\e[4$(set_color $color_bg1)m"
fg1="\e[3$(set_color $color_fg1)m"
bg2="\e[4$(set_color $color_bg2)m"
fg2="\e[3$(set_color $color_fg2)m"
