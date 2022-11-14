#!/bin/bash -eu
# extract particle coordinate from csv file.
# exclude other data.
# 実験結果のcsvファイルからプロット用のdatファイルを抽出する
# 移動先のパス (path_to_move)
# args
# 1: read file name
# 2: read_target
# @echo off


SCRIPT_DIR=$(cd $(dirname $0); pwd) # 実行スクリプトの絶対パスを取得する
cd "$SCRIPT_DIR"
cd ../../
ROOT_DIR=$(cd $(dirname $0); pwd) # 実行スクリプトの絶対パスを取得する
# echo $ROOT_DIR
cd ./data/csv/
# Choose default argument
read_target=${2:-"coordinate"}

# カンマ区切り
FS=","

# 移動先のパス (path_to_move)
tmp_dir="each_time"
plot_dir="../../visualize/plot_data/"

# input files
read_file=${1:-"parameter_100.csv"}

# output files

# search time

read_file=$(find . -type f \( -name "*.csv" -and -name "${read_file}*" \) | sort -n -k 2,2 -t "_" | tail -n 2 | head -n 1 | awk -F"/" '{print $2}')
# in2="${in2}_${stf}.csv"

echo "initial file name is '$read_file'."

# initialize

search_header_x="X-axis"
search_header_v="V.x"
search_header_vc="Bottom.x"
search_header_time="Time"

# ヘッダーの検索
# 1行目を列番号をつけてn行2列で出力する。その後、"X-axis"を検索し、その列番号を取得する
column_x=$(awk -F"${FS}" ' { for (i = 1; i <= NF; ++i) print i, $i; exit } ' $read_file | grep "${search_header_x}" | awk '{print $1}')

# 1行目を列番号をつけてn行2列で出力する。その後、"V,x"を検索し、その列番号を取得する
column_v=$(awk -F"${FS}" ' { for (i = 1; i <= NF; ++i) print i, $i; exit } ' $read_file | grep "${search_header_v}" | awk '{print $1}')

# 1行目を列番号をつけてn行2列で出力する。その後、"Bottom.x"を検索し、その列番号を取得する
column_vc=$(awk -F"${FS}" ' { for (i = 1; i <= NF; ++i) print i, $i; exit } ' $read_file | grep "${search_header_vc}" | awk '{print $1}')
# 1行目を列番号をつけてn行2列で出力する。その後、"Time"を検索し、その列番号を取得する
column_t=$(awk -F"${FS}" ' { for (i = 1; i <= NF; ++i) print i, $i; exit } ' $read_file | grep "${search_header_time}" | awk '{print $1}')

# echo "X-axis is culunm ${column_x}"
# echo "Bottoom.x colunm is ${column_vc}"
# echo "Time colunm is ${column_t}"

# 下2行をまとめて処理する
# search blank line number (list up blank line number | exclude ":" | only use first blank line number)
# first=$(grep -n "^$" $read_file | cut -d ":" -f 1 | head -1)

# grep -n "^$" $read_file | cut -d ":" -f 1
declare -a array=( $(grep -n "^$" $read_file | cut -d ":" -f 1) )
# echo ${#array[*]}
# echo ${array[${#array[@]}-1]}

if [ ! -d ${tmp_dir} ]; then
    mkdir "${tmp_dir}"
# else
#     rm -r   "${tmp_dir}"
#     mkdir "${tmp_dir}"
fi

# echo ${read_target}
if [ $read_target = "coordinate" ]; then
    column_target=${column_x}
    output_filename_ini="c_"
elif [ $read_target = "vector" ]; then
    column_target=${column_v}
    output_filename_ini="v_"
else
    echo "error"
    exit
fi

declare -i line_start=1
for i in ${array[@]}
do
    line_end=${i}

    # output_filename=$(sed -n "$((${line_start}+2))P" $read_file | cut -f "${column_t}" --delim="${FS}" | cut -d " " -f 1 | xargs printf '%.3f\n')
    output_filename=$(sed -n "$((${line_start}+2))P" $read_file | cut -f "${column_t}" --delim="${FS}" | cut -d " " -f 1 | xargs printf '%.5f\n')
    
    # echo ${output_filename}

    output_filename="${output_filename_ini}${output_filename}.csv"

    # sed -n "$((${line_start}+2)),${line_end}p" $read_file | cut -f "$column_x-$(($column_x + 2))" --delim="${FS}" | while read line
    sed -n "$((${line_start}+2)),${line_end}p" $read_file | cut -f "$column_target-$(($column_target + 2))" --delim="${FS}" | while read line
    do
        echo "$line" >> "${output_filename}"
    done
    mv ${output_filename} ${tmp_dir}
    line_start=${i}
done

