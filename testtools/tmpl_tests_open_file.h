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
 *  Purpose:                                                                  *
 *      Provides the TMPL_RAND_REAL macro. Used for creating pseudo-random    *
 *      real numbers between 0 and 1 of a given type.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdio.h:                                                              *
 *          fopen and puts are both provided in this header.                  *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   July 19, 2024                                                     *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/04/01: Ryan Maguire                                                  *
 *      Moved macro out of libtmpl_tests.h to this file.                      *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TESTS_OPEN_FILE_H
#define TMPL_TESTS_OPEN_FILE_H

/*  If running with C++, use std::func instead of just func, like in C.       */
#ifdef __cplusplus

/*  fopen and puts, as well as the FILE type, are found here.                 */
#include <cstdio>

/*  Opens a file with a given name, and with read-only permission. Aborts the *
 *  computation if fopen fails.                                               */
#define TMPL_OPEN_FILE(file_pointer, file_name)                                \
do {                                                                           \
    const char * const tmp_pfxs[] = {                                          \
        "./", "../", "../../", "../../../", "../../../../"                     \
    };                                                                         \
    const size_t tmp_pfx_length = sizeof(tmp_pfxs) / sizeof(tmp_pfxs[0]);      \
    size_t tmp_ind;                                                            \
    char tmp_path[1024];                                                       \
    for (tmp_ind = 0; tmp_ind < tmp_pfx_length; ++tmp_ind)                     \
    {                                                                          \
        std::sprintf(tmp_path, "%s%s", tmp_pfxs[tmp_ind], file_name);          \
        file_pointer = std::fopen(tmp_path, "r");                              \
        if (file_pointer)                                                      \
            break;                                                             \
    }                                                                          \
    if (!file_pointer)                                                         \
    {                                                                          \
        std::puts("fopen failed. Aborting.");                                  \
        return -1;                                                             \
    }                                                                          \
} while (0)

#else

/*  C equivalent of cstdio, just include stdio.h.                             */
#include <stdio.h>

/*  C version of the macro provided above.                                    */
#define TMPL_OPEN_FILE(file_pointer, file_name)                                \
do {                                                                           \
    const char * const tmp_pfxs[] = {                                          \
        "./", "../", "../../", "../../../", "../../../../"                     \
    };                                                                         \
    const size_t tmp_pfx_length = sizeof(tmp_pfxs) / sizeof(tmp_pfxs[0]);      \
    size_t tmp_ind;                                                            \
    char tmp_path[1024];                                                       \
    for (tmp_ind = 0; tmp_ind < tmp_pfx_length; ++tmp_ind)                     \
    {                                                                          \
        sprintf(tmp_path, "%s%s", tmp_pfxs[tmp_ind], file_name);               \
        file_pointer = fopen(tmp_path, "r");                                   \
        if (file_pointer)                                                      \
            break;                                                             \
    }                                                                          \
    if (!file_pointer)                                                         \
    {                                                                          \
        puts("fopen failed. Aborting.");                                       \
        return -1;                                                             \
    }                                                                          \
} while (0)

#endif
/*  End of C vs. C++.                                                         */

#endif
/*  End of include guard.                                                     */
