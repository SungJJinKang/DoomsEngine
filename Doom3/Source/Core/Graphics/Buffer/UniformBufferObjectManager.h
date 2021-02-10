#pragma once

#include <array>
#include <string>
#include <memory>
#include <utility>

#include "../Graphics_Core.h"
#include "UniformBufferObject.h"
#include "../../Game/GameFlow.h"
#include "../../../Helper/Singleton.h"
#include "UniformBlockOffsetInfo.h"

namespace doom
{
	namespace graphics
	{
		class UniformBufferObjectTempBufferUpdater;
		class UniformBufferObjectManager : public GameFlow, public ISingleton<UniformBufferObjectManager>
		{
			friend class Graphics_Server;
			friend class Material;
			friend class UniformBufferObjectTempBufferUpdater;
			friend class SceneGraphics;

		private:


			/// <summary>
			/// index is same with binding point
			/// </summary>
			std::array<UniformBufferObject, MAX_UNIFORM_BLOCK_BINDING_POINT> mUniformBufferObjects{};
			std::vector<UniformBufferObjectTempBufferUpdater*> mUniformBufferObjectTempBufferUpdaters{};
			
			/// <summary>
			/// Call UpdateUniformBufferObjectTempBuffer of UBO Temp Buffer Updaters 
			/// </summary>
			void UpdateUniformBufferObjectTempBufferUpdaters();

			/// <summary>
			/// Push Instance inheritings UniformBufferObjectTempBufferUpdater to container
			/// </summary>
			/// <param name="update_ptr"></param>
			void PushUniformBufferObjectTempBufferUpdater(UniformBufferObjectTempBufferUpdater* update_ptr);
			/// <summary>
			/// Remove Instance inheritings UniformBufferObjectTempBufferUpdater from container
			/// </summary>
			/// <param name="update_ptr"></param>
			void EraseUniformBufferObjectTempBufferUpdater(UniformBufferObjectTempBufferUpdater* update_ptr);

		protected:

			virtual void Init() final;
			/// <summary>
			/// Update uniform Buffer Object's TempBuffer -> Buffer Data to gpu
			/// </summary>
			virtual void Update() final;
			virtual void OnEndOfFrame() final;
			/// <summary>
			/// Send Uniform Buffer Object to gpu ( Buffer Data )
			/// </summary>
			void BufferDateOfUniformBufferObjects();			

			/// <summary>
			/// return Uniform Buffer Object class
			/// if uniform buffer object isn't initialized, Initialize it
			/// </summary>
			UniformBufferObject& GetOrAssignUniformBufferObject(unsigned int bindingPoint, unsigned int uniformBlockSize);
			UniformBufferObject& GetUniformBufferObject(unsigned int bindingPoint);
		public:
			void StoreDataAtTempBufferOfBindingPoint(unsigned int bindingPoint, const void* sourceData, unsigned int sizeInByteOfSourceData, unsigned int offsetInUniformBlock);

		};
	}
}

