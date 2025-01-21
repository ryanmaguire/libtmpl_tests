/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
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
 *  Date:       August 12, 2021                                               *
 ******************************************************************************/

/*  printf is here.                                                           */
#include <stdio.h>

/*  clock_t data type and clock() function found here.                        */
#include <time.h>

/*  tolower found here.                                                       */
#include <ctype.h>

/*  malloc and free are here.                                                 */
#include <stdlib.h>

/*  tmpl_ASCII_Lower_Case and tmpl_Lower_Case are here.                       */
#include <libtmpl/include/tmpl_string.h>

/*  Function for comparing tmpl_ASCII_Lower_Case, tmpl_Lower_Case, and the    *
 *  standard library function tolower for speed.                              */
int main(void)
{
    /*  Three char pointers, one for an array of random chars, one to store   *
     *  the results of tmpl_ASCII_Lower_Case, one for tmpl_Lower_Case, and    *
     *  one for storing the results of tolower.                               */
    char *str, *test1, *test2, *test3;

    /*  Variable for saving the results of the rand function.                 */
    int random;

    /*  Variable for indexing.                                                */
    unsigned long int n;

    /*  Number of elements in the str array. 4*10^8 bytes should fit fine     *
     *  with 2GB of RAM, taking up 20% of the total memory. Modern computers  *
     *  with 4GB or more will have no trouble running this test.              */
    unsigned long int N = 1E8;

    /*  Variables for computing clock time later.                             */
    clock_t t1, t2;

    /*  Allocate memory for all of the pointers.                              */
    str = malloc(N);

    /*  Check if malloc failed.                                               */
    if (!str)
    {
        puts("malloc failed and returned NULL. Aborting.");
        return -1;
    }

    test1 = malloc(N);

    if (!test1)
    {
        puts("malloc failed and returned NULL. Aborting.");

        /*  free str since it was successfully allocated memory.              */
        free(str);
        return -1;
    }

    test2 = malloc(N);

    if (!test2)
    {
        puts("malloc failed and returned NULL. Aborting.");

        /*  free the pointers that were successfully allocated memory.        */
        free(str);
        free(test1);
        return -1;
    }

    test3 = malloc(N);

    if (!test3)
    {
        puts("malloc failed and returned NULL. Aborting.");

        /*  free the pointers that were successfully allocated memory.        */
        free(str);
        free(test1);
        free(test2);
        return -1;
    }

    /*  Compute a bunch of random char's for the str array.                   */
    for (n = 0; n < N; ++n)
    {
        random = rand() % 255;
        str[n] = (char)random;
    }

    /*  Run a speed test with tmpl_ASCII_Lower_Case.                          */
    t1 = clock();
    for (n = 0; n < N; ++n)
        test1[n] = tmpl_Lower_Case(str[n]);
    t2 = clock();
    printf("tmpl_ASCII_Lower_Case: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    /*  Run a speed test with tmpl_Lower_Case.                                */
    t1 = clock();
    for (n = 0; n < N; ++n)
        test2[n] = tmpl_Lower_Case(str[n]);
    t2 = clock();
    printf("tmpl_Lower_Case:       %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    /*  Run a speed test with tolower.                                        */
    t1 = clock();
    for (n = 0; n < N; ++n)
        test3[n] = tolower(str[n]);
    t2 = clock();
    printf("tolower:               %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    /*  The results should all be the same. Check that this is true.          */
    for (n = 0U; n < N; ++n)
    {
        if ((test1[n] != test3[n]) || (test2[n] != test3[n]))
        {
            puts("FAILED");

            /*  Free everything.                                              */
            free(str);
            free(test1);
            free(test2);
            free(test3);
            return -1;
        }
    }

    /*  If we get here, all tests passed. Free all pointers and return.       */
    puts("PASSED");
    free(str);
    free(test1);
    free(test2);
    free(test3);
    return 0;
}
/*  End of main.                                                              */
