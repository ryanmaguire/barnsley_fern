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
#ifndef BF_SETUP_HPP
#define BF_SETUP_HPP

/*  Macros for some parameters to avoid compile-time warnings.                */
#define BF_SETUP_MAX_ITERS (64U)
#define BF_SETUP_XSIZE (1024U)
#define BF_SETUP_YSIZE (1024U)
#define BF_NUMBER_OF_PIXELS (BF_SETUP_XSIZE * BF_SETUP_YSIZE)
#define BF_SETUP_TOTAL (BF_NUMBER_OF_PIXELS * BF_SETUP_MAX_ITERS)

/*  Namespace for the mini-project. "Barnsley Fractal."                       */
namespace bf {

    /*  Another namespace to prevent possible conflicts with these variables. */
    namespace setup {

        /*  Starting parameters for the x and y values in the plane.          */
        static const double xstart = 0.0;
        static const double ystart = 1.0;

        /*  Number of iterations allowed in the main Barnsley fern function.  */
        static const unsigned int max_iters = BF_SETUP_MAX_ITERS;

        /*  Number of pixels in the x and y axes.                             */
        static const unsigned int xsize = BF_SETUP_XSIZE;
        static const unsigned int ysize = BF_SETUP_YSIZE;

        /*  The total number of pixels in the output PPM file.                */
        static const unsigned int number_of_pixels = BF_NUMBER_OF_PIXELS;

        /*  Product of the number of pixels and the max number of iterations. */
        static const unsigned int total = BF_SETUP_TOTAL;

        /*  Growth factor for the fern. Set this between 0 and 1.             */
        static const double growth_factor = 0.8;

        /*  Scale and shift factors for the affine transformations.           */
        static const double xscale = +0.195*static_cast<double>(BF_SETUP_XSIZE);
        static const double yscale = -0.090*static_cast<double>(BF_SETUP_YSIZE);
        static const double xshift = +0.450*static_cast<double>(BF_SETUP_XSIZE);
        static const double yshift = +1.000*static_cast<double>(BF_SETUP_YSIZE);

        /**********************************************************************
         *  Function:                                                         *
         *      bf_point_to_pixel                                             *
         *  Purpose:                                                          *
         *      Converts a point in the plane to the corresponding pixel.     *
         *  Arguments:                                                        *
         *      xpt (double):                                                 *
         *          The x-coordinate of the input point.                      *
         *      ypt (double):                                                 *
         *          The y-coordinate of the input point.                      *
         *  Outputs:                                                          *
         *      ind (unsigned int):                                           *
         *          The integer x + y*width where x and y are the pixels      *
         *          corresponding to (xpt, ypt), where width is the width     *
         *          of the PPM.                                               *
         **********************************************************************/
        inline unsigned int point_to_pixel(double xpt, double ypt)
        {
            const double xpx = xshift + xscale*xpt;
            const double ypx = yshift + yscale*ypt;
            const unsigned int xn = static_cast<unsigned int>(xpx);
            const unsigned int yn = static_cast<unsigned int>(ypx);
            return xn + yn*xsize;
        }
        /*  End of point_to_pixel.                                            */
    }
    /*  End of namespace "setup".                                             */
}
/*  End of namespace "bf".                                                    */

/*  Undefine macros just to clean things up a bit.                            */
#undef BF_SETUP_MAX_ITERS
#undef BF_SETUP_XSIZE
#undef BF_SETUP_YSIZE
#undef BF_NUMBER_OF_PIXELS
#undef BF_SETUP_TOTAL

#endif
/*  End of include guard.                                                     */
