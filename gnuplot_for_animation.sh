#!/bin/bash -eu
# gnuplot を用いたプロット
# @echo off
# args
# 1: ファイルを分ける頻度（div_file）
# 2: アニメーションの表示間隔(ms)
# 3: zscalar 
export MAGICK_THREAD_LIMIT=1
interval=${2:-10}
zscalar=${3:-1E0}
NUM=${4:-0}
PATH_DIR_SCRIPT="$(cd "$(dirname "${BASH_SOURCE:-$0}")" && pwd)" # 実行ファイルの親ディレクトリを取得する
cd $PATH_DIR_SCRIPT
cd "src/scripts"

if [ $# != 1 ]; then
    echo error argument: "$*"
    echo "ファイルを分ける頻度（div_file）を入力してください"
    read div_file

else
    div_file=$1
fi


pids=()
# ok.sh は 0 を返す
# ng.sh は 1 を返す
# commands=("./extract_data.sh ${NUM}" "./scatter_plot.sh ${zscalar}" "./3dsurface_plot.sh" "./quicklook.sh")

# for command in ${commands[@]}; do
#   ${command} &
#   pids+=($!)
#   wait
# done
./delete_csv_dat_file.sh
wait
./extract_data_for_animation.sh "${div_file}"
# pids+=($!)
wait
#./scatter_plot_for_animation.sh ${zscalar}
# pids+=($!)
wait

echo "プロットをスキップしますか？スキップするときは1を。"
read skip_plot
if [ ! "${skip_plot}" -eq 1 ]; then
    ./3dsurface_plot_for_animation.sh ${zscalar}
fi
# pids+=($!)
wait

#./crosssection.sh

# pids+=($!)
wait

#./quicklook.sh

# pids+=($!)
wait

cd ../..
echo "アニメーションを作成します"
echo "アニメーションのファイル名'(拡張子抜き)を入力してください"
read animation_file
echo "俯瞰した図のアニメーションは作成しますか？スキップするときは1を。"
read skip_plot_normal
if [ ! "${skip_plot_normal}" -eq 1 ]; then
convert -limit memory 4028MB -delay "${interval}" -loop 0 ./visualize/div_fig/div_sail_deformation_****.png ./visualize/div_fig/"${animation_file}".gif
fi
echo "アニメーション50%終わり"
convert -limit memory 4028MB -delay "${interval}" -loop 0 ./visualize/fig/div_sail_deformation_****_xy.png ./visualize/fig/"${animation_file}".gif
echo "gnuplot処理終了"
explorer.exe "$(wslpath -aw ./visualize/fig/"${animation_file}".gif)" 
explorer.exe "$(wslpath -aw ./visualize/div_fig/"${animation_file}".gif)"
echo "gnuplot処理終了"
