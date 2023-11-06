/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file	ForceCalc.hpp
 * @brief	各粒子に作用する力を計算する
 * @details
 * @par
 * ///////////////////////////////////////////////////////////////////////////////
 */

#if defined __SHAPE_CUBE__
void MultiParticle::ForceCalc(int const& i, int const& j, int const& k) {
    if (p->flag[i][j][k] & BIT_CEILING) {
        switch (p->flag[i][j][k]) {
            case (BIT_CEILING):

                p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i][j][k] +
                                     p->hi[i][j - 1][k] + p->hj[i - 1][j][k]) /
                                    4;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mj[i - 1][j][k])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i - 1][j][k], 1);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j - 1][k], 0);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j - 1][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i - 1][j][k].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i - 1][j][k].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i + 1][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i - 1][j][k]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i + 1][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i - 1][j][k]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i - 1][j][k].norm,
                                p->hj[i - 1][j][k]);
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i - 1][j][k].norm,
                                p->hj[i - 1][j][k]);

                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                     normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k])),
                    (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k]) +
                     normCalcV2(p->mj0[i][j][k], p->g0[i][j - 1][k])));
                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                     normCalcV2(p->mi[i][j][k], p->g[i - 1][j][k])),
                    (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                     normCalcV2(p->mi0[i][j][k], p->g0[i - 1][j][k])));

                //	l_gj = g(i+1/2, j+1/2)とmiの長さ + g(i+1/2,
                // j-1/2)とmiの長さ
                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                               normCalcV2(p->mi[i][j][k], p->g[i - 1][j][k]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                               normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);
                break;

            case (BIT_CEILING | BIT_RIGHT):
                // p->h_ave[i][j][k] = (p->hj[i][j][k] + p->hi[i][j - 1][k] +
                // p->hj[i - 1][j][k]) / 3;
                p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i][j][k] +
                                     p->hi[i][j - 1][k] + p->hj[i - 1][j][k]) /
                                    4;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mj[i - 1][j][k])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i - 1][j][k], 1);
                // p->Ij[i][j][k] = ((normCalcV2(p->c[i][j][k], p->mi[i][j -
                // 1][k])) * p->h_ave3[i][j][k]);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k - 1], p->c[i][j - 1][k], 0);
                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j - 1][k].norm,
                            p->li[i][j - 1][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i - 1][j][k].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);
                // 追加
                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                //
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i - 1][j][k].norm;
                // p->beta[i][j][k].pp = angleCalc(p->c[i][j][k],
                // p->vc_Right[i][j][k], p->c[i + 1][j][k]); p->beta[i][j][k].pm
                // = angleCalc(p->c[i][j][k], p->vc_Right[i][j][k], p->c[i -
                // 1][j][k]);
                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j][k - 1], p->c[i + 1][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j][k - 1], p->c[i - 1][j][k]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i + 1][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i - 1][j][k]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                // p->Fsi[i][j][k].pp = 0;
                // p->Fsi[i][j][k].pm = 0;
                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i - 1][j][k].norm,
                                p->hj[i - 1][j][k]);
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i - 1][j][k].norm,
                                p->hj[i - 1][j][k]);

                // p->epsilongi[i][j][k] =
                // epsilongCalc((normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k])),
                // (normCalcV2(p->mj0[i][j][k], p->g0[i][j - 1][k])));
                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                     normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k])),
                    (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k]) +
                     normCalcV2(p->mj0[i][j][k], p->g0[i][j - 1][k])));
                // p->epsilongj[i][j][k] = 0;
                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                     normCalcV2(p->mi[i][j][k], p->g[i - 1][j][k])),
                    (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                     normCalcV2(p->mi0[i][j][k], p->g0[i - 1][j][k])));

                // p->Fti[i][j][k] = 0;
                p->Fti[i][j][k] = FtCalc(
                    normCalcV2(p->g[i][j][k - 1], p->mi[i][j][k - 1]) +
                        normCalcV2(p->mi[i][j][k - 1], p->g[i - 1][j][k]),
                    p->hi[i][j][k - 1], p->epsilonli[i][j][k],
                    p->epsilongj[i][j][k - 1]);
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);
                break;

            case (BIT_CEILING | BIT_BOTTOM):
                // p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i][j][k] +
                // p->hi[i][j - 1][k]) / 3;
                p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i][j][k] +
                                     p->hi[i][j - 1][k] + p->hj[i][j][k - 1]) /
                                    4;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];
                // p->Ii[i][j][k] = ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]))
                // * p->h_ave3[i][j][k]);
                p->Ii[i][j][k] =
                    ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                // p->alphaj[i][j][k] = angleCalc2(p->c[i][j][k], p->c[i +
                // 1][j][k], p->vc_Bottom[i][j][k], 1);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j][k - 1], 1);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j - 1][k], 0);
                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j - 1][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                ///////// add //////////
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;
                ///
                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i + 1][j][k]);
                // p->beta[i][j][k].pm = angleCalc(p->c[i][j][k], p->c[i][j +
                // 1][k], p->vc_Bottom[i][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i + 1][j][k]);
                // p->beta[i][j][k].mm = angleCalc(p->c[i][j][k], p->c[i][j -
                // 1][k], p->vc_Bottom[i][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                // p->Fsj[i][j][k].pm = 0;
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                // p->Fsj[i][j][k].mm = 0;
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                     normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k])),
                    (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k]) +
                     normCalcV2(p->mj0[i][j][k], p->g0[i][j - 1][k])));
                // p->epsilongj[i][j][k] =
                // epsilongCalc((normCalcV2(p->g[i][j][k], p->mi[i][j][k])),
                // (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k])));
                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                     normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1])),
                    (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                     normCalcV2(p->mi0[i][j][k], p->g0[i][j][k - 1])));

                // p->Fti[i][j][k] = FtCalc(normCalcV2(p->g[i][j][k],
                // p->mi[i][j][k]), p->hi[i][j][k], p->epsilonli[i][j][k],
                // p->epsilongj[i][j][k]);
                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                               normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                               normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);
                break;

            case (BIT_CEILING | BIT_TOP):
                p->h_ave[i][j][k] =
                    (p->hi[i][j][k] + p->hi[i][j - 1][k] + p->hj[i - 1][j][k]) /
                    3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mj[i - 1][j][k])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Top[i][j][k], p->c[i - 1][j][k], 1);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j - 1][k], 0);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j - 1][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i - 1][j][k].norm,
                            p->lj[i - 1][j][k].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                p->Fb[i][j][k].jpv = 0;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i - 1][j][k].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i - 1][j][k]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i - 1][j][k]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp = 0;
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i - 1][j][k].norm,
                                p->hj[i - 1][j][k]);
                p->Fsj[i][j][k].mp = 0;
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i - 1][j][k].norm,
                                p->hj[i - 1][j][k]);

                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->mi[i][j][k], p->g[i - 1][j][k])),
                    (normCalcV2(p->mi0[i][j][k], p->g0[i - 1][j][k])));

                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->mi[i][j][k], p->g[i - 1][j][k]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] = 0;
                break;

            case (BIT_CEILING | BIT_LEFT):
                p->h_ave[i][j][k] =
                    (p->hi[i][j][k] + p->hj[i][j][k] + p->hj[i - 1][j][k]) / 3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mj[i - 1][j][k])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i - 1][j][k], 1);
                p->Ij[i][j][k]     = ((normCalcV2(p->mi[i][j][k], p->c[i][j][k])) *
                                  p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j + 1][k], p->vc_Left[i][j][k], 0);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i - 1][j][k].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv = 0;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i - 1][j][k].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i + 1][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i - 1][j][k]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->c[i + 1][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->c[i - 1][j][k]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp = 0;
                p->Fsi[i][j][k].mm = 0;
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i - 1][j][k].norm,
                                p->hj[i - 1][j][k]);
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i - 1][j][k].norm,
                                p->hj[i - 1][j][k]);

                p->epsilongi[i][j][k] =
                    epsilongCalc((normCalcV2(p->g[i][j][k], p->mj[i][j][k])),
                                 (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k])));
                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                     normCalcV2(p->mi[i][j][k], p->g[i - 1][j][k])),
                    (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                     normCalcV2(p->mi0[i][j][k], p->g0[i - 1][j][k])));

                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                               normCalcV2(p->mi[i][j][k], p->g[i - 1][j][k]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] = FtCalc(
                    normCalcV2(p->g[i][j][k], p->mj[i][j][k]), p->hj[i][j][k],
                    p->epsilonlj[i][j][k], p->epsilongi[i][j][k]);
                break;

            case (BIT_CEILING | BIT_LEFT | BIT_TOP):
                p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i - 1][j][k]) / 2;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mj[i - 1][j][k])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Top[i][j][k], p->c[i - 1][j][k], 1);
                p->Ij[i][j][k]     = ((normCalcV2(p->mi[i][j][k], p->c[i][j][k])) *
                                  p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j + 1][k], p->vc_Left[i][j][k], 0);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i - 1][j][k].norm,
                            p->lj[i - 1][j][k].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv = 0;
                p->Fb[i][j][k].jpv = 0;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i - 1][j][k].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i - 1][j][k]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->c[i - 1][j][k]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp = 0;
                p->Fsi[i][j][k].mm = 0;
                p->Fsj[i][j][k].pp = 0;
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i - 1][j][k].norm,
                                p->hj[i - 1][j][k]);
                p->Fsj[i][j][k].mp = 0;
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i - 1][j][k].norm,
                                p->hj[i - 1][j][k]);

                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                     normCalcV2(p->mi[i][j][k], p->g[i - 1][j][k])),
                    (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                     normCalcV2(p->mi0[i][j][k], p->g0[i - 1][j][k])));

                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                               normCalcV2(p->mi[i][j][k], p->g[i - 1][j][k]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] = 0;
                break;

            case (BIT_CEILING | BIT_LEFT | BIT_BOTTOM):
                // p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i][j][k]) / 2;
                p->h_ave[i][j][k] =
                    (p->hi[i][j][k] + p->hj[i][j][k] + p->hj[i][j][k - 1]) / 3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                // p->Ii[i][j][k] = ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]))
                // * p->h_ave3[i][j][k]);
                p->Ii[i][j][k] =
                    ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                // p->alphaj[i][j][k] = angleCalc2(p->c[i][j][k], p->c[i +
                // 1][j][k], p->vc_Bottom[i][j][k], 1);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j][k - 1], 1);
                p->Ij[i][j][k]     = ((normCalcV2(p->mi[i][j][k], p->c[i][j][k])) *
                                  p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j + 1][k], p->vc_Left[i][j][k], 0);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j][k].norm);
                // p->etaj[i][j][k] = etaCalc(p->alphaj[i][j][k],
                // p->lj[i][j][k].norm, p->lj[i][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);
                ///////// add //////////
                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv = 0;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;
                /////
                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i + 1][j][k]);
                // p->beta[i][j][k].pm = angleCalc(p->c[i][j][k], p->c[i][j +
                // 1][k], p->vc_Bottom[i][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->c[i + 1][j][k]);
                // p->beta[i][j][k].mm = angleCalc(p->c[i][j][k],
                // p->vc_Left[i][j][k], p->vc_Bottom[i][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp = 0;
                p->Fsi[i][j][k].mm = 0;
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                // p->Fsj[i][j][k].pm = 0;
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                // p->Fsj[i][j][k].mm = 0;
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                p->epsilongi[i][j][k] =
                    epsilongCalc((normCalcV2(p->g[i][j][k], p->mj[i][j][k])),
                                 (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k])));
                // p->epsilongj[i][j][k] =
                // epsilongCalc((normCalcV2(p->g[i][j][k], p->mi[i][j][k])),
                // (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k])));
                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                     normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1])),
                    (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                     normCalcV2(p->mi0[i][j][k], p->g0[i][j][k - 1])));
                // p->Fti[i][j][k] = FtCalc(normCalcV2(p->g[i][j][k],
                // p->mi[i][j][k]), p->hi[i][j][k], p->epsilonli[i][j][k],
                // p->epsilongj[i][j][k]);
                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                               normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] = FtCalc(
                    normCalcV2(p->g[i][j][k], p->mj[i][j][k]), p->hj[i][j][k],
                    p->epsilonlj[i][j][k], p->epsilongi[i][j][k]);
                break;

            case (BIT_CEILING | BIT_RIGHT | BIT_BOTTOM):
                // p->h_ave[i][j][k] = (p->hj[i][j][k] + p->hi[i][j - 1][k]) /
                // 2;
                p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i][j][k] +
                                     p->hi[i][j - 1][k] + p->hj[i][j][k - 1]) /
                                    4;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                // p->Ii[i][j][k] = ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]))
                // * p->h_ave3[i][j][k]);
                p->Ii[i][j][k] =
                    ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                // p->alphaj[i][j][k] = angleCalc2(p->c[i][j][k], p->c[i +
                // 1][j][k], p->vc_Bottom[i][j][k], 1);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j][k - 1], 1);
                // p->Ij[i][j][k] = ((normCalcV2(p->c[i][j][k], p->mi[i][j -
                // 1][k])) * p->h_ave3[i][j][k]);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                // p->alphai[i][j][k] = angleCalc2(p->c[i][j][k],
                // p->vc_Right[i][j][k], p->c[i][j - 1][k], 0);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k - 1], p->c[i][j - 1][k], 0);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j - 1][k].norm,
                            p->li[i][j - 1][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);
                ///////// add //////////
                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;
                //////
                // p->beta[i][j][k].pp = angleCalc(p->c[i][j][k],
                // p->vc_Right[i][j][k], p->c[i + 1][j][k]);
                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j][k - 1], p->c[i + 1][j][k]);
                // p->beta[i][j][k].pm = angleCalc(p->c[i][j][k],
                // p->vc_Right[i][j][k], p->vc_Bottom[i][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j][k - 1], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i + 1][j][k]);
                // p->beta[i][j][k].mm = angleCalc(p->c[i][j][k], p->c[i][j -
                // 1][k], p->vc_Bottom[i][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                // p->Fsi[i][j][k].pp = 0;
                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                // p->Fsi[i][j][k].pm = 0;
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                // p->Fsj[i][j][k].pm = 0;
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                // p->Fsj[i][j][k].mm = 0;
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                // p->epsilongi[i][j][k] =
                // epsilongCalc((normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k])),
                // (normCalcV2(p->mj0[i][j][k], p->g0[i][j - 1][k])));
                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                     normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k])),
                    (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k]) +
                     normCalcV2(p->mj0[i][j][k], p->g0[i][j - 1][k])));
                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                     normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1])),
                    (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                     normCalcV2(p->mi0[i][j][k], p->g0[i][j][k - 1])));
                // p->Fti[i][j][k] = 0;
                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                               normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                // p->Ftj[i][j][k] = FtCalc(normCalcV2(p->mj[i][j][k], p->g[i][j
                // - 1][k]), p->hj[i][j][k], p->epsilonlj[i][j][k],
                // p->epsilongi[i][j][k]);
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                               normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);
                break;

            case (BIT_CEILING | BIT_RIGHT | BIT_TOP):
                // p->h_ave[i][j][k] = (p->hi[i][j - 1][k] + p->hj[i - 1][j][k])
                // / 2;
                p->h_ave[i][j][k] =
                    (p->hi[i][j][k] + p->hi[i][j - 1][k] + p->hj[i][j][k - 1]) /
                    3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                // p->Ii[i][j][k] = ((normCalcV2(p->c[i][j][k], p->mj[i -
                // 1][j][k])) * p->h_ave3[i][j][k]);
                p->Ii[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mj[i - 1][j][k])) *
                     p->h_ave3[i][j][k]);
                // p->alphaj[i][j][k] = angleCalc2(p->c[i][j][k],
                // p->vc_Top[i][j][k], p->c[i - 1][j][k], 1);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Top[i][j][k], p->c[i - 1][j][k], 1);
                // p->Ij[i][j][k] = ((normCalcV2(p->c[i][j][k], p->mi[i][j -
                // 1][k])) * p->h_ave3[i][j][k]);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                // p->alphai[i][j][k] = angleCalc2(p->c[i][j][k],
                // p->vc_Right[i][j][k], p->c[i][j - 1][k], 0);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k - 1], p->c[i][j - 1][k], 0);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j - 1][k].norm);
                // p->etaj[i][j][k] = etaCalc(p->alphaj[i][j][k], p->lj[i -
                // 1][j][k].norm, p->lj[i - 1][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i - 1][j][k].norm,
                            p->lj[i - 1][j][k].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);
                ////// add ////
                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                p->Fb[i][j][k].jpv = 0;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i - 1][j][k].norm;
                /////
                // p->beta[i][j][k].pp = angleCalc(p->c[i][j][k],
                // p->vc_Right[i][j][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j][k - 1], p->vc_Top[i][j][k]);
                // p->beta[i][j][k].pm = angleCalc(p->c[i][j][k],
                // p->vc_Right[i][j][k], p->c[i - 1][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j][k - 1], p->c[i - 1][j][k]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i - 1][j][k]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                // p->Fsi[i][j][k].pp = 0;
                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                // p->Fsi[i][j][k].pm = 0;
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp = 0;
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i - 1][j][k].norm,
                                p->hj[i - 1][j][k]);
                p->Fsj[i][j][k].mp = 0;
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i - 1][j][k].norm,
                                p->hj[i - 1][j][k]);
                ///////// add //////////
                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->mi[i][j][k], p->g[i - 1][j][k])),
                    (normCalcV2(p->mi0[i][j][k], p->g0[i - 1][j][k])));
                ////

                // p->Fti[i][j][k] = 0;
                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->mi[i][j][k], p->g[i - 1][j][k]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] = 0;
                break;
        }
    } else if (p->flag[i][j][k] & BIT_BACK) {
        switch (p->flag[i][j][k]) {
            case (BIT_BACK):

                p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i][j][k] +
                                     p->hi[i - 1][j][k] + p->hj[i][j][k - 1]) /
                                    4;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k + 1], p->c[i][j][k - 1], 3);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i - 1][j][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i - 1][j][k], 2);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i - 1][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i - 1][j][k].norm;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i - 1][j][k].norm,
                                p->hi[i - 1][j][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i - 1][j][k].norm,
                                p->hi[i - 1][j][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                     normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k])),
                    (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k]) +
                     normCalcV2(p->mj0[i][j][k], p->g0[i - 1][j][k])));
                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                     normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1])),
                    (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                     normCalcV2(p->mi0[i][j][k], p->g0[i][j][k - 1])));

                //	l_gj = g(i+1/2, j+1/2)とmiの長さ + g(i+1/2,
                // j-1/2)とmiの長さ
                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                               normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                               normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);
                break;

            case (BIT_BACK | BIT_RIGHT):
                p->h_ave[i][j][k] =
                    (p->hj[i][j][k] + p->hi[i - 1][j][k] + p->hj[i][j][k - 1]) /
                    3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k + 1], p->c[i][j][k - 1], 3);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mi[i - 1][j][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i - 1][j][k], 2);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i - 1][j][k].norm,
                            p->li[i - 1][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = 0;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i - 1][j][k].norm;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp = 0;
                p->Fsi[i][j][k].pm = 0;
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i - 1][j][k].norm,
                                p->hi[i - 1][j][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i - 1][j][k].norm,
                                p->hi[i - 1][j][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k])),
                    (normCalcV2(p->mj0[i][j][k], p->g0[i - 1][j][k])));

                p->Fti[i][j][k] = 0;
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);
                break;

            case (BIT_BACK | BIT_BOTTOM):
                p->h_ave[i][j][k] =
                    (p->hi[i][j][k] + p->hj[i][j][k] + p->hi[i - 1][j][k]) / 3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k]     = ((normCalcV2(p->mj[i][j][k], p->c[i][j][k])) *
                                  p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k + 1], p->vc_Bottom[i][j][k], 3);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i - 1][j][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i - 1][j][k], 2);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i - 1][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i - 1][j][k].norm;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv = 0;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i + 1][j][k], p->vc_Bottom[i][j][k]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i - 1][j][k], p->vc_Bottom[i][j][k]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i - 1][j][k].norm,
                                p->hi[i - 1][j][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i - 1][j][k].norm,
                                p->hi[i - 1][j][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm = 0;
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm = 0;

                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                     normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k])),
                    (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k]) +
                     normCalcV2(p->mj0[i][j][k], p->g0[i - 1][j][k])));
                p->epsilongj[i][j][k] =
                    epsilongCalc((normCalcV2(p->g[i][j][k], p->mi[i][j][k])),
                                 (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k])));

                p->Fti[i][j][k] = FtCalc(
                    normCalcV2(p->g[i][j][k], p->mi[i][j][k]), p->hi[i][j][k],
                    p->epsilonli[i][j][k], p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                               normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);
                break;

            case (BIT_BACK | BIT_TOP):
                p->h_ave[i][j][k] =
                    (p->hi[i][j][k] + p->hi[i - 1][j][k] + p->hj[i][j][k - 1]) /
                    3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Top[i][j][k], p->c[i][j][k - 1], 3);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i - 1][j][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i - 1][j][k], 2);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i - 1][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k - 1].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i - 1][j][k].norm;
                p->Fb[i][j][k].jpv = 0;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i + 1][j][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i - 1][j][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i - 1][j][k].norm,
                                p->hi[i - 1][j][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i - 1][j][k].norm,
                                p->hi[i - 1][j][k]);
                p->Fsj[i][j][k].pp = 0;
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp = 0;
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1])),
                    (normCalcV2(p->mi0[i][j][k], p->g0[i][j][k - 1])));

                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] = 0;
                break;

            case (BIT_BACK | BIT_LEFT):
                p->h_ave[i][j][k] =
                    (p->hi[i][j][k] + p->hj[i][j][k] + p->hj[i][j][k - 1]) / 3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k + 1], p->c[i][j][k - 1], 3);
                // p->Ij[i][j][k] = ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]))
                // * p->h_ave3[i][j][k]);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                // p->alphai[i][j][k] = angleCalc2(p->c[i][j][k], p->c[i +
                // 1][j][k], p->vc_Left[i][j][k], 2);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j - 1][k], 2);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                ///////// add //////////
                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                //////////////////////
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j][k - 1]);
                // p->beta[i][j][k].mp = angleCalc(p->c[i][j][k],
                // p->vc_Left[i][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i][j][k + 1]);
                // p->beta[i][j][k].mm = angleCalc(p->c[i][j][k],
                // p->vc_Left[i][j][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                // p->Fsi[i][j][k].mp = 0;
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                // p->Fsi[i][j][k].mm = 0;
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                // p->epsilongi[i][j][k] =
                // epsilongCalc((normCalcV2(p->g[i][j][k], p->mj[i][j][k])),
                // (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k])));
                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                     normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k])),
                    (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k]) +
                     normCalcV2(p->mj0[i][j][k], p->g0[i][j - 1][k])));
                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                     normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1])),
                    (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                     normCalcV2(p->mi0[i][j][k], p->g0[i][j][k - 1])));

                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                               normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                // p->Ftj[i][j][k] = FtCalc(normCalcV2(p->g[i][j][k],
                // p->mj[i][j][k]), p->hj[i][j][k], p->epsilonlj[i][j][k],
                // p->epsilongi[i][j][k]);
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                               normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);
                break;

            case (BIT_BACK | BIT_LEFT | BIT_TOP):
                // ここには入らない
                // p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i][j][k - 1]) /
                // 2;
                p->h_ave[i][j][k] =
                    (p->hi[i][j][k] + p->hi[i][j - 1][k] + p->hj[i][j][k - 1]) /
                    3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Top[i][j][k], p->c[i][j][k - 1], 3);
                p->Ij[i][j][k] = ((normCalcV2(p->mi[i][j][k], p->c[i][j][k])) *
                                  p->h_ave3[i][j][k]);
                // p->alphai[i][j][k] = angleCalc2(p->c[i][j][k], p->c[i +
                // 1][j][k], p->vc_Left[i][j][k], 2);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j - 1][k], 2);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k - 1].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);
                ///////////// add /////////////
                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                p->Fb[i][j][k].jpv = 0;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;
                /////////////////
                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i + 1][j][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp = 0;
                p->Fsi[i][j][k].mm = 0;
                p->Fsj[i][j][k].pp = 0;
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp = 0;
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                     normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1])),
                    (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                     normCalcV2(p->mi0[i][j][k], p->g0[i][j][k - 1])));

                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                               normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] = 0;
                break;

            case (BIT_BACK | BIT_LEFT | BIT_BOTTOM):
                // p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i][j][k]) / 2;
                p->h_ave[i][j][k] =
                    (p->hi[i][j][k] + p->hj[i][j][k] + p->hi[i][j - 1][k]) / 3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k]     = ((normCalcV2(p->mj[i][j][k], p->c[i][j][k])) *
                                  p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k + 1], p->vc_Bottom[i][j][k], 3);
                // p->Ij[i][j][k] = ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]))
                // * p->h_ave3[i][j][k]);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                // p->alphai[i][j][k] = angleCalc2(p->c[i][j][k], p->c[i +
                // 1][j][k], p->vc_Left[i][j][k], 2);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j - 1][k], 2);

                // p->etai[i][j][k] = etaCalc(p->alphai[i][j][k],
                // p->li[i][j][k].norm, p->li[i][j][k].norm);
                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j - 1][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);
                ///////// add //////////
                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv = 0;
                ///////////////////
                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i + 1][j][k], p->vc_Bottom[i][j][k]);
                // p->beta[i][j][k].mp = angleCalc(p->c[i][j][k],
                // p->vc_Left[i][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i][j][k + 1]);
                // p->beta[i][j][k].mm = angleCalc(p->c[i][j][k],
                // p->vc_Left[i][j][k], p->vc_Bottom[i][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->vc_Bottom[i][j][k]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                // p->Fsi[i][j][k].mp = 0;
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                // p->Fsi[i][j][k].mm = 0;
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm = 0;
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm = 0;
                p->epsilongj[i][j][k] =
                    epsilongCalc((normCalcV2(p->g[i][j][k], p->mi[i][j][k])),
                                 (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k])));
                // p->epsilongi[i][j][k] =
                // epsilongCalc((normCalcV2(p->g[i][j][k], p->mj[i][j][k])),
                // (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k])));
                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                     normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k])),
                    (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k]) +
                     normCalcV2(p->mj0[i][j][k], p->g0[i][j - 1][k])));
                p->Fti[i][j][k] = FtCalc(
                    normCalcV2(p->g[i][j][k], p->mi[i][j][k]), p->hi[i][j][k],
                    p->epsilonli[i][j][k], p->epsilongj[i][j][k]);
                // p->Ftj[i][j][k] = FtCalc(normCalcV2(p->g[i][j][k],
                // p->mj[i][j][k]), p->hj[i][j][k], p->epsilonlj[i][j][k],
                // p->epsilongi[i][j][k]);
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                               normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);

                break;

            case (BIT_BACK | BIT_RIGHT | BIT_BOTTOM):
                p->h_ave[i][j][k] = (p->hj[i][j][k] + p->hi[i - 1][j][k]) / 2;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k]     = ((normCalcV2(p->mj[i][j][k], p->c[i][j][k])) *
                                  p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k + 1], p->vc_Bottom[i][j][k], 3);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mi[i - 1][j][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i - 1][j][k], 2);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i - 1][j][k].norm,
                            p->li[i - 1][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = 0;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i - 1][j][k].norm;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv = 0;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->vc_Bottom[i][j][k]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i - 1][j][k], p->vc_Bottom[i][j][k]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp = 0;
                p->Fsi[i][j][k].pm = 0;
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i - 1][j][k].norm,
                                p->hi[i - 1][j][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i - 1][j][k].norm,
                                p->hi[i - 1][j][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm = 0;
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm    = 0;
                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k])),
                    (normCalcV2(p->mj0[i][j][k], p->g0[i - 1][j][k])));
                p->Fti[i][j][k] = 0;
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);
                break;

            case (BIT_BACK | BIT_RIGHT | BIT_TOP):
                p->h_ave[i][j][k] =
                    (p->hi[i - 1][j][k] + p->hj[i][j][k - 1]) / 2;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Top[i][j][k], p->c[i][j][k - 1], 3);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mi[i - 1][j][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i - 1][j][k], 2);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i - 1][j][k].norm,
                            p->li[i - 1][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k - 1].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = 0;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i - 1][j][k].norm;
                p->Fb[i][j][k].jpv = 0;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i - 1][j][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp = 0;
                p->Fsi[i][j][k].pm = 0;
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i - 1][j][k].norm,
                                p->hi[i - 1][j][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i - 1][j][k].norm,
                                p->hi[i - 1][j][k]);
                p->Fsj[i][j][k].pp = 0;
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp = 0;
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                p->Fti[i][j][k] = 0;
                p->Ftj[i][j][k] = 0;
                break;
        }
    } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
        switch (p->flag[i][j][k]) {
            case (BIT_RIGHTSIDE):

                p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i][j][k] +
                                     p->hi[i][j - 1][k] + p->hj[i][j][k - 1]) /
                                    4;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k + 1], p->c[i][j][k - 1], 5);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j - 1][k], 4);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j - 1][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                     normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k])),
                    (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k]) +
                     normCalcV2(p->mj0[i][j][k], p->g0[i][j - 1][k])));
                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                     normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1])),
                    (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                     normCalcV2(p->mi0[i][j][k], p->g0[i][j][k - 1])));

                //	l_gj = g(i+1/2, j+1/2)とmiの長さ + g(i+1/2,
                // j-1/2)とmiの長さ
                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                               normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                               normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);
                break;

            case (BIT_RIGHTSIDE | BIT_RIGHT):
                p->h_ave[i][j][k] =
                    (p->hj[i][j][k] + p->hi[i][j - 1][k] + p->hj[i][j][k - 1]) /
                    3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k + 1], p->c[i][j][k - 1], 5);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i][j - 1][k], 4);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j - 1][k].norm,
                            p->li[i][j - 1][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = 0;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp = 0;
                p->Fsi[i][j][k].pm = 0;
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k])),
                    (normCalcV2(p->mj0[i][j][k], p->g0[i][j - 1][k])));

                p->Fti[i][j][k] = 0;
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);
                break;

            case (BIT_RIGHTSIDE | BIT_BOTTOM):
                p->h_ave[i][j][k] =
                    (p->hi[i][j][k] + p->hj[i][j][k] + p->hi[i][j - 1][k]) / 3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k]     = ((normCalcV2(p->mj[i][j][k], p->c[i][j][k])) *
                                  p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k + 1], p->vc_Bottom[i][j][k], 5);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j - 1][k], 4);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j - 1][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv = 0;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->vc_Bottom[i][j][k]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->vc_Bottom[i][j][k]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm = 0;
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm = 0;

                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                     normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k])),
                    (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k]) +
                     normCalcV2(p->mj0[i][j][k], p->g0[i][j - 1][k])));
                p->epsilongj[i][j][k] =
                    epsilongCalc((normCalcV2(p->g[i][j][k], p->mi[i][j][k])),
                                 (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k])));

                p->Fti[i][j][k] = FtCalc(
                    normCalcV2(p->g[i][j][k], p->mi[i][j][k]), p->hi[i][j][k],
                    p->epsilonli[i][j][k], p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                               normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);
                break;

            case (BIT_RIGHTSIDE | BIT_TOP):
                p->h_ave[i][j][k] =
                    (p->hi[i][j][k] + p->hi[i][j - 1][k] + p->hj[i][j][k - 1]) /
                    3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Top[i][j][k], p->c[i][j][k - 1], 5);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j - 1][k], 4);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j - 1][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k - 1].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                p->Fb[i][j][k].jpv = 0;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp = 0;
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp = 0;
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1])),
                    (normCalcV2(p->mi0[i][j][k], p->g0[i][j][k - 1])));

                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] = 0;
                break;

            case (BIT_RIGHTSIDE | BIT_LEFT):
                p->h_ave[i][j][k] =
                    (p->hi[i][j][k] + p->hj[i][j][k] + p->hj[i][j][k - 1]) / 3;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]) +
                      normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k + 1], p->c[i][j][k - 1], 5);
                p->Ij[i][j][k]     = ((normCalcV2(p->mi[i][j][k], p->c[i][j][k])) *
                                  p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j + 1][k], p->vc_Left[i][j][k], 4);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv = 0;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp = 0;
                p->Fsi[i][j][k].mm = 0;
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                p->epsilongi[i][j][k] =
                    epsilongCalc((normCalcV2(p->g[i][j][k], p->mj[i][j][k])),
                                 (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k])));
                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                     normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1])),
                    (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                     normCalcV2(p->mi0[i][j][k], p->g0[i][j][k - 1])));

                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                               normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] = FtCalc(
                    normCalcV2(p->g[i][j][k], p->mj[i][j][k]), p->hj[i][j][k],
                    p->epsilonlj[i][j][k], p->epsilongi[i][j][k]);
                break;

            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_TOP):
                p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i][j][k - 1]) / 2;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Top[i][j][k], p->c[i][j][k - 1], 5);
                p->Ij[i][j][k]     = ((normCalcV2(p->mi[i][j][k], p->c[i][j][k])) *
                                  p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j + 1][k], p->vc_Left[i][j][k], 4);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k - 1].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv = 0;
                p->Fb[i][j][k].jpv = 0;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp = 0;
                p->Fsi[i][j][k].mm = 0;
                p->Fsj[i][j][k].pp = 0;
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp = 0;
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                p->epsilongj[i][j][k] = epsilongCalc(
                    (normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                     normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1])),
                    (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                     normCalcV2(p->mi0[i][j][k], p->g0[i][j][k - 1])));

                p->Fti[i][j][k] =
                    FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                               normCalcV2(p->mi[i][j][k], p->g[i][j][k - 1]),
                           p->hi[i][j][k], p->epsilonli[i][j][k],
                           p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] = 0;
                break;

            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_BOTTOM):
                p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i][j][k]) / 2;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k]     = ((normCalcV2(p->mj[i][j][k], p->c[i][j][k])) *
                                  p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k + 1], p->vc_Bottom[i][j][k], 5);
                p->Ij[i][j][k]     = ((normCalcV2(p->mi[i][j][k], p->c[i][j][k])) *
                                  p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j + 1][k], p->vc_Left[i][j][k], 4);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                            p->li[i][j][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
                p->Fb[i][j][k].imv = 0;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv = 0;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->c[i][j + 1][k], p->vc_Bottom[i][j][k]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->vc_Left[i][j][k], p->vc_Bottom[i][j][k]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                                p->hi[i][j][k]);
                p->Fsi[i][j][k].mp = 0;
                p->Fsi[i][j][k].mm = 0;
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm = 0;
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm = 0;
                p->epsilongi[i][j][k] =
                    epsilongCalc((normCalcV2(p->g[i][j][k], p->mj[i][j][k])),
                                 (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k])));
                p->epsilongj[i][j][k] =
                    epsilongCalc((normCalcV2(p->g[i][j][k], p->mi[i][j][k])),
                                 (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k])));
                p->Fti[i][j][k] = FtCalc(
                    normCalcV2(p->g[i][j][k], p->mi[i][j][k]), p->hi[i][j][k],
                    p->epsilonli[i][j][k], p->epsilongj[i][j][k]);
                p->Ftj[i][j][k] = FtCalc(
                    normCalcV2(p->g[i][j][k], p->mj[i][j][k]), p->hj[i][j][k],
                    p->epsilonlj[i][j][k], p->epsilongi[i][j][k]);
                break;

            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_BOTTOM):
                p->h_ave[i][j][k] = (p->hj[i][j][k] + p->hi[i][j - 1][k]) / 2;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k]     = ((normCalcV2(p->mj[i][j][k], p->c[i][j][k])) *
                                  p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->c[i][j][k + 1], p->vc_Bottom[i][j][k], 5);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i][j - 1][k], 4);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j - 1][k].norm,
                            p->li[i][j - 1][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                            p->lj[i][j][k].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = 0;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
                p->Fb[i][j][k].jmv = 0;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->vc_Bottom[i][j][k]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i][j][k + 1]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->vc_Bottom[i][j][k]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp = 0;
                p->Fsi[i][j][k].pm = 0;
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp =
                    -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].pm = 0;
                p->Fsj[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                                p->hj[i][j][k]);
                p->Fsj[i][j][k].mm    = 0;
                p->epsilongi[i][j][k] = epsilongCalc(
                    (normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k])),
                    (normCalcV2(p->mj0[i][j][k], p->g0[i][j - 1][k])));
                p->Fti[i][j][k] = 0;
                p->Ftj[i][j][k] =
                    FtCalc(normCalcV2(p->mj[i][j][k], p->g[i][j - 1][k]),
                           p->hj[i][j][k], p->epsilonlj[i][j][k],
                           p->epsilongi[i][j][k]);
                break;

            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_TOP):
                p->h_ave[i][j][k] =
                    (p->hi[i][j - 1][k] + p->hj[i][j][k - 1]) / 2;
                p->h_ave3[i][j][k] =
                    p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

                p->Ii[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mj[i][j][k - 1])) *
                     p->h_ave3[i][j][k]);
                p->alphaj[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Top[i][j][k], p->c[i][j][k - 1], 5);
                p->Ij[i][j][k] =
                    ((normCalcV2(p->c[i][j][k], p->mi[i][j - 1][k])) *
                     p->h_ave3[i][j][k]);
                p->alphai[i][j][k] = angleCalc2(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i][j - 1][k], 4);

                p->etai[i][j][k] =
                    etaCalc(p->alphai[i][j][k], p->li[i][j - 1][k].norm,
                            p->li[i][j - 1][k].norm);
                p->etaj[i][j][k] =
                    etaCalc(p->alphaj[i][j][k], p->lj[i][j][k - 1].norm,
                            p->lj[i][j][k - 1].norm);

                p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
                p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

                p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                       p->diff_etaj[i][j][k]);
                p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                       p->diff_etai[i][j][k]);

                p->Fb[i][j][k].ipv = 0;
                p->Fb[i][j][k].imv =
                    -1 * p->Mi[i][j][k] / p->li[i][j - 1][k].norm;
                p->Fb[i][j][k].jpv = 0;
                p->Fb[i][j][k].jmv =
                    -1 * p->Mj[i][j][k] / p->lj[i][j][k - 1].norm;

                p->beta[i][j][k].pp = angleCalc(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].pm = angleCalc(
                    p->c[i][j][k], p->vc_Right[i][j][k], p->c[i][j][k - 1]);
                p->beta[i][j][k].mp = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->vc_Top[i][j][k]);
                p->beta[i][j][k].mm = angleCalc(
                    p->c[i][j][k], p->c[i][j - 1][k], p->c[i][j][k - 1]);
                p->gamma[i][j][k].pp =
                    gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
                p->gamma[i][j][k].pm =
                    gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
                p->gamma[i][j][k].mp =
                    gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
                p->gamma[i][j][k].mm =
                    gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

                p->Fsi[i][j][k].pp = 0;
                p->Fsi[i][j][k].pm = 0;
                p->Fsi[i][j][k].mp =
                    -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsi[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i][j - 1][k].norm,
                                p->hi[i][j - 1][k]);
                p->Fsj[i][j][k].pp = 0;
                p->Fsj[i][j][k].pm =
                    -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);
                p->Fsj[i][j][k].mp = 0;
                p->Fsj[i][j][k].mm =
                    -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j][k - 1].norm,
                                p->hj[i][j][k - 1]);

                p->Fti[i][j][k] = 0;
                p->Ftj[i][j][k] = 0;
                break;
        }
    }

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// EDGE処理
///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
#ifdef Thicken
    if (p->flag[i][j][k] & BIT_CEILING) {
        if ((p->flag[i][j][k] & BIT_BOTTOM) || (p->flag[i][j][k] & BIT_RIGHT)) {
            p->Mi[i][j][k] /= param->thicken_coefficient;
            p->Mj[i][j][k] /= param->thicken_coefficient;

            p->Fb[i][j][k].ipv /= param->thicken_coefficient;
            p->Fb[i][j][k].imv /= param->thicken_coefficient;
            p->Fb[i][j][k].jpv /= param->thicken_coefficient;
            p->Fb[i][j][k].jmv /= param->thicken_coefficient;

            p->Fsi[i][j][k].pp /= param->thicken_coefficient;
            p->Fsi[i][j][k].pm /= param->thicken_coefficient;
            p->Fsi[i][j][k].mp /= param->thicken_coefficient;
            p->Fsi[i][j][k].mm /= param->thicken_coefficient;
            p->Fsj[i][j][k].pp /= param->thicken_coefficient;
            p->Fsj[i][j][k].pm /= param->thicken_coefficient;
            p->Fsj[i][j][k].mp /= param->thicken_coefficient;
            p->Fsj[i][j][k].mm /= param->thicken_coefficient;

            p->Fti[i][j][k] /= param->thicken_coefficient;
            p->Ftj[i][j][k] /= param->thicken_coefficient;
        }
    } else if (p->flag[i][j][k] & BIT_BACK) {
        if (p->flag[i][j][k] & BIT_LEFT) {
            p->Mi[i][j][k] /= param->thicken_coefficient;
            p->Mj[i][j][k] /= param->thicken_coefficient;

            p->Fb[i][j][k].ipv /= param->thicken_coefficient;
            p->Fb[i][j][k].imv /= param->thicken_coefficient;
            p->Fb[i][j][k].jpv /= param->thicken_coefficient;
            p->Fb[i][j][k].jmv /= param->thicken_coefficient;

            p->Fsi[i][j][k].pp /= param->thicken_coefficient;
            p->Fsi[i][j][k].pm /= param->thicken_coefficient;
            p->Fsi[i][j][k].mp /= param->thicken_coefficient;
            p->Fsi[i][j][k].mm /= param->thicken_coefficient;
            p->Fsj[i][j][k].pp /= param->thicken_coefficient;
            p->Fsj[i][j][k].pm /= param->thicken_coefficient;
            p->Fsj[i][j][k].mp /= param->thicken_coefficient;
            p->Fsj[i][j][k].mm /= param->thicken_coefficient;

            p->Fti[i][j][k] /= param->thicken_coefficient;
            p->Ftj[i][j][k] /= param->thicken_coefficient;
        }
    }
#endif
#ifdef EDGE_REINFORCE
    if (p->flag[i][j][k] & BIT_CEILING) {
        if (p->flag[i][j][k] & BIT_RIGHT) {
            p->Fb[i][j][k].ipv *= param->edge_reinforce;
        }

        if (p->flag[i][j][k] & BIT_BOTTOM) {
            p->Fb[i][j][k].jmv *= param->edge_reinforce;
        }
    } else if (p->flag[i][j][k] & BIT_BACK) {
        if (p->flag[i][j][k] & BIT_LEFT) {
            p->Fb[i][j][k].imv *= param->edge_reinforce;
        }
    }
#endif
}

//////////////////////////////////////////////////////////////
/////////////////////// Cube以外  ////////////////////////////
//////////////////////////////////////////////////////////////
/////////////////////////// 2d  //////////////////////////////
//////////////////////////////////////////////////////////////
#else

/**
 * @brief		Calclate force per particles.
 * (各粒子での力とそれを求めるために必要な値を計算する)
 * @param[in]	int i
 * @param[in]	int j
 * @param[in] 	int k
 * @details	 	各粒子での以下の値を求める
 * 					膜厚 hの平均
 * 					断面二次モーメント I
 * 					曲げ角度 α
 * 					曲率 η
 * 					曲げモーメント M
 * 					曲げ力 Fb
 * 					せん断角度 β
 * 					せん断ひずみ γ
 * 					せん断力 Fs
 * 					垂直ひずみ ε
 * 					伸縮力 Ft
 */
void MultiParticle::ForceCalc(int const& i, int const& j, int const& k) {
#ifdef __DEBUG__
    cout << "Run Force Calc" << endl;
    cout << i << "," << j << "," << k << endl;
#endif

    switch (p->flag[i][j][k]) {
        case Center:

            p->h_ave[i][j][k] = (p->hi[i][j][k] + p->hj[i][j][k] +
                                 p->hi[i - 1][j][k] + p->hj[i][j - 1][k]) /
                                4;
            p->h_ave3[i][j][k] =
                p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];

            p->Ii[i][j][k]     = ((normCalcV2(p->mj[i][j][k], p->c[i][j][k]) +
                               normCalcV2(p->c[i][j][k], p->mj[i][j - 1][k])) *
                              p->h_ave3[i][j][k]);
            p->alphaj[i][j][k] = angleCalc2(p->c[i][j][k], p->c[i][j + 1][k],
                                            p->c[i][j - 1][k], 1);
            p->Ij[i][j][k]     = ((normCalcV2(p->mi[i][j][k], p->c[i][j][k]) +
                               normCalcV2(p->c[i][j][k], p->mi[i - 1][j][k])) *
                              p->h_ave3[i][j][k]);
            p->alphai[i][j][k] = angleCalc2(p->c[i][j][k], p->c[i + 1][j][k],
                                            p->c[i - 1][j][k], 0);

            p->etai[i][j][k] = etaCalc(p->alphai[i][j][k], p->li[i][j][k].norm,
                                       p->li[i - 1][j][k].norm);
            p->etaj[i][j][k] = etaCalc(p->alphaj[i][j][k], p->lj[i][j][k].norm,
                                       p->lj[i][j - 1][k].norm);

            p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
            p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

            p->Mi[i][j][k] = MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k],
                                   p->diff_etaj[i][j][k]);
            p->Mj[i][j][k] = MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k],
                                   p->diff_etai[i][j][k]);

            p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
            p->Fb[i][j][k].imv = -1 * p->Mi[i][j][k] / p->li[i - 1][j][k].norm;
            p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
            p->Fb[i][j][k].jmv = -1 * p->Mj[i][j][k] / p->lj[i][j - 1][k].norm;

            p->beta[i][j][k].pp =
                angleCalc(p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j + 1][k]);
            p->beta[i][j][k].pm =
                angleCalc(p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j - 1][k]);
            p->beta[i][j][k].mp =
                angleCalc(p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j + 1][k]);
            p->beta[i][j][k].mm =
                angleCalc(p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j - 1][k]);
            p->gamma[i][j][k].pp =
                gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
            p->gamma[i][j][k].pm =
                gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
            p->gamma[i][j][k].mp =
                gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
            p->gamma[i][j][k].mm =
                gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

            p->Fsi[i][j][k].pp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                            p->hi[i][j][k]);
            p->Fsi[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                            p->hi[i][j][k]);
            p->Fsi[i][j][k].mp =
                -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i - 1][j][k].norm,
                            p->hi[i - 1][j][k]);
            p->Fsi[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i - 1][j][k].norm,
                            p->hi[i - 1][j][k]);
            p->Fsj[i][j][k].pp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                            p->hj[i][j][k]);
            p->Fsj[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j - 1][k].norm,
                            p->hj[i][j - 1][k]);
            p->Fsj[i][j][k].mp =
                -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                            p->hj[i][j][k]);
            p->Fsj[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j - 1][k].norm,
                            p->hj[i][j - 1][k]);

            p->epsilongi[i][j][k] =
                epsilongCalc((normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                              normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k])),
                             (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k]) +
                              normCalcV2(p->mj0[i][j][k], p->g0[i - 1][j][k])));
            p->epsilongj[i][j][k] =
                epsilongCalc((normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                              normCalcV2(p->mi[i][j][k], p->g[i][j - 1][k])),
                             (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                              normCalcV2(p->mi0[i][j][k], p->g0[i][j - 1][k])));

            //	l_gj = g(i+1/2, j+1/2)とmiの長さ + g(i+1/2, j-1/2)とmiの長さ
            p->Fti[i][j][k] = FtCalc(
                normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                    normCalcV2(p->mi[i][j][k], p->g[i][j - 1][k]),
                p->hi[i][j][k], p->epsilonli[i][j][k], p->epsilongj[i][j][k]);
            p->Ftj[i][j][k] = FtCalc(
                normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                    normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k]),
                p->hj[i][j][k], p->epsilonlj[i][j][k], p->epsilongi[i][j][k]);
            break;

        case Right:
#ifdef __CYLINDER_PRESSURE__
#ifdef __CYLINDER_BOUNDARY__
            p->Fb[i][j][k].ipv = 0;
            p->Fb[i][j][k].imv = -1 * p->Mi[i][j][k] / p->li[i - 1][j][k].norm;
#elif defined __CYLINDER_NON_BOUNDARY__
            lCalc(p->tmp.vec, p->c[i][j][k], p->vc_Right[i][j][k]);
            p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->tmp.vec.norm;
            p->Fb[i][j][k].imv = -1 * p->Mi[i][j][k] / p->li[i - 1][j][k].norm;
#endif
            p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
            p->Fb[i][j][k].jmv = -1 * p->Mj[i][j][k] / p->lj[i][j - 1][k].norm;
#endif

            p->beta[i][j][k].pp = angleCalc(p->c[i][j][k], p->vc_Right[i][j][k],
                                            p->c[i][j + 1][k]);
            p->beta[i][j][k].pm = angleCalc(p->c[i][j][k], p->vc_Right[i][j][k],
                                            p->c[i][j - 1][k]);
            p->beta[i][j][k].mp =
                angleCalc(p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j + 1][k]);
            p->beta[i][j][k].mm =
                angleCalc(p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j - 1][k]);
            p->gamma[i][j][k].pp =
                gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
            p->gamma[i][j][k].pm =
                gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
            p->gamma[i][j][k].mp =
                gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
            p->gamma[i][j][k].mm =
                gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);
#ifdef __CYLINDER_PRESSURE__
#ifdef __CYLINDER_BOUNDARY__
            p->Fsi[i][j][k].pp = 0;
            p->Fsi[i][j][k].pm = 0;
#elif defined __CYLINDER_NON_BOUNDARY__
            p->Fsi[i][j][k].pp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->omp[i][j][k].li.norm,
                            p->omp[i][j][k].hi);
            p->Fsi[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->omp[i][j][k].li.norm,
                            p->omp[i][j][k].hi);
            // lCalc(p->tmp.vec, p->c[i][j][k], p->vc_Right[i][j][k]);
            // p->Fsi[i][j][k].pp = -1 * FsCalc(p->gamma[i][j][k].pp,
            // p->tmp.vec.norm, p->hi[i][j][k]); p->Fsi[i][j][k].pm = -1 *
            // FsCalc(p->gamma[i][j][k].pm, p->tmp.vec.norm, p->hi[i][j][k]);
#endif
#endif

            p->Fsi[i][j][k].mp =
                -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i - 1][j][k].norm,
                            p->hi[i - 1][j][k]);
            p->Fsi[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i - 1][j][k].norm,
                            p->hi[i - 1][j][k]);
            p->Fsj[i][j][k].pp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                            p->hj[i][j][k]);
            p->Fsj[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j - 1][k].norm,
                            p->hj[i][j - 1][k]);
            p->Fsj[i][j][k].mp =
                -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                            p->hj[i][j][k]);
            p->Fsj[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j - 1][k].norm,
                            p->hj[i][j - 1][k]);

            p->epsilongi[i][j][k] =
                epsilongCalc((normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k])),
                             (normCalcV2(p->mj0[i][j][k], p->g0[i - 1][j][k])));
// Ftの場合分け
#ifdef __CYLINDER_PRESSURE__
#ifdef __CYLINDER_BOUNDARY__
            p->Fti[i][j][k] = 0;
#elif defined __CYLINDER_NON_BOUNDARY__
            p->omp[i][j][k].epsilongj = epsilongCalc(
                (normCalcV2(p->omp[i][j][k].g, p->omp[i][j][k].mi) +
                 normCalcV2(p->omp[i][j][k].mi, p->omp[i][j - 1][k].g)),
                (normCalcV2(p->omp[i][j][k].g0, p->omp[i][j][k].mi0) +
                 normCalcV2(p->omp[i][j][k].mi0, p->omp[i][j - 1][k].g0)));
            p->omp[i][j][k].Fti = FtCalc(
                normCalcV2(p->omp[i][j][k].g, p->omp[i][j][k].mi) +
                    normCalcV2(p->omp[i][j][k].mi, p->omp[i][j - 1][k].g),
                p->omp[i][j][k].hi, p->omp[i][j][k].epsilonli,
                p->omp[i][j][k].epsilongj);
            // p->Fti[i][j][k] = FtCalc(normCalcV2(p->g[i][j][k],
            // p->mi[i][j][k]) + normCalcV2(p->mi[i][j][k], p->g[i][j - 1][k]),
            // p->hi[i][j][k], p->epsilonli[i][j][k], p->epsilongj[i][j][k]);
#endif
#endif
            p->Ftj[i][j][k] = FtCalc(
                normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k]), p->hj[i][j][k],
                p->epsilonlj[i][j][k], p->epsilongi[i][j][k]);
            break;

        case Bottom:
#ifdef __CYLINDER_PRESSURE__
            p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
            p->Fb[i][j][k].jmv = 0;
#endif

            p->beta[i][j][k].pp =
                angleCalc(p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j + 1][k]);
            p->beta[i][j][k].pm = angleCalc(p->c[i][j][k], p->c[i + 1][j][k],
                                            p->vc_Bottom[i][j][k]);
            p->beta[i][j][k].mp =
                angleCalc(p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j + 1][k]);
            p->beta[i][j][k].mm = angleCalc(p->c[i][j][k], p->c[i - 1][j][k],
                                            p->vc_Bottom[i][j][k]);
            p->gamma[i][j][k].pp =
                gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
            p->gamma[i][j][k].pm =
                gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
            p->gamma[i][j][k].mp =
                gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
            p->gamma[i][j][k].mm =
                gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

            p->Fsi[i][j][k].pp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                            p->hi[i][j][k]);
            p->Fsi[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                            p->hi[i][j][k]);
            p->Fsi[i][j][k].mp =
                -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i - 1][j][k].norm,
                            p->hi[i - 1][j][k]);
            p->Fsi[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i - 1][j][k].norm,
                            p->hi[i - 1][j][k]);
            p->Fsj[i][j][k].pp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                            p->hj[i][j][k]);
            p->Fsj[i][j][k].pm = 0;
            p->Fsj[i][j][k].mp =
                -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                            p->hj[i][j][k]);
            p->Fsj[i][j][k].mm = 0;

            p->epsilongi[i][j][k] =
                epsilongCalc((normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                              normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k])),
                             (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k]) +
                              normCalcV2(p->mj0[i][j][k], p->g0[i - 1][j][k])));
            p->epsilongj[i][j][k] =
                epsilongCalc((normCalcV2(p->g[i][j][k], p->mi[i][j][k])),
                             (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k])));

            p->Fti[i][j][k] = FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]),
                                     p->hi[i][j][k], p->epsilonli[i][j][k],
                                     p->epsilongj[i][j][k]);
            p->Ftj[i][j][k] = FtCalc(
                normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                    normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k]),
                p->hj[i][j][k], p->epsilonlj[i][j][k], p->epsilongi[i][j][k]);
            break;

        case Top:

#ifdef __CYLINDER_PRESSURE__
            p->Fb[i][j][k].jpv = 0;
            p->Fb[i][j][k].jmv = -1 * p->Mj[i][j][k] / p->lj[i][j - 1][k].norm;
#endif

            p->beta[i][j][k].pp =
                angleCalc(p->c[i][j][k], p->c[i + 1][j][k], p->vc_Top[i][j][k]);
            p->beta[i][j][k].pm =
                angleCalc(p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j - 1][k]);
            p->beta[i][j][k].mp =
                angleCalc(p->c[i][j][k], p->c[i - 1][j][k], p->vc_Top[i][j][k]);
            p->beta[i][j][k].mm =
                angleCalc(p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j - 1][k]);
            p->gamma[i][j][k].pp =
                gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
            p->gamma[i][j][k].pm =
                gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
            p->gamma[i][j][k].mp =
                gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
            p->gamma[i][j][k].mm =
                gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

            p->Fsi[i][j][k].pp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                            p->hi[i][j][k]);
            p->Fsi[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                            p->hi[i][j][k]);
            p->Fsi[i][j][k].mp =
                -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i - 1][j][k].norm,
                            p->hi[i - 1][j][k]);
            p->Fsi[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i - 1][j][k].norm,
                            p->hi[i - 1][j][k]);
            p->Fsj[i][j][k].pp = 0;
            p->Fsj[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j - 1][k].norm,
                            p->hj[i][j - 1][k]);
            p->Fsj[i][j][k].mp = 0;
            p->Fsj[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j - 1][k].norm,
                            p->hj[i][j - 1][k]);

            p->epsilongj[i][j][k] =
                epsilongCalc((normCalcV2(p->mi[i][j][k], p->g[i][j - 1][k])),
                             (normCalcV2(p->mi0[i][j][k], p->g0[i][j - 1][k])));

            p->Fti[i][j][k] = FtCalc(
                normCalcV2(p->mi[i][j][k], p->g[i][j - 1][k]), p->hi[i][j][k],
                p->epsilonli[i][j][k], p->epsilongj[i][j][k]);
            p->Ftj[i][j][k] = 0;
            break;

        case Left:
#ifdef __CYLINDER_PRESSURE__
#ifdef __CYLINDER_BOUNDARY__
            p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
            p->Fb[i][j][k].imv = 0;
#elif defined __CYLINDER_NON_BOUNDARY__
            lCalc(p->tmp.vec, p->vc_Left[i][j][k], p->c[i][j][k]);
            p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
            p->Fb[i][j][k].imv = -1 * p->Mi[i][j][k] / p->tmp.vec.norm;
#endif
            p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
            p->Fb[i][j][k].jmv = -1 * p->Mj[i][j][k] / p->lj[i][j - 1][k].norm;
#endif

            p->beta[i][j][k].pp =
                angleCalc(p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j + 1][k]);
            p->beta[i][j][k].pm =
                angleCalc(p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j - 1][k]);
            p->beta[i][j][k].mp = angleCalc(p->c[i][j][k], p->vc_Left[i][j][k],
                                            p->c[i][j + 1][k]);
            p->beta[i][j][k].mm = angleCalc(p->c[i][j][k], p->vc_Left[i][j][k],
                                            p->c[i][j - 1][k]);
            p->gamma[i][j][k].pp =
                gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
            p->gamma[i][j][k].pm =
                gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
            p->gamma[i][j][k].mp =
                gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
            p->gamma[i][j][k].mm =
                gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

            p->Fsi[i][j][k].pp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                            p->hi[i][j][k]);
            p->Fsi[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                            p->hi[i][j][k]);
#ifdef __CYLINDER_PRESSURE__
#ifdef __CYLINDER_BOUNDARY__
            p->Fsi[i][j][k].mp = 0;
            p->Fsi[i][j][k].mm = 0;
#elif defined __CYLINDER_NON_BOUNDARY__
            p->Fsi[i][j][k].mp =
                -1 * FsCalc(p->gamma[i][j][k].mp, p->omp[i][j][k].li.norm,
                            p->omp[i][j][k].hi);
            p->Fsi[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].mm, p->omp[i][j][k].li.norm,
                            p->omp[i][j][k].hi);
            // lCalc(p->tmp.vec, p->vc_Left[i][j][k], p->c[i][j][k]);
            // p->Fsi[i][j][k].mp = -1 * FsCalc(p->gamma[i][j][k].pp,
            // p->tmp.vec.norm, p->hi[i][j][k]); p->Fsi[i][j][k].mm = -1 *
            // FsCalc(p->gamma[i][j][k].pm, p->tmp.vec.norm, p->hi[i][j][k]);
#endif
#endif
            p->Fsj[i][j][k].pp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                            p->hj[i][j][k]);
            p->Fsj[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j - 1][k].norm,
                            p->hj[i][j - 1][k]);
            p->Fsj[i][j][k].mp =
                -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                            p->hj[i][j][k]);
            p->Fsj[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j - 1][k].norm,
                            p->hj[i][j - 1][k]);

            p->epsilongi[i][j][k] =
                epsilongCalc((normCalcV2(p->g[i][j][k], p->mj[i][j][k])),
                             (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k])));
            p->epsilongj[i][j][k] =
                epsilongCalc((normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                              normCalcV2(p->mi[i][j][k], p->g[i][j - 1][k])),
                             (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                              normCalcV2(p->mi0[i][j][k], p->g0[i][j - 1][k])));
            p->Fti[i][j][k] = FtCalc(
                normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                    normCalcV2(p->mi[i][j][k], p->g[i][j - 1][k]),
                p->hi[i][j][k], p->epsilonli[i][j][k], p->epsilongj[i][j][k]);
            p->Ftj[i][j][k]           = FtCalc(normCalcV2(p->g[i][j][k], p->mj[i][j][k]),
                                               p->hj[i][j][k], p->epsilonlj[i][j][k],
                                               p->epsilongi[i][j][k]);
#ifdef __CYLINDER_NON_BOUNDARY__
            p->omp[i][j][k].epsilongj = epsilongCalc(
                (normCalcV2(p->omp[i][j][k].g, p->omp[i][j][k].mi) +
                 normCalcV2(p->omp[i][j][k].mi, p->omp[i][j - 1][k].g)),
                (normCalcV2(p->omp[i][j][k].g0, p->omp[i][j][k].mi0) +
                 normCalcV2(p->omp[i][j][k].mi0, p->omp[i][j - 1][k].g0)));
            p->omp[i][j][k].Fti = FtCalc(
                normCalcV2(p->omp[i][j][k].g, p->omp[i][j][k].mi) +
                    normCalcV2(p->omp[i][j][k].mi, p->omp[i][j - 1][k].g),
                p->omp[i][j][k].hi, p->omp[i][j][k].epsilonli,
                p->omp[i][j][k].epsilongj);
#endif
            break;

        case LeftTop:
#ifdef __CYLINDER_PRESSURE__
#ifdef __CYLINDER_BOUNDARY__
            p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
            p->Fb[i][j][k].imv = 0;
#elif defined __CYLINDER_NON_BOUNDARY__
            lCalc(p->tmp.vec, p->vc_Left[i][j][k], p->c[i][j][k]);
            p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
            p->Fb[i][j][k].imv = -1 * p->Mi[i][j][k] / p->tmp.vec.norm;
#endif
            p->Fb[i][j][k].jpv = 0;
            p->Fb[i][j][k].jmv = -1 * p->Mj[i][j][k] / p->lj[i][j - 1][k].norm;
#endif

            p->beta[i][j][k].pp =
                angleCalc(p->c[i][j][k], p->c[i + 1][j][k], p->vc_Top[i][j][k]);
            p->beta[i][j][k].pm =
                angleCalc(p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j - 1][k]);
            p->beta[i][j][k].mp = angleCalc(p->c[i][j][k], p->vc_Left[i][j][k],
                                            p->vc_Top[i][j][k]);
            p->beta[i][j][k].mm = angleCalc(p->c[i][j][k], p->vc_Left[i][j][k],
                                            p->c[i][j - 1][k]);
            p->gamma[i][j][k].pp =
                gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
            p->gamma[i][j][k].pm =
                gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
            p->gamma[i][j][k].mp =
                gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
            p->gamma[i][j][k].mm =
                gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

            p->Fsi[i][j][k].pp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                            p->hi[i][j][k]);
            p->Fsi[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                            p->hi[i][j][k]);
#ifdef __CYLINDER_PRESSURE__
#ifdef __CYLINDER_BOUNDARY__
            p->Fsi[i][j][k].mp = 0;
            p->Fsi[i][j][k].mm = 0;
#elif defined __CYLINDER_NON_BOUNDARY__
            p->Fsi[i][j][k].mp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->omp[i][j][k].li.norm,
                            p->omp[i][j][k].hi);
            p->Fsi[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->omp[i][j][k].li.norm,
                            p->omp[i][j][k].hi);
            // lCalc(p->tmp.vec, p->vc_Left[i][j][k], p->c[i][j][k]);
            // p->Fsi[i][j][k].mp = -1 * FsCalc(p->gamma[i][j][k].pp,
            // p->tmp.vec.norm, p->hi[i][j][k]); p->Fsi[i][j][k].mm = -1 *
            // FsCalc(p->gamma[i][j][k].pm, p->tmp.vec.norm, p->hi[i][j][k]);
#endif
#endif
            p->Fsj[i][j][k].pp = 0;
            p->Fsj[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j - 1][k].norm,
                            p->hj[i][j - 1][k]);
            p->Fsj[i][j][k].mp = 0;
            p->Fsj[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j - 1][k].norm,
                            p->hj[i][j - 1][k]);

            p->epsilongj[i][j][k] =
                epsilongCalc((normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                              normCalcV2(p->mi[i][j][k], p->g[i][j - 1][k])),
                             (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]) +
                              normCalcV2(p->mi0[i][j][k], p->g0[i][j - 1][k])));

            p->Fti[i][j][k] =
                FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]) +
                           normCalcV2(p->mi[i][j][k], p->g[i][j - 1][k]),
                       p->hi[i][j][k], p->epsilonli[i][j][k],
                       p->omp[i][j][k].epsilongj);
            p->Ftj[i][j][k]           = 0;
#ifdef __CYLINDER_NON_BOUNDARY__
            p->omp[i][j][k].epsilongj = epsilongCalc(
                (normCalcV2(p->omp[i][j][k].mi, p->omp[i][j - 1][k].g)),
                (normCalcV2(p->omp[i][j][k].mi0, p->omp[i][j - 1][k].g0)));
            p->omp[i][j][k].Fti =
                FtCalc(normCalcV2(p->omp[i][j][k].g, p->omp[i][j][k].mi),
                       p->omp[i][j][k].hi, p->omp[i][j][k].epsilonli,
                       p->epsilongj[i][j][k]);
#endif
            break;

        case LeftBottom:
#ifdef __CYLINDER_PRESSURE__
#ifdef __CYLINDER_BOUNDARY__
            p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
            p->Fb[i][j][k].imv = 0;
#elif defined __CYLINDER_NON_BOUNDARY__
            lCalc(p->tmp.vec, p->vc_Left[i][j][k], p->c[i][j][k]);
            p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
            p->Fb[i][j][k].imv = -1 * p->Mi[i][j][k] / p->tmp.vec.norm;
#endif
            p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
            p->Fb[i][j][k].jmv = 0;
#endif

            p->beta[i][j][k].pp =
                angleCalc(p->c[i][j][k], p->c[i + 1][j][k], p->c[i][j + 1][k]);
            p->beta[i][j][k].pm = angleCalc(p->c[i][j][k], p->c[i + 1][j][k],
                                            p->vc_Bottom[i][j][k]);
            p->beta[i][j][k].mp = angleCalc(p->c[i][j][k], p->vc_Left[i][j][k],
                                            p->c[i][j + 1][k]);
            p->beta[i][j][k].mm = angleCalc(p->c[i][j][k], p->vc_Left[i][j][k],
                                            p->vc_Bottom[i][j][k]);
            p->gamma[i][j][k].pp =
                gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
            p->gamma[i][j][k].pm =
                gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
            p->gamma[i][j][k].mp =
                gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
            p->gamma[i][j][k].mm =
                gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

            p->Fsi[i][j][k].pp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->li[i][j][k].norm,
                            p->hi[i][j][k]);
            p->Fsi[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->li[i][j][k].norm,
                            p->hi[i][j][k]);
#ifdef __CYLINDER_PRESSURE__
#ifdef __CYLINDER_BOUNDARY__
            p->Fsi[i][j][k].mp = 0;
            p->Fsi[i][j][k].mm = 0;
#elif defined __CYLINDER_NON_BOUNDARY__
            p->Fsi[i][j][k].mp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->omp[i][j][k].li.norm,
                            p->omp[i][j][k].hi);
            p->Fsi[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->omp[i][j][k].li.norm,
                            p->omp[i][j][k].hi);
            // lCalc(p->tmp.vec, p->vc_Left[i][j][k], p->c[i][j][k]);
            // p->Fsi[i][j][k].mp = -1 * FsCalc(p->gamma[i][j][k].pp,
            // p->tmp.vec.norm, p->hi[i][j][k]); p->Fsi[i][j][k].mm = -1 *
            // FsCalc(p->gamma[i][j][k].pm, p->tmp.vec.norm, p->hi[i][j][k]);
#endif
#endif
            p->Fsj[i][j][k].pp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->lj[i][j][k].norm,
                            p->hj[i][j][k]);
            p->Fsj[i][j][k].pm = 0;
            p->Fsj[i][j][k].mp =
                -1 * FsCalc(p->gamma[i][j][k].mp, p->lj[i][j][k].norm,
                            p->hj[i][j][k]);
            p->Fsj[i][j][k].mm = 0;
            p->epsilongi[i][j][k] =
                epsilongCalc((normCalcV2(p->g[i][j][k], p->mj[i][j][k])),
                             (normCalcV2(p->g0[i][j][k], p->mj0[i][j][k])));
            p->epsilongj[i][j][k] =
                epsilongCalc((normCalcV2(p->g[i][j][k], p->mi[i][j][k])),
                             (normCalcV2(p->g0[i][j][k], p->mi0[i][j][k])));
            p->Fti[i][j][k]           = FtCalc(normCalcV2(p->g[i][j][k], p->mi[i][j][k]),
                                               p->hi[i][j][k], p->epsilonli[i][j][k],
                                               p->epsilongj[i][j][k]);
            p->Ftj[i][j][k]           = FtCalc(normCalcV2(p->g[i][j][k], p->mj[i][j][k]),
                                               p->hj[i][j][k], p->epsilonlj[i][j][k],
                                               p->epsilongi[i][j][k]);
#ifdef __CYLINDER_NON_BOUNDARY__
            p->omp[i][j][k].epsilongj = epsilongCalc(
                (normCalcV2(p->omp[i][j][k].g, p->omp[i][j][k].mi)),
                (normCalcV2(p->omp[i][j][k].g0, p->omp[i][j][k].mi0)));
            p->omp[i][j][k].Fti =
                FtCalc(normCalcV2(p->omp[i][j][k].g, p->omp[i][j][k].mi),
                       p->omp[i][j][k].hi, p->omp[i][j][k].epsilonli,
                       p->omp[i][j][k].epsilongj);
#endif
            break;

        case RightBottom:
            // p->h_av

#ifdef __CYLINDER_PRESSURE__
#ifdef __CYLINDER_BOUNDARY__
            p->Fb[i][j][k].ipv = 0;
            p->Fb[i][j][k].imv = -1 * p->Mi[i][j][k] / p->li[i - 1][j][k].norm;
#elif defined __CYLINDER_NON_BOUNDARY__
            lCalc(p->tmp.vec, p->c[i][j][k], p->vc_Right[i][j][k]);
            p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->tmp.vec.norm;
            p->Fb[i][j][k].imv = -1 * p->Mi[i][j][k] / p->li[i - 1][j][k].norm;
#endif
            p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
            p->Fb[i][j][k].jmv = 0;
#endif

            p->beta[i][j][k].pp = angleCalc(p->c[i][j][k], p->vc_Right[i][j][k],
                                            p->c[i][j + 1][k]);
            p->beta[i][j][k].pm = angleCalc(p->c[i][j][k], p->vc_Right[i][j][k],
                                            p->vc_Bottom[i][j][k]);
            p->beta[i][j][k].mp =
                angleCalc(p->c[i][j][k], p->c[i - 1][j][k], p->c[i][j + 1][k]);
            p->beta[i][j][k].mm = angleCalc(p->c[i][j][k], p->c[i - 1][j][k],
                                            p->vc_Bottom[i][j][k]);
            p->gamma[i][j][k].pp =
                gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
            p->gamma[i][j][k].pm =
                gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
            p->gamma[i][j][k].mp =
                gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
            p->gamma[i][j][k].mm =
                gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

#ifdef __CYLINDER_PRESSURE__
#ifdef __CYLINDER_BOUNDARY__
            p->Fsi[i][j][k].pp = 0;
            p->Fsi[i][j][k].pm = 0;
#elif defined __CYLINDER_NON_BOUNDARY__
            p->Fsi[i][j][k].pp =
                -1 * FsCalc(p->gamma[i][j][k].pp, p->omp[i][j][k].li.norm,
                            p->omp[i][j][k].hi);
            p->Fsi[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->omp[i][j][k].li.norm,
                            p->omp[i][j][k].hi);
            // lCalc(p->tmp.vec, p->c[i][j][k], p->vc_Right[i][j][k]);
            // p->Fsi[i][j][k].pp = -1 * FsCalc(p->gamma[i][j][k].pp,
            // p->tmp.vec.norm, p->hi[i][j][k]); p->Fsi[i][j][k].pm = -1 *
            // FsCalc(p->gamma[i][j][k].pm, p->tmp.vec.norm, p->hi[i][j][k]);
#endif
#endif
            p->Fsi[i][j][k].mp =
                -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i - 1][j][k].norm,
                            p->hi[i - 1][j][k]);
            p->Fsi[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i - 1][j][k].norm,
                            p->hi[i - 1][j][k]);
            p->Fsj[i][j][k].pp = 0;
            p->Fsj[i][j][k].pm =
                -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j - 1][k].norm,
                            p->hj[i][j - 1][k]);
            p->Fsj[i][j][k].mp = 0;
            p->Fsj[i][j][k].mm =
                -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j - 1][k].norm,
                            p->hj[i][j - 1][k]);

            if (CylinderPressure) {
                if (param->boundary.cylinder_boundary) {
                    p->Fti[i][j][k] = 0;
                }
                if (!param->boundary.cylinder_boundary) {
                    p->omp[i][j][k].epsilongj = epsilongCalc(
                        (normCalcV2(p->omp[i][j][k].mi, p->omp[i][j - 1][k].g)),
                        (normCalcV2(p->omp[i][j][k].mi0,
                                    p->omp[i][j - 1][k].g0)));
                    p->omp[i][j][k].Fti = FtCalc(
                        normCalcV2(p->omp[i][j][k].g, p->omp[i][j][k].mi),
                        p->omp[i][j][k].hi, p->omp[i][j][k].epsilonli,
                        p->omp[i][j][k].epsilongj);
                    // p->Fti[i][j][k] = FtCalc(normCalcV2(p->g[i][j][k],
                    // p->mi[i][j][k]) + normCalcV2(p->mi[i][j][k], p->g[i][j -
                    // 1][k]), p->hi[i][j][k], p->epsilonli[i][j][k],
                    // p->epsilongj[i][j][k]);
                }
            }

            p->Ftj[i][j][k] = 0;
            break;
    }
}
#endif

////////////////////////////////// Current Function ////////////////////////////

/**
 * @brief TensileForceCalc
 *
 * @param i
 * @param j
 * @param k
 */
void MultiParticle::TensileForceCalc(const int& i, const int& j, const int& k) {
    {
        double lengthAfter   = normCalcV2(p->g[i][j][k], p->mj[i][j][k]);
        double lengthInitial = normCalcV2(p->g0[i][j][k], p->mj0[i][j][k]);
        if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
            lengthAfter += normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k]);
            lengthInitial += normCalcV2(p->mj0[i][j][k], p->g0[i - 1][j][k]);
        }
        p->epsilongi[i][j][k] = epsilongCalc(lengthAfter, lengthInitial);
    }

    {
        double lengthAfter   = normCalcV2(p->g[i][j][k], p->mi[i][j][k]);
        double lengthInitial = normCalcV2(p->g0[i][j][k], p->mi0[i][j][k]);

        if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
            lengthAfter += normCalcV2(p->mi[i][j][k], p->g[i][j - 1][k]);
            lengthInitial += normCalcV2(p->mi0[i][j][k], p->g0[i][j - 1][k]);
        }

        p->epsilongj[i][j][k] = epsilongCalc(lengthAfter, lengthInitial);
    }

    if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
        double length = normCalcV2(p->g[i][j][k], p->mi[i][j][k]);
        if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
            length += normCalcV2(p->mi[i][j][k], p->g[i][j - 1][k]);
        }
        p->Fti[i][j][k] = FtCalc(length, p->hi[i][j][k], p->epsilonli[i][j][k],
                                 p->epsilongj[i][j][k]);

#ifdef __DAMPER__
        p->cti[i][j][k] = CtCalc(length, p->hi[i][j][k], p->Si0[i][j][k], p->li0[i][j][k])
                            * (p->v[i + 1][j][k] - p->v[i][j][k]);
#endif  

    } else {
        p->Fti[i][j][k] = 0;
#ifdef __DAMPER__
        p->cti[i][j][k] = 0;
#endif  
    }

    if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
        double length = 0;

        if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
            length += normCalcV2(p->g[i][j][k], p->mj[i][j][k]);
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
            length += normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k]);
        }
        p->Ftj[i][j][k] = FtCalc(length, p->hj[i][j][k], p->epsilonlj[i][j][k],
                                 p->epsilongi[i][j][k]);

#ifdef __DAMPER__
        p->ctj[i][j][k] = CtCalc(length, p->hj[i][j][k], p->Sj0[i][j][k], p->lj0[i][j][k])
                            * (p->v[i][j + 1][k] - p->v[i][j][k]);
#endif  

    } else {
        p->Ftj[i][j][k] = 0;

#ifdef __DAMPER__
        p->ctj[i][j][k] = 0;
#endif  

    }  
}

/**
 * @brief ShareForceCalc
 * 
 * @param i
 * @param j
 * @param k
 */
void MultiParticle::ShareForceCalc(const int& i, const int& j, const int& k) {
    {
        C argip;
        C argim;
        C argjp;
        C argjm;
        Quarter delgamma; //前のgamma - 今のgamma。

        if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
            argip = p->c[i + 1][j][k];
        } else {
            argip = p->vc_Right[i][j][k];
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
            argim = p->c[i - 1][j][k];
        } else {
            argim = p->vc_Left[i][j][k];
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
            argjp = p->c[i][j + 1][k];
        } else {
            argjp = p->vc_Top[i][j][k];
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
            argjm = p->c[i][j - 1][k];
        } else {
            argjm = p->vc_Bottom[i][j][k];
        }

        p->beta[i][j][k].pp = angleCalc(p->c[i][j][k], argip, argjp);
        p->beta[i][j][k].pm = angleCalc(p->c[i][j][k], argip, argjm);
        p->beta[i][j][k].mp = angleCalc(p->c[i][j][k], argim, argjp);
        p->beta[i][j][k].mm = angleCalc(p->c[i][j][k], argim, argjm);
    }

    {
        delgamma.pp = p->gamma[i][j][k].pp;
        delgamma.pm = p->gamma[i][j][k].pm;
        delgamma.mp = p->gamma[i][j][k].mp;
        delgamma.mm = p->gamma[i][j][k].mm;

        p->gamma[i][j][k].pp =
            gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
        p->gamma[i][j][k].pm =
            gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
        p->gamma[i][j][k].mp =
            gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
        p->gamma[i][j][k].mm =
            gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);

        delgamma.pp -= p->gamma[i][j][k].pp;
        delgamma.pm -= p->gamma[i][j][k].pm;
        delgamma.mp -= p->gamma[i][j][k].mp;
        delgamma.mm -= p->gamma[i][j][k].mm;
    }

    if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
        p->Fsi[i][j][k].pp = -1 * FsCalc(p->gamma[i][j][k].pp,
                                         p->li[i][j][k].norm, p->hi[i][j][k]);
        p->Fsi[i][j][k].pm = -1 * FsCalc(p->gamma[i][j][k].pm,
                                         p->li[i][j][k].norm, p->hi[i][j][k]);

#ifdef __DAMPER__
        p->cs[i][j][k].ip = CsCalc(p->hi[i][j][k], p->Si0[i][j][k])
                                p->li[i][j][k].norm * (delgamma.pp + delgamma.pm) / 2;
#endif  

    } else {
        p->Fsi[i][j][k].pp = 0;
        p->Fsi[i][j][k].pm = 0;

#ifdef __DAMPER__
        p->cs[i][j][k].ip = 0;
#endif  

    }

    if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
        p->Fsi[i][j][k].mp =
            -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i - 1][j][k].norm,
                        p->hi[i - 1][j][k]);
        p->Fsi[i][j][k].mm =
            -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i - 1][j][k].norm,
                        p->hi[i - 1][j][k]);
                        
#ifdef __DAMPER__
        p->cs[i][j][k].im = CsCalc(p->hi[i - 1][j][k], p->Si0[i - 1][j][k])
                                p->li[i - 1][j][k].norm * (delgamma.mp + delgamma.mm) / 2;
#endif  

    } else {
        p->Fsi[i][j][k].mp = 0;
        p->Fsi[i][j][k].mm = 0;
        
#ifdef __DAMPER__
        p->cs[i][j][k].im = 0;
#endif  

        // double li_l_norm   = normCalc(p->c[i][j][k] - p->vc_Left[i][j][k]);

        // C Si_i;
        // C Si_j;
        // int num = 0;
        // if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
        //     num += 2;
        //     Si_i += p->c[i][j][k] - p->vc_Left[i][j][k];
        //     Si_i += p->c[i][j + 1][k] - p->vc_Left[i][j + 1][k];
        // }
        // if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
        //     num += 2;
        //     Si_i += p->c[i][j][k] - p->vc_Left[i][j][k];
        //     Si_i += p->c[i][j - 1][k] - p->vc_Left[i][j - 1][k];
        // }
        // Si_i /= num;
        // num = 0;
        // if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
        //     num += 2;
        //     Si_j += p->c[i][j + 1][k] - p->c[i][j][k];
        //     Si_j += p->c[i + 1][j + 1][k] - p->c[i + 1][j][k];
        // }
        // if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
        //     num += 2;
        //     Si_j += p->c[i][j][k] - p->c[i][j - 1][k];
        //     Si_j += p->c[i + 1][j][k] - p->c[i + 1][j - 1][k];
        // }
        // Si_j /= num;

        // C Si_l_cp        = Si_i * Si_j;
        // double Si_l_norm = normCalc(Si_l_cp);
        // double hi_l      = hCalc(Si_l_norm, p->Si0[i][j][k]);

        // p->Fsi[i][j][k].mp = -1 * FsCalc(p->gamma[i][j][k].mp, li_l_norm,
        // hi_l); p->Fsi[i][j][k].mm = -1 * FsCalc(p->gamma[i][j][k].mm,
        // li_l_norm, hi_l);
    }

    if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
        p->Fsj[i][j][k].pp = -1 * FsCalc(p->gamma[i][j][k].pp,
                                         p->lj[i][j][k].norm, p->hj[i][j][k]);
        p->Fsj[i][j][k].mp = -1 * FsCalc(p->gamma[i][j][k].mp,
                                         p->lj[i][j][k].norm, p->hj[i][j][k]);
                                         
#ifdef __DAMPER__
        p->cs[i][j][k].jp = CsCalc(p->hj[i][j][k], p->Sj0[i][j][k])
                                p->lj[i][j][k].norm * (delgamma.pp + delgamma.mp) / 2;
#endif  

    } else {
        p->Fsj[i][j][k].pp = 0;
        p->Fsj[i][j][k].mp = 0;
                                                 
#ifdef __DAMPER__
        p->cs[i][j][k].jp = 0;
#endif  

    }
    if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
        p->Fsj[i][j][k].pm =
            -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j - 1][k].norm,
                        p->hj[i][j - 1][k]);
        p->Fsj[i][j][k].mm =
            -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j - 1][k].norm,
                        p->hj[i][j - 1][k]);
                                                                 
#ifdef __DAMPER__
        p->cs[i][j][k].jm = CsCalc(p->hj[i][j - 1][k], p->Sj0[i][j - 1][k])
                                p->lj[i][j - 1][k].norm * (delgamma.pm + delgamma.mm) / 2;
#endif  

    } else {
        p->Fsj[i][j][k].pm = 0;
        p->Fsj[i][j][k].mm = 0;
                                                 
#ifdef __DAMPER__
        p->cs[i][j][k].jm = 0;
#endif  

    }

    if (p->flag[i][j][k] & Right) {
        if (!param->boundary.right_share_fix) {
            p->Fsj[i][j][k].pp = 0;
            p->Fsj[i][j][k].pm = 0;
            p->Fsj[i][j][k].mp = 0;
            p->Fsj[i][j][k].mm = 0;
                                                     
#ifdef __DAMPER__
            p->cs[i][j][k].jp = 0;
            p->cs[i][j][k].jm = 0;
            p->cs[i][j][k].ip = 0;
            p->cs[i][j][k].im = 0;
#endif  

        }
    }
    if (p->flag[i][j][k] & Left) {
        if (!param->boundary.left_share_fix) {
            p->Fsj[i][j][k].pp = 0;
            p->Fsj[i][j][k].pm = 0;
            p->Fsj[i][j][k].mp = 0;
            p->Fsj[i][j][k].mm = 0;
                                                                 
#ifdef __DAMPER__
            p->cs[i][j][k].jp = 0;
            p->cs[i][j][k].jm = 0;
            p->cs[i][j][k].ip = 0;
            p->cs[i][j][k].im = 0;
#endif  

        }
    }
    if (p->flag[i][j][k] & Top) {
        if (!param->boundary.top_share_fix) {
            p->Fsi[i][j][k].pp = 0;
            p->Fsi[i][j][k].pm = 0;
            p->Fsi[i][j][k].mp = 0;
            p->Fsi[i][j][k].mm = 0;
                                                                 
#ifdef __DAMPER__
            p->cs[i][j][k].jp = 0;
            p->cs[i][j][k].jm = 0;
            p->cs[i][j][k].ip = 0;
            p->cs[i][j][k].im = 0;
#endif  

        }
    }
    if (p->flag[i][j][k] & Bottom) {
        if (!param->boundary.bottom_share_fix) {
            p->Fsi[i][j][k].pp = 0;
            p->Fsi[i][j][k].pm = 0;
            p->Fsi[i][j][k].mp = 0;
            p->Fsi[i][j][k].mm = 0;
                                                                 
#ifdef __DAMPER__
            p->cs[i][j][k].jp = 0;
            p->cs[i][j][k].jm = 0;
            p->cs[i][j][k].ip = 0;
            p->cs[i][j][k].im = 0;
#endif  

        }
    }
}

/**
 * @brief BendForceCalc  ここから（減衰項の追加）
 *
 * @param i
 * @param j
 * @param k
 */
void MultiParticle::BendForceCalc(const int& i, const int& j, const int& k) {
    double del_etai = 0;// 今の曲率 - 前の時間の曲率
    double del_etaj = 0;
    {
        p->h_ave[i][j][k] = 0;
        int sum_count     = 0;
        if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
            p->h_ave[i][j][k] += p->hi[i][j][k];
            sum_count++;
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
            p->h_ave[i][j][k] += p->hi[i - 1][j][k];
            sum_count++;
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
            p->h_ave[i][j][k] += p->hj[i][j][k];
            sum_count++;
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
            p->h_ave[i][j][k] += p->hj[i][j - 1][k];
            sum_count++;
        }
        p->h_ave[i][j][k] /= sum_count;
        p->h_ave3[i][j][k] =
            p->h_ave[i][j][k] * p->h_ave[i][j][k] * p->h_ave[i][j][k];
        // p->h_ave3[i][j][k] =
        //     0.000001;
    }
    {
        double norm_j_plus  = 0;
        double norm_j_minus = 0;
        if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
            norm_j_plus = normCalcV2(p->mj[i][j][k], p->c[i][j][k]);
            // norm_j_plus = 0.025;
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
            norm_j_minus = normCalcV2(p->c[i][j][k], p->mj[i][j - 1][k]);
            // norm_j_minus = 0.025;
        }
        p->Ii[i][j][k] = (norm_j_plus + norm_j_minus) * p->h_ave3[i][j][k];
    }

    {
        double norm_i_plus  = 0;
        double norm_i_minus = 0;
        if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
            norm_i_plus = normCalcV2(p->mi[i][j][k], p->c[i][j][k]);
            // norm_i_plus = 0.025;
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
            norm_i_minus = normCalcV2(p->c[i][j][k], p->mi[i - 1][j][k]);
            // norm_i_minus = 0.025;
        }
        p->Ij[i][j][k] = (norm_i_plus + norm_i_minus) * p->h_ave3[i][j][k];
    }

    {
        C plus;
        C minus;
        if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
            plus = p->c[i][j + 1][k];
        } else {
            plus = p->vc_Top[i][j][k];
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
            minus = p->c[i][j - 1][k];
        } else {
            minus = p->vc_Bottom[i][j][k];
        }
        p->alphaj[i][j][k] = angleCalc2(p->c[i][j][k], plus, minus, "j");
    }

    {
        C plus;
        C minus;
        if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
            plus = p->c[i + 1][j][k];
        } else {
            plus = p->vc_Right[i][j][k];
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
            minus = p->c[i - 1][j][k];
        } else {
            minus = p->vc_Left[i][j][k];
        }
        p->alphai[i][j][k] = angleCalc2(p->c[i][j][k], plus, minus, "i");

        // if ((p->surround_particle_exsit[i][j][k] & BIT_RIGHT) &&
        //     (p->surround_particle_exsit[i][j][k] & BIT_LEFT)) {
        //     p->alphai[i][j][k] = angleCalc2(p->c[i][j][k], p->c[i + 1][j][k],
        //                                     p->c[i - 1][j][k], 0);
        // } else if (!(p->surround_particle_exsit[i][j][k] & BIT_RIGHT)) {
        //     p->alphai[i][j][k] = angleCalc2(p->c[i][j][k],
        //     p->vc_Right[i][j][k],
        //                                     p->c[i - 1][j][k], 0);
        // } else if (!(p->surround_particle_exsit[i][j][k] & BIT_LEFT)) {
        //     p->alphai[i][j][k] = ngleCalc2(p->c[i][j][k], p->c[i + 1][j][k],
        //                                     p->vc_Left[i][j][k], 0);
        // }
    }
    C li_left, li_right;
    double li_left_norm  = 0;
    double li_right_norm = 0;
    C lj_bottom, lj_top;
    double lj_bottom_norm = 0;
    double lj_top_norm    = 0;
    {
        if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
            li_right_norm = p->li[i][j][k].norm;
        } else {
            li_right      = p->vc_Right[i][j][k] - p->c[i][j][k];
            li_right_norm = normCalc(li_right);
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
            li_left_norm = p->li[i - 1][j][k].norm;
        } else {
            li_left      = p->c[i][j][k] - p->vc_Left[i][j][k];
            li_left_norm = normCalc(li_left);
        }
        p->etai[i][j][k] =
            etaCalc(p->alphai[i][j][k], li_right_norm, li_left_norm);
    }
    {
        if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
            lj_top_norm = p->lj[i][j][k].norm;
        } else {
            lj_top      = p->vc_Top[i][j][k] - p->c[i][j][k];
            lj_top_norm = normCalc(lj_top);
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
            lj_bottom_norm = p->lj[i][j - 1][k].norm;
        } else {
            lj_bottom      = p->c[i][j][k] - p->vc_Bottom[i][j][k];
            lj_bottom_norm = normCalc(lj_bottom);
        }
        p->etaj[i][j][k] =
            etaCalc(p->alphaj[i][j][k], lj_top_norm, lj_bottom_norm);
    }
    del_etai -= p->diff_etai[i][j][k];
    del_etaj -= p->diff_etaj[i][j][k];
    p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
    p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];
    del_etai += p->diff_etai[i][j][k];
    del_etaj += p->diff_etaj[i][j][k];

    p->Mi[i][j][k] =
        MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k], p->diff_etaj[i][j][k]);
    p->Mj[i][j][k] =
        MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k], p->diff_etai[i][j][k]);

    if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
        p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
        // p->Fb[i][j][k].ipv = 0;
#ifdef __DAMPER__
        p->cb[i][j][k].ipv = CbCalc(li_right_norm, p->Ii[i][j][k],
                                p->S0[i][j][k], li_left_norm)
                                * (li_right_norm * li_left_norm) * del_etai / 2;
#endif
    }
    if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
        p->Fb[i][j][k].imv = -1 * p->Mi[i][j][k] / p->li[i - 1][j][k].norm;
        // p->Fb[i][j][k].imv = 0;
#ifdef __DAMPER__
        p->cb[i][j][k].imv = CbCalc(li_left_norm, p->Ii[i][j][k],
                                p->S0[i][j][k], li_right_norm)
                                * (li_right_norm * li_left_norm) * del_etai / 2;
#endif
    }
    if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
        p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
        // p->Fb[i][j][k].jpv = 0;
#ifdef __DAMPER__
        p->cb[i][j][k].jpv = CbCalc(lj_top_norm, p->Ij[i][j][k],
                                p->S0[i][j][k], lj_bottom_norm)
                                * (lj_bottom_norm * lj_top_norm) * del_etaj / 2;
#endif
    }
    if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
        p->Fb[i][j][k].jmv = -1 * p->Mj[i][j][k] / p->lj[i][j - 1][k].norm;
        // p->Fb[i][j][k].jmv = 0;
#ifdef __DAMPER__
        p->cb[i][j][k].jmv = CbCalc(lj_bottom_norm, p->Ij[i][j][k],
                                p->S0[i][j][k], lj_top_norm)
                                * (lj_bottom_norm * lj_top_norm) * del_etaj / 2;
#endif
    }


    if (p->flag[i][j][k] & Right) {
        if (!param->boundary.right_bend_fix) {
            p->Fb[i][j][k].ipv = 0;
#ifdef __DAMPER__
            p->cb[i][j][k].ipv = 0;
#endif
            if (!param->boundary.right_free) {
                p->Fb[i][j][k].imv = 0;
#ifdef __DAMPER__
                p->cb[i][j][k].imv = 0;
#endif
            }
        }
    }
    if (p->flag[i][j][k] & Left) {
        if (!param->boundary.left_bend_fix) {
            if (!param->boundary.left_free) {
                p->Fb[i][j][k].ipv = 0;
#ifdef __DAMPER__
                p->cb[i][j][k].ipv = 0;
#endif
            }
            p->Fb[i][j][k].imv = 0;
#ifdef __DAMPER__
            p->cb[i][j][k].imv = 0;
#endif
        }
    }
    if (p->flag[i][j][k] & Top) {
        if (!param->boundary.top_bend_fix) {
#ifdef __DAMPER__
            p->cb[i][j][k].jpv = 0;
#endif
            p->Fb[i][j][k].jpv = 0;
            if (!param->boundary.top_free) {
                p->Fb[i][j][k].jmv = 0;
#ifdef __DAMPER__
                p->cb[i][j][k].jmv = 0;
#endif
            }
        }
    }
    if (p->flag[i][j][k] & Bottom) {
        if (!param->boundary.bottom_bend_fix) {
            if (!param->boundary.bottom_free) {
                p->Fb[i][j][k].jpv = 0;
#ifdef __DAMPER__
                p->cb[i][j][k].jpv = 0;
#endif
            }
            p->Fb[i][j][k].jmv = 0;
#ifdef __DAMPER__
            p->cb[i][j][k].jmv = 0;
#endif
        }
    }
}


/**
 * @brief TwistForceCalc
 *
 * @param i
 * @param j
 * @param k
 * @continue ここに交点の関数を入れる
 * 
 */
void MultiParticle::TwistForceCalc(const int& i, const int& j, const int& k) {
    // 最初は完全な平面を想定して計算。初期角度が0でない場合には少し変更する必要あり
    
    double h_ave_i, h_ave3_i, Ip1_i;
    double norm_j_plus  = 0;
    double norm_j_minus = 0;
    double norm3_j = 0;
    double h_ave_j, h_ave3_j, Ip1_j;
    double norm_i_plus  = 0;
    double norm_i_minus = 0;
    double norm3_i = 0;
    C Insec;
    C Insec_plus;
    C Unit;
    C Cp;
    C H; // Ftwのベクトルを計算するときに使う、粒子から垂線を下した交点
    // double projec_minus = 0;
    // double projec_plus = 0;
    double radian = 0;
    double k1 = 0.2915; // l（粒子間距離）/m_h0 = 50の時の値
    // double p = 0;
    // double s = 0;
    Vector Hr_minus;// 粒子i,jと軸との垂線
    Vector intersec;// 粒子i+1,jと軸との垂線  これわざわざ計算しなくてもいいかも
    Vector Hr_plus;
    Vector Ftw_vector; // Ftwのベクトルを計算するときに使う、平面に垂直なベクトル。
                        // 単位ベクトルに変換してからFtwの計算に用いる
    Vector normal; // Ftwのベクトルを計算するときに使う、平面に垂直なベクトル。間接的に用いる
    bool UpperRight = (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) 
        && (p->surround_particle_exsit[i][j][k] & BIT_TOP);
    bool LowerRight = (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) 
        && (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM);
    bool UpperLeft = (p->surround_particle_exsit[i][j][k] & BIT_LEFT)
        && (p->surround_particle_exsit[i][j][k] & BIT_TOP);
    bool LowerLeft = (p->surround_particle_exsit[i][j][k] & BIT_LEFT)
        && (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM);
    
    if (UpperRight){
        //i方向（x軸方向）
        // cout << "i=" << i
        //      << "j=" << j
        //      << "UpperRight"
        //      << endl;
        // if (!(p->surround_particle_exsit[i + 1][j][k] & BIT_RIGHT)) { return; }
        
        h_ave_i = (p->hj[i][j][k] + p->hj[i + 1][j][k] + p->hi[i][j][k] + p->hi[i][j + 1][k]) / 4;
        h_ave3_i = h_ave_i * h_ave_i * h_ave_i;

        // cout << "hi=" << h_ave_i
        //      << endl;
        

        norm_j_minus = normCalcV2(p->mj[i][j][k], p->c[i][j][k]);
        norm_j_plus = normCalcV2(p->mj[i + 1][j][k], p->c[i + 1][j][k]);
        norm3_j = 
            (norm_j_plus + norm_j_minus) * (norm_j_plus + norm_j_minus) * (norm_j_plus + norm_j_minus);
        Ip1_i = (norm_j_plus + norm_j_minus) * h_ave3_i;
        // Ip2_i = norm3_j * h_ave_i;
        p->Ipi[i][j][k] = (norm_j_plus + norm_j_minus) * h_ave3_i;

        // cout << "Ip=" << p->Ipi[i][j][k]
        //      << endl;

        // 時間あれば、ここの角度求めるところ関数にしてもわかりやすいかも
        interSectionLengthCalc(p->axis_i[i][j][k], p->mj[i][j][k], p->mj[i + 1][j][k], 
                                p->c[i][j][k], p->c[i + 1][j][k], Hr_minus, intersec, Hr_plus);

        // if (j == 10 && i == 10){
        //     cout << "axis.x=" << p->axis_i[i][j][k].vector.x
        //      << ", axis.y=" << p->axis_i[i][j][k].vector.y
        //      << ", axis.z=" << p->axis_i[i][j][k].vector.z
        //      << ", Hrm.x=" << Hr_minus.vector.x
        //      << ", Hrm.y=" << Hr_minus.vector.y
        //      << ", Hrm.z=" << Hr_minus.vector.z
        //      << ", Hrp.x=" << Hr_plus.vector.x
        //      << ", Hrp.y=" << Hr_plus.vector.y
        //      << ", Hrp.z=" << Hr_plus.vector.z
        //      << ", Inter.x=" << intersec.vector.x
        //      << ", Inter.y=" << intersec.vector.y
        //      << ", Inter.z=" << intersec.vector.z
        //      << endl;
        // }
        

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
        // lCalc(Hr_minus, Insec, p->c[i][j][k]);

        //ここの過程も交点の関数に入れる Hr_plusもそこで求める
        // p = (Unit.x * (p->c[i + 1][j][k].x - p->c[i][j][k].x)
        //     + Unit.y * (p->c[i + 1][j][k].y - p->c[i][j][k].y)
        //     + Unit.z * (p->c[i + 1][j][k].z - p->c[i][j][k].z))
        //     / (Unit.x*Unit.x + Unit.y*Unit.y + Unit.z*Unit.z);
        // Insec_plus.x = p->c[i + 1][j][k].x + p * Unit.x;
        // Insec_plus.y = p->c[i + 1][j][k].y + p * Unit.y;
        // Insec_plus.x = p->c[i + 1][j][k].z + p * Unit.z;
        
        // projec_plus = 
        //     ((p->c[i + 1][j][k].x - p->mj[i + 1][j][k].x) * Unit.x + (p->c[i + 1][j][k].y - p->mj[i + 1][j][k].y) * Unit.y 
        //     + (p->c[i + 1][j][k].z - p->mj[i + 1][j][k].z) * Unit.z);
        // Insec_plus.x = p->mj[i + 1][j][k].x + projec_plus * Unit.x;
        // Insec_plus.y = p->mj[i + 1][j][k].y + projec_plus * Unit.y;
        // Insec_plus.z = p->mj[i + 1][j][k].z + projec_plus * Unit.z;
        // lCalc(Hr_plus, Insec, Insec_plus);
        crossProductCalc(Cp, Hr_minus.vector, intersec.vector);
        radian = 
            innerProductCalc(intersec.vector, Hr_minus.vector) / (intersec.norm * Hr_minus.norm);
        // if (Cp.x > 0) {
        //     p->diffang_i[i][j][k] = math::sacos(radian);
        // }
        // else {
        //     p->diffang_i[i][j][k] = -1 * math::sacos(radian);
        // }
        p->diffang_i[i][j][k] = math::sacos(radian);

        p->Torque_i[i][j][k] = 
            TCalc(p->Ipi[i][j][k], p->diffang_i[i][j][k], p->axis_i[i][j][k].norm, k1);

        p->Ftw_quater[i][j][k].ipv.norm = p->Torque_i[i][j][k] / intersec.norm;
        FtwVector(p->c[i + 1][j + 1][k], p->c[i + 1][j][k], p->axis_i[i][j][k].vector,
                                p->c[i][j][k], p->Ftw_quater[i][j][k].ipv);

        p->Ftw_quater[i][j][k].imv.norm = p->Torque_i[i][j][k] / Hr_minus.norm;
        FtwVector(p->c[i][j + 1][k], p->c[i][j][k], p->axis_i[i][j][k].vector,
                                p->c[i + 1][j][k], p->Ftw_quater[i][j][k].imv);

        // if (j == 10 && i == 10){
        //     cout << "ftw=" << p->Ftw_quater[i][j][k].ipv.norm
        //      << ", Ftw=" << p->Ftw_quater[i][j][k].imv.norm
        //      << ", Ftwp.x=" << p->Ftw_quater[i][j][k].ipv.vector.x
        //      << ", Ftwp.y=" << p->Ftw_quater[i][j][k].ipv.vector.y
        //      << ", Ftwp.z=" << p->Ftw_quater[i][j][k].ipv.vector.z
        //      << ", Ftwm.x=" << p->Ftw_quater[i][j][k].imv.vector.x
        //      << ", Ftwm.y=" << p->Ftw_quater[i][j][k].imv.vector.y
        //      << ", Ftwm.z=" << p->Ftw_quater[i][j][k].imv.vector.z
        //      << endl;
        // }

        // crossProductCalc(normal.vector, p->c[i + 1][j + 1][k] - p->c[i + 1][j][k], p->axis_i[i][j][k]);
        // normal.norm = normCalc(normal.vector);
        // normal.vector.x /= normal.norm;
        // normal.vector.y /= normal.norm;
        // normal.vector.z /= normal.norm;
        // s = innerProductCalc(normal.vector, p->c[i][j][k] - p->c[i + 1][j][k]);
        // H.x = p->c[i][j][k].x - s * normal.vector.x;
        // H.y = p->c[i][j][k].y - s * normal.vector.y;
        // H.z = p->c[i][j][k].z - s * normal.vector.z;
        // Ftw_vector.vector = p->c[i][j][k] - H;
        // Ftw_vector.norm = normCalc(Ftw_vector.vector);
        // Ftw_vector.vector.x /= Ftw_vector.norm;
        // Ftw_vector.vector.y /= Ftw_vector.norm;
        // Ftw_vector.vector.z /= Ftw_vector.norm;

        // p->Ftw_quater[i][j][k].ipv.vector.x = p->Ftw_quater[i][j][k].ipv.norm * Ftw_vector.vector.x;
        // p->Ftw_quater[i][j][k].ipv.vector.y = p->Ftw_quater[i][j][k].ipv.norm * Ftw_vector.vector.y;
        // p->Ftw_quater[i][j][k].ipv.vector.z = p->Ftw_quater[i][j][k].ipv.norm * Ftw_vector.vector.z;

        
        // 粒子と軸からなる平面からもう片方の粒子がどっち側にあるかで方向を決める（粒子から平面に垂線を下す。
        // その後、垂線を下した交点から粒子までのベクトルの方向に力をかける）
        // 粒子の間の直線と軸の二つのベクトルの外積で平面に垂直なベクトルが求めれる。
        // p 粒子の座標、A 粒子i+1の座標


        // Ftwiを先にここで計算する Ftw_quater ipv.norm, imp.norm  Ftw=T/Hr_minus;

        //j方向（y軸方向）


        h_ave_j = h_ave_i;
        h_ave3_j =
            h_ave_j * h_ave_j * h_ave_j;

        norm_i_minus = normCalcV2(p->mi[i][j][k], p->c[i][j][k]);
        norm_i_plus = normCalcV2(p->mi[i][j + 1][k], p->c[i][j + 1][k]);
        norm3_i = 
            (norm_i_plus + norm_i_minus) * (norm_i_plus + norm_i_minus) * (norm_i_plus + norm_i_minus);
        Ip1_j = (norm_i_plus + norm_i_minus) * h_ave3_j;
        // Ip2_j = norm3_i * h_ave_j;
        p->Ipj[i][j][k] = (norm_i_plus + norm_i_minus) * h_ave3_j;

        // 時間あれば、ここの角度求めるところ関数にしてもわかりやすいかも
        interSectionLengthCalc(p->axis_j[i][j][k], p->mi[i][j][k], p->mi[i][j + 1][k], 
                                p->c[i][j][k], p->c[i][j + 1][k], Hr_minus, intersec, Hr_plus);

        // lCalc(p->axis_j[i][j][k], p->mi[i][j][k], p->mi[i][j + 1][k]); // 軸ベクトルの計算
        // Unit.x = p->axis_j[i][j][k].vector.x / p->axis_j[i][j][k].norm;// 軸の単位ベクトル計算
        // Unit.y = p->axis_j[i][j][k].vector.y / p->axis_j[i][j][k].norm;
        // Unit.z = p->axis_j[i][j][k].vector.z / p->axis_j[i][j][k].norm;
        // projec_minus = 
        //     ((p->c[i][j][k].x - p->mi[i][j][k].x) * Unit.x + (p->c[i][j][k].y - p->mi[i][j][k].y) * Unit.y 
        //     + (p->c[i][j][k].z - p->mi[i][j][k].z) * Unit.z);
        // Insec.x = p->mi[i][j][k].x + projec_minus * Unit.x;
        // Insec.y = p->mi[i][j][k].y + projec_minus * Unit.y;
        // Insec.z = p->mi[i][j][k].z + projec_minus * Unit.z;
        // lCalc(Hr_minus, Insec, p->c[i][j][k]);

        // p = (Unit.x * (p->c[i][j + 1][k].x - p->c[i][j][k].x)
        //     + Unit.y * (p->c[i][j + 1][k].y - p->c[i][j][k].y)
        //     + Unit.z * (p->c[i][j + 1][k].z - p->c[i][j][k].z))
        //     / (Unit.x*Unit.x + Unit.y*Unit.y + Unit.z*Unit.z);
        // Insec_plus.x = p->c[i][j + 1][k].x + p * Unit.x;
        // Insec_plus.y = p->c[i][j + 1][k].y + p * Unit.y;
        // Insec_plus.x = p->c[i][j + 1][k].z + p * Unit.z;
        // // projec_plus = 
        // //     ((p->c[i][j + 1][k].x - p->mi[i][j + 1][k].x) * Unit.x + (p->c[i][j + 1][k].y - p->mi[i][j + 1][k].y) * Unit.y 
        // //     + (p->c[i][j + 1][k].z - p->mi[i][j + 1][k].z) * Unit.z);
        // // Insec.x = p->mi[i][j + 1][k].x + projec_minus * Unit.x;
        // // Insec.y = p->mi[i][j + 1][k].y + projec_minus * Unit.y;
        // // Insec.z = p->mi[i][j + 1][k].z + projec_minus * Unit.z;
        // lCalc(Hr_plus, Insec_plus, p->c[i][j + 1][k]);
        crossProductCalc(Cp, Hr_minus.vector, intersec.vector);
        radian = 
            innerProductCalc(intersec.vector, Hr_minus.vector) / (intersec.norm * Hr_minus.norm);
        // if (Cp.y > 0) {
        //     p->diffang_j[i][j][k] = math::sacos(radian);
        // }
        // else {
        //     p->diffang_j[i][j][k] = -1 * math::sacos(radian);
        // }
        p->diffang_j[i][j][k] = math::sacos(radian);

        p->Torque_j[i][j][k] = 
            TCalc(p->Ipj[i][j][k], p->diffang_j[i][j][k], p->axis_j[i][j][k].norm, k1); 

        p->Ftw_quater[i][j][k].jpv.norm = p->Torque_j[i][j][k] / intersec.norm;
        FtwVector(p->c[i + 1][j + 1][k], p->c[i][j + 1][k], p->axis_j[i][j][k].vector,
                                p->c[i][j][k], p->Ftw_quater[i][j][k].jpv);

        p->Ftw_quater[i][j][k].jmv.norm = p->Torque_j[i][j][k] / Hr_minus.norm;
        FtwVector(p->c[i + 1][j][k], p->c[i][j][k], p->axis_j[i][j][k].vector,
                                p->c[i][j + 1][k], p->Ftw_quater[i][j][k].jmv);
        // if(i==19 && j == 19){
        //      cout << ", Ftwp.x=" << p->Ftw_quater[i][j][k].jpv.vector.x
        //  << ", Ftwp.y=" << p->Ftw_quater[i][j][k].jpv.vector.z
        //  << ", Ftwp.z=" << p->Ftw_quater[i][j][k].ipv.vector.z
        //  << endl;
        // }

    }

    // 粒子(i,j)にかかる全ねじり力を足し合わせる
    p->Ftw[i][j][k].x = 0;
    p->Ftw[i][j][k].y = 0;
    p->Ftw[i][j][k].z = 0;

    double Torque;
    double Verang_i, Verang_j;
    Vector VerFtw_ip;
    Vector VerFtw_jp;
    

    VerFtw_ip.vector.x = 0;
    VerFtw_ip.vector.y = 0;
    VerFtw_ip.vector.z = 0;

    VerFtw_jp.vector.x = 0;
    VerFtw_jp.vector.y = 0;
    VerFtw_jp.vector.z = 0;

    if (!(p->surround_particle_exsit[i][j][k] & BIT_LEFT)) {
        if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)) { return; }
            //i方向（x軸方向）
        
        h_ave_i = p->hj[i][j][k];
        h_ave3_i = h_ave_i * h_ave_i * h_ave_i;

        norm_j_minus = normCalcV2(p->vc_Left[i][j+1][k], p->vc_Left[i][j][k]) / 2;
        norm_j_plus = normCalcV2(p->mj[i][j][k], p->c[i][j][k]);
        norm3_j = 
            (norm_j_plus + norm_j_minus) * (norm_j_plus + norm_j_minus) * (norm_j_plus + norm_j_minus);
        Ip1_i = (norm_j_plus + norm_j_minus) * h_ave3_i;
        // Ip2_i = norm3_j * h_ave_i;
        // p->Ipi[i][j][k] = (norm_j_plus + norm_j_minus) * h_ave3_i;

        // cout << "Ip=" << p->Ipi[i][j][k]
        //      << endl;

        // 時間あれば、ここの角度求めるところ関数にしてもわかりやすいかも
        interSectionLengthCalc(p->axis_i[i][j][k], (p->vc_Left[i][j][k] + p->vc_Left[i][j+1][k])/2, p->mj[i][j][k], 
                                p->vc_Left[i][j][k], p->c[i][j][k], Hr_minus, intersec, Hr_plus);

        crossProductCalc(Cp, Hr_minus.vector, intersec.vector);
        radian = 
            innerProductCalc(intersec.vector, Hr_minus.vector) / (intersec.norm * Hr_minus.norm);
        
        Verang_i = math::sacos(radian);

        Torque = 
            TCalc(Ip1_i, Verang_i, p->axis_i[i][j][k].norm, k1);

        p->ftw_ver[i][j][k].ipv.norm = Torque / intersec.norm;
        FtwVector(p->c[i][j + 1][k], p->c[i][j][k], p->axis_i[i][j][k].vector,
                                p->vc_Left[i][j][k], p->ftw_ver[i][j][k].ipv);

        p->ftw_ver[i][j][k].imv.norm = Torque / Hr_minus.norm;
        FtwVector(p->vc_Left[i][j+1][k], p->vc_Left[i][j][k], p->axis_i[i][j][k].vector,
                                p->c[i][j][k], p->ftw_ver[i][j][k].imv);
        
        // Ftwiを先にここで計算する Ftw_quater ipv.norm, imp.norm  Ftw=T/Hr_minus;

        //j方向（y軸方向）
        h_ave_j = h_ave_i;
        h_ave3_j =
            h_ave_j * h_ave_j * h_ave_j;

        norm_i_minus = normCalcV2(p->vc_Left[i][j][k], p->c[i][j][k])/2;
        norm_i_plus = normCalcV2(p->vc_Left[i][j+1][k], p->c[i][j + 1][k])/2;
        norm3_i = 
            (norm_i_plus + norm_i_minus) * (norm_i_plus + norm_i_minus) * (norm_i_plus + norm_i_minus);
        Ip1_j = (norm_i_plus + norm_i_minus) * h_ave3_j;
        // Ip2_j = norm3_i * h_ave_j;
        // p->Ipj[i][j][k] = (norm_i_plus + norm_i_minus) * h_ave3_j;

        // 時間あれば、ここの角度求めるところ関数にしてもわかりやすいかも
        interSectionLengthCalc(p->axis_j[i][j][k], (p->vc_Left[i][j][k], p->c[i][j][k])/2, 
                                (p->vc_Left[i][j+1][k], p->c[i][j + 1][k])/2, 
                                p->vc_Left[i][j][k], p->vc_Left[i][j+1][k], Hr_minus, intersec, Hr_plus);

        crossProductCalc(Cp, Hr_minus.vector, intersec.vector);
        radian = 
            innerProductCalc(intersec.vector, Hr_minus.vector) / (intersec.norm * Hr_minus.norm);
        
        Verang_j = math::sacos(radian);

        Torque = 
            TCalc(Ip1_j, Verang_j, p->axis_j[i][j][k].norm, k1); 

        p->ftw_ver[i][j][k].jpv.norm = Torque / intersec.norm;
        FtwVector(p->c[i][j + 1][k], p->vc_Left[i][j+1][k], p->axis_j[i][j][k].vector,
                                p->vc_Left[i][j][k], p->ftw_ver[i][j][k].jpv);

        p->ftw_ver[i][j][k].jmv.norm = Torque / Hr_minus.norm;
        FtwVector(p->c[i][j][k], p->vc_Left[i][j][k], p->axis_j[i][j][k].vector,
                                p->vc_Left[i][j+1][k], p->ftw_ver[i][j][k].jmv);

    } 

    

    if (UpperRight) {
        p->Ftw[i][j][k] += p->Ftw_quater[i][j][k].imv.vector;
        p->Ftw[i][j][k] += p->Ftw_quater[i][j][k].jmv.vector;
    }
    if (LowerRight) {
        p->Ftw[i][j][k] -= p->Ftw_quater[i][j - 1][k].imv.vector;
        p->Ftw[i][j][k] += p->Ftw_quater[i][j - 1][k].jpv.vector;
    }
    if (UpperLeft) {
        p->Ftw[i][j][k] += p->Ftw_quater[i - 1][j][k].ipv.vector;
        p->Ftw[i][j][k] -= p->Ftw_quater[i - 1][j][k].jmv.vector;
    }
    if (LowerLeft) {
        p->Ftw[i][j][k] -= p->Ftw_quater[i - 1][j - 1][k].ipv.vector;
        p->Ftw[i][j][k] -= p->Ftw_quater[i - 1][j - 1][k].jpv.vector; 
    }

//境界条件
    if ((p->flag[i][j][k] & Left)&&(param->boundary.left_bend_fix)) {
        if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
            p->Ftw[i][j][k] += p->ftw_ver[i][j][k].ipv.vector;
            p->Ftw[i][j][k] -= p->ftw_ver[i][j][k].jmv.vector;
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
            p->Ftw[i][j][k] -= p->ftw_ver[i][j-1][k].ipv.vector;
            p->Ftw[i][j][k] -= p->ftw_ver[i][j-1][k].jpv.vector;
        }
    }

    p->Ftw[i][j][k] /= 2;
    //ここは後で詳しくやる。
    //（他の場所でf=0として、計算させる？）
    
    // if (p->flag[i][j][k] & Right) {
    //     if (!param->boundary.right_bend_fix) {
    //         p->Fb[i][j][k].ipv = 0;
    //         if (!param->boundary.right_free) {
    //             p->Fb[i][j][k].imv = 0;
    //         }
    //     }
    // }
    // if (p->flag[i][j][k] & Left) {
    //     if (!param->boundary.left_bend_fix) {
    //         if (!param->boundary.left_free) {
    //             p->Fb[i][j][k].ipv = 0;
    //         }
    //         p->Fb[i][j][k].imv = 0;
    //     }
    // }
    // if (p->flag[i][j][k] & Top) {
    //     if (!param->boundary.top_bend_fix) {
    //         p->Fb[i][j][k].jpv = 0;
    //         if (!param->boundary.top_free) {
    //             p->Fb[i][j][k].jmv = 0;
    //         }
    //     }
    // }
    // if (p->flag[i][j][k] & Bottom) {
    //     if (!param->boundary.bottom_bend_fix) {
    //         if (!param->boundary.bottom_free) {
    //             p->Fb[i][j][k].jpv = 0;
    //         }
    //         p->Fb[i][j][k].jmv = 0;
    //     }
    // }
}


/**
 * @brief Air Force and Disturbance calc and gravity calc
 *
 * @param i
 * @param j
 * @param k
 */
void MultiParticle::AirForceCalc(const int& i, const int& j, const int& k) {
    if (CubePressure) {
        // None以外で圧力を計算する
        // もしかしたら圧力の向きを間違っているかも
        // αを求める式を修正しなければ
        if (p->flag[i][j][k] != BIT_NONE) {
            p->pressure[i][j][k].x = 1.0 *
                                     (param->C_AE / p->S[i][j][k].cp.norm) *
                                     p->S[i][j][k].cp.vector.x;
            p->pressure[i][j][k].y = 1.0 *
                                     (param->C_AE / p->S[i][j][k].cp.norm) *
                                     p->S[i][j][k].cp.vector.y;
            p->pressure[i][j][k].z = 1.0 *
                                     (param->C_AE / p->S[i][j][k].cp.norm) *
                                     p->S[i][j][k].cp.vector.z;
            // Fa内積を代入する
            p->Fa[i][j][k] =
                innerProductCalc(p->pressure[i][j][k], p->S[i][j][k].cp.vector);
            return;
        }
    }

    if (CylinderPressure) {
        // Pressureは常に直行する方向に働く
        p->pressure[i][j][k].x = 1.0 * (param->C_AE / p->S[i][j][k].cp.norm) *
                                 p->S[i][j][k].cp.vector.x;
        p->pressure[i][j][k].y = 1.0 * (param->C_AE / p->S[i][j][k].cp.norm) *
                                 p->S[i][j][k].cp.vector.y;
        p->pressure[i][j][k].z = 1.0 * (param->C_AE / p->S[i][j][k].cp.norm) *
                                 p->S[i][j][k].cp.vector.z;
    }

    if (SimplePressure) {
        p->pressure[i][j][k].x = 0;
        p->pressure[i][j][k].y = 0;
        p->pressure[i][j][k].z = -1.0 * param->C_AE;

        // p->pressure[i][j][k].x = 1.0 * (param->C_AE / p->S[i][j][k].cp.norm)
        // *
        //                          p->S[i][j][k].cp.vector.x;
        // p->pressure[i][j][k].y = 1.0 * (param->C_AE / p->S[i][j][k].cp.norm)
        // *
        //                          p->S[i][j][k].cp.vector.y;
        // p->pressure[i][j][k].z = -1.0 * (param->C_AE / p->S[i][j][k].cp.norm)
        // *
        //                          p->S[i][j][k].cp.vector.z;
    }
    if (SolarSail) {
        p->pressure[i][j][k] = param->pressure_initial;

        p->angle_surface_sun[i][j][k] =
            math::sacos(innerProductCalc(-1.0 * p->pressure[i][j][k].unit(),
                                         p->S[i][j][k].cp.vector.unit()));

        p->Fnormal[i][j][k] = -1.0 * param->m_Pc * p->S[i][j][k].cp.norm * param->pre_eta_n * pow(cos(p->angle_surface_sun[i][j][k]), 2) * p->S[i][j][k].cp.vector.unit();
        // innerProductCalc(p->pressure[i][j][k].unit(), p->S[i][j][k].cp.vector.unit())
        C transverse;
        if (p->angle_surface_sun[i][j][k] == 0) {
            transverse.reset();
        } else {
            transverse = p->pressure[i][j][k].unit() + p->S[i][j][k].cp.vector.unit();
        }
        p->Ftrans[i][j][k] =
            param->m_Pc * p->S[i][j][k].cp.norm * param->pre_eta_t *
            cos(p->angle_surface_sun[i][j][k]) *
            sin(p->angle_surface_sun[i][j][k]) *
            (transverse.unit());
        // p->Ftrans_i[i][j][k] = param->m_Pc * p->S[i][j][k].cp.norm * innerProductCalc(p->pressure[i][j][k].unit(), p->S[i][j][k].cp.vector.unit()) * p->S[i][j][k].cp.vector.unit();
    }
// #ifndef __GEOMETRYDISTURBANCE__
                
    // if (param->add_disturbance) {
    //     disturbance_Calc(p->disturbance[i][j][k], param->disturbance_range);
    //     if (param->disturbance_mode == "direct") {
    //         p->Fd[i][j][k] = normCalc(p->disturbance[i][j][k]);
    //     } else {
    //         p->Fd[i][j][k] = innerProductCalc(p->disturbance[i][j][k],
    //                                           p->S[i][j][k].cp.vector);
    //     }
    // }
// #endif
    
    p->Fa[i][j][k] =
        innerProductCalc(p->pressure[i][j][k], p->S[i][j][k].cp.vector);

}

void MultiParticle::ContradictBendForceCalc(const int& i, const int& j,
                                            const int& k) {
    p->Fb[i][j][k].ipmv = 0;
    p->Fb[i][j][k].jpmv = 0;

    if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
        p->Fb[i][j][k].ipmv +=
            -1 * (UnitVectorCalc(p->Fb[i + 1][j][k].imv, p->Si[i][j][k]));

        // p->Fb[i][j][k].ipmv =
        //     -1 * (UnitVectorCalc(p->Fb[i + 1][j][k].imv, p->Si[i][j][k]) +
        //           UnitVectorCalc(p->Fb[i - 1][j][k].ipv, p->Si[i -
        //           1][j][k]));
    }
    if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
        p->Fb[i][j][k].ipmv +=
            -1 * UnitVectorCalc(p->Fb[i - 1][j][k].ipv, p->Si[i - 1][j][k]);
    }
    //  else {
    //     p->Fb[i][j][k].ipmv.x =
    //         -1 * (p->Fb[i][j][k].imv * p->Si[i][j][k].cp.vector.x /
    //                   p->Si[i][j][k].cp.norm +
    //               p->Fb[i][j][k].ipv * p->Si[i][j][k].cp.vector.x /
    //                   p->Si[i][j][k].cp.norm);
    // }

    // p->Fb[i][j][k].ipmv.x =
    //     -1 * (p->Fb[i][j][k].imv * p->Si[i][j][k].cp.vector.x /
    //               p->Si[i][j][k].cp.norm +
    //           p->Fb[i][j][k].ipv * p->Si[i][j][k].cp.vector.x /
    //               p->Si[i][j][k].cp.norm);

    if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
        p->Fb[i][j][k].jpmv +=
            -1 * UnitVectorCalc(p->Fb[i][j + 1][k].jmv, p->Sj[i][j][k]);
    }
    if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
        p->Fb[i][j][k].jpmv +=
            -1 * UnitVectorCalc(p->Fb[i][j - 1][k].jpv, p->Sj[i][j - 1][k]);
    }
    // else {
    //     p->Fb[i][j][;k].jpmv =
    //         -1 * (UnitVectorCalc(p->Fb[i][j + 1][k].jmv, p->Si[i][j][k]) +
    //               UnitVectorCalc(p->Fb[i][j - 1][k].jpv, p->Si[i][j -
    //               1][k]));
    // }
}

/**
 * @brief
 *
 * @param i
 * @param j
 * @param k
 * @note 回転する膜はxy平面上のものとみなす。
 */
void MultiParticle::RotationInertiaForceCalc(const int& i, const int& j, const int& k) {
    if (i == param->center_i && j == param->center_j && k == param->center_k) {
        return;
    }

    p->r[i][j][k].vector =
        p->c[i][j][k] - p->c[param->center_i][param->center_j][param->center_k];
    p->r[i][j][k].norm = p->r[i][j][k].vector.abs();
    double pre_phi     = p->phi[i][j][k];
    double pre_theta   = p->theta[i][j][k];
    double pre_psi     = p->psi[i][j][k];
    // double pre_omega_phi   = p->omega_phi[i][j][k];
    // double pre_omega_theta = p->omega_theta[i][j][k];
    // double pre_omega_psi   = p->omega_psi[i][j][k];
    // C pre_omega       = p->omega[i][j][k];
    p->phi[i][j][k]   = 0;
    p->theta[i][j][k] = acos(p->r[i][j][k].vector.z / p->r[i][j][k].norm);
    p->psi[i][j][k] =
        acos(p->r[i][j][k].vector.x /
             sqrt(p->r[i][j][k].vector.x * p->r[i][j][k].vector.x +
                  p->r[i][j][k].vector.y * p->r[i][j][k].vector.y));
    if (p->r[i][j][k].vector.y < 0) {
        p->psi[i][j][k] *= -1.0;
    }
    p->omega_phi[i][j][k]   = p->phi[i][j][k] - pre_phi;
    p->omega_theta[i][j][k] = p->theta[i][j][k] - pre_theta;
    p->omega_psi[i][j][k]   = p->psi[i][j][k] - pre_psi;

    {  // すべての粒子が等速回転運動を行っている。
        p->omega_phi[i][j][k]   = param->phi_d;
        p->omega_theta[i][j][k] = param->theta_d;
        p->omega_psi[i][j][k]   = param->psi_d;
    }
    {  //
        param->phi_dd   = param->phi_d - param->pre_phi_d;
        param->theta_dd = param->theta_d - param->pre_theta_d;
        param->psi_dd   = param->psi_d - param->pre_psi_d;
    }
    {
        param->pre_phi_d   = param->phi_d;
        param->pre_theta_d = param->theta_d;
        param->pre_psi_d   = param->psi_d;
    }
    {  // omega_phi_vec
        p->omega_phi_vec[i][j][k].x = 0;
        p->omega_phi_vec[i][j][k].y = 0;
        p->omega_phi_vec[i][j][k].z = param->initial_phi_d;
    }

    // web page を参考にしたもの
    // p->omega[i][j][k].x = -p->omega_phi[i][j][k] * sin(p->theta[i][j][k]);
    // p->omega[i][j][k].y = p->omega_theta[i][j][k];
    // p->omega[i][j][k].z = -p->omega_phi[i][j][k] * cos(p->theta[i][j][k]);

    // y-node
    // p->omega[i][j][k].x =
    //     p->omega_theta[i][j][k] * sin(p->psi[i][j][k]) -
    //     p->omega_phi[i][j][k] * cos(p->psi[i][j][k]) * sin(p->theta[i][j][k]);
    // p->omega[i][j][k].y =
    //     p->omega_theta[i][j][k] * cos(p->psi[i][j][k]) +
    //     p->omega_phi[i][j][k] * sin(p->psi[i][j][k]) * sin(p->theta[i][j][k]);
    // p->omega[i][j][k].z = p->omega_psi[i][j][k] + p->omega_phi[i][j][k] * cos(p->theta[i][j][k]);

    {  // y-node 座標回転による力
        param->omega_system.x =
            param->theta_d * sin(param->psi) -
            param->phi_d * cos(param->psi) * sin(param->theta);
        param->omega_system.y =
            param->theta_d * cos(param->psi) +
            param->phi_d * sin(param->psi) * sin(param->theta);
        param->omega_system.z = param->psi_d + param->phi_d * cos(param->theta);

        p->omega[i][j][k] = param->omega_system;

        param->a_euler_system.x =
            param->phi_dd * sin(param->theta) * sin(param->theta) +
            param->theta_dd * cos(param->theta) +
            param->phi_d * param->theta_d * cos(param->theta) * sin(param->theta) +
            param->phi_d * param->psi_d * sin(param->theta) * cos(param->theta) -
            param->theta_d * param->psi_d * sin(param->theta);
        param->a_euler_system.y =
            param->phi_dd * sin(param->theta) * cos(param->theta) -
            param->theta_dd * sin(param->theta) +
            param->phi_d * param->theta_d * cos(param->theta) * cos(param->theta) +
            param->phi_d * param->psi_d * sin(param->theta) * sin(param->theta) -
            param->theta_d * param->psi_d * cos(param->theta);
        param->a_euler_system.z =
            param->phi_dd * cos(param->theta) -
            param->phi_d * param->theta_d * sin(param->theta);

        p->a_euler[i][j][k] = param->a_euler_system;
    }
    // p->r[i][j][k].vector = p->omega[i][j][k];
    p->v_rot[i][j][k] = (p->r[i][j][k].vector - p->pre_r[i][j][k].vector) / param->m_dt;
    // p->v_rot[i][j][k] = cross(p->omega[i][j][k], p->r[i][j][k].vector);

    {  // Centrifugal Force
        // omega を利用しない
        // p->Fc[i][j][k].x = -(p->S0[i][j][k] / param->C_EI) * p->omega_phi[i][j][k] * p->omega_phi[i][j][k] * p->r[i][j][k].vector.x;
        // p->Fc[i][j][k].y = -(p->S0[i][j][k] / param->C_EI) * p->omega_phi[i][j][k] * p->omega_phi[i][j][k] * p->r[i][j][k].vector.y;

        // p->Fc[i][j][k] += -(p->S0[i][j][k] / param->C_EI) * p->omega_theta[i][j][k] * p->omega_theta[i][j][k] * p->r[i][j][k].vector;

        // 座標が回転することによる力
        p->F_Cen[i][j][k] = -(p->S0[i][j][k] / param->C_EI) * cross(p->omega[i][j][k], cross(p->omega[i][j][k], p->r[i][j][k].vector));
    }
    {  // Coriolis Force
        /*
            double Fcol = 2 * (p->S0[i][j][k] / param->C_EI) * p->omega_theta[i][j][k];
            p->Fcol.x   = fabs(Fcol * sin(p->theta[i][j][k]));
            p->Fcol.y   = fabs(Fcol * cos(p->theta[i][j][k]));
            p->Fcol.z   = 0;

            if (relative_coordinate_x >= 0) {
                p->Fcol[i][j][k].y *= -1.0;
            }
            if (relative_coordinate_y <= 0) {
                p->Fcol[i][j][k].x *= -1.0;
            }
            // 回転方向と逆向き
            p->Fcol *= -1.0;
        */
        // p->Fcol[i][j][k] = -2 * (p->S0[i][j][k] / param->C_EI) * p->omega[i][j][k] * p->vector_r[i][j][k];
        p->F_Cor[i][j][k] = -2 * (p->S0[i][j][k] / param->C_EI) * cross(p->omega[i][j][k], p->v_rot[i][j][k]);
    }
    {  // calculate inertia force by rotate (Euler Force)
        /*
           double Fi =
               (p->S0[i][j][k] / param->C_EI) * relative_length_xy * angular_acceleration;
           p->Fi[i][j][k].x = fabs(Fi * sin(p->theta[i][j][k]));
           p->Fi[i][j][k].y = fabs(Fi * cos(p->theta[i][j][k]));
           p->Fi[i][j][k].z = 0;

           if (relative_coordinate_x >= 0) {
               p->Fi[i][j][k].y *= -1.0;
           }
           if (relative_coordinate_y <= 0) {
               p->Fi[i][j][k].x *= -1.0;
           }
        */

        p->F_Euler[i][j][k] = -(p->S0[i][j][k] / param->C_EI) * cross(p->a_euler[i][j][k], p->r[i][j][k].vector);
        // p->Fi[i][j][k].reset();
    }

    p->F_roll[i][j][k] = p->F_Cen[i][j][k] + p->F_Cor[i][j][k] + p->F_Euler[i][j][k];
    p->pre_r[i][j][k]  = p->r[i][j][k];
    return;
}

/**
 * @brief Air Force and Disturbance calc
 *
 * @param i
 * @param j
 * @param k
 */
void MultiParticle::ExternalForceCalc(const int& i, const int& j,
                                      const int& k) {
    // cout << "run ExternalForceCalc" << endl;
    if (SimpleTensile) {
        if (p->flag[i][j][k] & BIT_RIGHT) {
            double length;
            if (!(p->surround_particle_exsit[i][j][k] & BIT_BOTTOM)) {
                length = p->mj[i][j][k].y - p->c[i][j][k].y;
            } else if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
                length = p->c[i][j][k].y - p->mj[i][j - 1][k].y;
            } else {
                length = p->mj[i][j][k].y - p->mj[i][j - 1][k].y;
            }
            p->external_force[i][j][k].x =
                -1 * ((param->m_fx * length) / param->m_Lref_x);
            // p->external_force[i][j][k].x =
            //     ((param->m_fx * (p->mj[i][j][k].y - p->mj[i][j - 1][k].y)) /
            //  param->m_Lref_x);
#ifndef __GEOMETRYDISTURBANCE__
            // if (param->add_disturbance) {
            //     disturbance_Calc(p->disturbance[i][j][k], param->disturbance_range);
            //     if (param->disturbance_mode == "direct") {
            //         p->Fd[i][j][k] = normCalc(p->disturbance[i][j][k]);
            //     } else {
            //         p->Fd[i][j][k] = innerProductCalc(p->disturbance[i][j][k],
            //                                         p->S[i][j][k].cp.vector);
            //     }
            // }
#endif
            return;
        }
    }
    if (SimpleShare) {

        if (p->flag[i][j][k] & BIT_RIGHT) {
            if (!(p->surround_particle_exsit[i][j][k] & BIT_BOTTOM)) {
                // double length = p->mj[i][j][k].y - p->c[i][j][k].y;
                double length = p->g0[i - 1][j][k].y - 0;
                p->external_force[i][j][k].y =
                    (param->m_fy * length) / param->m_Lref_x;
                
            }
            else if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
                // double length = p->c[i][j][k].y - p->mj[i][j - 1][k].y;
                double length = param->m_Lref_y - p->g0[i][j - 1][k].y;
                p->external_force[i][j][k].y =
                    (param->m_fy * length) / param->m_Lref_x;
                
            }
            // p->external_force[i][j][k].y =
            //     (param->m_fy * (p->mj[i][j][k].y - p->mj[i][j - 1][k].y)) /
            //     param->m_Lref_x;
            else {
                p->external_force[i][j][k].y =
                    (param->m_fy * (p->g0[i - 1][j][k].y - p->g0[i][j - 1][k].y)) /
                    param->m_Lref_x;
            }
        }
#ifdef __EVERYSHARE__
        if (p->flag[i][j][k] & BIT_LEFT) {
            if (!(p->surround_particle_exsit[i][j][k] & BIT_BOTTOM)) {
                double length = p->mj[i][j][k].y - p->c[i][j][k].y;
                // double length = p->g0[i - 1][j][k].y - 0;
                p->external_force[i][j][k].y =
                    -1 * (param->m_fy * length) / param->m_Lref_x;
                
            }
            else if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
                double length = p->c[i][j][k].y - p->mj[i][j - 1][k].y;
                // double length = param->m_Lref_y - p->g0[i][j - 1][k].y;
                p->external_force[i][j][k].y =
                    -1 * (param->m_fy * length) / param->m_Lref_x;
                
            }
            else {
                p->external_force[i][j][k].y =
                    -1 * (param->m_fy * (p->mj[i][j][k].y - p->mj[i][j - 1][k].y)) /
                    param->m_Lref_x;
            }
        }
        if (p->flag[i][j][k] & BIT_TOP) {
            if (!(p->surround_particle_exsit[i][j][k] & BIT_LEFT)) {
                double length = p->mi[i][j][k].x - p->c[i][j][k].x;
                // double length = p->g0[i - 1][j][k].y - 0;
                p->external_force[i][j][k].x =
                    (param->m_fy * length) / param->m_Lref_x;
                return;
            }
            if (!(p->surround_particle_exsit[i][j][k] & BIT_RIGHT)) {
                double length = p->c[i][j][k].y - p->mj[i - 1][j][k].y;
                // double length = param->m_Lref_y - p->g0[i][j - 1][k].y;
                p->external_force[i][j][k].x =
                    (param->m_fy * length) / param->m_Lref_x;
                return;
            }

            p->external_force[i][j][k].x =
                (param->m_fy * (p->mi[i][j][k].x - p->mi[i - 1][j][k].x)) /
                param->m_Lref_x;
        }
        if (p->flag[i][j][k] & BIT_BOTTOM) {
            if (!(p->surround_particle_exsit[i][j][k] & BIT_LEFT)) {
                double length = p->mi[i][j][k].x - p->c[i][j][k].x;
                // double length = p->g0[i - 1][j][k].y - 0;
                p->external_force[i][j][k].x =
                    -1 * (param->m_fy * length) / param->m_Lref_x;
                return;
            }
            if (!(p->surround_particle_exsit[i][j][k] & BIT_RIGHT)) {
                double length = p->c[i][j][k].y - p->mj[i - 1][j][k].y;
                // double length = param->m_Lref_y - p->g0[i][j - 1][k].y;
                p->external_force[i][j][k].x =
                    -1 * (param->m_fy * length) / param->m_Lref_x;
                return;
            }

            p->external_force[i][j][k].x =
                -1 * (param->m_fy * (p->mi[i][j][k].x - p->mi[i - 1][j][k].x)) /
                param->m_Lref_x;
        }
#endif
        return;
    }

    if (SimpleBend) {
        if (p->flag[i][j][k] & BIT_RIGHT) {
            // if(j==10){ return;}
            // else{
            // double diff_x = p->c[i][j][k].y - p->c[20][10][0].y;
            // double diff_y = p->c[i][j][k].z - p->c[20][10][0].z;
            // double diff_r = sqrt(diff_x*diff_x + diff_y*diff_y);
            // if (diff_r == 0){
            //     return;
            // }
            // p->external_force[i][j][k].z =
            //     0.5 * param->m_fz * diff_x * abs(j - 10)/(diff_r * 55);
            // p->external_force[i][j][k].y =
            //     0.5 * param->m_fz * diff_y * abs(j - 10)/(diff_r * 55);
            // return;
            // }
            if (!(p->surround_particle_exsit[i][j][k] & BIT_BOTTOM)) {
                // double length = p->mj0[i][j][k].y - p->c[i][j][k].y;
                // p->external_force[i][j][k].z =
                //     -1 * (param->m_fz * length) / param->m_Lref_x;
                double diff_x = p->c[i][j][k].y - p->c[20][10][0].y;
                double diff_y = p->c[i][j][k].z - p->c[20][10][0].z;
                double diff_r = sqrt(diff_x*diff_x + diff_y*diff_y);
                p->external_force[i][j][k].z =
                    0.5 * param->m_fz * diff_x/diff_r;
                p->external_force[i][j][k].y =
                    0.5 * param->m_fz * diff_y/diff_r;
                return;
            }
            // if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
            //     // double length = p->c[i][j][k].y - p->mj0[i][j - 1][k].y;
            //     // p->external_force[i][j][k].z =
            //     //     -1 * (param->m_fz * length) / param->m_Lref_x;
            //     // return;
            //     double diff_x = p->c[i][j][k].y - p->c[20][10][0].y;
            //     double diff_y = p->c[i][j][k].z - p->c[20][10][0].z;
            //     double diff_r = sqrt(diff_x*diff_x + diff_y*diff_y);
            //     p->external_force[i][j][k].z =
            //         0.5 * param->m_fz * diff_x/diff_r;
            //     p->external_force[i][j][k].y =
            //         0.5 * param->m_fz * diff_y/diff_r;
            // }
            // p->external_force[i][j][k].z =
            //     -1 *
            //     (param->m_fz * (p->mj0[i][j][k].y - p->mj0[i][j - 1][k].y)) /
            //     param->m_Lref_x;
        }
        return;
    }

    if (SimplePressure) {
        p->external_force[i][j][k].x =
            p->Fa[i][j][k] * p->S[i][j][k].cp.vector.x / p->S[i][j][k].cp.norm;
        p->external_force[i][j][k].y =
            p->Fa[i][j][k] * p->S[i][j][k].cp.vector.y / p->S[i][j][k].cp.norm;
        p->external_force[i][j][k].z =
            p->Fa[i][j][k] * p->S[i][j][k].cp.vector.z / p->S[i][j][k].cp.norm;
        p->external_force[i][j][k] = UnitVectorCalc(p->Fa[i][j][k], p->S[i][j][k]);
        return;
    }

    if (SimpleCompression) {
        if (p->flag[i][j][k] & BIT_RIGHT) {
            if (!(p->surround_particle_exsit[i][j][k] & BIT_BOTTOM)) {
                double length = p->mj[i][j][k].y - p->c[i][j][k].y;
                p->external_force[i][j][k].x =
                    -1 * ((param->m_fx * length) / param->m_Lref_x);
                return;
            }
            if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
                double length = p->c[i][j][k].y - p->mj[i][j - 1][k].y;
                p->external_force[i][j][k].x =
                    -1 * ((param->m_fx * length) / param->m_Lref_x);
                return;
            }
            p->external_force[i][j][k].x =
                -1 *
                ((param->m_fx * (p->mj[i][j][k].y - p->mj[i][j - 1][k].y)) /
                 param->m_Lref_x);
            // p->external_force[i][j][k].x =
            //     -1 *
            //     ((-param->m_fx * (p->mj[i][j][k].y - p->mj[i][j -
            //     1][k].y)) /
            //      param->m_Lref_x);
        }
        return;
    }
    if (DiagonalTensile) {
        if ((p->flag[i][j][k] & BIT_RIGHT) && (p->flag[i][j][k] & BIT_BOTTOM)) {
            // p->external_force[i][j][k].x =
            //     (param->m_fx * (p->mj[i][j][k].y - p->c[i][j][k].y)) /
            //     param->m_Lref_x;
            // p->external_force[i][j][k].y =
            //     -1.0 *
            //     (param->m_fy * (p->c[i][j][k].x - p->mi[i - 1][j][k].x)) /
            //     param->m_Lref_x;
            p->external_force[i][j][k].x = param->m_fx;
            p->external_force[i][j][k].y = -1.0 * param->m_fy;
        } else if ((p->flag[i][j][k] & BIT_RIGHT) &&
                   (p->flag[i][j][k] & BIT_TOP)) {
            // p->external_force[i][j][k].x =
            //     (param->m_fx * (p->c[i][j][k].y - p->mj[i][j - 1][k].y)) /
            //     param->m_Lref_x;
            // p->external_force[i][j][k].y =
            //     (param->m_fy * (p->c[i][j][k].x - p->mi[i - 1][j][k].x)) /
            //     param->m_Lref_x;
            p->external_force[i][j][k].x = param->m_fx;
            p->external_force[i][j][k].y = param->m_fy;
        } else if ((p->flag[i][j][k] & BIT_LEFT) &&
                   (p->flag[i][j][k] & BIT_TOP)) {
            // p->external_force[i][j][k].x =
            //     -1 * ((param->m_fx * (p->c[i][j][k].y - p->mj[i][j -
            //     1][k].y)) /
            //           param->m_Lref_x);
            // p->external_force[i][j][k].y =
            //     ((param->m_fy * (p->mi[i][j][k].x - p->c[i][j][k].x)) /
            //      param->m_Lref_x);
            p->external_force[i][j][k].x = -1.0 * param->m_fx;
            p->external_force[i][j][k].y = param->m_fy;
        } else if ((p->flag[i][j][k] & BIT_LEFT) &&
                   (p->flag[i][j][k] & BIT_BOTTOM)) {
            // p->external_force[i][j][k].x =
            //     -1 * ((param->m_fx * (p->mj[i][j][k].y - p->c[i][j][k].y)) /
            //           param->m_Lref_x),
            // p->external_force[i][j][k].y =
            //     -1 * ((param->m_fy * (p->mi[i][j][k].x - p->c[i][j][k].x)) /
            //           param->m_Lref_x);
            p->external_force[i][j][k].x = -1.0 * param->m_fx;
            p->external_force[i][j][k].y = -1.0 * param->m_fy;
        }
        return;
    }
    if (SolarSail) {
        // p->external_force[i][j][k].x =
        //     p->Fa[i][j][k] * p->S[i][j][k].cp.vector.x / p->S[i][j][k].cp.norm;
        // p->external_force[i][j][k].y =
        //     p->Fa[i][j][k] * p->S[i][j][k].cp.vector.y / p->S[i][j][k].cp.norm;
        // p->external_force[i][j][k].z =
        //     p->Fa[i][j][k] * p->S[i][j][k].cp.vector.z / p->S[i][j][k].cp.norm;
        // p->external_force[i][j][k]             = UnitVectorCalc(p->Fa[i][j][k], p->S[i][j][k]);

        p->external_force_by_pressure[i][j][k] = p->Fnormal[i][j][k] + p->Ftrans[i][j][k];
        // 重力
        p->external_force[i][j][k].z = p->Fg[i][j][k];
        // p->external_force_by_pressure[i][j][k] = UnitVectorCalc(p->Fa[i][j][k], p->S[i][j][k]);
        return;
    }
    if (PlateRevolution) {
        // int revolution_particle = p->flag.size() / 2;
        int revolution_particle = 1;

        if ((i == param->center_i + revolution_particle ||
             i == param->center_i - revolution_particle) &&
            (j == param->center_j + revolution_particle ||
             j == param->center_j - revolution_particle)) {
            // 中心から+-2 の粒子
            // unsigned int itr_x = p->c.size() / 2;
            // unsigned int itr_y = p->c[itr_x].size() / 2;
            // unsigned int itr_z = p->c[itr_x][itr_y].size() / 2;

            double relative_coordinate_x =
                p->c[i][j][k].x -
                p->c[param->itr_harf_x][param->itr_harf_y][param->itr_harf_z].x;
            double relative_coordinate_y =
                p->c[i][j][k].y -
                p->c[param->itr_harf_x][param->itr_harf_y][param->itr_harf_z].y;
            double relative_length_xy =
                sqrt(relative_coordinate_x * relative_coordinate_x +
                     relative_coordinate_y * relative_coordinate_y);
            double theta = acos(relative_coordinate_x / relative_length_xy);

            p->external_force[i][j][k].x = fabs(param->m_fe * sin(theta));
            p->external_force[i][j][k].y = fabs(param->m_fe * cos(theta));

            if (relative_coordinate_x >= 0) {
                p->external_force[i][j][k].y *= -1.0;
            }
            if (relative_coordinate_y <= 0) {
                p->external_force[i][j][k].x *= -1.0;
            }
        }

        return;
    }
    return;
}

void MultiParticle::MoveParticleByRungeKutta(const int& i, const int& j,
                                             const int& k) {
    // center point fix
    if (PlateRevolution || DiagonalTensile) {
        if (i == (int)p->flag.size() / 2 && j == (int)p->flag[i].size() / 2 &&
            k == (int)p->flag[i][j].size() / 2) {
            return;
        }
    }

    if (param->oblique_rigid) {
        if (param->oblique_move == "allFix") {
            if (i == j || j == (((int)p->flag.size() - 1) - i)) {
                return;
            }
        }
        if (param->oblique_move == "pointFix") {
            if (i == j || j == (((int)p->flag.size() - 1) - i)) {
                if (i == 0 || i == param->center_i || i == param->itr_max_x) {
                    return;
                }
                if (i % 2 == 0) {
                    return;
                }
            }
        }
        if (param->oblique_move == "obliqueExtend") {
            if (i == j || j == (((int)p->flag.size() - 1) - i)) {
                // unsigned int itr_x = p->v.size() - 1;
                // unsigned int itr_y = p->v[0].size() - 1;
                // unsigned int itr_z = p->v[0][0].size() - 1;
                double stop_extend = param->m_Lref_x * 1.1;

                if (sqrt(pow(p->v[param->itr_max_x][param->itr_max_y]
                                 [param->itr_max_z]
                                     .x,
                             2) +
                         pow(p->v[param->itr_max_x][param->itr_max_y]
                                 [param->itr_max_z]
                                     .y,
                             2)) <= stop_extend) {
                    double extend_x = p->li0[i][j][k] / (p->flag.size() - 1);
                    double extend_y = p->lj0[i][j][k] / (p->flag[i].size() - 1);
                    C extend_oblique(extend_x, extend_y, 0.0);
                    p->c[i][j][k] = p->c[i][j][k] + extend_oblique;
                    return;
                }
            }
        }
        // cout << "oblique_move is empty" << endl;
        // abort();
    }

    if (p->flag[i][j][k] == Center) {
        if (param->roll_inertia_system) {
            RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                 p->f[i][j][k].x + p->external_force[i][j][k].x + p->F_roll[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x,
                 p->damper[i][j][k].x);
            RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                 p->f[i][j][k].y + p->external_force[i][j][k].y + p->F_roll[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y,
                 p->damper[i][j][k].y);
            RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                 p->f[i][j][k].z + p->external_force[i][j][k].z + p->F_roll[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z,
                 p->damper[i][j][k].z);
        } else {
            RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                 p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x,
                 p->damper[i][j][k].x);
            RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                 p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y,
                 p->damper[i][j][k].y);
            RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                 p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z,
                 p->damper[i][j][k].z);
        }
        return;
    }

    // RIghtTopなどで boundary.top_moveが反映されない
    // Right LeftはTop Bottomより優先される
    if (param->roll_inertia_system) {
        if (p->flag[i][j][k] & Right) {
            if (param->boundary.right_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x + p->F_roll[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x,
                     p->damper[i][j][k].x);
            }
            if (param->boundary.right_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y + p->F_roll[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y,
                     p->damper[i][j][k].y);
            }
            if (param->boundary.right_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z + p->F_roll[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z,
                     p->damper[i][j][k].z);
            }
            return;
        }
        if (p->flag[i][j][k] & Left) {
            if (param->boundary.left_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x + p->F_roll[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x,
                     p->damper[i][j][k].x);
            }
            if (param->boundary.left_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y + p->F_roll[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y,
                     p->damper[i][j][k].y);
            }
            if (param->boundary.left_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z + p->F_roll[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z,
                     p->damper[i][j][k].z);
            }
            return;
        }
        if (p->flag[i][j][k] & Top) {
            if (param->boundary.top_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x + p->F_roll[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x,
                     p->damper[i][j][k].x);
            }
            if (param->boundary.top_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y + p->F_roll[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y,
                     p->damper[i][j][k].y);
            }
            if (param->boundary.top_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z + p->F_roll[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z,
                     p->damper[i][j][k].z);
            }
            return;
        }
        if (p->flag[i][j][k] & Bottom) {
            if (param->boundary.bottom_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x + p->F_roll[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x,
                     p->damper[i][j][k].x);
            }
            if (param->boundary.bottom_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y + p->F_roll[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y,
                     p->damper[i][j][k].y);
            }
            if (param->boundary.bottom_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z + p->F_roll[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z,
                     p->damper[i][j][k].z);
            }
            return;
        }
    } else {
        // if (p->flag[i][j][k] & Right) {
        if (!(p->surround_particle_exsit[i][j][k] & BIT_RIGHT)) {
            // if ((p->surround_particle_exsit[i][j][k] & BIT_TOP) && (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM)) {
#ifdef __SIMPLE_SHARE__
                if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)){ 
                    RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                        p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
                
                    return;
                }// only simple compression
#endif
                if (param->boundary.right_move.x) {
                    RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                        p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x,
                        p->damper[i][j][k].x);
                }

#ifdef __SIMPLE_COMPRESSION__
                if (j == 10){ return;}// only simple compression
#endif
                if (param->boundary.right_move.y) {
                    RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                        p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y,
                        p->damper[i][j][k].y);
                }
                if (param->boundary.right_move.z) {
                    RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                        p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z,
                        p->damper[i][j][k].z);
                }
            // }
            return;
        }
        // if (p->flag[i][j][k] & Left) {
        if (!(p->surround_particle_exsit[i][j][k] & BIT_LEFT)) {
#ifdef __SIMPLE_SHARE__
                if (j == 0){ return;}// only simple compression
#endif
            if (param->boundary.left_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x,
                     p->damper[i][j][k].x);
            }
#ifdef __SIMPLE_COMPRESSION__
                if (j == 10){ return;}// only simple compression
#endif
            if (param->boundary.left_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y,
                     p->damper[i][j][k].y);
            }
            if (param->boundary.left_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z,
                     p->damper[i][j][k].z);
            }
            return;
        }
       //  if (p->flag[i][j][k] & Top) {
        if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
            if (param->boundary.top_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x,
                     p->damper[i][j][k].x);
            }
            if (param->boundary.top_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y,
                     p->damper[i][j][k].y);
            }
            if (param->boundary.top_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z,
                     p->damper[i][j][k].z);
            }
            return;
        }
        // if (p->flag[i][j][k] & Bottom) {
        if (!(p->surround_particle_exsit[i][j][k] & BIT_BOTTOM)) {
#ifdef __SIMPLE_SHARE__
                // if (i == 0){ return;}// only simple compression
#endif
            if (param->boundary.bottom_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x,
                     p->damper[i][j][k].x);
            }
            if (param->boundary.bottom_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y,
                     p->damper[i][j][k].y);
            }
            if (param->boundary.bottom_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z,
                     p->damper[i][j][k].z);
            }
            return;
        }
    }
}
