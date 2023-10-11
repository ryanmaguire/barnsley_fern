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
package main

import "math/rand"

/*  Computes the values for the Barnsley fern and stores them in the buffer.  */
func CreateFern(data []float64) {

    /*  Variables for indexing and looping over pixels in the fern.           */
    var n, index uint32

    /*  The variables for the fern itself.                                    */
    var x_val float64 = X_Start
    var y_val float64 = Y_Start

    /*  Loop over and create the fern.                                        */
    for n = 0; n < Total; n += 1 {

        /*  Get a random integer using the standard library function rand().  */
        var random_value = rand.Float64() * 100.0

        /*  Initialize the old variables. Copy the current ones in to them.   */
        var x_old float64 = x_val;
        var y_old float64 = y_val;

        /*  Use the affine transformations defined by Barnsley to update.     */
        if (random_value < 1.0) {
            x_val = 0.0
            y_val = 0.16*y_old
        } else if (random_value < 86.0) {
            x_val = Growth_Factor*x_old + 0.04*y_old;
            y_val = -0.04*x_old + 0.85*y_val + 1.6;
        } else if (random_value < 93.0) {
            x_val = 0.20*x_old - 0.26*y_old;
            y_val = 0.23*x_old + 0.22*y_old + 1.6;
        } else {
            x_val = -0.15*x_old + 0.28*y_old;
            y_val = 0.26*x_old + 0.24*y_old + 0.44;
        }

        /*  Get the pixel x_val and y_val correspond to.                      */
        index = PointToPixel(x_val, y_val);
        data[index] += 1.0;
    }
    /*  End of for-loop over n.                                               */
}
/*  End of CreateFern.                                                        */
