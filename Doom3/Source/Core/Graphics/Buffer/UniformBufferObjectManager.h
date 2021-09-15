#pragma once

#include <array>
#include <string>
#include <memory>
#include <utility>

#include "../Graphics_Core.h"
#include "UniformBufferObject.h"
#include "../../Game/IGameFlow.h"
#include "UniformBlockOffsetInfo.h"

namespace doom
{
	namespace graphics
	{
		class UniformBufferObjectUpdater;
		class UniformBufferObjectManager : public IGameFlow, public ISingleton<UniformBufferObjectManager>
		{
			friend class Graphics_Server;
			friend class Material;

		private:


			/// <summary>
			/// index is same with binding point
			/// </summary>
			std::array<UniformBufferObject, MAX_UNIFORM_BLOCK_BINDING_POINT> mUniformBufferObjects{};
			std::vector<UniformBufferObjectUpdater*> mUniformBufferObjectTempBufferUpdaters{};
			
		

		protected:

			virtual void Init() final;
			/// <summary>
			/// Update uniform Buffer Object's TempBuffer -> Buffer Data to gpu
			/// </summary>
			virtual void Update() final;
			virtual void OnEndOfFrame() final;
			
		
		public:

			UniformBufferObjectManager();

			/// <summary>
			/// Send Uniform Buffer Object to gpu ( Buffer Data )
			/// </summary>
			void BufferDateOfUniformBufferObjects();

			/// <summary>
			/// return Uniform Buffer Object class
			/// if uniform buffer object isn't initialized, Initialize it
			/// </summary>
			UniformBufferObject& GetOrGenerateUniformBufferObject(unsigned int bindingPoint, unsigned int uniformBlockSize);
			UniformBufferObject& GetUniformBufferObject(unsigned int bindingPoint);

			/// <summary>
			/// Call UpdateUniformBufferObject of UBO Temp Buffer Updaters 
			/// </summary>
			void UpdateUniformBufferObjects();

			/// <summary>
			/// Push Instance inheritings UniformBufferObjectUpdater to container
			/// </summary>
			/// <param name="update_ptr"></param>
			void PushUniformBufferObjectTempBufferUpdater(UniformBufferObjectUpdater* update_ptr);
			/// <summary>
			/// Remove Instance inheritings UniformBufferObjectUpdater from container
			/// </summary>
			/// <param name="update_ptr"></param>
			void EraseUniformBufferObjectTempBufferUpdater(UniformBufferObjectUpdater* update_ptr);


		};
	}
}

