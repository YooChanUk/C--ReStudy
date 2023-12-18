#include"CBST.h"



int main()
{
	//이진탐색 트리(정렬된 데이터만 사용가능)
	//1.이진탐색을 위해 고안된 이진트리
	//2.데이터 입력시 O(logN)의 효율
	//3.탐색 효율은O(logN)

	//4.트리의 모양이 밸런스가 깨진 경우 제대로된 탐색효율 나오지 않는다.
	// - 해결을 위해 자가균형 기능이 필요(AVL,Red/Black)

	CBST<int, int> bstint;

	bstint.insert(make_bstpair(100, 0)); //     225
	bstint.insert(make_bstpair(150, 0)); //  50      135
	bstint.insert(make_bstpair(50, 0)); //      
	//bstint.insert(make_bstpair(270, 0));
	//bstint.insert(make_bstpair(340, 0));
	//bstint.insert(make_bstpair(35, 0));
	//bstint.insert(make_bstpair(15, 0));
	bstint.insert(make_bstpair(225, 0));
	//bstint.insert(make_bstpair(75, 0));
	bstint.insert(make_bstpair(135, 0));

	CBST<int, int>::iterator iter = bstint.begin();

	iter = bstint.find(150);

	iter = bstint.erase(iter);

	iter->first;

	for (iter = bstint.begin(); iter != bstint.end(); ++iter)
	{
		wcout << iter->first << " " << iter->second << endl;
	}

	
	

	return 0;
}
