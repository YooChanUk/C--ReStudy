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

	bstint.insert(make_bstpair(100, 0));
	bstint.insert(make_bstpair(150, 0));
	bstint.insert(make_bstpair(50, 0));

	CBST<int, int>::iterator iter = bstint.begin();

	iter = bstint.find(150);

	return 0;
}
