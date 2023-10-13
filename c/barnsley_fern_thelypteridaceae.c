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
 *  Creates a thelypteridaceae fern.                                          *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/10/13                                                        *
 ******************************************************************************/

/*  All required tools are provided here.                                     */
#include "bf/bf.h"

/*  Function for drawing the Barnsley Fern.                                   */
int main(void)
{
    const char *name = "barnsley_fern_thelypteridaceae.ppm";
    bf_run(bf_colorer_grayscale, &bf_thelypteridaceae_data, name);
    return 0;
}
/*  End of main.                                                              */
