#!/bin/bash -eu
# @echo off
# support to move parameter and results fiels.

SCRIPT_DIR=$(cd $(dirname $0); pwd) # 実行スクリプトの絶対パスを取得する
cd "$SCRIPT_DIR"
cd ../../

ESC=$(printf '\033')

csvDir="./data/csv/"
paramDir="./data/input_file/"
plotdataDir="./visualize/plot_data/"
plotfigDir="./visualize/fig/"
targetDir="./data/results/"

nowDir=$(date +%Y-%m-%d-%H-%M)
saveDirname=${1:-}
# array=('SimpleTensile' 'SimpleShare' 'SimpleBend' 'SimpleCompression' 'DiagonalTensile')
# list="SimpleTensile SimpleShare SimpleBend SimpleCompression DiagonalTensile"

if [ -z "$saveDirname" ]; then
    echo "+-------------------------------------------------"
    echo "Where save Directory Name❓"
    echo "+-------------------------------------------------"
    for i in "${!array[@]}"; do
        echo "$1 => ${array[$i]}"
    done
    list=$(find "${paramDir}" -type f \( -name "*.cfg" \) | awk -F"/" '{print $4}' | sort -n)
    select filename in $list
        do
        if [ "${REPLY}" = "q" ]; then
            echo "終了します."
            exit 0
        fi

        if [ -n "${filename}" ]; then
            break
        else
         echo "invalid selection."
        fi
    done
    situationname=$(echo ${filename} | awk -F"." '{print $1}')
    echo "Move [$situationname]"
    saveDirname=${situationname}
fi

echo "+-------------------------------------------------"
echo "Do you want to comment❓"
echo "+-------------------------------------------------"
read -p ":" INPUT_STR
if [ -z ${INPUT_STR} ]; then
    echo "No comment"
else
    echo "Use comment [$INPUT_STR]"
fi
saveDirname="${saveDirname}_${INPUT_STR}"




CHECKDIR="${targetDir}${nowDir}_${saveDirname}"
if [ ! -d ${CHECKDIR} ]; then
    echo "No directory ${CHECKDIR}"
    echo "Create [${CHECKDIR}]"
    mkdir -p ${CHECKDIR}
fi

if [ ! -f "${CHECKDIR}*"   ]; then
    echo safe
    cp "${paramDir}${filename}" "${CHECKDIR}/"
    cp -rp "${csvDir}" "${CHECKDIR}/"
    cp -rp "${plotdataDir}" "${CHECKDIR}/"
    cp -rp "${plotfigDir}" "${CHECKDIR}/"
    if [ -f "${plotdataDir}each_time/" ];then
        rm -r "${plotdataDir}each_time/"
    fi
else
    # printf "${ESC}[31m%s${ESC}$[m\n" "Already exsist❗❗"
    echo hoge
fi


