#!/bin/bash

end="\e[m"
printf "${bg1}${fg1}HOSTNAME${end} = ${bg2}${fg2}%s${end}\n" "$hostname"
printf "${bg1}${fg1}TIMEZONE${end} = ${bg2}${fg2}%s${end}\n" "$timezone"
printf "${bg1}${fg1}USER${end} = ${bg2}${fg2}%s${end}\n" "$user"
printf "${bg1}${fg1}OS${end} = ${bg2}${fg2}%s${end}\n" "$os"
printf "${bg1}${fg1}DATE${end} = ${bg2}${fg2}%s${end}\n" "$Date"
printf "${bg1}${fg1}UPTIME${end} = ${bg2}${fg2}%s${end}\n" "$up"
printf "${bg1}${fg1}UPTIME_SEC${end} = ${bg2}${fg2}%s${end}\n" "$up_sec"
printf "${bg1}${fg1}IP${end} = ${bg2}${fg2}%s${end}\n" "$ip_"
printf "${bg1}${fg1}MASK${end} = ${bg2}${fg2}%s${end}\n" "$mask"
printf "${bg1}${fg1}GATEWAY${end} = ${bg2}${fg2}%s${end}\n" "$gateway"
printf "${bg1}${fg1}RAM_TOTAL${end} = ${bg2}${fg2}%s${end}\n" "$ram_total"
printf "${bg1}${fg1}RAM_USED${end} = ${bg2}${fg2}%s${end}\n" "$ram_used"
printf "${bg1}${fg1}RAM_FREE${end} = ${bg2}${fg2}%s${end}\n" "$ram_free"
printf "${bg1}${fg1}SPACE_ROOT${end} = ${bg2}${fg2}%s${end}\n" "$space_root"
printf "${bg1}${fg1}SPACE_ROOT_USED${end} = ${bg2}${fg2}%s${end}\n" "$space_root_used"
printf "${bg1}${fg1}SPACE_ROOT_FREE${end} = ${bg2}${fg2}%s${end}\n" "$space_root_free"

if [[ $flag_def == 1 ]]; then
	printf "\nColumn 1 background = default ($(set_name "$color_bg1"))"
	printf "Column 1 font color = default ($(set_name "$color_fg1"))\n"
	printf "Column 2 background = default ($(set_name "$color_bg2"))\n"
	printf "Column 2 font color = default ($(set_name "$color_fg2"))\n"
else
	printf "\nColumn 1 background = $color_bg1 ($(set_name "$color_bg1"))\n"
	printf "Column 1 font color = $color_fg1 ($(set_name "$color_fg1"))\n"
	printf "Column 2 background = $color_bg2 ($(set_name "$color_bg2"))\n"
	printf "Column 2 font color = $color_fg2 ($(set_name "$color_fg2"))\n"
fi
