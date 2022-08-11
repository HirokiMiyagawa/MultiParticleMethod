#!/bin/sh
# 実験結果のcsvファイルからプロット用のdatファイルを抽出する
# 移動先のパス (path_to_move)
# args
# 1: ファイルを分ける頻度（div_file）
# 2:ファイル名の含む数値（parameter_○○.csvの○○はいくつまであるか）       使ってない
# @echo off


SCRIPT_DIR=$(cd $(dirname $0); pwd) # 実行スクリプトの絶対パスを取得する
cd "$SCRIPT_DIR" || exit
cd ../../
ROOT_DIR=$(pwd)
echo $ROOT_DIR
cd ./data/csv/ || exit
# Choose default argument
# OUTPUT=${1:-"cylinder"}
#stf=${1:-0} # search target file number
# OUTPUT=${2:-"cylinder"}
OUTPUT=${3:-"sail"}
#sta=2 # seerch target array

if [ $# != 1 ]; then
    echo error argument: "$*"
    echo "ファイルを分ける頻度（div_file）を引数に指定してください"
    exit 1
fi


# カンマ区切り
FS=","

# 移動先のパス (path_to_move)
plot_dir="../../visualize/plot_data/"
excel_dir="../../visualize/Excel/"


# input files
in1="parameter_0.csv"
in3="condition.csv"



# search time
# st1=${1:-2.5}
# st2=${2:-0.0}

# Replace CFLR line feed code with LR.o
find . -type f -name "*.csv" | xargs sed -i "s/\r//"


search_header_x="X-axis"
search_header_vc="Bottom.x"
search_header_time="Time"

# ヘッダーの検索
# 1行目を列番号をつけてn行2列で出力する。その後、"X-axis"を検索し、その列番号を取得する
column1=$(awk -F"${FS}" ' { for (i = 1; i <= NF; ++i) print i, $i; exit } ' $in1 | grep "${search_header_x}" | awk '{print $1}')
# 1行目を列番号をつけてn行2列で出力する。その後、"Bottom.x"を検索し、その列番号を取得する
column2=$(awk -F"${FS}" ' { for (i = 1; i <= NF; ++i) print i, $i; exit } ' $in1 | grep "${search_header_vc}" | awk '{print $1}')
# 1行目を列番号をつけてn行2列で出力する。その後、"Time"を検索し、その列番号を取得する
#column3=$(awk -F"${FS}" ' { for (i = 1; i <= NF; ++i) print i, $i; exit } ' $in1 | grep "${search_header_time}" | awk '{print $1}')

#echo "X-axis is culunm ${column1}"
#echo "Bottoom.x colunm is ${column2}"


# 下2行をまとめて処理する
# 空行を検索 | 
#ファイルごとに処理
i=0
#while [ $2 -le "$1" ]
while :
do
    cd "$SCRIPT_DIR" || exit
    cd ../../data/csv/ || exit
    j=0
    #input data
    in2="parameter_${i}.csv"
    #ファイルが見つからなくなるまで処理
    if [ ! -e "$in2" ]; then
        #echo "axis is culunm ${i}"
        break
    fi
    #ファイルの中での複数このデータの処理
    while [ $j -lt "$1" ]
    #while :
    do
        cd "$SCRIPT_DIR" || exit
        cd ../../data/csv/ || exit
        #何個目のファイルか（0から始まる）
        count=$((j+i))
        # output files
        of1="${OUTPUT}_deformation_${count}.csv" 
        of3="vp_${OUTPUT}_deformation_coordinates_${count}.csv" 
        of5="nextValue_${count}.dat"
        #of6="preValue_${count}.dat"

        #すでにデータ処理しているかの確認
        cd ../../visualize/Excel/ || exit
        if [ -e "$of5" ]; then
            cd ../../visualize/plot_data/ || exit
            if [ -e "$of1" ] && [ -e "$of3" ]; then
                j=$((j+1))
                echo "No. ${count}のファイルは処理済み"
                cd ../../data/csv/ || exit
                continue
            fi
        fi
        cd ../../data/csv/ || exit

        #1ブロック目の時は1行目スタート，それ以外の時は何もない行スタート
        if [ $j -eq 0 ]; then
            start=1
        else
            start=$(grep -n "^$" $in2 | cut -d ":" -f 1 | awk "NR==$j")
        fi
        if [ -z "$start" ]; then
            # MinGWで作成したcsvファイルの空行検索ができないので、とりあえず実数を代入した
            # first=444
            iNum=$(grep "iNum" "${in3}" | awk -F',' '{print $3}')
            jNum=$(grep "jNum" "${in3}" | awk -F',' '{print $3}')
            iNum=$(echo ${iNum} | tr -d "\r")
            jNum=$(echo ${jNum} | tr -d "\r")
            start=$(echo "scale=0;${iNum}*${jNum}+3" | bc -l)
        fi
        # 処理の終了行数
        finish=$(grep -n "^$" $in2 | cut -d ":" -f 1 | awk "NR==$((j+1))")

        if [ -z "$finish" ]; then
            break
        fi

        #確認テスト用の表示
        #echo "count: ${count}"
        #echo "start line: ${start}"
        #echo "Extract start line: ${finish}"
 

        # deformation
        # sed -e "$((${second_s}+2)), $second_e!d" $in2 | cut -d " " -f $column1-$(($column1 + 2)) | while read line
        # sed -n "$((${second_s}+2)),${second_e}p" $in2 | awk -F '[ \t]' "$column1-$(($column1 + 2))" | while read line
        sed -n "$((${start}+2)),${finish}p" $in2 | cut -f "$column1-$(($column1 + 2))" --delim="${FS}" | while read line
        do
            echo "$line" >> $of1
        done

        # deformation vp      これは何？
        # sed -e "$((${second_s}+2)), $second_e!d" $in2 | cut -d " " -f $column2-$(($column2 + 11)) | while read line
        sed -n "$((${start}+2)),${finish}p" $in2 | cut -f "$column2-$(($column2 + 11))" --delim="${FS}" | while read line
        do
            echo "$line" >> $of3
        done

        # make parameter files      なにこれ？
        # initial parrameter
        # sed -e "3,${first}!d" $in1  | cut -d "    " -f 4-$NF | while read line
        # sed -n "3,${first}p" $in1 | awk -F '[ \t]' "{print $4-$(($NF))}" | while read line
        #sed -n "3,${start}p" $in1 | cut -f 4-$NF --delim="${FS}" | while read line
        #do
            #echo "$line" >> $of6
        #done

        # deformation parameter
        # sed -e "$((${second_s}+2)), $second_e!d" $in2 | cut -d " " -f 4-$NF | while read line
        # sed -n "$((${second_s}+2)),${second_e}p" $in2 | awk -F '[ \t]' "4-$(($NF))" | while read line
        sed -n "$((${start}+2)),${finish}p" $in2 | cut -f 4-$NF --delim="${FS}" | while read line
        do
            echo "$line" >> $of5
        done


        # plotに使用するファイルを移動する
        mv -f "$of1" "$of3" $plot_dir

        # Excelに使用するファイルを移動する
        mv -f $of5 $excel_dir
        j=$((j+1))
    done
    i=$((i+j))
    echo "count: ${i}"
done

#完了のメッセージ
echo "データ処理完了しました"