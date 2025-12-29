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
 ******************************************************************************/
#include <libtmpl/include/tmpl_cayley_table.h>
#include <stdio.h>

static unsigned int data[9] = {
    0, 0, 0,
    2, 2, 2,
    1, 1, 1
};

int main(void)
{
    tmpl_UIntCayleyTable table;

    table.data = data;
    table.size = 3;

    if (tmpl_UIntCayleyTable_Is_Right_Self_Distributive(&table))
        puts("FAIL");
    else
        puts("PASS");

    return 0;
}
