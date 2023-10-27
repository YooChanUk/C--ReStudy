#include "CArr.h"
#include "CList.h"

int main()
{
	/*CArr<int> carr;

	carr.push_back(10);
	carr.push_back(20);
	carr.push_back(30);

	carr.check();

	int i = carr[1] = 500;

	std::cout << i << std::endl;*/

	CList<int> clist;

	clist.push_back(10);
	clist.push_front(500);
	clist.push_back(20);
	clist.push_front(100);
	clist.push_back(30);
	clist.push_front(300);


	return 0;
}