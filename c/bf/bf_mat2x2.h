/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of barnsley_fern.                                       *
 *                                                                            *
 *  barnsley_fern is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  barnsley_fern is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with barnsley_fern.  If not, see <https://www.gnu.org/licenses/>.   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a 2-by-2 matrix struct for working with transformations.     *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/10/12                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef BF_MAT2X2_H
#define BF_MAT2X2_H

#include "bf_inline.h"
#include "bf_vec2.h"

struct bf_mat2x2 {
    double dat[2][2];
};

BF_INLINE struct bf_mat2x2
bf_mat2x2_create(double a00, double a01, double a10, double a11)
{
    struct bf_mat2x2 mat;
    mat.dat[0][0] = a00;
    mat.dat[0][1] = a01;
    mat.dat[1][0] = a10;
    mat.dat[1][1] = a11;
    return mat;
}

BF_INLINE struct bf_mat2x2
bf_mat2x2_add(const struct bf_mat2x2 *A, const struct bf_mat2x2 *B)
{
    struct bf_mat2x2 mat;
    mat.dat[0][0] = A->dat[0][0] + B->dat[0][0];
    mat.dat[0][1] = A->dat[0][1] + B->dat[0][1];
    mat.dat[1][0] = A->dat[1][0] + B->dat[1][0];
    mat.dat[1][1] = A->dat[1][1] + B->dat[1][1];
    return mat;
}

BF_INLINE void
bf_mat2x2_addto(struct bf_mat2x2 *A, const struct bf_mat2x2 *B)
{
    A->dat[0][0] += B->dat[0][0];
    A->dat[0][1] += B->dat[0][1];
    A->dat[1][0] += B->dat[1][0];
    A->dat[1][1] += B->dat[1][1];
}

BF_INLINE struct bf_mat2x2
bf_mat2x2_scale(double a, const struct bf_mat2x2 *A)
{
    struct bf_mat2x2 mat;
    mat.dat[0][0] = a * A->dat[0][0];
    mat.dat[0][1] = a * A->dat[0][1];
    mat.dat[1][0] = a * A->dat[1][0];
    mat.dat[1][1] = a * A->dat[1][1];
    return mat;
}

BF_INLINE void
bf_mat2x2_scaleby(double a, struct bf_mat2x2 *A)
{
    A->dat[0][0] *= a;
    A->dat[0][1] *= a;
    A->dat[1][0] *= a;
    A->dat[1][1] *= a;
}

BF_INLINE struct bf_vec2
bf_mat2x2_product(const struct bf_mat2x2 *A, const struct bf_vec2 *P)
{
    struct bf_vec2 prod;
    prod.x = A->dat[0][0]*P->x + A->dat[0][1]*P->y;
    prod.y = A->dat[1][0]*P->x + A->dat[1][1]*P->y;
    return prod;
}

BF_INLINE void
bf_mat2x2_productby(const struct bf_mat2x2 *A, struct bf_vec2 *P)
{
    const double x = A->dat[0][0]*P->x + A->dat[0][1]*P->y;
    P->y           = A->dat[1][0]*P->x + A->dat[1][1]*P->y;
    P->x = x;
}

#endif
/*  End of include guard.                                                     */
