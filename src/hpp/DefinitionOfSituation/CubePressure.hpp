/**
 * @file        CylinderPressure.hpp
 * @brief       円筒の1/4モデルに内圧を作用したシミュレーション
 */

// Share situation setting
//---------------------------------------
// #define __EQUALLY_DEVIDED__
// #define __UNEQUALLY_DEVIDED__
// #define __SHAPE_CYLINDER__
// #define __SHAPE_CUBE__

// Share situation setting
// 対象面ではせん断力は存在しない
//---------------------------------------
// #define SHARE_BOTTOM_FIXED
// #define SHARE_TOP_FIXED
// #define SHARE_LEFT_FIXED
// #define SHARE_RIGHT_FIXED
//---------------------------------------

// Bend situation setting
//---------------------------------------
// #define BEND_BOTTOM_ROTATE
// #define BEND_TOP_ROTATE
// #define BEND_LEFT_ROTATE
// #define BEND_RIGHT_ROTATE
//---------------------------------------

// "External Force" situation setting
//---------------------------------------
// #define __SIMPLE_PRESSURE__
// #define __CYLINDER_PRESSURE__
#define __CUBE_PRESSURE__
// constexpr bool CubePressure = ture;
//---------------------------------------

// #define EDGE_REINFORCE
// #define Thicken
