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
package main

/*  Function for drawing the Barnsley Fern.                                   */
func Run(color Colorer, name string) {

    /*  Integers for looping over pixels in the fern.                         */
    var x, y uint32

    /*  Scale factor for the intensity of the color.                          */
    const scale_factor float64 = 1.0 / 256.0

    /*  Buffer for the Barnsley fern. The values for the fern will be stored  *
     *  here. The (x, y) pixel is given by the x + y*bf_setup_xsize entry.    */
    var data []float64 = make([]float64, Number_Of_Pixels);

    /*  Open the file and give it write permissions.                          */
    var ppm PPM

    ppm.Create(name)

    /*  fopen returns NULL on failure. Check for this.                        */
    if (ppm.Fp == nil) {
        return
    }

    ppm.Init()
    CreateFern(data)

    /*  Loop over the y pixels and create the PPM file.                       */
    for y = 0; y < Y_Size; y += 1 {

        /*  Loop over x pixels.                                               */
        for x = 0; x < X_Size; x += 1 {

            /*  Compute the color the pixel is going to be.                   */
            var val float64 = 1.0 - scale_factor*data[x + y*X_Size]
            var c Color = color(val)

            /*  Add this color to the PPM file.                               */
            c.WriteToPPM(&ppm)
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the file and return.                                            */
    ppm.Close()
}
/*  End of Run.                                                               */
