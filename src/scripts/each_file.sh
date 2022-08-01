#!/bin/bash -eu
# extract particle coordinate from csv file.
# exclude other data.
# 実験結果のcsvファイルからプロット用のdatファイルを抽出する
# 移動先のパス (path_to_move)
# args
# 1: read file name
# @echo off


PATH_DIR_SCRIPT="$(cd "$(dirname "${BASH_SOURCE:-$0}")" && pwd)"
cd $PATH_DIR_SCRIPT
echo "sript dir: " $PATH_DIR_SCRIPT
cd ../../
ROOT_DIR=$(pwd) # 実行スクリプトの絶対パスを取得する
echo "root dir: " $ROOT_DIR
# cd ./data/csv/

# Choose default argument

# カンマ区切り
# FS=","

# 移動先のパス (path_to_move)
plot_dir="../../visualize/plot_data/"
csvDir="./data/csv/"
call_scriptDir="./src/scripts/extract_data_from_argument.sh"
mergeDir="./visualize/plot_data/each_time/"
#
# input files
read_file=${1:-"parameter"}

# output files

# search time

# list=$(find . -type f \( -name "*.csv" -and -name "${read_file}*" \) | sort -n -k 2,2 -t "_" | tail -n 2 | head -n 1 | awk -F"/" '{print $2}')
# saveIFS="$FS"
# FS=" "
list=( $(find ${csvDir} -type f \( -name "*.csv" -and -name "${read_file}*" \) | sort -n -k 2,2 -t "_" | awk -F"/" '{print $4}') )
echo "${#list[*]}"


mvDir=$(find ${csvDir} -type d -name "*time*")

if [ -d ${mergeDir} ]; then
    rm -r "${mergeDir}"
fi

for i in ${list[@]}
do
    ${call_scriptDir} ${i} "coordinate"
    ${call_scriptDir} ${i} "vector"
done
# mvDir=$(find ${csvDir} -type d | awk -F"/" '{print $4}')
mvDir=$(find ${csvDir} -type d -name "*time*")
# echo $mvDir
mv ${mvDir} ${mergeDir}

# find . -type f \( -name "*.csv" -and -name "${read_file}*" \) | sort -n -k 2,2 -t "_" | awk -F"/" '{print $2}'
# echo $list[0]
# in2="${in2}_${stf}.csv"
# IFS="$saveIFS"


# grep -n "^$" $read_file | cut -d ":" -f 1
# declare -a array=( $(grep -n "^$" $read_file | cut -d ":" -f 1) )
# echo ${#array[*]}
# foo=$(echo ${#array[*]})
# echo $foo
# # echo ${array[${#array[@]}-1]}

# if [ ! -d ${tmp_dir} ]; then
#     mkdir "${tmp_dir}"
# fi

# declare -i line_start=1
# for i in ${array[@]}
# do
#     line_end=${i}

#     output_filename=$(sed -n "$((${line_start}+2))P" $read_file | cut -f "${column_t}" --delim="${FS}" | cut -d " " -f 1 | xargs printf '%.3f\n')
    
#     echo ${output_filename}

#     output_filename="${output_filename}.csv"

#     sed -n "$((${line_start}+2)),${line_end}p" $read_file | cut -f "$column_x-$(($column_x + 2))" --delim="${FS}" | while read line
#     do
#         echo "$line" >> "${output_filename}"
#     done
#     mv ${output_filename} ${tmp_dir}
#     line_start=${i}
# done

