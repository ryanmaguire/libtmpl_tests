#include <libtmpl/include/tmpl_vec3.h>
#include <stdio.h>

int main(void)
{
	tmpl_ThreeVectorDouble P = tmpl_3DDouble_Rect(1.0, 1.0, 0.0);
	tmpl_ThreeVectorDouble Q = tmpl_3DDouble_Rect(0.01, 0.10, 1.0);
	double a = tmpl_3DDouble_Quick_Angle(&P, &Q);
	double b = tmpl_3DDouble_Angle(&P, &Q);

	printf("%.24e\n%.24e\n%.24e\n", a, b, (a - b) / b);
	return 0;
}
