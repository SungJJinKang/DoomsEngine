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
#include <set>

#include "../fast_find_simd.h"


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
		for (long long i = 0; i < 1000; i+=8)
		{
			benchmark::DoNotOptimize(std::find(a.begin(), a.end(), (long long)i));
		}
	}
}
// Register the function as a benchmark
BENCHMARK(Scalar_unordered_set_find_8byte);

static void Scalar_set_find_8byte(benchmark::State& state)
{
	std::set<long long> a;
	for (unsigned long long i = 0; i <= 1000; i++)
	{
		a.emplace(i);
	}
	for (auto _ : state)
	{
		for (long long i = 0; i < 1000; i += 8)
		{
			benchmark::DoNotOptimize(std::find(a.begin(), a.end(), (long long)i));
		}
	}
}
// Register the function as a benchmark
BENCHMARK(Scalar_set_find_8byte);

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
		for (long long i = 0; i < 1000; i+=8)
		{
			benchmark::DoNotOptimize(fast_find_simd::find_simd(a.begin(), a.end(), (long long)i));
		}
	}

}
BENCHMARK(Simd_vector_find_8byte);


static void Scalar_set_find_4byte(benchmark::State& state)
{
	std::set<int> a;
	for (unsigned int i = 0; i <= 1000; i++)
	{
		a.emplace(i);
	}
	for (auto _ : state)
	{
		for (int i = 0; i < 1000; i += 8)
		{
			benchmark::DoNotOptimize(std::find(a.begin(), a.end(), (int)i));
		}
	}
}
// Register the function as a benchmark
BENCHMARK(Scalar_set_find_4byte);

static void Scalar_unordered_set_find_4byte(benchmark::State& state)
{
	std::unordered_set<int> a;
	a.reserve(1001);
	for (unsigned int i = 0; i <= 1000; i++)
	{
		a.emplace(i);
	}
	for (auto _ : state)
	{
		for (int i = 0; i < 1000; i += 8)
		{
			benchmark::DoNotOptimize(std::find(a.begin(), a.end(), (int)i));
		}
	}
}
// Register the function as a benchmark
BENCHMARK(Scalar_unordered_set_find_4byte);

// Define another benchmark
static void Simd_vector_find_4byte(benchmark::State& state)
{
	std::vector<int> a;
	a.reserve(1001);
	for (unsigned int i = 0; i <= 1000; i++)
	{
		a.push_back(i);
	}
	for (auto _ : state)
	{
		for (int i = 0; i < 1000; i += 8)
		{
			benchmark::DoNotOptimize(fast_find_simd::find_simd(a.begin(), a.end(), (int)i));
		}
	}

}
BENCHMARK(Simd_vector_find_4byte);



