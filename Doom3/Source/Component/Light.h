#pragma once
#include "Core/CoreComponent.h"

namespace doom
{
	class Light : public CoreComponent
	{
	private:

		Light(const Light&) = delete;
		Light(Light&&) noexcept = delete;
		Light& operator=(const Light&) = delete;
		Light& operator=(Light&&) noexcept = delete;

	protected:
		Light() {}
		virtual ~Light() {}
	};
}


