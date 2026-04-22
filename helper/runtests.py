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
#   Date:       April 22, 2026                                                 #
################################################################################

import sys
import os
import subprocess
import pathlib

def cleanup_binary(filename):
    """
        Helper function to clean up compiled binaries.
    """
    if os.path.exists(filename):
        os.remove(filename)

def runtests():
    """
        Runs all tests in a given directory and of a given type.
            Example Usage:
                python3 runtests.py -cc=gcc -cpp=clang++ -type=unit -Wall
            Arguments:
                -cc:
                    Any C compiler supporting C99 and C11 extensions. The tests
                    make use of the _Generic keyword and variadic macros, so
                    while the the core of libtmpl is C89 compliant (and C99,
                    C11, and C18), the tests are not.
                -cpp:
                    Any C++ compiler.
                -type:
                    The type of tests you wish to run. Options are:
                        -type=unit
                        -type=time
                -ExtraArgs:
                    Space separated arguments for the C and C++ compilers.
                    For example:
                        -Wall -Wextra -Wpedantic
        All arguments are optional. Default values are:
            -cc=gcc
            -cpp=g++
            -type=unit
    """
    # Default variable setup
    cc = "gcc"
    cpp = "g++"
    extra_args = [
        "-O2",
        "-flto",
        "-I/usr/local/include"
    ]

    linker_flags = [
        "-L/usr/local/lib",
        "-lgsl",
        "-lcerf",
        "-lgmp",
        "-lm",
        "-ltmpl",
        "-lquadmath"
    ]

    test_type = "unit"

    # Parse the inputs
    for arg in sys.argv[1:]:
        if not arg:
            break
        elif arg.startswith("-cc="):
            cc = arg.split("=", 1)[1]
        elif arg.startswith("-cpp="):
            cpp = arg.split("=", 1)[1]
        elif arg.startswith("-type="):
            test_type = arg.split("=", 1)[1]
        elif arg.startswith("-l"):
            linker_flags.append(arg)
        elif arg == "-noquadmath":
            linker_flags = [flag for flag in linker_flags if flag != "-lquadmath"]
        elif arg == "-nogsl":
            linker_flags = [flag for flag in linker_flags if flag != "-lgsl"]
        elif arg == "-nogmp":
            linker_flags = [flag for flag in linker_flags if flag != "-lgmp"]
            linker_flags.append("-DNO_GMP")
        elif arg == "-nocerf":
            linker_flags = [flag for flag in linker_flags if flag != "-lcerf"]
        else:
            extra_args.append(arg)

    c_files = sorted(
        p for p in pathlib.Path('.').rglob(f'*{test_type}*.c') if p.is_file()
    )

    for file_path in c_files:

        cmd = [cc] + extra_args + [str(file_path), "-o", "main"] + linker_flags
        subprocess.run(cmd, check=False)

        print(f"{file_path.name}: ", end="", flush=True)

        if cc == "emcc":
            subprocess.run(["node", "main"], check=False)
            cleanup_binary("main.wasm")
        else:
            if os.path.exists("./main"):
                subprocess.run(["./main"], check=False)

        cleanup_binary("main")

    cpp_files = sorted(
        p for p in pathlib.Path('.').rglob(f'*{test_type}*.cpp') if p.is_file()
    )

    for file_path in cpp_files:

        cmd = [cpp] + extra_args + ["-std=c++17", str(file_path), "-o", "main"] + linker_flags
        subprocess.run(cmd, check=False)

        print(f"{file_path.name}: ", end="", flush=True)

        if os.path.exists("./main"):
            subprocess.run(["./main"], check=False)

        cleanup_binary("main")

if __name__ == "__main__":
    runtests()