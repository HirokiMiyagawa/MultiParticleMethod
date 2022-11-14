/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file	MatrixCalc.hpp
 * @brief	行列に関わる基本的な計算を行う。
 *
 * @par
 * @date Create 2021-07-04<br>
 * @date last update 2021-07-04
 * @author raptel
 * ///////////////////////////////////////////////////////////////////////////////
 */

#ifndef MatrixCalc_hpp
#define MatrixCalc_hpp

/* include header files */

/* end include header files*/

/* include standard files */
#include <iostream>   // for debug writing
#include <string>     // useful for reading and writing
#include <vector>     // 動的配列
#include <algorithm>  // vectorの最大値を取得する
#include <cmath>      // fabs

#include <fstream>  // ifstream, ofstream
#include <sstream>  // istringstream

/* end include standard files */

/* usingnamespace declaration(名前空間の宣言) */
using std::cout;
using std::endl;
using std::flush;
using std::string;
using std::vector;
/* end usingnamespace declaration*/

/* declaration MACRO */

/* end declaration MACRO */

/* prototype declaration */
class Matrix;  // クラスの前方宣言

/* end prototype declaration*/

/* declaration enumlation */
/**
 * @brief       ソートモードを指定する
 * @param[in] 	vector<double> matrixA
 * @note
 * @typedef choose the criteria for sorting eigenvalues and eigenvectors
 */
typedef enum {
    DO_NOT_SORT,
    SORT_DECREASING_ARRAY,
    SORT_INCREASING_ARRAY,
    SORT_DECREASING_ABS_ARRAY,
    SORT_INCREASING_ABS_ARRAY
} SortMode;

/* declaration namespace */

/* end declaration namespace */
class MatrixCalc;
class RotationMatrixCalc;

/**
 * @brief       行列を扱うクラス
 * @note
 */
class MatrixCalc {
    // vector<vector<double>> matrix;
   public:
    double innerProductCalc(vector<double> const& matrixA,
                            vector<double> const& matrixB);  // 内積を求める。
    void plusMatrix(vector<double> const& mA, vector<double> const& mB,
                    vector<double>& plusres);  // 行列の足し算
    void minMatrix(vector<double> const& mA, vector<double> const& mB,
                   vector<double>& minres);  // 行列の引き算
    double matrixProduct(vector<double> const& matrixA,
                         vector<double> const& matrixB);  // nx1 1xn 行列の積
    void matrixProduct(vector<vector<double>> const& matrixA,
                       vector<double> const& matrixB,
                       vector<double>& out_matrix);  // 行列の積
    void matrixProduct(vector<vector<double>> const& matrixA,
                       vector<vector<double>> const& matrixB,
                       vector<vector<double>>& out_matrix);  // 行列の積
    vector<double> matrixProductCalc(const vector<vector<double>>& matrixA,
                                     const vector<double>& matrixB);  // 行列の積
    vector<vector<double>> matrixProductCalc(const vector<vector<double>>& matrixA,
                                             const vector<vector<double>>& matrixB);  // 行列の積
    vector<vector<double>> transpose_matrix(const vector<vector<double>>&);
    void printMatrix(vector<double> const& v);          // 行列を表示する
    void printMatrix(vector<vector<double>> const& v);  // 行列を表示する
    void matrixScalarProduct(
        double const& scalar, vector<double> const& in_matrix,
        vector<double>& out_matrix);  // 行列の全要素をx倍する
    void matrixScalarDiv(
        double const& scalar, vector<double> const& in_matrix,
        vector<double>& out_matrix);  // 行列の全要素を1/x倍し、係数を返す
    double maxMatrix(vector<vector<double>> const& in_matrix, double& max_value,
                     int& maxi,
                     int& maxj);  // 行列の全要素の最大値を返す。
    double maxMatrix_n(vector<vector<double>> const& in_matrix, double& max_value,
                       int& maxi,
                       int& maxj);  // 行列の全要素の最大値を返す。
    void SortRows(vector<double>& arr, vector<vector<double>>& vec,
                  SortMode const& sort_mode);  // 配列、行列をソートする。
};

/**
 * @brief        内積を計算する
 * @param[in] 	vector<double> matrixA
 * @param[in] 	vector<double> matrixB
 * @return		double 内積
 * @note
 */
double MatrixCalc::innerProductCalc(vector<double> const& matrixA, vector<double> const& matrixB) {
    double outnum = 0;
    int size      = matrixA.size();  // matrixAの要素数を格納する

    for (int i = 0; i < size; i++) {
        outnum += matrixA[i] * matrixB[i];
    }
    return outnum;
}

/**
 * @brief       行列の足し算
 * @param[in]   mA
 * @param[in]   mB
 * @param[out]  plusres
 * @note
 */
void MatrixCalc::plusMatrix(vector<double> const& mA, vector<double> const& mB, vector<double>& plusres) {
    int size = mA.size();  // vectorAの要素数を格納する

    for (int i = 0; i < size; i++) {
        plusres[i] = mA[i] + mB[i];
    }
}

/**
 * @brief       行列の引き算
 * @param[in]   mA
 * @param[in]   mB
 * @param[out]  minres
 * @note
 */
void MatrixCalc::minMatrix(vector<double> const& mA, vector<double> const& mB, vector<double>& minres) {
    int size = mA.size();  // vectorAの要素数を格納する

    for (int i = 0; i < size; i++) {
        minres[i] = mA[i] - mB[i];
    }
}

/**
 * @brief       1xn と nx1 行列の積
 * @param[in]   matrixA 1xn行列
 * @param[in]   matrixB nx1行列
 * @return double
 * @note
 */
double MatrixCalc::matrixProduct(vector<double> const& matrixA, vector<double> const& matrixB) {
    int size   = matrixA.size();  // in_matrixの要素数を格納する
    double out = 0;

    for (int i = 0; i < size; i++) {
        out += matrixA[i] * matrixB[i];
    }
    return out;
}

/**
 * @brief       nxn と nx1 行列の積
 * @param[in]   matrixA nxn行列
 * @param[in]   matrixB nx1行列
 * @param[out]  out_matrix  nx1行列
 * @note
 */
void MatrixCalc::matrixProduct(vector<vector<double>> const& matrixA, vector<double> const& matrixB, vector<double>& out_matrix) {
    int size = matrixA.size();  // matrixAの要素数を格納する

    for (int i = 0; i < size; i++) {
        out_matrix[i] = 0;  // 初期化
        for (int j = 0; j < size; j++) {
            out_matrix[i] += matrixA[i][j] * matrixB[j];
        }
    }
}

/**
 * @brief       nxm と mxn 行列の積
 * @param[in]   matrixA nxn行列
 * @param[in]   matrixB nx1行列
 * @param[out]  out_matrix  nx1行列
 * @note
 */
void MatrixCalc::matrixProduct(vector<vector<double>> const& matrixA, vector<vector<double>> const& matrixB, vector<vector<double>>& out_matrix) {
    int size = matrixA.size();  // matrixAの要素数を格納する

    int n_rows = matrixA.size();
    int n_cols = matrixA[0].size();

    out_matrix.assign(n_rows, vector<double>(n_cols, 0));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            out_matrix[i][j] = matrixA[i][j] * matrixB[j][i];
        }
    }
}

/**
 * @brief       nxn と nx1 行列の積
 * @param[in]   matrixA nxn行列
 * @param[in]   matrixB nx1行列
 * @return      out_matrix  nx1行列
 * @note
 */
vector<double> MatrixCalc::matrixProductCalc(const vector<vector<double>>& matrixA, const vector<double>& matrixB) {
    int size = matrixA.size();  // matrixAの要素数を格納する

    vector<double> out_matrix(size, 0);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            out_matrix[i] += matrixA[i][j] * matrixB[j];
        }
    }
    return out_matrix;
}
/**
 * @brief       nxn と nxn 行列の積
 * @param[in]   matrixA nxn行列
 * @param[in]   matrixB nxn行列
 * @return      out_matrix  nxn行列
 * @note
 */
vector<vector<double>> MatrixCalc::matrixProductCalc(const vector<vector<double>>& matrixA, const vector<vector<double>>& matrixB) {
    int n_rows_A    = matrixA.size();
    int n_columns_A = matrixA[0].size();
    int n_rows_B    = matrixB.size();
    int n_columns_B = matrixB[0].size();
    // out_matrix.assign(n_rows, vector<double>(n_cols, 0));

    if (n_columns_A != n_rows_B) {
        cout << "No match row and column on matrixProductCalc" << endl;
        abort();
    }

    vector<vector<double>> out_matrix(n_rows_A, vector<double>(n_columns_B, 0));

    for (int i = 0; i < n_rows_A; i++) {
        for (int j = 0; j < n_columns_B; j++) {
            for (int k = 0; k < n_columns_A; k++) {
                out_matrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return out_matrix;
}

vector<vector<double>> MatrixCalc::transpose_matrix(const vector<vector<double>>& matrixA) {
    int n_rows    = matrixA.size();
    int n_columns = matrixA[0].size();
    vector<vector<double>> Ret(n_columns, vector<double>(n_rows));

    for (int i = 0; i < n_columns; i++) {
        for (int j = 0; j < n_rows; j++) {
            Ret[i][j] = matrixA[j][i];
        }
    }

    return Ret;
}
/**
 * @brief       行列を表示する
 * @param[in]   v 表示する行列
 * @note
 */
void MatrixCalc::printMatrix(vector<double> const& v) {
    // cout << "Print Matrix" << endl;
    int size = v.size();  // vの要素数を格納する

    cout << "-----------" << endl;
    for (int i = 0; i < size; i++) {
        cout << v[i] << ",";
    }
    cout << endl;
    cout << "-----------" << endl;
}
/**
 * @brief       行列を表示する（オーバーロード）
 * @param[in]   v 表示する行列
 * @note
 */
void MatrixCalc::printMatrix(vector<vector<double>> const& v) {
    // cout << "Print Matrix" << endl;
    int row    = v.size();     // vの行の要素数を格納する
    int colunm = v[0].size();  // vの列の要素数を格納する
    cout << "-----------" << endl;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < colunm; j++) {
            cout << v[i][j] << ",";
        }
        cout << endl;
    }
    cout << "-----------" << endl;
}

/**
 * @brief       行列の全要素をx倍する
 * @param[in]   scalar スカラー係数。倍率。行列の係数
 * @param[in]   in_matrix x倍する行列
 * @param[out]  out_matrix 係数をかけた後の行列
 * @note
 */
void MatrixCalc::matrixScalarProduct(double const& scalar, vector<double> const& in_matrix, vector<double>& out_matrix) {
    int size = in_matrix.size();  // in_matrixの要素数を格納する

    for (int i = 0; i < size; i++) {
        out_matrix[i] = scalar * in_matrix[i];
    }
}

/**
 * @brief       行列の全要素を1/x倍し、係数をくくりだす。
 * @param[in]   scalar スカラー倍率。掃き出す
 * @param[in]   in_matrix 1/x倍する行列
 * @param[out]  out_matrix 係数を出した後の行列
 * @note
 */
void MatrixCalc::matrixScalarDiv(double const& scalar, vector<double> const& in_matrix, vector<double>& out_matrix) {
    int size = in_matrix.size();  // in_matrixの要素数を格納する

    for (int i = 0; i < size; i++) {
        out_matrix[i] = in_matrix[i] / scalar;
    }
}

/**
 * @brief       行列の全要素の最大値を返す。
 * @param[in]   in_matrix  検索する行列
 * @param[out]  max_value  最大値
 * @param[out]  maxi  		最大値のイテレータ (i)
 * @param[out]  maxj		最大値のイテレータ (j)
 * @return double 最大値
 * @note
 */
double MatrixCalc::maxMatrix(vector<vector<double>> const& in_matrix, double& max_value, int& maxi, int& maxj) {
    int size  = in_matrix.size();  // in_matrixの要素数を格納する
    double a  = 0;                 // maxの値を一時的に保管する。
    max_value = 0;
    maxi      = 0;
    maxj      = 0;

    for (int i = 0; i < size - 1; i++) {
        for (int j = i; j < size; j++) {
            a = std::max(fabs(max_value), fabs(in_matrix[i][j]));
            if (fabs(max_value) < a) {
                max_value = in_matrix[i][j];
                maxi      = i;
                maxj      = j;
            }
        }
    }
    return max_value;
}

/**
 * @brief       行列の非対角要素での絶対値の最大値を返す。
 * @param[in]   in_matrix  検索する行列
 * @param[out]  max_value  最大値
 * @param[out]  maxi  		最大値のイテレータ (i)
 * @param[out]  maxj		最大値のイテレータ (j)
 * @return double 最大値
 * @note
 */
double MatrixCalc::maxMatrix_n(vector<vector<double>> const& in_matrix, double& max_value, int& maxi, int& maxj) {
    int size = in_matrix.size();  // in_matrixの要素数を格納する
    double a = 0;                 // maxの値を一時的に保管する。

    // 初期化
    max_value = 0;
    maxi      = 0;
    maxj      = 0;

    for (int i = 0; i < size - 1; i++) {
        for (int j = i; j < size; j++) {
            if (i != j) {
                a = std::max(fabs(max_value), fabs(in_matrix[i][j]));
                if (fabs(max_value) < a) {
                    max_value = in_matrix[i][j];
                    maxi      = i;
                    maxj      = j;
                }
            }
        }
    }
    return max_value;
}

/**
 * @brief       配列の値でソートする
 * @param[in]   arr			ソートする配列（2次元配列の特徴量を格納。この値を参考にソートする）
 * @param[in]   vec  		ソートする2次元配列
 * @param[in]   sort_mode	ソートモード（昇・降順と絶対値バージョン）
 * @return double 最大値
 * @note
 * Sort the rows of a matrix "vec" by the numbers contained in "eval"
 */
void MatrixCalc::SortRows(vector<double>& arr, vector<vector<double>>& vec, SortMode const& sort_mode) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int i_max = i;
        for (int j = i + 1; j < n; j++) {
            // find the "maximum" element in the array starting at position i+1
            switch (sort_mode) {
                case SORT_DECREASING_ARRAY:
                    if (arr[j] > arr[i_max])
                        i_max = j;
                    break;
                case SORT_INCREASING_ARRAY:
                    if (arr[j] < arr[i_max])
                        i_max = j;
                    break;
                case SORT_DECREASING_ABS_ARRAY:
                    if (std::abs(arr[j]) > std::abs(arr[i_max]))
                        i_max = j;
                    break;
                case SORT_INCREASING_ABS_ARRAY:
                    if (std::abs(arr[j]) < std::abs(arr[i_max]))
                        i_max = j;
                    break;
                default:
                    break;
            }
        }
        std::swap(arr[i], arr[i_max]);  // sort "arr"
        for (int k = 0; k < n; k++)
            std::swap(vec[i][k], vec[i_max][k]);  // sort "vec"
    }
}

class RotationMatrixCalc {
    // vector<vector<double>> rotation_matrix_x(3, vector<double>(3, 0));
    // vector<vector<double>> rotation_matrix_y(3, vector<double>(3, 0));
    // vector<vector<double>> rotation_matrix_z(3, vector<double>(3, 0));

    // constructor

    // member function
    vector<vector<double>> set_x(const double&);
    vector<vector<double>> set_y(const double&);
    vector<vector<double>> set_z(const double&);

    double angle_1;
    double angle_2;
    double angle_3;
    string rotation_axis_order_1;
    string rotation_axis_order_2;
    string rotation_axis_order_3;

   public:
    MatrixCalc mc;
    vector<vector<vector<double>>> rotation_matrix;
    vector<vector<double>> rotation_matrix_conv;

    vector<double> angles;
    //! 3 charactor (zyz)
    string rotation_axis_order;

    RotationMatrixCalc(void);
    RotationMatrixCalc(const double&, const double&, const double&);
    RotationMatrixCalc(const string&, const double&, const double&, const double&);
    void set_rotation_axis(const string&);
    void set(const double&, const double&, const double&);
    void set(const string&, const double&, const double&, const double&);
    void set_angle(void);
    void set_angle(const double&, const double&, const double&);
    void set_rotation_matrix(void);
    vector<double> rotate(const vector<double>&);
    vector<double> vec_rotate(const vector<double>&);

    bool iequals(const string& a, const string& b) {
        return std::equal(
            a.begin(), a.end(), b.begin(), b.end(),
            [](char a, char b) { return tolower(a) == tolower(b); });
    }
};

// constructor
RotationMatrixCalc::RotationMatrixCalc(void) {
    RotationMatrixCalc(0, 0, 0);
}
RotationMatrixCalc::RotationMatrixCalc(const double& a_1, const double& a_2, const double& a_3) {
    RotationMatrixCalc("zyz", a_1, a_2, a_3);
}
RotationMatrixCalc::RotationMatrixCalc(const string& rao, const double& a_1, const double& a_2, const double& a_3) {
    rotation_matrix.resize(3);
    set(rao, a_1, a_2, a_3);
}

// member function
void RotationMatrixCalc::set_rotation_axis(const string& rao) {
    rotation_axis_order   = rao;
    rotation_axis_order_1 = rao.substr(0, 1);
    rotation_axis_order_2 = rao.substr(1, 1);
    rotation_axis_order_3 = rao.substr(2, 1);
};

void RotationMatrixCalc::set_angle(void) {
    set_angle(angle_1, angle_2, angle_3);
}
void RotationMatrixCalc::set_angle(const double& a_1, const double& a_2, const double& a_3) {
    angle_1 = a_1;
    angle_2 = a_2;
    angle_3 = a_3;
    angles  = {
        angle_1,
        angle_2,
        angle_3,
    };
}

vector<vector<double>> RotationMatrixCalc::set_x(const double& angle) {
    vector<vector<double>> Ret = {
        {1, 0, 0},
        {0, cos(angle), -sin(angle)},
        {0, sin(angle), cos(angle)},
    };
    return Ret;
}
vector<vector<double>> RotationMatrixCalc::set_y(const double& angle) {
    vector<vector<double>> Ret = {
        {cos(angle), 0, sin(angle)},
        {0, 1, 0},
        {-sin(angle), 0, cos(angle)},
    };
    return Ret;
}
vector<vector<double>> RotationMatrixCalc::set_z(const double& angle) {
    vector<vector<double>> Ret = {
        {cos(angle), -sin(angle), 0},
        {sin(angle), cos(angle), 0},
        {0, 0, 1},
    };
    return Ret;
}
void RotationMatrixCalc::set(const double& a_1, const double& a_2, const double& a_3) {
    set_angle(a_1, a_2, a_3);
    // cout << angles[0] << "," << angles[1] << "," << angles[2] << endl;
    rotation_matrix.resize(3);

    for (int i = 0; i < 3; i++) {
        // cout << "i:" << i <<endl;
        // cout << "rao:" << rotation_axis_order.substr(i, 1) << endl;
        if (iequals(rotation_axis_order.substr(i, 1), "x")) {
            rotation_matrix[i] = set_x(angles[i]);
        } else if (iequals(rotation_axis_order.substr(i, 1), "y")) {
            rotation_matrix[i] = set_y(angles[i]);
        } else if (iequals(rotation_axis_order.substr(i, 1), "z")) {
            rotation_matrix[i] = set_z(angles[i]);
        } else {
            cout << "rotation_axis_order is not found" << endl;
            abort();
        }
        // mc.printMatrix(rotation_matrix[i]);
    }
    set_rotation_matrix();
    // rotation_matrix[0] = set_x(a_x);
    // rotation_matrix[1] = set_y(a_y);
    // rotation_matrix[2] = set_z(a_z);
}
void RotationMatrixCalc::set(const string& rao, const double& a_1, const double& a_2, const double& a_3) {
    set_rotation_axis(rao);
    set(a_1, a_2, a_3);
}

/**
 * @brief
 * @note R = R3(a_3)R2(a_2)R1(a_1)
 * R3(a_1)R(a_2 a_1)
 */
void RotationMatrixCalc::set_rotation_matrix(void) {
    rotation_matrix_conv = mc.matrixProductCalc(rotation_matrix[2], mc.matrixProductCalc(rotation_matrix[1], rotation_matrix[0]));
    return;
}

vector<double> RotationMatrixCalc::rotate(const vector<double>& matrix) {
    vector<double> Ret = mc.matrixProductCalc(rotation_matrix_conv, matrix);
    return Ret;
}
vector<double> RotationMatrixCalc::vec_rotate(const vector<double>& matrix) {
    vector<double> Ret = mc.matrixProductCalc(mc.transpose_matrix(rotation_matrix_conv), matrix);
    // cout << "R1:" << endl;
    // mc.printMatrix(rotation_matrix[0]);
    // mc.printMatrix(rotation_matrix[1]);
    // mc.printMatrix(rotation_matrix[2]);

    // cout << "R21:" << endl;
    // mc.printMatrix(mc.matrixProductCalc(rotation_matrix[1], rotation_matrix[0]));

    // cout << "R:" << endl;
    // mc.printMatrix(rotation_matrix_conv);
    // cout << "\n R^T:" << endl;
    // mc.printMatrix(mc.transpose_matrix(rotation_matrix_conv));
    return Ret;
}

class SphericalCoordinate {
    double radius;
    double angle_1;
    double angle_2;
    vector<double> xyz;
    vector<double> spherical_coordinates;

   public:
    SphericalCoordinate(void);
    SphericalCoordinate(const double&, const double&, const double&);
    void set(const double&, const double&, const double&);

    MatrixCalc mc;
    // vector<double> transform(const vector<double>&);
    vector<double> transform(void);
};

// constructor
SphericalCoordinate::SphericalCoordinate(void) { SphericalCoordinate(0, 0, 0); }
SphericalCoordinate::SphericalCoordinate(const double& r, const double& a_1, const double& a_2) {
    set(r, a_1, a_2);
}

void SphericalCoordinate::set(const double& r, const double& a_1, const double& a_2) {
    xyz.resize(3);
    radius  = r;
    angle_1 = a_1;
    angle_2 = a_2;
}

vector<double> SphericalCoordinate::transform(void) {
    xyz.resize(3);
    xyz[0] = radius * sin(angle_1) * cos(angle_2);
    xyz[1] = radius * sin(angle_1) * sin(angle_2);
    xyz[2] = radius * cos(angle_1);
    return xyz;
}

#endif  // ヘッダーファイルの終了
