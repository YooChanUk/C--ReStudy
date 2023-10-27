#include<stdio.h>


int Fibonacci(int count)
{
	if (1 == count || 2 == count)
	{
		return 1;
	}

	int num1 = 1;
	int num2 = 1;
	int tmp = 0;

	for (int i = 0; i < count - 2; ++i)
	{
		tmp = num1 + num2;
		num1 = num2;
		num2 = tmp;
	}

	return num2;
}

int Fibonacci_re(int count)
{
	if (1 == count || 2 == count)
	{
		return 1;
	}

	return Fibonacci_re(count - 1) + Fibonacci_re(count - 2);
}


int main()
{
	int fibo = Fibonacci(7);
	int refibo = Fibonacci_re(8);

	return 0;
}