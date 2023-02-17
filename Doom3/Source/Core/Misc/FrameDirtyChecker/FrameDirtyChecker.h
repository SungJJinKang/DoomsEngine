#pragma once

#include <Core.h>
#include <DirtyChecker/DirtySender.h>

#include "FrameDirtyChecker.reflection.h"
namespace dooms
{
	/// <summary>
	/// Check Data is dirty at this frame
	/// 
	/// WHY USE PREVIOUS FRAME :
	/// 
	/// In game flow if you set dirty at late of current frame, object at early of current frame can't know whether is dirty at current frame
	/// So We Check previous frame's dirty, then Every objects can know data is dirty at current frame
	/// </summary>
	class DOOM_API D_CLASS FrameDirtyChecker
	{
		GENERATE_BODY()
	private:

		/// <summary>
		/// Check whether become dirty at previous frame
		/// this value is reset at EndOfFrame
		/// 
		/// </summary>
		bool bmIsDirtyAtPreviousFrame{ true };

		bool bmIsDirtyAtThisFrame{ true };

		

	protected:
		
		DirtySender mDirtySender{};
		
		/// <summary>
		/// Use can't set dirty false
		/// </summary>
		inline void SetDirtyTrueAtThisFrame() noexcept
		{
			bmIsDirtyAtThisFrame = true;
			mDirtySender.NotifyDirty();
		}

		/// <summary>
		/// Must call this function at end of frame
		/// </summary>
		constexpr void FrameDirtyChecker_EndOfFrame() noexcept
		{
			bmIsDirtyAtPreviousFrame = bmIsDirtyAtThisFrame; // pass current frame dirty to previous frame dirty
			bmIsDirtyAtThisFrame = false;
		}


	public:

		/// <summary>
		/// WHY USE PREVIOUS FRAME CHECK :
		/// READ FrameDirtyChecker class Description
		/// </summary>
		/// <returns></returns>
		NO_DISCARD constexpr bool GetIsDirtyAtPreviousFrame() noexcept
		{
			return bmIsDirtyAtPreviousFrame;
		}

		FrameDirtyChecker();
		virtual ~FrameDirtyChecker();
	};
	
}
