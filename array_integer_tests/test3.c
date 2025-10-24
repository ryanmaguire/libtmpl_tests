#include <stdio.h>
#include <stdlib.h>
#include <libtmpl/include/tmpl.h>
#include <time.h>

int main(void)
{
    const double real_len = 1.0E8;
    const double answer = 0.5 * real_len * (real_len - 1.0);
    const size_t len = (size_t)(real_len);
    size_t n;
    double sum;
    clock_t t0, t1;

    signed long long int * const arr = malloc(sizeof(*arr) * len);

    if (!arr)
    {
        puts("malloc failed.");
        return -1;
    }

    for (n = 0; n < len; ++n)
        arr[n] = (signed long long int)n;

    t0 = clock();
    sum = tmpl_LLong_Array_Double_Sum(arr, len);
    t1 = clock();

    printf("Time: %E\n", (double)(t1 - t0) / CLOCKS_PER_SEC);

    if (sum != answer)
        puts("FAIL");
    else
        puts("PASS");

    printf("%.24E\n%.24E\n", sum, answer);

    free(arr);
    return 0;
}
