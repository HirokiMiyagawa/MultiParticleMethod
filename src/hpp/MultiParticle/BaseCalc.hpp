/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file	BaseCalc.hpp
 * @brief	様々な基本的な計算を行う。
 * @details
 * @par
 * ///////////////////////////////////////////////////////////////////////////////
 */

#include <cmath>
#include <string>

/**
 * @brief		粒子間距離 lを求める
 * @param[out] Vector myl
 * @param[in] C myc
 * @param[in] C large
 */
void MultiParticle::lCalc(Vector& myl, C const& myc, C const& large) {
    myl.vector.x = large.x - myc.x;
    myl.vector.y = large.y - myc.y;
    myl.vector.z = large.z - myc.z;
    myl.norm     = normCalc(myl.vector);
}

/**
 * @brief		垂直ひずみ εを求める
 * @param[in]	今の長さ
 * @param[in]	初期長さ
 * @return		double 垂直ひずみ
 */
double MultiParticle::epsilonlCulc(double const& myl,
                                   double const& initialvalue) {
    return ((myl - initialvalue) / initialvalue);
}

/**
 * @brief		粒子間の中心点を求める
 * @note
 * miやmjを求めるのにほぼ同じ計算を使うのは無駄だと感じたため
 */
void MultiParticle::mCalc(C& myc, C const& A, C const& B) {
    myc.x = ((A.x + B.x) / 2);
    myc.y = ((A.x + B.y) / 2);
    myc.z = ((A.x + B.z) / 2);
}

/**
 * @brief		粒子間の重心を求める
 * @note		2点間の重心 gを求めることに使用する
 */
void MultiParticle::gCalc(C& myc, C const& A, C const& B) {
    myc.x = ((A.x + B.x) / 2);
    myc.y = ((A.x + B.y) / 2);
    myc.z = ((A.x + B.z) / 2);
}

/**
 * @brief		粒子間の重心を求める
 * @note		4点間の重心 gを求めることに使用する
 */
void MultiParticle::gCalc(C& myc, C const& Acoordinates, C const& Bcoordinates,
                          C const& Ccoordinates, C const& Dcoordinates) {
    myc.x =
        ((Acoordinates.x + Bcoordinates.x + Ccoordinates.x + Dcoordinates.x) /
         4);
    myc.y =
        ((Acoordinates.x + Bcoordinates.y + Ccoordinates.y + Dcoordinates.y) /
         4);
    myc.z =
        ((Acoordinates.x + Bcoordinates.z + Ccoordinates.z + Dcoordinates.z) /
         4);
}

/**
 * @brief		せん断角度 βを求める
 * @return angle between the point AcB.
 * @note		ifの条件はacos()の引数になるのか
 * acos()の引数が-1<= 引数 <= 1かどうか
 * 常に180度以下が返り値になる想定
 */
double MultiParticle::angleCalc(C const& myc, C const& A, C const& B) {
    C Adif;
    C Bdif;

    // Adif.x = A.x - myc.x;
    // Adif.y = A.y - myc.y;
    // Adif.z = A.z - myc.z;
    Adif = A - myc;

    // Bdif.x = B.x - myc.x;
    // Bdif.y = B.y - myc.y;
    // Bdif.z = B.z - myc.z;
    Bdif = B - myc;

    return math::sacos(innerProductCalc(Adif, Bdif) /
                       (normCalc(Adif) * normCalc(Bdif)));
}

/**
 * @brief		曲げ角度 αを求める
 * @param[in]	A：次
 * @param[in]	B：前
 * @param[in]	int xy：1のとき、αi、0のときαjを求める
 * @note		ifの条件はacos()の引数になるのか
 * acos()の引数が-1<= 引数 <= 1かどうか
 * xy==0のとき、(0 < Cp.y)が条件で曲げ角度の設定を行う
 * また、xy != 0のとき、(Cp.x < 0)が条件となる
 * 外積のxやyが条件文に記載されている理由は不明
 * Cylinderのときは、180-αが内側の角度となる
 * Aが先
 * xとyが正のとき、
 */
double MultiParticle::angleCalc2(C const& myc, C const& A, C const& B, int xy) {
    C Adif;
    C Bdif;
    C Cp;
    Adif = A - myc;
    Bdif = B - myc;
    crossProductCalc(Cp, Adif, Bdif);
#ifdef __CYLINDER_PRESSURE__

    if (xy == 0) {
        if (0 < Cp.z) {
            return math::sacos(innerProductCalc(Adif, Bdif) /
                               (normCalc(Adif) * normCalc(Bdif)));
        } else {
            return (2 * math::pi()) -
                   (math::sacos(innerProductCalc(Adif, Bdif) /
                                (normCalc(Adif) * normCalc(Bdif))));
        }
    } else {
        if (Cp.x < 0 && 0 < Cp.y) {
            return math::sacos(innerProductCalc(Adif, Bdif) /
                               (normCalc(Adif) * normCalc(Bdif)));
        } else {
            return (2 * math::pi()) -
                   (math::sacos(innerProductCalc(Adif, Bdif) /
                                (normCalc(Adif) * normCalc(Bdif))));
        }
    }
#elif defined __SHAPE_CUBE__
    if (xy == 0) {
        // Ceiling Horizontal
        if (Cp.x < 0) {
            return math::sacos(innerProductCalc(Adif, Bdif) /
                               (normCalc(Adif) * normCalc(Bdif)));
        } else {
            return (2 * math::pi()) -
                   (math::sacos(innerProductCalc(Adif, Bdif) /
                                (normCalc(Adif) * normCalc(Bdif))));
        }
    } else if (xy == 1) {
        // Ceiling Vertical
        if (Cp.y < 0) {
            return math::sacos(innerProductCalc(Adif, Bdif) /
                               (normCalc(Adif) * normCalc(Bdif)));
        } else {
            return (2 * math::pi()) -
                   (math::sacos(innerProductCalc(Adif, Bdif) /
                                (normCalc(Adif) * normCalc(Bdif))));
        }
    } else if (xy == 2) {
        // Back Horizontal
        if (0 < Cp.z) {
            return math::sacos(innerProductCalc(Adif, Bdif) /
                               (normCalc(Adif) * normCalc(Bdif)));
        } else {
            return (2 * math::pi()) -
                   (math::sacos(innerProductCalc(Adif, Bdif) /
                                (normCalc(Adif) * normCalc(Bdif))));
        }
    } else if (xy == 3) {
        // Back Vertical
        if (0 < Cp.x) {
            return math::sacos(innerProductCalc(Adif, Bdif) /
                               (normCalc(Adif) * normCalc(Bdif)));
        } else {
            return (2 * math::pi()) -
                   (math::sacos(innerProductCalc(Adif, Bdif) /
                                (normCalc(Adif) * normCalc(Bdif))));
        }
    } else if (xy == 4) {
        // RightSide Horizontal
        if (0 < Cp.z) {
            return math::sacos(innerProductCalc(Adif, Bdif) /
                               (normCalc(Adif) * normCalc(Bdif)));
        } else {
            return (2 * math::pi()) -
                   (math::sacos(innerProductCalc(Adif, Bdif) /
                                (normCalc(Adif) * normCalc(Bdif))));
        }
    } else if (xy == 5) {
        // RightSide Vertical
        if (Cp.y < 0) {
            return math::sacos(innerProductCalc(Adif, Bdif) /
                               (normCalc(Adif) * normCalc(Bdif)));
        } else {
            return (2 * math::pi()) -
                   (math::sacos(innerProductCalc(Adif, Bdif) /
                                (normCalc(Adif) * normCalc(Bdif))));
        }
    } else {
        return 0;
    }

//////////////////////////////////////////
#else
    if (xy == 0) {
        if (0 < Cp.y) {
            return acos(innerProductCalc(Adif, Bdif) /
                        (normCalc(Adif) * normCalc(Bdif)));
        } else {
            return (2 * math::pi()) - (acos(innerProductCalc(Adif, Bdif) /
                                            (normCalc(Adif) * normCalc(Bdif))));
        }
    } else {
        if (Cp.x < 0) {
            return acos(innerProductCalc(Adif, Bdif) /
                        (normCalc(Adif) * normCalc(Bdif)));
        } else {
            return (2 * math::pi()) - (acos(innerProductCalc(Adif, Bdif) /
                                            (normCalc(Adif) * normCalc(Bdif))));
        }
    }
    // if (xy == 0) {
    //     if (-1 <= (innerProductCalc(Adif, Bdif) /
    //                (normCalc(Adif) * normCalc(Bdif))) &&
    //         1 >= (innerProductCalc(Adif, Bdif) /
    //               (normCalc(Adif) * normCalc(Bdif)))) {
    //         if (0 < Cp.y) {
    //             return acos(innerProductCalc(Adif, Bdif) /
    //                         (normCalc(Adif) * normCalc(Bdif)));
    //         } else {
    //             return (2 * math::pi()) -
    //                    (acos(innerProductCalc(Adif, Bdif) /
    //                          (normCalc(Adif) * normCalc(Bdif))));
    //         }
    //     } else {
    //         return math::pi();
    //     }
    // } else {
    //     if (-1 <= (innerProductCalc(Adif, Bdif) /
    //                (normCalc(Adif) * normCalc(Bdif))) &&
    //         1 >= (innerProductCalc(Adif, Bdif) /
    //               (normCalc(Adif) * normCalc(Bdif)))) {
    //         if (0 > Cp.x) {
    //             return acos(innerProductCalc(Adif, Bdif) /
    //                         (normCalc(Adif) * normCalc(Bdif)));
    //         } else {
    //             return (2 * math
    //                     : pi()) -
    //                    (acos(innerProductCalc(Adif, Bdif) /
    //                          (normCalc(Adif) * normCalc(Bdif))));
    //         }
    //     } else {
    //         return math::pi();
    //     }
    // }
#endif
}

/**
 * @brief		曲げ角度 αを求める
 * @param[in]	A：次
 * @param[in]	B：前
 * @param[in]	int xy：1のとき、αi、0のときαjを求める
 * @note		ifの条件はacos()の引数になるのか
 * acos()の引数が-1<= 引数 <= 1かどうか
 * xy==0のとき、(0 < Cp.y)が条件で曲げ角度の設定を行う
 * また、xy != 0のとき、(Cp.x < 0)が条件となる
 * 外積のxやyが条件文に記載されている理由は不明
 * Cylinderのときは180-αが内側の角度となる
 * Aが先
 * xとyが正のとき、
 */
double MultiParticle::angleCalc2(const C& myc, const C& A, const C& B,
                                 const string& direction) {
    C Adif;
    C Bdif;
    C Cp;
    Adif = A - myc;
    Bdif = B - myc;
    crossProductCalc(Cp, Adif, Bdif);
    double radian =
        innerProductCalc(Adif, Bdif) / (normCalc(Adif) * normCalc(Bdif));
    // if (fabs(radian) > 1.0) {
    //     cout << "radian:" << radian << endl;
    //     cout << myc.x << "," << myc.y << "," << myc.z << "\n" << endl;
    // }
    double Ret = math::sacos(radian);
    if ((normCalc(Adif) * normCalc(Bdif) == 0)) {
        cout << "on angleCalc2. same 3 point coordinate" << endl;
        cout << "myc:" << myc.x << ',' << myc.y << ',' << myc.z << endl;
        cout << "A:" << A.x << ',' << A.y << ',' << A.z << endl;
        cout << "B:" << B.x << ',' << B.y << ',' << B.z << endl;
        cout << direction << endl;
        abort();
        return math::pi();
    } else {
        if ((direction == "i" && 0 < Cp.y) || (direction == "j" && Cp.x < 0)) {
            return Ret;
            // return math::sacos(innerProductCalc(Adif, Bdif) /
            //                    (normCalc(Adif) * normCalc(Bdif)));
        } else {
            return (2 * math::pi()) - Ret;
            // return (2 * math::pi()) -
            //        (math::sacos(innerProductCalc(Adif, Bdif) /
            //                     (normCalc(Adif) * normCalc(Bdif))));
        }
    }
}

/**
 * @brief	せん断ひずみ γ
 */
double MultiParticle::gammaCalc(double const& B, double const& A) {
    return (B - A);
}

/**
 * @brief	膜厚h(i+1/2,j)
 * @note	preCalc3 = ν/(1-ν)
 */
double MultiParticle::hCalc(double const& S, double const& S0) {
    return param->m_h0 * (S0) / (param->m_preCalc3 * ((S) - (S0)) + (S0));
}

/**
 * @brief	垂直ひずみ εj(i+1/2,j)
 */
double MultiParticle::epsilongCalc(double const& A, double const& B) {
    return (A - B) / B;
}

/**
 * @brief	せん断力 Fs
 * @note 	preCalc2 = 1 / 4(1+ν)
 */
double MultiParticle::FsCalc(double const& gamma, double const& l,
                             double const& h) {
    return param->m_preCalc2 * (h) * (l) * (gamma) / param->m_h0;
}

/**
 * @brief	せん断ばねに並列につなぐ減衰項 cs
 */
double MultiParticle::CsCalc(double const& h, double const& Area) {
    return 2 * param->m_Cv * sqrt(param->m_preCalc5 * Area * h / (param->m_h0)) / sqrt(param->C_EI);
    
}

/**
 * @brief	伸縮力 Ft
 */
double MultiParticle::FtCalc(double const& L, double const& h,
                             double const& epsilonl, double const& epsilong) {
    return param->m_preCalc1 * (h)*L * ((epsilonl) + param->m_nu * (epsilong)) /
           param->m_h0;
}

/**
 * @brief	伸縮ばねに並列につなぐ減衰項 ct
 */
double MultiParticle::CtCalc(double const& L, double const& h,
                             double const& Area, double const& L0) {
    return 2 * param->m_Cv * sqrt(L * Area * h / (L0 * param->m_h0)) / sqrt(param->C_EI);
    
}

/**
 * @brief	重力 mg 次続きやる
 */
double MultiParticle::MgCalc(double const& Area) {
    double g = 9806.65;// [mm / s^2]
    g = g * param->Lref * param->Lref / (param->Vref * param->Vref * param->Vref);//　無次元化
    return Area * g / (param->C_EI);
}

/**
 * @brief	曲率 η
 * @note	条件分岐でプラマイの判別
 *
 */
double MultiParticle::etaCalc(double const& alpha, double const& lp,
                              double const& lm) {
    if (sqrt(lp * lp + lm * lm - 2 * lp * lm * cos(alpha)) != 0) {
        if (math::pi() < alpha) {
            return -1 * (2 * sqrt(1 - cos(alpha) * cos(alpha))) /
                   sqrt(lp * lp + lm * lm - 2 * lp * lm * cos(alpha));
        } else {
            return +1 * (2 * sqrt(1 - cos(alpha) * cos(alpha))) /
                   sqrt(lp * lp + lm * lm - 2 * lp * lm * cos(alpha));
        }
    } else {
        return 0;
    }
}

/**
 * @brief	ねじりの際の軸と粒子の交点と粒子の距離（x,y,z座標も込み）を計算する
 * @param[out] intersect
 * @param[out] Hr 粒子をもう片方の粒子を通る軸に垂直の平面におろしたときの交点と軸の距離
 * @param[in] i
 * @param[in] j
 * @param[in] k
 * @param[in] const string& direction ばねがi方向なのかj方向なのか
 * @note	ばねがi方向なのかj方向なのかで分岐
 *         
 *
 */
void MultiParticle::interSectionLengthCalc(Vector& axis, const C& m_small, const C& m_large,
                                        const C& c_small, const C& c_large, Vector& intersect_minus,
                                        Vector& intersect_plus, Vector& Hr) {
    C Unit;
    C Insec;
    C Insec_plus;
    double projec_minus = 0;
    double projec_plus = 0;
    double p = 0;
    
    //Caluculate intersect minus

    lCalc(axis, m_small, m_large); // 軸ベクトルの計算
    Unit.x = axis.vector.x / axis.norm;// 軸の単位ベクトルの計算
    Unit.y = axis.vector.y / axis.norm;
    Unit.z = axis.vector.z / axis.norm;
    projec_minus = 
        ((c_small.x - m_small.x) * Unit.x + (c_small.y - m_small.y) * Unit.y 
        + (c_small.z - m_small.z) * Unit.z);
    Insec.x = m_small.x + projec_minus * Unit.x;
    Insec.y = m_small.y + projec_minus * Unit.y;
    Insec.z = m_small.z + projec_minus * Unit.z;
    lCalc(intersect_minus, Insec, c_small);

    // cout << "inter.x=" << intersect_minus.vector.x
    //         << ", inter.y=" << intersect_minus.vector.y
    //         << ", inter.z=" << intersect_minus.vector.z
    //         << ", Insec.x=" << Insec.x
    //         << ", Insec.y=" << Insec.y
    //         << ", Insec.z=" << Insec.z
    //         << ", c.x=" << c_small.x
    //         << ", c.y=" << c_small.y
    //         << ", c.z=" << c_small.z
    //         << ", projec=" << projec_minus
    //         << endl;
    // Calculate intersect plus
    projec_plus = 
        ((c_large.x - m_large.x) * Unit.x + (c_large.y - m_large.y) * Unit.y 
        + (c_large.z - m_large.z) * Unit.z);
    Insec_plus.x = m_large.x + projec_plus * Unit.x;
    Insec_plus.y = m_large.y + projec_plus * Unit.y;
    Insec_plus.z = m_large.z + projec_plus * Unit.z;
    lCalc(intersect_plus, Insec_plus, c_large);

    // Calculate Hr
    p = (Unit.x * (c_large.x - c_small.x)
        + Unit.y * (c_large.y - c_small.y)
        + Unit.z * (c_large.z - c_small.z))
        / (Unit.x*Unit.x + Unit.y*Unit.y + Unit.z*Unit.z);
    Insec_plus.x = c_large.x + p * Unit.x;
    Insec_plus.y = c_large.y + p * Unit.y;
    Insec_plus.x = c_large.z + p * Unit.z;
    lCalc(Hr, Insec, Insec_plus);
        // lCalc(p->axis_i[i][j][k], p->mj[i][j][k], p->mj[i + 1][j][k]); // 軸ベクトルの計算
        // Unit.x = p->axis_i[i][j][k].vector.x / p->axis_i[i][j][k].norm;// 軸の単位ベクトルの計算
        // Unit.y = p->axis_i[i][j][k].vector.y / p->axis_i[i][j][k].norm;
        // Unit.z = p->axis_i[i][j][k].vector.z / p->axis_i[i][j][k].norm;
        // projec_minus = 
        //     ((p->c[i][j][k].x - p->mj[i][j][k].x) * Unit.x + (p->c[i][j][k].y - p->mj[i][j][k].y) * Unit.y 
        //     + (p->c[i][j][k].z - p->mj[i][j][k].z) * Unit.z);
        // Insec.x = p->mj[i][j][k].x + projec_minus * Unit.x;
        // Insec.y = p->mj[i][j][k].y + projec_minus * Unit.y;
        // Insec.z = p->mj[i][j][k].z + projec_minus * Unit.z;
        // lCalc(intersect_minus, Insec, p->c[i][j][k]);

        // // Calculate intersect plus
        // projec_plus = 
        //     ((p->c[i + 1][j][k].x - p->mj[i + 1][j][k].x) * Unit.x + (p->c[i + 1][j][k].y - p->mj[i + 1][j][k].y) * Unit.y 
        //     + (p->c[i + 1][j][k].z - p->mj[i + 1][j][k].z) * Unit.z);
        // Insec_plus.x = p->mj[i + 1][j][k].x + projec_plus * Unit.x;
        // Insec_plus.y = p->mj[i + 1][j][k].y + projec_plus * Unit.y;
        // Insec_plus.z = p->mj[i + 1][j][k].z + projec_plus * Unit.z;
        // lCalc(intersect_plus, Insec_plus, p->c[i + 1][j][k]);

        // // Calculate Hr
        // p = (Unit.x * (p->c[i + 1][j][k].x - p->c[i][j][k].x)
        //     + Unit.y * (p->c[i + 1][j][k].y - p->c[i][j][k].y)
        //     + Unit.z * (p->c[i + 1][j][k].z - p->c[i][j][k].z))
        //     / (Unit.x*Unit.x + Unit.y*Unit.y + Unit.z*Unit.z);
        // Insec_plus.x = p->c[i + 1][j][k].x + p * Unit.x;
        // Insec_plus.y = p->c[i + 1][j][k].y + p * Unit.y;
        // Insec_plus.x = p->c[i + 1][j][k].z + p * Unit.z;
        // lCalc(Hr, Insec, Insec_plus);
    
    // else if (direction == "j"){
    //     // Calculate intersect minus
    //     lCalc(p->axis_j[i][j][k], p->mi[i][j][k], p->mi[i][j + 1][k]); // 軸ベクトルの計算
    //     Unit.x = p->axis_j[i][j][k].vector.x / p->axis_j[i][j][k].norm;// 軸の単位ベクトル計算
    //     Unit.y = p->axis_j[i][j][k].vector.y / p->axis_j[i][j][k].norm;
    //     Unit.z = p->axis_j[i][j][k].vector.z / p->axis_j[i][j][k].norm;
    //     projec_minus = 
    //         ((p->c[i][j][k].x - p->mi[i][j][k].x) * Unit.x + (p->c[i][j][k].y - p->mi[i][j][k].y) * Unit.y 
    //         + (p->c[i][j][k].z - p->mi[i][j][k].z) * Unit.z);
    //     Insec.x = p->mi[i][j][k].x + projec_minus * Unit.x;
    //     Insec.y = p->mi[i][j][k].y + projec_minus * Unit.y;
    //     Insec.z = p->mi[i][j][k].z + projec_minus * Unit.z;
    //     lCalc(intersect_minus, Insec, p->c[i][j][k]);

    //     // Calculate intersect plus
    //     projec_plus = 
    //         ((p->c[i][j + 1][k].x - p->mi[i][j + 1][k].x) * Unit.x + (p->c[i][j + 1][k].y - p->mi[i][j + 1][k].y) * Unit.y 
    //         + (p->c[i][j + 1][k].z - p->mi[i][j + 1][k].z) * Unit.z);
    //     Insec.x = p->mi[i][j + 1][k].x + projec_plus * Unit.x;
    //     Insec.y = p->mi[i][j + 1][k].y + projec_plus * Unit.y;
    //     Insec.z = p->mi[i][j + 1][k].z + projec_plus * Unit.z;
    //     lCalc(intersect_plus, Insec_plus, p->c[i][j + 1][k]);
        
    //     // Calculate Hr
    //     p = (Unit.x * (p->c[i][j + 1][k].x - p->c[i][j][k].x)
    //         + Unit.y * (p->c[i][j + 1][k].y - p->c[i][j][k].y)
    //         + Unit.z * (p->c[i][j + 1][k].z - p->c[i][j][k].z))
    //         / (Unit.x*Unit.x + Unit.y*Unit.y + Unit.z*Unit.z);
    //     Insec_plus.x = p->c[i][j + 1][k].x + p * Unit.x;
    //     Insec_plus.y = p->c[i][j + 1][k].y + p * Unit.y;
    //     Insec_plus.x = p->c[i][j + 1][k].z + p * Unit.z;
    //     lCalc(Hr, Insec, Insec_plus);
    // }
    // else{
    //     cout << "can't calculate intersection because direction is not valid"
    //          << endl;
    // }
}

/**
 * @brief	ねじりの際の軸と粒子の交点と粒子の距離（x,y,z座標も込み）を計算する
 * @param[out] intersect
 * @param[out] Hr 粒子をもう片方の粒子を通る軸に垂直の平面におろしたときの交点と軸の距離
 * @param[in] i
 * @param[in] j
 * @param[in] k
 * @param[in] const string& direction ばねがi方向なのかj方向なのか
 * @note	ばねがi方向なのかj方向なのかで分岐
 *         
 *
 */
void MultiParticle::FtwVector(const C& c_plus, const C& c_minus, const C& axis,
                                const C& c_ex, Vector& ftw) {
    double s = 0;
    Vector Ftw_vector; // Ftwのベクトルを計算するときに使う、平面に垂直なベクトル。
                       // 単位ベクトルに変換してからFtwの計算に用いる
    Vector normal; // Ftwのベクトルを計算するときに使う、平面に垂直なベクトル。間接的に用いる
    C H; // Ftwのベクトルを計算するときに使う、粒子から垂線を下した交点

    crossProductCalc(normal.vector, c_plus - c_minus, axis);
    normal.norm = normCalc(normal.vector);
    normal.vector.x /= normal.norm;
    normal.vector.y /= normal.norm;
    normal.vector.z /= normal.norm;
    if (normal.norm == 0){
        normal.vector.x = 0;
        normal.vector.y = 0;
        normal.vector.z = 0;
    }
    s = innerProductCalc(normal.vector, c_ex - c_minus);
    H.x = c_ex.x - s * normal.vector.x;
    H.y = c_ex.y - s * normal.vector.y;
    H.z = c_ex.z - s * normal.vector.z;
    Ftw_vector.vector = c_ex - H;
    Ftw_vector.norm = normCalc(Ftw_vector.vector);
    Ftw_vector.vector.x /= Ftw_vector.norm;
    Ftw_vector.vector.y /= Ftw_vector.norm;
    Ftw_vector.vector.z /= Ftw_vector.norm;
    if (Ftw_vector.norm == 0){//std::isnanがきちんと動作してくれなかったため、これで代用
        Ftw_vector.vector.x = 0;
        Ftw_vector.vector.y = 0;
        Ftw_vector.vector.z = 0;
        // cout << "Ftw is nan"
        //      << endl;
    }
    // cout << ", Ftwp.x=" << Ftw_vector.vector.x
    //     << ", Ftwp.y=" << Ftw_vector.vector.y
    //     << ", Ftwp.z=" << Ftw_vector.vector.z
    //     << ", isfinite = " << std::isnan(Ftw_vector.vector.x)
    //     << ", isnan_1 = " << std::isnan(1)
    //     << endl;
    ftw.vector.x = ftw.norm * Ftw_vector.vector.x;
    ftw.vector.y = ftw.norm * Ftw_vector.vector.y;
    ftw.vector.z = ftw.norm * Ftw_vector.vector.z;
   
}

/**
 * @brief		曲げモーメント Mを計算する
 * @param[in] 	double I 断面2次モーメント
 * @param[in] 	double diff_eta モーメント方向の曲率
 * @param[in] 	double diff_etav モーメントと直行する方向の曲率
 * @return		double モーメントの計算結果
 */
double MultiParticle::MCalc(double const& I, double const& diff_eta,
                            double const& diff_etav) {
    return param->m_preCalc4 * I * (diff_eta + param->m_nu * diff_etav) /
           param->m_h0;
}

/**
 * @brief		ねじりモーメント Tを計算する
 * @param[in] 	double Ip 断面2次極モーメント
 * @param[in] 	double diff_theta ねじれ角の差
 * @param[in] 	double lon 軸の長さ
 * @return		double モーメントの計算結果
 */
double MultiParticle::TCalc(double const& Ip, double const& diff_theta,
                            double const& lon, double const& k1) {
    return param->m_preCalc5 * Ip * diff_theta * k1 /
           (lon * param->m_h0);
}

/**
 * @brief
 *
 * @param[in] Fb_v  bend force previous or next
 * @param[in] Scp   influense area cross production
 * @return C Ret   Fb(i+-,j) or Fb(i,j+-)
 */
C MultiParticle::UnitVectorCalc(const double& Fb_n, const Area& Scp) {
    C Ret;
    Ret.x = Fb_n * Scp.cp.vector.x / Scp.cp.norm;
    Ret.y = Fb_n * Scp.cp.vector.y / Scp.cp.norm;
    Ret.z = Fb_n * Scp.cp.vector.z / Scp.cp.norm;
    return Ret;
}

C MultiParticle::UnitVectorCalc(const double& Fb_n, const Vector& V) {
    C Ret;
    Ret.x = Fb_n * V.vector.x / V.norm;
    Ret.y = Fb_n * V.vector.y / V.norm;
    Ret.z = Fb_n * V.vector.z / V.norm;
    return Ret;
}

/**
 * @brief		擾乱生成
 * @param[out] 	out
 * @param[in]	range
 * @details
 * @note
 */
void MultiParticle::disturbance_Calc(C& out, double const& range) {
    Vector direction;
    direction.vector.x = get_random();
    direction.vector.y = get_random();
    direction.vector.z = get_random();
    direction.norm     = normCalc(direction.vector);

    direction.vector.x = direction.vector.x / direction.norm * range;
    direction.vector.y = direction.vector.y / direction.norm * range;
    direction.vector.z = direction.vector.z / direction.norm * range;
    out                = direction.vector;
}

/**
 * @brief		[-1:1]のランダムな値
 * @details		この関数単体では1度しか計算を行わない
 * @note		BaseCalc.hppで定義
 * @return		random [0:1]
 */
double MultiParticle::get_random() {
    // 乱数生成器
    static std::mt19937_64 mt64(0);

    // [min_val, max_val] の一様分布整数 (doulb) の分布生成器
    std::uniform_real_distribution<double> get_rand_uni_real(-1.0, 1.0);

    // 乱数を生成
    return get_rand_uni_real(mt64);
}

#if defined __SHAPE_CUBE__
/**
 * @brief  		合力 Fをベクトル Fに変換する
 * @param[in] 	int j
 * @param[in]	int i
 * @details		恐らく力の合成はここで行っている
 * @note
 */
void MultiParticle::fConv(int const& i, int const& j, int const& k) {
    // initialize
    p->f[i][j][k].x = 0;
    p->f[i][j][k].y = 0;
    p->f[i][j][k].z = 0;
    if (p->flag[i][j][k] & BIT_CEILING) {
        if (p->F[i][j][k].ip != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].ip * p->li[i][j][k].vector.x /
                                p->li[i][j][k].norm);
            p->f[i][j][k].y += (p->F[i][j][k].ip * p->li[i][j][k].vector.y /
                                p->li[i][j][k].norm);
            p->f[i][j][k].z += (p->F[i][j][k].ip * p->li[i][j][k].vector.z /
                                p->li[i][j][k].norm);
        }

        if (p->F[i][j][k].im != 0) {
            p->f[i][j][k].x +=
                (p->F[i][j][k].im * -1 * p->li[i][j - 1][k].vector.x /
                 p->li[i][j - 1][k].norm);
            p->f[i][j][k].y +=
                (p->F[i][j][k].im * -1 * p->li[i][j - 1][k].vector.y /
                 p->li[i][j - 1][k].norm);
            p->f[i][j][k].z +=
                (p->F[i][j][k].im * -1 * p->li[i][j - 1][k].vector.z /
                 p->li[i][j - 1][k].norm);
        }

        if (p->F[i][j][k].jp != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].jp * p->lj[i][j][k].vector.x /
                                p->lj[i][j][k].norm);
            p->f[i][j][k].y += (p->F[i][j][k].jp * p->lj[i][j][k].vector.y /
                                p->lj[i][j][k].norm);
            p->f[i][j][k].z += (p->F[i][j][k].jp * p->lj[i][j][k].vector.z /
                                p->lj[i][j][k].norm);
        }

        if (p->F[i][j][k].jm != 0) {
            if (p->flag[i][j][k] & BIT_BOTTOM) {
                p->f[i][j][k].x +=
                    (p->F[i][j][k].jm * -1 * p->lj[i][j][k - 1].vector.x /
                     p->lj[i][j][k - 1].norm);
                p->f[i][j][k].y +=
                    (p->F[i][j][k].jm * -1 * p->lj[i][j][k - 1].vector.y /
                     p->lj[i][j][k - 1].norm);
                p->f[i][j][k].z +=
                    (p->F[i][j][k].jm * -1 * p->lj[i][j][k - 1].vector.z /
                     p->lj[i][j][k - 1].norm);
            } else {
                p->f[i][j][k].x +=
                    (p->F[i][j][k].jm * -1 * p->lj[i - 1][j][k].vector.x /
                     p->lj[i - 1][j][k].norm);
                p->f[i][j][k].y +=
                    (p->F[i][j][k].jm * -1 * p->lj[i - 1][j][k].vector.y /
                     p->lj[i - 1][j][k].norm);
                p->f[i][j][k].z +=
                    (p->F[i][j][k].jm * -1 * p->lj[i - 1][j][k].vector.z /
                     p->lj[i - 1][j][k].norm);
            }
        }

        if (p->F[i][j][k].sv != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.x /
                                p->S[i][j][k].cp.norm);
            p->f[i][j][k].y += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.y /
                                p->S[i][j][k].cp.norm);
            p->f[i][j][k].z += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.z /
                                p->S[i][j][k].cp.norm);
        }

        // 面外の曲げによる力を計算
        if (p->F[i][j][k].ipv != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].ipv * p->Si[i][j][k].cp.vector.x /
                                p->Si[i][j][k].cp.norm);
            p->f[i][j][k].y += (p->F[i][j][k].ipv * p->Si[i][j][k].cp.vector.y /
                                p->Si[i][j][k].cp.norm);
            p->f[i][j][k].z += (p->F[i][j][k].ipv * p->Si[i][j][k].cp.vector.z /
                                p->Si[i][j][k].cp.norm);
        }

        if (p->F[i][j][k].imv != 0) {
            p->f[i][j][k].x +=
                (p->F[i][j][k].imv * p->Si[i][j - 1][k].cp.vector.x /
                 p->Si[i][j - 1][k].cp.norm);
            p->f[i][j][k].y +=
                (p->F[i][j][k].imv * p->Si[i][j - 1][k].cp.vector.y /
                 p->Si[i][j - 1][k].cp.norm);
            p->f[i][j][k].z +=
                (p->F[i][j][k].imv * p->Si[i][j - 1][k].cp.vector.z /
                 p->Si[i][j - 1][k].cp.norm);
        }

        if (p->F[i][j][k].jpv != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].jpv * p->Sj[i][j][k].cp.vector.x /
                                p->Sj[i][j][k].cp.norm);
            p->f[i][j][k].y += (p->F[i][j][k].jpv * p->Sj[i][j][k].cp.vector.y /
                                p->Sj[i][j][k].cp.norm);
            p->f[i][j][k].z += (p->F[i][j][k].jpv * p->Sj[i][j][k].cp.vector.z /
                                p->Sj[i][j][k].cp.norm);
        }

        if (p->F[i][j][k].jmv != 0) {
            if (p->flag[i][j][k] & BIT_BOTTOM) {
                p->f[i][j][k].x +=
                    (p->F[i][j][k].jmv * p->Sj[i][j][k - 1].cp.vector.x /
                     p->Sj[i][j][k - 1].cp.norm);
                p->f[i][j][k].y +=
                    (p->F[i][j][k].jmv * p->Sj[i][j][k - 1].cp.vector.y /
                     p->Sj[i][j][k - 1].cp.norm);
                p->f[i][j][k].z +=
                    (p->F[i][j][k].jmv * p->Sj[i][j][k - 1].cp.vector.z /
                     p->Sj[i][j][k - 1].cp.norm);
            } else {
                p->f[i][j][k].x +=
                    (p->F[i][j][k].jmv * p->Sj[i - 1][j][k].cp.vector.x /
                     p->Sj[i - 1][j][k].cp.norm);
                p->f[i][j][k].y +=
                    (p->F[i][j][k].jmv * p->Sj[i - 1][j][k].cp.vector.y /
                     p->Sj[i - 1][j][k].cp.norm);
                p->f[i][j][k].z +=
                    (p->F[i][j][k].jmv * p->Sj[i - 1][j][k].cp.vector.z /
                     p->Sj[i - 1][j][k].cp.norm);
            }
        }
    } else if (p->flag[i][j][k] & BIT_BACK) {
        if (p->F[i][j][k].ip != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].ip * p->li[i][j][k].vector.x /
                                p->li[i][j][k].norm);
            p->f[i][j][k].y += (p->F[i][j][k].ip * p->li[i][j][k].vector.y /
                                p->li[i][j][k].norm);
            p->f[i][j][k].z += (p->F[i][j][k].ip * p->li[i][j][k].vector.z /
                                p->li[i][j][k].norm);
        }

        if (p->F[i][j][k].im != 0) {
            if (p->flag[i][j][k] & BIT_LEFT) {
                p->f[i][j][k].x +=
                    (p->F[i][j][k].im * -1 * p->li[i][j - 1][k].vector.x /
                     p->li[i][j - 1][k].norm);
                p->f[i][j][k].y +=
                    (p->F[i][j][k].im * -1 * p->li[i][j - 1][k].vector.y /
                     p->li[i][j - 1][k].norm);
                p->f[i][j][k].z +=
                    (p->F[i][j][k].im * -1 * p->li[i][j - 1][k].vector.z /
                     p->li[i][j - 1][k].norm);
            } else {
                p->f[i][j][k].x +=
                    (p->F[i][j][k].im * -1 * p->li[i - 1][j][k].vector.x /
                     p->li[i - 1][j][k].norm);
                p->f[i][j][k].y +=
                    (p->F[i][j][k].im * -1 * p->li[i - 1][j][k].vector.y /
                     p->li[i - 1][j][k].norm);
                p->f[i][j][k].z +=
                    (p->F[i][j][k].im * -1 * p->li[i - 1][j][k].vector.z /
                     p->li[i - 1][j][k].norm);
            }
        }

        if (p->F[i][j][k].jp != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].jp * p->lj[i][j][k].vector.x /
                                p->lj[i][j][k].norm);
            p->f[i][j][k].y += (p->F[i][j][k].jp * p->lj[i][j][k].vector.y /
                                p->lj[i][j][k].norm);
            p->f[i][j][k].z += (p->F[i][j][k].jp * p->lj[i][j][k].vector.z /
                                p->lj[i][j][k].norm);
        }

        if (p->F[i][j][k].jm != 0) {
            p->f[i][j][k].x +=
                (p->F[i][j][k].jm * -1 * p->lj[i][j][k - 1].vector.x /
                 p->lj[i][j][k - 1].norm);
            p->f[i][j][k].y +=
                (p->F[i][j][k].jm * -1 * p->lj[i][j][k - 1].vector.y /
                 p->lj[i][j][k - 1].norm);
            p->f[i][j][k].z +=
                (p->F[i][j][k].jm * -1 * p->lj[i][j][k - 1].vector.z /
                 p->lj[i][j][k - 1].norm);
        }

        if (p->F[i][j][k].sv != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.x /
                                p->S[i][j][k].cp.norm);
            p->f[i][j][k].y += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.y /
                                p->S[i][j][k].cp.norm);
            p->f[i][j][k].z += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.z /
                                p->S[i][j][k].cp.norm);
        }

        // 面外の曲げによる力を計算
        if (p->F[i][j][k].ipv != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].ipv * p->Si[i][j][k].cp.vector.x /
                                p->Si[i][j][k].cp.norm);
            p->f[i][j][k].y += (p->F[i][j][k].ipv * p->Si[i][j][k].cp.vector.y /
                                p->Si[i][j][k].cp.norm);
            p->f[i][j][k].z += (p->F[i][j][k].ipv * p->Si[i][j][k].cp.vector.z /
                                p->Si[i][j][k].cp.norm);
        }

        if (p->F[i][j][k].imv != 0) {
            if (p->flag[i][j][k] & BIT_LEFT) {
                p->f[i][j][k].x +=
                    (p->F[i][j][k].imv * p->Si[i][j - 1][k].cp.vector.x /
                     p->Si[i][j - 1][k].cp.norm);
                p->f[i][j][k].y +=
                    (p->F[i][j][k].imv * p->Si[i][j - 1][k].cp.vector.y /
                     p->Si[i][j - 1][k].cp.norm);
                p->f[i][j][k].z +=
                    (p->F[i][j][k].imv * p->Si[i][j - 1][k].cp.vector.z /
                     p->Si[i][j - 1][k].cp.norm);
            } else {
                p->f[i][j][k].x +=
                    (p->F[i][j][k].imv * p->Si[i - 1][j][k].cp.vector.x /
                     p->Si[i - 1][j][k].cp.norm);
                p->f[i][j][k].y +=
                    (p->F[i][j][k].imv * p->Si[i - 1][j][k].cp.vector.y /
                     p->Si[i - 1][j][k].cp.norm);
                p->f[i][j][k].z +=
                    (p->F[i][j][k].imv * p->Si[i - 1][j][k].cp.vector.z /
                     p->Si[i - 1][j][k].cp.norm);
            }
        }

        if (p->F[i][j][k].jpv != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].jpv * p->Sj[i][j][k].cp.vector.x /
                                p->Sj[i][j][k].cp.norm);
            p->f[i][j][k].y += (p->F[i][j][k].jpv * p->Sj[i][j][k].cp.vector.y /
                                p->Sj[i][j][k].cp.norm);
            p->f[i][j][k].z += (p->F[i][j][k].jpv * p->Sj[i][j][k].cp.vector.z /
                                p->Sj[i][j][k].cp.norm);
        }

        if (p->F[i][j][k].jmv != 0) {
            p->f[i][j][k].x +=
                (p->F[i][j][k].jmv * p->Sj[i][j][k - 1].cp.vector.x /
                 p->Sj[i][j][k - 1].cp.norm);
            p->f[i][j][k].y +=
                (p->F[i][j][k].jmv * p->Sj[i][j][k - 1].cp.vector.y /
                 p->Sj[i][j][k - 1].cp.norm);
            p->f[i][j][k].z +=
                (p->F[i][j][k].jmv * p->Sj[i][j][k - 1].cp.vector.z /
                 p->Sj[i][j][k - 1].cp.norm);
        }
    } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
        if (p->F[i][j][k].ip != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].ip * p->li[i][j][k].vector.x /
                                p->li[i][j][k].norm);
            p->f[i][j][k].y += (p->F[i][j][k].ip * p->li[i][j][k].vector.y /
                                p->li[i][j][k].norm);
            p->f[i][j][k].z += (p->F[i][j][k].ip * p->li[i][j][k].vector.z /
                                p->li[i][j][k].norm);
        }

        if (p->F[i][j][k].im != 0) {
            p->f[i][j][k].x +=
                (p->F[i][j][k].im * -1 * p->li[i][j - 1][k].vector.x /
                 p->li[i][j - 1][k].norm);
            p->f[i][j][k].y +=
                (p->F[i][j][k].im * -1 * p->li[i][j - 1][k].vector.y /
                 p->li[i][j - 1][k].norm);
            p->f[i][j][k].z +=
                (p->F[i][j][k].im * -1 * p->li[i][j - 1][k].vector.z /
                 p->li[i][j - 1][k].norm);
        }

        if (p->F[i][j][k].jp != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].jp * p->lj[i][j][k].vector.x /
                                p->lj[i][j][k].norm);
            p->f[i][j][k].y += (p->F[i][j][k].jp * p->lj[i][j][k].vector.y /
                                p->lj[i][j][k].norm);
            p->f[i][j][k].z += (p->F[i][j][k].jp * p->lj[i][j][k].vector.z /
                                p->lj[i][j][k].norm);
        }

        if (p->F[i][j][k].jm != 0) {
            p->f[i][j][k].x +=
                (p->F[i][j][k].jm * -1 * p->lj[i][j][k - 1].vector.x /
                 p->lj[i][j][k - 1].norm);
            p->f[i][j][k].y +=
                (p->F[i][j][k].jm * -1 * p->lj[i][j][k - 1].vector.y /
                 p->lj[i][j][k - 1].norm);
            p->f[i][j][k].z +=
                (p->F[i][j][k].jm * -1 * p->lj[i][j][k - 1].vector.z /
                 p->lj[i][j][k - 1].norm);
        }

        if (p->F[i][j][k].sv != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.x /
                                p->S[i][j][k].cp.norm);
            p->f[i][j][k].y += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.y /
                                p->S[i][j][k].cp.norm);
            p->f[i][j][k].z += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.z /
                                p->S[i][j][k].cp.norm);
        }

        // 面外の曲げによる力を計算
        if (p->F[i][j][k].ipv != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].ipv * p->Si[i][j][k].cp.vector.x /
                                p->Si[i][j][k].cp.norm);
            p->f[i][j][k].y += (p->F[i][j][k].ipv * p->Si[i][j][k].cp.vector.y /
                                p->Si[i][j][k].cp.norm);
            p->f[i][j][k].z += (p->F[i][j][k].ipv * p->Si[i][j][k].cp.vector.z /
                                p->Si[i][j][k].cp.norm);
        }

        if (p->F[i][j][k].imv != 0) {
            p->f[i][j][k].x +=
                (p->F[i][j][k].imv * p->Si[i][j - 1][k].cp.vector.x /
                 p->Si[i][j - 1][k].cp.norm);
            p->f[i][j][k].y +=
                (p->F[i][j][k].imv * p->Si[i][j - 1][k].cp.vector.y /
                 p->Si[i][j - 1][k].cp.norm);
            p->f[i][j][k].z +=
                (p->F[i][j][k].imv * p->Si[i][j - 1][k].cp.vector.z /
                 p->Si[i][j - 1][k].cp.norm);
        }

        if (p->F[i][j][k].jpv != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].jpv * p->Sj[i][j][k].cp.vector.x /
                                p->Sj[i][j][k].cp.norm);
            p->f[i][j][k].y += (p->F[i][j][k].jpv * p->Sj[i][j][k].cp.vector.y /
                                p->Sj[i][j][k].cp.norm);
            p->f[i][j][k].z += (p->F[i][j][k].jpv * p->Sj[i][j][k].cp.vector.z /
                                p->Sj[i][j][k].cp.norm);
        }

        if (p->F[i][j][k].jmv != 0) {
            p->f[i][j][k].x +=
                (p->F[i][j][k].jmv * p->Sj[i][j][k - 1].cp.vector.x /
                 p->Sj[i][j][k - 1].cp.norm);
            p->f[i][j][k].y +=
                (p->F[i][j][k].jmv * p->Sj[i][j][k - 1].cp.vector.y /
                 p->Sj[i][j][k - 1].cp.norm);
            p->f[i][j][k].z +=
                (p->F[i][j][k].jmv * p->Sj[i][j][k - 1].cp.vector.z /
                 p->Sj[i][j][k - 1].cp.norm);
        }
    }
}
#else
// -- Cube 以外 -- //
/**
 * @brief  		合力 Fをベクトル Fに変換する
 * @param[in] 	int j
 * @param[in]	int i
 * @details		恐らく力の合成はここで行っている
 * @note
 */
void MultiParticle::fConv(int const& i, int const& j, int const& k) {
    // initialize
    p->f[i][j][k].x = 0;
    p->f[i][j][k].y = 0;
    p->f[i][j][k].z = 0;
    p->damper[i][j][k].x = 0;
    p->damper[i][j][k].y = 0;
    p->damper[i][j][k].z = 0;

    if (CylinderPressure) {
        if (param->boundary.cylinder_boundary) {
            if (p->F[i][j][k].ip != 0) {
                p->f[i][j][k].x += (p->F[i][j][k].ip * p->li[i][j][k].vector.x /
                                    p->li[i][j][k].norm);
                p->f[i][j][k].y += (p->F[i][j][k].ip * p->li[i][j][k].vector.y /
                                    p->li[i][j][k].norm);
                p->f[i][j][k].z += (p->F[i][j][k].ip * p->li[i][j][k].vector.z /
                                    p->li[i][j][k].norm);
            }
            if (p->flag[i][j][k] == Left || p->flag[i][j][k] == LeftBottom ||
                p->flag[i][j][k] == LeftTop) {
                p->f[i][j][k].x +=
                    (p->F[i][j][k].im * -1 * p->li[i - 1][j][k].vector.x /
                     p->li[i - 1][j][k].norm);
                p->f[i][j][k].y +=
                    (p->F[i][j][k].im * -1 * p->li[i - 1][j][k].vector.y /
                     p->li[i - 1][j][k].norm);
                p->f[i][j][k].z +=
                    (p->F[i][j][k].im * -1 * p->li[i - 1][j][k].vector.z /
                     p->li[i - 1][j][k].norm);
            }
        } else {
            if (p->F[i][j][k].ip != 0) {
                if (p->flag[i][j][k] == Right ||
                    p->flag[i][j][k] == RightBottom ||
                    p->flag[i][j][k] == RightTop) {
                    p->f[i][j][k].y +=
                        (p->F[i][j][k].ip * p->omp[i][j][k].li.vector.y /
                         p->omp[i][j][k].li.norm);
                    p->f[i][j][k].x +=
                        (p->F[i][j][k].ip * p->omp[i][j][k].li.vector.x /
                         p->omp[i][j][k].li.norm);
                    p->f[i][j][k].z +=
                        (p->F[i][j][k].ip * p->omp[i][j][k].li.vector.z /
                         p->omp[i][j][k].li.norm);
                }
                if (p->flag[i][j][k] == Left ||
                    p->flag[i][j][k] == LeftBottom ||
                    p->flag[i][j][k] == LeftTop) {
                    p->f[i][j][k].x +=
                        (p->F[i][j][k].im * -1 * p->omp[i][j][k].li.vector.x /
                         p->omp[i][j][k].li.norm);
                    p->f[i][j][k].y +=
                        (p->F[i][j][k].im * -1 * p->omp[i][j][k].li.vector.y /
                         p->omp[i][j][k].li.norm);
                    p->f[i][j][k].z +=
                        (p->F[i][j][k].im * -1 * p->omp[i][j][k].li.vector.z /
                         p->omp[i][j][k].li.norm);
                }
            }
        }
        if (p->F[i][j][k].sv != 0) {
            p->f[i][j][k].x += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.x /
                                p->S[i][j][k].cp.norm);
            p->f[i][j][k].y += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.y /
                                p->S[i][j][k].cp.norm);
            p->f[i][j][k].z += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.z /
                                p->S[i][j][k].cp.norm);
        }
    } else { //Current part
        if (p->F[i][j][k].ip != 0) {
            // p->f[i][j][k].x += (p->F[i][j][k].ip * p->li[i][j][k].vector.x /
            //                     p->li[i][j][k].norm);
            // p->f[i][j][k].y += (p->F[i][j][k].ip * p->li[i][j][k].vector.y /
            //                     p->li[i][j][k].norm);
            // p->f[i][j][k].z += (p->F[i][j][k].ip * p->li[i][j][k].vector.z /
            //                     p->li[i][j][k].norm);

            p->f[i][j][k] += (p->F[i][j][k].ip * p->li[i][j][k].vector /
                              p->li[i][j][k].norm);

            p->damper[i][j][k] += p->cti[i][j][k];
            p->damper[i][j][k] += (p->cs[i][j][k].ip * p->li[i][j][k].vector /
                              p->li[i][j][k].norm);
            // p->f[i][j][k] += UnitVectorCalc(p->F[i][j][k].ip,
            // p->li[i][j][k]);
        }
        if (p->F[i][j][k].sv != 0) {
            // p->f[i][j][k].x += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.x /
            //                     p->S[i][j][k].cp.norm);
            // p->f[i][j][k].y += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.y /
            //                     p->S[i][j][k].cp.norm);
            // p->f[i][j][k].z += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector.z /
            //                     p->S[i][j][k].cp.norm);

            p->f[i][j][k] += (p->F[i][j][k].sv * p->S[i][j][k].cp.vector /
                              p->S[i][j][k].cp.norm);
            // p->f[i][j][k] += UnitVectorCalc(p->F[i][j][k].sv, p->S[i][j][k]);
        }
    }

    if (p->F[i][j][k].im != 0) {
        // p->f[i][j][k].x +=
        //     (p->F[i][j][k].im * -1 * p->li[i - 1][j][k].vector.x /
        //      p->li[i - 1][j][k].norm);
        // p->f[i][j][k].y +=
        //     (p->F[i][j][k].im * -1 * p->li[i - 1][j][k].vector.y /
        //      p->li[i - 1][j][k].norm);
        // p->f[i][j][k].z +=
        //     (p->F[i][j][k].im * -1 * p->li[i - 1][j][k].vector.z /
        //      p->li[i - 1][j][k].norm);

        p->f[i][j][k] += (p->F[i][j][k].im * -1 * p->li[i - 1][j][k].vector /
                          p->li[i - 1][j][k].norm);

        p->damper[i][j][k] -= p->cti[i - 1][j][k];
        p->damper[i][j][k] += (p->cs[i][j][k].im  * -1 * p->li[i - 1][j][k].vector /
                                p->li[i - 1][j][k].norm);
        // p->f[i][j][k] += UnitVectorCalc(p->F[i][j][k].im, p->li[i -
        // 1][j][k]);
    }

    if (p->F[i][j][k].jp != 0) {
        // p->f[i][j][k].x +=
        //     (p->F[i][j][k].jp * p->lj[i][j][k].vector.x / p->lj[i][j][k].norm);
        // p->f[i][j][k].y +=
        //     (p->F[i][j][k].jp * p->lj[i][j][k].vector.y / p->lj[i][j][k].norm);
        // p->f[i][j][k].z +=
        //     (p->F[i][j][k].jp * p->lj[i][j][k].vector.z / p->lj[i][j][k].norm);

        p->f[i][j][k] +=
            (p->F[i][j][k].jp * p->lj[i][j][k].vector / p->lj[i][j][k].norm);

        p->damper[i][j][k] += p->ctj[i][j][k];
        p->damper[i][j][k] += (p->cs[i][j][k].jp 
                                * p->lj[i][j][k].vector / p->lj[i][j][k].norm);
        // p->f[i][j][k] += UnitVectorCalc(p->F[i][j][k].jp, p->lj[i][j][k]);
    }

    if (p->F[i][j][k].jm != 0) {
        // p->f[i][j][k].x +=
        //     (p->F[i][j][k].jm * -1 * p->lj[i][j - 1][k].vector.x /
        //      p->lj[i][j - 1][k].norm);
        // p->f[i][j][k].y +=
        //     (p->F[i][j][k].jm * -1 * p->lj[i][j - 1][k].vector.y /
        //      p->lj[i][j - 1][k].norm);
        // p->f[i][j][k].z +=
        //     (p->F[i][j][k].jm * -1 * p->lj[i][j - 1][k].vector.z /
        //      p->lj[i][j - 1][k].norm);

        p->f[i][j][k] += (p->F[i][j][k].jm * -1 * p->lj[i][j - 1][k].vector /
                          p->lj[i][j - 1][k].norm);

        p->damper[i][j][k] -= p->ctj[i][j - 1][k];
        p->damper[i][j][k] += (p->cs[i][j][k].jm * -1 * p->lj[i][j - 1][k].vector /
                          p->lj[i][j - 1][k].norm);
        // p->f[i][j][k] += UnitVectorCalc(p->F[i][j][k].jm, p->lj[i][j -
        // 1][k]);
    }

    // 面外の曲げによる力を計算
    if (p->F[i][j][k].ipv != 0) {
        // p->f[i][j][k].x += (p->F[i][j][k].ipv * p->Si[i][j][k].cp.vector.x /
        //                     p->Si[i][j][k].cp.norm);
        // p->f[i][j][k].y += (p->F[i][j][k].ipv * p->Si[i][j][k].cp.vector.y /
        //                     p->Si[i][j][k].cp.norm);
        // p->f[i][j][k].z += (p->F[i][j][k].ipv * p->Si[i][j][k].cp.vector.z /
        //                     p->Si[i][j][k].cp.norm);

        p->f[i][j][k] += (p->F[i][j][k].ipv * p->Si[i][j][k].cp.vector /
                          p->Si[i][j][k].cp.norm);
        // p->f[i][j][k] += UnitVectorCalc(p->F[i][j][k].ipv, p->Si[i][j][k]);
    }

    if (p->F[i][j][k].imv != 0) {
        // p->f[i][j][k].x += (p->F[i][j][k].imv * p->Si[i - 1][j][k].cp.vector.x /
        //                     p->Si[i - 1][j][k].cp.norm);
        // p->f[i][j][k].y += (p->F[i][j][k].imv * p->Si[i - 1][j][k].cp.vector.y /
        //                     p->Si[i - 1][j][k].cp.norm);
        // p->f[i][j][k].z += (p->F[i][j][k].imv * p->Si[i - 1][j][k].cp.vector.z /
        //                     p->Si[i - 1][j][k].cp.norm);

        p->f[i][j][k] += (p->F[i][j][k].imv * p->Si[i - 1][j][k].cp.vector /
                          p->Si[i - 1][j][k].cp.norm);
        // p->f[i][j][k] += UnitVectorCalc(p->F[i][j][k].imv, p->Si[i][j -
        // 1][k]);
    }

    if (p->F[i][j][k].jpv != 0) {
        // p->f[i][j][k].x += (p->F[i][j][k].jpv * p->Sj[i][j][k].cp.vector.x /
        //                     p->Sj[i][j][k].cp.norm);
        // p->f[i][j][k].y += (p->F[i][j][k].jpv * p->Sj[i][j][k].cp.vector.y /
        //                     p->Sj[i][j][k].cp.norm);
        // p->f[i][j][k].z += (p->F[i][j][k].jpv * p->Sj[i][j][k].cp.vector.z /
        //                     p->Sj[i][j][k].cp.norm);

        p->f[i][j][k] += (p->F[i][j][k].jpv * p->Sj[i][j][k].cp.vector /
                          p->Sj[i][j][k].cp.norm);
        // p->f[i][j][k] += UnitVectorCalc(p->F[i][j][k].jpv, p->Sj[i][j][k]);
    }

    if (p->F[i][j][k].jmv != 0) {
        // p->f[i][j][k].x += (p->F[i][j][k].jmv * p->Sj[i][j - 1][k].cp.vector.x /
        //                     p->Sj[i][j - 1][k].cp.norm);
        // p->f[i][j][k].y += (p->F[i][j][k].jmv * p->Sj[i][j - 1][k].cp.vector.y /
        //                     p->Sj[i][j - 1][k].cp.norm);
        // p->f[i][j][k].z += (p->F[i][j][k].jmv * p->Sj[i][j - 1][k].cp.vector.z /
        //                     p->Sj[i][j - 1][k].cp.norm);

        p->f[i][j][k] += (p->F[i][j][k].jmv * p->Sj[i][j - 1][k].cp.vector /
                          p->Sj[i][j - 1][k].cp.norm);
        // p->f[i][j][k] += UnitVectorCalc(p->F[i][j][k].jmv, p->Sj[i][j -
        // 1][k]);
    }

#ifdef __TWIST__ //ねじりによる力を計算
    // if (j == 20 && i == 20){
    //      cout << "f.x=" << p->f[i][j][k].x
    //           << ", f.y=" << p->f[i][j][k].y
    //           << ", f.z=" << p->f[i][j][k].z
    //           << endl;
    // }
    p->f[i][j][k] += p->Ftw[i][j][k];
    // if (j == 20 && i == 20){
    //      cout << "after, "
    //           << "ftw.x=" << p->Ftw[i][j][k].x
    //           << ", ftw.y=" << p->Ftw[i][j][k].y
    //           << ", ftw.z=" << p->Ftw[i][j][k].z
    //           << endl;
    //     cout << "after     f.x=" << p->f[i][j][k].x
    //           << ", f.y=" << p->f[i][j][k].y
    //           << ", f.z=" << p->f[i][j][k].z
    //           << endl;
    // }

#endif

}
#endif

/**
 * @brief 		内積を計算する
 * @param[in] 	C vectorA
 * @param[in] 	C vectorB
 * @return		double 内積
 */
double MultiParticle::innerProductCalc(C const& vectorA, C const& vectorB) {
    return (vectorA.x * vectorB.x + vectorA.y * vectorB.y +
            vectorA.z * vectorB.z);
}

/**
 * @brief 		外積を計算する
 * @param[out] 	C product：外積
 * @param[in] 	C vectorA
 * @param[in] 	C vectorB
 */
void MultiParticle::crossProductCalc(C& product, C const& vectorA,
                                     C const& vectorB) {
    product.x = vectorA.y * vectorB.z - vectorA.z * vectorB.y;
    product.y = vectorA.z * vectorB.x - vectorA.x * vectorB.z;
    product.z = vectorA.x * vectorB.y - vectorA.y * vectorB.x;
}

/**
 * @brief 		Calclate length (長さを計算する)
 * @param[in] 	C vector
 * @return		double 長さ
 */
double MultiParticle::normCalc(C const& vector) {
    return sqrt((vector.x * vector.x) + (vector.y * vector.y) +
                (vector.z * vector.z));
}

/**
 * @brief 		vectorAとvectorBによってなすベクトルの長さを計算する
 * @param[in] 	C vectorA
 * @param[in] 	C vectorB
 * @return		double 長さ
 */
double MultiParticle::normCalcV2(C const& vectorA, C const& vectorB) {
    return sqrt(((vectorA.x - vectorB.x) * (vectorA.x - vectorB.x)) +
                ((vectorA.y - vectorB.y) * (vectorA.y - vectorB.y)) +
                ((vectorA.z - vectorB.z) * (vectorA.z - vectorB.z)));
}

//-----------------------------------
//
// Runge Kutta Calc Method 4th Order.
//
//-----------------------------------
/**
 * @brief		ルンゲクッタ法
 * @param[in] 	double r = p_>c[i][j]
 * @param[in] 	double v = p_>v[i][j]
 * @param[in] 	double f = p_>f[i][j]
 * @param[in] 	double S = p_>S0[i][j]
 * @details		この関数単体では1度しか計算を行わない
 * @note		BaseCalc.hppで定義
 * GetNewCoordinate.hppで使用されている
 * 問題点
 * k41, k2を求めるときに、k32を半分にしている
 */
void MultiParticle::RK4M(double& myr, double& myv, double const& f,
                         double const& S) {
    double k11, k12;
    double k21, k22;
    double k31, k32;
    double k41, k42;

    k11 = param->m_dt * RK4One(myv);
    k12 = param->m_dt * RK4Two(myv, f, S);

    k21 = param->m_dt * RK4One(myv + k12 / 2);
    k22 = param->m_dt * RK4Two(myv + k12 / 2, f, S);

    k31 = param->m_dt * RK4One(myv + k22 / 2);
    k32 = param->m_dt * RK4Two(myv + k22 / 2, f, S);

    k41 = param->m_dt * RK4One(myv + k32 / 2);
    k42 = param->m_dt * RK4Two(myv + k32 / 2, f, S);
    // k41 = param->m_dt * RK4One(myv + k32 / 2);
    // k42 = param->m_dt * RK4Two(myv + k32 / 2, f, S);

    myr = myr + (k11 + 2 * k21 + 2 * k31 + k41) / 6;
    myv = myv + (k12 + 2 * k22 + 2 * k32 + k42) / 6;
}

//-----------------------------------
//
// Runge Kutta Calc Method 4th Order function one.
//
//-----------------------------------
/**
 * @brief	ルンゲクッタ法のrの微小変化を求める式
 * @note	計算式は
 */
double MultiParticle::RK4One(double const& v) { return v; }

//-----------------------------------
//
// Runge Kutta Calc Method 4th Order funciton two.
//
//-----------------------------------
/**
 * @brief	ルンゲクッタ法のvの微小変化を求める式
 */
double MultiParticle::RK4Two(double const& v, double const& f,
                             double const& S) {
    //! vの微小変化を求める式、C_EI ;* (f - Cv * v) / S ここで、Cvは粘性項
    // cout << f << ',' << param->m_Cv * v << ',' << S << endl;
    // cout << std::fabs(f) << ',' << std::fabs(param->m_Cv * v) << ',' << S
    //      << endl;
    // cout << endl;
    // Correct
    // return (param->C_EI * (f - param->m_Cv * v) / S);
    return ((param->C_EI * f) / S) - (param->C_EI * (param->m_Cv * v) / S);
    return (param->C_EI * (f) / S - (param->m_Cv * v));

    // if (f == 0) {
    //     return 0;
    // } else if (f > 0) {
    //     return (param->C_EI * (std::fabs(f) - std::fabs(param->m_Cv * v)) /
    //     S);
    // } else {
    //     return -1.0 *
    //            (param->C_EI * (std::fabs(f) - std::fabs(param->m_Cv * v)) /
    //            S);
    // }
}

/*                       TEST (Trial)                              */
// おそらくこちらが使われている？
/**
 * @brief		ルンゲクッタ法
 * @param[in] 	double r = p_>c[i][j]
 * @param[in] 	double v = p_>v[i][j]
 * @param[in] 	double f = p_>f[i][j]
 * @param[in] 	double S = p_>S0[i][j]
 * @details		この関数単体では1度しか計算を行わない
 * @note		BaseCalc.hppで定義
 * GetNewCoordinate.hppで使用されている
 * 問題点
 * k41, k2を求めるときに、k32を半分にしている
 */
void MultiParticle::RK4M(double& myr, double& myv, const double& f,
                         const double& S0,
                         const double& Fair, const double& c) {
    //   if (Fair != 0) {
    //     cout << "arguments number" << endl;
    //     cout << myr << ":" << myv << ":" << f << ":" <<
    // S0
    //          << ":" << Fair << endl;
    //   }
    // if (!SimplePressure) {
    //     cout << "use test RK4M" << endl;
    //     abort();
    // }

    double k11, k12;
    double k21, k22;
    double k31, k32;
    double k41, k42;

    k11 = param->m_dt * RK4One(myv);
    k12 = param->m_dt * RK4Two(myv, f, S0, Fair, c);
    //   if (k11 != 0 && k12 != 0) {
    //     cout << "k11,k12: " << k11 << "," << k12 << endl;
    //   }

    k21 = param->m_dt * RK4One(myv + k12 / 2);
    k22 = param->m_dt * RK4Two(myv + k12 / 2, f, S0, Fair, c);
    //   if (k21 != 0 && k22 != 0) {
    //     cout << "k21,k22: " << k21 << "," << k22 << endl;
    //   }

    k31 = param->m_dt * RK4One(myv + k22 / 2);
    k32 = param->m_dt * RK4Two(myv + k22 / 2, f, S0, Fair, c);
    //   if (k31 != 0 && k32 != 0) {
    //     cout << "k31,k32: " << k31 << "," << k32 << endl;
    //   }

    k41 = param->m_dt * RK4One(myv + k32 / 2);
    k42 = param->m_dt * RK4Two(myv + k32 / 2, f, S0, Fair, c);
    //   if (k41 != 0 && k42 != 0) {
    //     cout << "k41,k42: " << k41 << "," << k42 << endl;
    //   }

    myr = myr + (k11 + 2 * k21 + 2 * k31 + k41) / 6;
    myv = myv + (k12 + 2 * k22 + 2 * k32 + k42) / 6;
}

//-----------------------------------
//
// Runge Kutta Calc Method 4th Order function one.
//
//-----------------------------------
/**
 * @brief	ルンゲクッタ法のrの微小変化を求める式
 * @note	計算式は
 */
// double MultiParticle::RK4One(double const& v) { return v; }

//-----------------------------------
//
// Runge Kutta Calc Method 4th Order funciton two.
//
//-----------------------------------
/**
 * @brief	ルンゲクッタ法のvの微小変化を求める式
 */
double MultiParticle::RK4Two(const double& v, const double& f,
                             const double& S0,
                             const double& Fair, const double& c) {
    //! vの微小変化を求める式、C_EI * (f - Cv * v) / S ここで、Cvは粘性項

#ifdef __DAMPER__
    return (((param->C_EI * (f - c)) / S0) + ((param->C_EI * param->C_AE * Fair) / S0));
#else
    return (((param->C_EI * f) / S0) + ((param->C_EI * param->C_AE * Fair) / S0)) - ((param->C_EI * param->m_Cv * v) / S0);

    return (param->C_EI * (f - param->m_Cv * v) / S0 +
            (param->C_EI * param->C_AE) * (Fair - param->m_Cv * v) /
                S0);
#endif  
}
