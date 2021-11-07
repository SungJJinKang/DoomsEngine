#pragma once

#include <array>

#include "../Graphics_Core.h"
#include "UniformBufferObject.h"
#include "../../Game/IGameFlow.h"

namespace dooms
{
	namespace graphics
	{
		class UniformBufferObjectUpdater;
		class UniformBufferObjectManager : public DObject, public ISingleton<UniformBufferObjectManager>
		{
			DOBJECT_CLASS_BODY(UniformBufferObjectManager, dooms::eDOBJECT_ClassFlags::NonCopyable);
			DOBJECT_CLASS_BASE_CHAIN(DObject)
		private:


			/// <summary>
			/// index is same with binding point
			/// </summary>
			std::array<UniformBufferObject, MAX_UNIFORM_BLOCK_BINDING_POINT> mUniformBufferObjects{};
			std::vector<UniformBufferObjectUpdater*> mUniformBufferObjectTempBufferUpdaters{};
			
		

		public:

			
			
		
			UniformBufferObjectManager();

			/// <summary>
			/// Send Uniform Buffer Object to gpu ( Buffer Data )
			/// </summary>
			void BufferDateOfUniformBufferObjects();

			/// <summary>
			/// Update uniform Buffer Object's TempBuffer -> Buffer Data to gpu
			/// </summary>
			void UpdateUniformObjects();

			/// <summary>
			/// return Uniform Buffer Object class
			/// if uniform buffer object isn't initialized, Initialize it
			/// </summary>
			UniformBufferObject& GetOrGenerateUniformBufferObject(UINT32 bindingPoint, UINT32 uniformBlockSize);
			UniformBufferObject& GetUniformBufferObject(UINT32 bindingPoint);

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

