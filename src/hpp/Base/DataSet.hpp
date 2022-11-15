/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file
 * @brief
 * @details
 * ///////////////////////////////////////////////////////////////////////////////
 */

// Enumerated type define
//---------------------------------------
#ifndef __DATASET_HPP__
#define __DATASET_HPP__



#include "InputParam.hpp"
#include <vector>  // 動的配列
using std::vector;

// #if defined(__SIMPLE_TENSILE__) || defined(__SIMPLE_BEND__) ||
//     defined(__SIMPLE_SHARE__) || defined(__SIMPLE_PRESSURE__) ||
//     defined(__CYLINDER_PRESSURE__) || defined(__CYLINDER_PRESSURE__) ||
//     defined(__DIAGONAL_TENSILE__)
enum Positions {
    Center = 0b00000000,
    Right  = 0b00000001,
    Left   = 0b00000010,
    Bottom = 0b00000100,
    Top    = 0b00001000,

    RightBottom = 0b00000101,
    RightTop    = 0b00001001,
    LeftBottom  = 0b00000110,
    LeftTop     = 0b00001010,

    Crease = 0b10000000,//折り目

    // Center = 0x00,
    // Left   = 0x01,
    // Right  = 0x02,
    // Bottom = 0x03,
    // Top    = 0x04,

    // LeftBottom  = 0x05,
    // LeftTop     = 0x06,
    // RightBottom = 0x07,
    // RightTop    = 0x08,
};
// #elif defined __SHAPE_CUBE__
// Bit演算用
const unsigned int BIT_RIGHT     = (1 << 0);
const unsigned int BIT_LEFT      = (1 << 1);
const unsigned int BIT_BOTTOM    = (1 << 2);
const unsigned int BIT_TOP       = (1 << 3);
const unsigned int BIT_RIGHTSIDE = (1 << 4);
const unsigned int BIT_BACK      = (1 << 5);
const unsigned int BIT_CEILING   = (1 << 6);
const unsigned int BIT_EDGE      = (1 << 7);
const unsigned int BIT_NONE      = 0b00000000;

// enum Positions {
//     // Center = 0b00000000,
//     None = 0b00000000,
//     Left = 0b00000010,
//     Right = 0b00000001,
//     Top = 0b00001000,
//     Bottom = 0b00000100,

//     BitLeft = 1,
//     BitRight = 0,
//     BitTop = 3,
//     BitBottom = 2,

//     LeftBottom = 0b00000110,
//     LeftTop = 0b00001010,
//     RightBottom = 0b00000101,
//     RightTop = 0b00001001,

//     // 右サイド 0001
//     BitRightSide = 4,
//     RightSideCenter = 0b00010000,
//     RightSideLeft = 0b00010010,
//     RightSideRight = 0b00010001,
//     RightSideTop = 0b00011000,
//     RightSideBottom = 0b00010100,

//     RightSideLeftBottom = 0b00010110,
//     RightSideLeftTop = 0b00011010,
//     RightSideRightBottom = 0b00010101,
//     RightSideRightTop = 0b00011001,

//     // バック 0010
//     BitBack = 5,
//     BackCenter = 0b00100000,
//     BackLeft = 0b00100010,
//     BackRight = 0b00100001,
//     BackTop = 0b00101000,
//     BackBottom = 0b00100100,

//     BackLeftBottom = 0b00100110,
//     BackLeftTop = 0b00101010,
//     BackRightBottom = 0b00100101,
//     BackRightTop = 0b00101001,

//     // 天井 0100
//     BitCeiling = 6,
//     CeilingCenter = 0b01000000,
//     CeilingLeft = 0b01000010,
//     CeilingRight = 0b01000001,
//     CeilingTop = 0b01001000,
//     CeilingBottom = 0b01000100,

//     CeilingLeftBottom = 0b01000110,
//     CeilingLeftTop = 0b01001010,
//     CeilingRightBottom = 0b01000101,
//     CeilingRightTop = 0b01001001,

// };
// #endif

struct MoveXYZ {
    bool x;
    bool y;
    bool z;
};

struct BoundaryCondition {
    bool right_share_fix;
    bool right_bend_fix;
    bool right_free;
    // bool right_share_rotate;
    // bool right_bend_rotate;

    bool left_share_fix;
    bool left_bend_fix;
    bool left_free;
    // bool left_share_rotate;
    // bool left_bend_rotate;

    bool top_share_fix;
    bool top_bend_fix;
    bool top_free;
    // bool top_share_rotate;
    // bool top_bend_rotate;

    bool bottom_share_fix;
    bool bottom_bend_fix;
    bool bottom_free;
    // bool bottom_share_rotate;
    // bool bottom_bend_rotate;

    MoveXYZ right_move;
    MoveXYZ left_move;
    MoveXYZ top_move;
    MoveXYZ bottom_move;
    bool cylinder_boundary;
    bool boundary_more_detail;

    template <class T>
    bool contain(const std::string& s, const T& v) {
        return s.find(v) != std::string::npos;
    }
    void judge_xyz_fix(MoveXYZ& xyz, const string& judge_strring) {
        xyz.x = contain<string>(judge_strring, "x");
        xyz.y = contain<string>(judge_strring, "y");
        xyz.z = contain<string>(judge_strring, "z");
    }
    string get_boundary_move(const MoveXYZ& xyz) {
        string Ret;
        if (xyz.x) {
            Ret += "x";
        }
        if (xyz.y) {
            Ret += "y";
        }
        if (xyz.z) {
            Ret += "z";
        }
        return Ret;
    }

    void set_param(const string& filename) {
        param::parameter read(filename);
        cylinder_boundary    = read.get<bool>("cylinder_boundary", false);
        boundary_more_detail = read.get<bool>("boundary_more_detail", false);

        right_bend_fix  = read.get<bool>("RightBend");
        left_bend_fix   = read.get<bool>("LeftBend");
        bottom_bend_fix = read.get<bool>("BottomBend");
        top_bend_fix    = read.get<bool>("TopBend");

        right_share_fix  = read.get<bool>("RightShare");
        left_share_fix   = read.get<bool>("LeftShare");
        bottom_share_fix = read.get<bool>("BottomShare");
        top_share_fix    = read.get<bool>("TopShare");

        judge_xyz_fix(right_move, (read.get<string>("RightMove")));
        judge_xyz_fix(left_move, (read.get<string>("LeftMove")));
        judge_xyz_fix(top_move, (read.get<string>("TopMove")));
        judge_xyz_fix(bottom_move, (read.get<string>("BottomMove")));
    }
};

enum Communication { Send  = 0x01,
                     Recv  = 0x02,
                     Empty = 0x03 };
//---------------------------------------

// Structure define
//---------------------------------------

/**
 * @brief	x,y,z方向に値を持つ
 */
class C {
   public:
    double x, y, z;

    // constructor
    C(void);
    C(const int&, const int&, const int&);
    C(const double&, const double&, const double&);

    // operators
    C& operator=(const C&);
    C& operator=(const int&);
    C& operator+=(const C&);
    C& operator-=(const C&);
    C& operator*=(const double&);
    C& operator/=(const int&);

    // frind operators
    friend C operator+(const C&);
    friend C operator-(const C&);
    friend C operator+(const C&, const C&);
    friend C operator-(const C&, const C&);
    friend C operator*(const C&, const C&);
    friend double operator%(const C&, const C&);

    friend C operator*(const double&, const C&);
    friend C operator*(const C&, const double&);
    friend C operator*(const C&, const int&);
    friend C operator/(const C&, const double&);
    friend C operator/(const C&, const int&);

    // member functions
    void set(const double&, const double&, const double&);
    void set(const int&, const int&, const int&);
    void set(const vector<double>&);
    void set(void);
    void reset(void);
    void print(void);
    vector<double> out_array(void);

    double abs2(void) const;
    double abs(void) const;
    C unit(void) const;
    double gamma(void) const;
    double ugamma(void) const;

    friend C cross(const C&, const C&);
    friend double dot(const C&, const C&);
    friend double abs(const C&);
    friend void print(const C&);
};
// ---- constructor ----
C::C(void) : x(0.0), y(0.0), z(0.0) {}
C::C(const int& _x, const int& _y, const int& _z)
    : x(double(_x)), y(double(_y)), z(double(_z)) {}
C::C(const double& _x, const double& _y, const double& _z)
    : x(_x), y(_y), z(_z) {}

// ---- operators ----
inline C& C::operator+=(const C& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}
inline C& C::operator-=(const C& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

// unary operators
inline C& C::operator=(const C& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}
inline C& C::operator=(const int& v) {
    x = v;
    y = v;
    z = v;
    return *this;
}
inline C& C::operator*=(const double& d) {
    x *= d;
    y *= d;
    z *= d;
    return *this;
}
inline C& C::operator/=(const int& i) {
    x /= i;
    y /= i;
    z /= i;
    return *this;
}

inline C operator+(const C& v) { return v; }
inline C operator-(const C& v) { return C(-v.x, -v.y, -v.z); }
inline C operator+(const C& a, const C& b) {
    return C(a.x + b.x, a.y + b.y, a.z + b.z);
}
inline C operator-(const C& a, const C& b) {
    return C(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline C operator*(const double& d, const C& v) {
    return C(d * v.x, d * v.y, d * v.z);
}

inline C operator*(const C& v, const double& d) {
    return C(d * v.x, d * v.y, d * v.z);
}
// Cross product
inline C operator*(const C& a, const C& b) {
    return C(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
             a.x * b.y - a.y * b.x);
}
// InnerProduct
inline double operator%(const C& a, const C& b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline C operator*(const C& v, const int& i) {
    double d = (double)i;
    return C(d * v.x, d * v.y, d * v.z);
}

inline C operator/(const C& v, const double& d) {
    return C(v.x / d, v.y / d, v.z / d);
}
inline C operator/(const C& v, const int& i) {
    double d = (double)i;
    return C(v.x / d, v.y / d, v.z / d);
}

// ---- member functions ----
void C::set(const double& _x, const double& _y, const double& _z) {
    x = _x;
    y = _y;
    z = _z;
}
void C::set(const int& _x, const int& _y, const int& _z) {
    x = (double)_x;
    y = (double)_y;
    z = (double)_z;
}
void C::set(const vector<double>& xyz) {
    set(xyz[0], xyz[1], xyz[2]);
}
void C::set(void) {
    x = 0.0;
    y = 0.0;
    z = 0.0;
}
void C::reset(void) {
    x = 0.0;
    y = 0.0;
    z = 0.0;
}
void C::print(void) { cout << x << ',' << y << ',' << z << endl; }
vector<double> C::out_array(void) {
    vector<double> Ret = {
        x,
        y,
        z,
    };
    return Ret;
}
inline double C::abs2(void) const { return (x * x + y * y + z * z); }
inline double C::abs(void) const { return sqrt(x * x + y * y + z * z); }
inline C C::unit(void) const {
    double norm = sqrt(x * x + y * y + z * z);
    if (norm == 0) {
        return C(0, 0, 0);
    }
    return C(x / norm, y / norm, z / norm);
    // C Ret(x, y, z);
    // Ret /= norm;
    // return Ret;
}
inline double C::gamma(void) const {
    return 1.0 / sqrt(1.0 - x * x + y * y + z * z);
}
inline double C::ugamma(void) const {
    return sqrt(1.0 + x * x + y * y + z * z);
}

C cross(const C& a, const C& b) { return (a * b); }
double dot(const C& a, const C& b) { return (a % b); }
double abs(const C& v) { return v.abs(); }
void print(const C& v) { cout << v.x << ',' << v.y << ',' << v.z << endl; }

// C(void);
// C(const double&, const double&, const double&);
// C(const int&, const int&, const int&);

// operator
// C& operator+(C ci) {
//     x += ci.x;
//     y += ci.y;
//     z += ci.z;
// }

// C operator*(double sc) {
//     C cRet;

//     cRet.x = x * sc;
//     cRet.y = y * sc;
//     cRet.z = z * sc;

//     return cRet;
// }
// };

// C operator*(double sc, C ci) {
//     C c;
//     c.x = ci.x * sc;
//     c.y = ci.y * sc;
//     c.z = ci.z * sc;
//     return c;
// }

/**
 * @brief   i,j方向にプラスマイナスの構造体
 * @note    せん断角度 β、せん断ひずみ γ、せん断力 Fsで使用する
 */
struct Quarter {
    double pp;
    double pm;
    double mp;
    double mm;
    Quarter& operator=(const Quarter&);
};
inline Quarter& Quarter::operator=(const Quarter& q) {
    pp = q.pp;
    pm = q.pm;
    mp = q.mp;
    mm = q.mm;
    return *this;
}

/**
 * @brief   i,j方向にプラスマイナスの構造体
 * @note    曲げによる力を格納する 曲げによる力Fb
 */
struct PreDirection {
    double ipv;
    double imv;
    double jpv;
    double jmv;
    C ipmv;
    C jpmv;
};

/**
 * @brief	iとjのプラマイ方向を2つずつ格納する
 * @note	合力で使用する (F)
 */
struct Direction {
    double ip;
    double im;
    double jp;
    double jm;

    double sv;
    double ipv;
    double imv;
    double jpv;
    double jmv;
};

/**
 * @brief ベクトルと長さを格納する
 */
struct Vector {
    C vector;
    double norm;
};

/**
 * @brief	i, jのx,y,z方向成分
 */
struct Area {
    C i;
    C j;
    //!	cross productの略。vector i, vector jの外積 cpベクトルを格納する (Normal Vector)
    Vector cp;

    //! transverse vector in i
    // Vector ti;
    //! transverse vector in j
    // Vector tj;
};

/**
 * @brief	一時的に使用する構造体
 * @note
 * switch文内で新しく関数を宣言することができないので、switch文外で宣言する必要があり、
 * 			tmpを様々な場所に配置すると処理の把握が困難になると思われるので、tmp関数を全てこの構造体で賄う
 */
struct Tmp {
    Vector vec;
    Vector vec2;
    Vector vec3;
    C vc_coordinates;
};

/**
 * @brief	stock outer most parameter. we use it when Non Cylinder Boundary
 * @note
 */
struct OuterMostParameter {
    C mi;
    C mi0;
    C mj;
    C g;
    C g0;
    C ci;
    C cj;
    Vector lj;
    Vector li;
    double lj0;
    double li0;
    double epsilonli;
    double epsilongj;
    double S0;
    double Si0;
    double Sj0;
    Area S;
    Area Si;
    Area Sj;
    double hi;
    double Fti;
    Quarter beta;
    Quarter beta0;
    Quarter gamma;
    Quarter Fsi;
    // Quarter Fsj;
};

/**
 * @brief	仮想粒子関係の計算結果を格納する構造体
 * @note
 * 仮想粒子に関係する値がどれなのか不明瞭になってきたため、まとめることにした
 */
struct VirtualParticle {
    //! Rightの座標 Virtual Particle Coordinate
    C vpc_Right;
    //! Leftの座標 Virtual Particle Coordinate
    C vpc_Left;
    //! Topの座標 Virtual Particle Coordinate
    C vpc_Top;
    //! Bottomの座標 Virtual Particle Coordinate
    C vpc_Bottom;
    //! i方向成分の中間点
    C mi;
    //! j方向成分の中間点
    C mj;
};

#endif
