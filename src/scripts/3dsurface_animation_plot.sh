#!/bin/bash
#echo off
# arg
# 1 zscalar
# 2 j_max
# 3 shape (file name)

# 実行ファイルのパスに移動する
PATH_DIR_SCRIPT="$(cd "$(dirname "${BASH_SOURCE:-$0}")" && pwd)"
cd $PATH_DIR_SCRIPT
cd ../../

zscalar=${1:-1E0}
Shape=${4:-"sail"}
imagePath="visualize/fig/div_${Shape}_deformation.png"
plotScript="${PATH_DIR_SCRIPT}/3dsurface_gplot.plt"
outputPath="visualize/plot_data/time.csv"
conditionPath="data/csv/condition.csv"
SearchLine_i="iNum"
SearchLine_j="jNum"
eachfilePath="visualize/plot_data/each_time"
read_file_c="c_"
read_file_v="v_"
xy_min=-0.2
xy_max=1.2
z_min=-0.15
z_max=0.15

:>| "${outputPath}"

# カンマ区切り
FS=","

if [ -z $3 ]; then
    # j_max=$(echo "scale=0;sqrt(${row})" | bc -l)
    i_max=$(grep "${SearchLine_i}" "${conditionPath}" | awk -F',' '{print $2}')
    j_max=$(grep "${SearchLine_j}" "${conditionPath}" | awk -F',' '{print $2}')
else
    j_max=$2
fi
# j_max_harf=$(echo "scale=0;${j_max} / 2" | bc -l)
j_max_harf=$(( ${j_max} / 2 ))


# list_c=( $(find ${eachfilePath} -type f \( -name "*.csv" -and -name "${read_file_c}*" \) | sort -n -k 2,2 -t "_" | awk -F"/" '{print $4}') )
list_c=( $(find ${eachfilePath} -type f \( -name "*.csv" -and -name "${read_file_c}*" \) | sort -n -k 2,2 -t "_") )
echo "${#list_c[*]}"

function merge_each_time(){
    column=${1:-1}
    read_file=$2
    start_line=$(echo "scale=0;${j_max}*(${i_max}-1)+${j_max_harf}+1" | bc -l)
    # echo "1 ${start_line}"
    # start_line=$(( ${j_max}*(${i_max}-1)+${j_max_harf}+1 ))
    # echo "2 ${start_line}"
    cut -f "$column" --delim="${FS}" ${read_file} | sed -n "${start_line}p" | sed -e "s/[\r\n]\+//g" | tr "\n" " " >> "${outputPath}"
}

for i in ${list_c[@]}
do
    # ${call_scriptDir} ${i}
    echo ${i}
    file_v=$(echo ${i} | sed s/${read_file_c}/${read_file_v}/)
    echo ${file_v}

    echo -n ${i} | awk -F"/" '{print $4}' | sed "s/.csv//" | sed "s/${read_file_c}//"| tr "\n" "," >> "${outputPath}"
    # echo -n "," >> "${outputPath}"
    merge_each_time 1 ${i}
    echo -n "," >> "${outputPath}"
    merge_each_time 1 ${file_v}
    echo "$LF" >> "${outputPath}"
done



# pltファイルを利用する
# gnuplot -e "
gnuplot -p -e "
    call \"${plotScript}\" ${xy_min} ${xy_max} ${z_min} ${z_max} \"div_${Shape}\" \"deformation\" ${zscalar}
" > /dev/null

# # プロットしたファイルを開く
# explorer.exe `wslpath -aw ${imagePath}` 

# ESC=$(printf '\033') # \e や \x1b または $'\e' は使用しない
# echo
# printf "${ESC}[35m%s${ESC}[m\n" "Plot ${Shape}"
# printf "${ESC}[35m%s${ESC}[m\n" "Z scale x ${zscalar}"
# echo "---"
