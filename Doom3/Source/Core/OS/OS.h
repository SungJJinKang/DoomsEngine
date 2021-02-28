#pragma once

#include "../Core.h"

namespace doom
{
	/// <summary>
	/// refrain from using os call
	/// use portable library
	/// </summary>
	class OS : public ISingleton<OS>
	{
	public:

		//why put _ -> To prevent definition shadowing


		/// <summary>
		/// 
		/// </summary>
		/// <returns>millisecond</returns>
		virtual unsigned long long _GetTickCount() = 0;
		/// <summary>
		/// sleep for milliseconds
		/// </summary>
		/// <param name="milliseconds">sleep time</param>
		virtual void _Sleep(unsigned long milliseconds) = 0;
	};
}