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
 *      Provides the default parameters for the black holes.                  *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/09/23                                                        *
 ******************************************************************************/
package main

/******************************************************************************
 *                              Setup Parameters                              *
 ******************************************************************************/

/*  Starting parameters for the x and y values in the plane.                  */
const X_Start float64 = 0.0
const Y_Start float64 = 1.0

/*  Number of iterations allowed in the main Barnsley fern function.          */
const Max_Iters uint32 = 64

/*  Number of pixels in the x and y axes.                                     */
const X_Size uint32 = 1024
const Y_Size uint32 = 1024

/*  The total number of pixels in the output PPM file.                        */
const Number_Of_Pixels uint32 = X_Size * Y_Size

/*  Product of the number of pixels and the max number of iterations.         */
const Total uint32 = Number_Of_Pixels * Max_Iters

/*  Growth factor for the fern. Set this between 0 and 1.                     */
const Growth_Factor float64 = 0.8

/*  Scale and shift factors for the affine transformations.                   */
const X_Scale float64 = +0.195 * float64(X_Size)
const Y_Scale float64 = -0.090 * float64(Y_Size)
const X_Shift float64 = +0.450 * float64(X_Size)
const Y_Shift float64 = +1.000 * float64(Y_Size)

/******************************************************************************
 *                              Setup Functions                               *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      PointToPixel                                                          *
 *  Purpose:                                                                  *
 *      Converts a point in the plane to the corresponding pixel.             *
 *  Arguments:                                                                *
 *      xpt (float64):                                                        *
 *          The x-coordinate of the input point.                              *
 *      ypt (float64):                                                        *
 *          The y-coordinate of the input point.                              *
 *  Outputs:                                                                  *
 *      ind (uint32):                                                         *
 *          The integer x + y*width where x and y are the pixels              *
 *          corresponding to (xpt, ypt), where width is the width of the PPM. *
 ******************************************************************************/
func PointToPixel(xpt, ypt float64) uint32 {
    var xpx float64 = X_Shift + X_Scale*xpt;
    var ypx float64 = Y_Shift + Y_Scale*ypt;
    var xn uint32 = uint32(xpx);
    var yn uint32 = uint32(ypx);
    return xn + yn*X_Size;
}
/*  End of PointToPixel.                                                      */
