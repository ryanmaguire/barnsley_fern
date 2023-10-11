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
#       Code for generating Barnsley ferns.                                    #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       October 11, 2023.                                              #
################################################################################
"""

# Need to generated random numbers.
import random

# Setup parameters provided here.
from . import setup

def create_fern(data):
    """
        Function:
            create_fern
        Purpose:
            Generates the values for the Barnsley fern and stores them
            inside the input list "data".
        Arguments:
            data (list):
                A list initialized to zero for the Barnsley fern data.
        Outputs:
            None.
    """

    # Initialize variables to the starting paramters.
    x_val = setup.X_START
    y_val = setup.Y_START

    # Loop over all of the pixels in the PPM.
    for _ in range(setup.TOTAL):

        # Generate a random number for the drawing.
        random_value = 100.0 * random.random()

        # Save the current parameters to avoid over-writing values.
        x_old = x_val
        y_old = y_val

        if random_value < 1.0:
            x_val = 0.0
            y_val = 0.16*y_old
        elif random_value < 86.0:
            x_val = setup.GROWTH_FACTOR*x_old + 0.04*y_old
            y_val = -0.04*x_old + 0.85*y_val + 1.6
        elif random_value < 93.0:
            x_val = 0.20*x_old - 0.26*y_old
            y_val = 0.23*x_old + 0.22*y_old + 1.6
        else:
            x_val = -0.15*x_old + 0.28*y_old
            y_val = 0.26*x_old + 0.24*y_old + 0.44

        # The the pixel (x_val, y_val) correspond to.
        index = setup.point_to_pixel(x_val, y_val)
        data[index] += 1.0
