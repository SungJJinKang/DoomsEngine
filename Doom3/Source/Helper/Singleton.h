#pragma once
#include "../Core/Core.h"
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
		D_ASSERT(!Singleton<T>::SingletonInstance);

		Singleton<T>::SingletonInstance = static_cast<T*>(this);
	}

	~Singleton()
	{
		Singleton<T>::SingletonInstance = nullptr;
	}

public:

	static T& Instance()
	{
		D_ASSERT(Singleton<T>::SingletonInstance);
		return *(Singleton<T>::SingletonInstance);
	}

};

template <typename T>
T* Singleton<T>::SingletonInstance{};