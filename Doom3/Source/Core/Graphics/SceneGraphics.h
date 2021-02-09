#pragma once
#include "../Game/GameFlow.h"
#include "../../Helper/Singleton.h"
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
		class SceneGraphics : public GameFlow, public ISingleton<SceneGraphics>
		{
			friend class GameCore;
			friend class UniformBufferObjectManager;
		private:

		public:

			UniformBufferObjectManager mUniformBufferObjectManager{};
		protected:
			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;
		};

	}
}

