#pragma once
#include "../Core/CoreComponent/CoreComponent.h"
#include "../Core/Math/LightMath_Cpp/Matrix4x4.h"
#include "../Helper/Singleton.h"


namespace doom
{
	class Camera : public CoreComponent, ISingleton<Camera>
	{
	private:
		
	public:
	
		math::Matrix4x4 GetProjectionMatrix();

		Camera* GetMainCamera();
	};
}
