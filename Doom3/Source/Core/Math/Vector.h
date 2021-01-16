#pragma once

namespace Math
{
	template <size_t ComponentCount, typename T>
	class Vector
	{
	private:
		T values[ComponentCount];

	public:
		constexpr explicit Vector(T x, T y, T z)
		{

		}

		constexpr Vector(const Vector& vector)
		{

		}
		constexpr Vector(Vector&& vector) noexcept
		{

		}

		constexpr Vector& operator=(const Vector& vector)
		{

		}
		constexpr Vector& operator=(Vector&& vector) noexcept
		{

		}

		constexpr Vector& oprator+(const Vector & vector)
		{

		}

		constexpr Vector& oprator=(const Vector & vector)
		{

		}
		constexpr Vector& oprator*(const Vector & vector)
		{

		}
		constexpr Vector& oprator/(const Vector& vector)
		{

		}


	};

	template<typename T>
	using Vector1 = typename Vector<1, T>;

	template<typename T>
	using Vector2 = typename Vector<2, T>;

	template<typename T>
	using Vector3 = typename Vector<3, T>;

	template<typename T>
	using Vector4 = typename Vector<4, T>;
}