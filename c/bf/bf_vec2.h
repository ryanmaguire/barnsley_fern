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
 *      Provides a 2D vector struct.                                          *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef BF_VEC2_H
#define BF_VEC2_H

#include "bf_inline.h"

/*  Simple struct for a 2D vector.                                            */
struct bf_vec2 {

    /*  A vector is defined by its Cartesian coordinates.                     */
    double x, y;
};

BF_INLINE struct bf_vec2
bf_vec2_rect(double x, double y)
{
    struct bf_vec2 P;
    P.x = x;
    P.y = y;
    return P;
}

BF_INLINE struct bf_vec2
bf_vec2_add(const struct bf_vec2 *P, const struct bf_vec2 *Q)
{
    struct bf_vec2 sum;
    sum.x = P->x + Q->x;
    sum.y = P->y + Q->y;
    return sum;
}

BF_INLINE void
bf_vec2_addto(struct bf_vec2 *P, const struct bf_vec2 *Q)
{
    P->x += Q->x;
    P->y += Q->y;
}

BF_INLINE struct bf_vec2
bf_vec2_scale(double a, const struct bf_vec2 *P)
{
    struct bf_vec2 prod;
    prod.x = a * P->x;
    prod.y = a * P->y;
    return prod;
}

BF_INLINE void
bf_vec2_scaleby(double a, struct bf_vec2 *P)
{
    P->x *= a;
    P->y *= a;
}

#endif
/*  End of include guard.                                                     */
