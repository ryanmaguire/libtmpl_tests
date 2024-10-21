#!/bin/bash
rpl -R "  This file is part of libtmpl.                                             " "  This file is part of libtmpl_tests.                                       " *.c
rpl -R "  libtmpl is free software: you can redistribute it and/or modify           " "  libtmpl_tests is free software: you can redistribute it and/or modify     " *.c
rpl -R "  libtmpl is distributed in the hope that it will be useful,                " "  libtmpl_tests is distributed in the hope that it will be useful,          " *.c
rpl -R "  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         " "  along with libtmpl_tests.  If not, see <https://www.gnu.org/licenses/>.   " *.c
