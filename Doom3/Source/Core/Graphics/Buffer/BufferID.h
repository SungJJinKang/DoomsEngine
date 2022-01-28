#pragma once

#include <Core.h>

namespace dooms
{
	namespace graphics
	{
		class D_CLASS BufferID
		{
		public:

			inline static const UINT64 INVALID_BUFFER_ID = 0; // Don't change this. In opengl, Only low 4byte is used.

		private:

			
			D_PROPERTY()
			UINT64 mID; // This is used as pointer in directx

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

			FORCE_INLINE BufferID(UINT64 data) : mID{ data }
			{}

			FORCE_INLINE void operator=(const UINT64 data)
			{
				D_ASSERT_LOG(data != 0, "Dont set 0 to BufferID. Use BufferID::Reset() function.");
				mID = data;
			}

			FORCE_INLINE UINT64* operator& ()
			{
				return &(mID);
			}
			FORCE_INLINE const UINT64* operator& () const
			{
				return &(mID);
			}

			FORCE_INLINE UINT64 GetBufferID() const
			{
				return mID;
			}

			FORCE_INLINE UINT64& GetBufferIDRef()
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

			FORCE_INLINE operator UINT64 () const
			{
				return mID;
			}

			FORCE_INLINE UINT64* data()
			{
				return &mID;
			}

			FORCE_INLINE const UINT64* data() const
			{
				return &mID;
			}
		};


	}
}
