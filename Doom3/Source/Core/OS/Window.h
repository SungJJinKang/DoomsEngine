#pragma once
#include "OS.h"

// DWORLD unsigned long

namespace doom
{
	class Window : public OS
	{
	public:

		virtual unsigned long long _GetTickCount() final;

		void _Sleep(unsigned long milliseconds) override;

	};
}