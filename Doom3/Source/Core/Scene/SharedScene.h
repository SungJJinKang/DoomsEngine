#pragma once

#include "../Core.h"
#include "SharedSceneSetting.h"
#include "IWorldIndependent.h"

#include "SharedScene.reflection.h"
namespace dooms
{
	/// <summary>
	/// Scene Class shared by all world
	/// even if a scene is destroyed, this class object never be destroyed
	/// 
	/// This class contain data, object used by All Scene
	/// 
	/// </summary>
	class DOOM_API D_CLASS SharedScene : public DObject, public ISingleton<SharedScene>, public I_IndependentFromScene
	{

		GENERATE_BODY()
		

	private:
		SharedSceneSetting mSharedWorldSetting{};

	public:

	};
}