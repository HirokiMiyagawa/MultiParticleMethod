/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file	ForceCalc.hpp
 * @brief	各粒子に作用する力を計算する
 * @details
 * @par
 * ///////////////////////////////////////////////////////////////////////////////
 */

#if defined __SHAPE_CUBE__
/*
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
*/
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
 /*
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
                p->hi[i][j][k], p->epsilonli[i][j][k], p->epsilongj[i][j][k], p->S[i][j][k].cp);
            p->Ftj[i][j][k] = FtCalc(
                normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                    normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k]),
                p->hj[i][j][k], p->epsilonlj[i][j][k], p->epsilongi[i][j][k], p->S[i][j][k].cp);
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
                p->omp[i][j][k].epsilongj, p->S[i][j][k].cp);
            // p->Fti[i][j][k] = FtCalc(normCalcV2(p->g[i][j][k],
            // p->mi[i][j][k]) + normCalcV2(p->mi[i][j][k], p->g[i][j - 1][k]),
            // p->hi[i][j][k], p->epsilonli[i][j][k], p->epsilongj[i][j][k]);
#endif
#endif
            p->Ftj[i][j][k] = FtCalc(
                normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k]), p->hj[i][j][k],
                p->epsilonlj[i][j][k], p->epsilongi[i][j][k], p->S[i][j][k].cp);
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
                                     p->epsilongj[i][j][k], p->S[i][j][k].cp);
            p->Ftj[i][j][k] = FtCalc(
                normCalcV2(p->g[i][j][k], p->mj[i][j][k]) +
                    normCalcV2(p->mj[i][j][k], p->g[i - 1][j][k]),
                p->hj[i][j][k], p->epsilonlj[i][j][k], p->epsilongi[i][j][k], p->S[i][j][k].cp);
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
                p->epsilonli[i][j][k], p->epsilongj[i][j][k], p->S[i][j][k].cp);
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
                p->hi[i][j][k], p->epsilonli[i][j][k], p->epsilongj[i][j][k], p->S[i][j][k].cp);
            p->Ftj[i][j][k]           = FtCalc(normCalcV2(p->g[i][j][k], p->mj[i][j][k]),
                                               p->hj[i][j][k], p->epsilonlj[i][j][k],
                                               p->epsilongi[i][j][k], p->S[i][j][k].cp);
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
                p->omp[i][j][k].epsilongj, p->S[i][j][k].cp);
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
                       p->omp[i][j][k].epsilongj, p->S[i][j][k].cp);
            p->Ftj[i][j][k]           = 0;
#ifdef __CYLINDER_NON_BOUNDARY__
            p->omp[i][j][k].epsilongj = epsilongCalc(
                (normCalcV2(p->omp[i][j][k].mi, p->omp[i][j - 1][k].g)),
                (normCalcV2(p->omp[i][j][k].mi0, p->omp[i][j - 1][k].g0)));
            p->omp[i][j][k].Fti =
                FtCalc(normCalcV2(p->omp[i][j][k].g, p->omp[i][j][k].mi),
                       p->omp[i][j][k].hi, p->omp[i][j][k].epsilonli,
                       p->epsilongj[i][j][k], p->S[i][j][k].cp);
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
                                               p->epsilongj[i][j][k], p->S[i][j][k].cp);
            p->Ftj[i][j][k]           = FtCalc(normCalcV2(p->g[i][j][k], p->mj[i][j][k]),
                                               p->hj[i][j][k], p->epsilonlj[i][j][k],
                                               p->epsilongi[i][j][k], p->S[i][j][k].cp);
#ifdef __CYLINDER_NON_BOUNDARY__
            p->omp[i][j][k].epsilongj = epsilongCalc(
                (normCalcV2(p->omp[i][j][k].g, p->omp[i][j][k].mi)),
                (normCalcV2(p->omp[i][j][k].g0, p->omp[i][j][k].mi0)));
            p->omp[i][j][k].Fti =
                FtCalc(normCalcV2(p->omp[i][j][k].g, p->omp[i][j][k].mi),
                       p->omp[i][j][k].hi, p->omp[i][j][k].epsilonli,
                       p->omp[i][j][k].epsilongj, p->S[i][j][k].cp);
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
                        p->omp[i][j][k].epsilongj, p->S[i][j][k].cp);
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
*/
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
                                 p->epsilongj[i][j][k], p->S[i][j][k].cp, p->temperature[i][j][k]);
    } else {
        p->Fti[i][j][k] = 0;
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
                                 p->epsilongi[i][j][k], p->S[i][j][k].cp, p->temperature[i][j][k]);
    } else {
        p->Ftj[i][j][k] = 0;
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
        p->gamma[i][j][k].pp =
            gammaCalc(p->beta[i][j][k].pp, p->beta0[i][j][k].pp);
        p->gamma[i][j][k].pm =
            gammaCalc(p->beta[i][j][k].pm, p->beta0[i][j][k].pm);
        p->gamma[i][j][k].mp =
            gammaCalc(p->beta[i][j][k].mp, p->beta0[i][j][k].mp);
        p->gamma[i][j][k].mm =
            gammaCalc(p->beta[i][j][k].mm, p->beta0[i][j][k].mm);
    }

    if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
        p->Fsi[i][j][k].pp = -1 * FsCalc(p->gamma[i][j][k].pp,
                                         p->li[i][j][k].norm, p->hi[i][j][k]);
        p->Fsi[i][j][k].pm = -1 * FsCalc(p->gamma[i][j][k].pm,
                                         p->li[i][j][k].norm, p->hi[i][j][k]);
    } else {
        p->Fsi[i][j][k].pp = 0;
        p->Fsi[i][j][k].pm = 0;
    }

    if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
        p->Fsi[i][j][k].mp =
            -1 * FsCalc(p->gamma[i][j][k].mp, p->li[i - 1][j][k].norm,
                        p->hi[i - 1][j][k]);
        p->Fsi[i][j][k].mm =
            -1 * FsCalc(p->gamma[i][j][k].mm, p->li[i - 1][j][k].norm,
                        p->hi[i - 1][j][k]);
    } else {
        p->Fsi[i][j][k].mp = 0;
        p->Fsi[i][j][k].mm = 0;
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
    } else {
        p->Fsj[i][j][k].pp = 0;
        p->Fsj[i][j][k].mp = 0;
    }
    if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
        p->Fsj[i][j][k].pm =
            -1 * FsCalc(p->gamma[i][j][k].pm, p->lj[i][j - 1][k].norm,
                        p->hj[i][j - 1][k]);
        p->Fsj[i][j][k].mm =
            -1 * FsCalc(p->gamma[i][j][k].mm, p->lj[i][j - 1][k].norm,
                        p->hj[i][j - 1][k]);
    } else {
        p->Fsj[i][j][k].pm = 0;
        p->Fsj[i][j][k].mm = 0;
    }

    if (p->flag[i][j][k] & Right) {
        if (!param->boundary.right_share_fix) {
            p->Fsj[i][j][k].pp = 0;
            p->Fsj[i][j][k].pm = 0;
            p->Fsj[i][j][k].mp = 0;
            p->Fsj[i][j][k].mm = 0;
        }
    }
    if (p->flag[i][j][k] & Left) {
        if (!param->boundary.left_share_fix) {
            p->Fsj[i][j][k].pp = 0;
            p->Fsj[i][j][k].pm = 0;
            p->Fsj[i][j][k].mp = 0;
            p->Fsj[i][j][k].mm = 0;
        }
    }
    if (p->flag[i][j][k] & Top) {
        if (!param->boundary.top_share_fix) {
            p->Fsi[i][j][k].pp = 0;
            p->Fsi[i][j][k].pm = 0;
            p->Fsi[i][j][k].mp = 0;
            p->Fsi[i][j][k].mm = 0;
        }
    }
    if (p->flag[i][j][k] & Bottom) {
        if (!param->boundary.bottom_share_fix) {
            p->Fsi[i][j][k].pp = 0;
            p->Fsi[i][j][k].pm = 0;
            p->Fsi[i][j][k].mp = 0;
            p->Fsi[i][j][k].mm = 0;
        }
    }
}

/**
 * @brief BendForceCalc
 *
 * @param i
 * @param j
 * @param k
 */
void MultiParticle::BendForceCalc(const int& i, const int& j, const int& k) {
    double norm_j_plus  = 0;
    double norm_j_minus = 0;
    double norm_i_plus  = 0;
    double norm_i_minus = 0;
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
    }
    {//TODO
        if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
            norm_j_plus = normCalcV2(p->mj[i][j][k], p->c[i][j][k]);
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
            norm_j_minus = normCalcV2(p->c[i][j][k], p->mj[i][j - 1][k]);
        }
        p->Ii[i][j][k] = (norm_j_plus + norm_j_minus) * p->h_ave3[i][j][k];
    }

    {
        if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
            norm_i_plus = normCalcV2(p->mi[i][j][k], p->c[i][j][k]);
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
            norm_i_minus = normCalcV2(p->c[i][j][k], p->mi[i - 1][j][k]);
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
#ifdef __INERTIAMOMENT__
        p->Ii[i][j][k] = InertiaMomentCalc(p->alphaj[i][j][k] / 2, norm_j_plus,
                              norm_j_minus, p->h_ave[i][j][k]);
#endif
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

#ifdef __INERTIAMOMENT__
        p->Ij[i][j][k] = InertiaMomentCalc(p->alphai[i][j][k] / 2, norm_i_plus,
                              norm_i_minus, p->h_ave[i][j][k]);
#endif
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

    {
        C li_left, li_right;
        double li_left_norm  = 0;
        double li_right_norm = 0;
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
        C lj_bottom, lj_top;
        double lj_bottom_norm = 0;
        double lj_top_norm    = 0;
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

    p->diff_etai[i][j][k] = p->etai[i][j][k] - p->etai0[i][j][k];
    p->diff_etaj[i][j][k] = p->etaj[i][j][k] - p->etaj0[i][j][k];

#ifdef __CREASE__
    if(p->j_specialflag[i][j][k] == 1){
        p->Mi[i][j][k] = 
            creaseMCalc(norm_j_plus+norm_j_minus, -1*p->alphai[i][j][k]+p->alphai0[i][j][k], -1*p->alphaj[i][j][k]+p->alphaj0[i][j][k]);
        // cout << "this is a crease" << endl;
    }
    else {
        p->Mi[i][j][k] =
            MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k], p->diff_etaj[i][j][k]);
    }
    if(p->i_specialflag[i][j][k] == 1){
        p->Mj[i][j][k] = 
            creaseMCalc(norm_i_plus+norm_i_minus, -1*p->alphaj[i][j][k]+p->alphaj0[i][j][k], -1*p->alphai[i][j][k]+p->alphai0[i][j][k]);
        // cout << "this is a crease" << endl;
    }
    else {
        p->Mj[i][j][k] =
            MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k], p->diff_etai[i][j][k]);

    }
#else
    p->Mi[i][j][k] =
        MCalc(p->Ii[i][j][k], p->diff_etai[i][j][k], p->diff_etaj[i][j][k]);
    p->Mj[i][j][k] =
        MCalc(p->Ij[i][j][k], p->diff_etaj[i][j][k], p->diff_etai[i][j][k]);
#endif
    if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
        p->Fb[i][j][k].ipv = -1 * p->Mi[i][j][k] / p->li[i][j][k].norm;
    }
    if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
        p->Fb[i][j][k].imv = -1 * p->Mi[i][j][k] / p->li[i - 1][j][k].norm;
    }
    if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
        p->Fb[i][j][k].jpv = -1 * p->Mj[i][j][k] / p->lj[i][j][k].norm;
    }
    if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
        p->Fb[i][j][k].jmv = -1 * p->Mj[i][j][k] / p->lj[i][j - 1][k].norm;
    }

    if (p->flag[i][j][k] & Right) {
        if (!param->boundary.right_bend_fix) {
            p->Fb[i][j][k].ipv = 0;
            if (!param->boundary.right_free) {
                p->Fb[i][j][k].imv = 0;
            }
        }
    }
    if (p->flag[i][j][k] & Left) {
        if (!param->boundary.left_bend_fix) {
            if (!param->boundary.left_free) {
                p->Fb[i][j][k].ipv = 0;
            }
            p->Fb[i][j][k].imv = 0;
        }
    }
    if (p->flag[i][j][k] & Top) {
        if (!param->boundary.top_bend_fix) {
            p->Fb[i][j][k].jpv = 0;
            if (!param->boundary.top_free) {
                p->Fb[i][j][k].jmv = 0;
            }
        }
    }
    if (p->flag[i][j][k] & Bottom) {
        if (!param->boundary.bottom_bend_fix) {
            if (!param->boundary.bottom_free) {
                p->Fb[i][j][k].jpv = 0;
            }
            p->Fb[i][j][k].jmv = 0;
        }
    }
}

/**
 * @brief Air Force and Disturbance calc
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

        //! 正規化してから内積しているので、問題なし
        p->angle_surface_sun[i][j][k] =
            math::sacos(innerProductCalc(-1.0 * p->pressure[i][j][k].unit(),
                                         p->S[i][j][k].cp.vector.unit()));

        p->Fnormal[i][j][k] = -1.0 * param->m_Pc * p->S[i][j][k].cp.norm * param->pre_eta_n
                                * pow(cos(p->angle_surface_sun[i][j][k]), 2) * p->S[i][j][k].cp.vector.unit();
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

    if (param->add_disturbance) {
        disturbance_Calc(p->disturbance[i][j][k], param->disturbance_range);
        if (param->disturbance_mode == "direct") {
            p->Fd[i][j][k] = normCalc(p->disturbance[i][j][k]);
        } else {
            p->Fd[i][j][k] = innerProductCalc(p->disturbance[i][j][k],
                                              p->S[i][j][k].cp.vector);
        }
    }
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
                ((param->m_fx * length) / param->m_Lref_x);
            // p->external_force[i][j][k].x =
            //     ((param->m_fx * (p->mj[i][j][k].y - p->mj[i][j - 1][k].y)) /
            //  param->m_Lref_x);
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
                return;
            }
            if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
                // double length = p->c[i][j][k].y - p->mj[i][j - 1][k].y;
                double length = param->m_Lref_y - p->g0[i][j - 1][k].y;
                p->external_force[i][j][k].y =
                    (param->m_fy * length) / param->m_Lref_x;
                return;
            }
            // p->external_force[i][j][k].y =
            //     (param->m_fy * (p->mj[i][j][k].y - p->mj[i][j - 1][k].y)) /
            //     param->m_Lref_x;
            p->external_force[i][j][k].y =
                (param->m_fy * (p->g0[i - 1][j][k].y - p->g0[i][j - 1][k].y)) /
                param->m_Lref_x;
        }
        return;
    }

    if (SimpleBend) {
        if (p->flag[i][j][k] & BIT_RIGHT) {
            if (!(p->surround_particle_exsit[i][j][k] & BIT_BOTTOM)) {
                double length = p->mj0[i][j][k].y - p->c[i][j][k].y;
                p->external_force[i][j][k].z =
                    -1 * (param->m_fz * length) / param->m_Lref_x;
                return;
            }
            if (!(p->surround_particle_exsit[i][j][k] & BIT_TOP)) {
                double length = p->c[i][j][k].y - p->mj0[i][j - 1][k].y;
                p->external_force[i][j][k].z =
                    -1 * (param->m_fz * length) / param->m_Lref_x;
                return;
            }
            p->external_force[i][j][k].z =
                -1 *
                (param->m_fz * (p->mj0[i][j][k].y - p->mj0[i][j - 1][k].y)) /
                param->m_Lref_x;
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
        // 折り目用の処理。後で書き換える
        if (param->oblique_move == "allFix") {
#ifdef __CREASE__ //TODO
            if (p->boomflag[i][j][k] == 1){
                return;
            }
            // switch(i){
            //     case 0:
            //     case 1:
            //     case 2:
            //          if (i == j || j == ((19 - 1) - i)) {
            //             return;
            //          }
            //          break;
            //     case 4:
            //         if (j == 3 || j == 15){ 
            //             // RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
            //             //     p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            //             // RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
            //             //     p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            //             // RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
            //             //     p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
                
            //             return;
            //         }
            //         break;
            //     case 6:
            //     case 7:
            //         if ((i - 2) == j || j == ((19 - 1) - (i - 2))) {
            //             return;
            //          }
            //          break;
            //     case 9:
            //         if (j == 6 || j == 12){ 
            //             // RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
            //             //     p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            //             // RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
            //             //     p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            //             // RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
            //             //     p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
                
            //             return;
            //         }
            //         break;
            //     case 11:
            //     case 12:
            //         if ((i - 4) == j || j == ((19 - 1) - (i - 4))) {
            //             return;
            //          }
            //          break;
            //     case 14:
            //         if (j == 9){ 
            //             // RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
            //             //     p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            //             // RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
            //             //     p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            //             // RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
            //             //     p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
                
            //             return;
            //         }
            //         break;
            //     case 16:
            //     case 17:
            //         if ((i - 6) == j || j == ((19 - 1) - (i - 6))) {
            //             return;
            //          }
            //          break;
            //     case 19:
            //         if (j == 12 || j == 6){ 
            //             // RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
            //             //     p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            //             // RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
            //             //     p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            //             // RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
            //             //     p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
                
            //             return;
            //         }
            //         break;
            //     case 21:
            //     case 22:
            //         if ((i - 8) == j || j == ((19 - 1) - (i - 8))) {
            //             return;
            //          }
            //          break;
            //     case 24:
            //         if (j == 15 || j == 3){ 
            //             // RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
            //             //     p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            //             // RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
            //             //     p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            //             // RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
            //             //     p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
                
            //             return;
            //         }
            //         break;
            //     case 26:
            //     case 27:
            //     case 28:
            //         if ((i - 10) == j || j == ((19 - 1) - (i - 10))) {
            //             return;
            //          }
            //          break;
            //     default:
            //         break;
            // }
            // if (p->j_specialflag[i][j][k] == 3){
            //     return;
            // }
#else // not crease
            if (i == j || j == (((int)p->flag.size() - 1) - i)) {
                return;
            }
#endif
            
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
                 p->f[i][j][k].x + p->external_force[i][j][k].x + p->F_roll[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                 p->f[i][j][k].y + p->external_force[i][j][k].y + p->F_roll[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                 p->f[i][j][k].z + p->external_force[i][j][k].z + p->F_roll[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
        } else {
#ifdef __CREASE__
            if((p->i_specialflag[i][j][k]) || (p->j_specialflag[i][j][k])){
                RK4MCrease(p->c[i][j][k].x, p->v[i][j][k].x,
                    p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
                RK4MCrease(p->c[i][j][k].y, p->v[i][j][k].y,
                    p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
                RK4MCrease(p->c[i][j][k].z, p->v[i][j][k].z,
                    p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
                // cout << "this is a crease" << endl;
            }
            else{
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                    p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                    p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                    p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
        
            }
#else
            RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
    
#endif
        }
        return;
    }

    // RIghtTopなどで boundary.top_moveが反映されない
    // Right LeftはTop Bottomより優先される
    if (param->roll_inertia_system) {
        if (p->flag[i][j][k] & Right) {
            if (param->boundary.right_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x + p->F_roll[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            }
            if (param->boundary.right_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y + p->F_roll[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            }
            if (param->boundary.right_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z + p->F_roll[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
            }
            return;
        }
        if (p->flag[i][j][k] & Left) {
            if (param->boundary.left_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x + p->F_roll[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            }
            if (param->boundary.left_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y + p->F_roll[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            }
            if (param->boundary.left_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z + p->F_roll[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
            }
            return;
        }
        if (p->flag[i][j][k] & Top) {
            if (param->boundary.top_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x + p->F_roll[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            }
            if (param->boundary.top_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y + p->F_roll[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            }
            if (param->boundary.top_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z + p->F_roll[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
            }
            return;
        }
        if (p->flag[i][j][k] & Bottom) {
            if (param->boundary.bottom_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x + p->F_roll[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            }
            if (param->boundary.bottom_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y + p->F_roll[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            }
            if (param->boundary.bottom_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z + p->F_roll[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
            }
            return;
        }
    } else {
        if (p->flag[i][j][k] & Right) {
            if (param->boundary.right_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            }
            if (param->boundary.right_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            }
            if (param->boundary.right_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
            }
            return;
        }
        if (p->flag[i][j][k] & Left) {
            if (param->boundary.left_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            }
            if (param->boundary.left_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            }
            if (param->boundary.left_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
            }
            return;
        }
        if (p->flag[i][j][k] & Top) {
            if (param->boundary.top_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            }
            if (param->boundary.top_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            }
            if (param->boundary.top_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
            }
            return;
        }
        if (p->flag[i][j][k] & Bottom) {
            if (param->boundary.bottom_move.x) {
                RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
                     p->f[i][j][k].x + p->external_force[i][j][k].x, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].x);
            }
            if (param->boundary.bottom_move.y) {
                RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
                     p->f[i][j][k].y + p->external_force[i][j][k].y, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].y);
            }
            if (param->boundary.bottom_move.z) {
                RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
                     p->f[i][j][k].z + p->external_force[i][j][k].z, p->S0[i][j][k], p->external_force_by_pressure[i][j][k].z);
            }
            return;
        }
    }
}
