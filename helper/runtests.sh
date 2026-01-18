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
#   Date:       October 21, 2024                                               #
################################################################################

# Runs all tests in a given directory and of a given type.
#   Example Usage:
#       runtests -cc=gcc -cpp=clang++ -type=unit -Wall -Wextra -Wpedantic
#   Arguments:
#       -cc:
#           Any C compiler supporting C99 and C11 extensions. The tests make
#           use of the _Generic keyword and variadic macros, so while the
#           the core of libtmpl is C89 compliant (and C99, C11, and C18), the
#           tests are not.
#       -cpp:
#           Any C++ compiler.
#       -type:
#           The type of tests you wish to run. Options are:
#               -type=unit
#               -type=time
#       -ExtraArgs:
#           Space separated arguments for the C and C++ compilers. For example:
#               -Wall -Wextra -Wpedantic
# All arguments are optional. Default values are:
#   -cc=gcc
#   -cpp=g++
#   -type=unit
runtests() {
    CC=gcc
    CPP=g++
    ExtraArgs="-O2 -flto -I/usr/local/include"
    LinkerFlags="-L/usr/local/lib -lgsl -lcerf -lgmp -lm -ltmpl -lquadmath"
    TYPE="unit"

    # Parse the inputs.
    for arg in "$@"; do

        # If there are no more arguments, break out of this loop.
        if [ "$arg" == "" ]; then
            break

        # Check if the user wants to use a different C compiler.
        elif [[ "$arg" == *"-cc"* ]]; then
            CC=${arg#*=}

        # Check if the user wants to use a different C++ compiler.
        elif [[ "$arg" == *"-cpp"* ]]; then
            CPP=${arg#*=}

        # Check which type of test we're running.
        elif [[ "$arg" == *"-type"* ]]; then
            TYPE=${arg#*=}

        # Check if additional linker flags are being passed.
        elif [[ "$arg" == *"-l"* ]]; then
            LinkerFlags="$LinkerFlags ${arg#*}"

        # The user can add compiler options if they want.
        else
            ExtraArgs="$ExtraArgs ${arg#*}"
        fi
    done

    for file in $(find . -name "*$TYPE*.c" -type f | sort); do
        $CC $ExtraArgs $file -o main $LinkerFlags
        printf "$(basename $file): "

        if [[ "$CC" == "emcc" ]]; then
            node main
            rm -f main.wasm
        else
            ./main
        fi

        rm -f main
    done

    for file in $(find . -name "*$TYPE*.cpp" -type f | sort); do
        $CPP $ExtraArgs -std=c++17 $file -o main $LinkerFlags
        printf "$(basename $file): "
        ./main
        rm -f main
    done
}
