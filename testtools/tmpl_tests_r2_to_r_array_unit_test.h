#ifndef TMPL_TESTS_R2_TO_R_ARRAY_UNIT_TEST_H
#define TMPL_TESTS_R2_TO_R_ARRAY_UNIT_TEST_H

#define TMPL_R2_TO_R_ARRAY_UNIT_TEST(type, func, indata, outdata)              \
int main(void)                                                                 \
{                                                                              \
    struct real2 {type x, y;} in[] = indata;                                   \
    const type out[] = outdata;                                                \
    const type eps = 2 * TMPL_EPS(in[0].x);                                    \
    const size_t zero = TMPL_CAST(0, size_t);                                  \
    const size_t number_of_samples = TMPL_ARRAY_SIZE(in);                      \
    size_t n;                                                                  \
    for (n = zero; n < number_of_samples; ++n)                                 \
    {                                                                          \
        const type output = func(in[n].x, in[n].y);                            \
        const type err = TMPL_ERROR_VALUE(output, out[n]);                     \
        const tmpl_Bool val_is_nan = TMPL_IS_NAN(output);                      \
        const tmpl_Bool out_is_nan = TMPL_IS_NAN(out[n]);                      \
        if (out_is_nan && val_is_nan)                                          \
            continue;                                                          \
        else if ((val_is_nan != out_is_nan) || (err > eps))                    \
        {                                                                      \
            puts("FAIL");                                                      \
            printf("    Input x = %+.40LE\n", TMPL_CAST(in[n].x, long double));\
            printf("    Input y = %+.40LE\n", TMPL_CAST(in[n].y, long double));\
            printf("    libtmpl = %+.40LE\n", TMPL_CAST(output, long double)); \
            printf("    Other   = %+.40LE\n", TMPL_CAST(out[n], long double)); \
            return -1;                                                         \
        }                                                                      \
    }                                                                          \
    puts("PASS");                                                              \
    return 0;                                                                  \
}

#endif
