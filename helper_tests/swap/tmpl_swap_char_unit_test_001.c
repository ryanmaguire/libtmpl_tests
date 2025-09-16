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
 *  Date:       January 16, 2025                                              *
 ******************************************************************************/
#include <stdio.h>
#include <libtmpl/include/helper/tmpl_swap.h>

int main(void)
{
    const char c0 = 0x1F;
    const char c1 = 0x63;
    char x0 = c0;
    char x1 = c1;

    TMPL_SWAP(char, x0, x1);

    if ((x1 != c0) || (x0 != c1))
        puts("FAIL");
    else
        puts("PASS");

    return 0;
}
