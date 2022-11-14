#!/bin/sh
#echo off

# 実行ファイルのパスに移動する
PATH_DIR_SCRIPT="$(cd "$(dirname "${BASH_SOURCE:-$0}")" && pwd)" # 実行ファイルのディレクトリを取得する 
cd $PATH_DIR_SCRIPT
cd ../../

zscalar=${1:-1E0}   
Shape=${3:-"sail"}
#imagePath="visualize/fig/${Shape}_deformation.png"
#gnuplotのコードがある場所
plotScript="${PATH_DIR_SCRIPT}/scatter_gplot_for_animation.plt"
xy_min=-0.2
xy_max=1.2
z_min=-0.15
z_max=0.15


# --------------------------------------------------
#  プロット用のファイルが何個あるか確認する
# --------------------------------------------------
cd ./visualize/plot_data/ || exit
i=0
while :
do
    check="sail_deformation_${i}.csv"
    if [ ! -e "$check" ]; then
        i=$((i-1))
        break
    fi
    i=$((i+1))
done
echo "データの数は: ${i}"
echo "scatter_plot_for_animation.shによるプロットを始めます"
cd ../../



# pltファイルを利用する
# gnuplot -e "
# call \"${plotScript}\" \"${xy_min}\" \"${xy_max}\" \"${z_min}\" ${z_max} \"${Shape}\" \"initial\" ${zscalar}
# " > /dev/null
j=0
k=0
while [ $j -le "$i" ]
do
# gnuplot -p -e "

    #すでにデータ処理しているかの確認
    cd ./visualize/fig/ || exit
    check1=${Shape}_deformation_${j}.png
    check2=${Shape}_deformation_${j}_xy.png
    check3=${Shape}_deformation_${j}_xz.png
    check4=${Shape}_deformation_${j}_yz.png
    if [ -e "$check1" ] && [ -e "$check2" ] && [ -e "$check3" ] && [ -e "$check4" ]; then
        j=$((j+1))
        echo "No. ${j}のファイルは処理済み"
        cd ../../
        continue
    fi
    cd ../../ || exit

    gnuplot -p -e "
        call \"${plotScript}\" \"${xy_min}\" \"${xy_max}\" \"${z_min}\" ${z_max} \"${Shape}\" \"deformation\" \"${zscalar}\" ${j}
" > /dev/null
    #echo "${j}回目終わり"
    j=$((j+1))
    k=$((k+1))
    if [ ${k} -eq 10 ]; then
        echo "${j}個目終了"
        k=0
    fi
done
#確認テスト用の表示
#echo "データの数は： ${j}"
#echo "jがiよりも1大きければ正解"

# プロットしたファイルを開く
# explorer.exe `wslpath -aw ${imagePath}` 

ESC=$(printf '\033') # \e や \x1b または $'\e' は使用しない
echo
printf "${ESC}[35m%s${ESC}[m\n" "Plot ${Shape}"
printf "${ESC}[35m%s${ESC}[m\n" "Z scale x ${zscalar}"
echo "---"
