#include "../fast_find_simd.h"
#include <cassert>
#include <numeric>
#include <vector>

class TestClass
{
public:

	void Func1(){}
	void Func2(){}
	void Func3(){}
};

enum TestEnum : unsigned int
{
	A = 0,
	B,
	C,
	D,
	E,
	F,
	G,
	H
};

enum class TestEnumClass : unsigned int
{
	A = 0,
	B,
	C,
	D,
	E,
	F
};

int main()
{
	{
		using member_func = void (TestClass::*)();

		std::vector<member_func> a;

		a.reserve(128);
		for (char i = 0; i <= 126; i++)
		{
			if( i % 3 == 0)
			{
				a.push_back(&TestClass::Func1);
			}
			else if (i % 3 == 1)
			{
				a.push_back(&TestClass::Func2);
			}
			else if (i % 3 == 2)
			{
				a.push_back(&TestClass::Func3);
			}
		}
		for (char i = 0; i <= 126; i++)
		{
			if (i % 3 == 0)
			{
				auto iter = fast_find_simd::find_simd(a.begin(), a.end(), &TestClass::Func1);
				assert(*iter == &TestClass::Func1);
			}
			else if (i % 3 == 1)
			{
				auto iter = fast_find_simd::find_simd(a.begin(), a.end(), &TestClass::Func2);
				assert(*iter == &TestClass::Func2);
			}
			else if (i % 3 == 2)
			{

				auto iter = fast_find_simd::find_simd(a.begin(), a.end(), &TestClass::Func3);
				assert(*iter == &TestClass::Func3);
			}
		}
	}

	{
		std::vector<TestEnum> a;

		a.reserve(128);
		for (char i = 0; i <= 126; i++)
		{
			a.push_back((TestEnum)(i%8));
		}
		for (char i = 0; i <= 126; i++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (TestEnum)(i % 8));
			assert(*iter == (TestEnum)(i % 8));
		}
	}

	{
		std::vector<TestEnumClass> a;

		a.reserve(128);
		for (char i = 0; i <= 126; i++)
		{
			a.push_back((TestEnumClass)(i % 6));
		}
		for (char i = 0; i <= 126; i++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (TestEnumClass)(i % 6));
			assert(*iter == (TestEnumClass)(i % 6));
		}
	}
}