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
 *  Creates a Barnley fern.                                                   *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2022/10/11                                                        *
 ******************************************************************************/

/*  All required tools are provided here.                                     */
#include "bf/bf.hpp"

/*  Function for drawing the Barnsley Fern.                                   */
int main(void)
{
    bf::run(bf::colorer::greenscale, "barnsley_fern_green.ppm");
    return 0;
}
/*  End of main.                                                              */
