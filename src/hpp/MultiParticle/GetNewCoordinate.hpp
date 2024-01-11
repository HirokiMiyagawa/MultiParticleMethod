/**
 * @file 		GetNewCorrdinate.hpp
 * @details
 */

/* declaration namespace */

#if defined __SHAPE_CUBE__

void MultiParticle::GetNewCoordinate(int const& i, int const& j, int const& k) {
    if (CubePressure) {
        // cout << "Flag:" << std::bitset<8>(p->flag[i][j][k]) << ", i:" << i <<
        // " j:" << j << " k:" << k << endl;
        if (p->flag[i][j][k] & BIT_CEILING) {
            switch (p->flag[i][j][k]) {
                case (BIT_CEILING):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    p->F[i][j][k].jm = p->Ftj[i - 1][j][k] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j + 1][k].imv;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i + 1][j][k].jmv;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i - 1][j][k].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_CEILING | BIT_RIGHT):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    p->F[i][j][k].jm = p->Ftj[i - 1][j][k] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j][k - 1].imv;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i + 1][j][k].jmv;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i - 1][j][k].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_CEILING | BIT_BOTTOM):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    p->F[i][j][k].jm = p->Ftj[i][j][k - 1] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j + 1][k].imv;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i + 1][j][k].jmv;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_CEILING | BIT_TOP):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = 0;
                    p->F[i][j][k].jm = p->Ftj[i - 1][j][k] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j + 1][k].imv;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv = 0;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i - 1][j][k].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_CEILING | BIT_LEFT):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = 0;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    p->F[i][j][k].jm = p->Ftj[i][j - 1][k] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j + 1][k].imv;
                    p->F[i][j][k].imv = 0;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i + 1][j][k].jmv;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i - 1][j][k].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_CEILING | BIT_RIGHT | BIT_BOTTOM):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    p->F[i][j][k].jm = p->Ftj[i][j][k - 1] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j][k - 1].imv;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i + 1][j][k].jmv;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_CEILING | BIT_RIGHT | BIT_TOP):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = 0;
                    p->F[i][j][k].jm = p->Ftj[i - 1][j][k] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j][k - 1].imv;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv = 0;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i - 1][j][k].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_CEILING | BIT_LEFT | BIT_BOTTOM):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = 0;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    p->F[i][j][k].jm = p->Ftj[i][j][k - 1] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j + 1][k].imv;
                    p->F[i][j][k].imv = 0;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i + 1][j][k].jmv;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;
                    fConv(i, j, k);
                    break;

                case (BIT_CEILING | BIT_LEFT | BIT_TOP):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = 0;
                    p->F[i][j][k].jp = 0;
                    p->F[i][j][k].jm = p->Ftj[i][j - 1][k] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j + 1][k].imv;
                    p->F[i][j][k].imv = 0;
                    p->F[i][j][k].jpv = 0;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i - 1][j][k].jpv;

                    fConv(i, j, k);
                    break;
            }
            switch (p->flag[i][j][k]) {
                case (BIT_CEILING):
                    RK4M(p->c[i][j][k].x, p->v[i][j][k].x, p->f[i][j][k].x,
                         p->S0[i][j][k]);
                    RK4M(p->c[i][j][k].y, p->v[i][j][k].y, p->f[i][j][k].y,
                         p->S0[i][j][k]);
                    RK4M(p->c[i][j][k].z, p->v[i][j][k].z, p->f[i][j][k].z,
                         p->S0[i][j][k]);
                    break;
                    /*
            case (BIT_CEILING|BIT_RIGHT):
                    RK4M(p->c[i][j][k].x, p->v[i][j][k].x, p->f[i][j][k].x,
            p->S0[i][j][k]); RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
            p->f[i][j][k].y, p->S0[i][j][k]); RK4M(p->c[i][j][k].z,
            p->v[i][j][k].z, p->f[i][j][k].z, p->S0[i][j][k]); break; case
            (BIT_CEILING|BIT_BOTTOM): RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
            p->f[i][j][k].x, p->S0[i][j][k]); RK4M(p->c[i][j][k].y,
            p->v[i][j][k].y, p->f[i][j][k].y, p->S0[i][j][k]);
                    RK4M(p->c[i][j][k].z, p->v[i][j][k].z, p->f[i][j][k].z,
            p->S0[i][j][k]); break; case (BIT_CEILING|BIT_TOP):
            RK4M(p->c[i][j][k].y, p->v[i][j][k].y, p->f[i][j][k].y,
            p->S0[i][j][k]); RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
            p->f[i][j][k].z, p->S0[i][j][k]); break; case
            (BIT_CEILING|BIT_LEFT): RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
            p->f[i][j][k].x, p->S0[i][j][k]); RK4M(p->c[i][j][k].z,
            p->v[i][j][k].z, p->f[i][j][k].z, p->S0[i][j][k]); break; case
            (BIT_CEILING|BIT_RIGHT|BIT_BOTTOM): RK4M(p->c[i][j][k].x,
            p->v[i][j][k].x, p->f[i][j][k].x, p->S0[i][j][k]);
            RK4M(p->c[i][j][k].y, p->v[i][j][k].y, p->f[i][j][k].y,
            p->S0[i][j][k]); RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
            p->f[i][j][k].z, p->S0[i][j][k]); break; case
            (BIT_CEILING|BIT_RIGHT|BIT_TOP): RK4M(p->c[i][j][k].y,
            p->v[i][j][k].y, p->f[i][j][k].y, p->S0[i][j][k]);
            RK4M(p->c[i][j][k].z, p->v[i][j][k].z, p->f[i][j][k].z,
            p->S0[i][j][k]); break; case (BIT_CEILING|BIT_LEFT|BIT_BOTTOM):
            RK4M(p->c[i][j][k].x, p->v[i][j][k].x, p->f[i][j][k].x,
            p->S0[i][j][k]); RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
            p->f[i][j][k].z, p->S0[i][j][k]); break; case
            (BIT_CEILING|BIT_LEFT|BIT_TOP): RK4M(p->c[i][j][k].z,
            p->v[i][j][k].z, p->f[i][j][k].z, p->S0[i][j][k]); break;
                    */
                default:
                    break;
            }
        } else if (p->flag[i][j][k] & BIT_BACK) {
            switch (p->flag[i][j][k]) {
                case (BIT_BACK):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i - 1][j][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    p->F[i][j][k].jm = p->Ftj[i][j][k - 1] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i + 1][j][k].imv;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i - 1][j][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i][j][k + 1].jmv;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_BACK | BIT_RIGHT):
                    p->F[i][j][k].ip = 0;
                    p->F[i][j][k].im = p->Fti[i - 1][j][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    p->F[i][j][k].jm = p->Ftj[i][j - 1][k] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv  = p->Fa[i][j][k];
                    p->F[i][j][k].ipv = 0;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i - 1][j][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i][j][k + 1].jmv;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_BACK | BIT_BOTTOM):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i - 1][j][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    p->F[i][j][k].jm = 0;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i + 1][j][k].imv;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i - 1][j][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i][j][k + 1].jmv;
                    p->F[i][j][k].jmv = 0;

                    fConv(i, j, k);
                    break;

                case (BIT_BACK | BIT_TOP):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i - 1][j][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = 0;
                    p->F[i][j][k].jm = p->Ftj[i][j][k - 1] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i + 1][j][k].imv;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i - 1][j][k].ipv;
                    p->F[i][j][k].jpv = 0;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_BACK | BIT_LEFT):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    p->F[i][j][k].jm = p->Ftj[i][j - 1][k] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i + 1][j][k].imv;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i][j][k + 1].jmv;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_BACK | BIT_RIGHT | BIT_BOTTOM):
                    p->F[i][j][k].ip = 0;
                    p->F[i][j][k].im = p->Fti[i - 1][j][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    // p->F[i][j][k].jp = p->Ftj[i][j][k];
                    p->F[i][j][k].jm  = 0;
                    p->F[i][j][k].sv  = p->Fa[i][j][k];
                    p->F[i][j][k].ipv = 0;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i - 1][j][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i][j][k + 1].jmv;
                    p->F[i][j][k].jmv = 0;

                    fConv(i, j, k);
                    break;

                case (BIT_BACK | BIT_RIGHT | BIT_TOP):
                    p->F[i][j][k].ip = 0;
                    p->F[i][j][k].im = p->Fti[i - 1][j][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = 0;
                    p->F[i][j][k].jm = p->Ftj[i][j][k - 1] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    // p->F[i][j][k].jm = p->Ftj[i][j][k - 1];
                    p->F[i][j][k].sv  = p->Fa[i][j][k];
                    p->F[i][j][k].ipv = 0;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i - 1][j][k].ipv;
                    p->F[i][j][k].jpv = 0;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_BACK | BIT_LEFT | BIT_BOTTOM):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    // p->F[i][j][k].jp = p->Ftj[i][j][k];
                    p->F[i][j][k].jm = 0;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i + 1][j][k].imv;
                    // p->F[i][j][k].imv = 0;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i][j][k + 1].jmv;
                    p->F[i][j][k].jmv = 0;

                    fConv(i, j, k);
                    break;

                case (BIT_BACK | BIT_LEFT | BIT_TOP):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = 0;
                    p->F[i][j][k].jp = 0;
                    p->F[i][j][k].jm = p->Ftj[i][j][k - 1] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    // p->F[i][j][k].jm = p->Ftj[i][j][k - 1];
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i + 1][j][k].imv;
                    p->F[i][j][k].imv = 0;
                    p->F[i][j][k].jpv = 0;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;
            }
            switch (p->flag[i][j][k]) {
                case (BIT_BACK):
                    RK4M(p->c[i][j][k].x, p->v[i][j][k].x, p->f[i][j][k].x,
                         p->S0[i][j][k]);
                    RK4M(p->c[i][j][k].y, p->v[i][j][k].y, p->f[i][j][k].y,
                         p->S0[i][j][k]);
                    RK4M(p->c[i][j][k].z, p->v[i][j][k].z, p->f[i][j][k].z,
                         p->S0[i][j][k]);
                    break;
                    /*
            case (BIT_BACK | BIT_RIGHT):
                    RK4M(p->c[i][j][k].y, p->v[i][j][k].y, p->f[i][j][k].y,
            p->S0[i][j][k]); RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
            p->f[i][j][k].z, p->S0[i][j][k]); break; case (BIT_BACK |
            BIT_BOTTOM): RK4M(p->c[i][j][k].x, p->v[i][j][k].x, p->f[i][j][k].x,
            p->S0[i][j][k]); RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
            p->f[i][j][k].y, p->S0[i][j][k]); break; case (BIT_BACK | BIT_TOP):
                    RK4M(p->c[i][j][k].x, p->v[i][j][k].x, p->f[i][j][k].x,
            p->S0[i][j][k]); RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
            p->f[i][j][k].y, p->S0[i][j][k]); RK4M(p->c[i][j][k].z,
            p->v[i][j][k].z, p->f[i][j][k].z, p->S0[i][j][k]); break; case
            (BIT_BACK | BIT_LEFT): RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
            p->f[i][j][k].x, p->S0[i][j][k]); RK4M(p->c[i][j][k].y,
            p->v[i][j][k].y, p->f[i][j][k].y, p->S0[i][j][k]);
            RK4M(p->c[i][j][k].z, p->v[i][j][k].z, p->f[i][j][k].z,
            p->S0[i][j][k]); break; case (BIT_BACK|BIT_RIGHT|BIT_BOTTOM):
            RK4M(p->c[i][j][k].y, p->v[i][j][k].y, p->f[i][j][k].y,
            p->S0[i][j][k]); break; case (BIT_BACK | BIT_RIGHT | BIT_TOP):
            RK4M(p->c[i][j][k].y, p->v[i][j][k].y, p->f[i][j][k].y,
            p->S0[i][j][k]); RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
            p->f[i][j][k].z, p->S0[i][j][k]); break; case
            (BIT_BACK|BIT_LEFT|BIT_BOTTOM): RK4M(p->c[i][j][k].x,
            p->v[i][j][k].x, p->f[i][j][k].x, p->S0[i][j][k]);
            RK4M(p->c[i][j][k].y, p->v[i][j][k].y, p->f[i][j][k].y,
            p->S0[i][j][k]); break; case (BIT_BACK|BIT_LEFT|BIT_TOP):
            RK4M(p->c[i][j][k].x, p->v[i][j][k].x, p->f[i][j][k].x,
            p->S0[i][j][k]); RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
            p->f[i][j][k].y, p->S0[i][j][k]); RK4M(p->c[i][j][k].z,
            p->v[i][j][k].z, p->f[i][j][k].z, p->S0[i][j][k]); break;
                    */
                default:
                    break;
            }
        } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
            switch (p->flag[i][j][k]) {
                case (BIT_RIGHTSIDE):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    p->F[i][j][k].jm = p->Ftj[i][j][k - 1] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j + 1][k].imv;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i][j][k + 1].jmv;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_RIGHTSIDE | BIT_RIGHT):
                    p->F[i][j][k].ip = 0;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    // p->F[i][j][k].jp = p->Ftj[i][j][k];
                    p->F[i][j][k].jm = p->Ftj[i][j][k - 1] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    // p->F[i][j][k].jm = p->Ftj[i][j][k - 1];
                    p->F[i][j][k].sv  = p->Fa[i][j][k];
                    p->F[i][j][k].ipv = 0;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i][j][k + 1].jmv;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_RIGHTSIDE | BIT_BOTTOM):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    p->F[i][j][k].jm = 0;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j + 1][k].imv;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i][j][k + 1].jmv;
                    p->F[i][j][k].jmv = 0;

                    fConv(i, j, k);
                    break;

                case (BIT_RIGHTSIDE | BIT_TOP):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = 0;
                    p->F[i][j][k].jm = p->Ftj[i][j][k - 1] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j + 1][k].imv;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv = 0;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_RIGHTSIDE | BIT_LEFT):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = 0;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    // p->F[i][j][k].jp = p->Ftj[i][j][k];
                    p->F[i][j][k].jm = p->Ftj[i][j - 1][k] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    p->F[i][j][k].jm = p->Ftj[i][j][k - 1];
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j + 1][k].imv;
                    p->F[i][j][k].imv = 0;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i][j][k + 1].jmv;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_BOTTOM):
                    p->F[i][j][k].ip = 0;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    // p->F[i][j][k].jp = p->Ftj[i][j][k];
                    p->F[i][j][k].jm  = 0;
                    p->F[i][j][k].sv  = p->Fa[i][j][k];
                    p->F[i][j][k].ipv = 0;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i][j][k + 1].jmv;
                    p->F[i][j][k].jmv = 0;

                    fConv(i, j, k);
                    break;

                case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_TOP):
                    p->F[i][j][k].ip = 0;
                    p->F[i][j][k].im = p->Fti[i][j - 1][k] +
                                       p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
                    p->F[i][j][k].jp = 0;
                    p->F[i][j][k].jm = p->Ftj[i][j][k - 1] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    // p->F[i][j][k].jm = p->Ftj[i][j][k - 1];
                    p->F[i][j][k].sv  = p->Fa[i][j][k];
                    p->F[i][j][k].ipv = 0;
                    p->F[i][j][k].imv =
                        p->Fb[i][j][k].imv - p->Fb[i][j - 1][k].ipv;
                    p->F[i][j][k].jpv = 0;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;

                case (BIT_RIGHTSIDE | BIT_LEFT | BIT_BOTTOM):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = 0;
                    p->F[i][j][k].jp = p->Ftj[i][j][k] + p->Fsj[i][j][k].pp +
                                       p->Fsj[i][j][k].mp;
                    // p->F[i][j][k].jp = p->Ftj[i][j][k];
                    p->F[i][j][k].jm = 0;
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j + 1][k].imv;
                    p->F[i][j][k].imv = 0;
                    p->F[i][j][k].jpv =
                        p->Fb[i][j][k].jpv - p->Fb[i][j][k + 1].jmv;
                    p->F[i][j][k].jmv = 0;

                    fConv(i, j, k);
                    break;

                case (BIT_RIGHTSIDE | BIT_LEFT | BIT_TOP):
                    p->F[i][j][k].ip = p->Fti[i][j][k] + p->Fsi[i][j][k].pp +
                                       p->Fsi[i][j][k].pm;
                    p->F[i][j][k].im = 0;
                    p->F[i][j][k].jp = 0;
                    p->F[i][j][k].jm = p->Ftj[i][j][k - 1] +
                                       p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
                    // p->F[i][j][k].jm = p->Ftj[i][j][k - 1];
                    p->F[i][j][k].sv = p->Fa[i][j][k];
                    p->F[i][j][k].ipv =
                        p->Fb[i][j][k].ipv - p->Fb[i][j + 1][k].imv;
                    p->F[i][j][k].imv = 0;
                    p->F[i][j][k].jpv = 0;
                    p->F[i][j][k].jmv =
                        p->Fb[i][j][k].jmv - p->Fb[i][j][k - 1].jpv;

                    fConv(i, j, k);
                    break;
            }
            switch (p->flag[i][j][k]) {
                case (BIT_RIGHTSIDE):
                    RK4M(p->c[i][j][k].x, p->v[i][j][k].x, p->f[i][j][k].x,
                         p->S0[i][j][k]);
                    RK4M(p->c[i][j][k].y, p->v[i][j][k].y, p->f[i][j][k].y,
                         p->S0[i][j][k]);
                    RK4M(p->c[i][j][k].z, p->v[i][j][k].z, p->f[i][j][k].z,
                         p->S0[i][j][k]);
                    break;
                    /*
            case (BIT_RIGHTSIDE|BIT_RIGHT):
                    RK4M(p->c[i][j][k].x, p->v[i][j][k].x, p->f[i][j][k].x,
            p->S0[i][j][k]); RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
            p->f[i][j][k].y, p->S0[i][j][k]); RK4M(p->c[i][j][k].z,
            p->v[i][j][k].z, p->f[i][j][k].z, p->S0[i][j][k]); break; case
            (BIT_RIGHTSIDE|BIT_BOTTOM): RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
            p->f[i][j][k].x, p->S0[i][j][k]); RK4M(p->c[i][j][k].y,
            p->v[i][j][k].y, p->f[i][j][k].y, p->S0[i][j][k]);
                    RK4M(p->c[i][j][k].z, p->v[i][j][k].z, p->f[i][j][k].z,
            p->S0[i][j][k]); break; case (BIT_RIGHTSIDE|BIT_TOP):
            RK4M(p->c[i][j][k].x, p->v[i][j][k].x, p->f[i][j][k].x,
            p->S0[i][j][k]); RK4M(p->c[i][j][k].y, p->v[i][j][k].y,
            p->f[i][j][k].y, p->S0[i][j][k]); RK4M(p->c[i][j][k].z,
            p->v[i][j][k].z, p->f[i][j][k].z, p->S0[i][j][k]); break; case
            (BIT_RIGHTSIDE|BIT_LEFT): RK4M(p->c[i][j][k].x, p->v[i][j][k].x,
            p->f[i][j][k].x, p->S0[i][j][k]); RK4M(p->c[i][j][k].z,
            p->v[i][j][k].z, p->f[i][j][k].z, p->S0[i][j][k]); break; case
            (BIT_RIGHTSIDE|BIT_RIGHT|BIT_BOTTOM): RK4M(p->c[i][j][k].x,
            p->v[i][j][k].x, p->f[i][j][k].x, p->S0[i][j][k]);
            RK4M(p->c[i][j][k].y, p->v[i][j][k].y, p->f[i][j][k].y,
            p->S0[i][j][k]); RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
            p->f[i][j][k].z, p->S0[i][j][k]); break; case
            (BIT_RIGHTSIDE|BIT_RIGHT|BIT_TOP): RK4M(p->c[i][j][k].x,
            p->v[i][j][k].x, p->f[i][j][k].x, p->S0[i][j][k]);
            RK4M(p->c[i][j][k].y, p->v[i][j][k].y, p->f[i][j][k].y,
            p->S0[i][j][k]); RK4M(p->c[i][j][k].z, p->v[i][j][k].z,
            p->f[i][j][k].z, p->S0[i][j][k]); break; case
            (BIT_RIGHTSIDE|BIT_LEFT|BIT_BOTTOM): RK4M(p->c[i][j][k].x,
            p->v[i][j][k].x, p->f[i][j][k].x, p->S0[i][j][k]); break; case
            (BIT_RIGHTSIDE|BIT_LEFT|BIT_TOP): RK4M(p->c[i][j][k].x,
            p->v[i][j][k].x, p->f[i][j][k].x, p->S0[i][j][k]);
                    RK4M(p->c[i][j][k].z, p->v[i][j][k].z, p->f[i][j][k].z,
            p->S0[i][j][k]); break;
                    */
                default:
                    break;
            }
        }
    }
}
#endif

//*
void MultiParticle::GetNewCoordinate(int const& i, int const& j, int const& k) {
    // within membrane
    if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
        // Tensile and Share
        p->F[i][j][k].ip =
            p->Fti[i][j][k] + p->Fsi[i][j][k].pp + p->Fsi[i][j][k].pm;
#ifdef __CREASECALUCULATION__
        // cout << "creaseflag: " << p->j_specialflag[i + 1][j][k] << endl;
        // if ((p->j_specialflag[i + 1][j][k] == 3) || (p->j_specialflag[i + 1][j][k] == 4)){
        //     // cout << "checki+1" << endl;
        //     p->F[i][j][k].ip += p->Fti[i + 1][j][k] + p->Fsi[i + 1][j][k].pp + p->Fsi[i + 1][j][k].pm;
        // }
#endif

        // bend
#ifdef __CREASE__ 
        if (p->j_specialflag[i + 1][j][k] == 10){//not use
            // cout << "this is a crease" << endl;
            p->F[i][j][k].ipv = p->Fb[i][j][k].ipv;
        }
        else if (p->j_specialflag[i][j][k] == 10){//not use
            // cout << "this is a crease" << endl;
            p->F[i][j][k].ipv = -1 * p->Fb[i + 1][j][k].imv;
        }
        else{
            p->F[i][j][k].ipv = p->Fb[i][j][k].ipv - p->Fb[i + 1][j][k].imv;
        }
#else
        p->F[i][j][k].ipv = p->Fb[i][j][k].ipv - p->Fb[i + 1][j][k].imv;
#endif 
#ifdef __CREASECALUCULATION__
        if ((p->j_specialflag[i + 1][j][k] == 3) || (p->j_specialflag[i + 1][j][k] == 4)){
            // cout << "checki+1B" << endl;
            p->F[i][j][k].ipv = p->Fb[i][j][k].ipv - p->Fb[i + 2][j][k].imv;
        }
#endif //__CREASECALUCULATION__
        // p->F[i][j][k].ipv = p->Fb[i + 1][j][k].imv;
    } else {
        p->F[i][j][k].ip  = 0;
        p->F[i][j][k].ipv = 0;
    }

    if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
        // Tensile and Share
        p->F[i][j][k].im =
            p->Fti[i - 1][j][k] + p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
#ifdef __CREASECALUCULATION__
        if ((p->j_specialflag[i - 1][j][k] == 3) || (p->j_specialflag[i - 1][j][k] == 4)){
            // cout << "checki-1" << endl;
            p->F[i][j][k].im = p->Fti[i - 2][j][k] + p->Fsi[i][j][k].mp + p->Fsi[i][j][k].mm;
        }
#endif
        // bend
#ifdef __CREASE__ 
        if (p->j_specialflag[i - 1][j][k] == 10){
            // cout << "this is a crease" << endl;
            p->F[i][j][k].imv = p->Fb[i][j][k].imv;
        }
        else if (p->j_specialflag[i][j][k] == 10){
            // cout << "this is a crease" << endl;
            p->F[i][j][k].imv = -1 * p->Fb[i - 1][j][k].ipv;
        }
        else{
            p->F[i][j][k].imv = p->Fb[i][j][k].imv - p->Fb[i - 1][j][k].ipv;
        }
#else
        p->F[i][j][k].imv = p->Fb[i][j][k].imv - p->Fb[i - 1][j][k].ipv;
#endif 
#ifdef __CREASECALUCULATION__
        if ((p->j_specialflag[i - 1][j][k] == 3) || (p->j_specialflag[i - 1][j][k] == 4)){
            // cout << "checki-1B" << endl;
            p->F[i][j][k].imv = p->Fb[i][j][k].imv - p->Fb[i - 2][j][k].ipv;
        }
#endif
        // p->F[i][j][k].imv = p->Fb[i - 1][j][k].ipv;
    } else {
        p->F[i][j][k].im  = 0;
        p->F[i][j][k].imv = 0;
    }

    if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
        // Tensile and Share
        p->F[i][j][k].jp =
            p->Ftj[i][j][k] + p->Fsj[i][j][k].pp + p->Fsj[i][j][k].mp;
#ifdef __CREASECALUCULATION__
        // if ((p->i_specialflag[i][j + 1][k] == 3) || (p->i_specialflag[i][j + 1][k] == 4)){
        //     p->F[i][j][k].jp +=
        //         p->Ftj[i][j + 1][k] + p->Fsj[i][j + 1][k].pp + p->Fsj[i][j + 1][k].mp;
        // }
#endif // __CREASECALUCULATION__
        // bend
#ifdef __CREASE__ 
        if (p->i_specialflag[i][j + 1][k] == 10){
            // cout << "this is a crease" << endl;
            p->F[i][j][k].jpv = p->Fb[i][j][k].jpv;
        }
        else if (p->i_specialflag[i][j][k] == 10){
            // cout << "this is a crease" << endl;
            p->F[i][j][k].jpv = -1 * p->Fb[i][j + 1][k].jmv;
        }
        else{
            p->F[i][j][k].jpv = p->Fb[i][j][k].jpv - p->Fb[i][j + 1][k].jmv;
        }
#else
        p->F[i][j][k].jpv = p->Fb[i][j][k].jpv - p->Fb[i][j + 1][k].jmv;
#endif 
#ifdef __CREASECALUCULATION__
        if ((p->i_specialflag[i][j + 1][k] == 3) || (p->i_specialflag[i][j + 1][k] == 4)){
            p->F[i][j][k].jpv = p->Fb[i][j][k].jpv - p->Fb[i][j + 2][k].jmv;
        }
#endif // __CREASECALUCULATION__
        // p->F[i][j][k].jpv = p->Fb[i][j + 1][k].jmv;
    } else {
        p->F[i][j][k].jp  = 0;
        p->F[i][j][k].jpv = 0;
    }

    if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
        // Tensile and Share
        p->F[i][j][k].jm =
            p->Ftj[i][j - 1][k] + p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
#ifdef __CREASECALUCULATION__
        if ((p->i_specialflag[i][j - 1][k] == 3) || (p->i_specialflag[i][j - 1][k] == 4)){
            p->F[i][j][k].jm =
                p->Ftj[i][j - 2][k] + p->Fsj[i][j][k].pm + p->Fsj[i][j][k].mm;
        }
#endif // __CREASECALUCULATION__
        // bend
#ifdef __CREASE__ 
        if (p->i_specialflag[i][j - 1][k] == 10){
            // cout << "this is a crease" << endl;
            p->F[i][j][k].jmv = p->Fb[i][j][k].jmv;
        }
        else if (p->i_specialflag[i][j][k] == 10){
            // cout << "this is a crease" << endl;
            p->F[i][j][k].jmv = -1 * p->Fb[i][j - 1][k].jpv;
        }
        else{
            p->F[i][j][k].jmv = p->Fb[i][j][k].jmv - p->Fb[i][j - 1][k].jpv;
        }
#else
        p->F[i][j][k].jmv = p->Fb[i][j][k].jmv - p->Fb[i][j - 1][k].jpv;
#endif 
#ifdef __CREASECALUCULATION__
        if ((p->i_specialflag[i][j - 1][k] == 3) || (p->i_specialflag[i][j - 1][k] == 4)){
            p->F[i][j][k].jmv = p->Fb[i][j][k].jmv - p->Fb[i][j - 2][k].jpv;
        }
#endif // __CREASECALUCULATION__
        // p->F[i][j][k].jmv = p->Fb[i][j - 1][k].jpv;
    } else {
        p->F[i][j][k].jm  = 0;
        p->F[i][j][k].jmv = 0;
    }

    // if (((p->flag[i][j][k] & Top) && (!param->boundary.top_share_fix) ||
    //      (p->flag[i][j][k] & Bottom) && (!param->boundary.bottom_share_fix)))
    //      {
    //     p->F[i][j][k].ip = p->Fti[i][j][k];
    //     if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
    //         p->F[i][j][k].im = p->Fti[i - 1][j][k];
    //     }
    // }
    // if (((p->flag[i][j][k] & Right) && (!param->boundary.right_share_fix) ||
    //      (p->flag[i][j][k] & Left) && (!param->boundary.left_share_fix))) {
    //     p->F[i][j][k].jp = p->Ftj[i][j][k];
    //     if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
    //         p->F[i][j][k].jm = p->Ftj[i][j - 1][k];
    //     }
    // }

    // if (p->flag[i][j][k] & Right) {
    //     if (!param->boundary.right_bend_fix) {
    //         p->F[i][j][k].ipv = 0;
    //         p->F[i][j][k].imv = 0;
    //     }
    // }
    // if (p->flag[i][j][k] & Left) {
    //     if (!param->boundary.left_bend_fix) {
    //         p->F[i][j][k].ipv = 0;
    //         p->F[i][j][k].imv = 0;
    //     }
    // }
    // if (p->flag[i][j][k] & Top) {
    //     if (!param->boundary.top_bend_fix) {
    //         p->F[i][j][k].jpv = 0;
    //         p->F[i][j][k].jmv = 0;
    //     }
    // }
    // if (p->flag[i][j][k] & Bottom) {
    //     if (!param->boundary.bottom_bend_fix) {
    //         p->F[i][j][k].jpv = 0;
    //         p->F[i][j][k].jmv = 0;
    //     }
    // }

    fConv(i, j, k);

    // p->f[i][j][k] += p->Fb[i][j][k].ipmv;
    // p->f[i][j][k] += p->Fb[i][j][k].jpmv;

    if (param->add_disturbance) {
        if (param->disturbance_mode == "direct") {
            p->f[i][j][k] += p->disturbance[i][j][k];
        } else {
            p->f[i][j][k].x += (p->Fd[i][j][k] * p->S[i][j][k].cp.vector.x /
                                p->S[i][j][k].cp.norm);
            p->f[i][j][k].y += (p->Fd[i][j][k] * p->S[i][j][k].cp.vector.y /
                                p->S[i][j][k].cp.norm);
            p->f[i][j][k].z += (p->Fd[i][j][k] * p->S[i][j][k].cp.vector.z /
                                p->S[i][j][k].cp.norm);
        }
    }
}
//*/
