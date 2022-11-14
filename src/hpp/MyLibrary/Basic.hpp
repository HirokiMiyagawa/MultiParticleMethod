/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file	Basic.hpp
 * @brief	ファイルの入出力やBOM、桁区切りなど汎用性の高い関数を格納する
 *
 * @par
 * @date Create 2021-07-10<br>
 * @date last update 2021-07-10
 * @author raptel
 * ///////////////////////////////////////////////////////////////////////////////
 */

#ifndef Basic_hpp
#define Basic_hpp

/* include header files */

/* end include header files*/

/* include standard files */
#include <algorithm>  // vectorの最大値を取得する
#include <cmath>      // fabs
#include <fstream>    // ifstream, ofstream
#include <iomanip>    // std::setprecisionを使用するため
#include <iostream>   // for debug writing
#include <sstream>    // istringstream（stod）
#include <string>     // useful for reading and writing
#include <vector>     // 動的配列

/* end include standard files */

/* usingnamespace declaration(名前空間の宣言) */
// using std::cout;
// using std::endl;
// using std::flush;
// using std::string;
using std::vector;
/* end usingnamespace declaration*/

/* declaration MACRO */

/* end declaration MACRO */

/* prototype declaration */

class Basic;  // クラスの前方宣言

/* end prototype declaration*/

/* declaration enumlation */

/* declaration namespace */
namespace math {

//! 円周率 π
inline double pi(void) {
    // return 3.1415926535897932384626433832795;
    return std::acos(-1);
}

//! 安全なarc cos. 戻り値がnanにならない
inline double sacos(double x) {
    if (x < -1.0) {
        x = -1.0;
    } else if (1.0 < x) {
        x = 1.0;
    }
    return std::acos(x);
}
double degree_to_radian(double const&);
double radian_to_degree(double const&);
}  // namespace math

/* end declaration namespace */

/**
 * @brief       基本的な数字を扱うクラス
 * @note
 */
class Basic {
   public:
    std::string formatNumber(int num);
    bool GetContents(const std::string& filepath,
                     std::vector<std::vector<double>>& matrix,
                     std::vector<double>&
                         queue);  //  csvファイルから連立一次方程式を読み込む
    void create_utf8_stream(
        const std::string&
            path);  // ファイルの先頭にUTF-8のバイナリデータ（BOM）を書き込む
    bool GetCoordinates(
        const std::string& filepath,
        std::vector<std::vector<double>>&
            dataset);  //  csvファイルからn個の (x,y)の2次元座標を取得する

     //文字列型の引数をとり、分割処理をした後にvector<string>という複数の文字列を保持できる型に、分割したそれぞれを全て入れ込んで返します。
    std::vector<float> split(string& input, char delimiter);

};

/**
 * @brief 3桁ごとに数字に","を加える
 * @param[in] 	int num
 * @return		string 数字の3桁ごとに","を加えた文字列を返す
 * @note
 */
std::string Basic::formatNumber(int num) {
    std::vector<int> sepnum;
    int number = abs(num);
    int sgn    = num >= 0 ? 1 : -1;
    while (number / 1000) {
        sepnum.push_back(number % 1000);
        number /= 1000;
    }
    std::stringstream ss;
    ss << number * sgn;
    for (std::vector<int>::reverse_iterator i = sepnum.rbegin();
         i < sepnum.rend(); i++) {
        ss << "," << std::setfill('0') << std::setw(3) << *i;
    }
    return std::string(ss.str());
}

/**
 * @brief       角度をラジアンに変換する
 * @param[in]   double degree：角度 [deg.]
 * @return      double ：ラジアン [rad]
 */
double math::degree_to_radian(double const& degree) {
    return degree * math::pi() / 180.0;
}

/**
 * @brief       ラジアンを角度に変換する
 * @param[in]   double radian：ラジアン [rad]
 * @return      double ：角度 [deg.]
 */
double math::radian_to_degree(double const& radian) {
    return radian * 180 / math::pi();
}

/**
 * @brief   csvファイルから","区切りでデータをtable に格納する
 * @param[in] filepath  読み込む対象のファイル名
 * @param[out] matrix   読み込んだ行列Aを格納する (double)
 * @param[out] queue    読み込んだ行列bを格納する (double)
 * @note Ax = b を読み込むことを想定している
 * 要らない最後の改行は不要
 * csvファイルの形式は A(正方行列) と b（nx1）が1列別れて区切られているもの
 */
bool Basic::GetContents(const std::string& filepath,
                        std::vector<std::vector<double>>& matrix,
                        std::vector<double>& queue) {
    const char delimiter = ',';  // 区切り文字
    std::vector<std::vector<std::string>>
        table;  // 一時的に入力データを格納する

    // ファイルを開く
    std::fstream filestream(filepath);
    if (!filestream.is_open()) {
        // ファイルが開けなかった場合は終了する
        std::cout << "Can't input csv data" << std::endl;
        std::cout << "path: " << filepath << std::endl;
        return false;
    }

    // ファイルを読み込む
    while (!filestream.eof()) {
        // １行読み込む
        std::string buffer;
        filestream >> buffer;

        // ファイルから読み込んだ１行の文字列を区切り文字で分けてリストに追加する
        std::vector<std::string> record;          // １行分の文字列のリスト
        std::istringstream streambuffer(buffer);  // 文字列ストリーム
        std::string token;                        // １セル分の文字列
        while (getline(streambuffer, token, delimiter)) {
            // １セル分の文字列をリストに追加する
            record.push_back(token);
        }

        // １行分の文字列を出力引数のリストに追加する
        table.push_back(record);
    }

    table.pop_back();  // 最後の行を削除する
                       // （csvファイルをExcelで作成すると空の行ができるので）

    matrix.resize(table.size());
    for (unsigned row = 0; row < table.size(); row++) {
        matrix[row].resize(table[row].size());
    }

    for (unsigned int row = 0; row < table.size(); row++) {
        for (unsigned int colunm = 0; colunm < table[row].size() - 2;
             colunm++) {
            matrix[row][colunm] = std::stod(table[row][colunm]);
        }
        queue.push_back(std::stod(table[row][table[row].size() - 1]));
        // std::cout << std::endl;
    }

    return true;
}

/**
 * @brief   csvファイルから","区切りでデータをtable に格納する
 * @param[in] filepath  読み込む対象のファイルパス
 * @param[out] dataset   読み込んだ(x,y)座標を格納する
 * (std::vector<std::vector<<double>)
 * @details	x行y列の余分な行・列のないcsvファイルからデータを取得する
 * @note
 *
 *
 * csvファイルからn個の (x,y)の2次元座標を取得する
 * (x,y)のデータを nx2の行列として読み込む
 * 要らない最後の改行は無視する
 *
 * nxnの行列でも格納可能
 */
bool Basic::GetCoordinates(const std::string& filepath,
                           std::vector<std::vector<double>>& dataset) {
    const char delimiter = ',';  // 区切り文字
    std::vector<std::vector<std::string>>
        table;  // 一時的に入力データを格納する

    // ファイルを開く
    std::fstream filestream(filepath);
    if (!filestream.is_open()) {
        // ファイルが開けなかった場合は終了する
        std::cout << "Can't input csv data" << std::endl;
        std::cout << "path: " << filepath << std::endl;
        return false;
    }

    // ファイルを読み込む
    while (!filestream.eof()) {
        // １行読み込む
        std::string buffer;
        filestream >> buffer;

        // ファイルから読み込んだ１行の文字列を区切り文字で分けてリストに追加する
        std::vector<std::string> record;          // １行分の文字列のリスト
        std::istringstream streambuffer(buffer);  // 文字列ストリーム
        std::string token;                        // １セル分の文字列
        while (getline(streambuffer, token, delimiter)) {
            // １セル分の文字列をリストに追加する
            record.push_back(token);
        }

        // １行分の文字列を出力引数のリストに追加する
        table.push_back(record);
    }

    table.pop_back();  // 最後の行を削除する
                       // （csvファイルをExcelで作成すると空の行ができるので）

    dataset.resize(table.size());
    for (unsigned int row = 0; row < table.size(); row++) {
        dataset[row].resize(table[row].size());
    }

    for (unsigned int row = 0; row < table.size(); row++) {
        for (unsigned int colunm = 0; colunm < table[row].size(); colunm++) {
            dataset[row][colunm] = std::stod(table[row][colunm]);
        }
    }

    return true;
}

/**
 * @brief           ファイルの先頭にUTF-8のバイナリデータ（BOM）を書き込む
 * @param[in] path  読み込む対象のファイル名（パス）
 * @note
 */
void Basic::create_utf8_stream(const std::string& path) {
    // std::cout << "write BOM (UTF-8)" << std::endl;
    std::stringstream exportfile;
    std::ofstream ofs;
    exportfile << path;
    ofs.open(exportfile.str(),
             std::ios::ate | std::ios_base::in | std::ios_base::trunc);
    ofs.seekp(std::ios::beg);  // 先頭に移動
    unsigned char bom[] = {0xEF, 0xBB, 0xBF};
    ofs.write((char*)bom, sizeof(bom));

    ofs.close();
}

float stoff(const std::string& str) {
  const char* p = str.c_str();
  char* end;
  errno = 0;
  double x = std::strtof(p, &end);
  if (p == end) {
    throw std::invalid_argument("stoff");
  }
  if (errno == ERANGE) {
    throw std::out_of_range("stoff");
  }
  
  return static_cast<float>(x);
}

/**
 * @brief           //文字列型の引数をとり、分割処理をした後にvector<string>という複数の文字列を保持できる型に、分割したそれぞれを全て入れ込んで返します。
 * @param[in] input  読み込む対象のファイル名（パス）
 * @param[in] delimiter  通常は ","
 * @note   csvファイル処理用関数
 */
std::vector<float> Basic::split(string& input, char delimiter)
{
    //DEBUG
    //std::cout << "split function" << std::endl;
    //
    
    std::istringstream stream(input);
    std::string field;
    std::vector<float> result;
    while (getline(stream, field, delimiter)) {
        // result.push_back(stoff(field));
        try {
             result.push_back(stoff(field));
        } catch (...) { // ... で何でも受け取れる
            std::cout << "エラーが起きたのでTは強制的に1にしました。" << std::endl;
            result.push_back(1);;
        }
    }
    
    return result;
}

#endif  // ヘッダーファイルの終了
