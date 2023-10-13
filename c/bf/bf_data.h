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
 *      Provides a data structure for the Barnsley fractal.                   *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/10/12                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef BF_DATA_H
#define BF_DATA_H

/*  Affine transformations in the plane given here.                           */
#include "bf_affine2.h"

/*  Data structure for the Barnsley transformation.                           */
struct bf_data {

    /*  We split the interval [0, 100] into four sub-intervals with these     *
     *  cutoff-points. These must be in increasing order.                     */
    double cutoff[3];

    /*  The affine transformations for the four sub-intervals.                */
    struct bf_affine2 transform[4];
};

/*  Default parameters for "the" Barnsley fern.                               */
static const struct bf_data bf_default_data = {

    /*  The cut-off parameters.                                               */
    {1.0, 86.0, 93.0},

    /*  The four affine transformations for the sub-intervals.                */
    {
        {{{{+0.00, +0.00}, {+0.00, +0.16}}}, {0.00, 0.00}},
        {{{{+0.80, +0.04}, {-0.04, +0.85}}}, {0.00, 1.60}},
        {{{{+0.20, -0.26}, {+0.23, +0.22}}}, {0.00, 1.60}},
        {{{{-0.15, +0.28}, {+0.26, +0.24}}}, {0.00, 0.44}}
    }
};

/*  Mutated variant for the Thelypteridaceae fern.                            */
static const struct bf_data bf_thelypteridaceae_data = {

    /*  The cut-off parameters.                                               */
    {2.0, 86.0, 93.0},

    /*  The four affine transformations for the sub-intervals.                */
    {
        {{{{+0.000, +0.000}, {+0.000, +0.250}}}, {+0.000, -0.400}},
        {{{{+0.950, +0.002}, {-0.005, +0.930}}}, {-0.002, +0.700}},
        {{{{+0.035, -0.200}, {+0.160, +0.040}}}, {-0.090, +0.020}},
        {{{{-0.040, +0.200}, {+0.160, +0.040}}}, {+0.083, +0.120}}
    }
};

#endif
/*  End of include guard.                                                     */
