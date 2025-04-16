#ifndef TMPL_TESTS_RN_TO_R_SINGLE_UNIT_TEST_H
#define TMPL_TESTS_RN_TO_R_SINGLE_UNIT_TEST_H

#ifndef COMMA
#define COMMA ,
#endif

#define TMPL_RN_TO_R_SINGLE_UNIT_TEST(type, func, input, answer)               \
int main(void)                                                                 \
{                                                                              \
    const type result = func(input);                                           \
    const type output = answer;                                                \
    const type eps = 4 * TMPL_EPS(result);                                     \
    const type err = TMPL_ERROR_VALUE(result, output);                         \
    if (err < eps)                                                             \
        puts("PASS");                                                          \
    else                                                                       \
    {                                                                          \
        puts("FAIL");                                                          \
        printf("Result: %.16LE\n", TMPL_CAST(result, long double));            \
        printf("Answer: %.16LE\n", TMPL_CAST(output, long double));            \
        printf("Error:  %.16LE\n", TMPL_CAST(err, long double));               \
    }                                                                          \
    return 0;                                                                  \
}

#endif
