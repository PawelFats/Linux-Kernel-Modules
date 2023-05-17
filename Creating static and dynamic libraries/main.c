#include <stdio.h>

// описываем функцию f1() как внешнюю
extern int f1();

// описываем функцию f2() как внешнюю
extern int f2();

int main()
{
	int a, b, n1, n2;
	
	printf("Enter the number A: ");
	scanf("%d",&a);
	printf("Enter the number B: ");
	scanf("%d",&b);
	
	n1 = f1(a,b);
	n2 = f2(a,b);

	printf("Addition operation f1(a,b) = %d\n",n1);
	printf("Subtraction operation f2(a,b) = %d\n",n2);

	return 0;
}
