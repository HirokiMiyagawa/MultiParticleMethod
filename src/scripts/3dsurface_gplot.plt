# data_dir内のdatファイルからexport_dirにプロットする
# ARGV[1] x&y range-min
# ARGV[2] x&y range-max
# ARGV[3] z range-min 
# ARGV[4] z range-max 
# ARGV[5] shape (check file name & plot.sh)
# ARGV[6] initial / deformation
# ARGV[7] zscalar
# ARGV[8] plot mode
# ARGV[9] 

if ( ARGV[7] < 0 ){
    sprintf("$s", "Z scale ≦ 0. Please enter 0 < Z scale")
    exit
}

xy_range_min = ARGV[1]
xy_range_max = ARGV[2]
z_range_min = ARGV[3]
z_range_max = ARGV[4]
plot_mode = ARGV[8]
print(plot_mode)

# HACK: Don't work!!
set term qt 0 font "/usr/share/fonts/truetype/noto/NotoMono-Regular.ttf, 12"
# 区切り文字を指定する
set datafile separator ','

export_file = sprintf("%s%s%s", ARGV[5], "_" ,ARGV[6])
data_dir = "visualize/plot_data/"
export_dir ="visualize/fig/"
extention = ".csv"
ex_extention = ".png"


# コンターカラーを変更
set palette rgbformulae 22, 13, -31

# screen一杯にrgbで指定した背景を置く (set background color)
# set object 1 rect behind from screen 0,0 to screen 1,1 fc rgb "#F5F5F5" fillstyle solid 1.0     # Background color: snow
# set object 1 rect behind from screen 0,0 to screen 1,1 fc rgb "#fcefcd" fillstyle solid 1.0     # Background color: sepia


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
Scale=ARGV[7]   # Z軸の倍率を定める
u = "using 1:2:($3*Scale)"

if (ARGV[6] eq "initial"){
    p = "pt 2 ps 1 lc 1 w l"
    # p = "w l"
} else {
    p = "pt 7 ps 0.5 lc 2 w l"
    # p = "w l"
}
if (plot_mode eq "gray"){
    # 図表用
    p = "pt 2 ps 1 lc \"black\" w l"
    set palette gray
    unset colorbox
    unset key
}

# 仮想粒子
# uv1 = "using 1:2:($3*Scale)"     # Bottom
# uv2 = "using 4:5:($6*Scale)"     # Top
# uv3 = "using 7:8:($9*Scale)"     # Left
# uv4 = "using 10:11:($12*Scale)"  # Right
# pv = "pt 3 ps 0.3 lc 1"

# 縦横の比を統一する
# set size ratio -1
# 原点を表示する？
# set zero 1e-20
# 視点を回転させる
# set view 30,10,1,1
# set view 80,20,1,1

# set pm3d at b
if ( plot_mode eq "gray"){
}else{
    set pm3d
}

# set hidden3d
# set palette defined (0 "green", 1 "green")
# set palette defined (400 "purple", 475 "blue", 510 "green", 570 "yellow", 590 "orange", 650 "red", 675 "dark-red", 700 "black")
# splot [400:700][0:1] x



set term qt 1
set term pngcairo size 1280,960 font ".100"
set view 0,0,1,1        # Z軸からXY平面を見る
# set key box lt -1 lw 0        # 凡例を枠で囲む
set xrange [xy_range_min:xy_range_max]
set yrange [xy_range_min:xy_range_max]
set zrange [z_range_min:z_range_max]
set view equal xyz
set xlabel offset 0,1
set ylabel offset 10,-8
set zlabel offset -5,0
set ticslevel 0             # Z軸をXY平面に一致させる
set grid mxtics xtics mytics ytics # gridを作成する
splot sprintf("%s%s%s",data_dir,export_file,extention) @u @p title ARGV[6]
set output sprintf("%s%s%s%s",export_dir,export_file,"_xy",ex_extention)
replot

set term qt 2
set term pngcairo size 1280,960 font ".100"
set view 90,0,1,1        # Y軸からXZ平面を見る
unset ytics                  # Y軸の目盛りを削除する
set xtics offset 0,-2                    # X軸目盛りの位置
set xlabel offset 0,-4                   # x軸の位置
set ylabel offset -2,-3                   # y軸の位置
set zlabel offset -8,0
# set key box lt -1 lw 0        # 凡例を枠で囲む
set xrange [xy_range_min:xy_range_max]
set yrange [xy_range_min:xy_range_max]
set zrange [z_range_min:z_range_max]
set view equal xyz
set ticslevel 0             # Z軸をXY平面に一致させる
splot sprintf("%s%s%s",data_dir,export_file,extention) @u @p title ARGV[6]
set output sprintf("%s%s%s%s",export_dir,export_file,"_xz",ex_extention)
replot


set xtics offset 0,0                    # x軸目盛りの位置
set ytics font ",25"         # 目盛りのフォントサイズ


set term qt 3
set term pngcairo size 1280,960 font ".100"
# set view 90,90,1,1        # X軸からYZ平面を見る
set view 90,270,1,1        # X軸からYZ平面を見る 負のX軸に
# set key box lt -1 lw 0        # 凡例を枠で囲む
unset xtics                  # Y軸の目盛りを削除する
set ytics offset 0,-2                    # y軸目盛りの位置
set ytics 0, 0.2
set mytics 2

set xrange [xy_range_min:xy_range_max]
set yrange [xy_range_min:xy_range_max]
set zrange [z_range_min:z_range_max]
set view equal xyz
set xlabel offset -2,-3
set ylabel offset 0,-4
set zlabel offset -8,0
set ticslevel 0             # Z軸をXY平面に一致させる
splot sprintf("%s%s%s",data_dir,export_file,extention) @u @p title ARGV[6]
set output sprintf("%s%s%s%s",export_dir,export_file,"_yz",ex_extention)
replot

set xtics font ",20"                 # X軸の目盛り
set ytics font ",20"                 # Y軸の目盛り
set ztics font ",20"                 # Z軸の目盛り
set xtics 0, 0.2
set mxtics 

# 鳥瞰で出力する
set term qt 4
set term pngcairo size 1280,960 font ".100"
# set view 80,20,0.7,1            # 鳥瞰する (Cube or Cylinder)
set view 80,20,0.7,5            # 鳥瞰する
if (plot_mode eq "gray"){
    # set view 60,15,0.9,5 # compression
    set view 80,20,0.7,5
}
set xtics offset 0,-2                    # X軸目盛りの位置
set ytics offset 0,0                    # Y軸目盛りの位置
set xlabel offset 0,-5                   # x軸の位置
set ylabel offset 10,0                   # y軸の位置
set zlabel offset -8,0                   # z軸の位置
# set key box lt -1 lw 0        # 凡例を枠で囲む
if (plot_mode eq "gray"){
    unset tics
    unset xlabel
    unset ylabel
    unset zlabel
    set ticslevel 3 
}
set xrange [xy_range_min:xy_range_max]
set yrange [xy_range_min:xy_range_max]
set zrange [z_range_min:z_range_max]
set view equal xyz
splot sprintf("%s%s%s",data_dir,export_file,extention) @u @p title ARGV[6]
set output sprintf("%s%s%s",export_dir,export_file,ex_extention)
replot


# if (ARGV[6] eq "deformation"){
#     # 動かせる画面も表示する。
#     # TODO: 現状動かない + 目盛りタイトルが表示されない
#     # set term qt 5 font "/usr/share/fonts/truetype/noto/NotoMono-Regular.ttf, 12"
#     set term qt 5
#     set xtics offset 0,0                    # X軸目盛りの位置
#     set ytics offset 0,0                    # Y軸目盛りの位置
#     set ztics offset 0,0                    # Z軸目盛りの位置                    
#     set xlabel offset 0,-5                   # x軸の位置
#     set ylabel offset 10,0                   # y軸の位置
#     set zlabel offset -8,0                   # z軸の位置
#     # set key box lt -1 lw 0        # 凡例を枠で囲む
#     set xrange [xy_range_min:xy_range_max]
#     set yrange [xy_range_min:xy_range_max]
#     set zrange [z_range_min:z_range_max]
#     set view equal xyz
#     # splot sprintf("%s%s%s",data_dir,export_file,extention) @u @p title ARGV[6]
#     splot sprintf("%s%s%s",data_dir,export_file,extention) @u @p
#     replot
# }

# plot "data.dat" using 2:3 pt 1 title "data1"  +
# plot "data.dat" using 2:3 pt 3 title "data1"  *
# plot "data.dat" using 2:3 pt 2 title "data1"  ●
# plot "data.dat" using 2:3 pt 9 title "data1"  ▲
# print("\n\n\n\n")
