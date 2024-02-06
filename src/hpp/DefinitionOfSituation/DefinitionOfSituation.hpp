// #define __DEBUG__
// #define __STRONG_DEBUG__

// Situation
#define __SolarSail__
// #define __Plate_Revolution__
// #define __DIAGONAL_TENSILE__
// #define __SIMPLE_TENSILE__
// #define __Natural_Frequency__
// #define __Oblique__

// #define __SIMPLE_BEND__
// #define __SIMPLE_PRESSURE__

// #define __SIMPLE_SHARE__
// #define __SUPPORT_SHARE__

// Particle shape
//---------------------------------------
// #define __EQUALLY_DEVIDED__
//#define __UNEQUALLY_DEVIDED__
// #define __SHAPE_CYLINDER__
// #define __SHAPE_CUBE__

// Share situation setting
// 対象面ではせん断力は存在しない
//---------------------------------------
// #define SHARE_BOTTOM_ROTATE
//#define SHARE_BOTTOM_FIXED
// #define SHARE_TOP_ROTATE
//#define SHARE_TOP_FIXED
//#define SHARE_LEFT_ROTATE
// #define SHARE_LEFT_FIXED
//#define SHARE_RIGHT_ROTATE
// #define SHARE_RIGHT_FIXED
//---------------------------------------

// Bend situation setting
//---------------------------------------
// #define BEND_BOTTOM_ROTATE
//#define BEND_BOTTOM_FIXED
// #define BEND_TOP_ROTATE
//#define BEND_TOP_FIXED
//#define BEND_LEFT_ROTATE
// #define BEND_LEFT_FIXED
// #define BEND_RIGHT_ROTATE
//#define BEND_RIGHT_FIXED
//---------------------------------------

// "External Force" situation setting
//---------------------------------------
// #define __SIMPLE_TENSILE__
// #define __SIMPLE_SHARE__
// #define __SIMPLE_BEND__
// #define __SIMPLE_PRESSURE__
// #define __CYLINDER_PRESSURE__
// #define __CUBE_PRESSURE__
// #define __DIAGONAL_TENSILE__
// #define __SIMPLE_COMPRESSION__
//---------------------------------------

//擾乱ありかなしか (set disturbance)
// #define __CONDITION_DISTURBANCE__
// --------------------------------------------- Tensile Set
// -----------------------------------------------------------
// #define __SIMPLE_TENSILE__
// #define __SIMPLE_COMPRESSION__
// // // // //---------------------------------------
// #define __EQUALLY_DEVIDED__

// #define SHARE_RIGHT_ROTATE
// #define SHARE_LEFT_ROTATE
// #define SHARE_TOP_ROTATE
// #define SHARE_BOTTOM_ROTATE

// #define BEND_RIGHT_ROTATE
// #define BEND_LEFT_ROTATE
// #define BEND_TOP_ROTATE
// #define BEND_BOTTOM_ROTATE

// --------------------------------------------- Share Set
// -----------------------------------------------------------
// #define __SIMPLE_SHARE__
// #define __SUPPORT_SHARE__
// #define __EQUALLY_DEVIDED__

// #define SHARE_RIGHT_FIXED
// #define SHARE_LEFT_FIXED
// #define SHARE_TOP_ROTATE
// #define SHARE_BOTTOM_ROTATE

// #define BEND_RIGHT_ROTATE
// #define BEND_LEFT_ROTATE
// #define BEND_TOP_ROTATE
// #define BEND_BOTTOM_ROTATE

// --------------------------------------------- Bend Set
// -----------------------------------------------------------
// #define __SIMPLE_BEND__
// #define __EQUALLY_DEVIDED__

// #define SHARE_RIGHT_ROTATE
// #define SHARE_LEFT_FIXED
// #define SHARE_TOP_ROTATE
// #define SHARE_BOTTOM_ROTATE

// #define BEND_RIGHT_ROTATE
// #define BEND_LEFT_FIXED
// #define BEND_TOP_ROTATE
// #define BEND_BOTTOM_ROTATE

// --------------------------------------------- Pressure Set
// -----------------------------------------------------------
// #define __SIMPLE_PRESSURE__

// #define __EQUALLY_DEVIDED__

// #define SHARE_RIGHT_FIXED
// #define SHARE_LEFT_FIXED
// #define SHARE_TOP_FIXED
// #define SHARE_BOTTOM_FIXED

// #define BEND_LEFT_ROTATE
// #define BEND_RIGHT_ROTATE
// #define BEND_TOP_ROTATE
// #define BEND_BOTTOM_ROTATE

// --------------------------------------------- Diagonal Set
// -----------------------------------------------------------
// #define __DIAGONAL_TENSILE__
// #define __EQUALLY_DEVIDED__

// #define SHARE_RIGHT_ROTATE
// #define SHARE_LEFT_ROTATE
// #define SHARE_TOP_ROTATE
// #define SHARE_BOTTOM_ROTATE

// #define BEND_RIGHT_ROTATE
// #define BEND_LEFT_ROTATE
// #define BEND_TOP_ROTATE
// #define BEND_BOTTOM_ROTATE

// --------------------------------------------- Revolution Set
// -----------------------------------------------------------
// #define __Plate_Revolution__
// #define __EQUALLY_DEVIDED__

// #define SHARE_RIGHT_ROTATE
// #define SHARE_LEFT_ROTATE
// #define SHARE_TOP_ROTATE
// #define SHARE_BOTTOM_ROTATE

// #define BEND_RIGHT_ROTATE
// #define BEND_LEFT_ROTATE
// #define BEND_TOP_ROTATE
// #define BEND_BOTTOM_ROTATE

// --------------------------------------------- Cylinder Pressure Set
// -----------------------------------------------------------
// #define __SHAPE_CYLINDER__
// #define __CYLINDER_PRESSURE__
// #define __CYLINDER_BOUNDARY__

//  option
// #define __BOUNDARY_DETAILS__ // 境界近くの刻みを小さくする
// #define __CYLINDER_NON_BOUNDARY__

// --------------------------------------------- Cube Set
// -----------------------------------------------------------
// #define __SHAPE_CUBE__
// #define __CUBE_PRESSURE__


// --------------------------------------------- special setting
// -----------------------------------------------------------

// #define __GRAVITY__
#define __InputPosition__ // 変形後の粒子位置をcsvファイルから入力する場合のもの
// #define __ContinueAnalysis__ // 以前の解析結果を引き継いで解析を続けるときに宣言する。粒子速度をcsvファイルから入力する
#define __ThermalForce__ // 熱応力を入れるか否か
// #define __ThermalAnalysis__ // ソーラーセイルの変形後の形状を考慮して温度計算するか否か（非均一）エラー出るかもなので、今はコメントアウト外さないようにする.
// #define __CREASE__ // 折り目を考慮するか否か
// #define __CREASESRP__ // 折り目の際に曲げ角度の大きさを考慮して、SRPの修正をする
// #define __CREASECALUCULATION__ //折り目用に新しく配置した粒子で、折り目とは関係ない物の計算用.少しおかしいので今は使わない。
// #define __INPUT_INITIALPOSITION__ // 初期粒子位置をcsvファイルから入力する場合のもの
// #define __INERTIAMOMENT__  // 断面二次モーメントを二次元板と仮定せずに、変形を考慮して計算する。
// #define __CREASESTOP__ //折り目の部分を固定する場合のもの.宣言するときは、ContinueAnalysisをコメントアウトする
//#define __CREASEEXPERIMENT__ // 折り目の検証の際にコメントアウトする
// #define __CREASEDEBUG__ //creaseのテスト用。普段はコメントアウトしとく

// #define __CREASESTRECTH__ //solar sailで対角線を引っ張って折り目を伸ばす場合
