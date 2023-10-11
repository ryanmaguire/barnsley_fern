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
#ifndef BF_HPP
#define BF_HPP

/*  calloc and free are given here.                                           */
#include <stdlib.h>

/*  Basic color struct for working with colors in RGB format.                 */
#include "bf_color.hpp"

/*  Main function for generating the Barnsley fern provided here.             */
#include "bf_fern.hpp"

/*  PPM struct defined here with basic functions and utilities.               */
#include "bf_ppm.hpp"

/*  Setup parameters for the PPM.                                             */
#include "bf_setup.hpp"

/*  Namespace for the mini-project. "Barnsley Fractal."                       */
namespace bf {

    /*  Function for drawing the Barnsley Fern.                               */
    template <typename Tcolorer>
    inline void run(Tcolorer color, const char *name)
    {
        /*  Integers for looping over pixels in the fern.                     */
        unsigned int x, y;

        /*  Scale factor for the intensity of the color.                      */
        const double scale_factor = 1.0 / 256.0;

        /*  Buffer for the Barnsley fern. The values for the fern will be     *
         *  stored here. The (x, y) pixel is given by the x + y*xsize entry.  */
        double * const data =static_cast<double *>(
            std::calloc(setup::number_of_pixels, sizeof(*data))
        );

        /*  Open the file and give it write permissions.                      */
        struct ppm PPM = ppm(name);

        /*  fopen returns NULL on failure. Check for this.                    */
        if (!PPM.fp)
        {
            /*  If calloc succeeded, we need to free the data before exiting. */
            if (data)
                std::free(data);

            return;
        }

        /*  calloc returns NULL on failure. Check for this.                   */
        if (!data)
        {
            std::puts("calloc failed and returned NULL. Aborting.");

            /*  Close the file since fopen was successful.                    */
            PPM.close();
            return;
        }

        /*  Initialize the PPM file with default values for the preamble.     */
        PPM.init();

        /*  Create the Barnsley fern and store the values in the data buffer. */
        create_fern(data);

        /*  Loop over the y pixels and create the PPM file.                   */
        for (y = 0U; y < setup::ysize; ++y)
        {
            /*  Loop over x pixels.                                           */
            for (x = 0U; x < setup::xsize; ++x)
            {
                /*  Compute the color the pixel is going to be.               */
                const double val = 1.0 - scale_factor*data[x + y*setup::xsize];
                const bf::color c = color(val);

                /*  Add this color to the PPM file.                           */
                c.write(PPM);
            }
            /*  End of x for-loop.                                            */
        }
        /*  End of y for-loop.                                                */

        /*  Free the memory allocated for the data.                           */
        std::free(data);

        /*  Close the file and return.                                        */
        PPM.close();
    }
    /*  End of main.                                                          */
}
/*  End of namespace "bf".                                                    */

#endif
/*  End of include guard.                                                     */
