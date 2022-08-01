#!/bin/sh
#echo off
# arg
# 1 zscalar
# 2 divide_row
# 3 shape (file name)

# 実行ファイルのパスに移動する
PATH_DIR_SCRIPT="$(cd "$(dirname "${BASH_SOURCE:-$0}")" && pwd)"
cd $PATH_DIR_SCRIPT
cd ../../

zscalar=${1:-1E0}   
Shape=${3:-"sail"}
imagePath="visualize/fig/${Shape}_deformation.png"
plotScript="${PATH_DIR_SCRIPT}/dgrid_gplot.plt"
dataPathdef="visualize/plot_data/${Shape}_deformation.csv"
dataPathini="visualize/plot_data/${Shape}_deformation.csv"
outputPathdef="visualize/plot_data/${Shape}_deformation.csv"
outputPathini="visualize/plot_data/${Shape}_initial.csv"

echo ${dataPathdef}
row=$(wc -w ${dataPathdef} | awk -F" " '{print $1}')
echo ${row}

if [ -z $2 ]; then
    divide_row=$(echo "scale=0;sqrt(${row})" | bc -l)
else
    divide_row=$2
fi
echo $divide_row


# cat ${dataPathdef} | awk '{print $0} NR%'${divide_row}'==0 {printf "\n"}' > ${outputPathdef}
# cat ${dataPathini} | awk '{print $0} NR%'${divide_row}'==0 {printf "\n"}' > ${outputPathini}

# pltファイルを利用する
gnuplot -e "
    call \"${plotScript}\" \"-0.2\" 1.2 \"-0.1\" 0.1 \"${Shape}\" \"initial\" ${zscalar}
" > /dev/null

# gnuplot -p -e "
gnuplot -e "
    call \"${plotScript}\" \"-0.2\" 1.2 \"-0.1\" 0.1 \"${Shape}\" \"deformation\" ${zscalar}
" > /dev/null

# プロットしたファイルを開く
explorer.exe `wslpath -aw ${imagePath}` 

ESC=$(printf '\033') # \e や \x1b または $'\e' は使用しない
echo
printf "${ESC}[35m%s${ESC}[m\n" "Plot ${Shape}"
printf "${ESC}[35m%s${ESC}[m\n" "Z scale x ${zscalar}"
echo "---"
