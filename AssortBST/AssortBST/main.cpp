#include<iostream>
#include<map>
#include<set>

#include<string>
#include"CBST.h"

using std::map; //균형이 깨졌는지 회졌는지 확인하기위한 Red/black을 위한 라이브러리
using std::make_pair; //타입네임을 두개이상 받는 라이브러리를 묶음으로 전달할수 있는 짝을 맞춰주는 라이브러리

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
		wcscpy_s(szName, _pName);//문자열 복사 함수
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
	//이진탐색 트리(정렬된 데이터만 사용가능)
	//1.이진탐색을 위해 고안된 이진트리
	//2.데이터 입력시 O(logN)의 효율
	//3.탐색 효율은O(logN)

	//4.트리의 모양이 밸런스가 깨진 경우 제대로된 탐색효율 나오지 않는다.
	// - 해결을 위해 자가균형 기능이 필요(AVL,Red/Black)

	set<int> setInt;

	setInt.insert(100);
	setInt.insert(50);
	setInt.insert(150);

	map<const wchar_t*, tStdInfo> mapData;

	tStdInfo info(L"홍길동",18,MAN);
	tStdInfo info2(L"이지혜",25,WOMAN);

	mapData.insert(make_pair(L"홍길동", info));
	mapData.insert(make_pair(L"이지혜", info2));

	map<const wchar_t*, tStdInfo>::iterator mapiter;//wchar_t*는 주소값끼리 비교하는것이기에
	//우위를 가릴때 어떤 주소가 더 높나 낮나를 따지지 문자열끼리의 비교로 따지지 않는다.
	//예시로 "이지혜"라고하는 새로운 변수 문자열을 만들어서 이지혜를 찾으라고하면
	//상수 "이지혜"와 변수 "이지혜'는 주소값이 다르기에 찾지 못한다.
	//문자열을 비교하고싶다면 문자열을 다뤄주는 클래스 include<string>을 써야한다. using std::wstring

	mapiter = mapData.find(L"홍길동"); //찾으면 정보를 바로주는게 아닌 이터레이터를 준다.

	_wsetlocale(LC_ALL, L"korean");//2바이트형식의 문자열을 출력하기위해 포맷설정 wcout

	if (mapiter == mapData.end())
	{
		wcout << "데이터 찾지 못함" << endl;
	}
	else
	{
		wcout << L"이름 : " << mapiter->second.szName << endl;
		wcout << L"나이 : " << mapiter->second.age << endl;
		wcout << L"성별 : ";

		if (MAN == mapiter->second.gender)
		{
			wcout << L"남자" << endl;
		}
		else if (WOMAN == mapiter->second.gender)
		{
			wcout << L"여자" << endl;
		}
		else
		{
			wcout << L"알 수 없음" << endl;
		}
	}

	//map<wstring, tStdInfo> mapStdInfo;

	wstring str; //wstring은 자신 자체적으로 주소값을 가지고 있으며 문자열은 따로 그 공간안에 저장해놓는다.
	//(char처럼 주소를 바로 가지고있지 않는다) 힙영역으로 들어간다.(동적관리) 왜냐? 무한정으로 문자를 넣을수있기 때문
	//+문자구조는 연속된 구조이기에 가변배열에 가장 유사하다. vector<wchar_t>
	str = L"abcdef";
	str += L"hijk";
	str[1] = L'c';//""문자열은 const wchar_t의 값을 넘기기떄문에 바꿀 수 없음으로 표현된다.

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