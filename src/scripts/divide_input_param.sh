#!/bin/bash
# @echo off
# cppに書き込む場合はelse文の2行目を利用する。その後、「#」を「// 」に置換して型が正しいか確認する（iNumなどはintにする）
# arg 1: input data file name
# TODO: 各解析条件とその境界条件
# 列方向の並びに依存しない、ヘッダーの文字の検索による値の取得



SCRIPT_DIR=$(cd $(dirname $0); pwd) # 実行スクリプトの絶対パスを取得する
cd "$SCRIPT_DIR"
cd ../../
pwd

plot_data_dir="./data/input_file/"
cd $plot_data_dir
pwd

# カンマ区切り
FS=","

# ouput files
in1=${1:-"default.csv"}

if [ -z "$1" ]; then
    # echo "The following `*.csv` archives were found; select one:"
    echo "The following .csv archives were found; select one:"

    # set the prompt used by select, replacing "#?"
    PS3="Use number to select a file or 'q' to cancel: "

    # allow the user to choose a file
    select filename in *.csv
    do
        # leave the loop if the user says 'stop'
        if [[ "$REPLY" == "q" ]]; then exit 0; fi

        # complain if no file was selected, and loop to ask again
        if [[ "$filename" == "" ]]
        then
            echo "'$REPLY' is not a valid number"
            continue
        fi

        # now we can use the selected file
        echo "$filename installed"

        # it'll ask for another unless we leave the loop
        break
    done
fi
in1=$filename


SituationList=( $(head -n 1 ${in1} | sed "s/^.*Key,//" | sed "s/,/ /g") )
SituationList[-1]=$(echo "${SituationList[-1]}" | sed -e "s/[\r\n]\+//g")
# head -n 1 ${in1} | sed "s/^.*Key,//" | sed "s/,/ /g"

# output files
out_extention="cfg"
# of1="SimpleTensile.${out_extention}"
# of2="SimpleShare.${out_extention}"
# of3="SimpleBend.${out_extention}"
# of4="SimplePressure.${out_extention}"
# of5="DiagonalTensile.${out_extention}"
# of6="SimpleCompression.${out_extention}"
# of7="CylinderPressure.${out_extention}"
# of8="CubePressure.${out_extention}"
# of9="PastCylinder.${out_extention}"
# of10="NaturalFrequency.${out_extention}"
# of11="PlateRevolution.${out_extention}"
# of12="SimpleShareWrinkle.${out_extention}"
# of13="SupportShare.${out_extention}"


# initialize
# :>| $of1
# :>| $of2
# :>| $of3
# :>| $of4
# :>| $of5
# :>| $of6
# :>| $of7
# :>| $of8
# :>| $of9
# :>| $of10
# :>| $of11
# :>| $of12
# :>| $of13

for i in ${SituationList[@]}
do
    :>| "${i}.${out_extention}"
done


# outputs number
Num=$(head -1 $in1 | awk -F"," '{print NF}')
Num=$((Num-1))

row=$(wc -w $in1 | awk -F" " '{print $1}')


# 各of(N)毎に出力する
for i in $(seq 1 ${Num}); do
    # var_name="of${i}"
    # of_name=$(eval "echo \"\${${var_name}}\"")
    of_name="${SituationList[i-1]}.${out_extention}"
    echo ${of_name}

    column=$((${i}+1))

    # "`echo $ret | grep '200'`"
    awk -F',' -v "col=${column}" '{print $1,$col}' $in1 | while read key val
    do
        if [ "`echo $key | grep '#'`" ]; then
            echo "$key $val" >> ${of_name}
        else
            if [ -n "$val" ]; then
                echo $key\=$val >> ${of_name}
                # c++に書き込む用
                # echo "$key=param->get<double>(\"$key\",$val);" >> $of1
            fi
        fi
    done
done


ESC=$(printf '\033') # \e や \x1b または $'\e' は使用しない
printf "${ESC}[35m%s${ESC}[m\n" "Divide ${in1}"
echo "---"

