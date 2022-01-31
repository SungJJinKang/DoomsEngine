#pragma once

#include <Core.h>

#include <vector>
#include <unordered_map>
#include <../Helper/Simple_SingleTon/Singleton.h>
#include "UniformBufferObject.h"


#include "UniformBufferObjectManager.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class UniformBufferObjectUpdater;
		class DOOM_API D_CLASS UniformBufferObjectManager : public DObject, public ISingleton<UniformBufferObjectManager>
		{
			GENERATE_BODY()
			
		private:


			/// <summary>
			/// index is same with binding point
			/// </summary>
			//D_PROPERTY()

			D_PROPERTY()
			std::unordered_map<std::string, UniformBufferObject*> mUniformBufferObjects;

			D_PROPERTY()
			std::vector<UniformBufferObjectUpdater*> mUniformBufferObjectTempBufferUpdaters;
			
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
			
			UniformBufferObject* GetUniformBufferObject(const char* const uniformBufferName);
			UniformBufferObject* GetOrGenerateUniformBufferObjectIfNotExist
			(
				const std::string& uniformBufferName,
				const UINT64 uniformBufferSize,
				const UINT32 bindingPoint,
				const void* const initialData,
				const std::vector<asset::shaderReflectionDataParser::UniformBufferMember>* const uboMembers
			);
			
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

