#!/bin/bash -eu
# gnuplot を用いたプロット
# @echo off
# args
# 1: zscalar 
# 2: 読み込む parameter_(NUM)

zscalar=${1:-1E0}
NUM=${2:-0}
PATH_DIR_SCRIPT="$(cd "$(dirname "${BASH_SOURCE:-$0}")" && pwd)" # 実行ファイルの親ディレクトリを取得する
cd $PATH_DIR_SCRIPT
cd "src/scripts"


pids=()
# ok.sh は 0 を返す
# ng.sh は 1 を返す
# commands=("./extract_data.sh ${NUM}" "./scatter_plot.sh ${zscalar}" "./3dsurface_plot.sh" "./quicklook.sh")

# for command in ${commands[@]}; do
#   ${command} &
#   pids+=($!)
#   wait
# done
./extract_data.sh ${NUM}
# pids+=($!)
wait
./scatter_plot.sh ${zscalar}
# pids+=($!)
wait
./3dsurface_plot.sh ${zscalar}
# pids+=($!)
wait
./crosssection.sh
# pids+=($!)
wait
./quicklook.sh
# pids+=($!)
wait

# for pid in ${pids[@]}; do
#   wait $pid
#   if [ $? -ne 0 ]; then
#     echo "any commands is error"
#     exit 1
#   fi
# done



# 坂本さんの結果をプロットする
# gnuplot -e "
#     load 'plot_xyz.plt';
#     "
