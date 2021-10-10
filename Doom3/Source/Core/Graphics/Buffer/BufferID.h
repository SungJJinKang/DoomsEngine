#pragma once

/// <summary>
/// Why need this?
/// Read this : https://sungjjinkang.github.io/c++/2021/02/20/problemWhenUseMoveContrucotrCompilerMade.html
/// </summary>
class BufferID
{

private:
	unsigned int mData;

public:
	BufferID() : mData{ NULL }
	{}

	BufferID(const BufferID& bufferID)
	{
		mData = bufferID.mData;
	}
	BufferID(BufferID&& bufferID) noexcept
	{
		mData = bufferID.mData;
		bufferID.mData = NULL;
	}

	BufferID& operator=(const BufferID& bufferID)
	{
		mData = bufferID.mData;
		return *this;
	}
	BufferID& operator=(BufferID&& bufferID) noexcept
	{
		mData = bufferID.mData;
		bufferID.mData = NULL;
		return *this;
	}

	BufferID(unsigned int data) : mData{ data }
	{}

	void operator=(const unsigned int& data)
	{
		mData = data;
	}
	void operator=(unsigned int&& data) noexcept
	{
		mData = data;
		data = NULL;
	}

	operator unsigned int () const
	{
		return mData;
	}

	unsigned int* operator& ()
	{
		return &(mData);
	}
	const unsigned int* operator& () const
	{
		return &(mData);
	}

	unsigned int Get() const
	{
		return mData;
	}
};

