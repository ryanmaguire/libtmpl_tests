/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl_tests.                                       *
 *                                                                            *
 *  libtmpl_tests is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl_tests is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl_tests.  If not, see <https://www.gnu.org/licenses/>.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 25, 2022                                              *
 ******************************************************************************/

/*  Needed for the puts function.                                             */
#include <stdio.h>

/*  tmpl_Byte_Reverse4 found here.                                            */
#include <libtmpl/include/tmpl_bytes.h>

/*  Function for testing tmpl_Byte_Reverse4.                                  */
int main(void)
{
    /*  Create random char array that will be swapped later.                  */
    const char c[4] = {0x1A, 0x68, 0x33, 0x3E};

    /*  char array that will be swapped.                                      */
    char x[4];
    x[0] = c[0];
    x[1] = c[1];
    x[2] = c[2];
    x[3] = c[3];

    /*  Swap the variables.                                                   */
    tmpl_Byte_Reverse4(x);

    /*  Check if it worked.                                                   */
    if ((x[0] != c[3]) || (x[1] != c[2]) || (x[2] != c[1]) || (x[3] != c[0]))
        puts("FAIL");
    else
        puts("PASS");

    return 0;
}
/*  End of main.                                                              */
