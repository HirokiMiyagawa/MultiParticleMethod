/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file
 * @brief
 * @details
 * ///////////////////////////////////////////////////////////////////////////////
 */

#ifndef __INCLUDED_PARAMS_HPP__
#define __INCLUDED_PARAMS_HPP__

using namespace std;

/* ifdef change to constexpr */
#ifdef __CUBE_PRESSURE__
constexpr bool CubePressure = true;
#else
constexpr bool CubePressure      = false;
#endif
#ifdef __SIMPLE_TENSILE__
constexpr bool SimpleTensile = true;
#else
constexpr bool SimpleTensile     = false;
#endif
#ifdef __SIMPLE_SHARE__
constexpr bool SimpleShare = true;
#else
constexpr bool SimpleShare       = false;
#endif
#ifdef __SIMPLE_BEND__
constexpr bool SimpleBend = true;
#else
constexpr bool SimpleBend        = false;
#endif
#ifdef __SIMPLE_PRESSURE__
constexpr bool SimplePressure = true;
#else
constexpr bool SimplePressure    = false;
#endif
#ifdef __SIMPLE_COMPRESSION__
constexpr bool SimpleCompression = true;
#else
constexpr bool SimpleCompression = false;
#endif
#ifdef __DIAGONAL_TENSILE__
constexpr bool DiagonalTensile = true;
#else
constexpr bool DiagonalTensile   = false;
#endif
#ifdef __Plate_Revolution__
constexpr bool PlateRevolution = true;
#else
constexpr bool PlateRevolution   = false;
#endif
#ifdef __CYLINDER_PRESSURE__
constexpr bool CylinderPressure = true;
#else
constexpr bool CylinderPressure  = false;
#endif

#ifdef __SUPPORT_SHARE__
constexpr bool SupportShare = true;
#else
constexpr bool SupportShare      = false;
#endif
#ifdef __Natural_Frequency__
constexpr bool NaturalFrequency = true;
#else
constexpr bool NaturalFrequency  = false;
#endif
#ifdef __Oblique__
constexpr bool Oblique = true;
#else
constexpr bool Oblique           = false;
#endif
#ifdef __SolarSail__
constexpr bool SolarSail = true;
#else
constexpr bool SolarSail         = false;
#endif

#include <iostream>

#include "InputParam.hpp"
#include "DataSet.hpp"
#include "Basic.hpp"
#include "MatrixCalc.hpp"

class Params {
    param::parameter* param;

   public:
    std::string read_filename;
    //! 粒子の初期座標の入った座標
    std::string read_PositionFile;
    //! i方向の粒子数
    int m_iNum;
    //! j方向の粒子数
    int m_jNum;
    //! k方向の粒子数
    int m_kNum;
    //! csvに出力するまでの繰り返し数。N回の計算ごとに出力する
    int m_sheet_skip;

    //! 基準長さ 100 [mm]
    double Lref;
    //! 基準速度 100 [mm]
    double Vref;
    //! 基準圧力 35.5 * 10^-8 [N/mm^2]
    double Pref;
    //! Pressure on particle [N/mm^2]
    double Pc;
    double m_Pc;
    //! Pressure by sun light
    double Psun;
    //! Pressure by sun light angle axis (default: zyz)
    string Psun_angle_axis;
    //! Pressure by sun light angle 1 (input degree. save radian)
    double Psun_angle_phi;
    //! Pressure by sun light angle 2
    double Psun_angle_theta;
    //! Pressure by sun light angle 3
    double Psun_angle_psi;

    //! Pressure by sun light angle z for Spherical Coordinate
    double Psun_angle_s_theta;
    //! Pressure by sun light angle plate for Spherical Coordinate
    double Psun_angle_s_phi;

    //! Reflectance
    double reflectance;
    //! Specularity
    double specularity;

    double Length_x;
    double Length_y;
    //! ヤング率 [N/mm^2 MPa] / 野里さんのE = 35.5 MPaを使用している
    double m_E;
    //! 折り目用の新しいヤング率
    double m_newE;
    //! 無次元化した基準長さ (膜の縦と横の長さ)
    double m_Lref_x;
    double m_Lref_y;
    //! 無次元化した膜厚、膜厚比 [-]
    double m_h0;
    //! 無次元化した膜厚(隅)、膜厚比 [-] h_corner (only cube)
    double m_hc0;
    //! 初期膜厚 [mm]
    double h0;
    //! 密度 [kg/mm^3] (C_EIが無次元量になるような値)
    double m_rho;
    //! 水の密度 [kg/mm^3]
    double water_rho;
    //! 比重
    double specific_gravity;
    //! poason ratio (ポアソン比)
    double m_nu;
    //! Cv * m_kが代入されている。
    double m_Cv;
    //! 数値粘性係数。論文によると0.01-10.0程度の正の定数。
    double Cv;

    //! 終了時間
    double m_tmax;
    //! ファイルを分ける頻度 [回]
    int div_file;
    //! 荷重係数のノルム
    double m_k;
    //!	膜厚・ヤング率に依らず、同様なひずみとなるように外力を設定するための荷重係数
    //! X
    double m_kx;
    //! 荷重係数 Y
    double m_ky;
    //! 荷重係数 Z
    double m_kz;
    //! external force
    double fe;
    //! 無次元化した外力 (x方向の分布荷重)
    double m_fx;
    //! y方向の力？
    double m_fy;
    //! z方向の力？
    double m_fz;

    BoundaryCondition boundary;

    std::string analysis_shape;
    bool add_disturbance;
    std::string grid_pattern;
    bool force_release;
    bool oblique_rigid;

    // 回転による慣性力を考慮する
    bool roll_inertia_system;
    string oblique_move;
    double initial_phi_d;
    double initial_theta_d;
    double initial_psi_d;
    double initial_phi_dd;
    double initial_theta_dd;
    double initial_psi_dd;
    // セイル全体の回転 (system rotation)
    double phi;
    double theta;
    double psi;
    double phi_d;
    double theta_d;
    double psi_d;
    double pre_phi_d;
    double pre_theta_d;
    double pre_psi_d;
    double phi_dd;
    double theta_dd;
    double psi_dd;

    double m_phi_d;
    double m_theta_d;
    double m_psi_d;
    double m_phi_dd;
    double m_theta_dd;
    double m_psi_dd;

    C omega_system;
    C a_euler_system;

    //! 擾乱の範囲
    double disturbance_range;
    string disturbance_mode;
    //! 対角線方向の無次元化した集中荷重 [N]
    double m_fe;
    //! 刻み時間？
    double m_dt;

    //! 細かく区切る回数。 境界面付近のn個の粒子をm倍の精度にする
    double div_num;

    //! 境界面付近でほしい精度（他の場所の何倍の精度（間隔の短さ）が欲しいのか）
    double minuteness;

    //! 角の補強変数
    double edge_reinforce;
    //! 角の膜厚
    double thicken_coefficient;

    string m_paramsFile;
    bool m_fileExistFlag;

    //! 弾性力と慣性力の比を表す無次元パラメータ
    double C_EI;
    //! 空気力と弾性力の比を表す無次元パラメータ
    double C_AE;

    //! Matrix for Pressure
    RotationMatrixCalc rotation_matrix;
    C pressure_for_all;
    C pressure_initial;
    vector<double> pressure_matrix_unit;

    SphericalCoordinate spherical_coordinate;

    //! 1/(1-(ν^2)) 弾性力 Ftの計算で使用する
    double m_preCalc1;
    //! 1/(4*(1+ν)) せん断力 Fsの計算で使用する
    double m_preCalc2;
    //! ν/(1-ν) 膜厚 hの計算で使用する
    double m_preCalc3;
    //! 1/(12*(1-(ν^2))) モーメント Mの計算で使用する
    double m_preCalc4;

    //! (1+rs) r:reflectance, s:Specularity
    double pre_eta_n;
    //! (1-rs)
    double pre_eta_t;

    int center_i;
    int center_j;
    int center_k;
    int itr_harf_x;
    int itr_harf_y;
    int itr_harf_z;
    int itr_max_x;
    int itr_max_y;
    int itr_max_z;

    C test;
    C test2;
    C test3;
    Params() {
        // test.set(1, 2, 3);
        // test2.set(4, 5, 6);
        // test.print();
        // test2.print();
        // test += test2;
        // test.print();
        // test3 = test * 3;
        // test3.print();
        // test3 = test3 / 3;
        // test3.print();
        // test3 = test + test2;
        // test3.print();

        std::cout << "\033[31m";
        if (SimpleTensile) {
            read_filename = "./data/input_file/SimpleTensile.cfg";
            param         = new param::parameter(read_filename);
            // if (param->get<bool>("release")) {
            if (NaturalFrequency) {
                read_filename = "./data/input_file/NaturalFrequency.cfg";
                std::cout << "Input NaturalFrequency.cfg" << endl;
            } else if (Oblique) {
                read_filename = "./data/input_file/SimpleTensileOblique.cfg";
                std::cout << "Input SimpleTensileOblique.cfg" << endl;
            } else {
                std::cout << "Input Tensile" << endl;
            }
        } else if (SimpleShare) {
            read_filename = "./data/input_file/SimpleShare.cfg";
            if (SupportShare) {
                read_filename = "./data/input_file/SupportShare.cfg";
                std::cout << "Input SupportShare.cfg" << endl;
            } else {
                std::cout << "Input Share" << endl;
            }
        } else if (SimpleBend) {
            read_filename = "./data/input_file/SimpleBend.cfg";
            std::cout << "Input Bend" << endl;
        } else if (SimplePressure) {
            read_filename = "./data/input_file/SimplePressure.cfg";
            std::cout << "Input Pressure" << endl;
        } else if (SimpleCompression) {
            read_filename = "./data/input_file/SimpleCompression.cfg";
            std::cout << "Input Compression" << endl;
        } else if (CylinderPressure) {
            read_filename = "./data/input_file/CylinderPressure.cfg";
            std::cout << "Input Cylinder" << endl;
        } else if (DiagonalTensile) {
            read_filename = "./data/input_file/DiagonalTensile.cfg";
            std::cout << "Input Diagonal" << endl;
        } else if (PlateRevolution) {
            read_filename = "./data/input_file/PlateRevolution.cfg";
            std::cout << "Input Revolution" << endl;
        } else if (CubePressure) {
            read_filename = "./data/input_file/CubePressure.cfg";
            std::cout << "Input Cube" << endl;
        } else if (SolarSail) {
            read_filename = "./data/input_file/SolarSail.cfg";
            read_PositionFile = "./data/position/InitialPosition.csv";
            std::cout << "Input SolarSail" << endl;
        } else {
            read_filename = "./data/input_file/default.cfg";
            std::cout << "Not define force situation." << std::endl;
        }
        std::cout << "\033[m" << std::flush;

        param = new param::parameter(read_filename);
        // この構文が利用可能かわからない。 newが失敗とき!paramになるのか？
        // (!*param)に書き換えるべきかも
        if (!param) {
            std::cerr << "Could not find file " << read_filename << std::endl;
            std::cout << "on Params.hpp" << endl;
            std::abort();
        }
        // 粒子数
        m_iNum = param->get<int>("m_iNum");
        m_jNum = param->get<int>("m_jNum");
        m_kNum = param->get<int>("m_kNum");
        // 出力など
        m_sheet_skip = param->get<double>("m_sheet_skip");
        div_file     = param->get<double>("div_file");
        m_tmax       = param->get<double>("m_tmax");
        m_dt         = param->get<double>("m_dt");
        // 物性値
        Lref = param->get<double>("Lref");
        Vref = param->get<double>("Vref");
        Pref = param->get<double>("Pref");
        Psun = param->get<double>("Psun", 0);
        Pc   = Pref;
        if (SolarSail) {
            Pc = Psun;
        }
        Psun_angle_axis = param->get<string>("Psun_angle_axis", "zyz");
        Psun_angle_phi  = param->get<double>("Psun_angle_phi", 0);
        Psun_angle_phi *= math::pi() / 180;
        Psun_angle_theta = param->get<double>("Psun_angle_theta", 0);
        Psun_angle_theta *= math::pi() / 180;
        Psun_angle_psi = param->get<double>("Psun_angle_psi", 0);
        Psun_angle_psi *= math::pi() / 180;
        Psun_angle_s_theta = param->get<double>("Psun_angle_s_theta", 0);
        Psun_angle_s_theta *= math::pi() / 180;
        Psun_angle_s_phi = param->get<double>("Psun_angle_s_phi", 0);
        Psun_angle_s_phi *= math::pi() / 180;
        reflectance = param->get<double>("Reflectance", 0);
        specularity = param->get<double>("Specularity", 0);
        h0          = param->get<double>("h0");
        Length_x    = param->get<double>("Length_x");
        Length_y    = param->get<double>("Length_y");
        m_E         = param->get<double>("m_E");
        Cv          = param->get<double>("Cv");
        m_nu        = param->get<double>("m_nu");
        m_rho       = param->get<double>("m_rho");
        // 外力
        m_kx              = param->get<double>("m_kx");
        m_ky              = param->get<double>("m_ky");
        m_kz              = param->get<double>("m_kz");
        analysis_shape    = param->get<std::string>("analysis_shape");
        grid_pattern      = param->get<std::string>("grid_pattern");
        add_disturbance   = param->get<bool>("add_disturbance");
        disturbance_range = param->get<double>("disturbance_range");
        boundary.set_param(read_filename);
        boundary.cylinder_boundary =
            param->get<bool>("cylinder_boundary", false);
        boundary.boundary_more_detail =
            param->get<bool>("boundary_more_detail", false);

        boundary.right_share_fix  = param->get<bool>("RightShare");
        boundary.left_share_fix   = param->get<bool>("LeftShare");
        boundary.bottom_share_fix = param->get<bool>("BottomShare");
        boundary.top_share_fix    = param->get<bool>("TopShare");

        boundary.right_bend_fix  = param->get<bool>("RightBend");
        boundary.left_bend_fix   = param->get<bool>("LeftBend");
        boundary.bottom_bend_fix = param->get<bool>("BottomBend");
        boundary.top_bend_fix    = param->get<bool>("TopBend");

        boundary.right_free  = param->get<bool>("RightFree");
        boundary.left_free   = param->get<bool>("LeftFree");
        boundary.bottom_free = param->get<bool>("BottomFree");
        boundary.top_free    = param->get<bool>("TopFree");

        boundary.judge_xyz_fix(boundary.right_move,
                               (param->get<string>("RightMove")));
        boundary.judge_xyz_fix(boundary.left_move,
                               (param->get<string>("LeftMove")));
        boundary.judge_xyz_fix(boundary.top_move,
                               (param->get<string>("TopMove")));
        boundary.judge_xyz_fix(boundary.bottom_move,
                               (param->get<string>("BottomMove")));
        force_release       = param->get<bool>("release");
        roll_inertia_system = param->get<bool>("RollInertiaSystem", false);
        phi                 = param->get<double>("initial_phi", 0);
        theta               = param->get<double>("initial_theta", 0);
        psi                 = param->get<double>("initial_psi", 0);
        initial_phi_d       = param->get<double>("omega_phi", 0);
        initial_theta_d     = param->get<double>("omega_theta", 0);
        initial_psi_d       = param->get<double>("omega_psi", 0);
        initial_phi_dd      = param->get<double>("angular_acceleration_phi", 0);
        initial_theta_dd    = param->get<double>("angular_acceleration_theta", 0);
        initial_psi_dd      = param->get<double>("angular_acceleration_psi", 0);
        phi_d               = initial_phi_d;
        theta_d             = initial_theta_d;
        psi_d               = initial_psi_d;
        phi_dd              = initial_phi_dd;
        theta_dd            = initial_theta_dd;
        psi_dd              = initial_psi_dd;

        pressure_for_all.set(0, 0, -1);

        oblique_rigid = param->get<bool>("ObliqueRigid", false);
        if (oblique_rigid) {
            oblique_move = param->get<string>("ObliqueMove");
        }
        if (!add_disturbance) {
            disturbance_range = 0;
        }

        // 条件毎
        if (DiagonalTensile) {
            m_fe = param->get<double>("m_fe");
            m_kx = sqrt(m_fe);
            m_ky = sqrt(m_fe);
        }
        if (PlateRevolution) {
            m_fe = param->get<double>("m_fe");
            m_kx = 0;
            m_ky = 0;
        }
        if (Lref != Length_x) {
            std::cout << "\033[31m";
            cout << "Attension!! Difference Lref and Length_x " << endl;
            std::cout << "\033[m" << std::flush;
        }

        delete param;
        disturbance_mode = "direct";

        m_paramsFile    = "./data/Params.csv";
        m_fileExistFlag = false;
    }

    ~Params() {}
    void set_pressure_initial(void);

    void preCalc() {
        m_Lref_x = Length_x / Lref;
        m_Lref_y = Length_y / Lref;
        m_h0     = h0 / Lref;
        m_hc0    = m_h0 * 2;
        m_Pc     = Pc / Pref;
        m_fx     = m_kx * m_Lref_x;
        m_fy     = m_ky * m_Lref_x;
        m_fz     = m_kz * m_Lref_x;
        // XXX: Why add Pref?
        // m_k = sqrt(m_kx * m_kx + m_ky * m_ky + m_kz * m_kz) + Pref;
        m_k = sqrt(m_kx * m_kx + m_ky * m_ky + m_kz * m_kz);

        // C_EI = m_E / (m_rho * Vref * Vref * m_k);
        C_EI = m_E / (m_rho * Vref * Vref);
        if (SimplePressure) {
            C_AE = (Pc * Lref) / (m_E * h0);
        } else {
            C_AE = (Pref * Lref) / (m_E * h0);
        }
        if (SimpleTensile) {
            m_Cv = Cv;
            // m_Cv = Cv * m_k;
        } else {
            m_Cv = Cv;
        }

        m_preCalc1 = 1 / (1 - (m_nu * m_nu));
        m_preCalc2 = 1 / (4 * (1 + m_nu));
        m_preCalc3 = m_nu / (1 - m_nu);

        // m_preCalc4		= h0 * h0 * m_preCalc1 / ( 12 * Lref * Lref );
        m_preCalc4 = m_preCalc1 / 12;
        pre_eta_n  = (1 + reflectance * specularity);
        pre_eta_t  = (1 - reflectance * specularity);

        // Psun
        set_pressure_initial();
        pressure_initial.print();

        // rotation ineria system
        m_phi_d    = phi_d * m_dt;
        m_theta_d  = theta_d * m_dt;
        m_psi_d    = psi_d * m_dt;
        m_phi_dd   = phi_dd * m_dt;
        m_theta_dd = theta_dd * m_dt;
        m_psi_dd   = psi_dd * m_dt;
    }
};

void Params::set_pressure_initial(void) {
    // spherical_coordinate.set(-1.0, Psun_angle_s_theta, Psun_angle_s_phi);
    spherical_coordinate.set(-m_Pc, Psun_angle_s_theta, Psun_angle_s_phi);
    // spherical_coordinate.set(-m_Pc, Psun_angle_s_theta, Psun_angle_s_phi + psi);

    vector<double> spherical_xyz = spherical_coordinate.transform();
    pressure_initial.set(spherical_xyz);
    // pressure_initial.print();
    // pressure_initial *= m_Pc;

    // if (roll_inertia_system) {
    //     rotation_matrix.set(Psun_angle_axis, Psun_angle_phi, Psun_angle_theta,
    //                         Psun_angle_psi);
    // } else {
    //     rotation_matrix.set(Psun_angle_axis, Psun_angle_phi, Psun_angle_theta,
    //                         Psun_angle_psi);
    // }

    // pressure_matrix_unit           = pressure_for_all.out_array();
    // vector<double> pressure_matrix =
    // rotation_matrix.vec_rotate(pressure_matrix_unit);
    // pressure_initial.set(pressure_matrix);
    // pressure_initial *= m_Pc;
}

#endif
