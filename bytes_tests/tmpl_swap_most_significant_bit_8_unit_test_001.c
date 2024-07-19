/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 25, 2022                                              *
 ******************************************************************************/

/*  Needed for the puts function.                                             */
#include <stdio.h>

/*  tmpl_Swap_Most_Significant_Bit_8 found here.                              */
#include <libtmpl/include/tmpl_bytes.h>

/*  Function for testing tmpl_Swap_Most_Significant_Bit_8.                    */
int main(void)
{
    /*  Create random char array that will be swapped later.                  */
    const char c[8] = {0x1A, 0x68, 0x33, 0x3E, 0x77, 0x3D, 0x2C, 0x5B};

    /*  char array that will be swapped.                                      */
    char x[8];
    x[0] = c[0];
    x[1] = c[1];
    x[2] = c[2];
    x[3] = c[3];
    x[4] = c[4];
    x[5] = c[5];
    x[6] = c[6];
    x[7] = c[7];

    /*  Swap the variables.                                                   */
    tmpl_Swap_Most_Significant_Bit_8(x);

    /*  Check if it worked.                                                   */
    if ((x[0] != c[7]) || (x[1] != c[6]) || (x[2] != c[5]) || (x[3] != c[4]) ||
        (x[4] != c[3]) || (x[5] != c[2]) || (x[6] != c[1]) || (x[7] != c[0]))

        puts("FAIL");
    else
        puts("PASS");

    return 0;
}
/*  End of main.                                                              */

