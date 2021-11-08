#pragma once

#include "../Core.h"
#include "SharedSceneSetting.h"
#include "IWorldIndependent.h"

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

		DOBJECT_CLASS_BODY(SharedScene, dooms::eDOBJECT_ClassFlags::NonCopyable);
		DOBJECT_CLASS_BASE_CHAIN(DObject)

	private:
		SharedSceneSetting mSharedWorldSetting{};

	public:

	};
}