/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file	InitialConditions.hpp
 * @brief	粒子の初期配置を行い、パラメータの初期値を決める
 * @details
 * ///////////////////////////////////////////////////////////////////////////////
 */

/**
 * @brief set particle and flag depend shape
 * @note SetFlag, DivideModel and Cylinder used each class Params and Particle.
 * @param analysis_shape
 * @param grid_pattern
 */
void MultiParticle::setInitialAnalysisShape(std::string const& analysis_shape,
                                            std::string const& grid_pattern) {
    if (analysis_shape == "cuboid") {
        setInitialConditionsSetFlagCube();
        setInitialConditionsShapeCube();
    } else {
        setInitialConditionsSetFlag();
        if (analysis_shape == "cylinder") {
            setInitialConditionsShapeCylinder();
        } else if (analysis_shape == "square" ||
                   analysis_shape == "quadrangle") {
            if (grid_pattern == "equally") {
                setInitialConditionsEquallyDividedModeling();
            } else if (grid_pattern == "unequally") {
                setInitialConditionsUnEquallyDividedModeling();
            } else if (grid_pattern == "oblique") {
                setInitialConditionsObliqueAlignmentModeling();
            }
            setInitialConditionsSetParam();
        }
    }
}

/**
 * @brief	最初に書く粒子間のパラメータを求める
 */
void MultiParticle::setInitialConditions() {
    console(3);

    setInitialConditionsLCalc();
    setInitialConditionsGCalc();
    setInitialConditionsMiCalc();
    setInitialConditionsMjCalc();
    setInitialConditionsSCalc();
    setInitialConditionsSiCalc();
    setInitialConditionsSjCalc();

    param->center_i   = p->c.size() / 2;
    param->center_j   = p->c[param->center_i].size() / 2;
    param->center_k   = p->c[param->center_i][param->center_j].size() / 2;
    param->itr_harf_x = p->c.size() / 2;
    param->itr_harf_y = p->c[param->itr_harf_x].size() / 2;
    param->itr_harf_z = p->c[param->itr_harf_x][param->itr_harf_y].size() / 2;
    param->itr_max_x  = p->c.size() - 1;
    param->itr_max_y  = p->c[param->itr_max_x].size() - 1;
    param->itr_max_z  = p->c[param->itr_max_x][param->itr_max_y].size() - 1;

    // cout << "param->center_i:" << param->center_i << endl;
    // cout << "param->center_j:" << param->center_j << endl;
    // cout << "param->itr_harf_x:" << param->itr_harf_x << endl;
    // cout << "param->itr_harf_y:" << param->itr_harf_y << endl;
    // cout << "param->itr_harf_z:" << param->itr_harf_z << endl;
    // cout << "param->itr_max_x:" << param->itr_max_x << endl;
    // cout << "param->itr_max_y:" << param->itr_max_y << endl;
    // cout << "param->itr_max_z:" << param->itr_max_z << endl;

    CalcMainSimulation();
    //     int i, j, k;
    // #pragma omp parallel
    //     {
    //         //	iはプライベート(各スレッドで共有しない)、分割はstatic
    // #pragma omp for private(j) private(k) schedule(static)
    //         for (i = 0; i < param->itr_max_x; i++) {
    //             for (j = 0; j < param->itr_max_y; j++) {
    //                 for (k = 0; k < param->itr_max_z; k++) {
    //                     // cout << i << "," << j << "," << k << endl;
    //                     // cout << "Run VirtualParticleCalc" << endl;
    //                     // OldVirtualParticleCalc(i, j, k);

    //                     VirtualParticleCalc(i, j, k);
    //                 }
    //             }
    //         }

    // #pragma omp for private(j) private(k) schedule(static)
    //         for (i = 0; i < param->itr_max_x; i++) {
    //             for (j = 0; j < param->itr_max_y; j++) {
    //                 for (k = 0; k < param->itr_max_z; k++) {
    //                     // cout << "Run ThicknessCalc" << endl;
    //                     // ThicknessCalc(i, j, k);

    //                     InfluenceAreaCalc(i, j, k);
    //                 }
    //             }
    //         }

    // #pragma omp for private(j) private(k) schedule(static)
    //         for (i = 0; i < param->itr_max_x; i++) {
    //             for (j = 0; j < param->itr_max_y; j++) {
    //                 for (k = 0; k < param->itr_max_z; k++) {
    //                     // cout << "Run ForceCalc" << endl;
    //                     if (CubePressure) {
    //                         ForceCalc(i, j, k);
    //                     }
    //                     TensileForceCalc(i, j, k);
    //                     ShareForceCalc(i, j, k);
    //                     BendForceCalc(i, j, k);
    //                     AirForceCalc(i, j, k);
    //                 }
    //             }
    //         }
    //     }
    

    setInitialConditionsCopy();
    if (param->analysis_shape == "cylinder" ||
        param->analysis_shape == "cuboid") {
        setInitialConditionsSetParamShapeCylinder();
    }
    setInitialConditionsCopy();
}

// #if defined __SHAPE_CUBE__
/**
 * @brief	粒子のFlagを代入する
 * @note	3次元の立方体用のFlag
 */
void MultiParticle::setInitialConditionsSetFlagCube() {
    for (int i = 0; i < local_iNum; i++) {
        for (int j = 0; j < local_jNum; j++) {
            for (int k = 0; k < local_kNum; k++) {
                // どの面に所属するのか
                if (k == local_kNum - 1) {
                    // Ceiling
                    p->flag[i][j][k] |= BIT_CEILING;
                } else {
                    // Ceiling以外
                    if (j == local_jNum - 1) {
                        // Back
                        p->flag[i][j][k] |= BIT_BACK;
                    } else if (i == 0) {
                        // RightSide
                        p->flag[i][j][k] |= BIT_RIGHTSIDE;
                    }
                }

                if (!(p->flag[i][j][k] & BIT_CEILING ||
                      p->flag[i][j][k] & BIT_BACK ||
                      p->flag[i][j][k] & BIT_RIGHTSIDE)) {
                    p->flag[i][j][k] = BIT_NONE;
                }
                /////////////////////////////////////////////////////////////////////////
                // 面内での位置
                if (p->flag[i][j][k] & BIT_BACK) {
                    // Back
                    if (i == 0) {
                        p->flag[i][j][k] |= BIT_LEFT;
                    } else if (i == local_iNum - 1) {
                        p->flag[i][j][k] |= BIT_RIGHT;
                    }

                    if (k == 0) {
                        p->flag[i][j][k] |= BIT_BOTTOM;
                    } else if (k == local_kNum - 1) {
                        p->flag[i][j][k] |= BIT_TOP;
                    }
                } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
                    // RightSide
                    if (j == 0) {
                        p->flag[i][j][k] |= BIT_LEFT;
                    } else if (j == local_jNum - 1) {
                        p->flag[i][j][k] |= BIT_RIGHT;
                    }

                    if (k == 0) {
                        p->flag[i][j][k] |= BIT_BOTTOM;
                    } else if (k == local_kNum - 1) {
                        p->flag[i][j][k] |= BIT_TOP;
                    }
                } else if (p->flag[i][j][k] & BIT_CEILING) {
                    // Ceiling
                    if (j == 0) {
                        p->flag[i][j][k] |= BIT_LEFT;
                    } else if (j == local_jNum - 1) {
                        p->flag[i][j][k] |= BIT_RIGHT;
                    }

                    if (i == 0) {
                        p->flag[i][j][k] |= BIT_BOTTOM;
                    } else if (i == local_iNum - 1) {
                        p->flag[i][j][k] |= BIT_TOP;
                    }
                }
            }
        }
    }
}
// #else
/**
 * @brief	粒子のFlagを代入する
 */
void MultiParticle::setInitialConditionsSetFlag() {
    for (int k = 0; k < local_kNum; k++) {
        for (int j = 0; j < local_jNum; j++) {
            int global_j = responsible_range_start + j;
            for (int i = 0; i < local_iNum; i++) {
                if (i == 0) {
                    if (global_j == 0) {
                        p->flag[i][j][k] = LeftBottom;
                    } else if (global_j == param->m_jNum - 1) {
                        p->flag[i][j][k] = LeftTop;
                    } else {
                        p->flag[i][j][k] = Left;
                    }
                } else if (i == local_iNum - 1) {
                    if (global_j == 0) {
                        p->flag[i][j][k] = RightBottom;
                    } else if (global_j == param->m_jNum - 1) {
                        p->flag[i][j][k] = RightTop;
                    } else {
                        p->flag[i][j][k] = Right;
                    }
                } else {
                    if (global_j == 0) {
                        p->flag[i][j][k] = Bottom;
                    } else if (global_j == param->m_jNum - 1) {
                        p->flag[i][j][k] = Top;
                    } else {
                        p->flag[i][j][k] = Center;
                    }
                }
            }
        }
    }
    // p->surround_particle_exsit[i][j][k] |= BIT_NONE;
    for (size_t i = 0; i < p->surround_particle_exsit.size(); i++) {
        for (size_t j = 0; j < p->surround_particle_exsit[i].size(); j++) {
            for (size_t k = 0; k < p->surround_particle_exsit[i][j].size();
                 k++) {
                if (i != 0) {
                    p->surround_particle_exsit[i][j][k] |= BIT_LEFT;
                }
                if (i != p->surround_particle_exsit.size() - 1) {
                    p->surround_particle_exsit[i][j][k] |= BIT_RIGHT;
                }
                if (j != 0) {
                    p->surround_particle_exsit[i][j][k] |= BIT_BOTTOM;
                }
                if (j != p->surround_particle_exsit[i].size() - 1) {
                    p->surround_particle_exsit[i][j][k] |= BIT_TOP;
                }
            }
        }
    }
}
// #endif

/**
 * @brief	初期値が既知である値を代入する
 * @note Assumptions value
 */
void MultiParticle::setInitialConditionsSetParam() {
    for (int i = 0; i < local_iNum; i++) {
        for (int j = 0; j < local_jNum; j++) {
            for (int k = 0; k < local_kNum; k++) {
#ifndef __GEOMETRYDISTURBANCE__
                p->c[i][j][k].z       = 0;
#endif
                p->alphai[i][j][k]    = math::pi();
                p->alphaj[i][j][k]    = math::pi();
                p->etai[i][j][k]      = 0;
                p->etaj[i][j][k]      = 0;
                p->epsilonli[i][j][k] = 0;
                p->epsilonlj[i][j][k] = 0;
                p->hi[i][j][k]        = param->m_h0;
                p->hj[i][j][k]        = param->m_h0;
                p->v[i][j][k].x       = 0;
                p->v[i][j][k].y       = 0;
                p->v[i][j][k].z       = 0;
                p->Fti[i][j][k]       = 0;
                p->Ftj[i][j][k]       = 0;
                p->beta[i][j][k].pp   = math::pi() / 2;
                p->beta[i][j][k].pm   = math::pi() / 2;
                p->beta[i][j][k].mp   = math::pi() / 2;
                p->beta[i][j][k].mm   = math::pi() / 2;
            }
        }
    }
}

/**
 * @brief	形状がCylinderの場合の初期値を指定する
 * @note	Cylinder専用
 */
void MultiParticle::setInitialConditionsSetParamShapeCylinder() {
    for (int i = 0; i < local_iNum; i++) {
        for (int j = 0; j < local_jNum; j++) {
            for (int k = 0; k < local_kNum; k++) {
                VirtualParticleCalc(i, j, k);
            }
        }
    }
    for (int i = 0; i < local_iNum; i++) {
        for (int j = 0; j < local_jNum; j++) {
            for (int k = 0; k < local_kNum; k++) {
                ThicknessCalc(i, j, k);
            }
        }
    }
    for (int i = 0; i < local_iNum; i++) {
        for (int j = 0; j < local_jNum; j++) {
            for (int k = 0; k < local_kNum; k++) {
                ForceCalc(i, j, k);

                p->diff_etai[i][j][k] = 0;
                p->diff_etaj[i][j][k] = 0;
                p->epsilongi[i][j][k] = 0;
                p->epsilongj[i][j][k] = 0;
                p->epsilonli[i][j][k] = 0;
                p->epsilonlj[i][j][k] = 0;
                p->v[i][j][k].x       = 0;
                p->v[i][j][k].y       = 0;
                p->v[i][j][k].z       = 0;
                p->Fti[i][j][k]       = 0;
                p->Ftj[i][j][k]       = 0;

                if (!param->boundary.cylinder_boundary) {
                    p->omp[i][j][k].epsilonli = 0;
                    p->omp[i][j][k].epsilongj = 0;
                    p->omp[i][j][k].Fti       = 0;
                    p->epsilonli[i][j][k]     = 0;
                }
            }
        }
    }
}

/**
 * @brief	等間隔モデルの座標
 * @note
 * ここで、m_Lref_x(膜の長さ)を等分割で分割し、粒子に座標を設定している
 */
void MultiParticle::setInitialConditionsEquallyDividedModeling() {
    C distub;
    disturbance_Calc(distub, param->disturbance_range);
    for (int i = 0; i < local_iNum; i++) {
        for (int j = 0; j < local_jNum; j++) {
            for (int k = 0; k < local_kNum; k++) {
                p->c[i][j][k].x = param->m_Lref_x * i / (local_iNum - 1);
                p->c[i][j][k].y = param->m_Lref_y * j / (local_jNum - 1);
#ifdef __GEOMETRYDISTURBANCE__
            if (p->flag[i][j][k] == Center) {
                p->c[i][j][k].z = param->disturbance_range * get_random();
            }
                
                // cout << "z = "
                //      << p->c[i][j][k].z
                //      << endl;
#else
                // if (p->flag[i][j][k] == Right) {
                    if (param->add_disturbance) {
                        disturbance_Calc(p->disturbance[i][j][k], param->disturbance_range);
                        // p->disturbance[i][j][k] = distub;
                        if (param->disturbance_mode == "direct") {//ここのFdは、計算には用いていない
                            p->Fd[i][j][k] = normCalc(distub);
                        } else {
                            p->Fd[i][j][k] = innerProductCalc(p->disturbance[i][j][k],
                                                            p->S[i][j][k].cp.vector);
                        }
                    }
                // }
#endif
            }
        }
    }
}

/**
 * @brief	不等間隔モデル？の座標
 * @note
 * ここで、m_Lref_x(膜の長さ)を等分割で分割し、粒子に座標を設定している
 */
void MultiParticle::setInitialConditionsUnEquallyDividedModeling() {
    for (int i = 0; i < local_iNum; i++) {
        for (int j = 0; j < local_jNum; j++) {
            for (int k = 0; k < local_kNum; k++) {
                p->c[i][j][k].x = 0.5 * param->m_Lref_x *
                                  (1 - 1 * cos(math::pi() * i / (local_iNum - 1)));
                p->c[i][j][k].y = 0.5 * param->m_Lref_y *
                                  (1 - 1 * cos(math::pi() * j / (local_jNum - 1)));
            }
        }
    }
   
}

/**
 * @brief Diagonal Particle Model
 * @note
 *
 */
void MultiParticle::setInitialConditionsObliqueAlignmentModeling() {
    double diagonal_length     = sqrt(param->m_Lref_x * param->m_Lref_x +
                                      param->m_Lref_y * param->m_Lref_y);
    double div_diagonal_length = diagonal_length / local_iNum;
    double div_length_x        = div_diagonal_length * cos(math::pi() / 4);
    double div_length_y        = div_diagonal_length * sin(math::pi() / 4);

    if (param->m_Lref_x != param->m_Lref_y) {
        cout << "incorrect length" << endl;
        abort();
    }
    double length_one_side = param->m_Lref_x;
    for (int i = 0; i < local_iNum; i++) {
        for (int j = 0; j < local_jNum; j++) {
            for (int k = 0; k < local_kNum; k++) {
                if (i <= local_iNum / 2) {  // 粒子が左下か右下か
                    if (j < 2 * i + 1) {    // 粒子の配置範囲の指定
                        // p->c[i][j][k].x =
                        //     length_one_side * j / (local_iNum - 1);
                        // p->c[i][j][k].y =
                        //     length_one_side * j / (local_jNum - 1);
                        p->c[i][j][k].x = div_length_x * j;
                        p->c[i][j][k].y =
                            length_one_side -
                            (div_length_y * (local_iNum / 2 - 2 * i + j));
                    }
                } else {
                    if (j < 2 * (local_iNum - i) - 1) {
                        // p->c[i][j][k].x = length_one_side *
                        //                   (j + 2 * (i - local_iNum / 2)) /
                        //                   (local_iNum - 1);
                        // p->c[i][j][k].y = length_one_side *
                        //                   (local_iNum - (j + 1)) /
                        //                   (local_jNum - 1);

                        p->c[i][j][k].x =
                            2 * div_length_x * (i - local_iNum / 2) +
                            (div_length_x * j);
                        p->c[i][j][k].y = length_one_side - div_length_y * j;
                    }
                }
            }
        }
    }
}

// #ifdef __SHAPE_CYLINDER__
/**
 * @brief	1/4円筒の座標
 * @note
 * ここで、m_Lref_x(膜の長さ)を等分割で分割し、粒子に座標を設定している
 */
void MultiParticle::setInitialConditionsShapeCylinder() {
    double height = param->m_Lref_x;
    double radius = param->m_Lref_x / 2;
    double radian = 90 * math::pi() / 180;
    double z      = 0;

    // #ifdef __CYLINDER_BOUNDARY__
    if (param->boundary.cylinder_boundary) {
        // #ifdef __BOUNDARY_DETAILS__
        if (param->boundary.boundary_more_detail) {
            //! 高精度の部分の粒子間隔を求める
            double minuteness_radian =
                radian / ((local_iNum - 1) * param->minuteness);
            //! 粗精度の粒子間隔を求める
            double rough_radian =
                (radian - (minuteness_radian * 2 * (param->div_num - 1))) /
                ((local_iNum - 1) - ((param->div_num - 1) * 2));
            // cout << minuteness_radian << endl;
            // cout << rough_radian << endl;
            for (int k = 0; k < local_kNum; k++) {
                for (int j = 0; j < local_jNum;
                     j++, z += height / (local_jNum - 1)) {
                    double r = 0;
                    for (int i = 0; i < local_iNum; i++) {
                        if (i < param->div_num - 1 ||
                            i >= local_iNum - param->div_num) {
                            // cout << "i:" << i << " r:" << r << endl;
                            // cout << i << j << k << endl;
                            p->c[i][j][k].x = radius * std::cos(r);
                            p->c[i][j][k].y = radius * std::sin(r);
                            p->c[i][j][k].z = z;
                            r += minuteness_radian;
                        } else {
                            // cout << "i:" << i << " r:" << r << endl;
                            p->c[i][j][k].x = radius * std::cos(r);
                            p->c[i][j][k].y = radius * std::sin(r);
                            p->c[i][j][k].z = z;
                            r += rough_radian;
                        }
                    }
                }
            }

            // #else
        } else {
            for (int k = 0; k < local_kNum; k++) {
                for (int j = 0; j < local_jNum;
                     j++, z += height / (local_jNum - 1)) {
                    double r = 0;
                    for (int i = 0; i < local_iNum;
                         i++, r += radian / (local_iNum - 1)) {
                        // cout << i << j << k << endl;
                        p->c[i][j][k].x = radius * std::cos(r);
                        p->c[i][j][k].y = radius * std::sin(r);
                        p->c[i][j][k].z = z;
                    }
                }
            }
        }
        // #endif
    } else {
        // #ifdef __BOUNDARY_DETAILS__
        if (param->boundary.boundary_more_detail) {
            // #elif defined __CYLINDER_NON_BOUNDARY__  //
            // 円筒かつ境界面に粒子を配置しない
            //! 高精度の部分の粒子間隔を求める
            double minuteness_radian =
                radian / ((local_iNum - 1) * param->minuteness);
            //! 粗精度の粒子間隔を求める
            double rough_radian =
                (radian - (minuteness_radian * 2 * param->div_num)) /
                ((local_iNum - 1) - ((param->div_num * 2 - 1)));
            cout << minuteness_radian << endl;
            cout << rough_radian << endl;
            cout << z << endl;
            for (int k = 0; k < local_kNum; k++) {
                for (int j = 0; j < local_jNum;
                     j++, z += height / (local_jNum - 1)) {
                    // double r = 0;
                    double r = 0 + minuteness_radian / 2;
                    // for (int i = radian / (2 * local_iNum); i <
                    // local_iNum; i++, r += radian / local_iNum)
                    for (int i = 0; i < local_iNum; i++) {
                        if (i < param->div_num - 1 ||
                            i >= local_iNum - param->div_num - 1) {
                            // cout << "i:" << i << " r:" << r << endl;
                            // cout << i << j << k << endl;
                            p->c[i][j][k].x = radius * std::cos(r);
                            p->c[i][j][k].y = radius * std::sin(r);
                            p->c[i][j][k].z = z;
                            r += minuteness_radian;
                        } else {
                            // cout << "i:" << i << " r:" << r << endl;
                            p->c[i][j][k].x = radius * std::cos(r);
                            p->c[i][j][k].y = radius * std::sin(r);
                            p->c[i][j][k].z = z;
                            r += rough_radian;
                        }
                    }
                }
            }
            // #else
        } else {
            // cout << height << "," << radius << "," << radian << "," << endl;
            // // このif文内に入ったかの確認
            for (int k = 0; k < local_kNum; k++) {
                for (int j = 0; j < local_jNum;
                     j++, z += height / (local_jNum - 1)) {
                    double r = 0 + radian / (2 * local_iNum);
                    for (int i = radian / (2 * local_iNum); i < local_iNum;
                         i++, r += radian / local_iNum) {
                        // cout << i << j << k << endl;
                        p->c[i][j][k].x = radius * std::cos(r);
                        p->c[i][j][k].y = radius * std::sin(r);
                        p->c[i][j][k].z = z;
                    }
                }
            }
        }
        // #endif
    }

    // #endif
}
// #endif

// #if defined __SHAPE_CUBE__
/**
 * @brief	立方体の座標
 * @note
 * ここで、m_Lref_x(膜の長さ)を等分割で分割し、粒子に座標を設定している
 */
void MultiParticle::setInitialConditionsShapeCube() {
    double height = param->m_Lref_x / 2;
    // double width = param->m_Lref_x / 2;
    double length = param->m_Lref_x / 2;
    double w      = 0;
    double l      = 0;
    double h      = 0;

    // for (int i = 0; i < local_iNum; i++, w += width / (local_iNum -
    // 1))
    // {
    // for (int i = local_iNum - 1; 0 <= i; i--, w += width /
    // (local_iNum - 1))
    for (int i = local_iNum - 1; 0 <= i; i--, w += 0.025) {
        l = 0;
        for (int j = 0; j < local_jNum; j++, l += length / (local_jNum - 1)) {
            h = 0;
            for (int k = 0; k < local_kNum;
                 k++, h += height / (local_kNum - 1)) {
                // cout << i << j << k << endl;
                if (i == 0 || j == local_jNum - 1 || k == local_kNum - 1) {
                    p->c[i][j][k].x = w;
                    // p->c[i][j][k].x = width - w;
                    // if (i == local_iNum - 1)
                    // {
                    // 	p->c[i][j][k].x = 0;
                    // }
                    p->c[i][j][k].y = l;
                    p->c[i][j][k].z = h;
                }
            }
        }
    }
}
// #endif

/**
 * @brief	粒子間の距離 l を求める
 */
void MultiParticle::setInitialConditionsLCalc() {
    for (int i = 0; i < local_iNum; i++) {
        for (int j = 0; j < calc_jEnd; j++) {
            for (int k = 0; k < local_kNum; k++) {
                if (CubePressure) {
                    if (p->flag[i][j][k] & BIT_CEILING) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_CEILING):
                            case (BIT_CEILING | BIT_LEFT | BIT_BOTTOM):
                            case (BIT_CEILING | BIT_LEFT):
                            case (BIT_CEILING | BIT_BOTTOM):
                                lCalc(p->li[i][j][k], p->c[i][j][k],
                                      p->c[i][j + 1][k]);
                                lCalc(p->lj[i][j][k], p->c[i][j][k],
                                      p->c[i + 1][j][k]);
                                break;

                            case (BIT_CEILING | BIT_RIGHT):
                            case (BIT_CEILING | BIT_RIGHT | BIT_BOTTOM):
                                lCalc(p->lj[i][j][k], p->c[i][j][k],
                                      p->c[i + 1][j][k]);
                                break;

                            case (BIT_CEILING | BIT_TOP):
                            case (BIT_CEILING | BIT_LEFT | BIT_TOP):
                                lCalc(p->li[i][j][k], p->c[i][j][k],
                                      p->c[i][j + 1][k]);
                                break;

                            case (BIT_CEILING | BIT_RIGHT | BIT_TOP):
                                break;
                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    } else if (p->flag[i][j][k] & BIT_BACK) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_BACK):
                            case (BIT_BACK | BIT_LEFT | BIT_BOTTOM):
                            case (BIT_BACK | BIT_LEFT):
                            case (BIT_BACK | BIT_BOTTOM):
                                lCalc(p->li[i][j][k], p->c[i][j][k],
                                      p->c[i + 1][j][k]);
                                lCalc(p->lj[i][j][k], p->c[i][j][k],
                                      p->c[i][j][k + 1]);
                                break;

                            case (BIT_BACK | BIT_RIGHT):
                            case (BIT_BACK | BIT_RIGHT | BIT_BOTTOM):
                                lCalc(p->lj[i][j][k], p->c[i][j][k],
                                      p->c[i][j][k + 1]);
                                break;

                            case (BIT_BACK | BIT_TOP):
                            case (BIT_BACK | BIT_LEFT | BIT_TOP):
                                lCalc(p->li[i][j][k], p->c[i][j][k],
                                      p->c[i + 1][j][k]);
                                break;

                            case (BIT_BACK | BIT_RIGHT | BIT_TOP):
                                break;
                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_RIGHTSIDE):
                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_BOTTOM):
                            case (BIT_RIGHTSIDE | BIT_LEFT):
                            case (BIT_RIGHTSIDE | BIT_BOTTOM):
                                lCalc(p->li[i][j][k], p->c[i][j][k],
                                      p->c[i][j + 1][k]);
                                lCalc(p->lj[i][j][k], p->c[i][j][k],
                                      p->c[i][j][k + 1]);
                                break;

                            case (BIT_RIGHTSIDE | BIT_RIGHT):
                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_BOTTOM):
                                lCalc(p->lj[i][j][k], p->c[i][j][k],
                                      p->c[i][j][k + 1]);
                                break;

                            case (BIT_RIGHTSIDE | BIT_TOP):
                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_TOP):
                                lCalc(p->li[i][j][k], p->c[i][j][k],
                                      p->c[i][j + 1][k]);
                                break;

                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_TOP):
                                break;
                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    }
                } else if (!CubePressure) {
                    switch (p->flag[i][j][k]) {
                        case Center:
                        case LeftBottom:
                        case Left:
                        case Bottom:
                            lCalc(p->li[i][j][k], p->c[i][j][k],
                                  p->c[i + 1][j][k]);
                            lCalc(p->lj[i][j][k], p->c[i][j][k],
                                  p->c[i][j + 1][k]);
                            break;

                        case RightTop:
                            break;

                        case Right:
                        case RightBottom:
                            lCalc(p->lj[i][j][k], p->c[i][j][k],
                                  p->c[i][j + 1][k]);
                            break;

                        case Top:
                        case LeftTop:
                            lCalc(p->li[i][j][k], p->c[i][j][k],
                                  p->c[i + 1][j][k]);
                            break;
                        default:
                            console(4);
                            break;
                    }
                }
            }
        }
    }
}

/**
 * @brief	gを求める
 */
void MultiParticle::setInitialConditionsGCalc() {
    for (int i = 0; i < local_iNum; i++) {
        for (int j = 0; j < calc_jEnd; j++) {
            for (int k = 0; k < local_kNum; k++) {
                // cout << "Flag:" << std::bitset<8>(p->flag[i][j][k]) << ", i:"
                // << i << " j:" << j << " k:" << k << endl;
                if (CubePressure) {
                    if (p->flag[i][j][k] & BIT_CEILING) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_CEILING):
                            case (BIT_CEILING | BIT_LEFT | BIT_BOTTOM):
                            case (BIT_CEILING | BIT_LEFT):
                            case (BIT_CEILING | BIT_BOTTOM):
                                p->g[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x +
                                      p->c[i][j + 1][k].x +
                                      p->c[i + 1][j + 1][k].x) /
                                     4);
                                p->g[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y +
                                      p->c[i][j + 1][k].y +
                                      p->c[i + 1][j + 1][k].y) /
                                     4);
                                p->g[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z +
                                      p->c[i][j + 1][k].z +
                                      p->c[i + 1][j + 1][k].z) /
                                     4);
                                break;

                            case (BIT_CEILING | BIT_RIGHT):
                            case (BIT_CEILING | BIT_RIGHT | BIT_BOTTOM):
                                p->g[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) /
                                     2);
                                p->g[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) /
                                     2);
                                p->g[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) /
                                     2);
                                break;

                            case (BIT_CEILING | BIT_TOP):
                            case (BIT_CEILING | BIT_LEFT | BIT_TOP):
                                p->g[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) /
                                     2);
                                p->g[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) /
                                     2);
                                p->g[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) /
                                     2);
                                break;

                            case (BIT_CEILING | BIT_RIGHT | BIT_TOP):
                                p->g[i][j][k].x = p->c[i][j][k].x;
                                p->g[i][j][k].y = p->c[i][j][k].y;
                                p->g[i][j][k].z = p->c[i][j][k].z;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    } else if (p->flag[i][j][k] & BIT_BACK) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_BACK):
                            case (BIT_BACK | BIT_LEFT | BIT_BOTTOM):
                            case (BIT_BACK | BIT_LEFT):
                            case (BIT_BACK | BIT_BOTTOM):
                                p->g[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x +
                                      p->c[i][j][k].x + p->c[i][j][k + 1].x) /
                                     4);
                                p->g[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y +
                                      p->c[i][j][k].y + p->c[i][j][k + 1].y) /
                                     4);
                                p->g[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z +
                                      p->c[i][j][k].z + p->c[i][j][k + 1].z) /
                                     4);
                                break;

                            case (BIT_BACK | BIT_RIGHT):
                            case (BIT_BACK | BIT_RIGHT | BIT_BOTTOM):
                                p->g[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) /
                                     2);
                                p->g[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) /
                                     2);
                                p->g[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) /
                                     2);
                                break;

                            case (BIT_BACK | BIT_TOP):
                            case (BIT_BACK | BIT_LEFT | BIT_TOP):
                                p->g[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i][j][k].x) / 2);
                                p->g[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i][j][k].y) / 2);
                                p->g[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i][j][k].z) / 2);
                                break;

                            case (BIT_BACK | BIT_RIGHT | BIT_TOP):
                                p->g[i][j][k].x = p->c[i][j][k].x;
                                p->g[i][j][k].y = p->c[i][j][k].y;
                                p->g[i][j][k].z = p->c[i][j][k].z;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_RIGHTSIDE):
                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_BOTTOM):
                            case (BIT_RIGHTSIDE | BIT_LEFT):
                            case (BIT_RIGHTSIDE | BIT_BOTTOM):
                                p->g[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x +
                                      p->c[i][j + 1][k].x +
                                      p->c[i][j + 1][k + 1].x) /
                                     4);
                                p->g[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y +
                                      p->c[i][j + 1][k].y +
                                      p->c[i][j + 1][k + 1].y) /
                                     4);
                                p->g[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z +
                                      p->c[i][j + 1][k].z +
                                      p->c[i][j + 1][k + 1].z) /
                                     4);
                                break;

                            case (BIT_RIGHTSIDE | BIT_RIGHT):
                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_BOTTOM):
                                p->g[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) /
                                     2);
                                p->g[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) /
                                     2);
                                p->g[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) /
                                     2);
                                break;

                            case (BIT_RIGHTSIDE | BIT_TOP):
                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_TOP):
                                p->g[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) /
                                     2);
                                p->g[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) /
                                     2);
                                p->g[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) /
                                     2);
                                break;

                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_TOP):
                                p->g[i][j][k].x = p->c[i][j][k].x;
                                p->g[i][j][k].y = p->c[i][j][k].y;
                                p->g[i][j][k].z = p->c[i][j][k].z;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    }
                } else if (!CubePressure) {
                    switch (p->flag[i][j][k]) {
                        case Center:
                        case LeftBottom:
                        case Left:
                        case Bottom:
                            p->g[i][j][k].x =
                                ((p->c[i][j][k].x + p->c[i + 1][j][k].x +
                                  p->c[i][j + 1][k].x +
                                  p->c[i + 1][j + 1][k].x) /
                                 4);
                            p->g[i][j][k].y =
                                ((p->c[i][j][k].y + p->c[i + 1][j][k].y +
                                  p->c[i][j + 1][k].y +
                                  p->c[i + 1][j + 1][k].y) /
                                 4);
                            p->g[i][j][k].z =
                                ((p->c[i][j][k].z + p->c[i + 1][j][k].z +
                                  p->c[i][j + 1][k].z +
                                  p->c[i + 1][j + 1][k].z) /
                                 4);
                            break;

                        case RightTop:
                            p->g[i][j][k].x = p->c[i][j][k].x;
                            p->g[i][j][k].y = p->c[i][j][k].y;
                            p->g[i][j][k].z = p->c[i][j][k].z;
                            break;

                        case Right:
                        case RightBottom:
                            p->g[i][j][k].x =
                                ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                            p->g[i][j][k].y =
                                ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                            p->g[i][j][k].z =
                                ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                            break;

                        case Top:
                        case LeftTop:
                            p->g[i][j][k].x =
                                ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                            p->g[i][j][k].y =
                                ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                            p->g[i][j][k].z =
                                ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                            break;

                        default:
                            console(4);
                            break;
                    }
                }
            }
        }
    }
}

/**
 * @brief	M_iを求める
 */
void MultiParticle::setInitialConditionsMiCalc() {
    for (int i = 0; i < local_iNum; i++) {
        for (int j = 0; j < calc_jEnd; j++) {
            for (int k = 0; k < local_kNum; k++) {
                // cout << "Flag:" << std::bitset<8>(p->flag[i][j][k]) << ", i:"
                // << i << " j:" << j << " k:" << k << endl;
                if (CubePressure) {
                    if (p->flag[i][j][k] & BIT_CEILING) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_CEILING):
                            case (BIT_CEILING | BIT_LEFT | BIT_BOTTOM):
                            case (BIT_CEILING | BIT_LEFT):
                            case (BIT_CEILING | BIT_BOTTOM):
                            case (BIT_CEILING | BIT_TOP):
                            case (BIT_CEILING | BIT_LEFT | BIT_TOP):
                                p->mi[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) /
                                     2);
                                p->mi[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) /
                                     2);
                                p->mi[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) /
                                     2);
                                break;

                            case (BIT_CEILING | BIT_RIGHT):
                            case (BIT_CEILING | BIT_RIGHT | BIT_BOTTOM):
                            case (BIT_CEILING | BIT_RIGHT | BIT_TOP):
                                p->mi[i][j][k].x = 0;
                                p->mi[i][j][k].y = 0;
                                p->mi[i][j][k].z = 0;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    } else if (p->flag[i][j][k] & BIT_BACK) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_BACK):
                            case (BIT_BACK | BIT_LEFT | BIT_BOTTOM):
                            case (BIT_BACK | BIT_LEFT):
                            case (BIT_BACK | BIT_BOTTOM):
                            case (BIT_BACK | BIT_TOP):
                            case (BIT_BACK | BIT_LEFT | BIT_TOP):
                                p->mi[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) /
                                     2);
                                p->mi[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) /
                                     2);
                                p->mi[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) /
                                     2);
                                break;

                            case (BIT_BACK | BIT_RIGHT):
                            case (BIT_BACK | BIT_RIGHT | BIT_BOTTOM):
                            case (BIT_BACK | BIT_RIGHT | BIT_TOP):
                                p->mi[i][j][k].x = 0;
                                p->mi[i][j][k].y = 0;
                                p->mi[i][j][k].z = 0;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_RIGHTSIDE):
                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_BOTTOM):
                            case (BIT_RIGHTSIDE | BIT_LEFT):
                            case (BIT_RIGHTSIDE | BIT_BOTTOM):
                            case (BIT_RIGHTSIDE | BIT_TOP):
                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_TOP):
                                p->mi[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) /
                                     2);
                                p->mi[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) /
                                     2);
                                p->mi[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) /
                                     2);
                                break;

                            case (BIT_RIGHTSIDE | BIT_RIGHT):
                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_BOTTOM):
                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_TOP):
                                p->mi[i][j][k].x = 0;
                                p->mi[i][j][k].y = 0;
                                p->mi[i][j][k].z = 0;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    }
                }
                if (!CubePressure) {
                    switch (p->flag[i][j][k]) {
                        case Center:
                        case LeftBottom:
                        case Left:
                        case Bottom:
                            p->mi[i][j][k].x =
                                ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                            p->mi[i][j][k].y =
                                ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                            p->mi[i][j][k].z =
                                ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                            break;

                        case RightTop:
                            p->mi[i][j][k].x = 0;
                            p->mi[i][j][k].y = 0;
                            p->mi[i][j][k].z = 0;
                            break;

                        case Right:
                        case RightBottom:
                            p->mi[i][j][k].x = 0;
                            p->mi[i][j][k].y = 0;
                            p->mi[i][j][k].z = 0;
                            break;

                        case Top:
                        case LeftTop:
                            p->mi[i][j][k].x =
                                ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                            p->mi[i][j][k].y =
                                ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                            p->mi[i][j][k].z =
                                ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                            break;

                        default:
                            console(4);
                            break;
                    }
                }
            }
        }
    }
}

/**
 * @brief	M_jを求める
 */
void MultiParticle::setInitialConditionsMjCalc() {
    for (int i = 0; i < local_iNum; i++) {
        for (int j = 0; j < calc_jEnd; j++) {
            for (int k = 0; k < local_kNum; k++) {
                if (CubePressure) {
                    if (p->flag[i][j][k] & BIT_CEILING) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_CEILING):
                            case (BIT_CEILING | BIT_LEFT | BIT_BOTTOM):
                            case (BIT_CEILING | BIT_LEFT):
                            case (BIT_CEILING | BIT_BOTTOM):
                            case (BIT_CEILING | BIT_RIGHT):
                            case (BIT_CEILING | BIT_RIGHT | BIT_BOTTOM):
                                p->mj[i][j][k].x =
                                    ((p->c[i + 1][j][k].x + p->c[i][j][k].x) /
                                     2);
                                p->mj[i][j][k].y =
                                    ((p->c[i + 1][j][k].y + p->c[i][j][k].y) /
                                     2);
                                p->mj[i][j][k].z =
                                    ((p->c[i + 1][j][k].z + p->c[i][j][k].z) /
                                     2);
                                break;

                            case (BIT_CEILING | BIT_TOP):
                            case (BIT_CEILING | BIT_LEFT | BIT_TOP):
                            case (BIT_CEILING | BIT_RIGHT | BIT_TOP):
                                p->mj[i][j][k].x = 0;
                                p->mj[i][j][k].y = 0;
                                p->mj[i][j][k].z = 0;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    } else if (p->flag[i][j][k] & BIT_BACK) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_BACK):
                            case (BIT_BACK | BIT_LEFT | BIT_BOTTOM):
                            case (BIT_BACK | BIT_LEFT):
                            case (BIT_BACK | BIT_BOTTOM):
                            case (BIT_BACK | BIT_RIGHT):
                            case (BIT_BACK | BIT_RIGHT | BIT_BOTTOM):
                                p->mj[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) /
                                     2);
                                p->mj[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) /
                                     2);
                                p->mj[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) /
                                     2);
                                break;

                            case (BIT_BACK | BIT_TOP):
                            case (BIT_BACK | BIT_LEFT | BIT_TOP):
                            case (BIT_BACK | BIT_RIGHT | BIT_TOP):
                                p->mj[i][j][k].x = 0;
                                p->mj[i][j][k].y = 0;
                                p->mj[i][j][k].z = 0;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_RIGHTSIDE):
                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_BOTTOM):
                            case (BIT_RIGHTSIDE | BIT_LEFT):
                            case (BIT_RIGHTSIDE | BIT_BOTTOM):
                            case (BIT_RIGHTSIDE | BIT_RIGHT):
                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_BOTTOM):
                                p->mj[i][j][k].x =
                                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) /
                                     2);
                                p->mj[i][j][k].y =
                                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) /
                                     2);
                                p->mj[i][j][k].z =
                                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) /
                                     2);
                                break;

                            case (BIT_RIGHTSIDE | BIT_TOP):
                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_TOP):
                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_TOP):
                                p->mj[i][j][k].x = 0;
                                p->mj[i][j][k].y = 0;
                                p->mj[i][j][k].z = 0;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    }
                }
                if (!CubePressure) {
                    switch (p->flag[i][j][k]) {
                        case Center:
                        case LeftBottom:
                        case Left:
                        case Bottom:
                            p->mj[i][j][k].x =
                                ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                            p->mj[i][j][k].y =
                                ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                            p->mj[i][j][k].z =
                                ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                            break;

                        case RightTop:
                            p->mj[i][j][k].x = 0;
                            p->mj[i][j][k].y = 0;
                            p->mj[i][j][k].z = 0;
                            break;

                        case Right:
                        case RightBottom:
                            p->mj[i][j][k].x =
                                ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                            p->mj[i][j][k].y =
                                ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                            p->mj[i][j][k].z =
                                ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                            break;

                        case Top:
                        case LeftTop:
                            p->mj[i][j][k].x = 0;
                            p->mj[i][j][k].y = 0;
                            p->mj[i][j][k].z = 0;
                            break;

                        default:
                            console(4);
                            break;
                    }
                }
            }
        }
    }
}

/**
 * @brief	S_0を求める
 */
void MultiParticle::setInitialConditionsSCalc() {
    for (int i = 0; i < local_iNum; i++) {
        for (int j = calc_jStart; j < calc_jEnd; j++) {
            for (int k = 0; k < local_kNum; k++) {
                if (CubePressure) {
                    if (p->flag[i][j][k] & BIT_CEILING) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_CEILING):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i - 1][j][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i - 1][j][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i - 1][j][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;

                            case (BIT_CEILING | BIT_LEFT):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i - 1][j][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i - 1][j][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i - 1][j][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;

                            case (BIT_CEILING | BIT_RIGHT):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i - 1][j][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i - 1][j][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i - 1][j][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_CEILING | BIT_BOTTOM):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_CEILING | BIT_TOP):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i - 1][j][k].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i - 1][j][k].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i - 1][j][k].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_CEILING | BIT_LEFT | BIT_BOTTOM):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_CEILING | BIT_RIGHT | BIT_BOTTOM):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;

                            case (BIT_CEILING | BIT_LEFT | BIT_TOP):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i - 1][j][k].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i - 1][j][k].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i - 1][j][k].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_CEILING | BIT_RIGHT | BIT_TOP):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i - 1][j][k].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i - 1][j][k].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i - 1][j][k].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    } else if (p->flag[i][j][k] & BIT_BACK) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_BACK):
                                p->S[i][j][k].i.x =
                                    (p->li[i - 1][j][k].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].i.y =
                                    (p->li[i - 1][j][k].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].i.z =
                                    (p->li[i - 1][j][k].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;

                            case (BIT_BACK | BIT_LEFT):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;

                            case (BIT_BACK | BIT_RIGHT):
                                p->S[i][j][k].i.x =
                                    (p->li[i - 1][j][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i - 1][j][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i - 1][j][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_BACK | BIT_BOTTOM):
                                p->S[i][j][k].i.x =
                                    (p->li[i - 1][j][k].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].i.y =
                                    (p->li[i - 1][j][k].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].i.z =
                                    (p->li[i - 1][j][k].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_BACK | BIT_TOP):
                                p->S[i][j][k].i.x =
                                    (p->li[i - 1][j][k].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].i.y =
                                    (p->li[i - 1][j][k].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].i.z =
                                    (p->li[i - 1][j][k].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_BACK | BIT_LEFT | BIT_BOTTOM):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_BACK | BIT_RIGHT | BIT_BOTTOM):
                                p->S[i][j][k].i.x =
                                    (p->li[i - 1][j][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i - 1][j][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i - 1][j][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;

                            case (BIT_BACK | BIT_LEFT | BIT_TOP):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_BACK | BIT_RIGHT | BIT_TOP):
                                p->S[i][j][k].i.x =
                                    (p->li[i - 1][j][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i - 1][j][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i - 1][j][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_RIGHTSIDE):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;

                            case (BIT_RIGHTSIDE | BIT_LEFT):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;

                            case (BIT_RIGHTSIDE | BIT_RIGHT):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_RIGHTSIDE | BIT_BOTTOM):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_RIGHTSIDE | BIT_TOP):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_BOTTOM):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_BOTTOM):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;

                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_TOP):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;
                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_TOP):
                                p->S[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x) / 2;
                                p->S[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y) / 2;
                                p->S[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z) / 2;

                                p->S[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x) / 2;
                                p->S[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y) / 2;
                                p->S[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z) / 2;

                                crossProductCalc(p->S[i][j][k].cp.vector,
                                                 p->S[i][j][k].i,
                                                 p->S[i][j][k].j);
                                p->S[i][j][k].cp.norm =
                                    normCalc(p->S[i][j][k].cp.vector);
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                    }
                }
                if (!CubePressure) {
                    switch (p->flag[i][j][k]) {
                        case Center:
                            p->S[i][j][k].i.x = (p->li[i - 1][j][k].vector.x +
                                                 p->li[i][j][k].vector.x) /
                                                2;
                            p->S[i][j][k].i.y = (p->li[i - 1][j][k].vector.y +
                                                 p->li[i][j][k].vector.y) /
                                                2;
                            p->S[i][j][k].i.z = (p->li[i - 1][j][k].vector.z +
                                                 p->li[i][j][k].vector.z) /
                                                2;

                            p->S[i][j][k].j.x = (p->lj[i][j - 1][k].vector.x +
                                                 p->lj[i][j][k].vector.x) /
                                                2;
                            p->S[i][j][k].j.y = (p->lj[i][j - 1][k].vector.y +
                                                 p->lj[i][j][k].vector.y) /
                                                2;
                            p->S[i][j][k].j.z = (p->lj[i][j - 1][k].vector.z +
                                                 p->lj[i][j][k].vector.z) /
                                                2;

                            crossProductCalc(p->S[i][j][k].cp.vector,
                                             p->S[i][j][k].i, p->S[i][j][k].j);
                            p->S[i][j][k].cp.norm =
                                normCalc(p->S[i][j][k].cp.vector);
                            break;

                        case Left:
                            p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                            p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                            p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

                            p->S[i][j][k].j.x = (p->lj[i][j - 1][k].vector.x +
                                                 p->lj[i][j][k].vector.x) /
                                                2;
                            p->S[i][j][k].j.y = (p->lj[i][j - 1][k].vector.y +
                                                 p->lj[i][j][k].vector.y) /
                                                2;
                            p->S[i][j][k].j.z = (p->lj[i][j - 1][k].vector.z +
                                                 p->lj[i][j][k].vector.z) /
                                                2;

                            crossProductCalc(p->S[i][j][k].cp.vector,
                                             p->S[i][j][k].i, p->S[i][j][k].j);
                            p->S[i][j][k].cp.norm =
                                normCalc(p->S[i][j][k].cp.vector);
                            break;

                        case Bottom:
                            p->S[i][j][k].i.x = (p->li[i - 1][j][k].vector.x +
                                                 p->li[i][j][k].vector.x) /
                                                2;
                            p->S[i][j][k].i.y = (p->li[i - 1][j][k].vector.y +
                                                 p->li[i][j][k].vector.y) /
                                                2;
                            p->S[i][j][k].i.z = (p->li[i - 1][j][k].vector.z +
                                                 p->li[i][j][k].vector.z) /
                                                2;

                            p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                            p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                            p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

                            crossProductCalc(p->S[i][j][k].cp.vector,
                                             p->S[i][j][k].i, p->S[i][j][k].j);
                            p->S[i][j][k].cp.norm =
                                normCalc(p->S[i][j][k].cp.vector);
                            break;

                        case Right:
                            p->S[i][j][k].i.x =
                                (p->li[i - 1][j][k].vector.x) / 2;
                            p->S[i][j][k].i.y =
                                (p->li[i - 1][j][k].vector.y) / 2;
                            p->S[i][j][k].i.z =
                                (p->li[i - 1][j][k].vector.z) / 2;

                            p->S[i][j][k].j.x = (p->lj[i][j - 1][k].vector.x +
                                                 p->lj[i][j][k].vector.x) /
                                                2;
                            p->S[i][j][k].j.y = (p->lj[i][j - 1][k].vector.y +
                                                 p->lj[i][j][k].vector.y) /
                                                2;
                            p->S[i][j][k].j.z = (p->lj[i][j - 1][k].vector.z +
                                                 p->lj[i][j][k].vector.z) /
                                                2;

                            crossProductCalc(p->S[i][j][k].cp.vector,
                                             p->S[i][j][k].i, p->S[i][j][k].j);
                            p->S[i][j][k].cp.norm =
                                normCalc(p->S[i][j][k].cp.vector);
                            break;

                        case Top:

                            p->S[i][j][k].i.x = (p->li[i - 1][j][k].vector.x +
                                                 p->li[i][j][k].vector.x) /
                                                2;
                            p->S[i][j][k].i.y = (p->li[i - 1][j][k].vector.y +
                                                 p->li[i][j][k].vector.y) /
                                                2;
                            p->S[i][j][k].i.z = (p->li[i - 1][j][k].vector.z +
                                                 p->li[i][j][k].vector.z) /
                                                2;

                            p->S[i][j][k].j.x =
                                (p->lj[i][j - 1][k].vector.x) / 2;
                            p->S[i][j][k].j.y =
                                (p->lj[i][j - 1][k].vector.y) / 2;
                            p->S[i][j][k].j.z =
                                (p->lj[i][j - 1][k].vector.z) / 2;

                            crossProductCalc(p->S[i][j][k].cp.vector,
                                             p->S[i][j][k].i, p->S[i][j][k].j);
                            p->S[i][j][k].cp.norm =
                                normCalc(p->S[i][j][k].cp.vector);
                            break;

                        case LeftBottom:
                            p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                            p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                            p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

                            p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                            p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                            p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

                            crossProductCalc(p->S[i][j][k].cp.vector,
                                             p->S[i][j][k].i, p->S[i][j][k].j);
                            p->S[i][j][k].cp.norm =
                                normCalc(p->S[i][j][k].cp.vector);
                            break;

                        case RightBottom:
                            p->S[i][j][k].i.x =
                                (p->li[i - 1][j][k].vector.x) / 2;
                            p->S[i][j][k].i.y =
                                (p->li[i - 1][j][k].vector.y) / 2;
                            p->S[i][j][k].i.z =
                                (p->li[i - 1][j][k].vector.z) / 2;

                            p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                            p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                            p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

                            crossProductCalc(p->S[i][j][k].cp.vector,
                                             p->S[i][j][k].i, p->S[i][j][k].j);
                            p->S[i][j][k].cp.norm =
                                normCalc(p->S[i][j][k].cp.vector);
                            break;

                        case RightTop:
                            p->S[i][j][k].i.x =
                                (p->li[i - 1][j][k].vector.x) / 2;
                            p->S[i][j][k].i.y =
                                (p->li[i - 1][j][k].vector.y) / 2;
                            p->S[i][j][k].i.z =
                                (p->li[i - 1][j][k].vector.z) / 2;

                            p->S[i][j][k].j.x =
                                (p->lj[i][j - 1][k].vector.x) / 2;
                            p->S[i][j][k].j.y =
                                (p->lj[i][j - 1][k].vector.y) / 2;
                            p->S[i][j][k].j.z =
                                (p->lj[i][j - 1][k].vector.z) / 2;

                            crossProductCalc(p->S[i][j][k].cp.vector,
                                             p->S[i][j][k].i, p->S[i][j][k].j);
                            p->S[i][j][k].cp.norm =
                                normCalc(p->S[i][j][k].cp.vector);
                            break;

                        case LeftTop:
                            p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                            p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                            p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

                            p->S[i][j][k].j.x =
                                (p->lj[i][j - 1][k].vector.x) / 2;
                            p->S[i][j][k].j.y =
                                (p->lj[i][j - 1][k].vector.y) / 2;
                            p->S[i][j][k].j.z =
                                (p->lj[i][j - 1][k].vector.z) / 2;

                            crossProductCalc(p->S[i][j][k].cp.vector,
                                             p->S[i][j][k].i, p->S[i][j][k].j);
                            p->S[i][j][k].cp.norm =
                                normCalc(p->S[i][j][k].cp.vector);
                            break;

                        default:
                            console(4);
                            break;
                    }
                }
            }
        }
    }
}

/**
 * @brief	S_iを求める
 */
void MultiParticle::setInitialConditionsSiCalc() {
    for (int i = 0; i < local_iNum; i++) {
        for (int j = calc_jStart; j < calc_jEnd; j++) {
            for (int k = 0; k < local_kNum; k++) {
                if (CubePressure) {
                    if (p->flag[i][j][k] & BIT_CEILING) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_CEILING):
                                p->Si[i][j][k].i.x =
                                    (p->li[i + 1][j][k].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i - 1][j][k].vector.x) /
                                    4;
                                p->Si[i][j][k].i.y =
                                    (p->li[i + 1][j][k].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i - 1][j][k].vector.y) /
                                    4;
                                p->Si[i][j][k].i.z =
                                    (p->li[i + 1][j][k].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i - 1][j][k].vector.z) /
                                    4;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i - 1][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i - 1][j][k].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i - 1][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i - 1][j][k].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i - 1][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i - 1][j][k].vector.z) /
                                    4;
                                break;
                            case (BIT_CEILING | BIT_LEFT):
                                p->Si[i][j][k].i.x =
                                    (p->li[i + 1][j][k].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i - 1][j][k].vector.x) /
                                    4;
                                p->Si[i][j][k].i.y =
                                    (p->li[i + 1][j][k].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i - 1][j][k].vector.y) /
                                    4;
                                p->Si[i][j][k].i.z =
                                    (p->li[i + 1][j][k].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i - 1][j][k].vector.z) /
                                    4;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i - 1][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i - 1][j][k].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i - 1][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i - 1][j][k].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i - 1][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i - 1][j][k].vector.z) /
                                    4;
                                break;
                            case (BIT_CEILING | BIT_RIGHT):
                                p->Si[i][j][k].i.x = 0;
                                p->Si[i][j][k].i.y = 0;
                                p->Si[i][j][k].i.z = 0;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x +
                                     p->lj[i - 1][j][k].vector.x) /
                                    2;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y +
                                     p->lj[i - 1][j][k].vector.y) /
                                    2;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z +
                                     p->lj[i - 1][j][k].vector.z) /
                                    2;
                                break;
                            case (BIT_CEILING | BIT_BOTTOM):
                                p->Si[i][j][k].i.x =
                                    (p->li[i + 1][j][k].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->Si[i][j][k].i.y =
                                    (p->li[i + 1][j][k].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->Si[i][j][k].i.z =
                                    (p->li[i + 1][j][k].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    4;
                                break;
                            case (BIT_CEILING | BIT_TOP):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x +
                                     p->li[i - 1][j][k].vector.x) /
                                    2;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y +
                                     p->li[i - 1][j][k].vector.y) /
                                    2;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z +
                                     p->li[i - 1][j][k].vector.z) /
                                    2;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i - 1][j + 1][k].vector.x +
                                     p->lj[i - 1][j][k].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i - 1][j + 1][k].vector.y +
                                     p->lj[i - 1][j][k].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i - 1][j + 1][k].vector.z +
                                     p->lj[i - 1][j][k].vector.z) /
                                    4;
                                break;
                            case (BIT_CEILING | BIT_LEFT | BIT_BOTTOM):
                                p->Si[i][j][k].i.x =
                                    (p->li[i + 1][j][k].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->Si[i][j][k].i.y =
                                    (p->li[i + 1][j][k].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->Si[i][j][k].i.z =
                                    (p->li[i + 1][j][k].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    4;
                                break;
                            case (BIT_CEILING | BIT_RIGHT | BIT_BOTTOM):
                                p->Si[i][j][k].i.x = 0;
                                p->Si[i][j][k].i.y = 0;
                                p->Si[i][j][k].i.z = 0;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x) / 2;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y) / 2;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z) / 2;
                                break;

                            case (BIT_CEILING | BIT_LEFT | BIT_TOP):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x +
                                     p->li[i - 1][j][k].vector.x) /
                                    4;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y +
                                     p->li[i - 1][j][k].vector.y) /
                                    4;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z +
                                     p->li[i - 1][j][k].vector.z) /
                                    4;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i - 1][j + 1][k].vector.x +
                                     p->lj[i - 1][j][k].vector.x) /
                                    2;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i - 1][j + 1][k].vector.y +
                                     p->lj[i - 1][j][k].vector.y) /
                                    2;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i - 1][j + 1][k].vector.z +
                                     p->lj[i - 1][j][k].vector.z) /
                                    2;
                                break;

                            case (BIT_CEILING | BIT_RIGHT | BIT_TOP):
                                p->Si[i][j][k].i.x = 0;
                                p->Si[i][j][k].i.y = 0;
                                p->Si[i][j][k].i.z = 0;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i - 1][j][k].vector.x) / 2;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i - 1][j][k].vector.y) / 2;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i - 1][j][k].vector.z) / 2;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                        crossProductCalc(p->Si[i][j][k].cp.vector,
                                         p->Si[i][j][k].i, p->Si[i][j][k].j);
                        p->Si[i][j][k].cp.norm =
                            normCalc(p->Si[i][j][k].cp.vector);
                    } else if (p->flag[i][j][k] & BIT_BACK) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_BACK):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j][k - 1].vector.x) /
                                    4;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j][k - 1].vector.y) /
                                    4;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j][k - 1].vector.z) /
                                    4;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i + 1][j][k].vector.x +
                                     p->lj[i + 1][j][k - 1].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j][k - 1].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i + 1][j][k].vector.y +
                                     p->lj[i + 1][j][k - 1].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j][k - 1].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i + 1][j][k].vector.z +
                                     p->lj[i + 1][j][k - 1].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j][k - 1].vector.z) /
                                    4;
                                break;
                            case (BIT_BACK | BIT_LEFT):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j][k - 1].vector.x) /
                                    4;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j][k - 1].vector.y) /
                                    4;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j][k - 1].vector.z) /
                                    4;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i + 1][j][k].vector.x +
                                     p->lj[i + 1][j][k - 1].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j][k - 1].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i + 1][j][k].vector.y +
                                     p->lj[i + 1][j][k - 1].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j][k - 1].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i + 1][j][k].vector.z +
                                     p->lj[i + 1][j][k - 1].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j][k - 1].vector.z) /
                                    4;
                                break;
                            case (BIT_BACK | BIT_RIGHT):
                                p->Si[i][j][k].i.x = 0;
                                p->Si[i][j][k].i.y = 0;
                                p->Si[i][j][k].i.z = 0;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x +
                                     p->lj[i][j][k - 1].vector.x) /
                                    2;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y +
                                     p->lj[i][j][k - 1].vector.y) /
                                    2;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z +
                                     p->lj[i][j][k - 1].vector.z) /
                                    2;
                                break;
                            case (BIT_BACK | BIT_BOTTOM):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i + 1][j][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i + 1][j][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i + 1][j][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    4;
                                break;
                            case (BIT_BACK | BIT_TOP):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x +
                                     p->li[i][j][k - 1].vector.x) /
                                    2;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y +
                                     p->li[i][j][k - 1].vector.y) /
                                    2;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z +
                                     p->li[i][j][k - 1].vector.z) /
                                    2;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i + 1][j][k - 1].vector.x +
                                     p->lj[i][j][k - 1].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i + 1][j][k - 1].vector.y +
                                     p->lj[i][j][k - 1].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i + 1][j][k - 1].vector.z +
                                     p->lj[i][j][k - 1].vector.z) /
                                    4;
                                break;
                            case (BIT_BACK | BIT_LEFT | BIT_BOTTOM):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i + 1][j][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i + 1][j][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i + 1][j][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    4;
                                break;
                            case (BIT_BACK | BIT_RIGHT | BIT_BOTTOM):
                                p->Si[i][j][k].i.x = 0;
                                p->Si[i][j][k].i.y = 0;
                                p->Si[i][j][k].i.z = 0;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x) / 2;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y) / 2;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z) / 2;
                                break;

                            case (BIT_BACK | BIT_LEFT | BIT_TOP):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x +
                                     p->li[i][j][k - 1].vector.x) /
                                    4;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y +
                                     p->li[i][j][k - 1].vector.y) /
                                    4;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z +
                                     p->li[i][j][k - 1].vector.z) /
                                    4;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i + 1][j][k - 1].vector.x +
                                     p->lj[i][j][k - 1].vector.x) /
                                    2;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i + 1][j][k - 1].vector.y +
                                     p->lj[i][j][k - 1].vector.y) /
                                    2;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i + 1][j][k - 1].vector.z +
                                     p->lj[i][j][k - 1].vector.z) /
                                    2;
                                break;

                            case (BIT_BACK | BIT_RIGHT | BIT_TOP):
                                p->Si[i][j][k].i.x = 0;
                                p->Si[i][j][k].i.y = 0;
                                p->Si[i][j][k].i.z = 0;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x) / 2;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y) / 2;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z) / 2;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                        crossProductCalc(p->Si[i][j][k].cp.vector,
                                         p->Si[i][j][k].i, p->Si[i][j][k].j);
                        p->Si[i][j][k].cp.norm =
                            normCalc(p->Si[i][j][k].cp.vector);
                    } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_RIGHTSIDE):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j][k - 1].vector.x) /
                                    4;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j][k - 1].vector.y) /
                                    4;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j][k - 1].vector.z) /
                                    4;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j + 1][k - 1].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j][k - 1].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j + 1][k - 1].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j][k - 1].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j + 1][k - 1].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j][k - 1].vector.z) /
                                    4;
                                break;
                            case (BIT_RIGHTSIDE | BIT_LEFT):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j][k - 1].vector.x) /
                                    4;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j][k - 1].vector.y) /
                                    4;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j][k - 1].vector.z) /
                                    4;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j + 1][k - 1].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j][k - 1].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j + 1][k - 1].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j][k - 1].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j + 1][k - 1].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j][k - 1].vector.z) /
                                    4;
                                break;
                            case (BIT_RIGHTSIDE | BIT_RIGHT):
                                p->Si[i][j][k].i.x = 0;
                                p->Si[i][j][k].i.y = 0;
                                p->Si[i][j][k].i.z = 0;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x +
                                     p->lj[i][j][k - 1].vector.x) /
                                    2;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y +
                                     p->lj[i][j][k - 1].vector.y) /
                                    2;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z +
                                     p->lj[i][j][k - 1].vector.z) /
                                    2;
                                break;
                            case (BIT_RIGHTSIDE | BIT_BOTTOM):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    4;
                                break;
                            case (BIT_RIGHTSIDE | BIT_TOP):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x +
                                     p->li[i][j][k - 1].vector.x) /
                                    2;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y +
                                     p->li[i][j][k - 1].vector.y) /
                                    2;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z +
                                     p->li[i][j][k - 1].vector.z) /
                                    2;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j + 1][k - 1].vector.x +
                                     p->lj[i][j][k - 1].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j + 1][k - 1].vector.y +
                                     p->lj[i][j][k - 1].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j + 1][k - 1].vector.z +
                                     p->lj[i][j][k - 1].vector.z) /
                                    4;
                                break;
                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_BOTTOM):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    2;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    2;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    2;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    4;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    4;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    4;
                                break;
                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_BOTTOM):
                                p->Si[i][j][k].i.x = 0;
                                p->Si[i][j][k].i.y = 0;
                                p->Si[i][j][k].i.z = 0;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x) / 2;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y) / 2;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z) / 2;
                                break;

                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_TOP):
                                p->Si[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x +
                                     p->li[i][j][k - 1].vector.x) /
                                    4;
                                p->Si[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y +
                                     p->li[i][j][k - 1].vector.y) /
                                    4;
                                p->Si[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z +
                                     p->li[i][j][k - 1].vector.z) /
                                    4;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j + 1][k - 1].vector.x +
                                     p->lj[i][j][k - 1].vector.x) /
                                    2;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j + 1][k - 1].vector.y +
                                     p->lj[i][j][k - 1].vector.y) /
                                    2;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j + 1][k - 1].vector.z +
                                     p->lj[i][j][k - 1].vector.z) /
                                    2;
                                break;

                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_TOP):
                                p->Si[i][j][k].i.x = 0;
                                p->Si[i][j][k].i.y = 0;
                                p->Si[i][j][k].i.z = 0;

                                p->Si[i][j][k].j.x =
                                    (p->lj[i][j][k - 1].vector.x) / 2;
                                p->Si[i][j][k].j.y =
                                    (p->lj[i][j][k - 1].vector.y) / 2;
                                p->Si[i][j][k].j.z =
                                    (p->lj[i][j][k - 1].vector.z) / 2;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }
                        crossProductCalc(p->Si[i][j][k].cp.vector,
                                         p->Si[i][j][k].i, p->Si[i][j][k].j);
                        p->Si[i][j][k].cp.norm =
                            normCalc(p->Si[i][j][k].cp.vector);
                    }
                }
                if (!CubePressure) {
                    switch (p->flag[i][j][k]) {
                        case Center:
                            p->Si[i][j][k].i.x = (p->li[i][j + 1][k].vector.x +
                                                  p->li[i][j][k].vector.x +
                                                  p->li[i][j][k].vector.x +
                                                  p->li[i][j - 1][k].vector.x) /
                                                 4;
                            p->Si[i][j][k].i.y = (p->li[i][j + 1][k].vector.y +
                                                  p->li[i][j][k].vector.y +
                                                  p->li[i][j][k].vector.y +
                                                  p->li[i][j - 1][k].vector.y) /
                                                 4;
                            p->Si[i][j][k].i.z = (p->li[i][j + 1][k].vector.z +
                                                  p->li[i][j][k].vector.z +
                                                  p->li[i][j][k].vector.z +
                                                  p->li[i][j - 1][k].vector.z) /
                                                 4;

                            p->Si[i][j][k].j.x =
                                (p->lj[i + 1][j][k].vector.x +
                                 p->lj[i + 1][j - 1][k].vector.x +
                                 p->lj[i][j][k].vector.x +
                                 p->lj[i][j - 1][k].vector.x) /
                                4;
                            p->Si[i][j][k].j.y =
                                (p->lj[i + 1][j][k].vector.y +
                                 p->lj[i + 1][j - 1][k].vector.y +
                                 p->lj[i][j][k].vector.y +
                                 p->lj[i][j - 1][k].vector.y) /
                                4;
                            p->Si[i][j][k].j.z =
                                (p->lj[i + 1][j][k].vector.z +
                                 p->lj[i + 1][j - 1][k].vector.z +
                                 p->lj[i][j][k].vector.z +
                                 p->lj[i][j - 1][k].vector.z) /
                                4;
                            break;

                        case Left:
                            p->Si[i][j][k].i.x = (p->li[i][j + 1][k].vector.x +
                                                  p->li[i][j][k].vector.x +
                                                  p->li[i][j][k].vector.x +
                                                  p->li[i][j - 1][k].vector.x) /
                                                 4;
                            p->Si[i][j][k].i.y = (p->li[i][j + 1][k].vector.y +
                                                  p->li[i][j][k].vector.y +
                                                  p->li[i][j][k].vector.y +
                                                  p->li[i][j - 1][k].vector.y) /
                                                 4;
                            p->Si[i][j][k].i.z = (p->li[i][j + 1][k].vector.z +
                                                  p->li[i][j][k].vector.z +
                                                  p->li[i][j][k].vector.z +
                                                  p->li[i][j - 1][k].vector.z) /
                                                 4;

                            p->Si[i][j][k].j.x =
                                (p->lj[i + 1][j][k].vector.x +
                                 p->lj[i + 1][j - 1][k].vector.x +
                                 p->lj[i][j][k].vector.x +
                                 p->lj[i][j - 1][k].vector.x) /
                                4;
                            p->Si[i][j][k].j.y =
                                (p->lj[i + 1][j][k].vector.y +
                                 p->lj[i + 1][j - 1][k].vector.y +
                                 p->lj[i][j][k].vector.y +
                                 p->lj[i][j - 1][k].vector.y) /
                                4;
                            p->Si[i][j][k].j.z =
                                (p->lj[i + 1][j][k].vector.z +
                                 p->lj[i + 1][j - 1][k].vector.z +
                                 p->lj[i][j][k].vector.z +
                                 p->lj[i][j - 1][k].vector.z) /
                                4;
                            break;

                        case Bottom:
                            p->Si[i][j][k].i.x = (p->li[i][j + 1][k].vector.x +
                                                  p->li[i][j][k].vector.x) /
                                                 2;
                            p->Si[i][j][k].i.y = (p->li[i][j + 1][k].vector.y +
                                                  p->li[i][j][k].vector.y) /
                                                 2;
                            p->Si[i][j][k].i.z = (p->li[i][j + 1][k].vector.z +
                                                  p->li[i][j][k].vector.z) /
                                                 2;

                            p->Si[i][j][k].j.x = (p->lj[i + 1][j][k].vector.x +
                                                  p->lj[i][j][k].vector.x) /
                                                 4;
                            p->Si[i][j][k].j.y = (p->lj[i + 1][j][k].vector.y +
                                                  p->lj[i][j][k].vector.y) /
                                                 4;
                            p->Si[i][j][k].j.z = (p->lj[i + 1][j][k].vector.z +
                                                  p->lj[i][j][k].vector.z) /
                                                 4;
                            break;

                        case Right:
                            p->Si[i][j][k].i.x = 0;
                            p->Si[i][j][k].i.y = 0;
                            p->Si[i][j][k].i.z = 0;

                            p->Si[i][j][k].j.x = (p->lj[i][j][k].vector.x +
                                                  p->lj[i][j - 1][k].vector.x) /
                                                 2;
                            p->Si[i][j][k].j.y = (p->lj[i][j][k].vector.y +
                                                  p->lj[i][j - 1][k].vector.y) /
                                                 2;
                            p->Si[i][j][k].j.z = (p->lj[i][j][k].vector.z +
                                                  p->lj[i][j - 1][k].vector.z) /
                                                 2;
                            break;

                        case Top:
                            p->Si[i][j][k].i.x = (p->li[i][j][k].vector.x +
                                                  p->li[i][j - 1][k].vector.x) /
                                                 2;
                            p->Si[i][j][k].i.y = (p->li[i][j][k].vector.y +
                                                  p->li[i][j - 1][k].vector.y) /
                                                 2;
                            p->Si[i][j][k].i.z = (p->li[i][j][k].vector.z +
                                                  p->li[i][j - 1][k].vector.z) /
                                                 2;

                            p->Si[i][j][k].j.x =
                                (p->lj[i + 1][j - 1][k].vector.x +
                                 p->lj[i][j - 1][k].vector.x) /
                                4;
                            p->Si[i][j][k].j.y =
                                (p->lj[i + 1][j - 1][k].vector.y +
                                 p->lj[i][j - 1][k].vector.y) /
                                4;
                            p->Si[i][j][k].j.z =
                                (p->lj[i + 1][j - 1][k].vector.z +
                                 p->lj[i][j - 1][k].vector.z) /
                                4;
                            break;

                        case LeftBottom:
                            p->Si[i][j][k].i.x = (p->li[i][j + 1][k].vector.x +
                                                  p->li[i][j][k].vector.x) /
                                                 2;
                            p->Si[i][j][k].i.y = (p->li[i][j + 1][k].vector.y +
                                                  p->li[i][j][k].vector.y) /
                                                 2;
                            p->Si[i][j][k].i.z = (p->li[i][j + 1][k].vector.z +
                                                  p->li[i][j][k].vector.z) /
                                                 2;

                            p->Si[i][j][k].j.x = (p->lj[i + 1][j][k].vector.x +
                                                  p->lj[i][j][k].vector.x) /
                                                 4;
                            p->Si[i][j][k].j.y = (p->lj[i + 1][j][k].vector.y +
                                                  p->lj[i][j][k].vector.y) /
                                                 4;
                            p->Si[i][j][k].j.z = (p->lj[i + 1][j][k].vector.z +
                                                  p->lj[i][j][k].vector.z) /
                                                 4;
                            break;

                        case RightBottom:
                            p->Si[i][j][k].i.x = 0;
                            p->Si[i][j][k].i.y = 0;
                            p->Si[i][j][k].i.z = 0;

                            p->Si[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                            p->Si[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                            p->Si[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;
                            break;

                        case RightTop:
                            p->Si[i][j][k].i.x = 0;
                            p->Si[i][j][k].i.y = 0;
                            p->Si[i][j][k].i.z = 0;

                            p->Si[i][j][k].j.x =
                                (p->lj[i][j - 1][k].vector.x) / 2;
                            p->Si[i][j][k].j.y =
                                (p->lj[i][j - 1][k].vector.y) / 2;
                            p->Si[i][j][k].j.z =
                                (p->lj[i][j - 1][k].vector.z) / 2;
                            break;

                        case LeftTop:
                            p->Si[i][j][k].i.x = (p->li[i][j][k].vector.x +
                                                  p->li[i][j - 1][k].vector.x) /
                                                 4;
                            p->Si[i][j][k].i.y = (p->li[i][j][k].vector.y +
                                                  p->li[i][j - 1][k].vector.y) /
                                                 4;
                            p->Si[i][j][k].i.z = (p->li[i][j][k].vector.z +
                                                  p->li[i][j - 1][k].vector.z) /
                                                 4;

                            p->Si[i][j][k].j.x =
                                (p->lj[i + 1][j - 1][k].vector.x +
                                 p->lj[i][j - 1][k].vector.x) /
                                2;
                            p->Si[i][j][k].j.y =
                                (p->lj[i + 1][j - 1][k].vector.y +
                                 p->lj[i][j - 1][k].vector.y) /
                                2;
                            p->Si[i][j][k].j.z =
                                (p->lj[i + 1][j - 1][k].vector.z +
                                 p->lj[i][j - 1][k].vector.z) /
                                2;
                            break;

                        default:
                            console(4);
                            break;
                    }

                    crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                     p->Si[i][j][k].j);
                    p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);
                }
            }
        }
    }
}

/**
 * @brief	S_jを求める
 */
void MultiParticle::setInitialConditionsSjCalc() {
    for (int i = 0; i < local_iNum; i++) {
        for (int j = calc_jStart; j < calc_jEnd; j++) {
            for (int k = 0; k < local_kNum; k++) {
                if (CubePressure) {
                    if (p->flag[i][j][k] & BIT_CEILING) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_CEILING):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i + 1][j][k].vector.x +
                                     p->li[i + 1][j - 1][k].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j - 1][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i + 1][j][k].vector.y +
                                     p->li[i + 1][j - 1][k].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j - 1][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i + 1][j][k].vector.z +
                                     p->li[i + 1][j - 1][k].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j - 1][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j - 1][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j - 1][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j - 1][k].vector.z) /
                                    4;
                                break;

                            case (BIT_CEILING | BIT_LEFT):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i + 1][j][k].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i + 1][j][k].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i + 1][j][k].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;
                                break;

                            case (BIT_CEILING | BIT_BOTTOM):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i + 1][j][k].vector.x +
                                     p->li[i + 1][j - 1][k].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j - 1][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i + 1][j][k].vector.y +
                                     p->li[i + 1][j - 1][k].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j - 1][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i + 1][j][k].vector.z +
                                     p->li[i + 1][j - 1][k].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j - 1][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j - 1][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j - 1][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j - 1][k].vector.z) /
                                    4;
                                break;

                            case (BIT_CEILING | BIT_RIGHT):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i + 1][j - 1][k].vector.x +
                                     p->li[i][j - 1][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i + 1][j - 1][k].vector.y +
                                     p->li[i][j - 1][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i + 1][j - 1][k].vector.z +
                                     p->li[i][j - 1][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x +
                                     p->lj[i][j - 1][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y +
                                     p->lj[i][j - 1][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z +
                                     p->lj[i][j - 1][k].vector.z) /
                                    2;
                                break;

                            case (BIT_CEILING | BIT_LEFT | BIT_BOTTOM):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i + 1][j][k].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i + 1][j][k].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i + 1][j][k].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;
                                break;

                            case (BIT_CEILING | BIT_RIGHT | BIT_BOTTOM):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i + 1][j - 1][k].vector.x +
                                     p->li[i][j - 1][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i + 1][j - 1][k].vector.y +
                                     p->li[i][j - 1][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i + 1][j - 1][k].vector.z +
                                     p->li[i][j - 1][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x +
                                     p->lj[i][j - 1][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y +
                                     p->lj[i][j - 1][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z +
                                     p->lj[i][j - 1][k].vector.z) /
                                    2;
                                break;

                            case (BIT_CEILING | BIT_TOP):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x +
                                     p->li[i][j - 1][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y +
                                     p->li[i][j - 1][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z +
                                     p->li[i][j - 1][k].vector.z) /
                                    2;

                                p->Sj[i][j][k].j.x = 0;
                                p->Sj[i][j][k].j.y = 0;
                                p->Sj[i][j][k].j.z = 0;
                                break;

                            case (BIT_CEILING | BIT_RIGHT | BIT_TOP):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x) / 2;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y) / 2;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z) / 2;

                                p->Sj[i][j][k].j.x = 0;
                                p->Sj[i][j][k].j.y = 0;
                                p->Sj[i][j][k].j.z = 0;
                                break;

                            case (BIT_CEILING | BIT_LEFT | BIT_TOP):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x) / 2;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y) / 2;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z) / 2;

                                p->Sj[i][j][k].j.x = 0;
                                p->Sj[i][j][k].j.y = 0;
                                p->Sj[i][j][k].j.z = 0;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }

                        crossProductCalc(p->Sj[i][j][k].cp.vector,
                                         p->Sj[i][j][k].i, p->Sj[i][j][k].j);
                        p->Sj[i][j][k].cp.norm =
                            normCalc(p->Sj[i][j][k].cp.vector);
                    } else if (p->flag[i][j][k] & BIT_BACK) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_BACK):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i - 1][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i - 1][j][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i - 1][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i - 1][j][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i - 1][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i - 1][j][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i + 1][j][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i - 1][j][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i + 1][j][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i - 1][j][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i + 1][j][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i - 1][j][k].vector.z) /
                                    4;
                                break;

                            case (BIT_BACK | BIT_LEFT):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i + 1][j][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i + 1][j][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i + 1][j][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;
                                break;

                            case (BIT_BACK | BIT_BOTTOM):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i - 1][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i - 1][j][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i - 1][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i - 1][j][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i - 1][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i - 1][j][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i + 1][j][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i - 1][j][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i + 1][j][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i - 1][j][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i + 1][j][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i - 1][j][k].vector.z) /
                                    4;
                                break;

                            case (BIT_BACK | BIT_RIGHT):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i - 1][j][k + 1].vector.x +
                                     p->li[i - 1][j][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i - 1][j][k + 1].vector.y +
                                     p->li[i - 1][j][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i - 1][j][k + 1].vector.z +
                                     p->li[i - 1][j][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x +
                                     p->lj[i - 1][j][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y +
                                     p->lj[i - 1][j][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z +
                                     p->lj[i - 1][j][k].vector.z) /
                                    2;
                                break;

                            case (BIT_BACK | BIT_LEFT | BIT_BOTTOM):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i + 1][j][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i + 1][j][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i + 1][j][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;
                                break;

                            case (BIT_BACK | BIT_RIGHT | BIT_BOTTOM):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i - 1][j][k + 1].vector.x +
                                     p->li[i - 1][j][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i - 1][j][k + 1].vector.y +
                                     p->li[i - 1][j][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i - 1][j][k + 1].vector.z +
                                     p->li[i - 1][j][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x +
                                     p->lj[i - 1][j][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y +
                                     p->lj[i - 1][j][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z +
                                     p->lj[i - 1][j][k].vector.z) /
                                    2;
                                break;

                            case (BIT_BACK | BIT_TOP):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x +
                                     p->li[i - 1][j][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y +
                                     p->li[i - 1][j][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z +
                                     p->li[i - 1][j][k].vector.z) /
                                    2;

                                p->Sj[i][j][k].j.x = 0;
                                p->Sj[i][j][k].j.y = 0;
                                p->Sj[i][j][k].j.z = 0;
                                break;

                            case (BIT_BACK | BIT_RIGHT | BIT_TOP):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i - 1][j][k].vector.x) / 2;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i - 1][j][k].vector.y) / 2;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i - 1][j][k].vector.z) / 2;

                                p->Sj[i][j][k].j.x = 0;
                                p->Sj[i][j][k].j.y = 0;
                                p->Sj[i][j][k].j.z = 0;
                                break;

                            case (BIT_BACK | BIT_LEFT | BIT_TOP):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x) / 2;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y) / 2;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z) / 2;

                                p->Sj[i][j][k].j.x = 0;
                                p->Sj[i][j][k].j.y = 0;
                                p->Sj[i][j][k].j.z = 0;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }

                        crossProductCalc(p->Sj[i][j][k].cp.vector,
                                         p->Sj[i][j][k].i, p->Sj[i][j][k].j);
                        p->Sj[i][j][k].cp.norm =
                            normCalc(p->Sj[i][j][k].cp.vector);
                    } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
                        switch (p->flag[i][j][k]) {
                            case (BIT_RIGHTSIDE):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j - 1][k + 1].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j - 1][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j - 1][k + 1].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j - 1][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j - 1][k + 1].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j - 1][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j - 1][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j - 1][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j - 1][k].vector.z) /
                                    4;
                                break;

                            case (BIT_RIGHTSIDE | BIT_LEFT):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;
                                break;

                            case (BIT_RIGHTSIDE | BIT_BOTTOM):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j - 1][k + 1].vector.x +
                                     p->li[i][j][k].vector.x +
                                     p->li[i][j - 1][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j - 1][k + 1].vector.y +
                                     p->li[i][j][k].vector.y +
                                     p->li[i][j - 1][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j - 1][k + 1].vector.z +
                                     p->li[i][j][k].vector.z +
                                     p->li[i][j - 1][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j][k].vector.x +
                                     p->lj[i][j - 1][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j][k].vector.y +
                                     p->lj[i][j - 1][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j][k].vector.z +
                                     p->lj[i][j - 1][k].vector.z) /
                                    4;
                                break;

                            case (BIT_RIGHTSIDE | BIT_RIGHT):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j - 1][k + 1].vector.x +
                                     p->li[i][j - 1][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j - 1][k + 1].vector.y +
                                     p->li[i][j - 1][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j - 1][k + 1].vector.z +
                                     p->li[i][j - 1][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x +
                                     p->lj[i][j - 1][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y +
                                     p->lj[i][j - 1][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z +
                                     p->lj[i][j - 1][k].vector.z) /
                                    2;
                                break;

                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_BOTTOM):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k + 1].vector.x +
                                     p->li[i][j][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k + 1].vector.y +
                                     p->li[i][j][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k + 1].vector.z +
                                     p->li[i][j][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j + 1][k].vector.x +
                                     p->lj[i][j][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j + 1][k].vector.y +
                                     p->lj[i][j][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j + 1][k].vector.z +
                                     p->lj[i][j][k].vector.z) /
                                    2;
                                break;

                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_BOTTOM):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j - 1][k + 1].vector.x +
                                     p->li[i][j - 1][k].vector.x) /
                                    4;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j - 1][k + 1].vector.y +
                                     p->li[i][j - 1][k].vector.y) /
                                    4;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j - 1][k + 1].vector.z +
                                     p->li[i][j - 1][k].vector.z) /
                                    4;

                                p->Sj[i][j][k].j.x =
                                    (p->lj[i][j][k].vector.x +
                                     p->lj[i][j - 1][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].j.y =
                                    (p->lj[i][j][k].vector.y +
                                     p->lj[i][j - 1][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].j.z =
                                    (p->lj[i][j][k].vector.z +
                                     p->lj[i][j - 1][k].vector.z) /
                                    2;
                                break;

                            case (BIT_RIGHTSIDE | BIT_TOP):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x +
                                     p->li[i][j - 1][k].vector.x) /
                                    2;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y +
                                     p->li[i][j - 1][k].vector.y) /
                                    2;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z +
                                     p->li[i][j - 1][k].vector.z) /
                                    2;

                                p->Sj[i][j][k].j.x = 0;
                                p->Sj[i][j][k].j.y = 0;
                                p->Sj[i][j][k].j.z = 0;
                                break;

                            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_TOP):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j - 1][k].vector.x) / 2;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j - 1][k].vector.y) / 2;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j - 1][k].vector.z) / 2;

                                p->Sj[i][j][k].j.x = 0;
                                p->Sj[i][j][k].j.y = 0;
                                p->Sj[i][j][k].j.z = 0;
                                break;

                            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_TOP):
                                p->Sj[i][j][k].i.x =
                                    (p->li[i][j][k].vector.x) / 2;
                                p->Sj[i][j][k].i.y =
                                    (p->li[i][j][k].vector.y) / 2;
                                p->Sj[i][j][k].i.z =
                                    (p->li[i][j][k].vector.z) / 2;

                                p->Sj[i][j][k].j.x = 0;
                                p->Sj[i][j][k].j.y = 0;
                                p->Sj[i][j][k].j.z = 0;
                                break;

                            default:
                                console(4);
                                exit(1);
                                break;
                        }

                        crossProductCalc(p->Sj[i][j][k].cp.vector,
                                         p->Sj[i][j][k].i, p->Sj[i][j][k].j);
                        p->Sj[i][j][k].cp.norm =
                            normCalc(p->Sj[i][j][k].cp.vector);
                    }
                }
                if (!CubePressure) {
                    switch (p->flag[i][j][k]) {
                        case Center:
                            p->Sj[i][j][k].i.x =
                                (p->li[i][j + 1][k].vector.x +
                                 p->li[i - 1][j + 1][k].vector.x +
                                 p->li[i][j][k].vector.x +
                                 p->li[i - 1][j][k].vector.x) /
                                4;
                            p->Sj[i][j][k].i.y =
                                (p->li[i][j + 1][k].vector.y +
                                 p->li[i - 1][j + 1][k].vector.y +
                                 p->li[i][j][k].vector.y +
                                 p->li[i - 1][j][k].vector.y) /
                                4;
                            p->Sj[i][j][k].i.z =
                                (p->li[i][j + 1][k].vector.z +
                                 p->li[i - 1][j + 1][k].vector.z +
                                 p->li[i][j][k].vector.z +
                                 p->li[i - 1][j][k].vector.z) /
                                4;

                            p->Sj[i][j][k].j.x = (p->lj[i + 1][j][k].vector.x +
                                                  p->lj[i][j][k].vector.x +
                                                  p->lj[i][j][k].vector.x +
                                                  p->lj[i - 1][j][k].vector.x) /
                                                 4;
                            p->Sj[i][j][k].j.y = (p->lj[i + 1][j][k].vector.y +
                                                  p->lj[i][j][k].vector.y +
                                                  p->lj[i][j][k].vector.y +
                                                  p->lj[i - 1][j][k].vector.y) /
                                                 4;
                            p->Sj[i][j][k].j.z = (p->lj[i + 1][j][k].vector.z +
                                                  p->lj[i][j][k].vector.z +
                                                  p->lj[i][j][k].vector.z +
                                                  p->lj[i - 1][j][k].vector.z) /
                                                 4;
                            break;

                        case Left:
                            p->Sj[i][j][k].i.x = (p->li[i][j + 1][k].vector.x +
                                                  p->li[i][j][k].vector.x) /
                                                 4;
                            p->Sj[i][j][k].i.y = (p->li[i][j + 1][k].vector.y +
                                                  p->li[i][j][k].vector.y) /
                                                 4;
                            p->Sj[i][j][k].i.z = (p->li[i][j + 1][k].vector.z +
                                                  p->li[i][j][k].vector.z) /
                                                 4;

                            p->Sj[i][j][k].j.x = (p->lj[i + 1][j][k].vector.x +
                                                  p->lj[i][j][k].vector.x) /
                                                 2;
                            p->Sj[i][j][k].j.y = (p->lj[i + 1][j][k].vector.y +
                                                  p->lj[i][j][k].vector.y) /
                                                 2;
                            p->Sj[i][j][k].j.z = (p->lj[i + 1][j][k].vector.z +
                                                  p->lj[i][j][k].vector.z) /
                                                 2;
                            break;

                        case Bottom:
                            p->Sj[i][j][k].i.x =
                                (p->li[i][j + 1][k].vector.x +
                                 p->li[i - 1][j + 1][k].vector.x +
                                 p->li[i][j][k].vector.x +
                                 p->li[i - 1][j][k].vector.x) /
                                4;
                            p->Sj[i][j][k].i.y =
                                (p->li[i][j + 1][k].vector.y +
                                 p->li[i - 1][j + 1][k].vector.y +
                                 p->li[i][j][k].vector.y +
                                 p->li[i - 1][j][k].vector.y) /
                                4;
                            p->Sj[i][j][k].i.z =
                                (p->li[i][j + 1][k].vector.z +
                                 p->li[i - 1][j + 1][k].vector.z +
                                 p->li[i][j][k].vector.z +
                                 p->li[i - 1][j][k].vector.z) /
                                4;

                            p->Sj[i][j][k].j.x = (p->lj[i + 1][j][k].vector.x +
                                                  p->lj[i][j][k].vector.x +
                                                  p->lj[i][j][k].vector.x +
                                                  p->lj[i - 1][j][k].vector.x) /
                                                 4;
                            p->Sj[i][j][k].j.y = (p->lj[i + 1][j][k].vector.y +
                                                  p->lj[i][j][k].vector.y +
                                                  p->lj[i][j][k].vector.y +
                                                  p->lj[i - 1][j][k].vector.y) /
                                                 4;
                            p->Sj[i][j][k].j.z = (p->lj[i + 1][j][k].vector.z +
                                                  p->lj[i][j][k].vector.z +
                                                  p->lj[i][j][k].vector.z +
                                                  p->lj[i - 1][j][k].vector.z) /
                                                 4;
                            break;

                        case Right:
                            p->Sj[i][j][k].i.x =
                                (p->li[i - 1][j + 1][k].vector.x +
                                 p->li[i - 1][j][k].vector.x) /
                                4;
                            p->Sj[i][j][k].i.y =
                                (p->li[i - 1][j + 1][k].vector.y +
                                 p->li[i - 1][j][k].vector.y) /
                                4;
                            p->Sj[i][j][k].i.z =
                                (p->li[i - 1][j + 1][k].vector.z +
                                 p->li[i - 1][j][k].vector.z) /
                                4;

                            p->Sj[i][j][k].j.x = (p->lj[i][j][k].vector.x +
                                                  p->lj[i - 1][j][k].vector.x) /
                                                 2;
                            p->Sj[i][j][k].j.y = (p->lj[i][j][k].vector.y +
                                                  p->lj[i - 1][j][k].vector.y) /
                                                 2;
                            p->Sj[i][j][k].j.z = (p->lj[i][j][k].vector.z +
                                                  p->lj[i - 1][j][k].vector.z) /
                                                 2;
                            break;

                        case LeftBottom:
                            p->Sj[i][j][k].i.x = (p->li[i][j + 1][k].vector.x +
                                                  p->li[i][j][k].vector.x) /
                                                 4;
                            p->Sj[i][j][k].i.y = (p->li[i][j + 1][k].vector.y +
                                                  p->li[i][j][k].vector.y) /
                                                 4;
                            p->Sj[i][j][k].i.z = (p->li[i][j + 1][k].vector.z +
                                                  p->li[i][j][k].vector.z) /
                                                 4;

                            p->Sj[i][j][k].j.x = (p->lj[i + 1][j][k].vector.x +
                                                  p->lj[i][j][k].vector.x) /
                                                 2;
                            p->Sj[i][j][k].j.y = (p->lj[i + 1][j][k].vector.y +
                                                  p->lj[i][j][k].vector.y) /
                                                 2;
                            p->Sj[i][j][k].j.z = (p->lj[i + 1][j][k].vector.z +
                                                  p->lj[i][j][k].vector.z) /
                                                 2;
                            break;

                        case RightBottom:
                            p->Sj[i][j][k].i.x =
                                (p->li[i - 1][j + 1][k].vector.x +
                                 p->li[i - 1][j][k].vector.x) /
                                4;
                            p->Sj[i][j][k].i.y =
                                (p->li[i - 1][j + 1][k].vector.y +
                                 p->li[i - 1][j][k].vector.y) /
                                4;
                            p->Sj[i][j][k].i.z =
                                (p->li[i - 1][j + 1][k].vector.z +
                                 p->li[i - 1][j][k].vector.z) /
                                4;

                            p->Sj[i][j][k].j.x = (p->lj[i][j][k].vector.x +
                                                  p->lj[i - 1][j][k].vector.x) /
                                                 2;
                            p->Sj[i][j][k].j.y = (p->lj[i][j][k].vector.y +
                                                  p->lj[i - 1][j][k].vector.y) /
                                                 2;
                            p->Sj[i][j][k].j.z = (p->lj[i][j][k].vector.z +
                                                  p->lj[i - 1][j][k].vector.z) /
                                                 2;
                            break;

                        case Top:
                            p->Sj[i][j][k].i.x = (p->li[i][j][k].vector.x +
                                                  p->li[i - 1][j][k].vector.x) /
                                                 2;
                            p->Sj[i][j][k].i.y = (p->li[i][j][k].vector.y +
                                                  p->li[i - 1][j][k].vector.y) /
                                                 2;
                            p->Sj[i][j][k].i.z = (p->li[i][j][k].vector.z +
                                                  p->li[i - 1][j][k].vector.z) /
                                                 2;

                            p->Sj[i][j][k].j.x = 0;
                            p->Sj[i][j][k].j.y = 0;
                            p->Sj[i][j][k].j.z = 0;
                            break;

                        case RightTop:
                            p->Sj[i][j][k].i.x =
                                (p->li[i - 1][j][k].vector.x) / 2;
                            p->Sj[i][j][k].i.y =
                                (p->li[i - 1][j][k].vector.y) / 2;
                            p->Sj[i][j][k].i.z =
                                (p->li[i - 1][j][k].vector.z) / 2;

                            p->Sj[i][j][k].j.x = 0;
                            p->Sj[i][j][k].j.y = 0;
                            p->Sj[i][j][k].j.z = 0;
                            break;

                        case LeftTop:
                            p->Sj[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                            p->Sj[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                            p->Sj[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

                            p->Sj[i][j][k].j.x = 0;
                            p->Sj[i][j][k].j.y = 0;
                            p->Sj[i][j][k].j.z = 0;
                            break;

                        default:
                            console(4);
                            break;
                    }

                    crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                     p->Sj[i][j][k].j);
                    p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                }
            }
        }
    }
}

/**
 * @brief	計算した値を初期値を格納する変数に代入する
 */
void MultiParticle::setInitialConditionsCopy() {
    for (int i = 0; i < local_iNum; i++) {
        for (int j = 0; j < local_jNum; j++) {
            for (int k = 0; k < local_kNum; k++) {
                p->new_c[i][j][k] = p->c[i][j][k];
                // cout << "z = "
                //      << p->c[i][j][k].z
                //      << endl;
                p->new_v[i][j][k] = p->v[i][j][k];

                p->li0[i][j][k] = p->li[i][j][k].norm;
                p->lj0[i][j][k] = p->lj[i][j][k].norm;

                p->g0[i][j][k]  = p->g[i][j][k];
                p->mi0[i][j][k] = p->mi[i][j][k];
                p->mj0[i][j][k] = p->mj[i][j][k];

                p->beta0[i][j][k] = p->beta[i][j][k];

                p->S0[i][j][k]  = p->S[i][j][k].cp.norm;
                p->Si0[i][j][k] = p->Si[i][j][k].cp.norm;
                p->Sj0[i][j][k] = p->Sj[i][j][k].cp.norm;

                // p->etai0[i][j][k] = 0;
                // p->etaj0[i][j][k] = 0;
                p->etai0[i][j][k] = p->etai[i][j][k];
                p->etaj0[i][j][k] = p->etaj[i][j][k];
                // p->etai[i][j][k] = 0;
                // p->etaj[i][j][k] = 0;

                // cout << p->Si[i][j][k].cp.norm << endl;
#ifdef __CYLINDER_NON_BOUNDARY__
                p->omp[i][j][k].beta0.pp = p->omp[i][j][k].beta.pp;
                p->omp[i][j][k].beta0.pm = p->omp[i][j][k].beta.pm;
                p->omp[i][j][k].g0       = p->omp[i][j][k].g;
                p->omp[i][j][k].mi0      = p->omp[i][j][k].mi;
                p->omp[i][j][k].li0      = p->omp[i][j][k].li.norm;
                p->omp[i][j][k].lj0      = p->omp[i][j][k].lj.norm;
                p->omp[i][j][k].S0       = p->omp[i][j][k].S.cp.norm;
                p->omp[i][j][k].Si0      = p->omp[i][j][k].Si.cp.norm;
                p->omp[i][j][k].Sj0      = p->omp[i][j][k].Sj.cp.norm;
#endif
            }
        }
    }
}
