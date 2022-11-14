#!/bin/bash -eu
# 実験結果のcsvファイルからプロット用のdatファイルを抽出する
# 移動先のパス (path_to_move)
# args
# 1: ファイル名の含む数値
# 2: search target array
# 3: 読み込むファイル名番号
# @echo off

echo "Short Review this analysis❗❗"
echo "Nothig will be displayed, the value is very huge/little."

SCRIPT_DIR=$(cd $(dirname $0); pwd) # 実行スクリプトの絶対パスを取得する
cd "$SCRIPT_DIR"
cd ../../
ROOT_DIR=$(pwd)
# echo $ROOT_DIR

plot_dataDir="./visualize/plot_data"
cd $plot_dataDir
# pwd

# Choose default argument
# OUTPUT=${1:-"cylinder"}
# OUTPUT=${2:-"cylinder"}

# find . -type f -regex "^_deformation"

dataFile=$(find -regex "^.*_deformation\.csv")
echo $dataFile

xMax=$(find -regex "^.*_deformation\.csv" | xargs cat |  awk -F"," '{if(m<$1) m=$1} END{print m}')
yMax=$(find -regex "^.*_deformation\.csv" | xargs cat |  awk -F"," '{if(m<$2) m=$2} END{print m}')
zMax=$(find -regex "^.*_deformation\.csv" | xargs cat |  awk -F"," '{if(m<$3) m=$3} END{print m}')

ESC=$(printf '\033') # \e や \x1b または $'\e' は使用しない
printf "${ESC}[31m%s${ESC}[m\n" "Max"
echo "---"

echo "x: $xMax"
echo "y: $yMax"
echo "z: $zMax"


xMin=$(find -regex "^.*_deformation\.csv" | xargs cat |  awk -F"," '{if(m>$1) m=$1} END{print m}')
yMin=$(find -regex "^.*_deformation\.csv" | xargs cat |  awk -F"," '{if(m>$2) m=$2} END{print m}')
zMin=$(find -regex "^.*_deformation\.csv" | xargs cat |  awk -F"," '{if(m>$3) m=$3} END{print m}')

echo " "
printf "${ESC}[34m%s${ESC}[m\n" "Min"
echo "---"
echo "x: $xMin"
echo "y: $yMin"
echo "z: $zMin"

echo " "

