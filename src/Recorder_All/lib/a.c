#include <stdio.h>

int main()
{
	int b[10];
	printf("%lu %lu\n", &b[0], &b[1]);
	int i;
	for (i=0; i<10; i++) {
		int a = 0;
		a+=3;
	//	printf("%d\n", a);
	}
	return 0;
}
