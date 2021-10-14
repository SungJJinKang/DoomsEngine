#pragma once

/// <summary>
/// Why need this?
/// Read this : https://sungjjinkang.github.io/c++/2021/02/20/problemWhenUseMoveContrucotrCompilerMade.html
/// </summary>
class BufferID
{

private:
	UINT32 mData;

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

	BufferID(UINT32 data) : mData{ data }
	{}

	void operator=(const UINT32& data)
	{
		mData = data;
	}
	void operator=(UINT32&& data) noexcept
	{
		mData = data;
		data = NULL;
	}

	operator UINT32 () const
	{
		return mData;
	}

	UINT32* operator& ()
	{
		return &(mData);
	}
	const UINT32* operator& () const
	{
		return &(mData);
	}

	UINT32 Get() const
	{
		return mData;
	}
};

