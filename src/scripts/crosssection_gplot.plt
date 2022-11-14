# data_dir内のdatファイルからexport_dirにプロットする
# ARGV[1] input file path 
# ARGV[2] zscalar
# ARGV[3] divide row
# ARGV[4] Axis particle
# ARGV[5] Section Number

# ARGV[] x&y range-min
# ARGV[] x&y range-max
# ARGV[] z range-min 
# ARGV[] z range-max 


if ( ARGV[2] < 0 ){
    sprintf("$s", "Z scale ≦ 0. Please enter 0 < Z scale")
    exit
}

# xy_range_min = ARGV[]
# xy_range_max = ARGV[]
# z_range_min = ARGV[]
# z_range_max = ARGV[]

# HACK: Don't work!!
set term qt 0 font "/usr/share/fonts/truetype/noto/NotoMono-Regular.ttf, 12"
# 区切り文字を指定する
set datafile separator ','

input_file_path = ARGV[1]
export_file = sprintf("%s%s%s",ARGV[4],"-",ARGV[5])
# data_dir = "visualize/plot_data/"
export_dir ="visualize/fig/"
extention = ".csv"
ex_extention = ".png"


# コンターカラーを変更
set palette rgbformulae 22, 13, -31

# screen一杯にrgbで指定した背景を置く (set background color)
# set object 1 rect behind from screen 0,0 to screen 1,1 fc rgb "#F5F5F5" fillstyle solid 1.0     # Background color: snow
set object 1 rect behind from screen 0,0 to screen 1,1 fc rgb "#fcefcd" fillstyle solid 1.0     # Background color: sepia


Scale=ARGV[2]   # Z軸の倍率を定める
u = "using 1:2:($3*Scale)"


if (ARGV[2] eq "initial"){
    p = "pt 2 ps 1 lc 1 w l"
    # p = "w l"
} else {
    # p = "pt 7 ps 0.5 lc 2 w l"
    p = "pt 7 ps 1 lc 2 w lp"
    # p = "w l"
}
uxy = "using 1:2"
uxz = "using 1:($3*Scale)"
uyz = "using 2:($3*Scale)"
skip_row = ARGV[3] + 1
SectionNumber = ARGV[5] - 1
if ( ARGV[4] eq "i" ){
    # e = "every skip_row::SectionNumber:::"
    e = "every ::SectionNumber::SectionNumber"
    # e = "every ::SectionNumber"
    # e = "every 1::0:"
    u_plane = uxz
    # set xlabel "Y axix" font ",15" offset 0,1
    # set ylabel "Z axix" font ",15" offset 1,0
    set xlabel "Y axix"
    set ylabel "Z axix"
} else {
    e = "every :::SectionNumber::SectionNumber"
    u_plane = uyz
    set xlabel "X axix"
    set ylabel "Z axix"
}
# print(e)
# print(skip_row)
set xrange [-0.2:1.2]
# set xtics 0, 0.2
# set mxtics 2

set key font ",20" spacing 2          # 凡例のフォントサイズ

set term qt 5
set term pngcairo size 1280,960 font ".100"
# set ticslevel 0             # Z軸をXY平面に一致させる
set autoscale y
plot input_file_path @e @u_plane @p title sprintf("%s", export_file)
set output sprintf("%s%s%s%s",export_dir,export_file,"_hoge",ex_extention)
replot

# se t pm3d

# set xlabel "X axis" font ",30" offset 0,1 # x軸ラベルの名前とフォントサイズ, 位置
# set ylabel "Y axis" font ",30" offset 1,0 # y軸ラベルの名前とフォントサイズ, 位置
# set zlabel "Z axis" font ",30" offset -5,0 # z軸ラベルの名前とフォントサイズ, 位置
# set tics font ",25"         # メモリのフォントサイズ
# set key font ",30" spacing 2          # 凡例のフォントサイズ
# set xtics 0, 0.2
# set mxtics 2
# set ytics 0, 0.2
# set mytics 2
# set ztics 0, 0.2
# set mztics 2

# set term qt 1
# set term pngcairo size 1280,960 font ".100"
# set view 0,0,1,1        # Z軸からXY平面を見る
# # set key box lt -1 lw 0        # 凡例を枠で囲む
# # set xrange [xy_range_min:xy_range_max]
# # set yrange [xy_range_min:xy_range_max]
# # set zrange [z_range_min:z_range_max]
# set view equal xyz
# set xlabel offset 0,1
# set ylabel offset 10,-8
# set zlabel offset -5,0
# set ticslevel 0             # Z軸をXY平面に一致させる
# set grid mxtics xtics mytics ytics # gridを作成する
# splot sprintf("%s",input_file_path) @u @e @p title sprintf("%s", export_file))
# set output sprintf("%s%s%s%s",export_dir,export_file,"_xy",ex_extention)
# replot

# set term qt 2
# set term pngcairo size 1280,960 font ".100"
# set view 90,0,1,1        # Y軸からXZ平面を見る
# unset ytics                  # Y軸の目盛りを削除する
# set xtics offset 0,-2                    # X軸目盛りの位置
# set xlabel offset 0,-4                   # x軸の位置
# set ylabel offset -2,-3                   # y軸の位置
# set zlabel offset -8,0
# # set key box lt -1 lw 0        # 凡例を枠で囲む
# # set xrange [xy_range_min:xy_range_max]
# # set yrange [xy_range_min:xy_range_max]
# # set zrange [z_range_min:z_range_max]
# set view equal xyz
# set ticslevel 0             # Z軸をXY平面に一致させる
# splot sprintf("%s",input_file_path) @u @e @p title sprintf("%s", export_file))
# set output sprintf("%s%s%s%s",export_dir,export_file,"_xy",ex_extention)
# replot


# set xtics offset 0,0                    # x軸目盛りの位置
# set ytics font ",25"         # 目盛りのフォントサイズ


# set term qt 3
# set term pngcairo size 1280,960 font ".100"
# # set view 90,90,1,1        # X軸からYZ平面を見る
# set view 90,270,1,1        # X軸からYZ平面を見る 負のX軸に
# # set key box lt -1 lw 0        # 凡例を枠で囲む
# unset xtics                  # Y軸の目盛りを削除する
# set ytics offset 0,-2                    # y軸目盛りの位置
# set ytics 0, 0.2
# set mytics 2

# # set xrange [xy_range_min:xy_range_max]
# # set yrange [xy_range_min:xy_range_max]
# # set zrange [z_range_min:z_range_max]
# set view equal xyz
# set xlabel offset -2,-3
# set ylabel offset 0,-4
# set zlabel offset -8,0
# set ticslevel 0             # Z軸をXY平面に一致させる
# splot sprintf("%s",input_file_path) @u @e @p title sprintf("%s", export_file))
# set output sprintf("%s%s%s%s",export_dir,export_file,"_xy",ex_extention)
# replot

# set xtics font ",20"                 # X軸の目盛り
# set ytics font ",20"                 # Y軸の目盛り
# set ztics font ",20"                 # Z軸の目盛り
# set xtics 0, 0.2
# set mxtics 2


# plot "data.dat" using 2:3 pt 1 title "data1"  +
# plot "data.dat" using 2:3 pt 3 title "data1"  *
# plot "data.dat" using 2:3 pt 2 title "data1"  ●
# plot "data.dat" using 2:3 pt 9 title "data1"  ▲
# print("\n\n\n\n")
