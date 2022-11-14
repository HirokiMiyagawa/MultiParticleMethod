#!/bin/sh
# 実験結果のcsvファイルからプロット用のdatファイルを抽出する
# 移動先のパス (path_to_move)
# args
# 1: ファイル名の含む数値
# 2: search target array
# 3: 読み込むファイル名番号
# @echo off


SCRIPT_DIR=$(cd $(dirname $0); pwd) # 実行スクリプトの絶対パスを取得する
cd "$SCRIPT_DIR"
cd ../../
ROOT_DIR=$(pwd)
echo $ROOT_DIR
cd ./data/csv/
# Choose default argument
# OUTPUT=${1:-"cylinder"}
stf=${1:-0} # search target file number
# OUTPUT=${2:-"cylinder"}
OUTPUT=${2:-"sail"}
sta=${3:-2} # seerch target array
echo "sta=$sta"


# カンマ区切り
FS=","

# 移動先のパス (path_to_move)
plot_dir="../../visualize/plot_data/"
excel_dir="../../visualize/Excel/"


# input files
in1="parameter_0.csv"
in2="parameter"
in3="condition.csv"

# output files
of1="${OUTPUT}_deformation.csv" 
of2="${OUTPUT}_initial.csv" 
of3="vp_${OUTPUT}_deformation_coordinates.csv" 
of4="vp_${OUTPUT}_initial_coordinates.csv" 
of5="nextValue.dat"
of6="preValue.dat"

# search time
# st1=${1:-2.5}
# st2=${2:-0.0}

# Replace CFLR line feed code with LR.o
find . -type f -name "*.csv" | xargs sed -i "s/\r//"

# if [ ! $1 -eq 0 ]; then
# when you are running ./gnuplot.sh, if you don't specify arguments, the first one(if ~~) is choosen, not second one(else ~~).
# search a file of that ○○ is largest number for parameter_○○.csv
if [ -z $1 ] || [ $1 -eq 0 ]; then
    in2=$(find . -type f \( -name "*.csv" -and -name "${in2}*" \) | sort -n -k 2,2 -t "_" | tail -n 2 | head -n 1 | awk -F"/" '{print $2}')
else
    in2="${in2}_${stf}.csv"
fi

echo "initial file name is '${in1}'"
echo "deformation file name is '${in2}'"
echo "condition file name is '${in3}'"

# initialize
:>| $of1
:>| $of2
:>| $of3
:>| $of4
:>| $of5
:>| $of6

search_header_x="X-axis"
search_header_vc="Bottom.x"
search_header_time="Time"

# ヘッダーの検索
# 1行目を列番号をつけてn行2列で出力する。その後、"X-axis"を検索し、その列番号を取得する
column1=$(awk -F"${FS}" ' { for (i = 1; i <= NF; ++i) print i, $i; exit } ' $in1 | grep "${search_header_x}" | awk '{print $1}')
# 1行目を列番号をつけてn行2列で出力する。その後、"Bottom.x"を検索し、その列番号を取得する
column2=$(awk -F"${FS}" ' { for (i = 1; i <= NF; ++i) print i, $i; exit } ' $in1 | grep "${search_header_vc}" | awk '{print $1}')
# 1行目を列番号をつけてn行2列で出力する。その後、"Time"を検索し、その列番号を取得する
column3=$(awk -F"${FS}" ' { for (i = 1; i <= NF; ++i) print i, $i; exit } ' $in1 | grep "${search_header_time}" | awk '{print $1}')


echo "X-axis is culunm ${column1}"
echo "Bottoom.x colunm is ${column2}"

# 下2行をまとめて処理する
# 空行を検索 | 
first=$(grep -n "^$" $in2 | cut -d ":" -f 1 | head -1)
if [ -z $first ]; then
    # MinGWで作成したcsvファイルの空行検索ができないので、とりあえず実数を代入した
    # first=444
    iNum=$(grep "iNum" "${in3}" | awk -F',' '{print $2}')
    jNum=$(grep "jNum" "${in3}" | awk -F',' '{print $2}')
    iNum=$(echo ${iNum} | tr -d "\r")
    jNum=$(echo ${jNum} | tr -d "\r")
    first=$(echo "scale=0;${iNum}*${jNum}+3" | bc -l)
fi

# 2つ目のブロックの開始行数
second_s=$(grep -n "^$" $in2 | cut -d ":" -f 1 | awk "NR==$(($sta-1))")
# 2つ目のブロックの終了行数
second_e=$(grep -n "^$" $in2 | cut -d ":" -f 1 | awk "NR==$sta")

# 最後のブロックの終了行数
# second_e=$(wc -l parameter_0.csv | cut -d " " -f 1)
second_e=$(wc -l "${in2}" | cut -d " " -f 1)
second_s=$(($second_e - $first + 1))

echo "first line: ${first}"
echo "Extract start line: ${second_s}"
echo "Extract end line: ${second_e}"

# initial
# sed -e "3,${first}!d" $in1 | cut -d " " -f $column1-$(($column1 + 2)) | while read line
# sed -n "3,${first}p" $in1 | awk -F '[ \t]' "$column1-$(($column1 + 2))" | while read line
sed -n "3,${first}p" $in1 | cut -f "$column1-$(($column1 + 2))" --delim="${FS}" | while read line
do
    echo "$line" >> $of2
done

# initial vp
# sed -e "3,${first}!d" $in1 | cut -d " " -f $column2-$(($column2 + 11)) | while read line
# sed -n "3,${first}p" $in1 | awk -F '[ \t]' "$column2-$(($column2 + 11))" | while read line
sed -n "3,${first}p" $in1 | cut -f "$column2-$(($column2 + 11))" --delim="${FS}" | while read line
do
    echo "$line" >> $of4
done

# deformation
# sed -e "$((${second_s}+2)), $second_e!d" $in2 | cut -d " " -f $column1-$(($column1 + 2)) | while read line
# sed -n "$((${second_s}+2)),${second_e}p" $in2 | awk -F '[ \t]' "$column1-$(($column1 + 2))" | while read line
sed -n "$((${second_s}+2)),${second_e}p" $in2 | cut -f "$column1-$(($column1 + 2))" --delim="${FS}" | while read line
do
    echo "$line" >> $of1
done

# deformation vp
# sed -e "$((${second_s}+2)), $second_e!d" $in2 | cut -d " " -f $column2-$(($column2 + 11)) | while read line
sed -n "$((${second_s}+2)),${second_e}p" $in2 | cut -f "$column2-$(($column2 + 11))" --delim="${FS}" | while read line
do
    echo "$line" >> $of3
done

# make parameter files
# initial parrameter
# sed -e "3,${first}!d" $in1  | cut -d "    " -f 4-$NF | while read line
# sed -n "3,${first}p" $in1 | awk -F '[ \t]' "{print $4-$(($NF))}" | while read line
sed -n "3,${first}p" $in1 | cut -f 4-$NF --delim="${FS}" | while read line
do
    echo "$line" >> $of6
done

# deformation parameter
# sed -e "$((${second_s}+2)), $second_e!d" $in2 | cut -d " " -f 4-$NF | while read line
# sed -n "$((${second_s}+2)),${second_e}p" $in2 | awk -F '[ \t]' "4-$(($NF))" | while read line
sed -n "$((${second_s}+2)),${second_e}p" $in2 | cut -f 4-$NF --delim="${FS}" | while read line
do
    echo "$line" >> $of5
done


# plotに使用するファイルを移動する
mv -f $of1 $of2 $of3 $of4 $plot_dir

# Excelに使用するファイルを移動する
mv -f $of5 $of6 $excel_dir
