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
		this->mData = bufferID.mData;
	}
	constexpr ZeroResetMoveContainer(ZeroResetMoveContainer&& bufferID) noexcept
	{
		this->mData = std::move(bufferID.mData);
		bufferID.mData = NULL;
	}

	constexpr ZeroResetMoveContainer& operator=(const ZeroResetMoveContainer& bufferID)
	{
		this->mData = bufferID.mData;
		return *this;
	}
	constexpr ZeroResetMoveContainer& operator=(ZeroResetMoveContainer&& bufferID) noexcept
	{
		this->mData = std::move(bufferID.mData);
		bufferID.mData = NULL;
		return *this;
	}

	constexpr ZeroResetMoveContainer(T data) : mData{ data }
	{}

	constexpr void operator=(const T& data)
	{
		this->mData = data;
	}
	constexpr void operator=(T&& data) noexcept
	{
		this->mData = std::move(data);
		data = NULL;
	}

	constexpr operator T()
	{
		return this->mData;
	}
	constexpr operator T& () const
	{
		return this->mData;
	}

	constexpr T* operator& ()
	{
		return &(this->mData);
	}
	constexpr const T* operator& () const
	{
		return &(this->mData);
	}

	constexpr T Get()
	{
		return this->mData;
	}
	constexpr const T Get() const
	{
		return this->mData;
	}
};
using BufferID = typename ZeroResetMoveContainer<unsigned int>;

