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
#imagePath="visualize/fig/div_${Shape}_deformation.png"
plotScript="${PATH_DIR_SCRIPT}/3dsurface_gplot_for_animation.plt"
conditionPath="data/csv/condition.csv"
SearchLine="jNum"
plotMode=${2:-"gray"}
xy_min=-0.2
xy_max=1.2
z_min=-0.15
z_max=0.15

plotMode="hoge"


if [ -z $3 ]; then
    # divide_row=$(echo "scale=0;sqrt(${row})" | bc -l)
    divide_row=$(grep "${SearchLine}" "${conditionPath}" | awk -F',' '{print $2}')
else
    divide_row=$3
fi
echo $divide_row


# --------------------------------------------------
#  プロット用のファイルが何個あるか確認する
#  ついでにdiv_sail_deformation_i.csvファイルの作成
# --------------------------------------------------
i=0
k=0
while :
do
    cd ./visualize/plot_data/ || exit
    check="sail_deformation_${i}.csv"
    if [ ! -e "$check" ]; then
        i=$((i-1))
        break
    fi
    cd ../../
    outputPathdef="visualize/plot_data/div_${Shape}_deformation_${i}.csv"
    dataPathdef="visualize/plot_data/${Shape}_deformation_${i}.csv"
    #echo ${dataPathdef}
    #row=$(wc -w ${dataPathdef} | awk -F" " '{print $1}')
    #echo ${row}
    cat ${dataPathdef} | awk '{print $0} NR%'${divide_row}'==0 {printf "\n"}' > ${outputPathdef}
    i=$((i+1))
    k=$((k+1))
done
echo "データの数は: ${i}"
echo "3dsurface_plot_for_animationによるプロットを始めます"
cd ../../





# pltファイルを利用する
j=0
k=0
while [ $j -le "$i" ]
do
# gnuplot -p -e "

    #すでにデータ処理しているかの確認
    if [ $j -lt 10 ]; then
        check1=./visualize/div_fig/div_sail_deformation_000${j}.png
        check2=./visualize/fig/div_sail_deformation_000${j}_xy.png
        number="000${j}"
    elif [ $j -lt 100 ]; then
        check1=./visualize/div_fig/div_sail_deformation_00${j}.png
        check2=./visualize/fig/div_sail_deformation_00${j}_xy.png
    elif [ $j -lt 1000 ]; then
        check1=./visualize/div_fig/div_sail_deformation_0${j}.png
        check2=./visualize/fig/div_sail_deformation_0${j}_xy.png
    else
        check1=./visualize/div_fig/div_sail_deformation_${j}.png
        check2=./visualize/fig/div_sail_deformation_${j}_xy.png
    fi
    #check3=div_${Shape}_deformation_${j}_xz.png
    #check4=div_${Shape}_deformation_${j}_yz.png
    #echo "No. ${check1}"
    if [ -e "$check1" ] && [ -e "$check2" ]; then
        j=$((j+1))
        #echo "No. ${j}のファイルは処理済み"
        continue
    fi
   
    gnuplot -p -e "
        call \"${plotScript}\" \"${xy_min}\" \"${xy_max}\" \"${z_min}\" ${z_max} \"div_${Shape}\" \"deformation\" ${zscalar} \"${plotMode}\" ${j}
" > /dev/null
    #echo "${j}回目終わり"

     if [ $j -lt 10 ]; then
        mv ./visualize/div_fig/div_sail_deformation_${j}.png ./visualize/div_fig/div_sail_deformation_000${j}.png
        mv ./visualize/fig/div_sail_deformation_${j}_xy.png ./visualize/fig/div_sail_deformation_000${j}_xy.png
        number="000${j}"
    elif [ $j -lt 100 ]; then
        mv ./visualize/div_fig/div_sail_deformation_${j}.png ./visualize/div_fig/div_sail_deformation_00${j}.png
        mv ./visualize/fig/div_sail_deformation_${j}_xy.png ./visualize/fig/div_sail_deformation_00${j}_xy.png
    elif [ $j -lt 1000 ]; then
        mv ./visualize/div_fig/div_sail_deformation_${j}.png ./visualize/div_fig/div_sail_deformation_0${j}.png
        mv ./visualize/fig/div_sail_deformation_${j}_xy.png ./visualize/fig/div_sail_deformation_0${j}_xy.png
    else
        mv ./visualize/div_fig/div_sail_deformation_${j}.png ./visualize/div_fig/div_sail_deformation_${j}.png
        mv ./visualize/fig/div_sail_deformation_${j}_xy.png ./visualize/fig/div_sail_deformation_${j}_xy.png
    fi

    j=$((j+1))
    k=$((k+1))
    #echo "${number}"
    if [ ${k} -eq 10 ]; then
        echo "${j}個目終了"
        k=0
    fi
done


# プロットしたファイルを開く
#explorer.exe `wslpath -aw ${imagePath}` 

ESC=$(printf '\033') # \e や \x1b または $'\e' は使用しない
echo
printf "${ESC}[35m%s${ESC}[m\n" "Plot ${Shape}"
printf "${ESC}[35m%s${ESC}[m\n" "Z scale x ${zscalar}"
echo "---"
