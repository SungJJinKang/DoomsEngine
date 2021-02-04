#pragma once
#include "Component.h"
#include "../Core/Math/LightMath_Cpp/Matrix4x4.h"

namespace doom
{
	class Camera : public Component
	{
	private:
		
	public:
	
		math::Matrix4x4 GetProjectionMatrix();
	};
}
