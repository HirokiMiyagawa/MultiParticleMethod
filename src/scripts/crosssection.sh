#!/bin/sh
#echo off
# 指定のcsvファイルから任意の断面積をプロットする
# arg
# 1 i or j
# 2 section number
# 3 zscalar
# 4 divide_row
# 5 shape (file name)
# 実行ファイルのパスに移動する
PATH_DIR_SCRIPT="$(cd "$(dirname "${BASH_SOURCE:-$0}")" && pwd)"
cd $PATH_DIR_SCRIPT
echo "sript dir: " $PATH_DIR_SCRIPT
cd ../../
ROOT_DIR=$(pwd) # 実行スクリプトの絶対パスを取得する
echo "root dir: " $ROOT_DIR

ChooseParticleAxis=${1:-"i"}
SectionNumber=${2:-21}
zscalar=${3:-1E0}
Shape=${5:-"sail"}
imagePath="visualize/fig/div_${Shape}_deformation.png"
plotScript="${PATH_DIR_SCRIPT}/crosssection_gplot.plt"
dataPathdef="visualize/plot_data/${Shape}_deformation.csv"
dataPathini="visualize/plot_data/${Shape}_deformation.csv"
outputPathdef="visualize/plot_data/div_${Shape}_deformation.csv"
outputPathini="visualize/plot_data/div_${Shape}_initial.csv"
conditionPath="data/csv/condition.csv"
SearchLine="jNum"
xy_min=-0.2
xy_max=1.2
z_min=-0.15
z_max=0.15

echo ${dataPathdef}
row=$(wc -w ${dataPathdef} | awk -F" " '{print $1}')
echo ${row}

if [ -z $4 ]; then
    # divide_row=$(echo "scale=0;sqrt(${row})" | bc -l)
    divide_row=$(grep "${SearchLine}" "${conditionPath}" | awk -F',' '{print $2}')
else
    divide_row=$4
fi
echo $divide_row


cat ${dataPathdef} | awk '{print $0} NR%'${divide_row}'==0 {printf "\n"}' > ${outputPathdef}
cat ${dataPathini} | awk '{print $0} NR%'${divide_row}'==0 {printf "\n"}' > ${outputPathini}

gplot () {
    gnuplot -e "
        call \"${plotScript}\" \"${outputPathdef}\" \"${zscalar}\" \"${divide_row}\" \"${ChooseParticleAxis}\" \"${SectionNumber}\"        
    " > /dev/null
}
choose_gplot (){
    SectionNumber=1
    gplot
    SectionNumber=$divide_row
    gplot
    SectionNumber=$(echo "scale=0;${divide_row}/2+1" | bc -l)
    gplot
}

if [ -z $1 ]; then
    # pltファイルを利用する
    ChooseParticleAxis="i"
    choose_gplot
    ChooseParticleAxis="j"
    choose_gplot
else
    gnuplot -p -e "
        call \"${plotScript}\" \"${outputPathdef}\" \"${zscalar}\" \"${divide_row}\" \"${ChooseParticleAxis}\" \"${SectionNumber}\"        
    " > /dev/null
fi

# プロットしたファイルを開く
explorer.exe `wslpath -aw ${imagePath}` 

ESC=$(printf '\033') # \e や \x1b または $'\e' は使用しない
echo
printf "${ESC}[35m%s${ESC}[m\n" "Plot ${Shape}"
printf "${ESC}[35m%s${ESC}[m\n" "Z scale x ${zscalar}"
echo "---"
