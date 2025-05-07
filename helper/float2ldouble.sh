################################################################################
#                                   LICENSE                                    #
################################################################################
#   This file is part of libtmpl_tests.                                        #
#                                                                              #
#   libtmpl_tests is free software: you can redistribute it and/or modify      #
#   it under the terms of the GNU General Public License as published by       #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   libtmpl_tests is distributed in the hope that it will be useful,           #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with libtmpl_tests.  If not, see <https://www.gnu.org/licenses/>.    #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       May 7, 2025                                                    #
################################################################################
float2ldouble() {
    sed -i -e "s/0.0F/0.0L/g" *ldouble*.c
    sed -i -e "s/0.5F/0.5L/g" *ldouble*.c
    sed -i -e "s/1.0F/1.0L/g" *ldouble*.c
    sed -i -e "s/2.0F/2.0L/g" *ldouble*.c
    sed -i -e "s/BNUMF/BNUML/g" *ldouble*.c
    sed -i -e "s/DNUMF/DNUML/g" *ldouble*.c
    sed -i -e "s/TMPL_NANF/TMPL_NANL/g" *ldouble*.c
    sed -i -e "s/TMPL_INFINITYF/TMPL_INFINITYL/g" *ldouble*.c
    sed -i -e "s/ComplexFloat/ComplexLongDouble/g" *ldouble*.c
    sed -i -e "s/VectorFloat/VectorLongDouble/g" *ldouble*.c
    sed -i -e "s/Float/LDouble/g" *ldouble*.c
    sed -i -e "s/float/long double/g" *ldouble*.c
}
