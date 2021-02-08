#pragma once
#include "../Game/IGameFlow.h"
#include "../../Helper/Singleton.h"
#include "Buffer/UniformBufferObjectManager.h"
namespace doom
{
	class GameCore;
	namespace graphics
	{
		/// <summary>
		/// World Dependent Graphics Object
		/// if world is destroyed, this object will be destroyed also
		/// This class will be included at World instance
		/// </summary>
		class GraphicsInWorld : public IGameFlow, public ISingleton<GraphicsInWorld>
		{
			friend class GameCore;
			friend class UniformBufferObjectManager;
		private:

		public:

			UniformBufferObjectManager mUniformBufferObjectManager{};
		protected:
			virtual void Init() final;


			virtual void Update() final;

		};

	}
}

