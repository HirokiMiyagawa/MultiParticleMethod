# README

This program for analysis thin film.
Analysis method is Multi Particle Method.

first. if you can't access LINK, this Link is private note. You do search for the title of the link. and it note don't write specific on this research/program.


```toc

```


## Usage
1. set input.csv
	1. `# lines are comments.`
	2. key is File name. please divide "**,**".
	```csvsample.csv
	#Key, SimpleTensile, SimpleShare, ...
	#Shape
	m_iNum, 21, 21, 21, ...
	m_jNum, 21, 21, 21, ...
	```
	> Note: you can choose csv Editor. Excel, VSCode, etc...
	> Comments is not effect any.
	> blank is OK. but need to type ",".
2. compile with ~~makefile~~ [[CMake]]. (It is also possible to compile with Makefile)
	```shell
	$ # on project root directory
	$ ./main.sh
	```
> Note: If you don't want to automate the compilation, check the script
3. run program 
	```shell
	$ ./bin/[ConditionFileName]
	```
	1. otherwise run main.sh. it run under all preset situations.
	```shell
	$ s ./preset.sh
	```
4. 


#### ソースコードpdf出力

pdfの出力には，enscriptそ使用する．（日本語は文字化けします。）

```
make ps
make pdf
```

#### 作成ファイルの削除

```
make clean
```

### Visualization (processing after analysis)

```bash
./src/copy2results
./src/delete_csvfile.sh
```



### 良く使用するコマンド
git の直前コミットとワークツリーで差分を取る
```sh
git diff HEAD^ --name-only | grep -v "doxygen"
```

## Explain This Program

### process of file
`cpp → VirtualParticleCalc → ThicknessCalc → ForceCalc → GetNewCoordinate`
の順番で計算がおこわなれる。

## 出力

実行時間は`./data/time/time1.csv`に格納[ms]

`10653554`





## プロット

コマンドラインで

````
./plt/Cylinder
````


## Folder Tree (ファイル構造)

```
.
├── bin
├── data
│   ├── csv
│   ├── input_files
│   ├── params
│   ├── pdf
│   ├── position
│   └── time
├── Doxygen
│   ├── html
│   │   └── search
│   └── latex
├── src
│   ├── cpp
│   └── hpp
│       ├── Base
│       ├── DefinitionOfSituation
│       ├── Global
│       ├── MultiParticle
│       ├── MyLibrary
│       └── Readcsv
└── visualize
    ├── Excel
    ├── fig
    ├── plot_data
    └── plot_src

```

- root
	- plotGnuplot
		- gnuplotを用いて解析結果を出力する
- archive
	- データの保存先
- bin
	- コンパイル関係
- data
	- 結果や条件などの数字データやソースコードのPDFファイルを格納する
	- よく触る
- Doxygen
	- > C++のプログラムコードから自動でドキュメントを生成してくれるソフト
	- その出力HTMLファイルを格納する
- src
	- 実装したプログラム
- visualize
	- Excel
		- Excelを用いた可視化
		- 「extract_◯◯.sh」の出力「nextValue.dat」「preValue.dat」を利用してExcel上に表記する
	- fig
		- プロット結果
	- plot_data
		- プロットするデータファイル
	- plot_src
		- gnuplotを用いた可視化
	-  extract-data.sh
	- plot用のデータをcsvファイルから抽出する
	- `./data/csv/`直下の解析結果のうち最初と最後の粒子の配置を抽出し、datファイルにする。
	- 区切り文字は「` `」（半角スペース）
	- 仕様が変更されている可能性あり
		-  第1引数：ファイル名の指定
			-  sail or cylinder
		-  第2引数：検索する
		-  第3引数：変形後のファイル名に付いている数字の指定
			-  デフォルトでは最大値（=解析終了値）


#### extract-3files.sh

1.  `./data/position` の`c_x.dat`, `c_y.dat`, `c_z.dat`から任意のTimeの行を`old_xyz.dat`にコピペする。（x,y,zの順番で3列）
2.  `extract-3files.sh`を実行する
3.  `$plot_dir`に`x y z`座標をスペース区切りで格納されたdatファイルを出力する





### src

実際のプログラム



### tmp

実験結果などの一時的な待機場



## src

### 荷重係数 $k$

この値を決めることで$Eh_0$によらず、たわみ量が決定される



## Analysis Conditions

### SimpleTensile

$$F=kEh_0$$

$$\varepsilon_x = k$$

$$\varepsilon_y = -\nu k$$





### SimpleShare

$$F=kEh_0$$

$$\gamma = 2(1+\nu) k$$





### SimpleBend

$$F=kEh_0$$

$$\frac{\delta}{L_{ref}} = 4k(\frac{L_{ref}}{h_0})^2$$



### Physical value

Steel

| Label  | value            | Unit       |
| ------ | ---------------- | ---------- |
| E      | $2\times10^{11}$ | $[N/m^2]$  |
| $\nu$  | $0.3$          | $[-]$      |
| $\rho$ | $7860$           | $[kg/m^3]$ |




## Animation

### animation作成プログラム

c++とgnuplotによるアニメーションの作成を行った．graph.shによって読み込ませるデータを作成し，描画していく，

#### main.cpp



```cpp
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <cassert>
 
using namespace std;
 
bool checkFileExistence( const string& str ) {
	ifstream ifs( str.c_str() );
	return ifs.is_open();
}
 
 
int main(){
	FILE *gp = popen("gnuplot", "w");
	assert(gp);
 
	fprintf(gp, "set terminal gif animate optimize delay 10 size 1200,900\n");
	fprintf(gp, "set zeroaxis lt -1 lw 2\n");
	fprintf(gp, "unset xlabel\n");
	fprintf(gp, "unset ylabel\n");
	fprintf(gp, "unset title\n");
	fprintf(gp, "unset key\n");
	fprintf(gp, "set output 'tmp.gif'\n");
 
	fprintf(gp, "set nokey\n");
	fprintf(gp, "set grid\n");
	fprintf(gp, "set size ratio -1\n");
	fprintf(gp, "set xr [0:1.25]\n");
	fprintf(gp, "set yr [0:0.7]\n");
 
	string file1 = "data.dat";
	string file2 = "reverse.dat";
	ifstream *ifs1;
	ifstream *ifs2;
	char buf[50];
 
	for( int j=1; j < 550; j++ ){
		system("rm ./data.dat");
		system("rm ./reverse.dat");
		sprintf(buf,"sh graph.sh %d", j);
		cout << buf << endl;
		cout << flush;
		system(buf);
 
		ifs1 = new ifstream(file1, ios::in);
		while ( !*ifs1 ) {
			usleep(500000);
		}
		ifs1->close();
		delete ifs1;
 
		ifs2 = new ifstream(file2, ios::in);
		while ( !*ifs2 ) {
			usleep(500000);
		}
		ifs2->close();
		delete ifs2;
 
		while( fprintf(gp, "plot 'reverse.dat' using 1:2 with points pt 65 ps 1 lc rgb '#000000' lw 2 lt 1\n") < 0){
			usleep(500000);
		}
 
		while( fflush(gp) != 0 ) {
			usleep(500000);
		}
 
	}
	pclose(gp);
 
	return 0;
}
 
```


## Basic Data
### 開発環境
開発環境は以下の環境で行った，
動作確認行い済み．

#### Hardware

|            |       |
|------------|-------|
| CPU        | Intel(R) Core(TM) i5-9600K CPU @ 3.70(4.60)GHz |
| core       | 6 core 6thread|
| Mother Board | ASRock Z390 Extreme4 |
| Memory     | 16GB |

#### Software

|                 |                       |
| ------------------- | --------------------- |
| OS                  | Windows 10 21H1       |
| OS (WSL2)           | Ubuntu 18.04 LTS      |
| kernel              | 4.4.0-17763-Microsoft |
| Programing Language | C++                   |
| Compiler            | GNU compiler          |

Either WSL version 1 or 2 is fine.
WSL1: faster
WLS2: Active development.



### 作成者
スペースダイナミクス研究室 修士2年　大倉　輝久

### 作成日時
令和4年度卒業研究プログラム
最終更新日2022年2月

[GitHub Pages](https://github.com/okura-teruhsia/ThreeDemention_MultiParticle.git)



## References


