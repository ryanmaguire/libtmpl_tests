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
 *      Provides the NSAMPS macro, used for calculating how many samples to   *
 *      use for a given time or unit test.                                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_cast.h:                                                          *
 *          Header file with the TMPL_CAST macro for C vs. C++ compatibility. *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   July 19, 2024                                                     *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/04/01: Ryan Maguire                                                  *
 *      Moved macros and functions out of libtmpl_tests.h and into their own  *
 *      file. libtmpl_tests.h now includes this header.                       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TESTS_MEMSIZE_H
#define TMPL_TESTS_MEMSIZE_H

/*  TMPL_CAST, providing C vs. C++ compatibility, found here.                 */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  The user may directly specify how many tests to use by defining the       *
 *  TMPL_NSAMPS macro at compile time via -DTMPL_NSAMPS=NUMBER. If not, we    *
 *  set the number of samples to be large.                                    */
#ifndef TMPL_NSAMPS

/*  There is no portable method (that I know of) for computing available      *
 *  memory. There is POSIX / Unix way and a Windows way. Handle both.         */
#ifdef _MSC_VER

/******************************************************************************
 *                                   Windows                                  *
 ******************************************************************************/

/*  MEMORYSTATUSEX typedef and GlobalMemoryStatusEx function given here.      */
#include <windows.h>

static inline size_t tmpl_tests_memsize(void)
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return TMPL_CAST(status.ullTotalPhys, size_t);
}

/*  Otherwise, try the POSIX method. There are potentially strange operating  *
 *  systems that are neither POSIX / Unix-based nor Windows. These functions  *
 *  will not work on those machines. The user will need to define TMPL_NSAMPS *
 *  manually for the tests to run.                                            */
#else

/******************************************************************************
 *                  POSIX (GNU, Linux, FreeBSD, macOS, etc.)                  *
 ******************************************************************************/

/*  sysconf found here, as are the macros _SC_PHYS_PAGES and _SC_PAGE_SIZE.   */
#include <unistd.h>

static inline size_t tmpl_tests_memsize(void)
{
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return TMPL_CAST(pages * page_size, size_t);
}

#endif
/*  End of Windows vs. Unix.                                                  */

/*  Provide a macro for computing the number of samples used for a given test.*
 *  This must be a function of the size of the input data type, otherwise we  *
 *  risk attempting to malloc the whole computer!                             */
#define NSAMPS(a) (4 * tmpl_tests_memsize() / (5*sizeof(a)))

#else
/*  Else for #ifndef TMPL_NSAMPS.                                             */

/*  If the user provided a requested sample size, simply cast it to size_t.   */
#define NSAMPS(a) TMPL_CAST(TMPL_NSAMPS, size_t)

#endif
/*  End of #ifndef TMPL_NSAMPS.                                               */

#endif
/*  End of include guard.                                                     */
