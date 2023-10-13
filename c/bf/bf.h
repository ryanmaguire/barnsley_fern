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
 *      Creates a Barnley fern.                                               *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/10/11                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef BF_H
#define BF_H

/*  calloc and free are given here.                                           */
#include <stdlib.h>

/*  Basic color struct for working with colors in RGB format.                 */
#include "bf_color.h"

/*  Data structure with the affine transformations given here.                */
#include "bf_data.h"

/*  Main function for generating the Barnsley fern provided here.             */
#include "bf_fern.h"

/*  BF_INLINE macro provided here.                                            */
#include "bf_inline.h"

/*  PPM struct defined here with basic functions and utilities.               */
#include "bf_ppm.h"

/*  Setup parameters for the PPM.                                             */
#include "bf_setup.h"

/*  Function for drawing the Barnsley Fern.                                   */
BF_INLINE void
bf_run(colorer color, const struct bf_data *fern, const char *name)
{
    /*  Integers for looping over pixels in the fern.                         */
    unsigned int x, y;

    /*  Scale factor for the intensity of the color.                          */
    const double scale_factor = 1.0 / 256.0;

    /*  Buffer for the Barnsley fern. The values for the fern will be stored  *
     *  here. The (x, y) pixel is given by the x + y*bf_setup_xsize entry.    */
    double * const buffer = calloc(bf_setup_number_of_pixels, sizeof(*buffer));

    /*  Open the file and give it write permissions.                          */
    struct bf_ppm PPM = bf_ppm_create(name);

    /*  fopen returns NULL on failure. Check for this.                        */
    if (!PPM.fp)
    {
        /*  If calloc succeeded, we need to free the buffer before exiting.   */
        if (buffer)
            free(buffer);

        return;
    }

    /*  calloc returns NULL on failure. Check for this.                       */
    if (!buffer)
    {
        puts("calloc failed and returned NULL. Aborting.");

        /*  Close the file since fopen was successful.                        */
        bf_ppm_close(&PPM);
        return;
    }

    /*  Initialize the PPM file with default values for the preamble.         */
    bf_ppm_init(&PPM);

    /*  Create the Barnsley fern and store the values in the buffer.          */
    bf_create_fern(buffer, fern);

    /*  Loop over the y pixels and create the PPM file.                       */
    for (y = 0U; y < bf_setup_ysize; ++y)
    {
        /*  Loop over x pixels.                                               */
        for (x = 0U; x < bf_setup_xsize; ++x)
        {
            /*  Compute the color the pixel is going to be.                   */
            const double val = 1.0 - scale_factor*buffer[x + y*bf_setup_xsize];
            const struct bf_color c = color(val);

            /*  Add this color to the PPM file.                               */
            bf_color_write_to_ppm(&c, &PPM);
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Free the memory allocated for the buffer.                             */
    free(buffer);

    /*  Close the file and return.                                            */
    bf_ppm_close(&PPM);
}
/*  End of bf_run.                                                            */

#endif
/*  End of include guard.                                                     */
