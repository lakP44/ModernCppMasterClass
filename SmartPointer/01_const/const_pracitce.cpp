#include "const_pracitce.h"

// ��� ������ Ÿ�ӿ� �ʱ�ȭ�Ǵ� �����Դϴ�.
constinit float asd = 3.f;

/// consteval �����Լ�, �Ϻ��� ������ Ÿ�ӿ� ����˴ϴ�.
consteval int consteval_temp(int a)
{
	return a * a;
}

constexpr int const_practice::constexpr_temp(int a)
{
	int b = a * a;

	return b;
}

int const_practice::runtime_temp(int a)
{
	return 0;
}

int main(void)
{
	enum
	{
		test1 = const_practice::constexpr_temp(5),
		test2 = consteval_temp(2),
		// test3 = runtime_temp(3) // error
	};

	cout << test1 << "," << test2 << endl;
}