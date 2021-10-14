#pragma once

#include <Core.h>

#define INVALID_BUFFER_ID (UINT32)0

/// <summary>
/// Why need this?
/// Read this : https://sungjjinkang.github.io/c++/2021/02/20/problemWhenUseMoveContrucotrCompilerMade.html
/// </summary>
class BufferID
{

private:

	UINT32 mID;

public:

	FORCE_INLINE BufferID() : mID{ 0 }
	{}

	FORCE_INLINE BufferID(const BufferID& bufferID)
	{
		mID = bufferID.mID;
	}
	FORCE_INLINE BufferID(BufferID&& bufferID) noexcept
	{
		mID = bufferID.mID;
		bufferID.mID = 0;
	}

	FORCE_INLINE BufferID& operator=(const BufferID& bufferID)
	{
		mID = bufferID.mID;
		return *this;
	}
	FORCE_INLINE BufferID& operator=(BufferID&& bufferID) noexcept
	{
		mID = bufferID.mID;
		bufferID.mID = NULL;
		return *this;
	}

	FORCE_INLINE BufferID(UINT32 data) : mID{ data }
	{}

	FORCE_INLINE void operator=(const UINT32& data)
	{
		mID = data;
	}
	FORCE_INLINE void operator=(UINT32&& data) noexcept
	{
		mID = data;
		data = NULL;
	}

	FORCE_INLINE operator UINT32 () const
	{
		return mID;
	}

	FORCE_INLINE UINT32* operator& ()
	{
		return &(mID);
	}
	FORCE_INLINE const UINT32* operator& () const
	{
		return &(mID);
	}

	FORCE_INLINE UINT32 Get() const
	{
		return mID;
	}
};

