#!/bin/bash
# @echo off

SCRIPT_DIR=$(cd $(dirname $0); pwd) # 実行スクリプトの絶対パスを取得する
cd "$SCRIPT_DIR"
cd ../../
plot_data_dir="./data/csv/"
# cd "${plot_data_dir}"


ESC=$(printf '\033')

echo "+-------------------------------------------------"
echo "Try to delete the following data file '.csv'"
echo "+-------------------------------------------------"

findCSVfile () {
  if [ -z $1 ]; then
    find "${plot_data_dir}" -type f \( -name "*.csv" \)
  else
    printf "${ESC}[35m%s${ESC}[m\n" "Delete ❗❗"
    find "${plot_data_dir}" -type f \( -name "*.csv" \) -delete
  fi
}

findCSVfile

read -p "ok? (y/N): " yn
case "$yn" in [yY]*) ;; *) echo "abort." ; exit ;; esac

findCSVfile "delete"

