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

/* Include guard to prevent including this file twice.                        */
#ifndef BF_COLOR_HPP
#define BF_COLOR_HPP

/*  File data type found here.                                                */
#include <cstdio>

/*  Struct for working with PPM files found here.                             */
#include "bf_ppm.hpp"

/*  Namespace for the mini-project. "Barnsley Fractal."                       */
namespace bf {

    /*  Simple struct for working with colors in a PPM file.                  */
    struct color {

        /*  A color is given by its RGB values.                               */
        unsigned char red, green, blue;

        /*  Empty constructor.                                                */
        color(void);

        /**********************************************************************
         *  Constructor:                                                      *
         *      bf::color                                                     *
         *  Purpose:                                                          *
         *      Creates a color struct from three unsigned values.            *
         *  Arguments:                                                        *
         *      r (unsigned char):                                            *
         *          The red component of the color.                           *
         *      g (unsigned char):                                            *
         *          The green component of the color.                         *
         *      b (unsigned char):                                            *
         *          The blue component of the color.                          *
         *  Outputs:                                                          *
         *      c (bf::color):                                                *
         *          The color (r, g, b) in 24-bit RGB color space.            *
         **********************************************************************/
        color(unsigned char r, unsigned char g, unsigned char b);

        /**********************************************************************
         *  Method:                                                           *
         *      bf::write                                                     *
         *  Purpose:                                                          *
         *      Writes a color to a FILE.                                     *
         *  Arguments:                                                        *
         *      fp (FILE *):                                                  *
         *          A pointer to a file, the file the color is written to.    *
         *  Outputs:                                                          *
         *      None (void).                                                  *
         **********************************************************************/
        inline void write(FILE *fp) const;

        /**********************************************************************
         *  Method:                                                           *
         *      bf::write                                                     *
         *  Purpose:                                                          *
         *      Writes a color to a PPM file.                                 *
         *  Arguments:                                                        *
         *      PPM (bf::ppm &):                                              *
         *          A reference to a PPM file that has been initialized.      *
         *  Outputs:                                                          *
         *      None (void).                                                  *
         **********************************************************************/
        inline void write(ppm &PPM) const;

        /**********************************************************************
         *  Operator:                                                         *
         *      *                                                             *
         *  Purpose:                                                          *
         *      Scales the intensity of a color by a real number.             *
         *  Arguments:                                                        *
         *      t (double):                                                   *
         *          A real number, usually between 0 an 1.                    *
         *  Outputs:                                                          *
         *      tc (bf::color):                                               *
         *          The color *this* with each color channel scaled by t.     *
         **********************************************************************/
        inline color operator * (double t) const;
    };

    /*  Empty constructor, just return.                                       */
    color::color(void)
    {
        return;
    }

    /**************************************************************************
     *  Constructor:                                                          *
     *      bf::color                                                         *
     *  Purpose:                                                              *
     *      Creates a color struct from three unsigned values.                *
     *  Arguments:                                                            *
     *      r (unsigned char):                                                *
     *          The red component of the color.                               *
     *      g (unsigned char):                                                *
     *          The green component of the color.                             *
     *      b (unsigned char):                                                *
     *          The blue component of the color.                              *
     *  Outputs:                                                              *
     *      c (bf::color):                                                    *
     *          The color (r, g, b) in 24-bit RGB color space.                *
     **************************************************************************/
    color::color(unsigned char r, unsigned char g, unsigned char b)
    {
        red = r;
        green = g;
        blue = b;
    }

    /**************************************************************************
     *  Method:                                                               *
     *      bf::write                                                         *
     *  Purpose:                                                              *
     *      Writes a color to a FILE.                                         *
     *  Arguments:                                                            *
     *      fp (FILE *):                                                      *
     *          A pointer to a file, the file the color is written to.        *
     *  Outputs:                                                              *
     *      None (void).                                                      *
     **************************************************************************/
    inline void color::write(FILE *fp) const
    {
        std::fputc(int(red), fp);
        std::fputc(int(green), fp);
        std::fputc(int(blue), fp);
    }

    /**************************************************************************
     *  Method:                                                               *
     *      bf::write                                                         *
     *  Purpose:                                                              *
     *      Writes a color to a PPM file.                                     *
     *  Arguments:                                                            *
     *      PPM (bf::ppm &):                                                  *
     *          A reference to a PPM file that has been initialized.          *
     *  Outputs:                                                              *
     *      None (void).                                                      *
     **************************************************************************/
    inline void color::write(ppm &PPM) const
    {
        write(PPM.fp);
    }

    /**************************************************************************
     *  Operator:                                                             *
     *      *                                                                 *
     *  Purpose:                                                              *
     *      Scales the intensity of a color by a real number.                 *
     *  Arguments:                                                            *
     *      t (double):                                                       *
     *          A real number, usually between 0 an 1.                        *
     *  Outputs:                                                              *
     *      tc (bf::color):                                                   *
     *          The color *this* with each color channel scaled by t.         *
     *  Method:                                                               *
     *      Scale each color channel by t and then cast to unsigned char.     *
     *  Notes:                                                                *
     *      No checks for overflow are performed. Large or negative values of *
     *      t may yield unexpected results.                                   *
     **************************************************************************/
    inline color color::operator * (double t) const
    {
        const unsigned char r = static_cast<unsigned char>(t*red);
        const unsigned char g = static_cast<unsigned char>(t*green);
        const unsigned char b = static_cast<unsigned char>(t*blue);
        return color(r, g, b);
    }

    /*  Constant colors that are worth having.                                */
    namespace colors {
        inline color white(void)
        {
            return color(0xFFU, 0xFFU, 0xFFU);
        }

        inline color black(void)
        {
            return color(0x00U, 0x00U, 0x00U);
        }

        inline color green(void)
        {
            return color(0x00U, 0xFFU, 0x00U);
        }
    }
    /*  End of namespace "colors".                                            */

    namespace colorer {
        inline color grayscale(double val)
        {
            /*  Negative values will be black.                                */
            if (val <= 0.0)
                return colors::black();

            /*  Otherwise, use a grayscale gradient from black-to-white.      */
            else
            {
                const double val_sq = val*val;
                const double val_cb = val*val_sq;
                const double scale = val_cb * val_cb;
                return colors::white() * scale;
            }
        }

        inline color greenscale(double val)
        {
            /*  Negative values will be black.                                */
            if (val <= 0.0)
                return colors::green() * 0.5;

            /*  Otherwise, use a grayscale gradient from black-to-white.      */
            else if (val < 1.0)
            {
                const double val_sq = val*val;
                const double val_cb = val*val_sq;
                const double scale = 0.5 + val_cb * val_cb;
                return colors::green() * scale;
            }

            /*  Color the background white. These are points outside the fern.*/
            return colors::white();
        }
    }
    /*  End of namespace "colorer".                                           */
}
/*  End of "bf" namespace.                                                    */

#endif
/*  End of include guard.                                                     */
