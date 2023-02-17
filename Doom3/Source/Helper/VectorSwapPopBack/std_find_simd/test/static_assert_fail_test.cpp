#include "../fast_find_simd.h"
#include <cassert>
#include <numeric>
#include <vector>
#include <list>
#include <array>
#include <map>

struct A
{
	int a;
	int b;

	A(int _a) : a(_a)
	{}
};

int main()
{


	static_assert(fast_find_simd::is_iteratype_type_find_simd_capable<std::vector<A>::iterator>::value == true, "fail is_iteratype_type_find_simd_capable");

	{
		std::vector<A> a;

		for (int i = 0; i <= 200; i++)
		{
			a.emplace_back(i);
		}

		for (char i = 0; i <= 126; i++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (A)(i));
		}

	}
	
	{
		std::list<char> a;
		
		for (char i = 0; i <= 126; i++)
		{
			a.push_back(i);
		}

		for (char i = 0; i <= 126; i++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)(i));
		}

	}
	
}