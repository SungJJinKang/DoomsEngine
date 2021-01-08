#pragma once
#include "../Core/Assert.h"
#include <type_traits>
#include <functional>
template<typename T>
class Singleton
{
	static_assert(!std::is_pointer<T>::value, "Don't try making singleton with pointer type");

private:
	static T* SingletonInstance;

protected:
	
	constexpr Singleton()
	{
		assert(!Singleton<T>::SingletonInstance);

		Singleton<T>::SingletonInstance = static_cast<T*>(this);
	}

	~Singleton()
	{
		Singleton<T>::SingletonInstance = nullptr;
	}

public:

	static T& Instance()
	{
		assert(Singleton<T>::SingletonInstance);
		return *(Singleton<T>::SingletonInstance);
	}

};

template <typename T>
T* Singleton<T>::SingletonInstance{};