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

// /**
//  * @brief
//  * @param[in]	int argc	コマンドライン引数の数
//  * @param[in]	char **argv コマンドライン引数のポインタのポインタ
//  * @return	EXIT_SUCCESS 標準ライブラリにある。 int型で0を返す
//  * @return	EXIT_FAILURE 標準ライブラリにある。 int型で0以外の整数を返す
//  * @details
//  * argc = 1 のとき、21*21のシミュレーション (mainのみの実行)
//  * argc = 2
//  * のとき、argv[1]のファイル名のcsvファイルから読み込んでシミュレーション。読み込むデータに粒子の座標はなし
//  * (main csvファイルの名前) argc = 3
//  * のとき、argv[1]と[2]の文字列を数字に変換し、どちらも2以上大きいならばcalcFuncの引数としてcalcFuncを動かす。要するに、粒子数を指定したシミュレーション
//  * (main 3 3)
//  *
//  */

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

/*
 *  Copyright 2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// #define N 1000

// void matrix_addition(int *A, int *B, int *C) {
//     #pragma acc parallel loop collapse(2)
//     for (int i = 0; i < N; ++i) {
//         for (int j = 0; j < N; ++j) {
//             C[i * N + j] = A[i * N + j] + B[i * N + j];
//         }
//     }
// }

// int main() {
//     int *A, *B, *C;
//     A = (int *)malloc(N * N * sizeof(int));
//     B = (int *)malloc(N * N * sizeof(int));
//     C = (int *)malloc(N * N * sizeof(int));

//     // Initialize matrices A and B with random values
//     srand((unsigned)time(NULL));
//     for (int i = 0; i < N * N; ++i) {
//         A[i] = rand() % 100;
//         B[i] = rand() % 100;
//     }

//     // Perform matrix addition without OpenACC
//     clock_t start_time = clock();

//     for (int i = 0; i < N; ++i) {
//         for (int j = 0; j < N; ++j) {
//             C[i * N + j] = A[i * N + j] + B[i * N + j];
//         }
//     }

//     clock_t end_time = clock();
//     double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
//     printf("Time without OpenACC: %f seconds\n", elapsed_time);

//     // Perform matrix addition with OpenACC
//     clock_t start_time_acc = clock();
//     #pragma acc data copyin(A[0:N*N], B[0:N*N]) copyout(C[0:N*N])
//     {
//         // clock_t start_time_acc = clock();
// #pragma acc parallel loop collapse(2)
//     for (int i = 0; i < N; ++i) {
//         for (int j = 0; j < N; ++j) {
//             C[i * N + j] = A[i * N + j] + B[i * N + j];
//         }
//     }

//         clock_t end_time_acc = clock();
//         double elapsed_time_acc = ((double)(end_time_acc - start_time_acc)) / CLOCKS_PER_SEC;
//         printf("Time with OpenACC: %f seconds\n", elapsed_time_acc);
//     }

//     // Check if the results are consistent
//     for (int i = 0; i < N * N; ++i) {
//         if (C[i] != A[i] + B[i]) {
//             printf("Error: Mismatch in results at index %d\n", i);
//             break;
//         }
//     }

//     free(A);
//     free(B);
//     free(C);

//     return 0;
// }


