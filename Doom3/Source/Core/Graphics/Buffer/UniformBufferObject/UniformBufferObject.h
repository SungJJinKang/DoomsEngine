#pragma once

#include "../Buffer.h"

#include <unordered_map>
#include <string>
#include <vector>

#include "../../OverlapBindChecker.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include <Asset/Utility/ShaderAsset/shaderReflectionDataParser.h>

#include "UniformBufferObject.reflection.h"
namespace dooms
{
	namespace graphics
	{
		/// <summary>
		///
		///	OPENGL : Uniform Buffer Object
		/// DirectX : Constant Buffer
		/// reference : https://www.khronos.org/opengl/wiki/Program_Introspection, https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
		/// </summary>
		class DOOM_API D_CLASS UniformBufferObject : public Buffer
		{
			GENERATE_BODY()
			

		private:

			static inline const char GL_UNIFORM_BUFFER_TAG[]{ "GL_UNIFORM_BUFFER" };

			D_PROPERTY()
			BufferID mUniformBufferObject;

			/// <summary>
			/// for buffer data only when data is dirty
			/// </summary>
			D_PROPERTY()
			bool bmIsDirty = true;

			D_PROPERTY()
			std::string mUniformBlockName;

			D_PROPERTY()
			UINT64 mUniformBufferSize;
			
			D_PROPERTY()
			UINT32 mDefaultBindingPoint;
			
			D_PROPERTY()
			std::unique_ptr<UINT8[]> mUniformBufferTempData;

			/**
			 * \brief Key : Uniform Variable Name, Value : Offset
			 */
			std::unordered_map<std::string, asset::shaderReflectionDataParser::UniformBufferMember> mUniformVariableInfos;
			void InitializeUniformVariableOffset(const std::vector<asset::shaderReflectionDataParser::UniformBufferMember>& uboMembers);

			void GenerateUniformBufferObject(const UINT64 uniformBufferSize, const void* const initialData = 0);

						

			void OnSetPendingKill() override;

		public:

			UniformBufferObject();
			UniformBufferObject
			(
				const std::string& uniformBlockName,
				const UINT64 uniformBufferSize,
				const UINT32 defaultBindingPoint, 
				const void* const initialData,
				const std::vector<asset::shaderReflectionDataParser::UniformBufferMember>* const uboMembers
			);
			~UniformBufferObject();

			UniformBufferObject(const UniformBufferObject&) = delete;
			UniformBufferObject(UniformBufferObject&&) noexcept = default;
			UniformBufferObject& operator=(const UniformBufferObject&) = delete;
			UniformBufferObject& operator=(UniformBufferObject&&) noexcept = default;

			bool InitializeUniformBufferObject
			(
				const std::string& uniformBlockName,
				const UINT64 uniformBufferSize,
				const UINT32 defaultBindingPoint,
				const void* const initialData,
				const std::vector<asset::shaderReflectionDataParser::UniformBufferMember>* const uboMembers
			);

			std::string GetUniformBlockName();
			const std::string& GetUniformBlockName() const;

			void DeleteBuffers() final;

			FORCE_INLINE UINT64 GetUniformVariableOffset(const char* const targetVariableName) const
			{
				size_t offset = 0;

				D_ASSERT(IsBufferGenerated() == true);
				auto node = mUniformVariableInfos.find(targetVariableName);

				D_DEBUG_LOG(eLogType::D_ERROR, "Fail to find uniform variable ( %s ) from uniform buffer object ( %s )", targetVariableName, GetUniformBlockName().c_str());
				D_ASSERT(node != mUniformVariableInfos.end());

				if(node != mUniformVariableInfos.end())
				{
					offset = node->second.mOffset;
				}
				return offset;
			}
			
			FORCE_INLINE void BindBuffer(const UINT32 bindingPoint, const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage) const noexcept
			{
				D_ASSERT(mUniformBufferObject.IsValid() == true);
				if (IsBufferGenerated() == true)
				{
					if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(GL_UNIFORM_BUFFER_TAG, mUniformBufferObject))
					{
						GraphicsAPI::BindConstantBuffer(mUniformBufferObject, bindingPoint, targetPipeLineStage);
					}
				}
			}
			
			/// <summary>
			/// Send data in mUniformBufferData to gpu 
			/// </summary>
			/// <returns></returns>
			void UpdateLocalBufferToGPU() noexcept;
			FORCE_INLINE void UpdateDataToGPU(const void* sourceData, const UINT64 sizeOfSourceData, const UINT64 offsetInUniformBlock) noexcept
			{
				D_ASSERT(IsBufferGenerated() == true);

				if (IsBufferGenerated() == true)
				{
					GraphicsAPI::UpdateDataToBuffer(mUniformBufferObject, GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, offsetInUniformBlock, sizeOfSourceData, sourceData);
				}
			}
			FORCE_INLINE void UpdateDataToGPU(const void* sourceData, const UINT64 sizeOfSourceData, const char* const targetVariableName) noexcept
			{
				D_ASSERT(IsBufferGenerated() == true);

				if (IsBufferGenerated() == true)
				{
					D_DEBUG_LOG(eLogType::D_WARNING, "Uniform buffer object is updated with string variable name. This is slow operation. Please pass offset directly");
					const UINT64 offset = GetUniformVariableOffset(targetVariableName);
					GraphicsAPI::UpdateDataToBuffer(mUniformBufferObject, GraphicsAPI::eBufferTarget::UNIFORM_BUFFER, offset, sizeOfSourceData, sourceData);
				}
			}
			/// <summary>
			/// Store data in temporary buffer
			/// data isn't send to gpu instantly, it is stored in temp buffer
			/// if you want buffer data ( send data to gpu ), call BufferData function
			/// </summary>
			/// <param name="sourceData">souce data address</param>
			/// <param name="sizeInByte">data size in byte</param>
			/// <param name="offsetInUniformBlock"></param>
			void UpdateLocalBuffer
			(
				const void* sourceData,
				const UINT32 sizeOfSourceData,
				const UINT32 offsetInUniformBlock,
				const bool instantlyUpdateToGPU
			);
		
			bool IsBufferGenerated() const final;
		};
	}
}

