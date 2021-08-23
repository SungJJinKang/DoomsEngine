#pragma once
#include <cassert>

/// <summary>
/// Why need this?
/// Read this : https://sungjjinkang.github.io/c++/2021/02/20/problemWhenUseMoveContrucotrCompilerMade.html
/// </summary>
template <typename T>
class ZeroResetMoveContainer
{
private:
	T mData;
public:
	constexpr ZeroResetMoveContainer() : mData{ NULL }
	{}

	constexpr ZeroResetMoveContainer(const ZeroResetMoveContainer& bufferID)
	{
		mData = bufferID.mData;
	}
	constexpr ZeroResetMoveContainer(ZeroResetMoveContainer&& bufferID) noexcept
	{
		mData = std::move(bufferID.mData);
		bufferID.mData = NULL;
	}

	constexpr ZeroResetMoveContainer& operator=(const ZeroResetMoveContainer& bufferID)
	{
		mData = bufferID.mData;
		return *this;
	}
	constexpr ZeroResetMoveContainer& operator=(ZeroResetMoveContainer&& bufferID) noexcept
	{
		mData = std::move(bufferID.mData);
		bufferID.mData = NULL;
		return *this;
	}

	constexpr ZeroResetMoveContainer(T data) : mData{ data }
	{}

	constexpr void operator=(const T& data)
	{
		mData = data;
	}
	constexpr void operator=(T&& data) noexcept
	{
		mData = std::move(data);
		data = NULL;
	}

	constexpr operator T()
	{
		return mData;
	}
	constexpr operator T& () const
	{
		return mData;
	}

	constexpr T* operator& ()
	{
		return &(mData);
	}
	constexpr const T* operator& () const
	{
		return &(mData);
	}

	constexpr T Get()
	{
		return mData;
	}
	constexpr const T Get() const
	{
		return mData;
	}
};
using BufferID = typename ZeroResetMoveContainer<unsigned int>;

