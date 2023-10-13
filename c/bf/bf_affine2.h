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
 *      Provides a 2D affine transformation struct.                           *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/10/12                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef BF_AFFINE2_H
#define BF_AFFINE2_H

/*  2D linear transformations found here.                                     */
#include "bf_mat2x2.h"

/*  2D vector struct given here.                                              */
#include "bf_vec2.h"

/*  Affine transformation struct, linear transformation plus shift.           */
struct bf_affine2 {

    /*  Affine transformations are T(v) = Av + S where A is a linear          *
     *  transformation and S is a constant vector.                            */
    struct bf_mat2x2 mat;
    struct bf_vec2 shift;
};

/******************************************************************************
 *  Function:                                                                 *
 *      bf_affine2_create                                                     *
 *  Purpose:                                                                  *
 *      Creates an affine transformation from a linear transformation and a   *
 *      shift, given by a matrix and a vector, respectively.                  *
 *  Arguments:                                                                *
 *      A (const struct bf_mat2x2 *):                                         *
 *          A pointer to a matrix, the linear transformation part.            *
 *      P (const struct bf_vec2 *):                                           *
 *          A pointer to a vector, the shift component.                       *
 *  Output:                                                                   *
 *      T (struct bf_affine2):                                                *
 *          The affine transformation T(v) = A(v) + P.                        *
 ******************************************************************************/
BF_INLINE struct bf_affine2
bf_affine2_create(const struct bf_mat2x2 *A, const struct bf_vec2 *P)
{
    struct bf_affine2 T;
    T.shift = *P;
    T.mat = *A;
    return T;
}

/******************************************************************************
 *  Function:                                                                 *
 *      bf_affine2_transform                                                  *
 *  Purpose:                                                                  *
 *      Applies an affine transformation to a vector.                         *
 *  Arguments:                                                                *
 *      T (const struct bf_affine2 *):                                        *
 *          A pointer to an affine transformation.                            *
 *      P (const struct bf_vec2 *):                                           *
 *          A pointer to a vector, the input for the transformation.          *
 *  Output:                                                                   *
 *      Q (struct bf_vec2 ):                                                  *
 *          The application of the affine transformation T to P, Q = T(P).    *
 ******************************************************************************/
BF_INLINE struct bf_vec2
bf_affine2_transform(const struct bf_affine2 *T, const struct bf_vec2 *P)
{
    struct bf_vec2 out = bf_mat2x2_product(&T->mat, P);
    bf_vec2_addto(&out, &T->shift);
    return out;
}

/******************************************************************************
 *  Function:                                                                 *
 *      bf_affine2_transformby                                                *
 *  Purpose:                                                                  *
 *      Applies an affine transformation to a vector "in-place".              *
 *  Arguments:                                                                *
 *      T (const struct bf_affine2 *):                                        *
 *          A pointer to an affine transformation.                            *
 *      P (struct bf_vec2 *):                                                 *
 *          A pointer to a vector, the input for the transformation.          *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
BF_INLINE void
bf_affine2_transformby(const struct bf_affine2 *T, struct bf_vec2 *P)
{
    bf_mat2x2_productby(&T->mat, P);
    bf_vec2_addto(P, &T->shift);
}

#endif
/*  End of include guard.                                                     */
