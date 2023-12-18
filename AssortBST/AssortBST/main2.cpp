#include"CBST.h"



int main()
{
	//����Ž�� Ʈ��(���ĵ� �����͸� ��밡��)
	//1.����Ž���� ���� ��ȵ� ����Ʈ��
	//2.������ �Է½� O(logN)�� ȿ��
	//3.Ž�� ȿ����O(logN)

	//4.Ʈ���� ����� �뷱���� ���� ��� ����ε� Ž��ȿ�� ������ �ʴ´�.
	// - �ذ��� ���� �ڰ����� ����� �ʿ�(AVL,Red/Black)

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
