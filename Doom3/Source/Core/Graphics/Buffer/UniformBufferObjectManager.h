#pragma once

#include <array>
#include <string>

#include "../Graphics_Core.h"
#include "UniformBufferObject.h"
#include "../../Game/IGameFlow.h"
#include "../../../Helper/Singleton.h"

namespace doom
{
	namespace graphics
	{
		class UniformBufferObjectManager : public IGameFlow, public ISingleton<UniformBufferObjectManager>
		{
			friend class Graphics;
			friend class Material;
			friend class UniformBufferObjectTempBufferUpdater;
		private:


			/// <summary>
			/// index is same with binding point
			/// </summary>
			std::array<UniformBufferObject, MAX_UNIFORM_BLOCK_BINDING_POINT> mUniformBufferObjects{};

		protected:

			virtual void Init() final;
			void UpdateUniformBufferObjectTempBuffer();
			virtual void Update() final;
			/// <summary>
			/// return Uniform Buffer Object class
			/// if uniform buffer object isn't initialized, Initialize it
			/// </summary>
			UniformBufferObject& GetOrAssignUniformBufferObject(unsigned int bindingPoint, unsigned int uniformBlockSize);
			UniformBufferObject& GetUniformBufferObject(unsigned int bindingPoint);
		
		public:
			
		};
	}
}

