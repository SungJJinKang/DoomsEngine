#pragma once
#include "Light.h"

namespace doom
{
	class DirectionalLight : public Light
	{

	private:

		DirectionalLight(const DirectionalLight&) = delete;
		DirectionalLight(DirectionalLight&&) noexcept = delete;
		DirectionalLight& operator=(const DirectionalLight&) = delete;
		DirectionalLight& operator=(DirectionalLight&&) noexcept = delete;

	protected:

	public:
	};
}
