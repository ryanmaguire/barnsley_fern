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
 *      Provides a struct for working with colors in RGB 24-bit format.       *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/10/11                                                        *
 ******************************************************************************/
package main

/*  File data type found here.                                                */
import "os"

/*  Struct for working with colors in RGB format.                             */
type Color struct {

    /*  A color is completely defined by its red, green, and blue values.     */
    Red, Green, Blue uint8
}

/*  Function type used to color the ferns.                                    */
type Colorer func(float64) Color

/******************************************************************************
 *                        Color Functions and Methods                         *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      Color.WriteToFile                                                     *
 *  Purpose:                                                                  *
 *      Writes a color to a File pointer.                                     *
 *  Arguments:                                                                *
 *      fp (*os.File):                                                        *
 *          A pointer to the file the color is being written to.              *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func (c *Color) WriteToFile(fp *os.File) {
    rgb := []byte{c.Red, c.Green, c.Blue}
    fp.Write(rgb)
}
/*  End of Color.WriteToFile.                                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      Color.WriteToPPM                                                      *
 *  Purpose:                                                                  *
 *      Writes a color to a PPM.                                              *
 *  Arguments:                                                                *
 *      fp (*os.File):                                                        *
 *          A pointer to the file the color is being written to.              *
 *  Outputs:                                                                  *
 *      None.                                                                 *
 ******************************************************************************/
func (c *Color) WriteToPPM(ppm *PPM) {
    c.WriteToFile(ppm.Fp)
}
/*  End of Color.WriteToPPM.                                                  */

/******************************************************************************
 *  Function:                                                                 *
 *      ColorScale                                                            *
 *  Purpose:                                                                  *
 *      Scales a color by a real number. Used for darkening a color.          *
 *  Arguments:                                                                *
 *      c (*Color):                                                           *
 *          A pointer to a color.                                             *
 *      t (float64):                                                          *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      scaled_c (Color):                                                     *
 *          The input color c with RGB components scaled by t.                *
 ******************************************************************************/
func ColorScale(c *Color, t float64) Color {
    var r uint8 = uint8(t * float64(c.Red))
    var g uint8 = uint8(t * float64(c.Green))
    var b uint8 = uint8(t * float64(c.Blue))
    return Color{r, g, b}
}
/*  End of ColorScale.                                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      Black                                                                 *
 *  Purpose:                                                                  *
 *      Returns the color black in RGB format.                                *
 *  Arguments:                                                                *
 *      None.                                                                 *
 *  Outputs:                                                                  *
 *      black (Color):                                                        *
 *          The color black in RGB.                                           *
 *  Method:                                                                   *
 *      Set each of the RGB components to zero and return.                    *
 ******************************************************************************/
func Black() Color {
    return Color{0x00, 0x00, 0x00}
}

/******************************************************************************
 *  Function:                                                                 *
 *      Green                                                                 *
 *  Purpose:                                                                  *
 *      Returns the color green in RGB format.                                *
 *  Arguments:                                                                *
 *      t (float64):                                                          *
 *          The intensity of the color, should be between 0 and 1.            *
 *  Outputs:                                                                  *
 *      green (Color):                                                        *
 *          The color green in RGB.                                           *
 *  Method:                                                                   *
 *      Set the red and blue components to zero, and the green component to t.*
 ******************************************************************************/
func Green(t float64) Color {

    /*  8-bit colors have a max intensity of 255. Scale this by t.            */
    var val uint8 = uint8(t * 255.0)
    return Color{0x00, val, 0x00}
}

/******************************************************************************
 *  Function:                                                                 *
 *      White                                                                 *
 *  Purpose:                                                                  *
 *      Returns the color white in RGB format.                                *
 *  Arguments:                                                                *
 *      t (float64):                                                          *
 *          The intensity of the color, should be between 0 and 1.            *
 *  Outputs:                                                                  *
 *      white (Color):                                                        *
 *          The color white in RGB.                                           *
 *  Method:                                                                   *
 *      Set the red, green, and blue components to t.                         *
 ******************************************************************************/
func White(t float64) Color {
    var val uint8 = uint8(t * 255.0)
    return Color{val, val, val}
}

func Grayscale(val float64) Color {

    /*  Negative values will be black.                                        */
    if (val <= 0.0) {
        return Black();

    /*  Otherwise, use a grayscale gradient from black-to-white.              */
    } else {
        var val_sq float64 = val*val;
        var val_cb float64 = val*val_sq;
        var scale float64 = val_cb * val_cb;
        return White(scale);
    }
}

func Greenscale(val float64) Color {

    /*  Negative values will be dark-green.                                   */
    if (val <= 0.0) {
        return Green(0.5);

    /*  Otherwise, use a grayscale gradient from black-to-white.              */
    } else if (val < 1.0) {
        var val_sq float64 = val*val;
        var val_cb float64 = val*val_sq;
        var scale float64 = 0.5 + val_cb * val_cb;
        return Green(scale);
    }

    /*  For background colors return white.                                   */
    return White(1.0)
}
