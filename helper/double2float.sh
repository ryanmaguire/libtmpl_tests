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
double2float() {
    sed -i -e "s/0.0/0.0F/g" *float*.c
    sed -i -e "s/0.5/0.5F/g" *float*.c
    sed -i -e "s/1.0/1.0F/g" *float*.c
    sed -i -e "s/2.0/2.0F/g" *float*.c
    sed -i -e "s/BNUM/BNUMF/g" *float*.c
    sed -i -e "s/DNUM/DNUMF/g" *float*.c
    sed -i -e "s/TMPL_NAN/TMPL_NANF/g" *float*.c
    sed -i -e "s/TMPL_INFINITY/TMPL_INFINITYF/g" *float*.c
    sed -i -e "s/Double/Float/g" *float*.c
    sed -i -e "s/double/float/g" *float*.c
}
