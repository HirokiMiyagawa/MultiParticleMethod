#!/bin/sh
# @echo off
# 坂本さんの実験結果のcsvファイルからプロット用のdatファイルを抽出する
# 移動先のパス (path_to_move)
# args
# 1: 


SCRIPT_DIR=$(cd $(dirname $0); pwd) # 実行スクリプトの絶対パスを取得する
cd "$SCRIPT_DIR"
cd ../../
ROOT_DIR=$(cd $(dirname $0); pwd) # 実行スクリプトの絶対パスを取得する
echo $ROOT_DIR
cd ./data/position/

# Choose default argument

# 移動先のパス (path_to_move)
plot_dir="../../visualize/plot_data/"
analys_dir="../../visualize/Excel/"

# 区切り文字の指定
DIV=" "

# input files
in1x="c_x.dat"
in1y="c_y.dat"
in1z="c_z.dat"
in2="old_xyz.dat"
tx="temp_x.dat"
ty="temp_y.dat"
tz="temp_z.dat"

# output files
of1="old_xyz_transpose.dat"

# initialize
:>| $of1
:>| $in2


ROW=$(wc -l ${in1x} | cut -f 1 -d " ")
echo "Row is ${ROW}"

sed -n "${ROW}p" ${in1x} > $tx
sed -n "${ROW}p" ${in1y} > $ty
sed -n "${ROW}p" ${in1z} > $tz
cat $tx $ty $tz > $in2

COLUMN=$(head -n1 $in1x | wc -w)
echo "Column is ${COLUMN}"

# 1行目の時間を削除
for i in `seq 2 ${COLUMN}`
do
    cut -d "${DIV}" -f ${i} "$in2" | tr '\r\n' ',' >> $of1 #区切り文字を利用してその列を取得。改行を消去し、列を行とする。
    echo >> $of1    # 改行
done

sed -i -e "s/,\$//" $of1

rm $in2 $tx $ty $tz

# plotに使用するファイルを移動する
mv -f $of1 $plot_dir

# Excelに使用するファイルを移動する
# mv -f $of5 $of6 $analys_dir


