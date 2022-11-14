#!/bin/bash
# @echo off

SCRIPT_DIR=$(cd $(dirname $0); pwd) # 実行スクリプトの絶対パスを取得する
cd "$SCRIPT_DIR"
cd ../../
plot_data_dir="./visualize/plot_data/"
excel_dir="./visualize/Excel/"
# cd "${plot_data_dir}"


ESC=$(printf '\033')

echo "+-------------------------------------------------"
echo "Try to delete the following data file '.csv'"
echo "+-------------------------------------------------"

findfile () {
    #delete csv file
    if [ -z $1 ]; then
        find "${plot_data_dir}" -type f \( -name "*.csv" \)
    else
        printf "${ESC}[35m%s${ESC}[m\n" "Delete ❗❗"
        find "${plot_data_dir}" -type f \( -name "*.csv" \) -delete
    fi

    #delete dat file
    if [ -z $1 ]; then
        find "${excel_dir}" -type f \( -name "*.dat" \)
    else
        printf "${ESC}[35m%s${ESC}[m\n" "Delete ❗❗"
        find "${excel_dir}" -type f \( -name "*.dat" \) -delete
    fi
}

findfile

read -p "ok? (y/N): " yn
case "$yn" in [yY]*) ;; *) echo "abort." ; exit ;; esac

findfile "delete"

