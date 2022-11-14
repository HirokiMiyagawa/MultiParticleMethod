# usage
# run extract_old.sh
# run gnuplot and load this script
# splot "old_xyz_transpose.dat"

# 区切り文字を指定する
set datafile separator ','

# コンターカラーを変更
set palette rgbformulae 22, 13, -31

# screen一杯にrgbで指定した背景を置く (set background color)
set object 1 rect behind from screen 0,0 to screen 1,1 fc rgb "#fcefcd" fillstyle solid 1.0     # Background color: sepia


set xlabel "X axis" font ",30" offset 0,1 # x軸ラベルの名前とフォントサイズ, 位置
set ylabel "Y axis" font ",30" offset 1,0 # y軸ラベルの名前とフォントサイズ, 位置
set zlabel "Z axis" font ",30" offset -5,0 # z軸ラベルの名前とフォントサイズ, 位置
set tics font ",25"         # メモリのフォントサイズ
set key font ",30" spacing 2          # 凡例のフォントサイズ
set xtics 0, 0.2
set mxtics 2
set ytics 0, 0.2
set mytics 2
set ztics 0, 0.2
set mztics 2


set xtics offset 0,-2                    # X軸目盛りの位置
set ytics offset 0,0                    # Y軸目盛りの位置
set xlabel offset 0,-5                   # x軸の位置
set ylabel offset 10,0                   # y軸の位置
set zlabel offset -8,0                   # z軸の位置
set view equal xyz
