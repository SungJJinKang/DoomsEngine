#include "../fast_find_simd.h"
#include <cassert>
#include <numeric>
#include <vector>
#include <array>

#if defined(__GNUC__)  || defined( __clang__)
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#elif _MSC_VER
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif

int main()
{

	static_assert(fast_find_simd::is_iteratype_type_find_simd_capable<std::vector<char>::iterator>::value == true, "fail is_iteratype_type_find_simd_capable");
	static_assert(fast_find_simd::is_iteratype_type_find_simd_capable<std::vector<int>::iterator>::value == true, "fail is_iteratype_type_find_simd_capable");
	
	PACK(struct PackedStruct
	{
		alignas(4) char padding;
		char a[32];
		alignas(4) char padding3[3];
		int b[32];
	});

	{
		PackedStruct p;

		{
			for (char i = 0; i < 32; i++)
			{
				p.a[i] = (char)i;
			}

			for (char i = 0; i < 32; i++)
			{
				auto iter = fast_find_simd::find_simd_raw(p.a, p.a + 32, (char)i);
				assert(iter == p.a + i);
			}
		}

		{
			for (int i = 0; i < 32; i++)
			{
				p.b[i] = (int)i;
			}

			for (int i = 0; i < 32; i++)
			{
				auto iter = fast_find_simd::find_simd_raw(p.b, p.b + 32, (int)i);
				assert(iter == p.b + i);
			}
		}
		
	}

	{
		std::array<char, 32> a;

		a[31] = 2;
		for (char i = 0; i < 31; i++)
		{
			a[i] = (char)1;
		}

		auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)2);
		assert(iter == a.begin() + 31);
	}


	{
		std::array<char, 34> a;

		a[33] = 2;
		for (char i = 0; i < 33; i++)
		{
			a[i] = (char)1;
		}

		auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)2);
		assert(iter == a.begin() + 33);
	}

	{
		char a[126];

		for (char i = 0; i < 125; i++)
		{
			a[i] = (char)i;
		}


		char* const address = fast_find_simd::find_simd_raw(a, a + 126, (char)126);
		assert(address == a + 126);
	}

	{
		short a[1000];

		for (short i = 0; i < 1000; i++)
		{
			a[i] = (short)i;
		}

		short* const address = fast_find_simd::find_simd_raw(a, a + 1000, (short)1001);
		assert(address == a + 1000);
	}



	{
		char a[126];

		for (char i = 0; i < 125; i++)
		{
			a[i] = (char)2;
		}
		a[125] = 10;

		char* const address = fast_find_simd::find_simd_raw(a, a + 126, (char)10);
		assert(*address == 10);
		assert(address == a + 125);
	}
	{
		short a[1001];

		for (short i = 0; i < 1000; i++)
		{
			a[i] = (short)2;
		}
		a[1000] = 10;

		short* const address = fast_find_simd::find_simd_raw(a, a + 1000, (short)10);
		assert(*address == 10);
		assert(address == a + 1000);
	}



	{
		char a[126];

		for (char i = 0; i < 126; i++)
		{
			a[i] = (char)2;
		}


		char* const address = fast_find_simd::find_simd_raw(a, a + 126, (char)2);
		assert(*address == 2);
		assert(address == a);
	}

	{
		short a[1000];

		for (short i = 0; i < 1000; i++)
		{
			a[i] = (short)2;
		}

		short* const address = fast_find_simd::find_simd_raw(a, a + 1000, (short)2);
		assert(*address == 2);
		assert(address == a);
	}
	{
		unsigned int a[1000];

		for (unsigned int i = 0; i < 1000; i++)
		{
			a[i] = (unsigned int)2;
		}


		unsigned int* const address = fast_find_simd::find_simd_raw(a, a + 1000, (unsigned int)2);
		assert(*address == 2);
		assert(address == a);
	}


	{
		char a[126];

		for (char i = 0; i < 126; i++)
		{
			a[i] = (char)i;
		}


		for (char i = 0; i < 126; i += 2)
		{
			char* const address = fast_find_simd::find_simd_raw(a, a + 126, (char)i);
			assert(address == a + i);
		}
	}

	{
		short a[1000];

		for (short i = 0; i < 1000; i++)
		{
			a[i] = (short)i;
		}

		for (short i = 1; i < 999; i += 1)
		{
			short* const address = fast_find_simd::find_simd_raw(a, a + 1000, (short)i);
			assert(address == a + i);
			assert(address != a + i - 1);
			assert(address != a + i + 1);
		}

		for (short i = 0; i < 1000; i += 2)
		{
			short* const address = fast_find_simd::find_simd_raw(a, a + 1000, (short)i);
			assert(address == a + i);
		}
	}
	{
		unsigned int a[1000];

		for (unsigned int i = 0; i < 1000; i++)
		{
			a[i] = (unsigned int)i;
		}


		for (unsigned int i = 1; i < 126; i += 2)
		{
			unsigned int* const address = fast_find_simd::find_simd_raw(a, a + 1000, (unsigned int)i);
			assert(address == a + i);
			assert(address != a + i - 1);
			assert(address != a + i + 1);
		}
	}

	{
		long long a[1000];

		for (long long i = 0; i < 1000; i++)
		{
			a[i] = (long long)i;
		}


		for (long long i = 0; i < 126; i += 2)
		{
			long long* const address = fast_find_simd::find_simd_raw(a, a + 1000, (long long)i);
			assert(address == a + i);
		}
	}

	{
		std::array<char, 126> a;

		for (char i = 0; i < 126; i++)
		{
			a[i] = (char)i;
		}


		for (char i = 0; i < 126; i++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)i);
			assert(iter == a.begin() + i);
		}

		for (char i = 0; i < 124; i += 3)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)i);
			assert(iter == a.begin() + i);
		}

		for (char i = 0; i < 124; i += 2)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)i);
			assert(iter == a.begin() + i);
		}
	}

	{
		std::vector<char> a;

		a.reserve(128);
		for (char i = 0; i <= 126; i++)
		{
			a.push_back(i);
		}

		for (char i = 0; i <= 124; i += 3)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)i);
			assert(iter == a.begin() + i);
		}

		for (char i = 0; i <= 125; i += 2)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)i);
			assert(iter == a.begin() + i);
		}

		for (char i = 0; i <= 126; i++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)i);
			assert(iter == a.begin() + i);
		}
	}

	{
		std::vector<long long> a;
		a.reserve(10000001);
		for (unsigned long long i = 0; i <= 10000000; i++)
		{
			a.push_back(i);
		}


		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (long long)0);
			assert(iter == a.begin() + 0);
		}

		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (long long)1);
			assert(iter == a.begin() + 1);
		}


		for (long long i = 500000; i < 500050; i += 2)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (long long)i);
			assert(iter == a.begin() + i);
		}


		for (long long i = 0; i < 2000; i += 3)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (long long)i);
			assert(iter == a.begin() + i);
		}

		for (long long i = 10000000 - 500; i < 10000000; i += 4)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (long long)i);
			assert(iter == a.begin() + i);
		}

	}

	{
		std::vector<unsigned long long> a;
		a.reserve(11112351 + 1);
		for (unsigned long long i = 0; i <= 11112351; i++)
		{
			a.push_back(i);
		}


		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (unsigned long long)0);
			assert(iter == a.begin() + 0);
		}

		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (unsigned long long)1);
			assert(iter == a.begin() + 1);
		}


		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (unsigned long long)500001);
			assert(iter == a.begin() + 500001);
		}


		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (unsigned long long)500002);
			assert(iter == a.begin() + 500002);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (unsigned long long)500003);
			assert(iter == a.begin() + 500003);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (unsigned long long)10000000);
			assert(iter == a.begin() + 10000000);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (unsigned long long)10000001000);
			assert(iter == a.end());
		}
	}


	///
	///
	///
	///
	///
	///

	{
		std::vector<short> a;
		a.reserve(20001);
		for (short i = -500; i <= 500; i += 1)
		{
			a.push_back(i);
		}


		for (short i = -500; i < 500; i++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)i);
			assert(iter == a.begin() + (i + 500));
		}
	}

	{
		std::vector<short> a;
		a.reserve(20001);
		for (short i = 0; i <= 20000; i+=1)
		{
			a.push_back(i);
		}


		for (short i = 0; i < 500; i ++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)i);
			assert(iter == a.begin() + i);
		}

		for (short i = 20000 - 500; i < 20000; i+=2)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)i);
			assert(iter == a.begin() + i);
		}

		for (short i = 0; i < 500; i+=5)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)i);
			assert(iter == a.begin() + i);
		}

		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)0);
			assert(iter == a.begin() + 0);
		}

		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)1);
			assert(iter == a.begin() + 1);
		}


		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)9999);
			assert(iter == a.begin() + 9999);
		}


		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)9000);
			assert(iter == a.begin() + 9000);
		}

		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)9001);
			assert(iter == a.begin() + 9001);
		}

		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)9002);
			assert(iter == a.begin() + 9002);
		}

		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)9003);
			assert(iter == a.begin() + 9003);
		}

		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)9004);
			assert(iter == a.begin() + 9004);
		}

		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)9005);
			assert(iter == a.begin() + 9005);
		}

		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)9006);
			assert(iter == a.begin() + 9006);
		}

		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)9007);
			assert(iter == a.begin() + 9007);
		}

		for(short i = 9008 ; i < 10100 ; i++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)i);
			assert(iter == a.begin() + i);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)5000);
			assert(iter == a.begin() + 5000);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)2);
			assert(iter == a.begin() + 2);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), std::numeric_limits<short>::max());
			assert(iter == a.end());
		}
	}

	{
		std::vector<int> a;
		a.reserve(1000001);
		for (int i = 0; i <= 1000000; i++)
		{
			a.push_back(i);
		}


		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (int)0);
			assert(iter == a.begin() + 0);
		}

		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (int)1);
			assert(iter == a.begin() + 1);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (int)10000);
			assert(iter == a.begin() + 10000);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (int)10001);
			assert(iter == a.begin() + 10001);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (int)10002);
			assert(iter == a.begin() + 10002);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (int)10003);
			assert(iter == a.begin() + 10003);
		}
	

		for (int i = 0; i < 100; i+=3)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (int)i);
			assert(iter == a.begin() + i);
		}
		for(int i = 9000 ; i < 9100 ; i+=5)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (int)i);
			assert(iter == a.begin() + i);
		}

	

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (int)9000);
			assert(iter == a.begin() + 9000);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (int)5000);
			assert(iter == a.begin() + 5000);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (int)2);
			assert(iter == a.begin() + 2);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), std::numeric_limits<int>::max());
			assert(iter == a.end());
		}
	}


	
	{
		std::vector<char> a;
		a.reserve(128);
		for (char i = 0; i <= 126; i++)
		{
			a.push_back(i);
		}


		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)0);
			assert(iter == a.begin() + 0);
		}

		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)1);
			assert(iter == a.begin() + 1);
		}


		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)29);
			assert(iter == a.begin() + 29);
		}


		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)2);
			assert(iter == a.begin() + 2);
		}

	
		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)30);
			assert(iter == a.begin() + 30);
		}

		{

			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (char)126);
			assert(iter == a.begin() + 126);
		}
	}

	{
		std::vector<char> a;

		a.reserve(51);
		for (char i = 0; i <= 50; i++)
		{
			a.push_back(i);
		}

		for (char i = 0; i <= 30; i++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.begin() + 30, (char)i);
			assert(iter == a.begin() + i);
		}
	}

	{
		std::vector<short> a;

		a.reserve(51);
		for (char i = 0; i <= 50; i++)
		{
			a.push_back(i);
		}

		for (char i = 0; i <= 50; i++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (short)i);
			assert(iter == a.begin() + i);
		}
	}

	{
		std::vector<unsigned long> a;

		a.reserve(51);
		for (char i = 0; i <= 50; i++)
		{
			a.push_back(i);
		}

		for (char i = 0; i <= 50; i++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (unsigned long)i);
			assert(iter == a.begin() + i);
		}
	}

	{
		std::vector<unsigned long long> a;

		a.reserve(51);
		for (char i = 0; i <= 50; i++)
		{
			a.push_back(i);
		}

		for (char i = 0; i <= 50; i++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (unsigned long long)i);
			assert(iter == a.begin() + i);
		}
	}

	{
		std::vector<int*> a;
		a.reserve(20001);
		for (int i = 0; i <= 20000; i++)
		{
			a.push_back((int*)i);
		}
		for (int i = 0; i <= 20000; i++)
		{
			auto iter = fast_find_simd::find_simd(a.begin(), a.end(), (int*)i);
			assert(iter == a.begin() + i);
		}
	}


}
