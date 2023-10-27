#include "Array.h"


int main()
{
	arr a1;

	int maxcount = 2;

	arrayinit(&a1, maxcount);


	for(int i = 0; i < 10; i++)
	{
		arrayinput(&a1, i);
	}

	for (int i = 0; i < 10; i++)
	{
		printf("%d\n",a1.arr[i]);
	}

	return 0;
}