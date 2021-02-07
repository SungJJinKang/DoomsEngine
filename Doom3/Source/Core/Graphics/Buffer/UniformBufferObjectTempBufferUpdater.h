#pragma once
#include <initializer_list>
#include <vector>
#include <memory>
#include <tuple>
#include <functional>

#include "../../Game/IGameFlow.h"

namespace doom
{
	namespace graphics
	{
		/// <summary>
		/// interface for Sending Data to Temp container of Uniform Buffer Object
		/// Inherit this class for Update Uniform Buffer Object's TempBuffer
		/// </summary>
		class UniformBufferObjectTempBufferUpdater : public IGameFlow
		{
		private:
			static inline std::vector<std::unique_ptr<UniformBufferObjectTempBufferUpdater>> mUniformBufferObjectTempBufferUpdaters{};

		protected:
			
			void Init() override;

			/// <summary>
			/// Update Uniform Buffer Object's TempBuffer
			/// This Function Call UpdateUniformBufferObjectTempBuffer function
			/// </summary>
			void Update() override;

			/// <summary>
			/// Implement This Function!!!!
			/// Update Uniform Buffer Object's TempBuffer
			/// 
			/// like this : 
			/// UniformBufferObjectManager::GetSingleton()->GetUniformBufferObject(x).StoreDataAtTempBuffer(~~~~~)
			/// </summary>
			virtual void UpdateUniformBufferObjectTempBuffer() = 0; // Never remove = 0, This function must be implemented

		public:

			UniformBufferObjectTempBufferUpdater();
			virtual ~UniformBufferObjectTempBufferUpdater();

		};

		
	}
}