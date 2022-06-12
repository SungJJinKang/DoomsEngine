#pragma once

#include <Core.h>

#include <unordered_map>
#include <string>
#include <vector>

#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include <Asset/Utility/ShaderAsset/shaderReflectionDataParser.h>

#include "UniformBufferObject.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class RenderingUniformBufferProxy;

		/// <summary>
		///
		///	OPENGL : Uniform Buffer Object
		/// DirectX : Constant Buffer
		/// reference : https://www.khronos.org/opengl/wiki/Program_Introspection, https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
		/// </summary>
		class DOOM_API D_CLASS UniformBufferObject : public DObject
		{
			//GENERATE_BODY()
			
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
			
			void InitializeUniformBufferObject
			(
				const std::string& uniformBlockName,
				const UINT64 uniformBufferSize,
				const UINT32 defaultBindingPoint,
				const void* const initialData,
				const std::vector<asset::shaderReflectionDataParser::UniformBufferMember>* const uboMembers
			);

			std::string GetUniformBlockName();
			const std::string& GetUniformBlockName() const;

			void DestroyUniformBufferProxy();
			
			void BindBuffer(const UINT32 bindingPoint, const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage) noexcept;
			void UnBindBuffer(const UINT32 bindingPoint, const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage) noexcept;

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
				const UINT64 offsetInUniformBlock,
				const UINT64 sizeOfSourceData
			);

			/// <summary>
			/// Send data in mUniformBufferData to gpu 
			/// </summary>
			/// <returns></returns>
			void UpdateLocalBufferToGPU() noexcept;
			void UpdateDataToGPU(const void* sourceData, const UINT64 offsetInUniformBlock, const UINT64 sizeOfSourceData) noexcept;
			void UpdateDataToGPU(const void* sourceData, const char* const targetVariableName, const UINT64 sizeOfSourceData) noexcept;

			bool IsBufferGenerated() const final;
			RenderingUniformBufferProxy* GetUniformBufferProxy() const;
			
		private:

			static inline const char GL_UNIFORM_BUFFER_TAG[]{ "GL_UNIFORM_BUFFER" };

			RenderingUniformBufferProxy* UniformBufferProxy{ nullptr };

			D_PROPERTY()
			std::string UniformBlockName;
			
			D_PROPERTY()
			UINT64 UniformBufferSize;

			D_PROPERTY()
			UINT32 DefaultBindingPoint;

			D_PROPERTY()
			std::vector<asset::shaderReflectionDataParser::UniformBufferMember> UniformBufferMemberList;

			void OnSetPendingKill() override;

			void CreateRenderingUniformBufferProxy();
			void GenerateUniformBufferObject(const void* const RawInitialData = nullptr, const UINT64 SizeOfSourceData = 0);
		};
	}
}

