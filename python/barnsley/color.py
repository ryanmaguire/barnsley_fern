"""
################################################################################
#                                   LICENSE                                    #
################################################################################
#   This file is part of barnsley_fern.                                        #
#                                                                              #
#   barnsley_fern is free software: you can redistribute it and/or modify it   #
#   under the terms of the GNU General Public License as published by          #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   barnsley_fern is distributed in the hope that it will be useful,           #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with barnsley_fern.  If not, see <https://www.gnu.org/licenses/>.    #
################################################################################
#   Purpose:                                                                   #
#       Provides a class for working with colors in RGB format.                #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       October 11, 2023.                                              #
################################################################################
"""

# File type TextIOWrapper given here.
import io

# Class for working with colors.
class Color:
    """
        Class:
            Color
        Purpose:
            Basic color class for working with colors in RGB format.
    """

    # Constructor from the red, green, and blue components.
    def __init__(self, red, green, blue):
        """
            Function:
                __init__
            Purpose:
                Creates a Color class from RGB values.
            Arguments:
                red (int):
                    The red component of the color.
                green (int):
                    The green component of the color.
                blue (int):
                    The blue component of the color.
            Outputs:
                The color with RGB components given by the inputs.
        """

        # The inputs should be representable as integers. Try to convert.
        try:
            # Colors are 8-bit integers. Reduce mod 2^8 = 256 (0xFF = 255).
            self.red = abs(int(red)) & 0xFF
            self.green = abs(int(green)) & 0xFF
            self.blue = abs(int(blue)) & 0xFF

        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Color\n"
                "    Cannot convert inputs to ints."
            ) from err

    # Writes a color to a PPM file.
    def write(self, file):
        """
            Function:
                write
            Purpose:
                Writes a color to a file.
            Arguments:
                file (io.TextIOWrapper):
                    The file the color is being written to.
        """
        if not isinstance(file, io.TextIOWrapper):
            raise TypeError(
                "\nError: Color\n"
                "    Can only write a Color instance to a file."
            )

        file.write("%u %u %u\n" % (self.red, self.green, self.blue))

    # Scales a color by a real number. Used for darkening.
    def __mul__(self, scale):
        """
            Operator:
                Multiplication (*).
            Purpose:
                Scales the intensity of a Color by a positive real number.
            Arguments:
                scale (float):
                    The scale factor for the intensity, usually between 0 and 1.
            Outputs:
                scaled_color (Color):
                    self scaled by the scale factor.
        """

        # Input must be representable as a float.
        try:
            scale_factor = float(scale)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Color\n"
                "    Trying to multiply a Color instance with an\n"
                "    object that cannot be converted to float."
            ) from err

        # Scale the colors and convert to ints.
        red = int(abs(scale_factor * self.red))
        green = int(abs(scale_factor * self.green))
        blue = int(abs(scale_factor * self.blue))
        return Color(red, green, blue)

    # Scales a color by a real number. Used for darkening.
    def __rmul__(self, scale):
        """
            Operator:
                Multiplication (*).
            Purpose:
                Scales the intensity of a Color by a positive real number.
            Arguments:
                scale (float):
                    The scale factor for the intensity, usually between 0 and 1.
            Outputs:
                scaled_color (Color):
                    self scaled by the scale factor.
        """

        # Input must be representable as a float.
        try:
            scale_factor = float(scale)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Color\n"
                "    Trying to multiply a Color instance with an\n"
                "    object that cannot be converted to float."
            ) from err

        # Scale the colors and convert to ints.
        red = int(abs(scale_factor * self.red))
        green = int(abs(scale_factor * self.green))
        blue = int(abs(scale_factor * self.blue))
        return Color(red, green, blue)

    # Scales a color by a real number. Used for darkening.
    def __imul__(self, scale):
        """
            Operator:
                Multiplication (*=).
            Purpose:
                Scales the intensity of a Color by a positive real number.
            Arguments:
                scale (float):
                    The scale factor for the intensity, usually between 0 and 1.
            Outputs:
                None.
        """

        # Input must be representable as a float.
        try:
            scale_factor = float(scale)
        except (TypeError, ValueError) as err:
            raise TypeError(
                "\nError: Color\n"
                "    Trying to multiply a Color instance with an\n"
                "    object that cannot be converted to float."
            ) from err

        # Scale the colors and convert to ints.
        self.red = int(abs(scale_factor * self.red))
        self.green = int(abs(scale_factor * self.green))
        self.blue = int(abs(scale_factor * self.blue))
        return self

# Constant colors that are useful.
GREEN = Color(0x00, 0xFF, 0x00)
WHITE = Color(0xFF, 0xFF, 0xFF)
BLACK = Color(0x00, 0x00, 0x00)

def grayscale(val):
    """
        Function:
            grayscale
        Purpose:
            Creates a gray-scale pattern from real numbers 0 to 1.
        Arguments:
            val (float):
                A real number between 0 and 1.
        Outputs:
            col (Color):
                The grayscale pattern as a function of val.
    """

    # The input should be representable as a float.
    try:
        val_as_float = float(val)
    except ValueError as err:
        raise TypeError(
            "\nError: Color\n"
            "    Cannot convert input to float."
        ) from err

    # Negative values will be black.
    if val_as_float <= 0.0:
        return BLACK

    # Otherwise use a black-to-white gradient.
    val_sq = val_as_float * val_as_float
    val_cb = val_as_float * val_sq
    scale = val_cb * val_cb
    return WHITE * scale

def greenscale(val):
    """
        Function:
            greenscale
        Purpose:
            Creates a green-scale pattern from real numbers 0 to 1.
        Arguments:
            val (float):
                A real number between 0 and 1.
        Outputs:
            col (Color):
                The green-scale pattern as a function of val.
    """

    # The input should be representable as a float.
    try:
        val_as_float = float(val)
    except ValueError as err:
        raise TypeError(
            "\nError: Color\n"
            "    Cannot convert input to float."
        ) from err

    # Negative values will be black.
    if val_as_float <= 0.0:
        return 0.5 * GREEN

    # Otherwise use a black-to-white gradient.
    if val_as_float < 1.0:
        val_sq = val_as_float * val_as_float
        val_cb = val_as_float * val_sq
        scale = 0.5 + val_cb * val_cb
        return GREEN * scale

    # The background pixels will be colored white.
    return WHITE
