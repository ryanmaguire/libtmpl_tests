#include <stdio.h>
#include <libtmpl/include/tmpl.h>

int main(void)
{
    const signed long long int big = 9223372036854775807LL;
    const signed long long int arr[4] = {1LL, big, 1LL, -big};
    const double sum = tmpl_LLong_Array_Double_Sum(arr, 4);
    printf("%E\n", sum);
    return 0;
}
