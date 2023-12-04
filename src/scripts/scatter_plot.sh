#!/bin/sh
#echo off

# 実行ファイルのパスに移動する
PATH_DIR_SCRIPT="$(cd "$(dirname "${BASH_SOURCE:-$0}")" && pwd)" # 実行ファイルのディレクトリを取得する 
cd $PATH_DIR_SCRIPT
cd ../../

zscalar=${1:-1E0}   
Shape=${3:-"sail"}
imagePath="visualize/fig/${Shape}_deformation.png"
plotScript="${PATH_DIR_SCRIPT}/scatter_gplot.plt"
xy_min=-0.2
xy_max=1.2
z_min=-0.15
z_max=0.15

# pltファイルを利用する
# gnuplot -e "
# call \"${plotScript}\" \"${xy_min}\" \"${xy_max}\" \"${z_min}\" ${z_max} \"${Shape}\" \"initial\" ${zscalar}
# " > /dev/null

# gnuplot -p -e "
gnuplot -p -e "
    call \"${plotScript}\" \"${xy_min}\" \"${xy_max}\" \"${z_min}\" ${z_max} \"${Shape}\" \"deformation\" ${zscalar}
" > /dev/null

# プロットしたファイルを開く
# explorer.exe `wslpath -aw ${imagePath}` 

ESC=$(printf '\033') # \e や \x1b または $'\e' は使用しない
echo
printf "${ESC}[35m%s${ESC}[m\n" "Plot ${Shape}"
printf "${ESC}[35m%s${ESC}[m\n" "Z scale x ${zscalar}"
echo "---"
