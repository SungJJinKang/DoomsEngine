#pragma once
#include <type_traits>

template <typename T>
class Singleton
{
	static_assert(!std::is_pointer_v<T>);
private:
	static inline T* Instance{nullptr};
public:

	T& GetInstance()
	{
		if (Instance == nullptr)
		{
			
		}

	}

	

	inline Singleton()
	{

	}

	inline ~Singleton()
	{

	}
};