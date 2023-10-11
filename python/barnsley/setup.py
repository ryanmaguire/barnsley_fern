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
#       Provides the basic setup parameters for the Barnsley fern.             #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       October 11, 2023.                                              #
################################################################################
"""

# Starting parameters for the x and y coordinates.
X_START = 0.0
Y_START = 1.0

# Maximum number of iterations allowed when making the fern.
MAX_ITERS = 64

# Number of pixels in the x and y axes.
X_SIZE = 1024
Y_SIZE = 1024

# Growth factor for the fern, between 0 and 1.
GROWTH_FACTOR = 0.8

# Total number of pixels in the PPM file.
NUMBER_OF_PIXELS = X_SIZE * Y_SIZE

# Total size of the loop, product of number of pixels and number of iterations.
TOTAL = NUMBER_OF_PIXELS * MAX_ITERS

# Scale and shift factors for the affine transformations.
X_SCALE = +0.195 * X_SIZE
Y_SCALE = -0.090 * Y_SIZE
X_SHIFT = +0.450 * X_SIZE
Y_SHIFT = +1.000 * Y_SIZE

# Converts a point on a PPM to a point in space.
def point_to_pixel(x_pt, y_pt):
    """
        Function:
            point_to_pixel
        Purpose:
            Converts a point in the plane to the corresponding pixel.
        Arguments:
            x_pt (float):
                The x coordinate of the point.
            y_pt (float):
                The y coordinate of the point.
        Outputs:
            index (int):
                The value x + y*width where (x, y) is the pixel corresponding
                to the point and width is the number of pixels in the x-axis.
    """

    # The inputs should be representable as floats. Try to convert.
    try:
        xpx = X_SHIFT + X_SCALE*x_pt
        ypx = Y_SHIFT + Y_SCALE*y_pt
        x_int = int(xpx)
        y_int = int(ypx)
        return x_int + y_int*X_SIZE

    except (TypeError, ValueError) as err:
        raise TypeError(
            "\nError: point_to_pixel\n"
            "    Inputs should be representable as floats."
        ) from err
