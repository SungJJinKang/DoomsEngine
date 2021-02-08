#pragma once

#include "../Core.h"
#include "SharedWorldSetting.h"
#include "IWorldIndependent.h"

namespace doom
{
	/// <summary>
	/// World Class shared by all world
	/// even if a world is destroyed, this class object never be destroyed
	/// 
	/// This class contain data used by All World
	/// 
	/// </summary>
	class SharedWorld : public ISingleton<SharedWorld>, public IWorldIndependent
	{

	private:
		SharedWorldSetting mSharedWorldSetting{};

	public:

	};
}