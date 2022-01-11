#pragma once

#include <Core.h>

#define INVALID_BUFFER_ID (UINT32)-1

/// <summary>
/// Why need this?
/// Read this : https://sungjjinkang.github.io/c++/2021/02/20/problemWhenUseMoveContrucotrCompilerMade.html
/// </summary>
class D_CLASS BufferID
{

private:

	D_PROPERTY()
	UINT32 mID;

public:

	FORCE_INLINE BufferID() : mID{ INVALID_BUFFER_ID }
	{}

	FORCE_INLINE BufferID(const BufferID& bufferID)
	{
		mID = bufferID.mID;
	}
	FORCE_INLINE BufferID(BufferID&& bufferID) noexcept
	{
		mID = bufferID.mID;
		bufferID.mID = INVALID_BUFFER_ID;
	}

	FORCE_INLINE BufferID& operator=(const BufferID& bufferID)
	{
		mID = bufferID.mID;
		return *this;
	}
	FORCE_INLINE BufferID& operator=(BufferID&& bufferID) noexcept
	{
		mID = bufferID.mID;
		bufferID.mID = INVALID_BUFFER_ID;
		return *this;
	}

	FORCE_INLINE BufferID(UINT32 data) : mID{ data }
	{}

	FORCE_INLINE void operator=(const UINT32 data)
	{
		D_ASSERT_LOG(data != 0, "Dont set 0 to BufferID. Use BufferID::Reset() function.");
		mID = data;
	}

	FORCE_INLINE UINT32* operator& ()
	{
		return &(mID);
	}
	FORCE_INLINE const UINT32* operator& () const
	{
		return &(mID);
	}

	FORCE_INLINE UINT32 GetBufferID() const
	{
		return mID;
	}

	FORCE_INLINE bool IsValid() const
	{
		return mID != INVALID_BUFFER_ID;
	}

	FORCE_INLINE void Reset()
	{
		mID = INVALID_BUFFER_ID;
	}

	FORCE_INLINE operator bool() const
	{
		return IsValid();
	}

	FORCE_INLINE operator UINT32 () const
	{
		return mID;
	}

	FORCE_INLINE UINT32* data()
	{
		return &mID;
	}

	FORCE_INLINE const UINT32* data() const
	{
		return &mID;
	}
};

