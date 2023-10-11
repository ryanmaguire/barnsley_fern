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
 *      Provides a struct for using colors.                                   *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/10/11                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef BF_COLOR_H
#define BF_COLOR_H

/*  FILE data type found here.                                                */
#include <stdio.h>

/*  BF_INLINE macro found here.                                               */
#include "bf_inline.h"

/*  Struct for working with PPM files found here.                             */
#include "bf_ppm.h"

/*  Simple struct for working with colors in a PPM file.                      */
struct bf_color {

    /*  A color is defined by its RGB values.                                 */
    unsigned char red, green, blue;
};

/*  Functions that color the fern.                                            */
typedef struct bf_color (*colorer)(double);

/*  Constant colors that are frequently used.                                 */
static const struct bf_color bf_white = {0xFFU, 0xFFU, 0xFFU};
static const struct bf_color bf_black = {0x00U, 0x00U, 0x00U};
static const struct bf_color bf_red = {0xFFU, 0x00U, 0x00U};
static const struct bf_color bf_green = {0x00U, 0xFFU, 0x00U};
static const struct bf_color bf_blue = {0x00U, 0x00U, 0xFFU};

/******************************************************************************
 *  Function:                                                                 *
 *      bf_color_create                                                       *
 *  Purpose:                                                                  *
 *      Creates a color struct from three unsigned values.                    *
 *  Arguments:                                                                *
 *      r (unsigned char):                                                    *
 *          The red component of the color.                                   *
 *      g (unsigned char):                                                    *
 *          The green component of the color.                                 *
 *      b (unsigned char):                                                    *
 *          The blue component of the color.                                  *
 *  Outputs:                                                                  *
 *      c (struct bf_color):                                                  *
 *          The color (r, g, b) in 24-bit RGB color space.                    *
 ******************************************************************************/
BF_INLINE struct bf_color
bf_color_create(unsigned char r, unsigned char g, unsigned char b)
{
    /*  Declare a variable for the output color.                              */
    struct bf_color c;

    /*  Set the individual components and return.                             */
    c.red = r;
    c.green = g;
    c.blue = b;
    return c;
}
/*  End of bf_color_create.                                                   */

/******************************************************************************
 *  Function:                                                                 *
 *      bf_color_write_to_file                                                *
 *  Purpose:                                                                  *
 *      Writes a color to a FILE pointer.                                     *
 *  Arguments:                                                                *
 *      c (const struct bf_color *):                                          *
 *          A pointer to a color.                                             *
 *      fp (FILE *):                                                          *
 *          A pointer to the file the color is being written to.              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
BF_INLINE void
bf_color_write_to_file(const struct bf_color *c, FILE *fp)
{
    fputc(c->red, fp);
    fputc(c->green, fp);
    fputc(c->blue, fp);
}
/*  End of bf_color_write_to_file.                                            */

/******************************************************************************
 *  Function:                                                                 *
 *      bf_color_write_to_ppm                                                 *
 *  Purpose:                                                                  *
 *      Writes a color to a ppm pointer.                                      *
 *  Arguments:                                                                *
 *      c (const struct bf_color *):                                          *
 *          A pointer to a color.                                             *
 *      PPM (struct bf_ppm *):                                                *
 *          A pointer to the ppm the color is being written to.               *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
BF_INLINE void
bf_color_write_to_ppm(const struct bf_color *c, struct bf_ppm *PPM)
{
    bf_color_write_to_file(c, PPM->fp);
}
/*  End of bf_color_write_to_ppm.                                             */

/******************************************************************************
 *  Function:                                                                 *
 *      bf_color_scale                                                        *
 *  Purpose:                                                                  *
 *      Scales a color by a real number. Used for darkening a color.          *
 *  Arguments:                                                                *
 *      c (const struct bf_color *):                                          *
 *          A pointer to a color.                                             *
 *      t (double):                                                           *
 *          The scale factor, usually between 0 and 1.                        *
 *  Outputs:                                                                  *
 *      scaled_c (struct bf_color):                                           *
 *          The input color c with RGB components scaled by t.                *
 ******************************************************************************/
BF_INLINE struct bf_color
bf_color_scale(const struct bf_color *c, double t)
{
    const unsigned char r = (unsigned char)(t * c->red);
    const unsigned char g = (unsigned char)(t * c->green);
    const unsigned char b = (unsigned char)(t * c->blue);
    return bf_color_create(r, g, b);
}
/*  End of bf_color_scale.                                                    */

/******************************************************************************
 *  Function:                                                                 *
 *      bf_colorer_grayscale                                                  *
 *  Purpose:                                                                  *
 *      Creates a grayscale as a function of a real number from 0 to 1.       *
 *  Arguments:                                                                *
 *      val (double):                                                         *
 *          The scale factor, between 0 and 1.                                *
 *  Outputs:                                                                  *
 *      grey (struct bf_color):                                               *
 *          A grey color with intensity given by the input.                   *
 ******************************************************************************/
BF_INLINE struct bf_color
bf_colorer_grayscale(double val)
{
    /*  Negative values will be black.                                        */
    if (val <= 0.0)
        return bf_black;

    /*  Otherwise, use a grayscale gradient from black-to-white.              */
    else
    {
        const double val_sq = val*val;
        const double val_cb = val*val_sq;
        const double scale = val_cb * val_cb;
        return bf_color_scale(&bf_white, scale);
    }
}
/*  End of bf_colorer_grayscale.                                              */

/******************************************************************************
 *  Function:                                                                 *
 *      bf_colorer_greenscale                                                 *
 *  Purpose:                                                                  *
 *      Creates a green-scale as a function of a real number from 0 to 1.     *
 *  Arguments:                                                                *
 *      val (double):                                                         *
 *          The scale factor, between 0 and 1.                                *
 *  Outputs:                                                                  *
 *      green (struct bf_color):                                              *
 *          A green color with intensity given by the input.                  *
 ******************************************************************************/
BF_INLINE struct bf_color
bf_colorer_greenscale(double val)
{
    /*  Negative values will be dark-green.                                   */
    if (val <= 0.0)
        return bf_color_scale(&bf_green, 0.5);

    /*  Otherwise, use a green-scale gradient from black-to-green.            */
    else if (val < 1.0)
    {
        const double val_sq = val*val;
        const double val_cb = val*val_sq;
        const double scale = 0.5 + val_cb * val_cb;
        return bf_color_scale(&bf_green, scale);
    }

    /*  For the background color use white.                                   */
    return bf_white;
}
/*  End of bf_colorer_greenscale.                                             */

#endif
/*  End of include guard.                                                     */
