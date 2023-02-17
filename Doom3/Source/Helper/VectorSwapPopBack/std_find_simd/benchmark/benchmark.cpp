// Alternatively, can add libraries using linker options.
#ifdef _WIN32
#pragma comment ( lib, "Shlwapi.lib" )
#ifdef _DEBUG
#pragma comment ( lib, "benchmarkd.lib" )
#else
#pragma comment ( lib, "benchmark.lib" )
#endif
#endif

#include <benchmark/benchmark.h>
#include <algorithm>
#include <unordered_set>

#include "../fast_find_simd.h"


static void Scalar_find_8byte(benchmark::State& state)
{
	std::vector<long long> a;
	a.reserve(1001);
	for (unsigned long long i = 0; i <= 1000; i++)
	{
		a.push_back(i);
	}
    for (auto _ : state)
    {
		for (long long i = 0; i < 1000; i++)
		{
			benchmark::DoNotOptimize(std::find(a.begin(), a.end(), (long long)i));
		}
    }
}
// Register the function as a benchmark
BENCHMARK(Scalar_find_8byte);

// Define another benchmark
static void Simd_find_8byte(benchmark::State& state)
{
	std::vector<long long> a;
	a.reserve(1001);
	for (unsigned long long i = 0; i <= 1000; i++)
	{
		a.push_back(i);
	}
    for (auto _ : state)
    {
		for (long long i = 0; i < 1000; i++)
		{
			benchmark::DoNotOptimize(fast_find_simd::find_simd(a.begin(), a.end(), (long long)i));
		}
    }

}
BENCHMARK(Simd_find_8byte);


static void Scalar_find_4byte(benchmark::State& state)
{
	std::vector<int> a;
	a.reserve(1001);
	for (unsigned int i = 0; i <= 1000; i++)
	{
		a.push_back(i);
	}
	for (auto _ : state)
	{
		for (int i = 0; i < 1000; i++)
		{
			benchmark::DoNotOptimize(std::find(a.begin(), a.end(), (int)i));
		}
	}
}
// Register the function as a benchmark
BENCHMARK(Scalar_find_4byte);

// Define another benchmark
static void Simd_find_4byte(benchmark::State& state)
{
	std::vector<int> a;
	a.reserve(1001);
	for (unsigned int i = 0; i <= 1000; i++)
	{
		a.push_back(i);
	}
	for (auto _ : state)
	{
		for (int i = 0; i < 1000; i++)
		{
			benchmark::DoNotOptimize(fast_find_simd::find_simd(a.begin(), a.end(), (int)i));
		}
	}

}
BENCHMARK(Simd_find_4byte);



static void Scalar_find_2byte(benchmark::State& state)
{
	std::vector<short> a;
	a.reserve(1001);
	for (unsigned short i = 0; i <= 1000; i++)
	{
		a.push_back(i);
	}
	for (auto _ : state)
	{
		for (short i = 0; i < 1000; i++)
		{
			benchmark::DoNotOptimize(std::find(a.begin(), a.end(), (short)i));
		}
	}
}
// Register the function as a benchmark
BENCHMARK(Scalar_find_2byte);

// Define another benchmark
static void Simd_find_2byte(benchmark::State& state)
{
	std::vector<short> a;
	a.reserve(1001);
	for (unsigned short i = 0; i <= 1000; i++)
	{
		a.push_back(i);
	}
	for (auto _ : state)
	{
		for (short i = 0; i < 1000; i++)
		{
			benchmark::DoNotOptimize(fast_find_simd::find_simd(a.begin(), a.end(), (short)i));
		}
	}

}
BENCHMARK(Simd_find_2byte);

static void Scalar_find_1byte(benchmark::State& state)
{
	std::vector<char> a;
	a.reserve(1001);

	for (size_t i = 0; i < 80; i++)
	{
		for (unsigned char i = 0; i <= 125; i++)
		{
			a.push_back(i);
		}
	}

	for (auto _ : state)
	{
		for (size_t i = 0; i < 80; i++)
		{
			for (char i = 0; i < 125; i++)
			{
				benchmark::DoNotOptimize(std::find(a.begin(), a.end(), (char)i));
			}
		}
	}
}
// Register the function as a benchmark
BENCHMARK(Scalar_find_1byte);

// Define another benchmark
static void Simd_find_1byte(benchmark::State& state)
{
	std::vector<char> a;
	a.reserve(1001);

	for(size_t i = 0 ; i < 80 ; i++)
	{
		for (unsigned char i = 0; i <= 125; i++)
		{
			a.push_back(i);
		}
	}
	
	for (auto _ : state)
	{
		for (size_t i = 0; i < 80; i++)
		{
			for (char i = 0; i < 125; i++)
			{
				benchmark::DoNotOptimize(fast_find_simd::find_simd(a.begin(), a.end(), (char)i));
			}
		}
	}

}
BENCHMARK(Simd_find_1byte);



/////////////////////

static void Scalar_unordered_set_find_8byte(benchmark::State& state)
{
	std::unordered_set<long long> a;
	a.reserve(1001);
	for (unsigned long long i = 0; i <= 1000; i++)
	{
		a.emplace(i);
	}
	for (auto _ : state)
	{
		for (long long i = 0; i < 1000; i += 10)
		{
			benchmark::DoNotOptimize(std::find(a.begin(), a.end(), (long long)i));
		}
	}
}
// Register the function as a benchmark
BENCHMARK(Scalar_unordered_set_find_8byte);

// Define another benchmark
static void Simd_vector_find_8byte(benchmark::State& state)
{
	std::vector<long long> a;
	a.reserve(1001);
	for (unsigned long long i = 0; i <= 1000; i++)
	{
		a.push_back(i);
	}
	for (auto _ : state)
	{
		for (long long i = 0; i < 1000; i += 10)
		{
			benchmark::DoNotOptimize(fast_find_simd::find_simd(a.begin(), a.end(), (long long)i));
		}
	}

}
BENCHMARK(Simd_vector_find_8byte);