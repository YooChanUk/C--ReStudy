#include<iostream>

typedef struct array {
	int* arr;
	int count;
	int maxcount;
}arr;

void arrayinit(array* _pArr, int maxcount);

void arrayinput(array* _pArr, int inum);
