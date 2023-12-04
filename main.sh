#!/bin/bash -eu
#@echo off
# If there are any arguments, skip to "make"
set -o pipefail

SCRIPT_DIR=$(cd $(dirname $0); pwd) # 実行スクリプトの絶対パスを取得する
cd "$SCRIPT_DIR"
mode=${1:-}

if [ -z $mode ]; then
  ESC=$(printf '\033') # \e や \x1b または $'\e' は使用しない
  printf "${ESC}[31m%s${ESC}[m\n" 'Run CMake' 
  echo "----------------------------------"

  echo "----------------------------------"
  echo "Run copy2results"
  echo "----------------------------------"
  ./src/scripts/copy2results.sh

  echo "----------------------------------"
  echo "Run delete_csvfiles"
  echo "----------------------------------"
  ./src/scripts/delete_csvfile.sh

  echo "----------------------------------"
  echo "Run divide_input_param"
  echo "----------------------------------"
  ./src/scripts/divide_input_param.sh

  cd build
  if [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    cmake ..
  elif [ "$(expr substr $(uname -s) 1 10)" == 'MINGW64_NT' ]; then
    cmake .. -G "MSYS Makefiles"
  else
    cmake ..
  fi
  # cd ../
  ESC=$(printf '\033') # \e や \x1b または $'\e' は使用しない
  if make -f Makefile; then
    cd ../
    make &
    makepid=$!
  fi
else
#   cd build
  echo "only Make"
  ESC=$(printf '\033') # \e や \x1b または $'\e' は使用しない
  if make -f Makefile; then
    # cd ../
    make &
    makepid=$!
  fi
fi

# cd ../

wait $makepid
echo $?

if [ $? -eq 0 ]; then
  printf "${ESC}[31m%s${ESC}[m\n" 'Start Anlysis'
  echo "----------------------------------"

  ./bin/main


  echo "----------------------------------"
  echo "Plot"
  echo "----------------------------------"
  ./gnuplot.sh

  echo "----------------------------------"
  echo "Run copy2results"
  echo "----------------------------------"
  ./src/scripts/copy2results.sh

  echo "----------------------------------"
  echo "Run delete_csvfiles"
  echo "----------------------------------"
  ./src/scripts/delete_csvfile.sh
else 
  printf "${ESC}[31m%s${ESC}[m\n" 'Missing Build'
  exit 1
fi
