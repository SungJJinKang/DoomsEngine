#pragma once

#include <limits>
#include <cmath>
#include <type_traits>

namespace Math
{
	template<typename T>
	constexpr T DegreeToRadin(T value);

	template<typename T>
	constexpr T RadinToDegree(T value);

	template<typename T>
	using Epsilon = std::numeric_limits<T>::epsilon();

	template<typename T>
	constexpr std::enable_if_t<std::is_floating_point_v<T>> PI = 3.14159265358979323846;

	template<typename T>
	constexpr std::enable_if_t<std::is_arithmetic_v<T> && !std::is_unsigned_v<T>> Abs(T value)
	{
		return std::abs(value);
	}

	template<typename T>
	constexpr std::enable_if_t<std::is_arithmetic_v<T> && std::is_unsigned_v<T>> Abs(T value)
	{
		return value;
	}

	template<typename T>
	constexpr T Acos(T value);

	template<typename T>
	constexpr T Asin(T value);

	template<typename T>
	constexpr T Atan(T value);

	template<typename T>
	constexpr T Atan2(T value);

	template<typename T, typename Limit, typename std::enable_if_t<std::is_arithmetic_v<Limit>> = true>
	constexpr typename std::enable_if_t<std::is_arithmetic_v<T>> Clamp(T value, Limit min, Limit max)
	{
		if (value < min)
			x = min;
		else if (value > max)
			x = max;
		return x;
	}

	template<typename T>
	constexpr typename std::enable_if_t<std::is_arithmetic_v<T>> Clamp(T value)
	{
		if (value < 0)
			x = min;
		else if (value > 1)
			x = max;
		return x;
	}


	template<typename T>
	constexpr T Cos(T value);

	template<typename T>
	constexpr T DeltaAngle(T value);

	template<typename T>
	constexpr T Exp(T value);

	template<typename T>
	using Infinity = std::numeric_limits<T>::max();

	template<typename T>
	using Infinity = std::numeric_limits<T>::lowest();

	template<typename T>
	constexpr T InverseLerp(T value);

	template<typename Value, typename Floating, typename std::enable_if_t<std::is_floating_point_v<Floating>> = true>
	constexpr typename std::enable_if_t<std::is_arithmetic_v<Value>> Lerp(Value value1, Value value2, Floating t)
	{
		return value1 + t(value2 - value1);
	}

	template<typename T>
	constexpr T LerpUnClamped(T value);

	template<typename T>
	constexpr T Log(T value);

	template<typename T>
	constexpr T Log10(T value);

	template<typename T, typename std::enable_if_t<std::is_arithmetic_v<T>> = true>
	constexpr T Max(T x, T y)
	{
		return x > y ? x : y;
	}

	template<typename T, typename std::enable_if_t<std::is_arithmetic_v<T>> = true>
	constexpr T Min(T x, T y)
	{
		return x < y ? x : y;
	}

	template<typename T>
	constexpr T PerlinNoise(T value);

	template<typename T>
	constexpr T Pow(T value, int p)
	{
		T result = 1;
		for (size_t i = 0; i < p; i++)
		{

		}
	}



	template<typename T>
	constexpr T Sin(T value);

	template<typename T>
	constexpr T SmoothDamp(T value);

	template<typename T>
	constexpr T SmoothStep(T value);

	template<typename T>
	constexpr T Sqrt(T value);

	template<typename T>
	constexpr T Tan(T value);


}