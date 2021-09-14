#pragma once
#include <initializer_list>
#include <vector>
#include <memory>
#include <tuple>
#include <functional>

#include "../../Game/IGameFlow.h"
#include "UniformBufferObjectManager.h"

namespace doom
{
	namespace graphics
	{
		class UniformBufferObjectManager;

		/// <summary>
		/// interface for Sending Data to Temp container of Uniform Buffer Object
		/// Inherit this class for Update Uniform Buffer Object's TempBuffer
		/// </summary>
		class UniformBufferObjectUpdater // Don't put IFlow
		{

		private:

		protected:
					
			
		public:

			bool bmUpdateWhenManagerUpdate;

			UniformBufferObjectUpdater();
			UniformBufferObjectUpdater(const bool _updateWhenManagerUpdate);
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