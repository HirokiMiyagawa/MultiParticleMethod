/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file	main.cpp
 * @brief	main関数があるファイル、エラー処理しか行わない
 * @details
 * コマンドライン引数次第でエラーが出たり処理が変わったりするらしい。普段はint
 * 1が入るのみかな？
 *
 * ///////////////////////////////////////////////////////////////////////////////
 */

// header
//---------------------------------------
//  Global header
//--------------------
#include "Library_header.hpp"
#include "Color.hpp"

// Situation
//--------------------
#include "DefinitionOfSituation.hpp"  // default
//#include "SimpleTensile.hpp"
//#include "SimpleShare.hpp"
//#include "SimpleBend.hpp"
// #include "SimplePressure.hpp"
// #include "CylinderPressure.hpp
// "include "CubePressure.hpp"

#include "csv.hpp"
#include "MultiParticle.hpp"
#include "InitialConditions.hpp"
#include "BaseCalc.hpp"
#include "VirtualParticleCalc.hpp"
#include "ThicknessCalc.hpp"
#include "ForceCalc.hpp"
#include "GetNewCoordinate.hpp"
#include "Console.hpp"
//---------------------------------------

using namespace std;

//-------------
// Prototype declaration
typedef void (*MAIN_ERROR_FUNC)();
inline void myNameIs();
inline void argError();
inline void unknownError();
inline void csvError();
inline void calcFunc(int const&, int const&, int const&);
//-------------

//-------------
// Global
MAIN_ERROR_FUNC main_error_func[] = {myNameIs, argError, unknownError,
                                     csvError};
//-------------

/**
 * @brief
 * @param[in]	int argc	コマンドライン引数の数
 * @param[in]	char **argv コマンドライン引数のポインタのポインタ
 * @return	EXIT_SUCCESS 標準ライブラリにある。 int型で0を返す
 * @return	EXIT_FAILURE 標準ライブラリにある。 int型で0以外の整数を返す
 * @details
 * argc = 1 のとき、21*21のシミュレーション (mainのみの実行)
 * argc = 2
 * のとき、argv[1]のファイル名のcsvファイルから読み込んでシミュレーション。読み込むデータに粒子の座標はなし
 * (main csvファイルの名前) argc = 3
 * のとき、argv[1]と[2]の文字列を数字に変換し、どちらも2以上大きいならばcalcFuncの引数としてcalcFuncを動かす。要するに、粒子数を指定したシミュレーション
 * (main 3 3)
 *
 */
int main(int argc, char** argv) {
    try {
        if (argc == 1) {
            //---------------------------
            //
            // default calc function call
            //
            //--------------------------
            Params p;
            calcFunc(p.m_iNum, p.m_jNum, p.m_kNum);
        } else if (argc == 2) {
            //--------------------------------------
            //
            // params file read.
            //
            //--------------------------------------
            Params myparam;
            const string csv_file = argv[1];
            vector<vector<string>> data;
            Csv objCsv(csv_file);
            if (!objCsv.getCsv(data)) {
                throw 3;
            }
            objCsv.myparamRead(myparam, data);

            //------------------------------
            //
            // new params file setting enter.
            //
            //------------------------------
            MultiParticle mp(myparam);
            mp.simulateMethod();
        } else if (argc == 3) {
            //------------------------------
            //
            // 4 Time Measurement
            //
            //------------------------------
            if ((2 <= atoi(argv[1])) && (2 <= atoi(argv[2]))) {
                calcFunc(atoi(argv[1]), atoi(argv[2]), 1);
            } else {
                //------------------------------
                //
                // error called.
                //
                //------------------------------
                throw 1;
            }
        } else if (argc == 4) {
            //------------------------------
            //
            // 4 Time Measurement
            //
            //------------------------------
            if ((2 <= atoi(argv[1])) && (2 <= atoi(argv[2])) &&
                (2 <= atoi(argv[3]))) {
                calcFunc(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
            } else {
                //------------------------------
                //
                // error called.
                //
                //------------------------------
                throw 1;
            }
        } else {
            throw 1;
        }

        return EXIT_SUCCESS;
    } catch (const int error_code) {
        //------------------------------
        //
        // Exception called.
        //
        //------------------------------
        (*main_error_func[0])();
        (*main_error_func[error_code])();

        return EXIT_FAILURE;
    }
}

/** -------------
 * @brief	report
 */
inline void myNameIs() {
    cout << " "
         << "[      " << FONT_RED << "main" << ALL_DEFAULT << "       ]"
         << " ";
}

// Error Message
inline void argError() { cout << "Execution argument error." << endl; }

inline void unknownError() { cout << "Unknown error." << endl; }

inline void csvError() { cout << "read csv file failed." << endl; }

/**
 * @brief		引数がない or 引数が2つ の実行の場合に呼び出される
 * @param[in]	int i：i-Position
 * @param[in]	int j：j-Position
 * @par
 * @note
 * @details 	MultiParticleクラスを引数(i, j)で作成
 * MultiParticleメソッドのsimulatemothodを実行
 *
 */
inline void calcFunc(int const& i, int const& j, int const& k) {
    MultiParticle mp(i, j, k);
    /*
    MPI_Comm_rank( MPI_COMM_WORLD, &st.rank );
    MPI_Comm_size( MPI_COMM_WORLD, &st.proc );

    if( st.rank == 0 ){
            ( *main_error_func[ 0 ] )();
            cout	<< "procs: "
                            << st.proc
                            << " i:"
                            << st.param->m_iNum
                            << " j:"
                            << st.param->m_jNum
                            << endl;
    }
  */
    mp.simulateMethod();
}
