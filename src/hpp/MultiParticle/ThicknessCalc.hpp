/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file	ThicknessCalc.hpp
 * @brief	厚さと影響面積の計算
 * @details
 * ///////////////////////////////////////////////////////////////////////////////
 */

#if defined __SHAPE_CUBE__
void MultiParticle::ThicknessCalc(int const& i, int const& j, int const& k) {
    if (p->flag[i][j][k] & BIT_CEILING) {
        switch (p->flag[i][j][k]) {
            case (BIT_CEILING):

                p->S[i][j][k].i.x =
                    (p->li[i][j - 1][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i][j - 1][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i][j - 1][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x =
                    (p->lj[i - 1][j][k].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y =
                    (p->lj[i - 1][j][k].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z =
                    (p->lj[i - 1][j][k].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i + 1][j][k].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j][k].vector.x + p->li[i - 1][j][k].vector.x) /
                    4;
                p->Si[i][j][k].i.y =
                    (p->li[i + 1][j][k].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j][k].vector.y + p->li[i - 1][j][k].vector.y) /
                    4;
                p->Si[i][j][k].i.z =
                    (p->li[i + 1][j][k].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j][k].vector.z + p->li[i - 1][j][k].vector.z) /
                    4;

                p->Si[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x +
                     p->lj[i - 1][j + 1][k].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i - 1][j][k].vector.x) /
                    4;
                p->Si[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y +
                     p->lj[i - 1][j + 1][k].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i - 1][j][k].vector.y) /
                    4;
                p->Si[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z +
                     p->lj[i - 1][j + 1][k].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i - 1][j][k].vector.z) /
                    4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x =
                    (p->li[i + 1][j][k].vector.x +
                     p->li[i + 1][j - 1][k].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].i.y =
                    (p->li[i + 1][j][k].vector.y +
                     p->li[i + 1][j - 1][k].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].i.z =
                    (p->li[i + 1][j][k].vector.z +
                     p->li[i + 1][j - 1][k].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j - 1][k].vector.z) /
                    4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) /
                    4;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_CEILING | BIT_LEFT):

                p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x =
                    (p->lj[i - 1][j][k].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y =
                    (p->lj[i - 1][j][k].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z =
                    (p->lj[i - 1][j][k].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i + 1][j][k].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j][k].vector.x + p->li[i - 1][j][k].vector.x) /
                    4;
                p->Si[i][j][k].i.y =
                    (p->li[i + 1][j][k].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j][k].vector.y + p->li[i - 1][j][k].vector.y) /
                    4;
                p->Si[i][j][k].i.z =
                    (p->li[i + 1][j][k].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j][k].vector.z + p->li[i - 1][j][k].vector.z) /
                    4;

                p->Si[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x +
                     p->lj[i - 1][j + 1][k].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i - 1][j][k].vector.x) /
                    4;
                p->Si[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y +
                     p->lj[i - 1][j + 1][k].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i - 1][j][k].vector.y) /
                    4;
                p->Si[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z +
                     p->lj[i - 1][j + 1][k].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i - 1][j][k].vector.z) /
                    4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x =
                    (p->li[i + 1][j][k].vector.x + p->li[i][j][k].vector.x) / 4;
                p->Sj[i][j][k].i.y =
                    (p->li[i + 1][j][k].vector.y + p->li[i][j][k].vector.y) / 4;
                p->Sj[i][j][k].i.z =
                    (p->li[i + 1][j][k].vector.z + p->li[i][j][k].vector.z) / 4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->Sj[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->Sj[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_CEILING | BIT_BOTTOM):

                p->S[i][j][k].i.x =
                    (p->li[i][j - 1][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i][j - 1][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i][j - 1][k].vector.z + p->li[i][j][k].vector.z) / 2;

                // p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                // p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                // p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;
                p->S[i][j][k].j.x =
                    (p->lj[i][j][k - 1].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y =
                    (p->lj[i][j][k - 1].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z =
                    (p->lj[i][j][k - 1].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                // p->Si[i][j][k].i.x = (p->li[i + 1][j][k].vector.x +
                // p->li[i][j][k].vector.x) / 2; p->Si[i][j][k].i.y = (p->li[i +
                // 1][j][k].vector.y + p->li[i][j][k].vector.y) / 2;
                // p->Si[i][j][k].i.z = (p->li[i + 1][j][k].vector.z +
                // p->li[i][j][k].vector.z) / 2;

                // p->Si[i][j][k].j.x = (p->lj[i][j + 1][k].vector.x +
                // p->lj[i][j][k].vector.x) / 4; p->Si[i][j][k].j.y =
                // (p->lj[i][j + 1][k].vector.y + p->lj[i][j][k].vector.y) / 4;
                // p->Si[i][j][k].j.z = (p->lj[i][j + 1][k].vector.z +
                // p->lj[i][j][k].vector.z) / 4;
                p->Si[i][j][k].i.x =
                    (p->li[i + 1][j][k].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j][k].vector.x + p->li[i][j][k - 1].vector.x) /
                    4;
                p->Si[i][j][k].i.y =
                    (p->li[i + 1][j][k].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j][k].vector.y + p->li[i][j][k - 1].vector.y) /
                    4;
                p->Si[i][j][k].i.z =
                    (p->li[i + 1][j][k].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j][k].vector.z + p->li[i][j][k - 1].vector.z) /
                    4;

                p->Si[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x +
                     p->lj[i][j + 1][k - 1].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k - 1].vector.x) /
                    4;
                p->Si[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y +
                     p->lj[i][j + 1][k - 1].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k - 1].vector.y) /
                    4;
                p->Si[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z +
                     p->lj[i][j + 1][k - 1].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k - 1].vector.z) /
                    4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x =
                    (p->li[i + 1][j][k].vector.x +
                     p->li[i + 1][j - 1][k].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].i.y =
                    (p->li[i + 1][j][k].vector.y +
                     p->li[i + 1][j - 1][k].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].i.z =
                    (p->li[i + 1][j][k].vector.z +
                     p->li[i + 1][j - 1][k].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j - 1][k].vector.z) /
                    4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) /
                    4;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_CEILING | BIT_RIGHT):

                // p->S[i][j][k].i.x = (p->li[i][j - 1][k].vector.x) / 2;
                // p->S[i][j][k].i.y = (p->li[i][j - 1][k].vector.y) / 2;
                // p->S[i][j][k].i.z = (p->li[i][j - 1][k].vector.z) / 2;
                p->S[i][j][k].i.x =
                    (p->li[i][j - 1][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i][j - 1][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i][j - 1][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x =
                    (p->lj[i - 1][j][k].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y =
                    (p->lj[i - 1][j][k].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z =
                    (p->lj[i - 1][j][k].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);
                ///////////// add /////////////
                p->Si[i][j][k].i.x =
                    (p->li[i + 1][j][k].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j][k].vector.x + p->li[i - 1][j][k].vector.x) /
                    4;
                p->Si[i][j][k].i.y =
                    (p->li[i + 1][j][k].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j][k].vector.y + p->li[i - 1][j][k].vector.y) /
                    4;
                p->Si[i][j][k].i.z =
                    (p->li[i + 1][j][k].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j][k].vector.z + p->li[i - 1][j][k].vector.z) /
                    4;

                p->Si[i][j][k].j.x =
                    (p->li[i][j][k - 1].vector.x +
                     p->li[i - 1][j][k - 1].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i - 1][j][k].vector.x) /
                    4;
                p->Si[i][j][k].j.y =
                    (p->li[i][j][k - 1].vector.y +
                     p->li[i - 1][j][k - 1].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i - 1][j][k].vector.y) /
                    4;
                p->Si[i][j][k].j.z =
                    (p->li[i][j][k - 1].vector.z +
                     p->li[i - 1][j][k - 1].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i - 1][j][k].vector.z) /
                    4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);
                //
                // p->Sj[i][j][k].i.x = (p->li[i + 1][j - 1][k].vector.x +
                // p->li[i][j - 1][k].vector.x) / 4; p->Sj[i][j][k].i.y =
                // (p->li[i + 1][j - 1][k].vector.y + p->li[i][j -
                // 1][k].vector.y) / 4; p->Sj[i][j][k].i.z = (p->li[i + 1][j -
                // 1][k].vector.z + p->li[i][j - 1][k].vector.z) / 4;
                p->Sj[i][j][k].i.x =
                    (p->li[i + 1][j][k].vector.x +
                     p->li[i + 1][j - 1][k].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].i.y =
                    (p->li[i + 1][j][k].vector.y +
                     p->li[i + 1][j - 1][k].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].i.z =
                    (p->li[i + 1][j][k].vector.z +
                     p->li[i + 1][j - 1][k].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j - 1][k].vector.z) /
                    4;

                // p->Sj[i][j][k].j.x = (p->lj[i][j][k].vector.x + p->lj[i][j -
                // 1][k].vector.x) / 2; p->Sj[i][j][k].j.y =
                // (p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) / 2;
                // p->Sj[i][j][k].j.z = (p->lj[i][j][k].vector.z + p->lj[i][j -
                // 1][k].vector.z) / 2;
                p->Sj[i][j][k].j.x =
                    (p->li[i][j][k - 1].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].j.y =
                    (p->li[i][j][k - 1].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].j.z =
                    (p->li[i][j][k - 1].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) /
                    4;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                // p->hi[i][j][k] = 0;
                p->hi[i][j][k] = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k] = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_CEILING | BIT_TOP):

                p->S[i][j][k].i.x =
                    (p->li[i][j - 1][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i][j - 1][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i][j - 1][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i - 1][j][k].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i - 1][j][k].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i - 1][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i][j][k].vector.x + p->li[i - 1][j][k].vector.x) / 2;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k].vector.y + p->li[i - 1][j][k].vector.y) / 2;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k].vector.z + p->li[i - 1][j][k].vector.z) / 2;

                p->Si[i][j][k].j.x = (p->lj[i - 1][j + 1][k].vector.x +
                                      p->lj[i - 1][j][k].vector.x) /
                                     4;
                p->Si[i][j][k].j.y = (p->lj[i - 1][j + 1][k].vector.y +
                                      p->lj[i - 1][j][k].vector.y) /
                                     4;
                p->Si[i][j][k].j.z = (p->lj[i - 1][j + 1][k].vector.z +
                                      p->lj[i - 1][j][k].vector.z) /
                                     4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = 0;
                break;

            case (BIT_CEILING | BIT_LEFT | BIT_BOTTOM):

                p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

                // p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                // p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                // p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;
                p->S[i][j][k].j.x =
                    (p->lj[i][j][k - 1].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y =
                    (p->lj[i][j][k - 1].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z =
                    (p->lj[i][j][k - 1].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i + 1][j][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->Si[i][j][k].i.y =
                    (p->li[i + 1][j][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->Si[i][j][k].i.z =
                    (p->li[i + 1][j][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->Si[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x + p->lj[i][j][k].vector.x) / 4;
                p->Si[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y + p->lj[i][j][k].vector.y) / 4;
                p->Si[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z + p->lj[i][j][k].vector.z) / 4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x =
                    (p->li[i + 1][j][k].vector.x + p->li[i][j][k].vector.x) / 4;
                p->Sj[i][j][k].i.y =
                    (p->li[i + 1][j][k].vector.y + p->li[i][j][k].vector.y) / 4;
                p->Sj[i][j][k].i.z =
                    (p->li[i + 1][j][k].vector.z + p->li[i][j][k].vector.z) / 4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->Sj[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->Sj[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_CEILING | BIT_RIGHT | BIT_BOTTOM):
                // what?
                // p->S[i][j][k].i.x = (p->li[i][j - 1][k].vector.x) / 2;
                // p->S[i][j][k].i.y = (p->li[i][j - 1][k].vector.y) / 2;
                // p->S[i][j][k].i.z = (p->li[i][j - 1][k].vector.z) / 2;

                // p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                // p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                // p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;
                p->S[i][j][k].i.x =
                    (p->li[i][j - 1][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i][j - 1][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i][j - 1][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x =
                    (p->lj[i][j][k - 1].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y =
                    (p->lj[i][j][k - 1].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z =
                    (p->lj[i][j][k - 1].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);
                ///////////// add /////////////
                p->Si[i][j][k].i.x =
                    (p->li[i + 1][j][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->Si[i][j][k].i.y =
                    (p->li[i + 1][j][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->Si[i][j][k].i.z =
                    (p->li[i + 1][j][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->Si[i][j][k].j.x =
                    (p->lj[i][j][k].vector.x + p->li[i][j][k - 1].vector.x) / 2;
                p->Si[i][j][k].j.y =
                    (p->lj[i][j][k].vector.y + p->li[i][j][k - 1].vector.y) / 2;
                p->Si[i][j][k].j.z =
                    (p->lj[i][j][k].vector.z + p->li[i][j][k - 1].vector.z) / 2;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);
                //
                // p->Sj[i][j][k].i.x = (p->li[i + 1][j - 1][k].vector.x +
                // p->li[i][j - 1][k].vector.x) / 4; p->Sj[i][j][k].i.y =
                // (p->li[i + 1][j - 1][k].vector.y + p->li[i][j -
                // 1][k].vector.y) / 4; p->Sj[i][j][k].i.z = (p->li[i + 1][j -
                // 1][k].vector.z + p->li[i][j - 1][k].vector.z) / 4;
                p->Sj[i][j][k].i.x =
                    (p->li[i + 1][j][k].vector.x +
                     p->li[i + 1][j - 1][k].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].i.y =
                    (p->li[i + 1][j][k].vector.y +
                     p->li[i + 1][j - 1][k].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].i.z =
                    (p->li[i + 1][j][k].vector.z +
                     p->li[i + 1][j - 1][k].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j - 1][k].vector.z) /
                    4;

                // p->Sj[i][j][k].j.x = (p->lj[i][j][k].vector.x + p->lj[i][j -
                // 1][k].vector.x) / 2; p->Sj[i][j][k].j.y =
                // (p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) / 2;
                // p->Sj[i][j][k].j.z = (p->lj[i][j][k].vector.z + p->lj[i][j -
                // 1][k].vector.z) / 2;
                p->Sj[i][j][k].j.x =
                    (p->li[i][j][k - 1].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].j.y =
                    (p->li[i][j][k - 1].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].j.z =
                    (p->li[i][j][k - 1].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) /
                    4;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                // p->hi[i][j][k] = 0;
                p->hi[i][j][k] = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k] = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_CEILING | BIT_RIGHT | BIT_TOP):

                p->S[i][j][k].i.x =
                    (p->li[i][j - 1][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i][j - 1][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i][j - 1][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i - 1][j][k].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i - 1][j][k].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i - 1][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                ///////////// add /////////////
                p->Si[i][j][k].i.x =
                    (p->li[i][j][k].vector.x + p->li[i - 1][j][k].vector.x) / 2;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k].vector.y + p->li[i - 1][j][k].vector.y) / 2;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k].vector.z + p->li[i - 1][j][k].vector.z) / 2;

                p->Si[i][j][k].j.x = (p->li[i - 1][j][k - 1].vector.x +
                                      p->lj[i - 1][j][k].vector.x) /
                                     4;
                p->Si[i][j][k].j.y = (p->li[i - 1][j][k - 1].vector.y +
                                      p->lj[i - 1][j][k].vector.y) /
                                     4;
                p->Si[i][j][k].j.z = (p->li[i - 1][j][k - 1].vector.z +
                                      p->lj[i - 1][j][k].vector.z) /
                                     4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);
                //

                // p->hi[i][j][k] = 0;
                p->hi[i][j][k] = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k] = 0;
                break;

            case (BIT_CEILING | BIT_LEFT | BIT_TOP):

                p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i - 1][j][k].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i - 1][j][k].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i - 1][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i][j][k].vector.x + p->li[i - 1][j][k].vector.x) / 4;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k].vector.y + p->li[i - 1][j][k].vector.y) / 4;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k].vector.z + p->li[i - 1][j][k].vector.z) / 4;

                p->Si[i][j][k].j.x = (p->lj[i - 1][j + 1][k].vector.x +
                                      p->lj[i - 1][j][k].vector.x) /
                                     2;
                p->Si[i][j][k].j.y = (p->lj[i - 1][j + 1][k].vector.y +
                                      p->lj[i - 1][j][k].vector.y) /
                                     2;
                p->Si[i][j][k].j.z = (p->lj[i - 1][j + 1][k].vector.z +
                                      p->lj[i - 1][j][k].vector.z) /
                                     2;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = 0;
                break;

            default:
                console(4);
                break;
        }
    } else if (p->flag[i][j][k] & BIT_BACK) {
        switch (p->flag[i][j][k]) {
            case (BIT_BACK):

                p->S[i][j][k].i.x =
                    (p->li[i - 1][j][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i - 1][j][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i - 1][j][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x =
                    (p->lj[i][j][k - 1].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y =
                    (p->lj[i][j][k - 1].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z =
                    (p->lj[i][j][k - 1].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j][k].vector.x + p->li[i][j][k - 1].vector.x) /
                    4;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j][k].vector.y + p->li[i][j][k - 1].vector.y) /
                    4;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j][k].vector.z + p->li[i][j][k - 1].vector.z) /
                    4;

                p->Si[i][j][k].j.x =
                    (p->lj[i + 1][j][k].vector.x +
                     p->lj[i + 1][j][k - 1].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k - 1].vector.x) /
                    4;
                p->Si[i][j][k].j.y =
                    (p->lj[i + 1][j][k].vector.y +
                     p->lj[i + 1][j][k - 1].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k - 1].vector.y) /
                    4;
                p->Si[i][j][k].j.z =
                    (p->lj[i + 1][j][k].vector.z +
                     p->lj[i + 1][j][k - 1].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k - 1].vector.z) /
                    4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x +
                     p->li[i - 1][j][k + 1].vector.x + p->li[i][j][k].vector.x +
                     p->li[i - 1][j][k].vector.x) /
                    4;
                p->Sj[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y +
                     p->li[i - 1][j][k + 1].vector.y + p->li[i][j][k].vector.y +
                     p->li[i - 1][j][k].vector.y) /
                    4;
                p->Sj[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z +
                     p->li[i - 1][j][k + 1].vector.z + p->li[i][j][k].vector.z +
                     p->li[i - 1][j][k].vector.z) /
                    4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i + 1][j][k].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k].vector.x + p->lj[i - 1][j][k].vector.x) /
                    4;
                p->Sj[i][j][k].j.y =
                    (p->lj[i + 1][j][k].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k].vector.y + p->lj[i - 1][j][k].vector.y) /
                    4;
                p->Sj[i][j][k].j.z =
                    (p->lj[i + 1][j][k].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k].vector.z + p->lj[i - 1][j][k].vector.z) /
                    4;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_BACK | BIT_LEFT):

                // p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                // p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                // p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;
                p->S[i][j][k].i.x =
                    (p->li[i][j - 1][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i][j - 1][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i][j - 1][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x =
                    (p->lj[i][j][k - 1].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y =
                    (p->lj[i][j][k - 1].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z =
                    (p->lj[i][j][k - 1].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j][k].vector.x + p->li[i][j][k - 1].vector.x) /
                    4;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j][k].vector.y + p->li[i][j][k - 1].vector.y) /
                    4;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j][k].vector.z + p->li[i][j][k - 1].vector.z) /
                    4;

                p->Si[i][j][k].j.x =
                    (p->lj[i + 1][j][k].vector.x +
                     p->lj[i + 1][j][k - 1].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k - 1].vector.x) /
                    4;
                p->Si[i][j][k].j.y =
                    (p->lj[i + 1][j][k].vector.y +
                     p->lj[i + 1][j][k - 1].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k - 1].vector.y) /
                    4;
                p->Si[i][j][k].j.z =
                    (p->lj[i + 1][j][k].vector.z +
                     p->lj[i + 1][j][k - 1].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k - 1].vector.z) /
                    4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

                // p->Sj[i][j][k].i.x = (p->li[i][j][k + 1].vector.x +
                // p->li[i][j][k].vector.x) / 4; p->Sj[i][j][k].i.y =
                // (p->li[i][j][k + 1].vector.y + p->li[i][j][k].vector.y) / 4;
                // p->Sj[i][j][k].i.z = (p->li[i][j][k + 1].vector.z +
                // p->li[i][j][k].vector.z) / 4;

                // p->Sj[i][j][k].j.x = (p->lj[i + 1][j][k].vector.x +
                // p->lj[i][j][k].vector.x) / 2; p->Sj[i][j][k].j.y = (p->lj[i +
                // 1][j][k].vector.y + p->lj[i][j][k].vector.y) / 2;
                // p->Sj[i][j][k].j.z = (p->lj[i + 1][j][k].vector.z +
                // p->lj[i][j][k].vector.z) / 2;
                p->Sj[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x +
                     p->li[i][j - 1][k + 1].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y +
                     p->li[i][j - 1][k + 1].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z +
                     p->li[i][j - 1][k + 1].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j - 1][k].vector.z) /
                    4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i + 1][j][k].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].j.y =
                    (p->lj[i + 1][j][k].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].j.z =
                    (p->lj[i + 1][j][k].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) /
                    4;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_BACK | BIT_BOTTOM):

                p->S[i][j][k].i.x =
                    (p->li[i - 1][j][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i - 1][j][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i - 1][j][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x + p->li[i][j][k].vector.x) / 2;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y + p->li[i][j][k].vector.y) / 2;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z + p->li[i][j][k].vector.z) / 2;

                p->Si[i][j][k].j.x =
                    (p->lj[i + 1][j][k].vector.x + p->lj[i][j][k].vector.x) / 4;
                p->Si[i][j][k].j.y =
                    (p->lj[i + 1][j][k].vector.y + p->lj[i][j][k].vector.y) / 4;
                p->Si[i][j][k].j.z =
                    (p->lj[i + 1][j][k].vector.z + p->lj[i][j][k].vector.z) / 4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x +
                     p->li[i - 1][j][k + 1].vector.x + p->li[i][j][k].vector.x +
                     p->li[i - 1][j][k].vector.x) /
                    4;
                p->Sj[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y +
                     p->li[i - 1][j][k + 1].vector.y + p->li[i][j][k].vector.y +
                     p->li[i - 1][j][k].vector.y) /
                    4;
                p->Sj[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z +
                     p->li[i - 1][j][k + 1].vector.z + p->li[i][j][k].vector.z +
                     p->li[i - 1][j][k].vector.z) /
                    4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i + 1][j][k].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k].vector.x + p->lj[i - 1][j][k].vector.x) /
                    4;
                p->Sj[i][j][k].j.y =
                    (p->lj[i + 1][j][k].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k].vector.y + p->lj[i - 1][j][k].vector.y) /
                    4;
                p->Sj[i][j][k].j.z =
                    (p->lj[i + 1][j][k].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k].vector.z + p->lj[i - 1][j][k].vector.z) /
                    4;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_BACK | BIT_RIGHT):

                p->S[i][j][k].i.x = (p->li[i - 1][j][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i - 1][j][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i - 1][j][k].vector.z) / 2;

                p->S[i][j][k].j.x =
                    (p->lj[i][j][k - 1].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y =
                    (p->lj[i][j][k - 1].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z =
                    (p->lj[i][j][k - 1].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x = (p->li[i - 1][j][k + 1].vector.x +
                                      p->li[i - 1][j][k].vector.x) /
                                     4;
                p->Sj[i][j][k].i.y = (p->li[i - 1][j][k + 1].vector.y +
                                      p->li[i - 1][j][k].vector.y) /
                                     4;
                p->Sj[i][j][k].i.z = (p->li[i - 1][j][k + 1].vector.z +
                                      p->li[i - 1][j][k].vector.z) /
                                     4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i][j][k].vector.x + p->lj[i - 1][j][k].vector.x) / 2;
                p->Sj[i][j][k].j.y =
                    (p->lj[i][j][k].vector.y + p->lj[i - 1][j][k].vector.y) / 2;
                p->Sj[i][j][k].j.z =
                    (p->lj[i][j][k].vector.z + p->lj[i - 1][j][k].vector.z) / 2;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = 0;
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_BACK | BIT_TOP):

                p->S[i][j][k].i.x =
                    (p->li[i - 1][j][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i - 1][j][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i - 1][j][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k - 1].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k - 1].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k - 1].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i][j][k].vector.x + p->li[i][j][k - 1].vector.x) / 2;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k].vector.y + p->li[i][j][k - 1].vector.y) / 2;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k].vector.z + p->li[i][j][k - 1].vector.z) / 2;

                p->Si[i][j][k].j.x = (p->lj[i + 1][j][k - 1].vector.x +
                                      p->lj[i][j][k - 1].vector.x) /
                                     4;
                p->Si[i][j][k].j.y = (p->lj[i + 1][j][k - 1].vector.y +
                                      p->lj[i][j][k - 1].vector.y) /
                                     4;
                p->Si[i][j][k].j.z = (p->lj[i + 1][j][k - 1].vector.z +
                                      p->lj[i][j][k - 1].vector.z) /
                                     4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = 0;
                break;

            case (BIT_BACK | BIT_LEFT | BIT_BOTTOM):

                p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x + p->li[i][j][k].vector.x) / 2;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y + p->li[i][j][k].vector.y) / 2;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z + p->li[i][j][k].vector.z) / 2;

                p->Si[i][j][k].j.x =
                    (p->lj[i + 1][j][k].vector.x + p->lj[i][j][k].vector.x) / 4;
                p->Si[i][j][k].j.y =
                    (p->lj[i + 1][j][k].vector.y + p->lj[i][j][k].vector.y) / 4;
                p->Si[i][j][k].j.z =
                    (p->lj[i + 1][j][k].vector.z + p->lj[i][j][k].vector.z) / 4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

                // p->Sj[i][j][k].i.x = (p->li[i][j][k + 1].vector.x +
                // p->li[i][j][k].vector.x) / 4; p->Sj[i][j][k].i.y =
                // (p->li[i][j][k + 1].vector.y + p->li[i][j][k].vector.y) / 4;
                // p->Sj[i][j][k].i.z = (p->li[i][j][k + 1].vector.z +
                // p->li[i][j][k].vector.z) / 4;

                // p->Sj[i][j][k].j.x = (p->lj[i + 1][j][k].vector.x +
                // p->lj[i][j][k].vector.x) / 2; p->Sj[i][j][k].j.y = (p->lj[i +
                // 1][j][k].vector.y + p->lj[i][j][k].vector.y) / 2;
                // p->Sj[i][j][k].j.z = (p->lj[i + 1][j][k].vector.z +
                // p->lj[i][j][k].vector.z) / 2;
                p->Sj[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x +
                     p->li[i][j - 1][k + 1].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y +
                     p->li[i][j - 1][k + 1].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z +
                     p->li[i][j - 1][k + 1].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j - 1][k].vector.z) /
                    4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i + 1][j][k].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].j.y =
                    (p->lj[i + 1][j][k].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].j.z =
                    (p->lj[i + 1][j][k].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) /
                    4;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_BACK | BIT_RIGHT | BIT_BOTTOM):

                p->S[i][j][k].i.x = (p->li[i - 1][j][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i - 1][j][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i - 1][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x = (p->li[i - 1][j][k + 1].vector.x +
                                      p->li[i - 1][j][k].vector.x) /
                                     4;
                p->Sj[i][j][k].i.y = (p->li[i - 1][j][k + 1].vector.y +
                                      p->li[i - 1][j][k].vector.y) /
                                     4;
                p->Sj[i][j][k].i.z = (p->li[i - 1][j][k + 1].vector.z +
                                      p->li[i - 1][j][k].vector.z) /
                                     4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i][j][k].vector.x + p->lj[i - 1][j][k].vector.x) / 2;
                p->Sj[i][j][k].j.y =
                    (p->lj[i][j][k].vector.y + p->lj[i - 1][j][k].vector.y) / 2;
                p->Sj[i][j][k].j.z =
                    (p->lj[i][j][k].vector.z + p->lj[i - 1][j][k].vector.z) / 2;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = 0;
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_BACK | BIT_RIGHT | BIT_TOP):

                p->S[i][j][k].i.x = (p->li[i - 1][j][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i - 1][j][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i - 1][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k - 1].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k - 1].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k - 1].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->hi[i][j][k] = 0;
                p->hj[i][j][k] = 0;
                break;

            case (BIT_BACK | BIT_LEFT | BIT_TOP):

                // p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                // p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                // p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;
                p->S[i][j][k].i.x =
                    (p->li[i][j - 1][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i][j - 1][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i][j - 1][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k - 1].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k - 1].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k - 1].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                // p->Si[i][j][k].i.x = (p->li[i][j][k].vector.x + p->li[i][j][k
                // - 1].vector.x) / 4; p->Si[i][j][k].i.y =
                // (p->li[i][j][k].vector.y + p->li[i][j][k - 1].vector.y) / 4;
                // p->Si[i][j][k].i.z = (p->li[i][j][k].vector.z + p->li[i][j][k
                // - 1].vector.z) / 4;
                p->Si[i][j][k].i.x =
                    (p->li[i][j][k].vector.x + p->li[i][j][k - 1].vector.x) / 4;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k].vector.y + p->li[i][j][k - 1].vector.y) / 4;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k].vector.z + p->li[i][j][k - 1].vector.z) / 4;

                p->Si[i][j][k].j.x = (p->lj[i + 1][j][k - 1].vector.x +
                                      p->lj[i][j][k - 1].vector.x) /
                                     2;
                p->Si[i][j][k].j.y = (p->lj[i + 1][j][k - 1].vector.y +
                                      p->lj[i][j][k - 1].vector.y) /
                                     2;
                p->Si[i][j][k].j.z = (p->lj[i + 1][j][k - 1].vector.z +
                                      p->lj[i][j][k - 1].vector.z) /
                                     2;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = 0;
                break;

            default:
                console(4);
                break;
        }
    } else if (p->flag[i][j][k] & BIT_RIGHTSIDE) {
        switch (p->flag[i][j][k]) {
            case (BIT_RIGHTSIDE):

                p->S[i][j][k].i.x =
                    (p->li[i][j - 1][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i][j - 1][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i][j - 1][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x =
                    (p->lj[i][j][k - 1].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y =
                    (p->lj[i][j][k - 1].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z =
                    (p->lj[i][j][k - 1].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j][k].vector.x + p->li[i][j][k - 1].vector.x) /
                    4;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j][k].vector.y + p->li[i][j][k - 1].vector.y) /
                    4;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j][k].vector.z + p->li[i][j][k - 1].vector.z) /
                    4;

                p->Si[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x +
                     p->lj[i][j + 1][k - 1].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k - 1].vector.x) /
                    4;
                p->Si[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y +
                     p->lj[i][j + 1][k - 1].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k - 1].vector.y) /
                    4;
                p->Si[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z +
                     p->lj[i][j + 1][k - 1].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k - 1].vector.z) /
                    4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x +
                     p->li[i][j - 1][k + 1].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y +
                     p->li[i][j - 1][k + 1].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z +
                     p->li[i][j - 1][k + 1].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j - 1][k].vector.z) /
                    4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) /
                    4;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_RIGHTSIDE | BIT_LEFT):

                p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x =
                    (p->lj[i][j][k - 1].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y =
                    (p->lj[i][j][k - 1].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z =
                    (p->lj[i][j][k - 1].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j][k].vector.x + p->li[i][j][k - 1].vector.x) /
                    4;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j][k].vector.y + p->li[i][j][k - 1].vector.y) /
                    4;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j][k].vector.z + p->li[i][j][k - 1].vector.z) /
                    4;

                p->Si[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x +
                     p->lj[i][j + 1][k - 1].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k - 1].vector.x) /
                    4;
                p->Si[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y +
                     p->lj[i][j + 1][k - 1].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k - 1].vector.y) /
                    4;
                p->Si[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z +
                     p->lj[i][j + 1][k - 1].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k - 1].vector.z) /
                    4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x + p->li[i][j][k].vector.x) / 4;
                p->Sj[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y + p->li[i][j][k].vector.y) / 4;
                p->Sj[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z + p->li[i][j][k].vector.z) / 4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->Sj[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->Sj[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_RIGHTSIDE | BIT_BOTTOM):

                p->S[i][j][k].i.x =
                    (p->li[i][j - 1][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i][j - 1][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i][j - 1][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x + p->li[i][j][k].vector.x) / 2;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y + p->li[i][j][k].vector.y) / 2;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z + p->li[i][j][k].vector.z) / 2;

                p->Si[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x + p->lj[i][j][k].vector.x) / 4;
                p->Si[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y + p->lj[i][j][k].vector.y) / 4;
                p->Si[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z + p->lj[i][j][k].vector.z) / 4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x +
                     p->li[i][j - 1][k + 1].vector.x + p->li[i][j][k].vector.x +
                     p->li[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y +
                     p->li[i][j - 1][k + 1].vector.y + p->li[i][j][k].vector.y +
                     p->li[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z +
                     p->li[i][j - 1][k + 1].vector.z + p->li[i][j][k].vector.z +
                     p->li[i][j - 1][k].vector.z) /
                    4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x + p->lj[i][j][k].vector.x +
                     p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) /
                    4;
                p->Sj[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y + p->lj[i][j][k].vector.y +
                     p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) /
                    4;
                p->Sj[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z + p->lj[i][j][k].vector.z +
                     p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) /
                    4;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_RIGHTSIDE | BIT_RIGHT):

                p->S[i][j][k].i.x = (p->li[i][j - 1][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i][j - 1][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i][j - 1][k].vector.z) / 2;

                p->S[i][j][k].j.x =
                    (p->lj[i][j][k - 1].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y =
                    (p->lj[i][j][k - 1].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z =
                    (p->lj[i][j][k - 1].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x = (p->li[i][j - 1][k + 1].vector.x +
                                      p->li[i][j - 1][k].vector.x) /
                                     4;
                p->Sj[i][j][k].i.y = (p->li[i][j - 1][k + 1].vector.y +
                                      p->li[i][j - 1][k].vector.y) /
                                     4;
                p->Sj[i][j][k].i.z = (p->li[i][j - 1][k + 1].vector.z +
                                      p->li[i][j - 1][k].vector.z) /
                                     4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) / 2;
                p->Sj[i][j][k].j.y =
                    (p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) / 2;
                p->Sj[i][j][k].j.z =
                    (p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) / 2;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = 0;
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_RIGHTSIDE | BIT_TOP):

                p->S[i][j][k].i.x =
                    (p->li[i][j - 1][k].vector.x + p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y =
                    (p->li[i][j - 1][k].vector.y + p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z =
                    (p->li[i][j - 1][k].vector.z + p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k - 1].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k - 1].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k - 1].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i][j][k].vector.x + p->li[i][j][k - 1].vector.x) / 2;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k].vector.y + p->li[i][j][k - 1].vector.y) / 2;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k].vector.z + p->li[i][j][k - 1].vector.z) / 2;

                p->Si[i][j][k].j.x = (p->lj[i][j + 1][k - 1].vector.x +
                                      p->lj[i][j][k - 1].vector.x) /
                                     4;
                p->Si[i][j][k].j.y = (p->lj[i][j + 1][k - 1].vector.y +
                                      p->lj[i][j][k - 1].vector.y) /
                                     4;
                p->Si[i][j][k].j.z = (p->lj[i][j + 1][k - 1].vector.z +
                                      p->lj[i][j][k - 1].vector.z) /
                                     4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = 0;
                break;

            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_BOTTOM):

                p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x + p->li[i][j][k].vector.x) / 2;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y + p->li[i][j][k].vector.y) / 2;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z + p->li[i][j][k].vector.z) / 2;

                p->Si[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x + p->lj[i][j][k].vector.x) / 4;
                p->Si[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y + p->lj[i][j][k].vector.y) / 4;
                p->Si[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z + p->lj[i][j][k].vector.z) / 4;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x =
                    (p->li[i][j][k + 1].vector.x + p->li[i][j][k].vector.x) / 4;
                p->Sj[i][j][k].i.y =
                    (p->li[i][j][k + 1].vector.y + p->li[i][j][k].vector.y) / 4;
                p->Sj[i][j][k].i.z =
                    (p->li[i][j][k + 1].vector.z + p->li[i][j][k].vector.z) / 4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i][j + 1][k].vector.x + p->lj[i][j][k].vector.x) / 2;
                p->Sj[i][j][k].j.y =
                    (p->lj[i][j + 1][k].vector.y + p->lj[i][j][k].vector.y) / 2;
                p->Sj[i][j][k].j.z =
                    (p->lj[i][j + 1][k].vector.z + p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_BOTTOM):

                p->S[i][j][k].i.x = (p->li[i][j - 1][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i][j - 1][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i][j - 1][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Sj[i][j][k].i.x = (p->li[i][j - 1][k + 1].vector.x +
                                      p->li[i][j - 1][k].vector.x) /
                                     4;
                p->Sj[i][j][k].i.y = (p->li[i][j - 1][k + 1].vector.y +
                                      p->li[i][j - 1][k].vector.y) /
                                     4;
                p->Sj[i][j][k].i.z = (p->li[i][j - 1][k + 1].vector.z +
                                      p->li[i][j - 1][k].vector.z) /
                                     4;

                p->Sj[i][j][k].j.x =
                    (p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) / 2;
                p->Sj[i][j][k].j.y =
                    (p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) / 2;
                p->Sj[i][j][k].j.z =
                    (p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) / 2;

                crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                                 p->Sj[i][j][k].j);
                p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
                p->hi[i][j][k]         = 0;
                p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
                break;

            case (BIT_RIGHTSIDE | BIT_RIGHT | BIT_TOP):

                p->S[i][j][k].i.x = (p->li[i][j - 1][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i][j - 1][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i][j - 1][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k - 1].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k - 1].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k - 1].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->hi[i][j][k] = 0;
                p->hj[i][j][k] = 0;
                break;

            case (BIT_RIGHTSIDE | BIT_LEFT | BIT_TOP):

                p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k - 1].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k - 1].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k - 1].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

                p->Si[i][j][k].i.x =
                    (p->li[i][j][k].vector.x + p->li[i][j][k - 1].vector.x) / 4;
                p->Si[i][j][k].i.y =
                    (p->li[i][j][k].vector.y + p->li[i][j][k - 1].vector.y) / 4;
                p->Si[i][j][k].i.z =
                    (p->li[i][j][k].vector.z + p->li[i][j][k - 1].vector.z) / 4;

                p->Si[i][j][k].j.x = (p->lj[i][j + 1][k - 1].vector.x +
                                      p->lj[i][j][k - 1].vector.x) /
                                     2;
                p->Si[i][j][k].j.y = (p->lj[i][j + 1][k - 1].vector.y +
                                      p->lj[i][j][k - 1].vector.y) /
                                     2;
                p->Si[i][j][k].j.z = (p->lj[i][j + 1][k - 1].vector.z +
                                      p->lj[i][j][k - 1].vector.z) /
                                     2;

                crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                                 p->Si[i][j][k].j);
                p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);
                p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
                p->hj[i][j][k]         = 0;
                break;

            default:
                console(4);
                break;
        }
    }

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// EDGE処理
///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
#ifdef Thicken
    if (p->flag[i][j][k] & BIT_CEILING) {
        if ((p->flag[i][j][k] & BIT_BOTTOM) && (p->flag[i][j][k] & BIT_RIGHT)) {
            p->hi[i][j][k] *= param->thicken_coefficient;
            p->hj[i][j][k] *= param->thicken_coefficient;
        } else if (p->flag[i][j][k] & BIT_BOTTOM) {
            p->hi[i][j][k] *= param->thicken_coefficient;
            p->hj[i][j][k] *= param->thicken_coefficient;
            p->hj[i][j][k - 1] *= param->thicken_coefficient;
        } else if (p->flag[i][j][k] & BIT_RIGHT) {
            p->hi[i][j][k] *= param->thicken_coefficient;
            p->hi[i][j][k - 1] *= param->thicken_coefficient;
            p->hj[i][j][k] *= param->thicken_coefficient;
        }
    } else if (p->flag[i][j][k] & BIT_BACK) {
        if (p->flag[i][j][k] & BIT_LEFT) {
            if (p->flag[i][j][k] & BIT_BOTTOM) {
                p->hi[i][j][k] *= param->thicken_coefficient;
                p->hj[i][j][k] *= param->thicken_coefficient;
                p->hi[i][j - 1][k] *= param->thicken_coefficient;
            } else if (p->flag[i][j][k] & BIT_TOP) {
                p->hi[i][j][k] *= param->thicken_coefficient;
                p->hi[i][j - 1][k] *= param->thicken_coefficient;
                p->hj[i][j][k - 1] *= param->thicken_coefficient;
            } else {
                p->hi[i][j][k] *= param->thicken_coefficient;
                p->hj[i][j][k] *= param->thicken_coefficient;
                p->hi[i][j - 1][k] *= param->thicken_coefficient;
                p->hj[i][j][k - 1] *= param->thicken_coefficient;
            }
        }
    }
#endif
}

////////////////////////////////////////////
///////////// 2次元的な形状 /////////////////
////////////////////////////////////////////
#else

void MultiParticle::ThicknessCalc(int const& i, int const& j, int const& k) {
#ifdef __DEBUG__
//   cout << "Run Thickness Calc:";
//   cout << i << "," << j << "," << k << endl;
#endif
    // cout << "Run ThicknessCalc" << endl;
    switch (p->flag[i][j][k]) {
        case Center:

            p->S[i][j][k].i.x =
                (p->li[i - 1][j][k].vector.x + p->li[i][j][k].vector.x) / 2;
            p->S[i][j][k].i.y =
                (p->li[i - 1][j][k].vector.y + p->li[i][j][k].vector.y) / 2;
            p->S[i][j][k].i.z =
                (p->li[i - 1][j][k].vector.z + p->li[i][j][k].vector.z) / 2;

            p->S[i][j][k].j.x =
                (p->lj[i][j - 1][k].vector.x + p->lj[i][j][k].vector.x) / 2;
            p->S[i][j][k].j.y =
                (p->lj[i][j - 1][k].vector.y + p->lj[i][j][k].vector.y) / 2;
            p->S[i][j][k].j.z =
                (p->lj[i][j - 1][k].vector.z + p->lj[i][j][k].vector.z) / 2;

            crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                             p->S[i][j][k].j);
            p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

            p->Si[i][j][k].i.x =
                (p->li[i][j + 1][k].vector.x + p->li[i][j][k].vector.x +
                 p->li[i][j][k].vector.x + p->li[i][j - 1][k].vector.x) /
                4;
            p->Si[i][j][k].i.y =
                (p->li[i][j + 1][k].vector.y + p->li[i][j][k].vector.y +
                 p->li[i][j][k].vector.y + p->li[i][j - 1][k].vector.y) /
                4;
            p->Si[i][j][k].i.z =
                (p->li[i][j + 1][k].vector.z + p->li[i][j][k].vector.z +
                 p->li[i][j][k].vector.z + p->li[i][j - 1][k].vector.z) /
                4;

            p->Si[i][j][k].j.x =
                (p->lj[i + 1][j][k].vector.x + p->lj[i + 1][j - 1][k].vector.x +
                 p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) /
                4;
            p->Si[i][j][k].j.y =
                (p->lj[i + 1][j][k].vector.y + p->lj[i + 1][j - 1][k].vector.y +
                 p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) /
                4;
            p->Si[i][j][k].j.z =
                (p->lj[i + 1][j][k].vector.z + p->lj[i + 1][j - 1][k].vector.z +
                 p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) /
                4;

            crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                             p->Si[i][j][k].j);
            p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

            p->Sj[i][j][k].i.x =
                (p->li[i][j + 1][k].vector.x + p->li[i - 1][j + 1][k].vector.x +
                 p->li[i][j][k].vector.x + p->li[i - 1][j][k].vector.x) /
                4;
            p->Sj[i][j][k].i.y =
                (p->li[i][j + 1][k].vector.y + p->li[i - 1][j + 1][k].vector.y +
                 p->li[i][j][k].vector.y + p->li[i - 1][j][k].vector.y) /
                4;
            p->Sj[i][j][k].i.z =
                (p->li[i][j + 1][k].vector.z + p->li[i - 1][j + 1][k].vector.z +
                 p->li[i][j][k].vector.z + p->li[i - 1][j][k].vector.z) /
                4;

            p->Sj[i][j][k].j.x =
                (p->lj[i + 1][j][k].vector.x + p->lj[i][j][k].vector.x +
                 p->lj[i][j][k].vector.x + p->lj[i - 1][j][k].vector.x) /
                4;
            p->Sj[i][j][k].j.y =
                (p->lj[i + 1][j][k].vector.y + p->lj[i][j][k].vector.y +
                 p->lj[i][j][k].vector.y + p->lj[i - 1][j][k].vector.y) /
                4;
            p->Sj[i][j][k].j.z =
                (p->lj[i + 1][j][k].vector.z + p->lj[i][j][k].vector.z +
                 p->lj[i][j][k].vector.z + p->lj[i - 1][j][k].vector.z) /
                4;

            crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                             p->Sj[i][j][k].j);
            p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
            p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
            p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
            break;

        case Left:

#ifdef __CYLINDER_NON_BOUNDARY__
            p->S[i][j][k].i.x =
                (p->li[i][j][k].vector.x + p->omp[i][j][k].li.vector.x) / 2;
            p->S[i][j][k].i.y =
                (p->li[i][j][k].vector.y + p->omp[i][j][k].li.vector.y) / 2;
            p->S[i][j][k].i.z =
                (p->li[i][j][k].vector.z + p->omp[i][j][k].li.vector.z) / 2;

            p->S[i][j][k].j.x =
                (p->lj[i][j - 1][k].vector.x + p->lj[i][j][k].vector.x) / 2;
            p->S[i][j][k].j.y =
                (p->lj[i][j - 1][k].vector.y + p->lj[i][j][k].vector.y) / 2;
            p->S[i][j][k].j.z =
                (p->lj[i][j - 1][k].vector.z + p->lj[i][j][k].vector.z) / 2;

            crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                             p->S[i][j][k].j);
            p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);
#else
            p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
            p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
            p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

            p->S[i][j][k].j.x =
                (p->lj[i][j - 1][k].vector.x + p->lj[i][j][k].vector.x) / 2;
            p->S[i][j][k].j.y =
                (p->lj[i][j - 1][k].vector.y + p->lj[i][j][k].vector.y) / 2;
            p->S[i][j][k].j.z =
                (p->lj[i][j - 1][k].vector.z + p->lj[i][j][k].vector.z) / 2;

            crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                             p->S[i][j][k].j);
            p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);
#endif

            p->Si[i][j][k].i.x =
                (p->li[i][j + 1][k].vector.x + p->li[i][j][k].vector.x +
                 p->li[i][j][k].vector.x + p->li[i][j - 1][k].vector.x) /
                4;
            p->Si[i][j][k].i.y =
                (p->li[i][j + 1][k].vector.y + p->li[i][j][k].vector.y +
                 p->li[i][j][k].vector.y + p->li[i][j - 1][k].vector.y) /
                4;
            p->Si[i][j][k].i.z =
                (p->li[i][j + 1][k].vector.z + p->li[i][j][k].vector.z +
                 p->li[i][j][k].vector.z + p->li[i][j - 1][k].vector.z) /
                4;

            p->Si[i][j][k].j.x =
                (p->lj[i + 1][j][k].vector.x + p->lj[i + 1][j - 1][k].vector.x +
                 p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) /
                4;
            p->Si[i][j][k].j.y =
                (p->lj[i + 1][j][k].vector.y + p->lj[i + 1][j - 1][k].vector.y +
                 p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) /
                4;
            p->Si[i][j][k].j.z =
                (p->lj[i + 1][j][k].vector.z + p->lj[i + 1][j - 1][k].vector.z +
                 p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) /
                4;

            crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                             p->Si[i][j][k].j);
            p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

            p->Sj[i][j][k].i.x =
                (p->li[i][j + 1][k].vector.x + p->li[i][j][k].vector.x) / 4;
            p->Sj[i][j][k].i.y =
                (p->li[i][j + 1][k].vector.y + p->li[i][j][k].vector.y) / 4;
            p->Sj[i][j][k].i.z =
                (p->li[i][j + 1][k].vector.z + p->li[i][j][k].vector.z) / 4;

            p->Sj[i][j][k].j.x =
                (p->lj[i + 1][j][k].vector.x + p->lj[i][j][k].vector.x) / 2;
            p->Sj[i][j][k].j.y =
                (p->lj[i + 1][j][k].vector.y + p->lj[i][j][k].vector.y) / 2;
            p->Sj[i][j][k].j.z =
                (p->lj[i + 1][j][k].vector.z + p->lj[i][j][k].vector.z) / 2;

            crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                             p->Sj[i][j][k].j);
            p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
            p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
            p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
#ifdef __CYLINDER_NON_BOUNDARY__
            p->omp[i][j][k].Si.i.x = (2 * p->omp[i][j][k].li.vector.x +
                                      p->omp[i][j - 1][k].li.vector.x +
                                      p->omp[i][j + 1][k].li.vector.x) /
                                     4;
            p->omp[i][j][k].Si.i.y = (2 * p->omp[i][j][k].li.vector.y +
                                      p->omp[i][j - 1][k].li.vector.y +
                                      p->omp[i][j + 1][k].li.vector.y) /
                                     4;
            p->omp[i][j][k].Si.i.z = (2 * p->omp[i][j][k].li.vector.z +
                                      p->omp[i][j - 1][k].li.vector.z +
                                      p->omp[i][j + 1][k].li.vector.z) /
                                     4;
            lCalc(p->omp[i][j - 1][k].lj, p->omp[i][j - 1][k].ci,
                  p->omp[i][j][k].ci);
            lCalc(p->omp[i][j][k].lj, p->omp[i][j][k].ci,
                  p->omp[i][j + 1][k].ci);
            p->omp[i][j][k].Si.j.x =
                (p->omp[i][j][k].lj.vector.x + p->omp[i][j - 1][k].lj.vector.x +
                 p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) /
                4;
            p->omp[i][j][k].Si.j.y =
                (p->omp[i][j][k].lj.vector.y + p->omp[i][j - 1][k].lj.vector.y +
                 p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) /
                4;
            p->omp[i][j][k].Si.j.z =
                (p->omp[i][j][k].lj.vector.z + p->omp[i][j - 1][k].lj.vector.z +
                 p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) /
                4;
            crossProductCalc(p->omp[i][j][k].Si.cp.vector, p->omp[i][j][k].Si.i,
                             p->omp[i][j][k].Si.j);
            p->omp[i][j][k].Si.cp.norm = normCalc(p->omp[i][j][k].Si.cp.vector);
            p->omp[i][j][k].hi =
                hCalc(p->omp[i][j][k].Si.cp.norm, p->omp[i][j][k].Si0);
#endif
            break;

        case Bottom:

            p->S[i][j][k].i.x =
                (p->li[i - 1][j][k].vector.x + p->li[i][j][k].vector.x) / 2;
            p->S[i][j][k].i.y =
                (p->li[i - 1][j][k].vector.y + p->li[i][j][k].vector.y) / 2;
            p->S[i][j][k].i.z =
                (p->li[i - 1][j][k].vector.z + p->li[i][j][k].vector.z) / 2;

            p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
            p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
            p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

            crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                             p->S[i][j][k].j);
            p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

            p->Si[i][j][k].i.x =
                (p->li[i][j + 1][k].vector.x + p->li[i][j][k].vector.x) / 2;
            p->Si[i][j][k].i.y =
                (p->li[i][j + 1][k].vector.y + p->li[i][j][k].vector.y) / 2;
            p->Si[i][j][k].i.z =
                (p->li[i][j + 1][k].vector.z + p->li[i][j][k].vector.z) / 2;

            p->Si[i][j][k].j.x =
                (p->lj[i + 1][j][k].vector.x + p->lj[i][j][k].vector.x) / 4;
            p->Si[i][j][k].j.y =
                (p->lj[i + 1][j][k].vector.y + p->lj[i][j][k].vector.y) / 4;
            p->Si[i][j][k].j.z =
                (p->lj[i + 1][j][k].vector.z + p->lj[i][j][k].vector.z) / 4;

            crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                             p->Si[i][j][k].j);
            p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

            p->Sj[i][j][k].i.x =
                (p->li[i][j + 1][k].vector.x + p->li[i - 1][j + 1][k].vector.x +
                 p->li[i][j][k].vector.x + p->li[i - 1][j][k].vector.x) /
                4;
            p->Sj[i][j][k].i.y =
                (p->li[i][j + 1][k].vector.y + p->li[i - 1][j + 1][k].vector.y +
                 p->li[i][j][k].vector.y + p->li[i - 1][j][k].vector.y) /
                4;
            p->Sj[i][j][k].i.z =
                (p->li[i][j + 1][k].vector.z + p->li[i - 1][j + 1][k].vector.z +
                 p->li[i][j][k].vector.z + p->li[i - 1][j][k].vector.z) /
                4;

            p->Sj[i][j][k].j.x =
                (p->lj[i + 1][j][k].vector.x + p->lj[i][j][k].vector.x +
                 p->lj[i][j][k].vector.x + p->lj[i - 1][j][k].vector.x) /
                4;
            p->Sj[i][j][k].j.y =
                (p->lj[i + 1][j][k].vector.y + p->lj[i][j][k].vector.y +
                 p->lj[i][j][k].vector.y + p->lj[i - 1][j][k].vector.y) /
                4;
            p->Sj[i][j][k].j.z =
                (p->lj[i + 1][j][k].vector.z + p->lj[i][j][k].vector.z +
                 p->lj[i][j][k].vector.z + p->lj[i - 1][j][k].vector.z) /
                4;

            crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                             p->Sj[i][j][k].j);
            p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
            p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
            p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
            break;

        case Right:
#ifdef __CYLINDER_NON_BOUNDARY__
            p->S[i][j][k].i.x =
                (p->li[i - 1][j][k].vector.x + p->omp[i][j][k].li.vector.x) / 2;
            p->S[i][j][k].i.y =
                (p->li[i - 1][j][k].vector.y + p->omp[i][j][k].li.vector.y) / 2;
            p->S[i][j][k].i.z =
                (p->li[i - 1][j][k].vector.z + p->omp[i][j][k].li.vector.z) / 2;

            p->S[i][j][k].j.x =
                (p->lj[i][j - 1][k].vector.x + p->lj[i][j][k].vector.x) / 2;
            p->S[i][j][k].j.y =
                (p->lj[i][j - 1][k].vector.y + p->lj[i][j][k].vector.y) / 2;
            p->S[i][j][k].j.z =
                (p->lj[i][j - 1][k].vector.z + p->lj[i][j][k].vector.z) / 2;

            crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                             p->S[i][j][k].j);
            p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);
#else
            p->S[i][j][k].i.x     = (p->li[i - 1][j][k].vector.x) / 2;
            p->S[i][j][k].i.y     = (p->li[i - 1][j][k].vector.y) / 2;
            p->S[i][j][k].i.z     = (p->li[i - 1][j][k].vector.z) / 2;

            p->S[i][j][k].j.x =
                (p->lj[i][j - 1][k].vector.x + p->lj[i][j][k].vector.x) / 2;
            p->S[i][j][k].j.y =
                (p->lj[i][j - 1][k].vector.y + p->lj[i][j][k].vector.y) / 2;
            p->S[i][j][k].j.z =
                (p->lj[i][j - 1][k].vector.z + p->lj[i][j][k].vector.z) / 2;

            crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                             p->S[i][j][k].j);
            p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);
#endif

#ifdef __CYLINDER_BOUNDARY__
            p->hi[i][j][k]        = 0;
#elif defined __CYLINDER_NON_BOUNDARY__
            // lCalc(p->tmp.vec, p->c[i][j][k], p->vc_Right[i][j][k]);
            // lCalc(p->tmp.vec2, p->c[i][j - 1][k], p->vc_Right[i][j -
                1][k]);
                // lCalc(p->tmp.vec3, p->c[i][j + 1][k], p->vc_Right[i][j +
                1][k]);
                // p->Si[i][j][k].i.x = (2 * p->tmp.vec.vector.x +
                // p->tmp.vec2.vector.x + p->tmp.vec3.vector.x) / 4;
                // p->Si[i][j][k].i.y = (2 * p->tmp.vec.vector.y +
                // p->tmp.vec2.vector.y + p->tmp.vec3.vector.y) / 4;
                // p->Si[i][j][k].i.z = (2 * p->tmp.vec.vector.z +
                // p->tmp.vec2.vector.z + p->tmp.vec3.vector.z) / 4;
                p->omp[i][j][k].Si.i.x = (2 * p->omp[i][j][k].li.vector.x +
                                          p->omp[i][j - 1][k].li.vector.x +
                                          p->omp[i][j + 1][k].li.vector.x) /
                                         4;
                p->omp[i][j][k].Si.i.y = (2 * p->omp[i][j][k].li.vector.y +
                                          p->omp[i][j - 1][k].li.vector.y +
                                          p->omp[i][j + 1][k].li.vector.y) /
                                         4;
                p->omp[i][j][k].Si.i.z = (2 * p->omp[i][j][k].li.vector.z +
                                          p->omp[i][j - 1][k].li.vector.z +
                                          p->omp[i][j + 1][k].li.vector.z) /
                                         4;

                // lCalc(p->tmp.vec, p->vc_Right[i][j][k], p->vc_Right[i][j -
                // 1][k]); lCalc(p->tmp.vec2, p->vc_Right[i][j][k],
                p->vc_Right[i][j
                // + 1][k]);
                lCalc(p->omp[i][j - 1][k].lj, p->omp[i][j - 1][k].ci,
                      p->omp[i][j][k].ci);
                lCalc(p->omp[i][j][k].lj, p->omp[i][j][k].ci,
                      p->omp[i][j + 1][k].ci);
                // p->Si[i][j][k].j.x = (p->tmp.vec.vector.x +
                p->tmp.vec2.vector.x
                // + p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) /
                4;
                // p->Si[i][j][k].j.y = (p->tmp.vec.vector.y +
                p->tmp.vec2.vector.y
                // + p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) /
                4;
                // p->Si[i][j][k].j.z = (p->tmp.vec.vector.z +
                p->tmp.vec2.vector.z
                // + p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) /
                4; p->omp[i][j][k].Si.j.x =
                    (p->omp[i][j][k].lj.vector.x + p->omp[i][j -
                    1][k].lj.vector.x +
                     p->lj[i][j][k].vector.x + p->lj[i][j - 1][k].vector.x) /
                    4;
                p->omp[i][j][k].Si.j.y =
                    (p->omp[i][j][k].lj.vector.y + p->omp[i][j -
                    1][k].lj.vector.y +
                     p->lj[i][j][k].vector.y + p->lj[i][j - 1][k].vector.y) /
                    4;
                p->omp[i][j][k].Si.j.z =
                    (p->omp[i][j][k].lj.vector.z + p->omp[i][j -
                    1][k].lj.vector.z +
                     p->lj[i][j][k].vector.z + p->lj[i][j - 1][k].vector.z) /
                    4;

                // crossProductCalc(p->SI[i][j][k].cp.vector,
                p->Si[i][j][k].i,
                // p->Si[i][j][k].j);
                crossProductCalc(p->omp[i][j][k].Si.cp.vector,
                p->omp[i][j][k].Si.i,
                                 p->omp[i][j][k].Si.j);
                // p->Si[i][j][k].cp.norm =
                normCalc(p->Si[i][j][k].cp.vector);
                p->omp[i][j][k].Si.cp.norm =
                normCalc(p->omp[i][j][k].Si.cp.vector);

                // p->hi[i][j][k] = hCalc(p->Si[i][j][k].cp.norm,
                p->Si0[i][j][k]); p->omp[i][j][k].hi =
                    hCalc(p->omp[i][j][k].Si.cp.norm, p->omp[i][j][k].Si0);
#endif

            p->Sj[i][j][k].i.x = (p->li[i - 1][j + 1][k].vector.x +
                                  p->li[i - 1][j][k].vector.x) /
                                 4;
            p->Sj[i][j][k].i.y = (p->li[i - 1][j + 1][k].vector.y +
                                  p->li[i - 1][j][k].vector.y) /
                                 4;
            p->Sj[i][j][k].i.z = (p->li[i - 1][j + 1][k].vector.z +
                                  p->li[i - 1][j][k].vector.z) /
                                 4;

            p->Sj[i][j][k].j.x =
                (p->lj[i][j][k].vector.x + p->lj[i - 1][j][k].vector.x) / 2;
            p->Sj[i][j][k].j.y =
                (p->lj[i][j][k].vector.y + p->lj[i - 1][j][k].vector.y) / 2;
            p->Sj[i][j][k].j.z =
                (p->lj[i][j][k].vector.z + p->lj[i - 1][j][k].vector.z) / 2;

            crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                             p->Sj[i][j][k].j);
            p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);

            p->hj[i][j][k] = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
            break;
        case Top:

            p->S[i][j][k].i.x =
                (p->li[i - 1][j][k].vector.x + p->li[i][j][k].vector.x) / 2;
            p->S[i][j][k].i.y =
                (p->li[i - 1][j][k].vector.y + p->li[i][j][k].vector.y) / 2;
            p->S[i][j][k].i.z =
                (p->li[i - 1][j][k].vector.z + p->li[i][j][k].vector.z) / 2;

            p->S[i][j][k].j.x = (p->lj[i][j - 1][k].vector.x) / 2;
            p->S[i][j][k].j.y = (p->lj[i][j - 1][k].vector.y) / 2;
            p->S[i][j][k].j.z = (p->lj[i][j - 1][k].vector.z) / 2;

            crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                             p->S[i][j][k].j);
            p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);

            p->Si[i][j][k].i.x =
                (p->li[i][j][k].vector.x + p->li[i][j - 1][k].vector.x) / 2;
            p->Si[i][j][k].i.y =
                (p->li[i][j][k].vector.y + p->li[i][j - 1][k].vector.y) / 2;
            p->Si[i][j][k].i.z =
                (p->li[i][j][k].vector.z + p->li[i][j - 1][k].vector.z) / 2;

            p->Si[i][j][k].j.x = (p->lj[i + 1][j - 1][k].vector.x +
                                  p->lj[i][j - 1][k].vector.x) /
                                 4;
            p->Si[i][j][k].j.y = (p->lj[i + 1][j - 1][k].vector.y +
                                  p->lj[i][j - 1][k].vector.y) /
                                 4;
            p->Si[i][j][k].j.z = (p->lj[i + 1][j - 1][k].vector.z +
                                  p->lj[i][j - 1][k].vector.z) /
                                 4;

            crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                             p->Si[i][j][k].j);
            p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);
            p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
            p->hj[i][j][k]         = 0;
            break;

        case LeftBottom:
#ifdef __CYLINDER_NON_BOUNDARY__
            p->S[i][j][k].i.x =
                (p->li[i][j][k].vector.x + p->omp[i][j][k].li.vector.x) / 2;
            p->S[i][j][k].i.y =
                (p->li[i][j][k].vector.y + p->omp[i][j][k].li.vector.y) / 2;
            p->S[i][j][k].i.z =
                (p->li[i][j][k].vector.z + p->omp[i][j][k].li.vector.z) / 2;

            p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
            p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
            p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

            crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                             p->S[i][j][k].j);
            p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);
#else
                p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);
#endif

            p->Si[i][j][k].i.x =
                (p->li[i][j + 1][k].vector.x + p->li[i][j][k].vector.x) / 2;
            p->Si[i][j][k].i.y =
                (p->li[i][j + 1][k].vector.y + p->li[i][j][k].vector.y) / 2;
            p->Si[i][j][k].i.z =
                (p->li[i][j + 1][k].vector.z + p->li[i][j][k].vector.z) / 2;

            p->Si[i][j][k].j.x =
                (p->lj[i + 1][j][k].vector.x + p->lj[i][j][k].vector.x) / 4;
            p->Si[i][j][k].j.y =
                (p->lj[i + 1][j][k].vector.y + p->lj[i][j][k].vector.y) / 4;
            p->Si[i][j][k].j.z =
                (p->lj[i + 1][j][k].vector.z + p->lj[i][j][k].vector.z) / 4;

            crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                             p->Si[i][j][k].j);
            p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);

            p->Sj[i][j][k].i.x =
                (p->li[i][j + 1][k].vector.x + p->li[i][j][k].vector.x) / 4;
            p->Sj[i][j][k].i.y =
                (p->li[i][j + 1][k].vector.y + p->li[i][j][k].vector.y) / 4;
            p->Sj[i][j][k].i.z =
                (p->li[i][j + 1][k].vector.z + p->li[i][j][k].vector.z) / 4;

            p->Sj[i][j][k].j.x =
                (p->lj[i + 1][j][k].vector.x + p->lj[i][j][k].vector.x) / 2;
            p->Sj[i][j][k].j.y =
                (p->lj[i + 1][j][k].vector.y + p->lj[i][j][k].vector.y) / 2;
            p->Sj[i][j][k].j.z =
                (p->lj[i + 1][j][k].vector.z + p->lj[i][j][k].vector.z) / 2;

            crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                             p->Sj[i][j][k].j);
            p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
            p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
            p->hj[i][j][k]         = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
#ifdef __CYLINDER_NON_BOUNDARY__
            p->omp[i][j][k].Si.i.x = (p->omp[i][j][k].li.vector.x +
                                      p->omp[i][j + 1][k].li.vector.x) /
                                     2;
            p->omp[i][j][k].Si.i.y = (p->omp[i][j][k].li.vector.y +
                                      p->omp[i][j + 1][k].li.vector.y) /
                                     2;
            p->omp[i][j][k].Si.i.z = (p->omp[i][j][k].li.vector.z +
                                      p->omp[i][j + 1][k].li.vector.z) /
                                     2;

            // lCalc(p->omp[i][j - 1][k].lj, p->omp[i][j - 1][k].vc,
            // p->omp[i][j][k].vc);
            lCalc(p->omp[i][j][k].lj, p->omp[i][j][k].ci,
                  p->omp[i][j + 1][k].ci);
            p->omp[i][j][k].Si.j.x =
                (p->omp[i][j][k].lj.vector.x + p->lj[i][j][k].vector.x) / 4;
            p->omp[i][j][k].Si.j.y =
                (p->omp[i][j][k].lj.vector.y + p->lj[i][j][k].vector.y) / 4;
            p->omp[i][j][k].Si.j.z =
                (p->omp[i][j][k].lj.vector.z + p->lj[i][j][k].vector.z) / 4;

            crossProductCalc(p->omp[i][j][k].Si.cp.vector, p->omp[i][j][k].Si.i,
                             p->omp[i][j][k].Si.j);
            p->omp[i][j][k].Si.cp.norm = normCalc(p->omp[i][j][k].Si.cp.vector);

            p->omp[i][j][k].hi =
                hCalc(p->omp[i][j][k].Si.cp.norm, p->omp[i][j][k].Si0);
#endif
            break;

        case RightBottom:
#ifdef __CYLINDER_NON_BOUNDARY__
            p->S[i][j][k].i.x =
                (p->li[i - 1][j][k].vector.x + p->omp[i][j][k].li.vector.x) / 2;
            p->S[i][j][k].i.y =
                (p->li[i - 1][j][k].vector.y + p->omp[i][j][k].li.vector.y) / 2;
            p->S[i][j][k].i.z =
                (p->li[i - 1][j][k].vector.z + p->omp[i][j][k].li.vector.z) / 2;

            p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
            p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
            p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

            crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                             p->S[i][j][k].j);
            p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);
#else
                p->S[i][j][k].i.x     = (p->li[i - 1][j][k].vector.x) / 2;
                p->S[i][j][k].i.y     = (p->li[i - 1][j][k].vector.y) / 2;
                p->S[i][j][k].i.z     = (p->li[i - 1][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j][k].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j][k].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm  = normCalc(p->S[i][j][k].cp.vector);
#endif

#ifdef __CYLINDER_BOUNDARY__
            p->hi[i][j][k]        = 0;
#elif defined __CYLINDER_NON_BOUNDARY__
                p->omp[i][j][k].Si.i.x = (p->omp[i][j][k].li.vector.x +
                                          p->omp[i][j + 1][k].li.vector.x) /
                                         2;
                p->omp[i][j][k].Si.i.y = (p->omp[i][j][k].li.vector.y +
                                          p->omp[i][j + 1][k].li.vector.y) /
                                         2;
                p->omp[i][j][k].Si.i.z = (p->omp[i][j][k].li.vector.z +
                                          p->omp[i][j + 1][k].li.vector.z) /
                                         2;

                // lCalc(p->omp[i][j - 1][k].lj, p->omp[i][j - 1][k].vc,
                // p->omp[i][j][k].vc);
                lCalc(p->omp[i][j][k].lj, p->omp[i][j][k].ci,
                      p->omp[i][j + 1][k].ci);
                p->omp[i][j][k].Si.j.x =
                    (p->omp[i][j][k].lj.vector.x + p->lj[i][j][k].vector.x) /
                    4;
                p->omp[i][j][k].Si.j.y =
                    (p->omp[i][j][k].lj.vector.y + p->lj[i][j][k].vector.y) /
                    4;
                p->omp[i][j][k].Si.j.z =
                    (p->omp[i][j][k].lj.vector.z + p->lj[i][j][k].vector.z) /
                    4;

                crossProductCalc(p->omp[i][j][k].Si.cp.vector,
                p->omp[i][j][k].Si.i,
                                 p->omp[i][j][k].Si.j);
                p->omp[i][j][k].Si.cp.norm =
                normCalc(p->omp[i][j][k].Si.cp.vector);

                p->omp[i][j][k].hi =
                    hCalc(p->omp[i][j][k].Si.cp.norm, p->omp[i][j][k].Si0);
#endif
            p->Sj[i][j][k].i.x    = (p->li[i - 1][j + 1][k].vector.x +
                                  p->li[i - 1][j][k].vector.x) /
                                 4;
            p->Sj[i][j][k].i.y = (p->li[i - 1][j + 1][k].vector.y +
                                  p->li[i - 1][j][k].vector.y) /
                                 4;
            p->Sj[i][j][k].i.z = (p->li[i - 1][j + 1][k].vector.z +
                                  p->li[i - 1][j][k].vector.z) /
                                 4;

            p->Sj[i][j][k].j.x =
                (p->lj[i][j][k].vector.x + p->lj[i - 1][j][k].vector.x) / 2;
            p->Sj[i][j][k].j.y =
                (p->lj[i][j][k].vector.y + p->lj[i - 1][j][k].vector.y) / 2;
            p->Sj[i][j][k].j.z =
                (p->lj[i][j][k].vector.z + p->lj[i - 1][j][k].vector.z) / 2;

            crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
                             p->Sj[i][j][k].j);
            p->Sj[i][j][k].cp.norm = normCalc(p->Sj[i][j][k].cp.vector);
            // p->hi[i][j][k] = 0;
            p->hj[i][j][k] = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
            break;

        case RightTop:
#ifdef __CYLINDER_NON_BOUNDARY__
            p->S[i][j][k].i.x =
                (p->li[i - 1][j][k].vector.x + p->omp[i][j][k].li.vector.x) / 2;
            p->S[i][j][k].i.y =
                (p->li[i - 1][j][k].vector.y + p->omp[i][j][k].li.vector.y) / 2;
            p->S[i][j][k].i.z =
                (p->li[i - 1][j][k].vector.z + p->omp[i][j][k].li.vector.z) / 2;

            p->S[i][j][k].j.x = (p->lj[i][j - 1][k].vector.x) / 2;
            p->S[i][j][k].j.y = (p->lj[i][j - 1][k].vector.y) / 2;
            p->S[i][j][k].j.z = (p->lj[i][j - 1][k].vector.z) / 2;

            crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                             p->S[i][j][k].j);
            p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);
#else
                p->S[i][j][k].i.x = (p->li[i - 1][j][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i - 1][j][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i - 1][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j - 1][k].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j - 1][k].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j - 1][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm  = normCalc(p->S[i][j][k].cp.vector);
#endif

#ifdef __CYLINDER_BOUNDARY__
            p->hi[i][j][k]        = 0;
#elif defined __CYLINDER_NON_BOUNDARY__
                p->omp[i][j][k].Si.i.x = (p->omp[i][j][k].li.vector.x +
                                          p->omp[i][j - 1][k].li.vector.x) /
                                         2;
                p->omp[i][j][k].Si.i.y = (p->omp[i][j][k].li.vector.y +
                                          p->omp[i][j - 1][k].li.vector.y) /
                                         2;
                p->omp[i][j][k].Si.i.z = (p->omp[i][j][k].li.vector.z +
                                          p->omp[i][j - 1][k].li.vector.z) /
                                         2;

                lCalc(p->omp[i][j - 1][k].lj, p->omp[i][j - 1][k].ci,
                      p->omp[i][j][k].ci);
                // lCalc(p->omp[i][j][k].lj, p->omp[i][j][k].ci, p->omp[i][j
                +
                // 1][k].cj);
                p->omp[i][j][k].Si.j.x = (p->omp[i][j - 1][k].lj.vector.x +
                                          p->lj[i][j - 1][k].vector.x) /
                                         4;
                p->omp[i][j][k].Si.j.y = (p->omp[i][j - 1][k].lj.vector.y +
                                          p->lj[i][j - 1][k].vector.y) /
                                         4;
                p->omp[i][j][k].Si.j.z = (p->omp[i][j - 1][k].lj.vector.z +
                                          p->lj[i][j - 1][k].vector.z) /
                                         4;

                crossProductCalc(p->omp[i][j][k].Si.cp.vector,
                p->omp[i][j][k].Si.i,
                                 p->omp[i][j][k].Si.j);
                p->omp[i][j][k].Si.cp.norm =
                normCalc(p->omp[i][j][k].Si.cp.vector);

                p->omp[i][j][k].hi =
                    hCalc(p->omp[i][j][k].Si.cp.norm, p->omp[i][j][k].Si0);
#endif
            // p->hi[i][j][k] = 0;
            p->hj[i][j][k] = 0;
            break;

        case LeftTop:
#ifdef __CYLINDER_NON_BOUNDARY__
            p->S[i][j][k].i.x =
                (p->li[i][j][k].vector.x + p->omp[i][j][k].li.vector.x) / 2;
            p->S[i][j][k].i.y =
                (p->li[i][j][k].vector.y + p->omp[i][j][k].li.vector.y) / 2;
            p->S[i][j][k].i.z =
                (p->li[i][j][k].vector.z + p->omp[i][j][k].li.vector.z) / 2;

            p->S[i][j][k].j.x = (p->lj[i][j - 1][k].vector.x) / 2;
            p->S[i][j][k].j.y = (p->lj[i][j - 1][k].vector.y) / 2;
            p->S[i][j][k].j.z = (p->lj[i][j - 1][k].vector.z) / 2;

            crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                             p->S[i][j][k].j);
            p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);
#else
                p->S[i][j][k].i.x = (p->li[i][j][k].vector.x) / 2;
                p->S[i][j][k].i.y = (p->li[i][j][k].vector.y) / 2;
                p->S[i][j][k].i.z = (p->li[i][j][k].vector.z) / 2;

                p->S[i][j][k].j.x = (p->lj[i][j - 1][k].vector.x) / 2;
                p->S[i][j][k].j.y = (p->lj[i][j - 1][k].vector.y) / 2;
                p->S[i][j][k].j.z = (p->lj[i][j - 1][k].vector.z) / 2;

                crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
                                 p->S[i][j][k].j);
                p->S[i][j][k].cp.norm = normCalc(p->S[i][j][k].cp.vector);
#endif

            p->Si[i][j][k].i.x =
                (p->li[i][j][k].vector.x + p->li[i][j - 1][k].vector.x) / 4;
            p->Si[i][j][k].i.y =
                (p->li[i][j][k].vector.y + p->li[i][j - 1][k].vector.y) / 4;
            p->Si[i][j][k].i.z =
                (p->li[i][j][k].vector.z + p->li[i][j - 1][k].vector.z) / 4;

            p->Si[i][j][k].j.x = (p->lj[i + 1][j - 1][k].vector.x +
                                  p->lj[i][j - 1][k].vector.x) /
                                 2;
            p->Si[i][j][k].j.y = (p->lj[i + 1][j - 1][k].vector.y +
                                  p->lj[i][j - 1][k].vector.y) /
                                 2;
            p->Si[i][j][k].j.z = (p->lj[i + 1][j - 1][k].vector.z +
                                  p->lj[i][j - 1][k].vector.z) /
                                 2;

            crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
                             p->Si[i][j][k].j);
            p->Si[i][j][k].cp.norm = normCalc(p->Si[i][j][k].cp.vector);
            p->hi[i][j][k]         = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
            p->hj[i][j][k]         = 0;
#ifdef __CYLINDER_NON_BOUNDARY__
            p->omp[i][j][k].Si.i.x = (p->omp[i][j][k].li.vector.x +
                                      p->omp[i][j - 1][k].li.vector.x) /
                                     2;
            p->omp[i][j][k].Si.i.y = (p->omp[i][j][k].li.vector.y +
                                      p->omp[i][j - 1][k].li.vector.y) /
                                     2;
            p->omp[i][j][k].Si.i.z = (p->omp[i][j][k].li.vector.z +
                                      p->omp[i][j - 1][k].li.vector.z) /
                                     2;

            lCalc(p->omp[i][j - 1][k].lj, p->omp[i][j - 1][k].ci,
                  p->omp[i][j][k].ci);
            // lCalc(p->omp[i][j][k].lj, p->omp[i][j][k].ci, p->omp[i][j
            +
                // 1][k].cj);
                p->omp[i][j][k].Si.j.x = (p->omp[i][j - 1][k].lj.vector.x +
                                          p->lj[i][j - 1][k].vector.x) /
                                         4;
            p->omp[i][j][k].Si.j.y = (p->omp[i][j - 1][k].lj.vector.y +
                                      p->lj[i][j - 1][k].vector.y) /
                                     4;
            p->omp[i][j][k].Si.j.z = (p->omp[i][j - 1][k].lj.vector.z +
                                      p->lj[i][j - 1][k].vector.z) /
                                     4;

            crossProductCalc(p->omp[i][j][k].Si.cp.vector, p->omp[i][j][k].Si.i,
                             p->omp[i][j][k].Si.j);
            p->omp[i][j][k].Si.cp.norm = normCalc(p->omp[i][j][k].Si.cp.vector);

            p->omp[i][j][k].hi =
                hCalc(p->omp[i][j][k].Si.cp.norm, p->omp[i][j][k].Si0);
#endif
            break;

        default:
            console(4);
            break;
    }
}
#endif

////////////// Current Function //////////////////////
void MultiParticle::InfluenceAreaCalc(const int& i, const int& j,
                                      const int& k) {
    {
        // S calc
        // C length;
        p->S[i][j][k].i.reset();
        if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
            p->S[i][j][k].i += p->li[i][j][k].vector;
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
            p->S[i][j][k].i += p->li[i - 1][j][k].vector;
        } else {
            if (!param->boundary.cylinder_boundary) {
                p->S[i][j][k].i += p->omp[i][j][k].li.vector;
            }
        }
        p->S[i][j][k].i /= 2;

        p->S[i][j][k].j.reset();
        if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
            p->S[i][j][k].j += p->lj[i][j][k].vector;
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
            p->S[i][j][k].j += p->lj[i][j - 1][k].vector;
        }
        p->S[i][j][k].j /= 2;

        // crossProductCalc(p->S[i][j][k].cp.vector, p->S[i][j][k].i,
        //                  p->S[i][j][k].j);
        p->S[i][j][k].cp.vector = p->S[i][j][k].i * p->S[i][j][k].j;
        p->S[i][j][k].cp.norm   = normCalc(p->S[i][j][k].cp.vector);
    }

    {
        // Si calc
        if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
            p->Si[i][j][k].i.reset();
            int num = 0;
            if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
                num += 2;
                p->Si[i][j][k].i += p->li[i][j + 1][k].vector;
                p->Si[i][j][k].i += p->li[i][j][k].vector;
            }
            if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
                num += 2;
                p->Si[i][j][k].i += p->li[i][j - 1][k].vector;
                p->Si[i][j][k].i += p->li[i][j][k].vector;
            }
            // num              = 4;
            p->Si[i][j][k].i = p->Si[i][j][k].i / num;
        }

        if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
            p->Si[i][j][k].j.reset();
            int num = 0;
            if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
                num += 2;
                p->Si[i][j][k].j += p->lj[i][j][k].vector;
                p->Si[i][j][k].j += p->lj[i + 1][j][k].vector;
            }
            if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
                num += 2;
                p->Si[i][j][k].j += p->lj[i][j - 1][k].vector;
                p->Si[i][j][k].j += p->lj[i + 1][j - 1][k].vector;
            }
            num              = 4;
            p->Si[i][j][k].j = p->Si[i][j][k].j / num;
        }
        // crossProductCalc(p->Si[i][j][k].cp.vector, p->Si[i][j][k].i,
        //                  p->Si[i][j][k].j);
        p->Si[i][j][k].cp.vector = p->Si[i][j][k].i * p->Si[i][j][k].j;
        p->Si[i][j][k].cp.norm   = normCalc(p->Si[i][j][k].cp.vector);
    }
    {
        // Sj calc
        if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
            p->Sj[i][j][k].i.reset();
            int num = 0;
            if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
                num += 2;
                p->Sj[i][j][k].i += p->li[i][j][k].vector;
                p->Sj[i][j][k].i += p->li[i][j + 1][k].vector;
            }
            if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
                num += 2;
                p->Sj[i][j][k].i += p->li[i - 1][j][k].vector;
                p->Sj[i][j][k].i += p->li[i - 1][j + 1][k].vector;
            }
            num = 4;
            p->Sj[i][j][k].i /= num;
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
            p->Sj[i][j][k].j.reset();
            int num = 0;
            if (p->surround_particle_exsit[i][j][k] & BIT_RIGHT) {
                num += 2;
                p->Sj[i][j][k].j += p->lj[i][j][k].vector;
                p->Sj[i][j][k].j += p->lj[i + 1][j][k].vector;
            }
            if (p->surround_particle_exsit[i][j][k] & BIT_LEFT) {
                num += 2;
                p->Sj[i][j][k].j += p->lj[i][j][k].vector;
                p->Sj[i][j][k].j += p->lj[i - 1][j][k].vector;
            }
            // num = 4;
            p->Sj[i][j][k].j /= num;
        }
        // crossProductCalc(p->Sj[i][j][k].cp.vector, p->Sj[i][j][k].i,
        //                  p->Sj[i][j][k].j);
        p->Sj[i][j][k].cp.vector = p->Sj[i][j][k].i * p->Sj[i][j][k].j;
        p->Sj[i][j][k].cp.norm   = normCalc(p->Sj[i][j][k].cp.vector);
    }
    if ((p->Si[i][j][k].cp.norm != 0) && (p->Si0[i][j][k] != 0)) {
        p->hi[i][j][k] = hCalc(p->Si[i][j][k].cp.norm, p->Si0[i][j][k]);
    }
    if ((p->Sj[i][j][k].cp.norm != 0) && (p->Sj0[i][j][k] != 0)) {
        p->hj[i][j][k] = hCalc(p->Sj[i][j][k].cp.norm, p->Sj0[i][j][k]);
    }
    if (!param->boundary.cylinder_boundary) {
        p->omp[i][j][k].Si.i.reset();
        int num = 0;
        if (p->surround_particle_exsit[i][j][k] & BIT_TOP) {
            num += 2;
            p->omp[i][j][k].Si.i += p->omp[i][j + 1][k].li.vector;
            p->omp[i][j][k].Si.i += p->omp[i][j][k].li.vector;
        }
        if (p->surround_particle_exsit[i][j][k] & BIT_BOTTOM) {
            num += 2;
            p->omp[i][j][k].Si.i += p->omp[i][j - 1][k].li.vector;
            p->omp[i][j][k].Si.i += p->omp[i][j][k].li.vector;
        }
        p->omp[i][j][k].Si.i = p->omp[i][j][k].Si.i / num;
    }
}
