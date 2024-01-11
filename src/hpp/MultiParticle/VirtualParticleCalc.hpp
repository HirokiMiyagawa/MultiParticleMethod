/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file	VirtualParticleCalc.hpp
 * @brief	仮想粒子の配置とl,g,ε
 * @details
 * ///////////////////////////////////////////////////////////////////////////////
 */

///////////// 3次元的な形状 /////////////////
#if defined __SHAPE_CUBE__
void MultiParticle::OldVirtualParticleCalc(int const& i, int const& j,
                                           int const& k) {
    if (p->flag[i][j][k] & BIT_CEILING) {
        switch (p->flag[i][j][k]) {
            case (BIT_CEILING):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x +
                      p->c[i + 1][j][k].x + p->c[i + 1][j + 1][k].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y +
                      p->c[i + 1][j][k].y + p->c[i + 1][j + 1][k].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z +
                      p->c[i + 1][j][k].z + p->c[i + 1][j + 1][k].z) /
                     4);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                break;

            case (BIT_CEILING | BIT_LEFT):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x +
                      p->c[i + 1][j][k].x + p->c[i + 1][j + 1][k].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y +
                      p->c[i + 1][j][k].y + p->c[i + 1][j + 1][k].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z +
                      p->c[i + 1][j][k].z + p->c[i + 1][j + 1][k].z) /
                     4);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                break;

            case (BIT_CEILING | BIT_RIGHT):
                // add
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j][k - 1]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                //
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                // p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i + 1][j][k].x) /
                // 2); p->g[i][j][k].y = ((p->c[i][j][k].y + p->c[i +
                // 1][j][k].y) / 2); p->g[i][j][k].z = ((p->c[i][j][k].z +
                // p->c[i + 1][j][k].z) / 2);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k - 1].x +
                      p->c[i + 1][j][k].x + p->c[i + 1][j][k - 1].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k - 1].y +
                      p->c[i + 1][j][k].y + p->c[i + 1][j][k - 1].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k - 1].z +
                      p->c[i + 1][j][k].z + p->c[i + 1][j][k - 1].z) /
                     4);
                // p->mi[i][j][k].x = 0;
                // p->mi[i][j][k].y = 0;
                // p->mi[i][j][k].z = 0;
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k - 1].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k - 1].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k - 1].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                break;

            case (BIT_CEILING | BIT_BOTTOM):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x +
                      p->c[i + 1][j][k].x + p->c[i + 1][j + 1][k].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y +
                      p->c[i + 1][j][k].y + p->c[i + 1][j + 1][k].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z +
                      p->c[i + 1][j][k].z + p->c[i + 1][j + 1][k].z) /
                     4);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                break;

            case (BIT_CEILING | BIT_TOP):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->g[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->g[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mj[i][j][k].x = 0;
                p->mj[i][j][k].y = 0;
                p->mj[i][j][k].z = 0;
                break;

            case (BIT_CEILING | BIT_LEFT | BIT_BOTTOM):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x +
                      p->c[i + 1][j][k].x + p->c[i + 1][j + 1][k].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y +
                      p->c[i + 1][j][k].y + p->c[i + 1][j + 1][k].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z +
                      p->c[i + 1][j][k].z + p->c[i + 1][j + 1][k].z) /
                     4);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                break;

            case (BIT_CEILING | BIT_LEFT | BIT_TOP):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->g[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->g[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mj[i][j][k].x = 0;
                p->mj[i][j][k].y = 0;
                p->mj[i][j][k].z = 0;
                break;

            case (BIT_CEILING | BIT_RIGHT | BIT_BOTTOM):
                // add
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j][k - 1]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                //
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                // p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i + 1][j][k].x) /
                // 2); p->g[i][j][k].y = ((p->c[i][j][k].y + p->c[i +
                // 1][j][k].y) / 2); p->g[i][j][k].z = ((p->c[i][j][k].z +
                // p->c[i + 1][j][k].z) / 2);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k - 1].x +
                      p->c[i + 1][j][k].x + p->c[i + 1][j][k - 1].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k - 1].y +
                      p->c[i + 1][j][k].y + p->c[i + 1][j][k - 1].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k - 1].z +
                      p->c[i + 1][j][k].z + p->c[i + 1][j][k - 1].z) /
                     4);
                // p->mi[i][j][k].x = 0;
                // p->mi[i][j][k].y = 0;
                // p->mi[i][j][k].z = 0;
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k - 1].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k - 1].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k - 1].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                break;

            case (BIT_CEILING | BIT_RIGHT | BIT_TOP):
                // add
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j][k - 1]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                //
                // p->g[i][j][k].x = p->c[i][j][k].x;
                // p->g[i][j][k].y = p->c[i][j][k].y;
                // p->g[i][j][k].z = p->c[i][j][k].z;
                p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j][k - 1].x) / 2);
                p->g[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j][k - 1].y) / 2);
                p->g[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j][k - 1].z) / 2);
                // p->mi[i][j][k].x = 0;
                // p->mi[i][j][k].y = 0;
                // p->mi[i][j][k].z = 0;
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k - 1].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k - 1].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k - 1].z) / 2);
                p->mj[i][j][k].x = 0;
                p->mj[i][j][k].y = 0;
                p->mj[i][j][k].z = 0;
                break;
        }
    } else if (p->flag[i][j][k] & BIT_BACK) {
        switch (p->flag[i][j][k]) {
            case (BIT_BACK):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j][k + 1]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x +
                      p->c[i][j][k + 1].x + p->c[i + 1][j][k + 1].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y +
                      p->c[i][j][k + 1].y + p->c[i + 1][j][k + 1].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z +
                      p->c[i][j][k + 1].z + p->c[i + 1][j][k + 1].z) /
                     4);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                break;

            case (BIT_BACK | BIT_LEFT):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j][k + 1]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x +
                      p->c[i][j][k + 1].x + p->c[i + 1][j][k + 1].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y +
                      p->c[i][j][k + 1].y + p->c[i + 1][j][k + 1].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z +
                      p->c[i][j][k + 1].z + p->c[i + 1][j][k + 1].z) /
                     4);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                break;

            case (BIT_BACK | BIT_RIGHT):
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j][k + 1]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->g[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->g[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                p->mi[i][j][k].x = 0;
                p->mi[i][j][k].y = 0;
                p->mi[i][j][k].z = 0;
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                break;

            case (BIT_BACK | BIT_BOTTOM):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j][k + 1]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x +
                      p->c[i][j][k + 1].x + p->c[i + 1][j][k + 1].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y +
                      p->c[i][j][k + 1].y + p->c[i + 1][j][k + 1].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z +
                      p->c[i][j][k + 1].z + p->c[i + 1][j][k + 1].z) /
                     4);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                break;

            case (BIT_BACK | BIT_TOP):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->g[i][j][k].y = ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->g[i][j][k].z = ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                p->mj[i][j][k].x = 0;
                p->mj[i][j][k].y = 0;
                p->mj[i][j][k].z = 0;
                break;

            case (BIT_BACK | BIT_LEFT | BIT_BOTTOM):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j][k + 1]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x +
                      p->c[i][j][k + 1].x + p->c[i + 1][j][k + 1].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y +
                      p->c[i][j][k + 1].y + p->c[i + 1][j][k + 1].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z +
                      p->c[i][j][k + 1].z + p->c[i + 1][j][k + 1].z) /
                     4);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                break;

            case (BIT_BACK | BIT_LEFT | BIT_TOP):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->g[i][j][k].y = ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->g[i][j][k].z = ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
                p->mj[i][j][k].x = 0;
                p->mj[i][j][k].y = 0;
                p->mj[i][j][k].z = 0;
                break;

            case (BIT_BACK | BIT_RIGHT | BIT_BOTTOM):
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j][k + 1]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->g[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->g[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                p->mi[i][j][k].x = 0;
                p->mi[i][j][k].y = 0;
                p->mi[i][j][k].z = 0;
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                break;

            case (BIT_BACK | BIT_RIGHT | BIT_TOP):
                p->g[i][j][k].x  = p->c[i][j][k].x;
                p->g[i][j][k].y  = p->c[i][j][k].y;
                p->g[i][j][k].z  = p->c[i][j][k].z;
                p->mi[i][j][k].x = 0;
                p->mi[i][j][k].y = 0;
                p->mi[i][j][k].z = 0;
                p->mj[i][j][k].x = 0;
                p->mj[i][j][k].y = 0;
                p->mj[i][j][k].z = 0;
                break;
        }
    } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
        switch (p->flag[i][j][k]) {
            case (BIT_RIGHTSIDE):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j][k + 1]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x +
                      p->c[i][j][k + 1].x + p->c[i][j + 1][k + 1].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y +
                      p->c[i][j][k + 1].y + p->c[i][j + 1][k + 1].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z +
                      p->c[i][j][k + 1].z + p->c[i][j + 1][k + 1].z) /
                     4);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                break;

            case (BIT_RIGHTSIDE | BIT_LEFT):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j][k + 1]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x +
                      p->c[i][j][k + 1].x + p->c[i][j + 1][k + 1].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y +
                      p->c[i][j][k + 1].y + p->c[i][j + 1][k + 1].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z +
                      p->c[i][j][k + 1].z + p->c[i][j + 1][k + 1].z) /
                     4);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                break;

            case (BIT_RIGHTSIDE | BIT_RIGHT):
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j][k + 1]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->g[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->g[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                p->mi[i][j][k].x = 0;
                p->mi[i][j][k].y = 0;
                p->mi[i][j][k].z = 0;
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                break;

            case (BIT_RIGHTSIDE | BIT_BOTTOM):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j][k + 1]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x +
                      p->c[i][j][k + 1].x + p->c[i][j + 1][k + 1].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y +
                      p->c[i][j][k + 1].y + p->c[i][j + 1][k + 1].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z +
                      p->c[i][j][k + 1].z + p->c[i][j + 1][k + 1].z) /
                     4);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                break;

            case (BIT_RIGHTSIDE | BIT_TOP):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->g[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->g[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mj[i][j][k].x = 0;
                p->mj[i][j][k].y = 0;
                p->mj[i][j][k].z = 0;
                break;

            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_BOTTOM):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j][k + 1]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x +
                      p->c[i][j][k + 1].x + p->c[i][j + 1][k + 1].x) /
                     4);
                p->g[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y +
                      p->c[i][j][k + 1].y + p->c[i][j + 1][k + 1].y) /
                     4);
                p->g[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z +
                      p->c[i][j][k + 1].z + p->c[i][j + 1][k + 1].z) /
                     4);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                break;

            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_TOP):
                lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
                p->epsilonli[i][j][k] =
                    epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
                p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->g[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->g[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mi[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->mi[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->mi[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->mj[i][j][k].x = 0;
                p->mj[i][j][k].y = 0;
                p->mj[i][j][k].z = 0;
                break;

            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_BOTTOM):
                lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j][k + 1]);
                p->epsilonlj[i][j][k] =
                    epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
                p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->g[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->g[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                p->mi[i][j][k].x = 0;
                p->mi[i][j][k].y = 0;
                p->mi[i][j][k].z = 0;
                p->mj[i][j][k].x =
                    ((p->c[i][j][k].x + p->c[i][j][k + 1].x) / 2);
                p->mj[i][j][k].y =
                    ((p->c[i][j][k].y + p->c[i][j][k + 1].y) / 2);
                p->mj[i][j][k].z =
                    ((p->c[i][j][k].z + p->c[i][j][k + 1].z) / 2);
                break;

            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_TOP):
                p->g[i][j][k].x  = p->c[i][j][k].x;
                p->g[i][j][k].y  = p->c[i][j][k].y;
                p->g[i][j][k].z  = p->c[i][j][k].z;
                p->mi[i][j][k].x = 0;
                p->mi[i][j][k].y = 0;
                p->mi[i][j][k].z = 0;
                p->mj[i][j][k].x = 0;
                p->mj[i][j][k].y = 0;
                p->mj[i][j][k].z = 0;
                break;
        }
    }
    //////////////////////////////////////////////////////////////////////
    ////////////////////////* 仮想粒子の配置 *////////////////////////////
    //////////////////////////////////////////////////////////////////////

    if (p->flag[i][j][k] & BIT_CEILING) {
        if (p->flag[i][j][k] & BIT_LEFT) {
            p->vc_Left[i][j][k].x = p->c[i][j][k].x;
            p->vc_Left[i][j][k].y = p->c[i][j][k].y - p->li[i][j][k].vector.y;
            p->vc_Left[i][j][k].z = p->c[i][j][k].z;
        }
        // if (p->flag[i][j][k] & BIT_RIGHT)
        // {
        // 	p->vc_Right[i][j][k].x = p->c[i][j][k].x;
        // 	p->vc_Right[i][j][k].y = p->c[i][j][k].y;
        // 	p->vc_Right[i][j][k].z = p->c[i][j][k].z;
        // }
        // if (p->flag[i][j][k] & BIT_BOTTOM)
        // {
        // 	p->vc_Bottom[i][j][k].x = p->c[i][j][k].x;
        // 	p->vc_Bottom[i][j][k].y = p->c[i][j][k].y;
        // 	p->vc_Bottom[i][j][k].z = p->c[i][j][k].z;
        // }
        if (p->flag[i][j][k] & BIT_TOP) {
            p->vc_Top[i][j][k].x =
                p->c[i][j][k].x + p->lj[i - 1][j][k].vector.x;
            p->vc_Top[i][j][k].y = p->c[i][j][k].y;
            p->vc_Top[i][j][k].z = p->c[i][j][k].z;
        }
    } else if (p->flag[i][j][k] & BIT_BACK) {
        // if (p->flag[i][j][k] & BIT_LEFT)
        // {
        // 	p->vc_Left[i][j][k].x = p->c[i][j][k].x;
        // 	p->vc_Left[i][j][k].y = p->c[i][j][k].y;
        // 	p->vc_Left[i][j][k].z = p->c[i][j][k].z;
        // }
        if (p->flag[i][j][k] & BIT_RIGHT) {
            p->vc_Right[i][j][k].x =
                p->c[i][j][k].x + p->li[i - 1][j][k].vector.x;
            p->vc_Right[i][j][k].y = p->c[i][j][k].y;
            p->vc_Right[i][j][k].z = p->c[i][j][k].z;
        }
        if (p->flag[i][j][k] & BIT_BOTTOM) {
            p->vc_Bottom[i][j][k].x = p->c[i][j][k].x;
            p->vc_Bottom[i][j][k].y = p->c[i][j][k].y;
            p->vc_Bottom[i][j][k].z = p->c[i][j][k].z - p->lj[i][j][k].vector.z;
        }
        // if (p->flag[i][j][k] & BIT_TOP)
        // {
        // 	p->vc_Top[i][j][k].x = p->c[i][j][k].x;
        // 	p->vc_Top[i][j][k].y = p->c[i][j][k].y;
        // 	p->vc_Top[i][j][k].z = p->c[i][j][k].z;
        // }
    } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
        if (p->flag[i][j][k] & BIT_LEFT) {
            p->vc_Left[i][j][k].x = p->c[i][j][k].x;
            p->vc_Left[i][j][k].y = p->c[i][j][k].y - p->li[i][j][k].vector.y;
            p->vc_Left[i][j][k].z = p->c[i][j][k].z;
        }
        // if (p->flag[i][j][k] & BIT_RIGHT)
        // {
        // 	p->vc_Right[i][j][k].x = p->c[i][j][k].x;
        // 	p->vc_Right[i][j][k].y = p->c[i][j][k].y;
        // 	p->vc_Right[i][j][k].z = p->c[i][j][k].z;
        // }
        if (p->flag[i][j][k] & BIT_BOTTOM) {
            p->vc_Bottom[i][j][k].x = p->c[i][j][k].x;
            p->vc_Bottom[i][j][k].y = p->c[i][j][k].y;
            p->vc_Bottom[i][j][k].z = p->c[i][j][k].z - p->lj[i][j][k].vector.z;
        }
        // if (p->flag[i][j][k] & BIT_TOP)
        // {
        // 	p->vc_Top[i][j][k].x = p->c[i][j][k].x;
        // 	p->vc_Top[i][j][k].y = p->c[i][j][k].y;
        // 	p->vc_Top[i][j][k].z = p->c[i][j][k].z;
        // }
    }
}

#else
////////////////////////////////////////////
///////////// 2次元的な形状 /////////////////
////////////////////////////////////////////


void MultiParticle::OldVirtualParticleCalc(int const& i, int const& j,
                                           int const& k) {
    switch (p->flag[i][j][k]) {
        case Center:
            lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
            p->epsilonli[i][j][k] =
                epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
            lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
            p->epsilonlj[i][j][k] =
                epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
            p->g[i][j][k].x  = ((p->c[i][j][k].x + p->c[i + 1][j][k].x +
                                p->c[i][j + 1][k].x + p->c[i + 1][j + 1][k].x) /
                               4);
            p->g[i][j][k].y  = ((p->c[i][j][k].y + p->c[i + 1][j][k].y +
                                p->c[i][j + 1][k].y + p->c[i + 1][j + 1][k].y) /
                               4);
            p->g[i][j][k].z  = ((p->c[i][j][k].z + p->c[i + 1][j][k].z +
                                p->c[i][j + 1][k].z + p->c[i + 1][j + 1][k].z) /
                               4);
            p->mi[i][j][k].x = ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
            p->mi[i][j][k].y = ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
            p->mi[i][j][k].z = ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
            p->mj[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
            p->mj[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
            p->mj[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
            break;

        case Left:
            lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
            p->epsilonli[i][j][k] =
                epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
            lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
            p->epsilonlj[i][j][k] =
                epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
            p->g[i][j][k].x  = ((p->c[i][j][k].x + p->c[i + 1][j][k].x +
                                p->c[i][j + 1][k].x + p->c[i + 1][j + 1][k].x) /
                               4);
            p->g[i][j][k].y  = ((p->c[i][j][k].y + p->c[i + 1][j][k].y +
                                p->c[i][j + 1][k].y + p->c[i + 1][j + 1][k].y) /
                               4);
            p->g[i][j][k].z  = ((p->c[i][j][k].z + p->c[i + 1][j][k].z +
                                p->c[i][j + 1][k].z + p->c[i + 1][j + 1][k].z) /
                               4);
            p->mi[i][j][k].x = ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
            p->mi[i][j][k].y = ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
            p->mi[i][j][k].z = ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
            p->mj[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
            p->mj[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
            p->mj[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
            // #ifdef __CYLINDER_NON_BOUNDARY__
            if (CylinderPressure && !param->boundary.cylinder_boundary) {
                p->omp[i][j][k].ci.x = p->c[i][j][k].x;
                p->omp[i][j][k].ci.y = -1 * p->c[i][j][k].y;
                p->omp[i][j][k].ci.z = p->c[i][j][k].z;
                lCalc(p->omp[i][j][k].li, p->omp[i][j][k].ci, p->c[i][j][k]);
                p->omp[i][j][k].epsilonli =
                    epsilonlCulc(p->omp[i][j][k].li.norm, p->omp[i][j][k].li0);
                p->omp[i][j][k].g.x =
                    ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                p->omp[i][j][k].g.y =
                    ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                p->omp[i][j][k].g.z =
                    ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                p->omp[i][j][k].mi.x = p->c[i][j][k].x;  // 0でいい
                p->omp[i][j][k].mi.y = 0;
                p->omp[i][j][k].mi.z = p->c[i][j][k].z;
            }
            // #endif
            break;

        case Right:
            lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
            p->epsilonlj[i][j][k] =
                epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
#ifdef __CYLINDER_PRESSURE__
            if (CylinderPressure) {
#ifdef __CYLINDER_BOUNDARY__
                if (param->boundary.cylinder_boundary) {
                    gCalc(p->g[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
                    // p->g[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j +
                    // 1][k].x) / 2); p->g[i][j][k].y = ((p->c[i][j][k].y +
                    // p->c[i][j + 1][k].y) / 2); p->g[i][j][k].z =
                    // ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                    p->mi[i][j][k].x = 0;
                    p->mi[i][j][k].y = 0;
                    p->mi[i][j][k].z = 0;
                }
#elif defined __CYLINDER_NON_BOUNDARY__
                if (!param->boundary.cylinder_boundary) {
                    // p->vc_tmp[i][j][k].x = -1 * p->c[i][j][k].x;
                    // p->vc_tmp[i][j][k].y = p->c[i][j][k].y;
                    // p->vc_tmp[i][j][k].z = p->c[i][j][k].z;
                    p->omp[i][j][k].ci.x = -1 * p->c[i][j][k].x;
                    p->omp[i][j][k].ci.y = p->c[i][j][k].y;
                    p->omp[i][j][k].ci.z = p->c[i][j][k].z;
                    // lCalc(p->li[i][j][k], p->c[i][j][k], p->vc_tmp[i][j][k]);
                    lCalc(p->li[i][j][k], p->c[i][j][k], p->omp[i][j][k].ci);
                    lCalc(p->omp[i][j][k].li, p->c[i][j][k],
                          p->omp[i][j][k].ci);
                    p->omp[i][j][k].epsilonli = epsilonlCulc(
                        p->omp[i][j][k].li.norm, p->omp[i][j][k].li0);
                    // p->epsilonli[i][j][k] =
                    // epsilonlCulc(p->omp[i][j][k].li.norm, p->li0[i][j][k]);
                    // p->epsilonli[i][j][k] = epsilonlCulc(p->li[i][j][k].norm,
                    // p->li0[i][j][k]); p->epsilonli[i][j][k] =
                    // epsilonlCulc(p->omp[i][j][k].li.norm,
                    // p->omp[i][j][k].li0); p->g[i][j][k].x = ((p->c[i][j][k].x
                    // + p->c[i][j + 1][k].x + 0 + 0) / 4); p->g[i][j][k].y =
                    // ((p->c[i][j][k].y + p->c[i][j
                    // + 1][k].y + p->c[i][j][k].y + p->c[i][j + 1][k].z) / 4);
                    // p->g[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j + 1][k].z
                    // + p->c[i][j][k].z + p->c[i][j + 1][k].z) / 4);
                    p->omp[i][j][k].g.x =
                        ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
                    p->omp[i][j][k].g.y =
                        ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
                    p->omp[i][j][k].g.z =
                        ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
                    // p->mi[i][j][k].x = 0;	// 0はおかしい
                    // p->mi[i][j][k].y = 0;	// 0はおかしい
                    // p->mi[i][j][k].z = 0;	// 0はおかしい
                    p->omp[i][j][k].mi.x = 0;  // 0でいい
                    p->omp[i][j][k].mi.y = p->c[i][j][k].y;
                    p->omp[i][j][k].mi.z = p->c[i][j][k].z;
                    // gCalc(p->g[i][j][k], p->c[i][j][k], p->c[i][j + 1][k],
                    // p->vc_Right[i][j][k], p->vc_Right[i][j + 1][k]);
                    // mCalc(p->mi[i][j][k], p->c[i][j][k],
                    // p->vc_Right[i][j][k]);
                }
#endif
            }
#endif
            p->mj[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
            p->mj[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
            p->mj[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
            break;

        case Bottom:
            lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
            p->epsilonli[i][j][k] =
                epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
            lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
            p->epsilonlj[i][j][k] =
                epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
            p->g[i][j][k].x  = ((p->c[i][j][k].x + p->c[i + 1][j][k].x +
                                p->c[i][j + 1][k].x + p->c[i + 1][j + 1][k].x) /
                               4);
            p->g[i][j][k].y  = ((p->c[i][j][k].y + p->c[i + 1][j][k].y +
                                p->c[i][j + 1][k].y + p->c[i + 1][j + 1][k].y) /
                               4);
            p->g[i][j][k].z  = ((p->c[i][j][k].z + p->c[i + 1][j][k].z +
                                p->c[i][j + 1][k].z + p->c[i + 1][j + 1][k].z) /
                               4);
            p->mi[i][j][k].x = ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
            p->mi[i][j][k].y = ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
            p->mi[i][j][k].z = ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
            p->mj[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
            p->mj[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
            p->mj[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
            break;

        case Top:
            lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
            p->epsilonli[i][j][k] =
                epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
            p->g[i][j][k].x  = ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
            p->g[i][j][k].y  = ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
            p->g[i][j][k].z  = ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
            p->mi[i][j][k].x = ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
            p->mi[i][j][k].y = ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
            p->mi[i][j][k].z = ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
            p->mj[i][j][k].x = 0;
            p->mj[i][j][k].y = 0;
            p->mj[i][j][k].z = 0;
            break;

        case LeftBottom:
            lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
            p->epsilonli[i][j][k] =
                epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
            lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
            p->epsilonlj[i][j][k] =
                epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
            p->g[i][j][k].x  = ((p->c[i][j][k].x + p->c[i + 1][j][k].x +
                                p->c[i][j + 1][k].x + p->c[i + 1][j + 1][k].x) /
                               4);
            p->g[i][j][k].y  = ((p->c[i][j][k].y + p->c[i + 1][j][k].y +
                                p->c[i][j + 1][k].y + p->c[i + 1][j + 1][k].y) /
                               4);
            p->g[i][j][k].z  = ((p->c[i][j][k].z + p->c[i + 1][j][k].z +
                                p->c[i][j + 1][k].z + p->c[i + 1][j + 1][k].z) /
                               4);
            p->mi[i][j][k].x = ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
            p->mi[i][j][k].y = ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
            p->mi[i][j][k].z = ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
            p->mj[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
            p->mj[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
            p->mj[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
#ifdef __CYLINDER_NON_BOUNDARY__
            p->omp[i][j][k].ci.x = p->c[i][j][k].x;
            p->omp[i][j][k].ci.y = -1 * p->c[i][j][k].y;
            p->omp[i][j][k].ci.z = p->c[i][j][k].z;
            lCalc(p->omp[i][j][k].li, p->omp[i][j][k].ci, p->c[i][j][k]);
            p->omp[i][j][k].epsilonli =
                epsilonlCulc(p->omp[i][j][k].li.norm, p->omp[i][j][k].li0);
            p->omp[i][j][k].g.x = ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
            p->omp[i][j][k].g.y = ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
            p->omp[i][j][k].g.z = ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
            p->omp[i][j][k].mi.x = p->c[i][j][k].x;  // 0でいい
            p->omp[i][j][k].mi.y = 0;
            p->omp[i][j][k].mi.z = p->c[i][j][k].z;
#endif
            break;

        case LeftTop:
            lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
            p->epsilonli[i][j][k] =
                epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
            p->g[i][j][k].x  = ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
            p->g[i][j][k].y  = ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
            p->g[i][j][k].z  = ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
            p->mi[i][j][k].x = ((p->c[i][j][k].x + p->c[i + 1][j][k].x) / 2);
            p->mi[i][j][k].y = ((p->c[i][j][k].y + p->c[i + 1][j][k].y) / 2);
            p->mi[i][j][k].z = ((p->c[i][j][k].z + p->c[i + 1][j][k].z) / 2);
            p->mj[i][j][k].x = 0;
            p->mj[i][j][k].y = 0;
            p->mj[i][j][k].z = 0;
#ifdef __CYLINDER_NON_BOUNDARY__
            p->omp[i][j][k].ci.x = p->c[i][j][k].x;
            p->omp[i][j][k].ci.y = -1 * p->c[i][j][k].y;
            p->omp[i][j][k].ci.z = p->c[i][j][k].z;
            lCalc(p->omp[i][j][k].li, p->omp[i][j][k].ci, p->c[i][j][k]);
            p->omp[i][j][k].epsilonli =
                epsilonlCulc(p->omp[i][j][k].li.norm, p->omp[i][j][k].li0);
            // p->omp[i][j][k].g.x = ((p->omp[i][j][k].ci.x + p->c[i][j][k].x) /
            // 2); p->omp[i][j][k].g.y = ((p->omp[i][j][k].ci.y +
            // p->c[i][j][k].y) / 2); p->omp[i][j][k].g.z =
            // ((p->omp[i][j][k].ci.z + p->c[i][j][k].z) / 2);
            p->omp[i][j][k].g.x  = +p->c[i][j][k].x;
            p->omp[i][j][k].g.y  = +p->c[i][j][k].y;
            p->omp[i][j][k].g.z  = +p->c[i][j][k].z;
            p->omp[i][j][k].mi.x = p->c[i][j][k].x;  // 0でいい
            p->omp[i][j][k].mi.y = 0;
            p->omp[i][j][k].mi.z = p->c[i][j][k].z;
#endif
            break;

        case RightBottom:
            lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
            p->epsilonlj[i][j][k] =
                epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
            p->g[i][j][k].x  = ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
            p->g[i][j][k].y  = ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
            p->g[i][j][k].z  = ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
            p->mi[i][j][k].x = 0;
            p->mi[i][j][k].y = 0;
            p->mi[i][j][k].z = 0;
            p->mj[i][j][k].x = ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
            p->mj[i][j][k].y = ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
            p->mj[i][j][k].z = ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
#ifdef __CYLINDER_NON_BOUNDARY__
            p->omp[i][j][k].ci.x = -1 * p->c[i][j][k].x;
            p->omp[i][j][k].ci.y = p->c[i][j][k].y;
            p->omp[i][j][k].ci.z = p->c[i][j][k].z;
            // lCalc(p->li[i][j][k],  p->c[i][j][k], p->omp[i][j][k].ci);
            lCalc(p->omp[i][j][k].li, p->c[i][j][k], p->omp[i][j][k].ci);
            p->omp[i][j][k].epsilonli =
                epsilonlCulc(p->omp[i][j][k].li.norm, p->omp[i][j][k].li0);
            p->omp[i][j][k].g.x = ((p->c[i][j][k].x + p->c[i][j + 1][k].x) / 2);
            p->omp[i][j][k].g.y = ((p->c[i][j][k].y + p->c[i][j + 1][k].y) / 2);
            p->omp[i][j][k].g.z = ((p->c[i][j][k].z + p->c[i][j + 1][k].z) / 2);
            p->omp[i][j][k].mi.x = 0;  // 0でいい
            p->omp[i][j][k].mi.y = p->c[i][j][k].y;
            p->omp[i][j][k].mi.z = p->c[i][j][k].z;
#endif
            break;

        case RightTop:
            p->g[i][j][k].x      = p->c[i][j][k].x;
            p->g[i][j][k].y      = p->c[i][j][k].y;
            p->g[i][j][k].z      = p->c[i][j][k].z;
            p->mi[i][j][k].x     = 0;
            p->mi[i][j][k].y     = 0;
            p->mi[i][j][k].z     = 0;
            p->mj[i][j][k].x     = 0;
            p->mj[i][j][k].y     = 0;
            p->mj[i][j][k].z     = 0;
#ifdef __CYLINDER_NON_BOUNDARY__
            p->omp[i][j][k].ci.x = -1 * p->c[i][j][k].x;
            p->omp[i][j][k].ci.y = p->c[i][j][k].y;
            p->omp[i][j][k].ci.z = p->c[i][j][k].z;
            // lCalc(p->li[i][j][k],  p->c[i][j][k], p->omp[i][j][k].vc);
            lCalc(p->omp[i][j][k].li, p->c[i][j][k], p->omp[i][j][k].ci);
            p->omp[i][j][k].epsilonli =
                epsilonlCulc(p->omp[i][j][k].li.norm, p->omp[i][j][k].li0);
            // p->omp[i][j][k].g.x = ((p->omp[i][j][k].ci.x + p->c[i][j][k].x) /
            // 2); p->omp[i][j][k].g.y = ((p->omp[i][j][k].ci.y +
            // p->c[i][j][k].y) / 2); p->omp[i][j][k].g.z =
            // ((p->omp[i][j][k].ci.z + p->c[i][j][k].z) / 2);
            p->omp[i][j][k].g.x  = p->c[i][j][k].x;
            p->omp[i][j][k].g.y  = p->c[i][j][k].y;
            p->omp[i][j][k].g.z  = p->c[i][j][k].z;
            p->omp[i][j][k].mi.x = 0;  // 0でいい
            p->omp[i][j][k].mi.y = p->c[i][j][k].y;
            p->omp[i][j][k].mi.z = p->c[i][j][k].z;
#endif
            break;
    }

    //////////////////////////////////////////////////////////////////////
    ////////////////////////* set virtual particle *////////////////////////////
    //////////////////////////////////////////////////////////////////////
    if (CylinderPressure) {
        // cout << "CYLINDER" << endl;
        if (p->flag[i][j][k] == Bottom || p->flag[i][j][k] == LeftBottom ||
            p->flag[i][j][k] == RightBottom) {
            p->vc_Bottom[i][j][k].z = p->c[i][j][k].z - p->lj[i][j][k].vector.z;
            p->vc_Bottom[i][j][k].x = p->c[i][j][k].x;
            p->vc_Bottom[i][j][k].y = p->c[i][j][k].y;

            if (param->boundary.bottom_share_fix) {
                p->vc_Bottom[i][j][k].x = p->c[i][j][k].x;
                p->vc_Bottom[i][j][k].y = p->c[i][j][k].y;
            } else {
                // p->vc_Bottom[i][j][k].x	= p->c[i][j][k].x -
                // p->lj[i][j][k].vector.x;
            }
            if (param->boundary.bottom_bend_fix) {
                p->vc_Bottom[i][j][k].x = p->c[i][j][k].x;
                p->vc_Bottom[i][j][k].y = p->c[i][j][k].y;
            } else {
                // p->vc_Bottom[i][j][k].z	= p->c[i][j][k].z -
                // p->lj[i][j][k].vector.z;
            }
            if ((!param->boundary.bottom_share_fix) &&
                (!param->boundary.bottom_bend_fix)) {
                p->vc_Bottom[i][j][k].x =
                    p->c[i][j][k].x - p->lj[i][j][k].vector.x;
                p->vc_Bottom[i][j][k].y =
                    p->c[i][j][k].y - p->lj[i][j][k].vector.y;
            }
        }

        if (p->flag[i][j][k] == Top || p->flag[i][j][k] == LeftTop ||
            p->flag[i][j][k] == RightTop) {
            p->vc_Top[i][j][k].z =
                p->c[i][j][k].z + p->lj[i][j - 1][k].vector.z;
            p->vc_Top[i][j][k].x = p->c[i][j][k].x;
            p->vc_Top[i][j][k].y = p->c[i][j][k].y;

            if (param->boundary.top_share_fix) {
                p->vc_Top[i][j][k].x = p->c[i][j][k].x;
                p->vc_Top[i][j][k].y = p->c[i][j][k].y;
            } else {
                // p->vc_Top[i][j][k].x		= p->c[i][j][k].x +
                // p->lj[i][j-1][k].vector.x;
            }
            if (param->boundary.top_bend_fix) {
                p->vc_Top[i][j][k].x = p->c[i][j][k].x;
                p->vc_Top[i][j][k].y = p->c[i][j][k].y;

            } else {
                // p->vc_Top[i][j][k].z		= p->c[i][j][k].z +
                // p->lj[i][j-1][k].vector.z;
            }
            if ((!param->boundary.top_share_fix) &&
                (!param->boundary.top_bend_fix)) {
                p->vc_Top[i][j][k].x =
                    p->c[i][j][k].x + p->lj[i][j - 1][k].vector.x;
                p->vc_Top[i][j][k].y =
                    p->c[i][j][k].y + p->lj[i][j - 1][k].vector.y;
            }
        }

        if (p->flag[i][j][k] == Left || p->flag[i][j][k] == LeftBottom ||
            p->flag[i][j][k] == LeftTop) {
            if (param->boundary.cylinder_boundary) {
                p->vc_Left[i][j][k].x =
                    p->c[i][j][k].x + p->li[i][j][k].vector.x;
                p->vc_Left[i][j][k].y =
                    p->c[i][j][k].y - p->li[i][j][k].vector.y;
                p->vc_Left[i][j][k].z = p->c[i][j][k].z;
            } else {
                p->vc_Left[i][j][k].x = p->c[i][j][k].x;
                p->vc_Left[i][j][k].y = -1 * p->c[i][j][k].y;
                p->vc_Left[i][j][k].z = p->c[i][j][k].z;
            }
            if (param->boundary.left_share_fix) {
                p->vc_Left[i][j][k].x = p->c[i][j][k].x;
                p->vc_Left[i][j][k].z = p->c[i][j][k].z;
            } else {
                // p->vc_Left[i][j][k].y = p->c[i][j][k].y -
                // p->li[i][j][k].vector.y;
            }
            if (param->boundary.left_bend_fix) {
                p->vc_Left[i][j][k].x = p->c[i][j][k].x;
                p->vc_Left[i][j][k].z = p->c[i][j][k].z;

            } else {
                // p->vc_Left[i][j][k].z		= p->c[i][j][k].z -
                // p->li[i][j][k].vector.z;
            }

            if ((!param->boundary.left_share_fix) &&
                (!param->boundary.left_bend_fix)) {
                p->vc_Left[i][j][k].z = p->c[i][j][k].z;
                p->vc_Left[i][j][k].x =
                    p->c[i][j][k].x - p->li[i][j][k].vector.x;
                p->vc_Left[i][j][k].z =
                    p->c[i][j][k].z - p->li[i][j][k].vector.z;
            }
        }

        if (p->flag[i][j][k] == Right || p->flag[i][j][k] == RightBottom ||
            p->flag[i][j][k] == RightTop) {
            if (param->boundary.cylinder_boundary) {
                p->vc_Right[i][j][k].x =
                    p->c[i][j][k].x + p->li[i - 1][j][k].vector.x;
                p->vc_Right[i][j][k].y =
                    p->c[i][j][k].y - p->li[i - 1][j][k].vector.y;
                p->vc_Right[i][j][k].z = p->c[i][j][k].z;

            } else {
                p->vc_Right[i][j][k].x = -1 * p->c[i][j][k].x;
                p->vc_Right[i][j][k].y = p->c[i][j][k].y;
                p->vc_Right[i][j][k].z = p->c[i][j][k].z;
            }
            if (param->boundary.right_share_fix) {
                p->vc_Right[i][j][k].y = p->c[i][j][k].y;
                p->vc_Right[i][j][k].z = p->c[i][j][k].z;

            } else {
                // p->vc_Right[i][j][k].y	= p->c[i][j][k].y +
                // p->li[i-1][j][k].vector.y;
            }
            if (param->boundary.right_bend_fix) {
                p->vc_Right[i][j][k].y = p->c[i][j][k].y;
                p->vc_Right[i][j][k].z = p->c[i][j][k].z;

            } else {
                // p->vc_Right[i][j][k].z	= p->c[i][j][k].z +
                // p->li[i-1][j][k][j].vector.z;
            }

            if ((!param->boundary.right_share_fix) &&
                (!param->boundary.right_bend_fix)) {
                p->vc_Right[i][j][k].y =
                    p->c[i][j][k].y - p->li[i][j][k].vector.y;
                p->vc_Right[i][j][k].z =
                    p->c[i][j][k].z - p->li[i][j][k].vector.z;
            }
        }

        //////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////// Cylinder以外
        ////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////
    } else {
        // cout << "PLATE" << endl;
        if (!(p->surround_particle_exsit[i][j][k] & BIT_BOTTOM)) {
            // if (p->flag[i][j][k] == Bottom || p->flag[i][j][k] == LeftBottom
            // ||
            //     p->flag[i][j][k] == RightBottom) {
            if (param->boundary.bottom_share_fix) {
                p->vc_Bottom[i][j][k].x = p->c[i][j][k].x;
            } else {
                p->vc_Bottom[i][j][k].x =
                    p->c[i][j][k].x - p->lj[i][j][k].vector.x;
            }
            if (param->boundary.bottom_bend_fix) {
                p->vc_Bottom[i][j][k].z = p->c[i][j][k].z;
            } else {
                p->vc_Bottom[i][j][k].z =
                    p->c[i][j][k].z - p->lj[i][j][k].vector.z;
            }
            p->vc_Bottom[i][j][k].y = p->c[i][j][k].y - p->lj[i][j][k].vector.y;
        }

        if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
            // if (p->flag[i][j][k] == Top || p->flag[i][j][k] == LeftTop ||
            //     p->flag[i][j][k] == RightTop) {
            if (param->boundary.top_share_fix) {
                p->vc_Top[i][j][k].x = p->c[i][j][k].x;
            } else {
                p->vc_Top[i][j][k].x =
                    p->c[i][j][k].x + p->lj[i][j - 1][k].vector.x;
            }
            if (param->boundary.top_bend_fix) {
                p->vc_Top[i][j][k].z = p->c[i][j][k].z;
            } else {
                p->vc_Top[i][j][k].z =
                    p->c[i][j][k].z + p->lj[i][j - 1][k].vector.z;
            }
            p->vc_Top[i][j][k].y =
                p->c[i][j][k].y + p->lj[i][j - 1][k].vector.y;
        }

        if (!(p->surround_particle_exsit[i][j][k] & BIT_LEFT)) {
            // if (p->flag[i][j][k] == Left || p->flag[i][j][k] == LeftBottom ||
            //     p->flag[i][j][k] == LeftTop) {
            if (param->boundary.left_share_fix) {
                p->vc_Left[i][j][k].y = p->c[i][j][k].y;
            } else {
                p->vc_Left[i][j][k].y =
                    p->c[i][j][k].y - p->li[i][j][k].vector.y;
            }
            if (param->boundary.left_bend_fix) {
                p->vc_Left[i][j][k].z = p->c[i][j][k].z;
            } else {
                p->vc_Left[i][j][k].z =
                    p->c[i][j][k].z - p->li[i][j][k].vector.z;
            }
            p->vc_Left[i][j][k].x = p->c[i][j][k].x - p->li[i][j][k].vector.x;
        }

        if (!(p->surround_particle_exsit[i][j][k] & BIT_RIGHT)) {
            // if (p->flag[i][j][k] == Right || p->flag[i][j][k] == RightBottom
            // ||p->flag[i][j][k] == RightTop) {
            if (param->boundary.right_share_fix) {
                p->vc_Right[i][j][k].y = p->c[i][j][k].y;
            } else {
                p->vc_Right[i][j][k].y =
                    p->c[i][j][k].y + p->li[i - 1][j][k].vector.y;
            }

            if (param->boundary.right_bend_fix) {
                p->vc_Right[i][j][k].z = p->c[i][j][k].z;
            } else {
                p->vc_Right[i][j][k].z =
                    p->c[i][j][k].z + p->li[i - 1][j][k].vector.z;
            }

            p->vc_Right[i][j][k].x =
                p->c[i][j][k].x + p->li[i - 1][j][k].vector.x;
        }
    }
}

#endif
////////////////////////////////////////////
// Current function
////////////////////////////////////////////
void MultiParticle::VirtualParticleCalc(const int& i, const int& j,
                                        const int& k) {
    if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
        lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 1][j][k]);
#ifdef __CREASECALUCULATION__
            // if ((p->j_specialflag[i + 1][j][k] == 3) || (p->j_specialflag[i + 1][j][k] == 4)){
            //     lCalc(p->li[i][j][k], p->c[i][j][k], p->c[i + 2][j][k]);
            // }
            // if ((p->j_specialflag[i][j][k] == 3) || (p->j_specialflag[i][j][k] == 4)){
            //     lCalc(p->li[i][j][k], p->c[i - 1][j][k], p->c[i + 1][j][k]);
            // }
#endif //__CREASECALUCULATION__
    }
    if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
        lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j + 1][k]);
#ifdef __CREASECALUCULATION__
            // if ((p->i_specialflag[i][j + 1][k] == 3) || (p->i_specialflag[i][j + 1][k] == 4)){
            //     lCalc(p->lj[i][j][k], p->c[i][j][k], p->c[i][j + 2][k]);
            // }
            // if ((p->i_specialflag[i][j][k] == 3) || (p->i_specialflag[i][j][k] == 4)){
            //     lCalc(p->lj[i][j][k], p->c[i][j - 1][k], p->c[i][j + 1][k]);
            // }
#endif //__CREASECALUCULATION__
    }

    //////////////////////////////////////////////////////////////////////
    ////////////////////////* set virtual particle *////////////////////////////
    //////////////////////////////////////////////////////////////////////
    if (CylinderPressure) {
        // cout << "CYLINDER" << endl;
        if (p->flag[i][j][k] == Bottom || p->flag[i][j][k] == LeftBottom ||
            p->flag[i][j][k] == RightBottom) {
            p->vc_Bottom[i][j][k].z = p->c[i][j][k].z - p->lj[i][j][k].vector.z;
            p->vc_Bottom[i][j][k].x = p->c[i][j][k].x;
            p->vc_Bottom[i][j][k].y = p->c[i][j][k].y;

            if (param->boundary.bottom_share_fix) {
                p->vc_Bottom[i][j][k].x = p->c[i][j][k].x;
                p->vc_Bottom[i][j][k].y = p->c[i][j][k].y;
            } else {
                // p->vc_Bottom[i][j][k].x	= p->c[i][j][k].x -
                // p->lj[i][j][k].vector.x;
            }
            if (param->boundary.bottom_bend_fix) {
                p->vc_Bottom[i][j][k].x = p->c[i][j][k].x;
                p->vc_Bottom[i][j][k].y = p->c[i][j][k].y;
            } else {
                // p->vc_Bottom[i][j][k].z	= p->c[i][j][k].z -
                // p->lj[i][j][k].vector.z;
            }
            if ((!param->boundary.bottom_share_fix) &&
                (!param->boundary.bottom_bend_fix)) {
                p->vc_Bottom[i][j][k].x =
                    p->c[i][j][k].x - p->lj[i][j][k].vector.x;
                p->vc_Bottom[i][j][k].y =
                    p->c[i][j][k].y - p->lj[i][j][k].vector.y;
            }
        }

        if (p->flag[i][j][k] == Top || p->flag[i][j][k] == LeftTop ||
            p->flag[i][j][k] == RightTop) {
            p->vc_Top[i][j][k].z =
                p->c[i][j][k].z + p->lj[i][j - 1][k].vector.z;
            p->vc_Top[i][j][k].x = p->c[i][j][k].x;
            p->vc_Top[i][j][k].y = p->c[i][j][k].y;

            if (param->boundary.top_share_fix) {
                p->vc_Top[i][j][k].x = p->c[i][j][k].x;
                p->vc_Top[i][j][k].y = p->c[i][j][k].y;
            } else {
                // p->vc_Top[i][j][k].x		= p->c[i][j][k].x +
                // p->lj[i][j-1][k].vector.x;
            }
            if (param->boundary.top_bend_fix) {
                p->vc_Top[i][j][k].x = p->c[i][j][k].x;
                p->vc_Top[i][j][k].y = p->c[i][j][k].y;

            } else {
                // p->vc_Top[i][j][k].z		= p->c[i][j][k].z +
                // p->lj[i][j-1][k].vector.z;
            }
            if ((!param->boundary.top_share_fix) &&
                (!param->boundary.top_bend_fix)) {
                p->vc_Top[i][j][k].x =
                    p->c[i][j][k].x + p->lj[i][j - 1][k].vector.x;
                p->vc_Top[i][j][k].y =
                    p->c[i][j][k].y + p->lj[i][j - 1][k].vector.y;
            }
        }

        if (p->flag[i][j][k] == Left || p->flag[i][j][k] == LeftBottom ||
            p->flag[i][j][k] == LeftTop) {
            if (param->boundary.cylinder_boundary) {
                p->vc_Left[i][j][k].x =
                    p->c[i][j][k].x + p->li[i][j][k].vector.x;
                p->vc_Left[i][j][k].y =
                    p->c[i][j][k].y - p->li[i][j][k].vector.y;
                p->vc_Left[i][j][k].z = p->c[i][j][k].z;
            } else {
                p->vc_Left[i][j][k].x = p->c[i][j][k].x;
                p->vc_Left[i][j][k].y = -1 * p->c[i][j][k].y;
                p->vc_Left[i][j][k].z = p->c[i][j][k].z;
            }
            if (param->boundary.left_share_fix) {
                p->vc_Left[i][j][k].x = p->c[i][j][k].x;
                p->vc_Left[i][j][k].z = p->c[i][j][k].z;
            } else {
                // p->vc_Left[i][j][k].y = p->c[i][j][k].y -
                // p->li[i][j][k].vector.y;
            }
            if (param->boundary.left_bend_fix) {
                p->vc_Left[i][j][k].x = p->c[i][j][k].x;
                p->vc_Left[i][j][k].z = p->c[i][j][k].z;

            } else {
                // p->vc_Left[i][j][k].z		= p->c[i][j][k].z -
                // p->li[i][j][k].vector.z;
            }

            if ((!param->boundary.left_share_fix) &&
                (!param->boundary.left_bend_fix)) {
                p->vc_Left[i][j][k].z = p->c[i][j][k].z;
                p->vc_Left[i][j][k].x =
                    p->c[i][j][k].x - p->li[i][j][k].vector.x;
                p->vc_Left[i][j][k].z =
                    p->c[i][j][k].z - p->li[i][j][k].vector.z;
            }
        }

        if (p->flag[i][j][k] == Right || p->flag[i][j][k] == RightBottom ||
            p->flag[i][j][k] == RightTop) {
            if (param->boundary.cylinder_boundary) {
                p->vc_Right[i][j][k].x =
                    p->c[i][j][k].x + p->li[i - 1][j][k].vector.x;
                p->vc_Right[i][j][k].y =
                    p->c[i][j][k].y - p->li[i - 1][j][k].vector.y;
                p->vc_Right[i][j][k].z = p->c[i][j][k].z;

            } else {
                p->vc_Right[i][j][k].x = -1 * p->c[i][j][k].x;
                p->vc_Right[i][j][k].y = p->c[i][j][k].y;
                p->vc_Right[i][j][k].z = p->c[i][j][k].z;
            }
            if (param->boundary.right_share_fix) {
                p->vc_Right[i][j][k].y = p->c[i][j][k].y;
                p->vc_Right[i][j][k].z = p->c[i][j][k].z;

            } else {
                // p->vc_Right[i][j][k].y	= p->c[i][j][k].y +
                // p->li[i-1][j][k].vector.y;
            }
            if (param->boundary.right_bend_fix) {
                p->vc_Right[i][j][k].y = p->c[i][j][k].y;
                p->vc_Right[i][j][k].z = p->c[i][j][k].z;

            } else {
                // p->vc_Right[i][j][k].z	= p->c[i][j][k].z +
                // p->li[i-1][j][k][j].vector.z;
            }

            if ((!param->boundary.right_share_fix) &&
                (!param->boundary.right_bend_fix)) {
                p->vc_Right[i][j][k].y =
                    p->c[i][j][k].y - p->li[i][j][k].vector.y;
                p->vc_Right[i][j][k].z =
                    p->c[i][j][k].z - p->li[i][j][k].vector.z;
            }
        }

        //////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////// Cylinder以外
        ////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////
    } else {
        // cout << "PLATE" << endl;
        if (!(p->surround_particle_exsit[i][j][k] & BIT_BOTTOM)) {
            // if (p->flag[i][j][k] == Bottom || p->flag[i][j][k] == LeftBottom
            // ||
            //     p->flag[i][j][k] == RightBottom) {
            if (param->boundary.bottom_share_fix) {
                p->vc_Bottom[i][j][k].x = p->c[i][j][k].x;
            } else {
                p->vc_Bottom[i][j][k].x =
                    p->c[i][j][k].x - p->lj[i][j][k].vector.x;
            }
            if (param->boundary.bottom_bend_fix) {
                p->vc_Bottom[i][j][k].z = p->c[i][j][k].z;
            } else {
                p->vc_Bottom[i][j][k].z =
                    p->c[i][j][k].z - p->lj[i][j][k].vector.z;
            }
            p->vc_Bottom[i][j][k].y = p->c[i][j][k].y - p->lj[i][j][k].vector.y;
        }

        if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
            // if (p->flag[i][j][k] == Top || p->flag[i][j][k] == LeftTop ||
            //     p->flag[i][j][k] == RightTop) {
            if (param->boundary.top_share_fix) {
                p->vc_Top[i][j][k].x = p->c[i][j][k].x;
            } else {
                p->vc_Top[i][j][k].x =
                    p->c[i][j][k].x + p->lj[i][j - 1][k].vector.x;
            }
            if (param->boundary.top_bend_fix) {
                p->vc_Top[i][j][k].z = p->c[i][j][k].z;
            } else {
                p->vc_Top[i][j][k].z =
                    p->c[i][j][k].z + p->lj[i][j - 1][k].vector.z;
            }
            p->vc_Top[i][j][k].y =
                p->c[i][j][k].y + p->lj[i][j - 1][k].vector.y;
        }

        if (!(p->surround_particle_exsit[i][j][k] & BIT_LEFT)) {
            // if (p->flag[i][j][k] == Left || p->flag[i][j][k] == LeftBottom ||
            //     p->flag[i][j][k] == LeftTop) {
            if (param->boundary.left_share_fix) {
                p->vc_Left[i][j][k].y = p->c[i][j][k].y;
            } else {
                p->vc_Left[i][j][k].y =
                    p->c[i][j][k].y - p->li[i][j][k].vector.y;
            }
            if (param->boundary.left_bend_fix) {
                p->vc_Left[i][j][k].z = p->c[i][j][k].z;
            } else {
                p->vc_Left[i][j][k].z =
                    p->c[i][j][k].z - p->li[i][j][k].vector.z;
            }
            p->vc_Left[i][j][k].x = p->c[i][j][k].x - p->li[i][j][k].vector.x;
        }

        if (!(p->surround_particle_exsit[i][j][k] & BIT_RIGHT)) {
            // if (p->flag[i][j][k] == Right || p->flag[i][j][k] == RightBottom
            // ||p->flag[i][j][k] == RightTop) {
            if (param->boundary.right_share_fix) {
                p->vc_Right[i][j][k].y = p->c[i][j][k].y;
            } else {
                p->vc_Right[i][j][k].y =
                    p->c[i][j][k].y + p->li[i - 1][j][k].vector.y;
            }

            if (param->boundary.right_bend_fix) {
                p->vc_Right[i][j][k].z = p->c[i][j][k].z;
            } else {
                p->vc_Right[i][j][k].z =
                    p->c[i][j][k].z + p->li[i - 1][j][k].vector.z;
            }

            p->vc_Right[i][j][k].x =
                p->c[i][j][k].x + p->li[i - 1][j][k].vector.x;
        }
    }

    // if (!(p->surround_particle_exsit[i][j][k] & BIT_RIGHT)) {
    //     lCalc(p->li[i][j][k], p->c[i][j][k], p->vc_Right[i][j][k]);
    // }
    // if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
    //     lCalc(p->lj[i][j][k], p->c[i][j][k], p->vc_Top[i][j][k]);
    // }

    {
        int num       = 1;
        p->g[i][j][k] = p->c[i][j][k];
        if ((p->surround_particle_exsit[i][j][k] & BIT_RIGHT)) {
            num += 1;
#ifdef __CREASECALUCULATION__
            // if ((p->j_specialflag[i + 1][j][k] == 3) || (p->j_specialflag[i + 1][j][k] == 4)){
            //     p->g[i][j][k] += p->c[i + 2][j][k];
            // }
            // else{
                p->g[i][j][k] += p->c[i + 1][j][k];
            // }
#else // not crease
            p->g[i][j][k] += p->c[i + 1][j][k];
#endif //__CREASECALUCULATION__
        }
        if ((p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
            num += 1;
#ifdef __CREASECALUCULATION__
            // if ((p->i_specialflag[i][j + 1][k] == 3) || (p->i_specialflag[i][j + 1][k] == 4)){
            //     p->g[i][j][k] += p->c[i][j + 2][k];
            // }
            // else{
                p->g[i][j][k] += p->c[i][j + 1][k];
            // }
#else // not crease
            p->g[i][j][k] += p->c[i][j + 1][k];
#endif //__CREASECALUCULATION__
        }
        if ((p->surround_particle_exsit[i][j][k] & BIT_RIGHT) &&
            (p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
            num += 1;
#ifdef __CREASECALUCULATION__
//ここifの条件式違う気がする
            // if ((p->i_specialflag[i + 1][j + 1][k] == 3) || (p->i_specialflag[i + 1][j + 1][k] == 4)){
            //     p->g[i][j][k] += p->c[i + 1][j + 2][k];
            // }
            // else if ((p->j_specialflag[i + 1][j + 1][k] == 3) || (p->j_specialflag[i + 1][j + 1][k] == 4)){
            //    p->g[i][j][k] += p->c[i + 2][j + 1][k];
            // }
            // else{
                p->g[i][j][k] += p->c[i + 1][j + 1][k];
            // }
#else // not crease
            p->g[i][j][k] += p->c[i + 1][j + 1][k];
#endif //__CREASECALUCULATION__
        }
        // cout << i << "," << j << ',' << k << endl;
        p->g[i][j][k] /= num;
        // if (fabs(p->g[i][j][k].z) > 1E-3) {
        //     cout << i << "," << j << ',' << k << endl;
        //     cout << "num:" << num << endl;
        //     p->g[i][j][k].print();
        //     p->c[i][j][k].print();
        //     abort();
        // }

        //   if ((p->surround_particle_exsit[i][j][k] & BIT_RIGHT) &&
        //       (p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
        //     p->g[i][j][k] = ((p->c[i][j][k] + p->c[i + 1][j][k] +
        //                       p->c[i][j + 1][k] + p->c[i + 1][j + 1][k])
        //                       /
        //                      4);
        //   } else if (!(p->surround_particle_exsit[i][j][k] & BIT_RIGHT))
        //   {
        //     p->g[i][j][k] = ((p->c[i][j][k] + p->c[i][j + 1][k]) / 2);
        //   } else if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
        //     p->g[i][j][k] = ((p->c[i][j][k] + p->c[i + 1][j][k]) / 2);
        //   }
    }

    if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
        p->epsilonli[i][j][k] =
            epsilonlCulc(p->li[i][j][k].norm, p->li0[i][j][k]);
    }
    if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
        p->epsilonlj[i][j][k] =
            epsilonlCulc(p->lj[i][j][k].norm, p->lj0[i][j][k]);
    }
    //from here
    if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
        p->mi[i][j][k] = ((p->c[i][j][k] + p->c[i + 1][j][k]) / 2);
#ifdef __CREASECALUCULATION__
        // if ((p->j_specialflag[i + 1][j][k] == 3) || (p->j_specialflag[i + 1][j][k] == 4)){
        //     p->mi[i][j][k] = ((p->c[i][j][k] + p->c[i + 2][j][k]) / 2);
        // }
        // if ((p->j_specialflag[i][j][k] == 3) || (p->j_specialflag[i][j][k] == 4)){
        //     p->mi[i][j][k] = ((p->c[i - 1][j][k] + p->c[i + 1][j][k]) / 2);
        // }
#endif //__CREASECALUCULATION__
    } else {
        p->mi[i][j][k] = ((p->c[i][j][k] + p->vc_Right[i][j][k]) / 2);
    }

    if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
        p->mj[i][j][k] = ((p->c[i][j][k] + p->c[i][j + 1][k]) / 2);
#ifdef __CREASECALUCULATION__
        // if ((p->i_specialflag[i][j + 1][k] == 3) || (p->i_specialflag[i][j + 1][k] == 4)){
        //     p->mj[i][j][k] = ((p->c[i][j][k] + p->c[i][j + 2][k]) / 2);
        // }
        // if ((p->i_specialflag[i][j][k] == 3) || (p->i_specialflag[i][j][k] == 4)){
        //     p->mj[i][j][k] = ((p->c[i][j - 1][k] + p->c[i][j + 1][k]) / 2);
        // }
#endif //__CREASECALUCULATION__
    } else {
        p->mj[i][j][k] = ((p->c[i][j][k] + p->vc_Top[i][j][k]) / 2);
    }
}
