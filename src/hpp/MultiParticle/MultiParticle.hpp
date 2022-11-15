/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file	MultiParticle.hpp
 * @brief	cppファイルからこちらに移動する。スーパークラス。
 *
 * ///////////////////////////////////////////////////////////////////////////////
 */

// header
//---------------------------------------

#include "CalcDataAllocation.hpp"

#include "Params.hpp"
#include "Basic.hpp"

#include <signal.h>  // sigction
#include <map>       // std::mapを使用するため
//---------------------------------------
#define DEBUG_MODE

using namespace std;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/* declaration namespace */

/**
 ///////////////////////////////////////////////////////////////////////////////
 * @brief      	よくわからんな
 * @details
 * @note
 *
 ///////////////////////////////////////////////////////////////////////////////
*/
class MultiParticle {
   public:
    int rank, proc;
    int local_max_threads;
    int* allthreads;
    int sum_threads;

    //!	計算を終了する回数
    int responsible_range_end;
    //!	計算を開始する回数
    int responsible_range_start;
    //!	i方向の計算回数
    int local_iNum;
    //! j方向の計算回数
    int local_jNum;
    //! k方向の計算回数
    int local_kNum;
    //!
    int calc_jStart;
    int calc_jEnd;
    bool loop_end_flag        = false;
    std::string parameter_dir = "./data/csv/";
    string time_file          = "./data/time/time1.csv";
    string position_cx_file   = "./data/position/c_x.dat";
    string position_cy_file   = "./data/position/c_y.dat";
    string position_cz_file   = "./data/position/c_z.dat";
    string position_vx_file   = "./data/position/v_x.dat";
    string position_vy_file   = "./data/position/v_y.dat";
    string position_vz_file   = "./data/position/v_z.dat";
    // string parameter_file = "./data/csv/parameter";
    // string coordinates_file = "./data/csv/coordinates";
    // string initial_file = "./data/csv/initial.csv";
    // string condition_file = "./data/csv/condition.csv";
    string parameter_file   = parameter_dir + "parameter";
    string coordinates_file = parameter_dir + "coordinates";
    string initial_file     = parameter_dir + "initial.csv";
    string condition_file   = parameter_dir + "condition.csv";

    //!	ofstreamオブジェクトのfoutcxを定義、引数がファイルのパス, モード
    std::ofstream foutparam;

    std::chrono::system_clock::time_point first_calc_time;

    std::map<int, string> reFlag;
    Params* param;
    Particles* p;

   private:
   public:
    Basic* basic;
    MultiParticle(){};

    /**
     * @brief	いつ使われるコンストラクタなのか？
     */
    MultiParticle(Params& myparam) {
        console(0);
        param = new Params();

        param = &myparam;

        //	無次元化などの予め行う計算
        param->preCalc();

        setExecEnv();
        p = new Particles(local_iNum, local_jNum, local_kNum);
    }

    /**
     * @brief	main関数から呼ばれる場合のコンストラクタ
     */
    MultiParticle(int const& i, int const& j, int const& k) {
        console(0);

        param         = new Params();
        param->m_iNum = i;
        param->m_jNum = j;
        param->m_kNum = k;
        param->preCalc();

        setExecEnv();
        p = new Particles(local_iNum, local_jNum, local_kNum);
    }

    ~MultiParticle() {
        console(1);
        delete p;
        delete param;
    }

    /**
     * @brief	main関数から呼ばれる場合のコンストラクタ
     * @note	setInitialConditions()を呼び出し、時間のcsvファイルに
     */
    void simulateMethod() {
        setInitialAnalysisShape(param->analysis_shape, param->grid_pattern);
        setInitialConditions();
        console(2);

        //! delete all csv files
        // delete_file(parameter_dir.c_str());
        ofstream fout(time_file.c_str(), ios_base::app);
        fout << " iNum: " << setw(5) << left << param->m_iNum
             << " jNum: " << setw(5) << left << param->m_jNum
             << " particle num: " << setw(5) << left << param->m_kNum
             << " particle num: " << setw(15) << left
             << param->m_iNum * param->m_jNum * param->m_kNum;
        // fout.close();

        //!	シミュレーションが開始した時刻
        std::chrono::system_clock::time_point start =
            chrono::system_clock::now();
        if (CubePressure) {
            reFlag = {{0b00000000, "BIT_NONE"},
                      {0b00010000, "RightSideCenter"},
                      {0b00010001, "RightSideRight"},
                      {0b00010010, "RightSideLeft"},
                      {0b00010100, "RightSideBottom"},
                      {0b00011000, "RightSideTop"},
                      {0b00010101, "RightSideRightBottom"},
                      {0b00011001, "RightSideRightTop"},
                      {0b00010110, "RightSideLeftBottom"},
                      {0b00011010, "RightSideLeftTop"},

                      {0b00100000, "BackCenter"},
                      {0b00100001, "BackRight"},
                      {0b00100010, "BackLeft"},
                      {0b00100100, "BackBottom"},
                      {0b00101000, "BackTop"},
                      {0b00100101, "BackRightBottom"},
                      {0b00101001, "BackRightTop"},
                      {0b00100110, "BackLeftBottom"},
                      {0b00101010, "BackLeftTop"},

                      {0b01000000, "CeilingCenter"},
                      {0b01000001, "CeilingRight"},
                      {0b01000010, "CeilingLeft"},
                      {0b01000100, "CeilingBottom"},
                      {0b01001000, "CeilingTop"},
                      {0b01000101, "CeilingRightBottom"},
                      {0b01001001, "CeilingRightTop"},
                      {0b01000110, "CeilingLeftBottom"},
                      {0b01001010, "CeilingLeftTop"}};
        } else {
            reFlag = {{Center, "Center"}, {Left, "Left"}, {Right, "Right"}, {Bottom, "Bottom"}, {Top, "Top"}, {LeftBottom, "LeftBottom"}, {LeftTop, "LeftTop"}, {RightBottom, "RightBottom"}, {RightTop, "RightTop"}};
        }

        // 初期値の挿入
        OutputInitial();
        OutputCondition();

        std::cout << "Start Analysis" << endl;
        //!	計算回数
        int time = 0;
        //!	粒子番号
        int i, j, k;
        double pre_vector  = 0;
        double pre_theta   = 0;
        bool judge_release = false;
        if (param->force_release) {
            judge_release = true;
        }
        //	シミュレーションの終了条件
        //	time, m_dt, m_sheet_skipの積がm_tmax以上で終了
        //	かつ
        //	loop_end_flagがfalseになる
        //	ループ終了ごとにtimeは1つ増える
        for (time = time;
             (time * param->m_dt * param->m_sheet_skip < param->m_tmax) &&
             loop_end_flag == false;
             time++) {
            // data.csvSetData(time, particle);
            //  OutputData(time * param->m_dt * param->m_sheet_skip);
            OutputParameter(time, start);
            // OutputCoordinates(time, start);
            //

            // dataCalc();
            // sheet_countがm_sheet_skip未満の間続ける
            // これは、m_dtの移動量を計算するためのfor文
            int show_count_max = 10;
            if (param->m_sheet_skip < 10) {
                show_count_max = 1;
            }
            for (int show_count = 0; show_count < show_count_max;
                 ++show_count) {
                for (int sheet_count = 0;
                     sheet_count < param->m_sheet_skip / show_count_max;
                     sheet_count++) {
                    // OpneMPによる並列処理開始
                    // 分割はstaticかつ、 i がprivate
                    // #pragma omp parallel
                    //                     {
                    //                         //
                    //                         iはプライベート(各スレッドで共有しない)、分割はstatic
                    // #pragma omp for private(j) private(k) schedule(static)
                    //                         for (i = 0; i < p->c.size(); i++)
                    //                         {
                    //                             for (j = 0; j <
                    //                             p->c[0].size(); j++) {
                    //                                 for (k = 0; k <
                    //                                 p->c[0][0].size(); k++) {
                    //                                     // cout << i << ","
                    //                                     << j << "," << k <<
                    //                                     // endl;
                    //                                     p->new_c[i][j][k] =
                    //                                     p->c[i][j][k];
                    //                                     p->new_v[i][j][k] =
                    //                                     p->v[i][j][k];
                    //                                     // cout << "Run
                    //                                     VirtualParticleCalc"
                    //                                     <<
                    //                                     // endl;
                    //                                     OldVirtualParticleCalc(i,
                    //                                     j, k);

                    //                                     //
                    //                                     VirtualParticleCalc(i,
                    //                                     j, k);
                    //                                 }
                    //                             }
                    //                         }

                    // #pragma omp for private(j) private(k) schedule(static)
                    //                         for (i = 0; i < p->c.size(); i++)
                    //                         {
                    //                             for (j = 0; j <
                    //                             p->c[0].size(); j++) {
                    //                                 for (k = 0; k <
                    //                                 p->c[0][0].size(); k++) {
                    //                                     // cout << "Run
                    //                                     ThicknessCalc" <<
                    //                                     endl;
                    //                                     ThicknessCalc(i, j,
                    //                                     k);

                    //                                     //
                    //                                     InfluenceAreaCalc(i,
                    //                                     j, k);
                    //                                 }
                    //                             }
                    //                         }

                    // #pragma omp for private(j) private(k) schedule(static)
                    //                         for (i = 0; i < p->c.size(); i++)
                    //                         {
                    //                             for (j = 0; j <
                    //                             p->c[0].size(); j++) {
                    //                                 for (k = 0; k <
                    //                                 p->c[0][0].size(); k++) {
                    //                                     // cout << "Run
                    //                                     ForceCalc" << endl;
                    //                                     // if (CubePressure)
                    //                                     { ForceCalc(i, j, k);
                    //                                     // }
                    //                                     //
                    //                                     TensileForceCalc(i,
                    //                                     j, k);
                    //                                     // ShareForceCalc(i,
                    //                                     j, k);
                    //                                     // BendForceCalc(i,
                    //                                     j, k);
                    //                                     // AirForceCalc(i, j,
                    //                                     k);
                    //                                 }
                    //                             }
                    //                         }

                    // #pragma omp for private(j) private(k) schedule(static)
                    //                         for (i = 0; i < p->c.size(); i++)
                    //                         {
                    //                             for (j = 0; j <
                    //                             p->c[0].size(); j++) {
                    //                                 for (k = 0; k <
                    //                                 p->c[0][0].size(); k++) {
                    //                                     // cout << "Run
                    //                                     GetNewCoordinate" <<
                    //                                     endl;
                    //                                     ContradictBendForceCalc(i,
                    //                                     j, k);
                    //                                     GetNewCoordinate(i,
                    //                                     j, k);
                    //                                     ExternalForceCalc(i,
                    //                                     j, k);
                    //                                 }
                    //                             }
                    //                         }
                    //                     }
                    CalcMainSimulation();
#pragma omp parallel
                    {
#pragma omp for private(j) private(k) schedule(static)
                        for (i = 0; i < local_iNum; i++) {
                            for (j = 0; j < local_jNum; j++) {
                                for (k = 0; k < local_kNum; k++) {
                                    // cout << "Run GetNewCoordinate" << endl;
                                    MoveParticleByRungeKutta(i, j, k);
                                }
                            }
                        }

                        // #pragma omp for private(j) private(k) schedule(static)
                        //                         for (i = 0; i < local_iNum; i++) {
                        //                             for (j = 0; j < local_jNum; j++) {
                        //                                 for (k = 0; k < local_kNum; k++) {
                        //                                     if (p->alphai[i][j][k] * 180 / math::pi() != 180) {
                        //                                         cout << i << "," << j << "," << k << endl;
                        //                                         cout << std::setprecision(17) << p->alphai[i][j][k] * 180 / math::pi()
                        //                                              << endl;
                        //                                         p->li[i][j][k].vector.print();
                        //                                         p->li[i - 1][j][k].vector.print();
                        //                                         cout << etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm, p->li[i - 1][j][k].norm) << endl;
                        //                                         cout << endl;
                        //                                     }
                        //                                 }
                        //                             }
                        //                         }
                    }
                    // if (sheet_count == 0) {
                    //     cout << "finish" << endl;
                    //     abort();
                    // }
                    if (time == 0 && sheet_count == 0 && show_count == 0) {
                        OutputParameter(time, start);
                        first_calc_time = chrono::system_clock::now();
                    }
                    if (time == 0 && sheet_count == 1 && show_count == 0) {
                        double save         = param->m_sheet_skip;
                        param->m_sheet_skip = 1;
                        OutputParameter(1, start);
                        param->m_sheet_skip = save;
                    }

                    if (time * param->m_sheet_skip +
                            show_count * param->m_sheet_skip / show_count_max +
                            sheet_count ==
                        1E5) {
                        std::chrono::system_clock::time_point second_calc_time =
                            chrono::system_clock::now();
                        auto one_loop_processing_time =
                            second_calc_time - first_calc_time;
                        std::stringstream onetime_duration_time;
                        onetime_duration_time << parameter_dir
                                              << "processing_time_"
                                              << std::chrono::duration_cast<
                                                     std::chrono::milliseconds>(
                                                     one_loop_processing_time)
                                                     .count()
                                              << "ms"
                                              << ".csv";
                        std::ofstream processing_time_fout;
                        basic->create_utf8_stream(onetime_duration_time.str());
                        processing_time_fout.open(onetime_duration_time.str(),
                                                  ios_base::app);
                        processing_time_fout << std::chrono::duration_cast<
                                                    std::chrono::milliseconds>(
                                                    one_loop_processing_time)
                                                    .count()
                                             << flush;
                        processing_time_fout.close();
                    }
                }
                {  // new angle
                    param->phi += param->m_phi_d;
                    param->theta += param->m_theta_d;
                    param->psi += param->m_psi_d;
                    param->phi_d += param->m_phi_dd;
                    param->theta_d += param->m_theta_dd;
                    param->psi_d += param->m_psi_dd;
                    if (param->phi > 2 * math::pi()) {
                        param->phi -= math::pi();
                    } else if (param->phi < -2 * math::pi()) {
                        param->phi += math::pi();
                    }
                    if (param->theta > 2 * math::pi()) {
                        param->theta -= math::pi();
                    } else if (param->theta < -2 * math::pi()) {
                        param->theta += math::pi();
                    }
                    if (param->psi > 2 * math::pi()) {
                        param->psi -= math::pi();
                    } else if (param->psi < -2 * math::pi()) {
                        param->psi += math::pi();
                    }
                    param->set_pressure_initial();
                }

                // release
                if (judge_release && param->force_release) {
                    double release_vector = 1e-5;
                    // double release_extend = 0.00001;
                    // cout << pre_vector << flush;
                    int itr_x = p->v.size() - 1;
                    int itr_y = p->v[0].size() / 2;
                    int itr_z = p->v[0][0].size() / 2;
                    if (fabs(p->v[itr_x][itr_y][itr_z].x) < release_vector &&
                        (fabs(p->v[itr_x][itr_y][itr_z].x - pre_vector) <
                         release_vector)) {
                        float nowtime =
                            time * param->m_dt * param->m_sheet_skip;
                        cout << "\n"
                             << "\033[31m"
                             << "release:" << nowtime << "\033[m" << endl;
                        param->m_fx   = 0;
                        param->m_fy   = 0;
                        param->m_fz   = 0;
                        param->m_fe   = 0;
                        judge_release = false;

                        string release_time_file = "release_time_";
                        std::stringstream release_filename;
                        release_filename << parameter_dir << release_time_file
                                         << "" << nowtime << ".csv";
                        std::ofstream release_fout;
                        release_fout.open(release_filename.str(),
                                          ios_base::out);

                        release_fout << nowtime << std::setprecision(15)
                                     << flush;
                        release_fout << endl;
                        release_fout.close();
                    }
                    // pre_vector = p->v[itr_x][itr_y][itr_z].x;
                }

                // execution monitor (現在の計算時間を表示する)
                if (show_current_param(time, pre_vector, pre_theta)) break;
            }
        }
        std::cout << '\n';

        //! シミュレーションが終了した時刻
        auto end = chrono::system_clock::now();
        //!	シミュレーションの処理時間
        auto diff = end - start;

        //	最後に処理時間を挿入する(左詰めで15文字)
        fout << " " << setw(15) << left
             << chrono::duration_cast<chrono::minutes>(diff).count() << flush;

        fout << endl;
        fout.close();
    }

   private:
    void console(int);

    /**
     * @brief		実行環境を設定する
     * @note		引数付きコンストラクタの際に、必ず呼び出される関数
     * @note		int time：型の変数に初期値を格納する
     * local_iNum, local_jNumも定義
     */
    void setExecEnv() {
        //! 計算を開始する粒子番号
        responsible_range_start = 0;
        //! 計算を終了する粒子番号(j)
        responsible_range_end = param->m_jNum - 1;
        //! i方向の計算回数
        local_iNum = param->m_iNum;
        //! j方向の計算回数
        local_jNum = responsible_range_end - (responsible_range_start - 1);
        //! k方向の計算回数
        local_kNum  = param->m_kNum;
        calc_jStart = 0;
        calc_jEnd   = local_jNum;
    }
    /* private関数を定義 */
    void setInitialAnalysisShape(std::string const&, std::string const&);
    void setInitialConditions();
    void setInitialConditionsSetFlag();
    void setInitialConditionsSetFlagCube();
    void setInitialConditionsSetParam();
    void setInitialConditionsSetParamShapeCylinder();
    void setInitialConditionsEquallyDividedModeling();
    void setInitialConditionsUnEquallyDividedModeling();
    void setInitialConditionsObliqueAlignmentModeling();
    void setInitialConditionsShapeCylinder();
    void setInitialConditionsShapeCube();
    void setInitialConditionsLCalc();
    void setInitialConditionsGCalc();
    void setInitialConditionsMiCalc();
    void setInitialConditionsMjCalc();
    void setInitialConditionsSCalc();
    void setInitialConditionsSiCalc();
    void setInitialConditionsSjCalc();
    void setInitialConditionsAreaCalc();
    void setInitialConditionsCopy();
    void setInitialConditionsSetVirtualParticle(int const&, int const&);
    void setInitialConditionsCreaseModeling();
    void setInitialConditionsCrease();

    inline void CalcMainSimulation() {
        int i, j, k;
#pragma omp parallel
        {
            //	iはプライベート(各スレッドで共有しない)、分割はstatic
#pragma omp for private(j) private(k) schedule(static)
            for (i = 0; i < local_iNum; i++) {
                for (j = 0; j < local_jNum; j++) {
                    for (k = 0; k < local_kNum; k++) {
                        // cout << i << "," << j << "," << k << endl;
                        p->new_c[i][j][k] = p->c[i][j][k];
                        p->new_v[i][j][k] = p->v[i][j][k];
                        // cout << "Run VirtualParticleCalc" << endl;
                        // OldVirtualParticleCalc(i, j, k);

                        VirtualParticleCalc(i, j, k);
                    }
                }
            }

#pragma omp for private(j) private(k) schedule(static)
            for (i = 0; i < local_iNum; i++) {
                for (j = 0; j < local_jNum; j++) {
                    for (k = 0; k < local_kNum; k++) {
                        // cout << "Run ThicknessCalc" << endl;
                        // ThicknessCalc(i, j, k);

                        InfluenceAreaCalc(i, j, k);
                    }
                }
            }

#pragma omp for private(j) private(k) schedule(static)
            for (i = 0; i < local_iNum; i++) {
                for (j = 0; j < local_jNum; j++) {
                    for (k = 0; k < local_kNum; k++) {
                        // cout << "Run ForceCalc" << endl;
                        // ForceCalc(i, j, k);

                        TensileForceCalc(i, j, k);
                        ShareForceCalc(i, j, k);
                        BendForceCalc(i, j, k);
                        AirForceCalc(i, j, k);
                        RotationInertiaForceCalc(i, j, k);
                    }
                }
            }
#pragma omp for private(j) private(k) schedule(static)
            for (i = 0; i < local_iNum; i++) {
                for (j = 0; j < local_jNum; j++) {
                    for (k = 0; k < local_kNum; k++) {
                        // cout << "Run GetNewCoordinate" << endl;
                        ContradictBendForceCalc(i, j, k);
                        GetNewCoordinate(i, j, k);
                        ExternalForceCalc(i, j, k);
                    }
                }
            }
        }
    }
    /**
     * @brief
     * 座標と速度のxyz成分を指定したファイルに、引数の時間が1列目になるようなdatファイルとして出力する
     * @param[in]	double const& time：現在の時間
     * @note		呼び出されるたびに、追記する
     * 基本的には各時間ごとにこの関数を呼び出すのだと思われる
     */
    void OutputData(double const& time) {
        //!	ofstreamオブジェクトのfoutcxを定義、引数がファイルのパス, モード
        ofstream foutcx(position_cx_file.c_str(), ios_base::app);
        ofstream foutcy(position_cy_file.c_str(), ios_base::app);
        ofstream foutcz(position_cz_file.c_str(), ios_base::app);
        ofstream foutvx(position_vx_file.c_str(), ios_base::app);
        ofstream foutvy(position_vy_file.c_str(), ios_base::app);
        ofstream foutvz(position_vz_file.c_str(), ios_base::app);

        //!	time以降の値は桁数15桁の精度を持つ
        foutcx << "#" << time << std::setprecision(17);
        foutcy << "#" << time << std::setprecision(17);
        foutcz << "#" << time << std::setprecision(17);
        foutvx << "#" << time << std::setprecision(17);
        foutvy << "#" << time << std::setprecision(17);
        foutvz << "#" << time << std::setprecision(17);

        //	座標と速度のxyz成分を各パスのファイルに出力する
        for (unsigned int i = 0; i < p->c.size(); i++) {
            for (unsigned int j = 0; j < p->c[i].size(); j++) {
                for (unsigned int k = 0; k < p->c[i][j].size(); k++) {
                    foutcx << " " << p->c[i][j][k].x;
                    foutcy << " " << p->c[i][j][k].y;
                    foutcz << " " << p->c[i][j][k].z;
                    foutvx << " " << p->v[i][j][k].x;
                    foutvy << " " << p->v[i][j][k].y;
                    foutvz << " " << p->v[i][j][k].z;
                }
            }
        }

        foutcx << endl;
        foutcy << endl;
        foutcz << endl;
        foutvx << endl;
        foutvy << endl;
        foutvz << endl;

        foutcx.close();
        foutcy.close();
        foutcz.close();
        foutvx.close();
        foutvy.close();
        foutvz.close();
    }

    /**
     * @brief
     * 引数の時間が1列目になるようなdatファイルとして出力する
     * @param[in]	double const& time：現在の時間
     * @note		呼び出されるたびに、追記する
     * 自作。後付した
     */
    void OutputCoordinates(int const& time,
                           std::chrono::system_clock::time_point& start_time) {
        // キャストした 経過回数*div_file 回ごとにファイルを分割する
        if (time % param->div_file == 0) {
            foutparam.close();
            //! 連番ファイルの作成
            std::stringstream filename;
            filename << coordinates_file << "_" << time << ".csv";
            basic->create_utf8_stream(filename.str());
            foutparam.open(filename.str(), ios_base::app);

            foutparam << "(i.j.k),"
                      << "Flag,"
                      << "Time,"
                      << "X-axis,"
                      << "Y-axis,"
                      << "Z-axis,"
                      << "V.x,"
                      << "V.y,"
                      << "V.z,"
                      << "α_i,"
                      << "α_j,"
                      //   << "P,"
                      << endl;
        }
        //!	time以降の値は桁数15桁の精度を持つ
        foutparam << std::setprecision(17);
        std::chrono::system_clock::time_point laptime =
            std::chrono::system_clock::now();
        auto nowtime = laptime - start_time;

        foutparam
            << std::chrono::duration_cast<std::chrono::minutes>(nowtime).count()
            << " min"
            << "\n";

        //	各時間での粒子のパラメータを出力する
        for (unsigned int i = 0; i < p->c.size(); i++) {
            for (unsigned int j = 0; j < p->c[i].size(); j++) {
                for (unsigned int k = 0; k < p->c[i][j].size(); k++) {
#if defined __SHAPE_CUBE__
                    if (p->flag[i][j][k] != BIT_NONE) {
#endif
                        // cout << "i."
                        // 	 << i
                        // 	 << "j."
                        // 	 << j
                        // 	 << "k."
                        // 	 << k
                        // 	 << "\n"
                        // 	 << endl;

                        foutparam
                            << "(" << i << "." << j << "." << k << "),"
                            << reFlag[p->flag[i][j][k]] << ","
                            << time * param->m_dt * param->m_sheet_skip << ","
                            << p->new_c[i][j][k].x << "," << p->new_c[i][j][k].y
                            << "," << p->new_c[i][j][k].z << ","
                            << p->new_v[i][j][k].x << "," << p->new_v[i][j][k].y
                            << "," << p->new_v[i][j][k].z << ","
                            << p->alphai[i][j][k] * 180 / math::pi() << ","
                            << p->alphaj[i][j][k] * 180 / math::pi() << ",\n";
#if defined __SHAPE_CUBE__
                    }
#endif
                }
            }
        }
        foutparam << endl;
    }

    /**
     * @brief
     * 引数の時間が1列目になるようなdatファイルとして出力する
     * @param[in]	double const& time：現在の時間
     * @param[in]   time_point
     * start_time：シミュレーションを開始してからの時間
     * @note		呼び出されるたびに、追記する
     * 自作。後付した
     */
    void OutputParameter(int const& time,
                         std::chrono::system_clock::time_point& start_time) {
        // キャストした 経過回数*div_file 回ごとにファイルを分割する
        if (time % param->div_file == 0) {
            foutparam.close();
            //! 連番ファイルの作成
            std::stringstream filename;
            filename << parameter_file << "_" << time << ".csv";
            basic->create_utf8_stream(filename.str());
            foutparam.open(filename.str(), ios_base::app);

            foutparam << "(i.j.k),"
                      << "Flag,"
                      << "ExistFlag,"
                      << "SpecialFlagNum,"
                      << "Time,"
                      << "X-axis,"
                      << "Y-axis,"
                      << "Z-axis,"
                      << "V.x,"
                      << "V.y,"
                      << "V.z,";

            foutparam << "li.x,"
                      << "li.y,"
                      << "li.z,"
                      << "lj.x,"
                      << "lj.y,"
                      << "lj.z,"
                      << "li,"
                      << "lj,"
                      << "g.x,"
                      << "g.y,"
                      << "g.z,"
                      << "mi.x,"
                      << "mi.y,"
                      << "mi.z,"
                      << "mj.x,"
                      << "mj.y,"
                      << "mj.z,"
                      << "Si.cp,"
                      << "Sj.cp,"
                      << "S.cp.x,"
                      << "S.cp.y,"
                      << "S.cp.z,"
                      << "S.cp,"
                      << "αi,"
                      << "αj,"
                      << "ηi,"
                      << "ηj,"
                      << "Δηi,"
                      << "Δηj,"
                      << "β++,"
                      << "β+-,"
                      << "β-+,"
                      << "β--,"
                      << "γ++,"
                      << "γ+-,"
                      << "γ-+,"
                      << "γ--,"
                      << "h(i+1/2.j),"
                      << "h(i.j+1/2),"
                      << "h(i.j),"
                      << "εi(i+1/2.j),"
                      << "εj(i+1/2.j),"
                      << "εj(i.j+1/2),"
                      << "εi(i.j+1/2),"
                      << "Ii,"
                      << "Ij,"
                      << "Mi,"
                      << "Mj,"
                      << "Px,"
                      << "Py,"
                      << "Pz,"
                      << "P.norm,";

            foutparam << "angleSun,"
                      << "fn.x,"
                      << "fn.y,"
                      << "fn.z,"
                      << "ft.x,"
                      << "ft.y,"
                      << "ft.z,";

            foutparam << "Bottom.x,"
                      << "Bottom.y,"
                      << "Bottom.z,"
                      << "Top.x,"
                      << "Top.y,"
                      << "Top.z,"
                      << "Left.x,"
                      << "Left.y,"
                      << "Left.z,"
                      << "Right.x,"
                      << "Right.y,"
                      << "Right.z,";

            foutparam << "Ft(i+1/2.j),"
                      << "Ft(i.j+1/2),"
                      << "Fs(i+.j),"
                      << "Fs(i-.j),"
                      << "Fs(i.j+),"
                      << "Fs(i.j-),"
                      << "Fb(i+.j),"
                      << "Fb(i-.j),"
                      << "Fb(i.j+),"
                      << "Fb(i.j-),"
                      << "Fb(i+-.j).x,"
                      << "Fb(i+-.j).y,"
                      << "Fb(i+-.j).z,"
                      << "Fb(i.j+-).x,"
                      << "Fb(i.j+-).y,"
                      << "Fb(i.j+-).z,"
                      << "Fb(i.j).x,"
                      << "Fb(i.j).y,"
                      << "Fb(i.j).z,"
                      << "Fa,"
                      << "Fall.ip,"
                      << "Fall.im,"
                      << "Fall.jp,"
                      << "Fall.jm,"
                      << "Fall.ipb,"
                      << "Fall.imb,"
                      << "Fall.jpb,"
                      << "Fall.jmb,"
                      << "Fall.air,"
                      << "Fvec.x,"
                      << "Fvec.y,"
                      << "Fvec.z,"
                      << "Fe.x,"
                      << "Fe.y,"
                      << "Fe.z,";
            foutparam << "Fe_air.x,"
                      << "Fe_air.y,"
                      << "Fe_air.z,";
            foutparam
                << "phi_system,"
                << "theta_system,"
                << "psi_system,"
                << "phi_d_system,"
                << "theta_d_system,"
                << "psi_d_system,"
                << "r.x,"
                << "r.y,"
                << "r.z,"
                << "v_r.x,"
                << "v_r.y,"
                << "v_r.z,"
                << "phi,"
                << "theta,"
                << "psi,"
                << "omega_phi,"
                << "omega_theta,"
                << "omega_psi,"
                << "omega.x,"
                << "omega.y,"
                << "omega.z,"
                << "a_Euler.x,"
                << "a_Euler.y,"
                << "a_Euler.z,"
                << "Fcen.x,"
                << "Fcen.y,"
                << "Fcen.z,"
                << "Fcol.x,"
                << "Fcol.y,"
                << "Fcol.z,"
                << "Fi.x,"
                << "Fi.y,"
                << "Fi.z,"
                << "F_roll.x,"
                << "F_roll.y,"
                << "F_roll.z,";

            if (CylinderPressure && !param->boundary.cylinder_boundary) {
                foutparam << "omp.ci.x,"
                          << "omp.ci.y,"
                          << "omp.ci.z,"
                          << "omp.g.x,"
                          << "omp.g.y,"
                          << "omp.g.z,"
                          << "omp.li.x,"
                          << "omp.li.y,"
                          << "omp.li.z,"
                          << "omp.lj.x,"
                          << "omp.lj.y,"
                          << "omp.lj.z,"
                          << "omp.li,"
                          << "omp.lj,"
                          << "omp.mi.x,"
                          << "omp.mi.y,"
                          << "omp.mi.z,"
                          << "omp.mj.x,"
                          << "omp.mj.y,"
                          << "omp.mj.z,"
                          << "omp.Si.i.x,"
                          << "omp.Si.i.y,"
                          << "omp.Si.i.z,"
                          << "omp.Si.i,"
                          << "omp.Si.j.x,"
                          << "omp.Si.j.y,"
                          << "omp.Si.j.z,"
                          << "omp.Si.j,"
                          << "omp.Si.cp,"
                          << "omp.hi,"
                          << "omp.εli,"
                          << "omp.εgj,"
                          << "omp.Fti,"
                          << "omp.Fs(i+.j),"
                          << "omp.Fs(i-.j),";
                //   << "omp.Fs(i.j+)"
                //   << "omp.Fs(i.j-)";
            }
            if (param->add_disturbance) {
                foutparam << "disturbance.x,"
                          << "disturbance.y,"
                          << "disturbance.z,"
                          << "Fd,";
            }

            foutparam << std::endl;
        }
        //!	time以降の値は桁数15桁の精度を持つ
        foutparam << std::setprecision(17);
        std::chrono::system_clock::time_point laptime =
            chrono::system_clock::now();
        auto nowtime = laptime - start_time;
        // foutparam
        //     << chrono::duration_cast<chrono::milliseconds>(nowtime).count() *
        //            1000
        //     << " s"
        //     << "\n";
        foutparam << chrono::duration_cast<chrono::seconds>(nowtime).count() /
                         60
                  << " m"
                  << "\n";

        double pressure;
        C Fb;

        //	output particles parameter to csv.
        //各時間での粒子のパラメータを出力する
        for (unsigned int i = 0; i < p->c.size(); i++) {
            for (unsigned int j = 0; j < p->c[i].size(); j++) {
                for (unsigned int k = 0; k < p->c[i][j].size(); k++) {
#if defined __SHAPE_CUBE__
                    if (p->flag[i][j][k] != BIT_NONE) {
#endif
                        // pressure = sqrt(pow(p->pressure[i][j][k].x, 2) +
                        //                 pow(p->pressure[i][j][k].y, 2) +
                        //                 pow(p->pressure[i][j][k].z, 2));
                        pressure = p->pressure[i][j][k].abs();
                        Fb.reset();
                        if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
                            Fb += UnitVectorCalc(p->Fb[i + 1][j][k].imv, p->Si[i][j][k]);
                        }
                        if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
                            Fb += UnitVectorCalc(p->Fb[i - 1][j][k].ipv, p->Si[i - 1][j][k]);
                        }
                        if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
                            // p->F[i][j][k].jpv = p->Fb[i][j + 1][k].jmv;
                            Fb += UnitVectorCalc(p->Fb[i][j + 1][k].jmv, p->Sj[i][j][k]);
                        }
                        if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
                            // Tensile and Share
                            Fb += UnitVectorCalc(p->Fb[i][j - 1][k].jpv, p->Sj[i][j - 1][k]);
                            // p->F[i][j][k].jmv = p->Fb[i][j - 1][k].jpv;
                        }

                        foutparam
                            << "(" << i << "." << j << "." << k << "),"
                            << reFlag[p->flag[i][j][k]] << ","
                            << std::bitset<8>(
                                   p->surround_particle_exsit[i][j][k])
                            << "," << p->i_specialflag[i][j][k]
                            << "," << time * param->m_dt * param->m_sheet_skip
                            << "," << p->new_c[i][j][k].x << ","
                            << p->new_c[i][j][k].y << "," << p->new_c[i][j][k].z
                            << "," << p->new_v[i][j][k].x << ","
                            << p->new_v[i][j][k].y << "," << p->new_v[i][j][k].z
                            << ",";
                        foutparam
                            << p->li[i][j][k].vector.x << ","
                            << p->li[i][j][k].vector.y << ","
                            << p->li[i][j][k].vector.z << ","
                            << p->lj[i][j][k].vector.x << ","
                            << p->lj[i][j][k].vector.y << ","
                            << p->lj[i][j][k].vector.z << ","
                            << p->li[i][j][k].norm << "," << p->lj[i][j][k].norm
                            << "," << p->g[i][j][k].x << "," << p->g[i][j][k].y
                            << "," << p->g[i][j][k].z << "," << p->mi[i][j][k].x
                            << "," << p->mi[i][j][k].y << ","
                            << p->mi[i][j][k].z << "," << p->mj[i][j][k].x
                            << "," << p->mj[i][j][k].y << ","
                            << p->mj[i][j][k].z << "," << p->Si[i][j][k].cp.norm
                            << "," << p->Sj[i][j][k].cp.norm << ","
                            << p->S[i][j][k].cp.vector.x << ","
                            << p->S[i][j][k].cp.vector.y << ","
                            << p->S[i][j][k].cp.vector.z << ","
                            << p->S[i][j][k].cp.norm << ","
                            << p->alphai[i][j][k] * 180 / math::pi() << ","
                            << p->alphaj[i][j][k] * 180 / math::pi() << ","
                            << p->etai[i][j][k] << "," << p->etaj[i][j][k]
                            << "," << p->diff_etai[i][j][k] << ","
                            << p->diff_etaj[i][j][k] << ","
                            << p->beta[i][j][k].pp * 180 / math::pi() << ","
                            << p->beta[i][j][k].pm * 180 / math::pi() << ","
                            << p->beta[i][j][k].mp * 180 / math::pi() << ","
                            << p->beta[i][j][k].mm * 180 / math::pi() << ","
                            << p->gamma[i][j][k].pp << ","
                            << p->gamma[i][j][k].pm << ","
                            << p->gamma[i][j][k].mp << ","
                            << p->gamma[i][j][k].mm << "," << p->hi[i][j][k]
                            << "," << p->hj[i][j][k] << "," << p->h_ave[i][j][k]
                            << "," << p->epsilonli[i][j][k] << ","
                            << p->epsilongj[i][j][k] << ","
                            << p->epsilonlj[i][j][k] << ","
                            << p->epsilongi[i][j][k] << "," << p->Ii[i][j][k]
                            << "," << p->Ij[i][j][k] << "," << p->Mi[i][j][k]
                            << "," << p->Mj[i][j][k] << ","
                            << p->pressure[i][j][k].x << ","
                            << p->pressure[i][j][k].y << ","
                            << p->pressure[i][j][k].z << "," << pressure << ",";

                        foutparam << p->angle_surface_sun[i][j][k] * 180 / math::pi() << ","
                                  << p->Fnormal[i][j][k].x << ","
                                  << p->Fnormal[i][j][k].y << ","
                                  << p->Fnormal[i][j][k].z << ","
                                  << p->Ftrans[i][j][k].x << ","
                                  << p->Ftrans[i][j][k].y << ","
                                  << p->Ftrans[i][j][k].z << ",";

                        foutparam << p->vc_Bottom[i][j][k].x << ","
                                  << p->vc_Bottom[i][j][k].y << ","
                                  << p->vc_Bottom[i][j][k].z << ","
                                  << p->vc_Top[i][j][k].x << ","
                                  << p->vc_Top[i][j][k].y << ","
                                  << p->vc_Top[i][j][k].z << ","
                                  << p->vc_Left[i][j][k].x << ","
                                  << p->vc_Left[i][j][k].y << ","
                                  << p->vc_Left[i][j][k].z << ","
                                  << p->vc_Right[i][j][k].x << ","
                                  << p->vc_Right[i][j][k].y << ","
                                  << p->vc_Right[i][j][k].z << ",";
                        foutparam
                            << p->Fti[i][j][k] << "," << p->Fti[i][j][k]
                            << ","
                            << p->Fsi[i][j][k].pp + p->Fsi[i][j][k].pm
                            << ","
                            << p->Fsi[i][j][k].pm + p->Fsi[i][j][k].pm
                            << ","
                            << p->Fsj[i][j][k].pp + p->Fsj[i][j][k].mp
                            << ","
                            << p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm
                            << ","
                            << p->Fb[i][j][k].ipv << ","
                            << p->Fb[i][j][k].imv << ","
                            << p->Fb[i][j][k].jpv << ","
                            << p->Fb[i][j][k].jmv << ","
                            << p->Fb[i][j][k].ipmv.x << ","
                            << p->Fb[i][j][k].ipmv.y << ","
                            << p->Fb[i][j][k].ipmv.z << ","
                            << p->Fb[i][j][k].jpmv.x << ","
                            << p->Fb[i][j][k].jpmv.y << ","
                            << p->Fb[i][j][k].jpmv.z << ","
                            << Fb.x << ","
                            << Fb.y << ","
                            << Fb.z << ","
                            << p->Fa[i][j][k] << "," << p->F[i][j][k].ip
                            << "," << p->F[i][j][k].im << ","
                            << p->F[i][j][k].jp << "," << p->F[i][j][k].jm
                            << "," << p->F[i][j][k].ipv << ","
                            << p->F[i][j][k].imv << "," << p->F[i][j][k].jpv
                            << "," << p->F[i][j][k].jmv << ","
                            << p->F[i][j][k].sv << "," << p->f[i][j][k].x
                            << "," << p->f[i][j][k].y << ","
                            << p->f[i][j][k].z << ","
                            << p->external_force[i][j][k].x << ","
                            << p->external_force[i][j][k].y << ","
                            << p->external_force[i][j][k].z << ",";
                        foutparam
                            << p->external_force_by_pressure[i][j][k].x << ","
                            << p->external_force_by_pressure[i][j][k].y << ","
                            << p->external_force_by_pressure[i][j][k].z << ",";
                        foutparam
                            << param->phi * 180 / math::pi() << ","
                            << param->theta * 180 / math::pi() << ","
                            << param->psi * 180 / math::pi() << ","
                            << param->phi_d << ","
                            << param->theta_d << ","
                            << param->psi_d << ","
                            << p->r[i][j][k].vector.x << ","
                            << p->r[i][j][k].vector.y << ","
                            << p->r[i][j][k].vector.z << ","
                            << p->v_rot[i][j][k].x << ","
                            << p->v_rot[i][j][k].y << ","
                            << p->v_rot[i][j][k].z << ","
                            << p->phi[i][j][k] * 180 / math::pi() << ","
                            << p->theta[i][j][k] * 180 / math::pi() << ","
                            << p->psi[i][j][k] * 180 / math::pi() << ","
                            << p->omega_phi[i][j][k] << ","
                            << p->omega_theta[i][j][k] << ","
                            << p->omega_psi[i][j][k] << ","
                            << p->omega[i][j][k].x << ","
                            << p->omega[i][j][k].y << ","
                            << p->omega[i][j][k].z << ","
                            << p->a_euler[i][j][k].x << ","
                            << p->a_euler[i][j][k].y << ","
                            << p->a_euler[i][j][k].z << ","
                            << p->F_Cen[i][j][k].x << ","
                            << p->F_Cen[i][j][k].y << ","
                            << p->F_Cen[i][j][k].z << ","
                            << p->F_Cor[i][j][k].x << ","
                            << p->F_Cor[i][j][k].y << ","
                            << p->F_Cor[i][j][k].z << ","
                            << p->F_Euler[i][j][k].x << ","
                            << p->F_Euler[i][j][k].y << ","
                            << p->F_Euler[i][j][k].z << ","
                            << p->F_roll[i][j][k].x << ","
                            << p->F_roll[i][j][k].y << ","
                            << p->F_roll[i][j][k].z << ",";

                        if (CylinderPressure &&
                            !param->boundary.cylinder_boundary) {
                            foutparam << p->omp[i][j][k].ci.x << ","
                                      << p->omp[i][j][k].ci.y << ","
                                      << p->omp[i][j][k].ci.z << ","
                                      << p->omp[i][j][k].g.x << ","
                                      << p->omp[i][j][k].g.y << ","
                                      << p->omp[i][j][k].g.z << ","
                                      << p->omp[i][j][k].li.vector.x << ","
                                      << p->omp[i][j][k].li.vector.y << ","
                                      << p->omp[i][j][k].li.vector.z << ","
                                      << p->omp[i][j][k].lj.vector.x << ","
                                      << p->omp[i][j][k].lj.vector.y << ","
                                      << p->omp[i][j][k].lj.vector.z << ","
                                      << p->omp[i][j][k].li.norm << ","
                                      << p->omp[i][j][k].lj.norm << ","
                                      << p->omp[i][j][k].mi.x << ","
                                      << p->omp[i][j][k].mi.y << ","
                                      << p->omp[i][j][k].mi.z << ","
                                      << p->omp[i][j][k].mj.x << ","
                                      << p->omp[i][j][k].mj.y << ","
                                      << p->omp[i][j][k].mj.z << ","
                                      << p->omp[i][j][k].Si.i.x << ","
                                      << p->omp[i][j][k].Si.i.y << ","
                                      << p->omp[i][j][k].Si.i.z << ","
                                      << normCalc(p->omp[i][j][k].Si.i) << ","
                                      << p->omp[i][j][k].Si.j.x << ","
                                      << p->omp[i][j][k].Si.j.y << ","
                                      << p->omp[i][j][k].Si.j.z << ","
                                      << normCalc(p->omp[i][j][k].Si.j) << ","
                                      << p->omp[i][j][k].Si.cp.norm << ","
                                      << p->omp[i][j][k].hi << ","
                                      << p->omp[i][j][k].epsilonli << ","
                                      << p->omp[i][j][k].epsilongj << ","
                                      << p->omp[i][j][k].Fti << ","
                                      << p->omp[i][j][k].Fsi.pp +
                                             p->omp[i][j][k].Fsi.pm
                                      << ","
                                      << p->omp[i][j][k].Fsi.pm +
                                             p->omp[i][j][k].Fsi.pm;
                            // << ","
                            // << p->omp[i][j][k].Fsj.pp +
                            // p->omp[i][j][k].Fsj.mp
                            // << ","
                            // << p->omp[i][j][k].Fsj.pm +
                            // p->omp[i][j][k].Fsj.mm;
                        }
                        if (param->add_disturbance) {
                            foutparam << p->disturbance[i][j][k].x << ","
                                      << p->disturbance[i][j][k].y << ","
                                      << p->disturbance[i][j][k].z << ","
                                      << p->Fd[i][j][k] << ",";
                        }
                        // foutparam << p->pressure[i][j][k].unit().x << ","
                        //           << p->pressure[i][j][k].unit().y << ","
                        //           << p->pressure[i][j][k].unit().z << ","
                        //           << p->S[i][j][k].cp.vector.unit().x << ","
                        //           << p->S[i][j][k].cp.vector.unit().y << ","
                        //           << p->S[i][j][k].cp.vector.unit().z << ",";

                        foutparam << "\n";
#if defined __SHAPE_CUBE__
                    }
#endif
                }
            }
        }
        foutparam << endl;
    }

    /**
     * @brief
     * 引数の時間が1列目になるようなdatファイルとして出力する
     * @param[in]	double const& time：現在の時間
     * @note		呼び出されるたびに、追記する
     * 自作。後付した
     */
    void OutputInitial() {
        //!	ofstreamオブジェクトのfoutcxを定義、引数がファイルのパス, モード
        basic->create_utf8_stream(initial_file.c_str());
        ofstream foutinitial(initial_file.c_str(), ios_base::app);

        foutinitial << "(i.j.k),"
                    << "Flag,"
                    << "FlagNum,"
                    << "SpecialFlagNum"
                    << "X-axis,"
                    << "Y-axis,"
                    << "Z-axis,"
                    << "V0.x,"
                    << "V0.y,"
                    << "V0.z,"
                    << "g0.x,"
                    << "g0.y,"
                    << "g0.z,"
                    << "li0,"
                    << "lj0,"
                    << "S_i0.cp,"
                    << "S_j0.cp,"
                    << "S0.cp,"
                    << "α_i,"
                    << "α_j,"
                    << "ηi0,"
                    << "ηj0,"
                    << "β0++,"
                    << "β0+-,"
                    << "β0-+,"
                    << "β0--,";
        if (CylinderPressure && !param->boundary.cylinder_boundary) {
            foutinitial << "omp.li0,"
                        << "omp.li0,";
        }
        foutinitial << endl;

        //!	time以降の値は桁数15桁の精度を持つ
        foutinitial << std::setprecision(17);

        //	座標と速度のxyz成分を各パスのファイルに出力する
        for (int i = 0; i < local_iNum; i++) {
            for (int j = 0; j < local_jNum; j++) {
                for (int k = 0; k < local_kNum; k++) {
#if defined __SHAPE_CUBE__
                    if (p->flag[i][j][k] != BIT_NONE) {
#endif
                        foutinitial
                            << "(" << i << "." << j << "." << k << "),"
                            << reFlag[p->flag[i][j][k]] << ","
                            << std::bitset<8>(p->flag[i][j][k]) << ","
                            << p->i_specialflag[i][j][k] << ","
                            << p->c[i][j][k].x << "," << p->c[i][j][k].y << ","
                            << p->c[i][j][k].z << "," << p->v[i][j][k].x << ","
                            << p->v[i][j][k].y << "," << p->v[i][j][k].z << ","
                            << p->g0[i][j][k].x << "," << p->g0[i][j][k].y
                            << "," << p->g0[i][j][k].z << "," << p->li0[i][j][k]
                            << "," << p->lj0[i][j][k] << "," << p->Si0[i][j][k]
                            << "," << p->Sj0[i][j][k] << "," << p->S0[i][j][k]
                            << "," << p->alphai[i][j][k] * 180 / math::pi()
                            << "," << p->alphaj[i][j][k] * 180 / math::pi()
                            << "," << p->etai0[i][j][k] << ","
                            << p->etaj0[i][j][k] << ","
                            << p->beta[i][j][k].pp * 180 / math::pi() << ","
                            << p->beta[i][j][k].pm * 180 / math::pi() << ","
                            << p->beta[i][j][k].mp * 180 / math::pi() << ","
                            << p->beta[i][j][k].mm * 180 / math::pi()
#ifdef __CYLINDER_NON_BOUNDARY__
                            << "," << p->omp[i][j][k].li0 << ","
                            << p->omp[i][j][k].lj0
#endif
                            << ",\n";
#if defined __SHAPE_CUBE__
                    }
#endif
                }
            }
        }
        foutinitial << "\n"
                    << endl;
        foutinitial.close();
    }

    /**
     * @brief
     * 引数の時間が1列目になるようなdatファイルとして出力する
     * @param[in]	double const& time：現在の時間
     * @note		呼び出されるたびに、追記する
     * 自作。後付した
     */
    void OutputCondition() {
        //!	ofstreamオブジェクトのfoutcxを定義、引数がファイルのパス, モード
        basic->create_utf8_stream(condition_file.c_str());
        ofstream foutcondition(condition_file.c_str(), ios_base::app);
        std::vector<std::pair<std::string, double>> out_condition = {
            {"iNum", param->m_iNum},
            {"jNum", param->m_jNum},
            {"kNum", param->m_kNum},
        };
        out_condition.reserve(100);
        out_condition.push_back({"m_tmax", param->m_tmax});
        out_condition.push_back({"m_dt", param->m_dt});
        out_condition.push_back({"m_sheet_skip", param->m_sheet_skip});
        out_condition.push_back({"Cv", param->Cv});
        out_condition.push_back({"m_Cv", param->m_Cv});
        out_condition.push_back({"Cei", param->C_EI});
        out_condition.push_back({"Cae", param->C_AE});
        out_condition.push_back({"Lref", param->Lref});
        out_condition.push_back({"Vref", param->Vref});
        out_condition.push_back({"Pref", param->Pref});
        out_condition.push_back({"Length_x", param->Length_x});
        out_condition.push_back({"Length_y", param->Length_y});
        out_condition.push_back({"h0", param->h0});
        out_condition.push_back({"ρ", param->m_rho});
        out_condition.push_back({"ν", param->m_nu});
        out_condition.push_back({"Pc", param->Pc});
        out_condition.push_back({"Psun", param->Psun});
        out_condition.push_back({"Psun_angle_phi", param->Psun_angle_phi * 180 / math::pi()});
        out_condition.push_back({"Psun_angle_theta", param->Psun_angle_theta * 180 / math::pi()});
        out_condition.push_back({"Psun_angle_psi", param->Psun_angle_psi * 180 / math::pi()});
        out_condition.push_back({"Psun_angle_s_phi", param->Psun_angle_s_phi * 180 / math::pi()});
        out_condition.push_back({"Psun_angle_s_theta", param->Psun_angle_s_theta * 180 / math::pi()});
        out_condition.push_back({"m_E", param->m_E});
        out_condition.push_back({"m_Lref_x", param->m_Lref_x});
        out_condition.push_back({"m_Lref_y", param->m_Lref_y});
        out_condition.push_back({"m_h0", param->m_h0});
        out_condition.push_back({"m_Pc", param->m_Pc});
        out_condition.push_back({"m_k", param->m_k});
        out_condition.push_back({"m_fx", param->m_fx});
        out_condition.push_back({"m_fy", param->m_fy});
        out_condition.push_back({"m_fz", param->m_fz});
        out_condition.push_back({"Reflectance", param->reflectance});
        out_condition.push_back({"Specularity", param->specularity});
        out_condition.push_back(
            {"disturbance_range", param->disturbance_range});
        out_condition.push_back(
            {"add_disturbance_range", param->add_disturbance});
        out_condition.push_back(
            {"cylinder_boundary", param->boundary.cylinder_boundary});
        out_condition.push_back({"force_release", param->force_release});

        out_condition.push_back(
            {"RightShare", param->boundary.right_share_fix});
        out_condition.push_back({"LeftShare", param->boundary.left_share_fix});
        out_condition.push_back({"TopShare", param->boundary.top_share_fix});
        out_condition.push_back(
            {"BottomShare", param->boundary.bottom_share_fix});
        out_condition.push_back({"LeftBend", param->boundary.left_bend_fix});
        out_condition.push_back({"RightBend", param->boundary.right_bend_fix});
        out_condition.push_back({"TopBend", param->boundary.top_bend_fix});
        out_condition.push_back(
            {"BottomBend", param->boundary.bottom_bend_fix});
        out_condition.push_back({"LeftFree", param->boundary.left_free});
        out_condition.push_back({"RightFree", param->boundary.right_free});
        out_condition.push_back({"TopFree", param->boundary.top_free});
        out_condition.push_back(
            {"BottomFree", param->boundary.bottom_free});
        out_condition.push_back(
            {"ObliqueRigid", param->oblique_rigid});
        out_condition.push_back(
            {"RollInertiaSystem", param->roll_inertia_system});
        out_condition.push_back({"initial_phi", param->phi});
        out_condition.push_back({"initial_theta", param->theta});
        out_condition.push_back({"initial_psi", param->psi});
        out_condition.push_back({"omega_phi", param->initial_phi_d});
        out_condition.push_back({"omega_theta", param->initial_theta_d});
        out_condition.push_back({"omega_psi", param->initial_psi_d});
        out_condition.push_back({"angular_acceleration_phi", param->initial_phi_dd});
        out_condition.push_back({"angular_acceleration_theta", param->initial_theta_dd});
        out_condition.push_back({"angular_acceleration_psi", param->initial_psi_dd});
        out_condition.push_back({"Px", param->pressure_initial.x});
        out_condition.push_back({"Py", param->pressure_initial.y});
        out_condition.push_back({"Pz", param->pressure_initial.z});

        std::vector<std::pair<std::string, std::string>>
            out_condition_string_pair;
        out_condition_string_pair.reserve(100);
        out_condition_string_pair.push_back(
            {"grid_pattern", param->grid_pattern});
        out_condition_string_pair.push_back(
            {"analysis_shape", param->analysis_shape});
        out_condition_string_pair.push_back(
            {"ObliqueMove", param->oblique_move});

        // param::parameter readfile(param->read_filename);
        // string Ret = readfile.get<string>("RightMove");
        // out_condition_string_pair.push_back({"RigthMove", Ret});
        // string Ret = readfile.get<string>("LeftMove");
        // out_condition_string_pair.push_back({"LeftMove", Ret});
        // string Ret = readfile.get<string>("TopMove");
        // out_condition_string_pair.push_back({"TopMove", Ret});
        // string Ret = readfile.get<string>("BottomMove");
        // out_condition_string_pair.push_back({"BottomMove", Ret});
        out_condition_string_pair.push_back(
            {"RightMove",
             param->boundary.get_boundary_move(param->boundary.right_move)});
        out_condition_string_pair.push_back(
            {"LeftMove",
             param->boundary.get_boundary_move(param->boundary.left_move)});
        out_condition_string_pair.push_back(
            {"TopMove",
             param->boundary.get_boundary_move(param->boundary.top_move)});
        out_condition_string_pair.push_back(
            {"BottomMove",
             param->boundary.get_boundary_move(param->boundary.bottom_move)});

        out_condition_string_pair.push_back({"Psun_angle_axis", param->Psun_angle_axis});

        if (SimpleTensile) {
            out_condition_string_pair.push_back(
                {"simuation is", "SimpleTensile"});
        }
        if (SimpleShare) {
            out_condition_string_pair.push_back(
                {"simuation is", "SimpleShare"});
        }
        if (SimpleBend) {
            out_condition_string_pair.push_back({"simuation is", "SimpleBend"});
        }
        if (SimpleCompression) {
            out_condition_string_pair.push_back(
                {"simuation is", "SimpleCompression"});
        }
        if (DiagonalTensile) {
            out_condition_string_pair.push_back(
                {"simuation is", "DiagonalTensile"});
        }
        if (CubePressure) {
            out_condition_string_pair.push_back(
                {"simuation is", "CubePressure"});
        }
        if (CylinderPressure) {
            out_condition_string_pair.push_back(
                {"simuation is", "CylinderPressure"});
        }
        if (SolarSail) {
            out_condition_string_pair.push_back({"simuation is", "SolarSail"});
        }
        // out_condition_string_pair.push_back(
        //     {"RightBend", param->boundary.right_bend_fix});
        // out_condition_string_pair.push_back(
        //     {"LeftBend", param->boundary.left_bend_fix});
        // out_condition_string_pair.push_back(
        //     {"BottomBend", param->boundary.bottom_bend_fix});
        // out_condition_string_pair.push_back(
        //     {"TopBend", param->boundary.top_bend_fix});
        // out_condition_string_pair.push_back(
        //     {"RightShare", param->boundary.right_share_fix});
        // out_condition_string_pair.push_back(
        //     {"LeftShare", param->boundary.left_share_fix});
        // out_condition_string_pair.push_back(
        //     {"BottomShare", param->boundary.bottom_share_fix});
        // out_condition_string_pair.push_back(
        //     {"TopShare", param->boundary.top_share_fix});
        // out_condition_string_pair.push_back(
        //     {"RightMove", param->boundary.right_move});
        // out_condition_string_pair.push_back(
        //     {"LeftMove", param->boundary.left_move});
        // out_condition_string_pair.push_back(
        //     {"TopMove", param->boundary.top_move});
        // out_condition_string_pair.push_back(
        //     {"BottomMove", param->boundary.bottom_move});

        std::cout << "------------------ condition ------------------"
                  << std::endl;
        foutcondition << std::setprecision(17);
        for (const auto& [key, value] : out_condition) {
            foutcondition << key << "," << value << "\n"
                          << std::flush;
            std::cout << key << "," << value << "\n"
                      << std::flush;
        }
        for (const auto& [key, value] : out_condition_string_pair) {
            foutcondition << key << "," << value << "\n"
                          << std::flush;
            std::cout << key << "," << value << "\n"
                      << std::flush;
        }
        foutcondition.close();
        std::cout << "-----------------------------------------------"
                  << std::endl;
    }

    /**
     * @brief standard output current parameter
     *
     * @param time
     * @param pre_vector
     * @return true diverrge and stop this simulation.
     * @return false not diverge
     */
    bool show_current_param(const int& time, double& pre_vector,
                            double& pre_theta) {
        // execution monitor (現在の計算時間を表示する)
        //
        std::cout << "\r"
                  << "time: " << time * param->m_dt * param->m_sheet_skip
                  << std::setprecision(15) << "," << std::string(2, ' ');
        std::cout << std::setprecision(5);

        double divergence = 10;
        if (SimpleTensile) {
            int itr_x = p->v.size() - 1;
            int itr_y = p->v[0].size() / 2;
            int itr_z = p->v[0][0].size() / 2;

            cout << std::setprecision(9);
            std::cout << "c.x:" << p->c[itr_x][itr_y][itr_z].x << ','
                      << std::string(3, ' ') << std::setprecision(5)
                      << "v.x:" << p->v[itr_x][itr_y][itr_z].x << ","
                      << std::string(3, ' ')
                      << "a.x:" << p->v[itr_x][itr_y][itr_z].x - pre_vector
                      << std::string(3, ' ') << std::flush;
            if (divergence <= fabs(p->v[itr_x][itr_y][itr_z].x)) {
                std::cout << std::endl;
                std::cout << "Divergence" << std::endl;
                return true;
            };
            pre_vector = p->v[itr_x][itr_y][itr_z].x;
            return false;
        } else if (SimpleShare) {
            int itr_x = p->v.size() - 1;
            int itr_y = p->v[0].size() - 1;
            int itr_z = p->v[0][0].size() / 2;

            std::cout << "c.y:" << p->c[itr_x][itr_y][itr_z].y << ','
                      << std::string(3, ' ')
                      << "v.y:" << p->v[itr_x][itr_y][itr_z].y << ","
                      << std::string(3, ' ')
                      << "a.y:" << p->v[itr_x][itr_y][itr_z].y - pre_vector
                      << std::string(3, ' ') << std::flush;
            if (divergence <= fabs(p->v[itr_x][itr_y][itr_z].x)) {
                std::cout << std::endl;
                std::cout << "Divergence" << std::endl;
                return true;
            }
            pre_vector = p->v[itr_x][itr_y][itr_z].y;
            return false;
        } else if (SimpleBend) {
            int itr_x = p->v.size() - 1;
            int itr_y = p->v[0].size() / 2;
            int itr_z = p->v[0][0].size() / 2;

            std::cout << "c.z:" << p->c[itr_x][itr_y][itr_z].z << ','
                      << std::string(3, ' ')
                      << "v.z:" << p->v[itr_x][itr_y][itr_z].z << ","
                      << std::string(3, ' ')
                      << "a.z:" << p->v[itr_x][itr_y][itr_z].z - pre_vector
                      << std::string(3, ' ') << std::flush;
            // if (divergence <= fabs(p->v[itr_x][itr_y][itr_z].z)) {
            //     std::cout << std::endl;
            //     std::cout << "Divergence" << std::endl;
            //     return true;
            // }
            pre_vector = p->v[itr_x][itr_y][itr_z].z;
            return false;
        } else if (DiagonalTensile) {
            int itr_x = p->v.size() - 1;
            int itr_y = p->v[0].size() - 1;
            int itr_z = p->v[0][0].size() - 1;

            std::cout << "c.xy:"
                      << sqrt(pow(p->c[itr_x][itr_y][itr_z].x, 2) +
                              pow(p->c[itr_x][itr_y][itr_z].y, 2))
                      << std::string(3, ' ') << "v.xy:"
                      << sqrt(pow(p->v[itr_x][itr_y][itr_z].x, 2) +
                              pow(p->v[itr_x][itr_y][itr_z].y, 2))
                      << std::string(3, ' ') << ","
                      << "a.xy:"
                      << sqrt(pow(p->v[itr_x][itr_y][itr_z].x, 2) +
                              pow(p->v[itr_x][itr_y][itr_z].y, 2)) -
                             pre_vector
                      << std::string(3, ' ') << std::flush;
            if (divergence <= sqrt(pow(p->v[itr_x][itr_y][itr_z].x, 2) +
                                   pow(p->v[itr_x][itr_y][itr_z].y, 2))) {
                std::cout << std::endl;
                std::cout << "Divergence" << std::endl;
                return true;
            }
            pre_vector = sqrt(pow(p->v[itr_x][itr_y][itr_z].x, 2) +
                              pow(p->v[itr_x][itr_y][itr_z].y, 2));
            return false;
        } else if (SimpleCompression) {
            divergence = 10 ^ 4;
            int itr_x  = p->v.size() - 1;
            int itr_y  = p->v[0].size() / 2;
            int itr_z  = p->v[0][0].size() / 2;

            std::cout << "c.x:" << p->c[itr_x][itr_y][itr_z].x << ','
                      << std::string(3, ' ')
                      << "v.x:" << p->v[itr_x][itr_y][itr_z].x << ','
                      << std::string(3, ' ')
                      << "a.x:" << p->v[itr_x][itr_y][itr_z].x - pre_vector
                      << std::string(3, ' ') << std::flush;
            if (divergence <= fabs(p->v[itr_x][itr_y][itr_z].x)) {
                std::cout << std::endl;
                std::cout << "Divergence" << std::endl;
                return true;
            };
            pre_vector = p->v[itr_x][itr_y][itr_z].x;
            return false;
        } else if (CubePressure) {
            int itr_x = p->c.size() / 2;
            int itr_y = p->c[0].size() / 2;
            int itr_z = p->c[0][0].size() / 2;

            std::cout << "v.z:" << p->v[itr_x][itr_y][itr_z].z << ","
                      << std::string(10, ' ')
                      << "a.z:" << p->v[itr_x][itr_y][itr_z].z - pre_vector
                      << std::string(10, ' ') << std::flush;
            if (divergence <= fabs(p->v[itr_x][itr_y][itr_z].z)) {
                std::cout << std::endl;
                std::cout << "Divergence" << std::endl;
                return true;
            }
            pre_vector = p->v[itr_x][itr_y][itr_z].z;

            return false;
        } else if (CylinderPressure) {
            int itr_x = p->c.size() / 2;
            int itr_y = p->c[0].size() / 2;
            int itr_z = p->c[0][0].size() / 2;

            std::cout << "r:"
                      << sqrt(pow(p->c[itr_x][itr_y][itr_z].x, 2) +
                              pow(p->c[itr_x][itr_y][itr_z].y, 2))
                      << std::string(10, ' ') << std::flush;
            if (divergence <= sqrt(pow(p->c[itr_x][itr_y][itr_z].x, 2) +
                                   pow(p->c[itr_x][itr_y][itr_z].y, 2))) {
                std::cout << std::endl;
                std::cout << "Divergence" << std::endl;
                return true;
            }
            return false;
        } else if (SimplePressure) {
            int itr_x = p->v.size() / 2;
            int itr_y = p->v[0].size() / 2;
            int itr_z = p->v[0][0].size() / 2;

            std::cout << "c.z:" << p->c[itr_x][itr_y][itr_z].z
                      << std::string(3, ' ')
                      << "v.z:" << p->v[itr_x][itr_y][itr_z].z << ","
                      << std::string(3, ' ')
                      << "a.z:" << p->v[itr_x][itr_y][itr_z].z - pre_vector
                      << std::string(3, ' ') << std::flush;
            if (divergence <= fabs(p->v[itr_x][itr_y][itr_z].z)) {
                std::cout << std::endl;
                std::cout << "Divergence" << std::endl;
                return true;
            }
            pre_vector = p->v[itr_x][itr_y][itr_z].z;
            return false;
        } else if (PlateRevolution) {
            int itr_x = p->v.size() - 1;
            int itr_y = p->v[0].size() - 1;
            int itr_z = p->v[0][0].size() - 1;

            int itr_center_x = p->c.size() / 2;
            int itr_center_y = p->c[itr_center_x].size() / 2;
            int itr_center_z = p->c[itr_center_x][itr_center_y].size() / 2;

            double relative_coordinate_x =
                p->c[itr_x][itr_y][itr_z].x -
                p->c[itr_center_x][itr_center_y][itr_center_z].x;
            double relative_coordinate_y =
                p->c[itr_x][itr_y][itr_z].y -
                p->c[itr_center_x][itr_center_y][itr_center_z].y;
            double relative_length_xy =
                sqrt(relative_coordinate_x * relative_coordinate_x +
                     relative_coordinate_y * relative_coordinate_y);
            double theta = acos(relative_coordinate_x / relative_length_xy);
            if (relative_coordinate_y < 0) {
                theta += math::pi();
            }
            theta *= 180 / math::pi();
            std::cout << "c.xy:"
                      << sqrt(pow(p->c[itr_x][itr_y][itr_z].x, 2) +
                              pow(p->c[itr_x][itr_y][itr_z].y, 2))
                      << std::string(3, ' ') << "v.xy:"
                      << sqrt(pow(p->v[itr_x][itr_y][itr_z].x, 2) +
                              pow(p->v[itr_x][itr_y][itr_z].y, 2))
                      << std::string(3, ' ') << ","
                      << "a.xy:"
                      << sqrt(pow(p->v[itr_x][itr_y][itr_z].x, 2) +
                              pow(p->v[itr_x][itr_y][itr_z].y, 2)) -
                             pre_vector
                      << std::flush;
            cout << "," << string(3, ' ') << "theta:" << theta << ","
                 << string(3, ' ') << "theta_a:" << theta - pre_theta
                 << string(5, ' ') << flush;
            if (divergence <= sqrt(pow(p->c[itr_x][itr_y][itr_z].x, 2) +
                                   pow(p->c[itr_x][itr_y][itr_z].y, 2))) {
                std::cout << std::endl;
                std::cout << "Divergence" << std::endl;
                return true;
            }
            pre_theta  = theta;
            pre_vector = sqrt(pow(p->v[itr_x][itr_y][itr_z].x, 2) +
                              pow(p->v[itr_x][itr_y][itr_z].y, 2));
            return false;
        } else if (SolarSail) {
            int itr_x = p->v.size() - 1;
            int itr_y = p->v[0].size() / 2;
            int itr_z = p->v[0][0].size() / 2;

            // int itr_center_x = p->c.size() / 2;
            // int itr_center_y = p->c[itr_center_x].size() / 2;
            // int itr_center_z = p->c[itr_center_x][itr_center_y].size() / 2;

            // angle
            // double relative_coordinate_x =
            //     p->c[itr_x][itr_y][itr_z].x -
            //     p->c[itr_center_x][itr_center_y][itr_center_z].x;
            // double relative_coordinate_y =
            //     p->c[itr_x][itr_y][itr_z].y -
            //     p->c[itr_center_x][itr_center_y][itr_center_z].y;
            // double relative_length_xy =
            //     sqrt(relative_coordinate_x * relative_coordinate_x +
            //          relative_coordinate_y * relative_coordinate_y);
            // double theta = acos(relative_coordinate_x / relative_length_xy);
            // if (relative_coordinate_y < 0) {
            //     theta += math::pi();
            // }
            // theta *= 180 / math::pi();

            std::cout << "c.z:" << p->c[itr_x][itr_y][itr_z].z << ","
                      << std::string(3, ' ')
                      << "v.z:" << p->v[itr_x][itr_y][itr_z].z << ","
                      << std::string(3, ' ')
                      << "a.z:" << p->v[itr_x][itr_y][itr_z].z - pre_vector
                      << std::flush;
            cout << ","
                 << std::string(3, ' ')
                 << "phi:" << param->phi
                 << ","
                 << std::string(3, ' ')
                 << "theta:" << param->theta
                 << ","
                 << std::string(3, ' ')
                 << "psi:" << param->psi
                 << flush;
            // angle
            // cout << "," << string(3, ' ') << "theta:" << theta << ","
            //      << string(3, ' ') << "theta_a:" << theta - pre_theta
            //      << string(5, ' ') << flush;
            if (divergence <= sqrt(pow(p->c[itr_x][itr_y][itr_z].x, 2) +
                                   pow(p->c[itr_x][itr_y][itr_z].y, 2))) {
                std::cout << std::endl;
                std::cout << "Divergence" << std::endl;
                return true;
            }
            // pre_theta  = theta;
            pre_vector = p->v[itr_x][itr_y][itr_z].z;
            return false;
        } else if (!(SimplePressure || CylinderPressure || CubePressure)) {
            int itr_x = p->h_ave.size() / 2;
            int itr_y = p->h_ave[0].size() / 2;
            int itr_z = p->h_ave[0][0].size() / 2;

            std::cout << "h:" << p->h_ave[itr_x][itr_y][itr_z]
                      << std::string(10, ' ') << std::flush;
            if (divergence <= fabs(p->h_ave[itr_x][itr_y][itr_z])) {
                std::cout << std::endl;
                std::cout << "Divergence" << std::endl;
                return true;
            }
            return false;
        }

        cout << "Unexpected analysis condition./n Please check define "
                "for "
                "definition"
             << endl;
        return true;
    }

    void dataCalc();
    typedef void (MultiParticle::*CALC_FUNC)(int const&, int const&);
    void OldVirtualParticleCalc(int const&, int const&, int const&);
    void VirtualParticleCalc(const int&, const int&, const int&);
    void ThicknessCalc(int const&, int const&, int const&);
    void ForceCalc(int const&, int const&, int const&);
    // void InertiaCalc(const int&, const int&, const int&);
    void InfluenceAreaCalc(const int&, const int&, const int&);
    void TensileForceCalc(const int&, const int&, const int&);
    void ShareForceCalc(const int&, const int&, const int&);
    void BendForceCalc(const int&, const int&, const int&);
    void ContradictBendForceCalc(const int&, const int&, const int&);
    void AirForceCalc(const int&, const int&, const int&);
    void RotationInertiaForceCalc(const int&, const int&, const int&);
    void ExternalForceCalc(const int&, const int&, const int&);
    void MoveParticleByRungeKutta(const int&, const int&, const int&); // ルンゲクッタ法を用いて粒子を動かす
    void GetNewCoordinate(int const&, int const&, int const&);
    void lCalc(Vector&, C const&, C const&);
    double epsilonlCulc(double const&, double const&);
    void mCalc(C&, C const&, C const&);
    void gCalc(C&, C const&, C const&);
    void gCalc(C&, C const&, C const&, C const&, C const&);
    double angleCalc(C const&, C const&, C const&);
    double angleCalc2(C const&, C const&, C const&, int);
    double angleCalc2(const C&, const C&, const C&, const string&);
    double gammaCalc(double const&, double const&);
    double hCalc(double const&, double const&);
    double epsilongCalc(double const&, double const&);
    double FsCalc(double const&, double const&, double const&);
    double FtCalc(double const&, double const&, double const&, double const&);
    double etaCalc(double const&, double const&, double const&);
    double MCalc(double const&, double const&, double const&);
    double MCalc(double const&, double const&, double const&, double);
    double get_random();
    void disturbance_Calc(C&, double const&);

    void fConv(int const&, int const&, int const&);

    double innerProductCalc(C const&, C const&);
    void crossProductCalc(C&, C const&, C const&);
    double normCalc(C const&);
    double normCalcV2(C const&, C const&);

    void RK4M(double&, double&, double const&, double const&);
    double RK4One(double const&);
    double RK4Two(double const&, double const&, double const&);
    void RK4M(double&, double&, const double&, const double&, const double&);
    double RK4Two(const double&, const double&, const double&, const double&);

    C UnitVectorCalc(const double&, const Area&);
    C UnitVectorCalc(const double&, const Vector&);
};

/**
 * @brief
 *
 */
class ChangeProcessEachParticle {
    Particles p;

    ChangeProcessEachParticle();
    ~ChangeProcessEachParticle();
    // p.external_force;
};
