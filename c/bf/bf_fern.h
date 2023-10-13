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
 *      Creates a Barnley fern and stores the result in a given data buffer.  *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/10/11                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef BF_FERN_H
#define BF_FERN_H

/*  rand() function is provided here.                                         */
#include <stdlib.h>

/*  Data structure with the affine transformations given here.                */
#include "bf_data.h"

/*  BF_INLINE macro is defined here.                                          */
#include "bf_inline.h"

/*  Parameters for the output PPM, such as number of pixels, given here.      */
#include "bf_setup.h"

/*  2D vector struct with basic vector arithmetic.                            */
#include "bf_vec2.h"

/*  Computes the values for the Barnsley fern and stores them in the buffer.  */
BF_INLINE void
bf_create_fern(double *buffer, const struct bf_data *fern)
{
    /*  Scale factor to convert random numbers to fall between 0 and 100.     */
    const double scale_factor = 100.0 / (double)RAND_MAX;

    /*  Variables for indexing and looping over pixels in the fern.           */
    unsigned int n, index;

    /*  The variables for the fern itself.                                    */
    struct bf_vec2 P = bf_vec2_rect(bf_setup_xstart, bf_setup_ystart);

    /*  Loop over and create the fern.                                        */
    for (n = 0U; n < bf_setup_total; ++n)
    {
        /*  Get a random integer using the standard library function rand().  */
        const int random_int = rand();

        /*  Scale this to a random number between 0 and 100.                  */
        const double random_value = (double)random_int * scale_factor;

        /*  Use the affine transformations defined by Barnsley to update.     */
        if (random_value < fern->cutoff[0])
            bf_affine2_transformby(&fern->transform[0], &P);

        else if (random_value < fern->cutoff[1])
            bf_affine2_transformby(&fern->transform[1], &P);

        else if (random_value < fern->cutoff[2])
            bf_affine2_transformby(&fern->transform[2], &P);

        else
            bf_affine2_transformby(&fern->transform[3], &P);

        /*  Get the pixel x_val and y_val correspond to.                      */
        index = bf_point_to_pixel(&P);
        buffer[index] += 1.0;
    }
    /*  End of for-loop over n.                                               */
}
/*  End of bf_create_fern.                                                    */

#endif
/*  End of include guard.                                                     */
