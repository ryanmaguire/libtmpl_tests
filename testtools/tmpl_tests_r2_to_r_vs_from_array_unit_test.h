#ifndef TMPL_TESTS_R2_TO_R_VS_FROM_ARRAY_UNIT_TEST_H
#define TMPL_TESTS_R2_TO_R_VS_FROM_ARRAY_UNIT_TEST_H

#define TMPL_R2_TO_R_VS_FROM_ARRAY_UNIT_TEST(type, func0, func1, indata)       \
int main(void)                                                                 \
{                                                                              \
    struct real2 {type x, y;} in[] = indata;                                   \
    size_t n;                                                                  \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const size_t number_of_samples = TMPL_ARRAY_SIZE(in);                      \
    const type real_zero = TMPL_CAST(0, type);                                 \
    const type eps = TMPL_DEFAULT_TOLERANCE * TMPL_EPS(in[0].x);               \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        const type x = in[n].x;                                                \
        const type y = in[n].y;                                                \
        const type z0 = func0(x, y);                                           \
        const type z1 = func1(x, y);                                           \
        const type err = TMPL_ERROR_VALUE(z0, z1);                             \
        const tmpl_Bool z0_is_nan = TMPL_IS_NAN(z0);                           \
        const tmpl_Bool z1_is_nan = TMPL_IS_NAN(z1);                           \
        if ((z0_is_nan != z1_is_nan) || (err > eps))                           \
        {                                                                      \
            puts("FAIL");                                                      \
            printf("    Input x = %+.40LE\n", TMPL_CAST(x, long double));      \
            printf("    Input y = %+.40LE\n", TMPL_CAST(y, long double));      \
            printf("    libtmpl = %+.40LE\n", TMPL_CAST(z0, long double));     \
            printf("    Other   = %+.40LE\n", TMPL_CAST(z1, long double));     \
            printf("    Error   = %+.40LE\n", TMPL_CAST(err, long double));    \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
    puts("PASS");                                                              \
    return 0;                                                                  \
}

#endif
