#include "TemplateArr.h"

int main()
{
	Arr<int> arr;

	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);

	arr.check();

	int data = arr[1];

	Arr<int>::iterator iter = arr.begin();

	return 0;
}
