#ifndef TMPL_TESTS_R_TO_R_VS_FROM_INTERVAL_EXACT_UNIT_TEST_H
#define TMPL_TESTS_R_TO_R_VS_FROM_INTERVAL_EXACT_UNIT_TEST_H

#define TMPL_R_TO_R_VS_FROM_INTERVAL_EXACT_UNIT_TEST(type, left, right, f0, f1)\
int main(void)                                                                 \
{                                                                              \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    size_t n;                                                                  \
    const type start = TMPL_CAST(left, type);                                  \
    const type end = TMPL_CAST(right, type);                                   \
    const size_t number_of_samples = NSAMPS(type);                             \
    const type dx = (end - start) / TMPL_CAST(number_of_samples, type);        \
    const type real_zero = TMPL_CAST(0, type);                                 \
    volatile int flag = 0;                                                     \
    volatile type x_bad = real_zero;                                           \
    volatile type y_bad = real_zero;                                           \
    volatile type z_bad = real_zero;                                           \
    TMPL_OPENMP_BASE_PRAGMA                                                    \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        if (flag)                                                              \
            continue;                                                          \
        else                                                                   \
        {                                                                      \
            const type x = TMPL_CAST(n, type) * dx + start;                    \
            const type y = f0(x);                                              \
            const type z = f1(x);                                              \
            if (y != z)                                                        \
            {                                                                  \
                x_bad = x;                                                     \
                y_bad = y;                                                     \
                z_bad = z;                                                     \
                flag = 1;                                                      \
            }                                                                  \
        }                                                                      \
    }                                                                          \
    if (flag)                                                                  \
    {                                                                          \
        puts("FAIL");                                                          \
        printf("    Input   = %+.40LE\n", TMPL_CAST(x_bad, long double));      \
        printf("    libtmpl = %+.40LE\n", TMPL_CAST(y_bad, long double));      \
        printf("    Other   = %+.40LE\n", TMPL_CAST(z_bad, long double));      \
    }                                                                          \
    else                                                                       \
        puts("PASS");                                                          \
    return 0;                                                                  \
}

#endif
