#include "../fast_find_simd.h"
#include <cassert>
#include <numeric>
#include <array>
#include <vector>


int main()
{

	{
		std::array<int, 1000> testArray;
		for(int i = 0 ; i < 1000 ; i++)
		{
			testArray[i] = i;
		}

		for (int i = 0; i < 1000; i++)
		{
			auto iter = fast_find_simd::find_simd(testArray.begin(), testArray.end(), testArray[i]);
			assert(*iter == testArray[i]);
		}
	}

	{
		std::array<short, 1000> testArray;
		for (int i = 0; i < 1000; i++)
		{
			testArray[i] = i;
		}

		for (int i = 0; i < 1000; i++)
		{
			auto iter = fast_find_simd::find_simd(testArray.begin(), testArray.end(), testArray[i]);
			assert(*iter == testArray[i]);
		}
	}

	{
		std::array<char, 1000> testArray;
		for (int i = 0; i < 1000; i++)
		{
			testArray[i] = i;
		}

		for (int i = 0; i < 1000; i++)
		{
			auto iter = fast_find_simd::find_simd(testArray.begin(), testArray.end(), testArray[i]);
			assert(*iter == testArray[i]);
		}
	}

	{
		std::vector<char> testVector;
		testVector.reserve(1001);
		for (int i = 0; i < 1000; i++)
		{
			testVector.push_back(i);
		}

		for (int i = 0; i < 1000; i++)
		{
			auto iter = fast_find_simd::find_simd(testVector.begin(), testVector.end(), testVector[i]);
			assert(*iter == testVector[i]);
		}
	}
}