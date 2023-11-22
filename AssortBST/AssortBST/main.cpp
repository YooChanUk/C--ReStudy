#include<iostream>
#include<map>
#include<set>

#include<string>
#include"CBST.h"

using std::map; //������ �������� ȸ������ Ȯ���ϱ����� Red/black�� ���� ���̺귯��
using std::make_pair; //Ÿ�Գ����� �ΰ��̻� �޴� ���̺귯���� �������� �����Ҽ� �ִ� ¦�� �����ִ� ���̺귯��

using std::set;

using std::wcout;
using std::endl;

using std::wstring;

#define MAN		1
#define WOMAN	2

struct tStdInfo
{
	wchar_t			szName[20];
	unsigned char	age;
	unsigned char	gender;

	tStdInfo()
		:szName{}
		,age(0)
		,gender(0)
	{
	
	}

	tStdInfo(const wchar_t* _pName, unsigned char _age, unsigned char _gender)
		:szName{}
		,age(_age)
		,gender(_gender)
	{
		wcscpy_s(szName, _pName);//���ڿ� ���� �Լ�
	}
};

class Myclass
{
private:
	int a;

public:
	bool operator < (const Myclass& _other) const
	{
		if (a < _other.a)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

int main()
{
	//����Ž�� Ʈ��(���ĵ� �����͸� ��밡��)
	//1.����Ž���� ���� ��ȵ� ����Ʈ��
	//2.������ �Է½� O(logN)�� ȿ��
	//3.Ž�� ȿ����O(logN)

	//4.Ʈ���� ����� �뷱���� ���� ��� ����ε� Ž��ȿ�� ������ �ʴ´�.
	// - �ذ��� ���� �ڰ����� ����� �ʿ�(AVL,Red/Black)

	set<int> setInt;

	setInt.insert(100);
	setInt.insert(50);
	setInt.insert(150);

	map<const wchar_t*, tStdInfo> mapData;

	tStdInfo info(L"ȫ�浿",18,MAN);
	tStdInfo info2(L"������",25,WOMAN);

	mapData.insert(make_pair(L"ȫ�浿", info));
	mapData.insert(make_pair(L"������", info2));

	map<const wchar_t*, tStdInfo>::iterator mapiter;//wchar_t*�� �ּҰ����� ���ϴ°��̱⿡
	//������ ������ � �ּҰ� �� ���� ������ ������ ���ڿ������� �񱳷� ������ �ʴ´�.
	//���÷� "������"����ϴ� ���ο� ���� ���ڿ��� ���� �������� ã������ϸ�
	//��� "������"�� ���� "������'�� �ּҰ��� �ٸ��⿡ ã�� ���Ѵ�.
	//���ڿ��� ���ϰ�ʹٸ� ���ڿ��� �ٷ��ִ� Ŭ���� include<string>�� ����Ѵ�. using std::wstring

	mapiter = mapData.find(L"ȫ�浿"); //ã���� ������ �ٷ��ִ°� �ƴ� ���ͷ����͸� �ش�.

	_wsetlocale(LC_ALL, L"korean");//2����Ʈ������ ���ڿ��� ����ϱ����� ���˼��� wcout

	if (mapiter == mapData.end())
	{
		wcout << "������ ã�� ����" << endl;
	}
	else
	{
		wcout << L"�̸� : " << mapiter->second.szName << endl;
		wcout << L"���� : " << mapiter->second.age << endl;
		wcout << L"���� : ";

		if (MAN == mapiter->second.gender)
		{
			wcout << L"����" << endl;
		}
		else if (WOMAN == mapiter->second.gender)
		{
			wcout << L"����" << endl;
		}
		else
		{
			wcout << L"�� �� ����" << endl;
		}
	}

	//map<wstring, tStdInfo> mapStdInfo;

	wstring str; //wstring�� �ڽ� ��ü������ �ּҰ��� ������ ������ ���ڿ��� ���� �� �����ȿ� �����س��´�.
	//(charó�� �ּҸ� �ٷ� ���������� �ʴ´�) ���������� ����.(��������) �ֳ�? ���������� ���ڸ� �������ֱ� ����
	//+���ڱ����� ���ӵ� �����̱⿡ �����迭�� ���� �����ϴ�. vector<wchar_t>
	str = L"abcdef";
	str += L"hijk";
	str[1] = L'c';//""���ڿ��� const wchar_t�� ���� �ѱ�⋚���� �ٲ� �� �������� ǥ���ȴ�.

	wstring str2;

	map<Myclass, tStdInfo> mapStdInfo;
	Myclass a;
	mapStdInfo.insert(make_pair(a,info));

	if (str == str2)
	{

	}
	else if (str < str2)
	{

	}

	return 0;
}