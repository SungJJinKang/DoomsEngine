#pragma once
#include <vector>
#include <EasyDirtyChecker/DirtySender.h>
#include <EasyDirtyChecker/DirtyReceiver.h>
namespace doom
{
	/// <summary>
	/// Check Data is dirty at this frame
	/// 
	/// WHY USE PREVIOUS FRAME :
	/// 
	/// In game flow if you set dirty at late of current frame, object at early of current frame can't know whether is dirty at current frame
	/// So We Check previous frame's dirty, then Every objects can know data is dirty at current frame
	/// </summary>
	class FrameDirtyChecker
	{

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
		[[nodiscard]] constexpr bool GetIsDirtyAtPreviousFrame() noexcept
		{
			return bmIsDirtyAtPreviousFrame;
		}


	};

}