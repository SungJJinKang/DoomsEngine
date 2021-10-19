#pragma once

#include "../Core.h"
#include "SharedSceneSetting.h"
#include "IWorldIndependent.h"

namespace doom
{
	/// <summary>
	/// Scene Class shared by all world
	/// even if a scene is destroyed, this class object never be destroyed
	/// 
	/// This class contain data, object used by All Scene
	/// 
	/// </summary>
	class DOOM_API SharedScene : public DObject, public ISingleton<SharedScene>, public I_IndependentFromScene
	{

		DOBJECT_CLASS_BODY(SharedScene, doom::eDOBJECT_ClassFlags::NonCopyable);

	private:
		SharedSceneSetting mSharedWorldSetting{};

	public:

	};
}