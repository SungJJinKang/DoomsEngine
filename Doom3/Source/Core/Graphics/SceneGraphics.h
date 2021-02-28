#pragma once
#include "../Core.h"
#include "../Game/IGameFlow.h"
#include "Buffer/UniformBufferObjectManager.h"
namespace doom
{
	class GameCore;
	namespace graphics
	{
		/// <summary>
		/// Scene Dependent Graphics Object
		/// if world is destroyed, this object will be destroyed also
		/// This class will be included at Scene instance
		/// </summary>
		class SceneGraphics : public ISingleton<SceneGraphics> // public GameFlow, Don't Put GameFlow
		{
			friend class GameCore;
			friend class UniformBufferObjectManager;
		private:

		public:

			UniformBufferObjectManager mUniformBufferObjectManager{};
		protected:
		};

	}
}

