/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file	CalcDataAllocation.cpp
 * @brief	初期値が決まっていないパラメーターの宣言を行うファイル
 * @details 配列の動的確保のためにresizeで変数の初期化を行う
 * @note　　メンバ変数はp->...とあらわしてる
 * ///////////////////////////////////////////////////////////////////////////////
 */

// header
//---------------------------------------
#include "./DataSet.hpp"
//---------------------------------------

/**
 * @date
 * @brief	粒子の持つ力や距離などのパラメ―タ
 * @details
 */
class Particles {
   public:
    //! Particle's Flag
    vector<vector<vector<int>>> flag;
    //! particle's special flag
    vector<vector<vector<int>>> i_specialflag;
    vector<vector<vector<int>>> surround_particle_exsit;
    vector<vector<vector<Communication>>> commflag;
    //! Particle Coordinates (x,y,z) 粒子の座標を格納する (Particle Coordinates)
    vector<vector<vector<C>>> c;
    //! New Particle Coordinates (出力するための粒子の座標を格納する)
    vector<vector<vector<C>>> new_c;
    //! Coordinate of Virtuale particle at the bottom
    vector<vector<vector<C>>> vc_Bottom;
    //! Coordinate of Virtuale particle at the top
    vector<vector<vector<C>>> vc_Top;
    //! Coordinate of Virtuale particle at the right
    vector<vector<vector<C>>> vc_Right;
    //! Coordinate of Virtuale particle at the left
    vector<vector<vector<C>>> vc_Left;

    //! Coordinate of Virtuale particle at tmp
    vector<vector<vector<C>>> vc_tmp;
    //! Virtual Particle Parameters (仮想粒子関係の値を格納する関数)
    vector<vector<vector<VirtualParticle>>> vp;

    //!	Midpoint particle(i,j) and (i+1,j).
    //!粒子(i,j)と粒子(i+1,j)sの中間点。Ij(i,j)とljgを求めるのに使用する。mi[i][j]とmi[i-1][j]の和で粒子(i,j)の前後の長さli(i,j)を求めれる。
    vector<vector<vector<C>>> mi;
    //!	Midpoint particle(i,j) and (i,j+1).
    //!粒子(i,j)と粒子(i,j+1)の中間点。Ii(i,j)とligを求めるのに使用する。これで、粒子(i,j)の前後の長さを求めれる。
    vector<vector<vector<C>>> mj;
    vector<vector<vector<C>>> mi0;
    vector<vector<vector<C>>> mj0;
    //! Vector per particle. 速度を格納する
    vector<vector<vector<C>>> v;
    //! New Vector per particle. 速度を格納する
    vector<vector<vector<C>>> new_v;
    //! Gravity point between 4 particle. 重心を格納する。計算方法はi+
    //! j+方向の4粒子のxyz座標の平均
    vector<vector<vector<C>>> g;
    //! Initial Gravity point. 初期重心を格納する
    vector<vector<vector<C>>> g0;
    //! Lnegth in i-direction. i方向の長さ
    vector<vector<vector<Vector>>> li;
    //! Length in j-direction/ j方向の長さ
    vector<vector<vector<Vector>>> lj;
    //! Initial Length in i-direction. 無負荷時のi方向の長さ
    vector<vector<vector<double>>> li0;
    //! Initial Length in j-direction. 無負荷時のj方向の長さ
    vector<vector<vector<double>>> lj0;
    //! Thickness in i-direction. i方向の膜厚
    vector<vector<vector<double>>> hi;
    //! Thickness in j-direction. j方向の膜厚
    vector<vector<vector<double>>> hj;
    //! Average thickness.
    vector<vector<vector<double>>> h_ave;
    //! Average thickness.
    vector<vector<vector<double>>> h_ave3;

    //! Influence area. 影響面積 S(i,j)
    vector<vector<vector<Area>>> S;
    //! 影響面積 S(i+1/2,j)
    vector<vector<vector<Area>>> Si;
    //! 影響面積 S(i,j+1/2)
    vector<vector<vector<Area>>> Sj;
    //! 無負荷時の影響面積
    vector<vector<vector<double>>> S0;
    vector<vector<vector<double>>> Si0;
    vector<vector<vector<double>>> Sj0;

    vector<vector<vector<double>>> Fti;
    vector<vector<vector<double>>> Ftj;

    //! 構造体C、x,y,z方向の力を格納する
    vector<vector<vector<C>>> f;

    //! せん断角度
    vector<vector<vector<Quarter>>> beta;
    //! 無負荷時のせん断角度
    vector<vector<vector<Quarter>>> beta0;
    //! せん断ひずみ
    vector<vector<vector<Quarter>>> gamma;
    //! i方向のせん断力
    vector<vector<vector<Quarter>>> Fsi;
    //! j方向のせん断力
    vector<vector<vector<Quarter>>> Fsj;

    //! 垂直ひずみ
    vector<vector<vector<double>>> epsilonli;
    //! 垂直ひずみ
    vector<vector<vector<double>>> epsilonlj;

    vector<vector<vector<double>>> epsilongi;
    vector<vector<vector<double>>> epsilongj;

    //! 断面2次モーメント
    vector<vector<vector<double>>> Ii;
    //! 断面2次モーメント
    vector<vector<vector<double>>> Ij;
    //! 曲げ角度
    vector<vector<vector<double>>> alphai;
    //! 曲げ角度
    vector<vector<vector<double>>> alphaj;
    //! 曲げ角度判定用変数
    vector<vector<vector<bool>>> alphai_identification;
    //! 曲げ角度判定用変数
    vector<vector<vector<bool>>> alphaj_identification;

    //! 曲率
    vector<vector<vector<double>>> etai;
    //! 曲率
    vector<vector<vector<double>>> etaj;
    //! 無負荷時の曲率
    vector<vector<vector<double>>> etai0;
    //! 無負荷時の曲率
    vector<vector<vector<double>>> etaj0;
    //! 曲率の変位
    vector<vector<vector<double>>> diff_etai;
    //! 曲率の変位
    vector<vector<vector<double>>> diff_etaj;

    //! Bending moment in i-direction (i方向の曲げモーメント)
    vector<vector<vector<double>>> Mi;
    //! Bending moment in j-direction j方向の曲げモーメント
    vector<vector<vector<double>>> Mj;

    //! Force by bending
    vector<vector<vector<PreDirection>>> Fb;
    //! Pressure
    vector<vector<vector<C>>> pressure;
    //! Force by air (Pressure)
    vector<vector<vector<double>>> Fa;
    //! Force by sun Normal
    vector<vector<vector<C>>> Fnormal;
    //! Force by sun transverse
    vector<vector<vector<C>>> Ftrans;
    //! Force by sun transverse in i
    vector<vector<vector<C>>> Ftrans_i;
    //! Force by sun transverse in j
    vector<vector<vector<C>>> Ftrans_j;
    //! Angle between the normal vector of surface ant the sun light in frame sunlight and transverse
    vector<vector<vector<double>>> angle_surface_sun;
    //! Angle between the normal vector of surface ant the sun light in i
    vector<vector<vector<double>>> angle_surface_sun_i;
    //! Angle between the normal vector of surface ant the sun light in j
    vector<vector<vector<double>>> angle_surface_sun_j;
    //! Disturbance 擾乱
    vector<vector<vector<C>>> disturbance;
    //! Force by dostirbance (Pressure)
    vector<vector<vector<double>>> Fd;
    //! GetNewCoordinate.hppで計算する値を入力する。Ft, Fs, Fbの合力
    vector<vector<vector<Direction>>> F;
    //! radius
    vector<vector<vector<Vector>>> r;
    //! pre radius
    vector<vector<vector<Vector>>> pre_r;
    //! radius oon rotation system
    vector<vector<vector<C>>> r_rot;
    //! vector on rotation system
    vector<vector<vector<C>>> v_rot;
    //! 角度 [rad] (spherical coordinate system)
    vector<vector<vector<double>>> phi;
    //! 角度 [rad] (spherical coordinate system)
    vector<vector<vector<double>>> theta;
    //! 角度 [rad] (spherical coordinate system)(i=max,j=harf phi=0. i=harf,j=max phi=90 deg.)
    vector<vector<vector<double>>> psi;
    //! 回転角速度 [rad/s] omega
    vector<vector<vector<C>>> omega;
    //! 回転角加速度 [rad/s^2] angular acceleration
    vector<vector<vector<C>>> a_euler;
    //! 回転角速度 [rad/s] omega_phi
    vector<vector<vector<double>>> omega_phi;
    //! 回転角速度 [rad/s] omega_phi
    vector<vector<vector<C>>> omega_phi_vec;
    //! 回転角速度 [rad/s] omega_theta
    vector<vector<vector<double>>> omega_theta;
    //! 回転角速度 [rad/s] omega_psi Z-axix angle
    vector<vector<vector<double>>> omega_psi;
    //! 回転方向の慣性力 (Euler Force)
    vector<vector<vector<C>>> F_Euler;
    //! 遠心力 (Centrifugal Force)
    vector<vector<vector<C>>> F_Cen;
    //! コリオリ力 (Coriolis Force)
    vector<vector<vector<C>>> F_Cor;
    //! 系の回転による力
    vector<vector<vector<C>>> F_roll;
    //! GetNewCoordinate.hppで計算する値を入力する。ExternalForce
    vector<vector<vector<C>>> external_force;
    //! GetNewCoordinate.hppで計算する値を入力する。ExternalForce by Pressure
    vector<vector<vector<C>>> external_force_by_pressure;

    //! Outer most parameters (最外殻粒子のパラメーター)
    vector<vector<vector<OuterMostParameter>>> omp;

    Tmp tmp;

    // void initialize_member(int iNum, int jum, int Knum);
    Particles(int iNum, int jNum, int kNum) {
        flag.resize(iNum);
        i_specialflag.resize(iNum);
        surround_particle_exsit.resize(iNum);
        commflag.resize(iNum);
        // C型のkNum個の配列のポインタを格納
        c.resize(iNum);
        r.resize(iNum);
        pre_r.resize(iNum);
        new_c.resize(iNum);
        vc_Left.resize(iNum);
        vc_Right.resize(iNum);
        vc_Top.resize(iNum);
        vc_Bottom.resize(iNum);
        vc_tmp.resize(iNum);
        vp.resize(iNum);
        mi.resize(iNum);
        mj.resize(iNum);
        mi0.resize(iNum);
        mj0.resize(iNum);
        v.resize(iNum);
        new_v.resize(iNum);
        g.resize(iNum);
        g0.resize(iNum);
        li.resize(iNum);
        lj.resize(iNum);
        li0.resize(iNum);
        lj0.resize(iNum);
        hi.resize(iNum);
        hj.resize(iNum);
        h_ave.resize(iNum);
        h_ave3.resize(iNum);

        S.resize(iNum);
        Si.resize(iNum);
        Sj.resize(iNum);
        S0.resize(iNum);
        Si0.resize(iNum);
        Sj0.resize(iNum);

        Fti.resize(iNum);
        Ftj.resize(iNum);

        f.resize(iNum);

        beta.resize(iNum);
        beta0.resize(iNum);
        gamma.resize(iNum);
        Fsi.resize(iNum);
        Fsj.resize(iNum);
        epsilonli.resize(iNum);
        epsilonlj.resize(iNum);
        epsilongi.resize(iNum);
        epsilongj.resize(iNum);
        Ii.resize(iNum);
        Ij.resize(iNum);
        alphai.resize(iNum);
        alphaj.resize(iNum);
        alphai_identification.resize(iNum);
        alphaj_identification.resize(iNum);

        etai.resize(iNum);
        etaj.resize(iNum);
        etai0.resize(iNum);
        etaj0.resize(iNum);
        diff_etai.resize(iNum);
        diff_etaj.resize(iNum);

        Mi.resize(iNum);
        Mj.resize(iNum);

        Fb.resize(iNum);
        pressure.resize(iNum);
        Fa.resize(iNum);
        Fnormal.resize(iNum);
        Ftrans.resize(iNum);
        Ftrans_i.resize(iNum);
        Ftrans_j.resize(iNum);
        disturbance.resize(iNum);
        Fd.resize(iNum);
        r_rot.resize(iNum);
        v_rot.resize(iNum);
        phi.resize(iNum);
        psi.resize(iNum);
        theta.resize(iNum);
        omega.resize(iNum);
        a_euler.resize(iNum);
        omega_phi.resize(iNum);
        omega_psi.resize(iNum);
        omega_phi_vec.resize(iNum);
        omega_theta.resize(iNum);
        F.resize(iNum);
        F_Euler.resize(iNum);
        F_Cen.resize(iNum);
        F_Cor.resize(iNum);
        F_roll.resize(iNum);
        angle_surface_sun.resize(iNum);
        angle_surface_sun_i.resize(iNum);
        angle_surface_sun_j.resize(iNum);
        external_force.resize(iNum);
        external_force_by_pressure.resize(iNum);
        omp.resize(iNum);

        for (int i = 0; i < iNum; i++) {
            flag[i].resize(jNum);
            i_specialflag[i].resize(jNum);
            surround_particle_exsit[i].resize(jNum);
            commflag[i].resize(jNum);
            // C型のkNum個の配列のポインタを格納
            c[i].resize(jNum);
            r[i].resize(jNum);
            pre_r[i].resize(jNum);
            new_c[i].resize(jNum);
            vc_Left[i].resize(jNum);
            vc_Right[i].resize(jNum);
            vc_Top[i].resize(jNum);
            vc_Bottom[i].resize(jNum);
            vc_tmp[i].resize(jNum);
            vp[i].resize(jNum);
            mi[i].resize(jNum);
            mj[i].resize(jNum);
            mi0[i].resize(jNum);
            mj0[i].resize(jNum);
            v[i].resize(jNum);
            new_v[i].resize(jNum);
            g[i].resize(jNum);
            g0[i].resize(jNum);
            li[i].resize(jNum);
            lj[i].resize(jNum);
            li0[i].resize(jNum);
            lj0[i].resize(jNum);
            hi[i].resize(jNum);
            hj[i].resize(jNum);
            h_ave[i].resize(jNum);
            h_ave3[i].resize(jNum);

            S[i].resize(jNum);
            Si[i].resize(jNum);
            Sj[i].resize(jNum);
            S0[i].resize(jNum);
            Si0[i].resize(jNum);
            Sj0[i].resize(jNum);

            Fti[i].resize(jNum);
            Ftj[i].resize(jNum);

            f[i].resize(jNum);

            beta[i].resize(jNum);
            beta0[i].resize(jNum);
            gamma[i].resize(jNum);
            Fsi[i].resize(jNum);
            Fsj[i].resize(jNum);
            epsilonli[i].resize(jNum);
            epsilonlj[i].resize(jNum);
            epsilongi[i].resize(jNum);
            epsilongj[i].resize(jNum);
            Ii[i].resize(jNum);
            Ij[i].resize(jNum);
            alphai[i].resize(jNum);
            alphaj[i].resize(jNum);
            alphai_identification[i].resize(jNum);
            alphaj_identification[i].resize(jNum);

            etai[i].resize(jNum);
            etaj[i].resize(jNum);
            etai0[i].resize(jNum);
            etaj0[i].resize(jNum);
            diff_etai[i].resize(jNum);
            diff_etaj[i].resize(jNum);

            Mi[i].resize(jNum);
            Mj[i].resize(jNum);

            Fb[i].resize(jNum);
            pressure[i].resize(jNum);
            Fa[i].resize(jNum);
            Fnormal[i].resize(jNum);
            Ftrans[i].resize(jNum);
            Ftrans_i[i].resize(jNum);
            Ftrans_j[i].resize(jNum);
            disturbance[i].resize(jNum);
            Fd[i].resize(jNum);
            r_rot[i].resize(jNum);
            v_rot[i].resize(jNum);
            phi[i].resize(jNum);
            psi[i].resize(jNum);
            theta[i].resize(jNum);
            omega[i].resize(jNum);
            a_euler[i].resize(jNum);
            omega_phi[i].resize(jNum);
            omega_psi[i].resize(jNum);
            omega_phi_vec[i].resize(jNum);
            omega_theta[i].resize(jNum);
            F[i].resize(jNum);
            F_Euler[i].resize(jNum);
            F_Cen[i].resize(jNum);
            F_Cor[i].resize(jNum);
            F_roll[i].resize(jNum);
            angle_surface_sun[i].resize(jNum);
            angle_surface_sun_i[i].resize(jNum);
            angle_surface_sun_j[i].resize(jNum);
            external_force[i].resize(jNum);
            external_force_by_pressure[i].resize(jNum);
            omp[i].resize(jNum);

            for (int j = 0; j < jNum; j++) {
                flag[i][j].resize(kNum);
                i_specialflag[i][j].resize(kNum);
                surround_particle_exsit[i][j].resize(kNum);
                commflag[i][j].resize(kNum);
                // C型のkNum個の配列のポインタを格納
                c[i][j].resize(kNum);
                r[i][j].resize(kNum);
                pre_r[i][j].resize(kNum);
                new_c[i][j].resize(kNum);
                vc_Left[i][j].resize(kNum);
                vc_Right[i][j].resize(kNum);
                vc_Top[i][j].resize(kNum);
                vc_Bottom[i][j].resize(kNum);
                vc_tmp[i][j].resize(kNum);
                vp[i][j].resize(kNum);
                mi[i][j].resize(kNum);
                mj[i][j].resize(kNum);
                mi0[i][j].resize(kNum);
                mj0[i][j].resize(kNum);
                v[i][j].resize(kNum);
                new_v[i][j].resize(kNum);
                g[i][j].resize(kNum);
                g0[i][j].resize(kNum);
                li[i][j].resize(kNum);
                lj[i][j].resize(kNum);
                li0[i][j].resize(kNum);
                lj0[i][j].resize(kNum);
                hi[i][j].resize(kNum);
                hj[i][j].resize(kNum);
                h_ave[i][j].resize(kNum);
                h_ave3[i][j].resize(kNum);

                S[i][j].resize(kNum);
                Si[i][j].resize(kNum);
                Sj[i][j].resize(kNum);
                S0[i][j].resize(kNum);
                Si0[i][j].resize(kNum);
                Sj0[i][j].resize(kNum);

                Fti[i][j].resize(kNum);
                Ftj[i][j].resize(kNum);

                f[i][j].resize(kNum);

                beta[i][j].resize(kNum);
                beta0[i][j].resize(kNum);
                gamma[i][j].resize(kNum);
                Fsi[i][j].resize(kNum);
                Fsj[i][j].resize(kNum);
                epsilonli[i][j].resize(kNum);
                epsilonlj[i][j].resize(kNum);
                epsilongi[i][j].resize(kNum);
                epsilongj[i][j].resize(kNum);
                Ii[i][j].resize(kNum);
                Ij[i][j].resize(kNum);
                alphai[i][j].resize(kNum);
                alphaj[i][j].resize(kNum);
                alphai_identification[i][j].resize(kNum);
                alphaj_identification[i][j].resize(kNum);

                etai[i][j].resize(kNum);
                etaj[i][j].resize(kNum);
                etai0[i][j].resize(kNum);
                etaj0[i][j].resize(kNum);
                diff_etai[i][j].resize(kNum);
                diff_etaj[i][j].resize(kNum);

                Mi[i][j].resize(kNum);
                Mj[i][j].resize(kNum);

                Fb[i][j].resize(kNum);
                pressure[i][j].resize(kNum);
                Fa[i][j].resize(kNum);
                Fnormal[i][j].resize(kNum);
                Ftrans[i][j].resize(kNum);
                Ftrans_i[i][j].resize(kNum);
                Ftrans_j[i][j].resize(kNum);
                disturbance[i][j].resize(kNum);
                Fd[i][j].resize(kNum);
                r_rot[i][j].resize(kNum);
                v_rot[i][j].resize(kNum);
                phi[i][j].resize(kNum);
                psi[i][j].resize(kNum);
                theta[i][j].resize(kNum);
                omega[i][j].resize(kNum);
                a_euler[i][j].resize(kNum);
                omega_phi[i][j].resize(kNum);
                omega_psi[i][j].resize(kNum);
                omega_phi_vec[i][j].resize(kNum);
                omega_theta[i][j].resize(kNum);
                F[i][j].resize(kNum);
                F_Euler[i][j].resize(kNum);
                F_Cen[i][j].resize(kNum);
                F_Cor[i][j].resize(kNum);
                F_roll[i][j].resize(kNum);
                angle_surface_sun[i][j].resize(kNum);
                angle_surface_sun_i[i][j].resize(kNum);
                angle_surface_sun_j[i][j].resize(kNum);
                external_force[i][j].resize(kNum);
                external_force_by_pressure[i][j].resize(kNum);
                omp[i][j].resize(kNum);
            }
        }
    }

    ~Particles() {}
};
