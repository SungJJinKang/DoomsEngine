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
		class UniformBufferObjectTempBufferUpdater // Don't put IFlow
		{

		private:

		protected:
					
			
		public:

			bool bmUpdateWhenManagerUpdate;

			UniformBufferObjectTempBufferUpdater();
			UniformBufferObjectTempBufferUpdater(const bool _updateWhenManagerUpdate);
			virtual ~UniformBufferObjectTempBufferUpdater();

			/// <summary>
			/// Implement This Function!!!!
			/// Update Uniform Buffer Object's TempBuffer
			/// This Function will be called once before UpdateUniformBufferObject in a frame
			/// 
			/// HOW TO IMPLEMNET THIS PURE FUNCTION : 
			/// 
			/// uboManager.StoreDataAtTempBufferOfBindingPoint(0, ~~~);
			/// 
			/// </summary>
			virtual void UpdateUniformBufferObjectTempBuffer() = 0; // Never remove = 0, This function must be implemented


		};

		
	}
}