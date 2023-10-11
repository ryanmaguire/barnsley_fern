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

# Setup parameters provided here.
from . import ppm
from . import setup
from . import fern

SCALE_FACTOR = 1.0 / 256.0

def run(colorer, name):
    """
        Function:
            run
        Purpose:
            Creates the Barnsley fern.
        Arguments:
            colorer (function):
                A function that returns a color from a real argument.
            name (str):
                The name of the output PPM file.

    """

    # Create a list for the data set and initialze entries to zero.
    data = [0.0]*setup.NUMBER_OF_PIXELS

    # Create and initialize the PPM file.
    ppm_file = ppm.PPM(name)
    ppm_file.init()

    # Generate the data for the Barnsley fern.
    fern.create_fern(data)

    # Loop over the y-pixels of the PPM file.
    for y_ind in range(setup.Y_SIZE):

        # And loop over the x-pixels.
        for x_ind in range(setup.X_SIZE):

            # Get the scale factor for the current pixel.
            val = 1.0 - SCALE_FACTOR * data[x_ind + y_ind * setup.X_SIZE]

            # Generate the color and draw it.
            col = colorer(val)
            col.write(ppm_file.file)

    # Close the file and exit.
    ppm_file.close()
