#pragma once

#include <Core.h>

#include "UniformBufferObjectUpdater.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class UniformBufferObjectManager;

		/// <summary>
		/// interface for Sending Data to Temp container of Uniform Buffer Object
		/// Inherit this class for Update Uniform Buffer Object's TempBuffer
		/// </summary>
		class DOOM_API D_CLASS UniformBufferObjectUpdater // Don't put DObject here, Because Light Component should inherit this class, But it already inherit DObject through Component Class
		{
			GENERATE_BODY()
		private:

		protected:
					
			
		public:

			bool bmUpdateWhenManagerUpdate;

			UniformBufferObjectUpdater();
			UniformBufferObjectUpdater(const bool _updateWhenManagerUpdate);

			UniformBufferObjectUpdater(const UniformBufferObjectUpdater& updater);
			UniformBufferObjectUpdater(UniformBufferObjectUpdater&& updater) noexcept = delete;
			UniformBufferObjectUpdater& operator=(const UniformBufferObjectUpdater& updater);
			UniformBufferObjectUpdater& operator=(UniformBufferObjectUpdater&& updater) noexcept = delete;

			virtual ~UniformBufferObjectUpdater();

			/// <summary>
			/// Implement This Function!!!!
			/// Update Uniform Buffer Object's TempBuffer
			/// This Function will be called once before UpdateUniformBufferObject in a frame
			/// 
			/// HOW TO IMPLEMNET THIS PURE FUNCTION : 
			/// 
			/// uboManager.GetUniformBufferObject(GLOBAL_UNIFORM_BLOCK_BINDING_POINT).StoreDataAtTempBuffer(0, ~~~);
			/// 
			/// </summary>
			virtual void UpdateUniformBufferObject() = 0; // Never remove = 0, This function must be implemented


		};

		
	}
}