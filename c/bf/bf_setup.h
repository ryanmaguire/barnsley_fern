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
 *      Provides the basic setup parameters of the Barnsley fern images.      *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/10/11                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef BF_SETUP_H
#define BF_SETUP_H

/*  BF_INLINE macro found here.                                               */
#include "bf_inline.h"

/*  2D vector struct found here. Used in the "point-to-pixel" function.       */
#include "bf_vec2.h"

/*  Macros for some parameters to avoid compile-time warnings.                */
#define BF_SETUP_MAX_ITERS (64U)
#define BF_SETUP_XSIZE (1024U)
#define BF_SETUP_YSIZE (1024U)
#define BF_NUMBER_OF_PIXELS (BF_SETUP_XSIZE * BF_SETUP_YSIZE)
#define BF_SETUP_TOTAL (BF_NUMBER_OF_PIXELS * BF_SETUP_MAX_ITERS)

/*  Starting parameters for the x and y values in the plane.                  */
static const double bf_setup_xstart = 0.0;
static const double bf_setup_ystart = 0.0;

/*  Number of iterations allowed in the main Barnsley fern function.          */
static const unsigned int bf_setup_max_iters = BF_SETUP_MAX_ITERS;

/*  Number of pixels in the x and y axes.                                     */
static const unsigned int bf_setup_xsize = BF_SETUP_XSIZE;
static const unsigned int bf_setup_ysize = BF_SETUP_YSIZE;

/*  The total number of pixels in the output PPM file.                        */
static const unsigned int bf_setup_number_of_pixels = BF_NUMBER_OF_PIXELS;

/*  Product of the number of pixels and the max number of iterations.         */
static const unsigned int bf_setup_total = BF_SETUP_TOTAL;

/*  Growth factor for the fern. Set this between 0 and 1.                     */
static const double bf_setup_growth_factor = 0.8;

/*  Scale and shift factors for the affine transformations.                   */
static const double bf_setup_xscale = +0.195 * (double)BF_SETUP_XSIZE;
static const double bf_setup_yscale = -0.090 * (double)BF_SETUP_YSIZE;
static const double bf_setup_xshift = +0.450 * (double)BF_SETUP_XSIZE;
static const double bf_setup_yshift = +0.940 * (double)BF_SETUP_YSIZE;

/*  Undefine macros just to clean things up a bit.                            */
#undef BF_SETUP_MAX_ITERS
#undef BF_SETUP_XSIZE
#undef BF_SETUP_YSIZE
#undef BF_NUMBER_OF_PIXELS
#undef BF_SETUP_TOTAL

/******************************************************************************
 *  Function:                                                                 *
 *      bf_point_to_pixel                                                     *
 *  Purpose:                                                                  *
 *      Converts a point in the plane to the corresponding pixel.             *
 *  Arguments:                                                                *
 *      P (const struct bf_vec2 *P):                                          *
 *          A point in the plane, P = (x, y).                                 *
 *  Outputs:                                                                  *
 *      ind (unsigned int):                                                   *
 *          The integer x + y*width where x and y are the pixels              *
 *          corresponding to (xpt, ypt), where width is the width of the PPM. *
 ******************************************************************************/
BF_INLINE unsigned int
bf_point_to_pixel(const struct bf_vec2 *P)
{
    const double xpx = bf_setup_xshift + bf_setup_xscale*P->x;
    const double ypx = bf_setup_yshift + bf_setup_yscale*P->y;
    const unsigned int xn = (unsigned int)xpx;
    const unsigned int yn = (unsigned int)ypx;
    const unsigned int index = xn + yn*bf_setup_xsize;

    /*  If this point goes beyond the bounds the drawing, return 0.           */
    if (index >= bf_setup_number_of_pixels)
        return 0U;

    return index;
}
/*  End of bf_point_to_pixel.                                                 */

#endif
/*  End of include guard.                                                     */
