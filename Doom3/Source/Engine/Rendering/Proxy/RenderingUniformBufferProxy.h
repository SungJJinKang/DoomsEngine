#pragma once

#include <Core.h>

#include <memory>

#include "RenderingProxy.h"
#include "Graphics/GraphicsAPI/GraphicsAPI.h"
#include "Rendering/Buffer/BufferID.h"
#include "Asset/Utility/ShaderAsset/shaderReflectionDataParser.h"

namespace dooms
{
	namespace graphics
	{
		class RenderingUniformBufferProxy : public RenderingProxy
		{

		public:

			virtual ~RenderingUniformBufferProxy();

			struct FRenderingUniformBufferProxyInitializer
			{
				std::string UniformBufferName;
				UINT64 UniformBufferSize;
				UINT32 DefaultBindingPoint;
				std::unordered_map<std::string, asset::shaderReflectionDataParser::UniformBufferMember> UniformVariableInfos;
			};

			void InitUniformBufferProxy(FRenderingUniformBufferProxyInitializer& Initializer);

			void DeleteBuffers();
			
			void BindBuffer(const UINT32 BindingPoint, const GraphicsAPI::eGraphicsPipeLineStage TargetPipeLineStage) const noexcept;
			void UnBindBuffer(const UINT32 BindingPoint, const GraphicsAPI::eGraphicsPipeLineStage TargetPipeLineStage) const noexcept;

			/// <summary>
			/// Store data in temporary buffer
			/// data isn't send to gpu instantly, it is stored in temp buffer
			/// if you want buffer data ( send data to gpu ), call BufferData function
			/// </summary>
			/// <param name="SourceData">souce data address</param>
			/// <param name="sizeInByte">data size in byte</param>
			/// <param name="OffsetInUniformBlock"></param>
			void UpdateLocalBuffer
			(
				const void* const SourceData,
				const UINT64 OffsetInUniformBlock,
				const UINT64 SizeOfSourceData
			);

			/// <summary>
			/// Send data in mUniformBufferData to gpu 
			/// </summary>
			/// <returns></returns>
			void UpdateLocalBufferToGPU() noexcept;
			UINT64 GetUniformVariableOffset(const char* const TargetVariableName) const;

			void UpdateDataToGPU(const void* const SourceData, const UINT64 OffsetInUniformBlock, const UINT64 SizeOfSourceData) noexcept;
			void UpdateDataToGPU(const void* const SourceData, const char* const TargetVariableName, const UINT64 SizeOfSourceData) noexcept;
			bool IsBufferGenerated() const;

			const std::string& GetUniformBufferName() const;
			UINT64 GetUniformBufferSize() const;
			UINT32 GetDefaultBindingPoint() const;

			void GenerateUniformBufferObject(const void* const InitialData = nullptr);

		private:

			inline static const UINT32 MAX_UNIFORM_BUFFER_SLOT_COUNT = 14;
			static UINT64 BOUND_UNIFORM_BUFFER_ID[GRAPHICS_PIPELINE_STAGE_COUNT][MAX_UNIFORM_BUFFER_SLOT_COUNT];

			std::string UniformBufferName;
			BufferID UniformBufferObject{};
			UINT64 UniformBufferSize;
			UINT32 DefaultBindingPoint;
			std::unique_ptr<UINT8[]> UniformBufferLocalBuffer;
			
			std::unordered_map<std::string, dooms::asset::shaderReflectionDataParser::UniformBufferMember> UniformVariableInfos;

			bool bIsLocalBufferDirty;

			void UpdateLocalBuffer_Internal
			(
				const void* sourceData,
				const UINT64 offsetInUniformBlock,
				const UINT64 sizeOfSourceData
			);
			void UpdateDataToGPU_Internal(const void* sourceData, const UINT64 offsetInUniformBlock, const UINT64 sizeOfSourceData) noexcept;
			
		};
	}
}

