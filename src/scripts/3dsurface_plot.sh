#!/bin/sh
#echo off
# arg
# 1 zscalar
# 2 mode
# 3 divide_row
# 4 shape (file name)

# 実行ファイルのパスに移動する
PATH_DIR_SCRIPT="$(cd "$(dirname "${BASH_SOURCE:-$0}")" && pwd)"
cd $PATH_DIR_SCRIPT
cd ../../

zscalar=${1:-1E0}   
Shape=${4:-"sail"}
imagePath="visualize/fig/div_${Shape}_deformation.png"
plotScript="${PATH_DIR_SCRIPT}/3dsurface_gplot.plt"
dataPathdef="visualize/plot_data/${Shape}_deformation.csv"
dataPathini="visualize/plot_data/${Shape}_initial.csv"
outputPathdef="visualize/plot_data/div_${Shape}_deformation.csv"
outputPathini="visualize/plot_data/div_${Shape}_initial.csv"
conditionPath="data/csv/condition.csv"
SearchLine="jNum"
plotMode=${2:-"gray"}
xy_min=-0.2
xy_max=1.5
z_min=-0.15
z_max=0.15

plotMode="hoge"

echo ${dataPathdef}
row=$(wc -w ${dataPathdef} | awk -F" " '{print $1}')
echo ${row}

if [ -z $3 ]; then
    # divide_row=$(echo "scale=0;sqrt(${row})" | bc -l)
    divide_row=$(grep "${SearchLine}" "${conditionPath}" | awk -F',' '{print $2}')
else
    divide_row=$3
fi
echo $divide_row


cat ${dataPathini} | awk '{print $0} NR%'${divide_row}'==0 {printf "\n"}' > ${outputPathini}
cat ${dataPathdef} | awk '{print $0} NR%'${divide_row}'==0 {printf "\n"}' > ${outputPathdef}

# pltファイルを利用する
gnuplot -e "
    call \"${plotScript}\" \"${xy_min}\" \"${xy_max}\" \"${z_min}\" ${z_max} \"div_${Shape}\" \"initial\" ${zscalar} \"${plotMode}\"
" > /dev/null

gnuplot -p -e "
    call \"${plotScript}\" \"${xy_min}\" \"${xy_max}\" \"${z_min}\" ${z_max} \"div_${Shape}\" \"deformation\" ${zscalar} \"${plotMode}\"
" > /dev/null

# プロットしたファイルを開く
explorer.exe `wslpath -aw ${imagePath}` 

ESC=$(printf '\033') # \e や \x1b または $'\e' は使用しない
echo
printf "${ESC}[35m%s${ESC}[m\n" "Plot ${Shape}"
printf "${ESC}[35m%s${ESC}[m\n" "Z scale x ${zscalar}"
echo "---"
