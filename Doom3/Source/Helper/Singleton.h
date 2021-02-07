#pragma once
#include <cassert>
#include <type_traits>
#include <functional>

template <typename T>
class ISingleton
{
	static_assert(!std::is_pointer<T>::value, "Don't try making singleton with pointer type");
private:
	static inline T* mSingleTon{ nullptr };

public:
	ISingleton()
	{
		assert(mSingleTon == nullptr);
		mSingleTon = (T*)this;
	}
	virtual ~ISingleton()
	{
		delete mSingleTon;
	}

	static T& GetSingleton()
	{
		assert(mSingleTon != nullptr);
		return *mSingleTon;
	}
};