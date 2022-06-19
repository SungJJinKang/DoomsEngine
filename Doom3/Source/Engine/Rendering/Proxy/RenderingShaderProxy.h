#pragma once
#include <Core.h>

#include <array>

#include "RenderingProxy.h"
#include "Graphics/GraphicsAPI/GraphicsAPI.h"
#include "Rendering/Buffer/BufferID.h"
#include "Rendering/Shader/eShaderCompileStatus.h"
#include "Rendering/Shader/ShaderTextData.h"

namespace dooms
{
	namespace asset
	{
		struct FShaderTextData;
		class ShaderAsset;
		class TextureAsset;
	}

	namespace graphics
	{
		class UniformBufferObject;
		class RenderingTextureViewProxy;
		class RenderingUniformBufferProxy;

		class RenderingShaderProxy : public RenderingProxy
		{
		public:

			virtual ~RenderingShaderProxy() override;

			struct FRenderingShaderProxyInitializer
			{
				std::array<asset::FShaderTextData, GRAPHICS_PIPELINE_STAGE_COUNT> ShaderTextDatas;
				std::vector<RenderingUniformBufferProxy*> RenderingUniformBufferProxyList;
			};

			void InitRenderingShaderProxy(FRenderingShaderProxyInitializer& Initilizer);

			/// <summary>
			/// Don't call this subthread, Should Call this at mainthread
			/// </summary>
			bool CompileShaders();

			/// <summary>
			/// You can delete shaders after Linking to material program
			/// If Shader is linked to material program when the shader is deleted,
			/// Deleting is delayed until the shader is unlinked to the mateiral  
			/// </summary>
			void DestroyShaderObjects();

			dooms::graphics::BufferID GetShaderObject(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;
			graphics::eShaderCompileStatus GetCurrentShaderCompileStatus(const graphics::GraphicsAPI::eGraphicsPipeLineStage shaderType) const;

			bool IsHasAnyValidShaderObject() const;
			bool IsShaderObjectSuccessfullyCreated(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage TargetGraphicsPipeLineStage) const;

			bool IsHasAnyValidShaderTextString() const;

			//const std::string& GetShaderStringText(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;
			//const std::string& GetShaderReflectionDataStringText(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;
			const asset::shaderReflectionDataParser::ShaderReflectionData& GetShaderReflectionData(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage) const;

			const std::vector<dooms::graphics::RenderingUniformBufferProxy*>& GetContainedRenderingUniformBufferProxyList() const;
			FORCE_INLINE const graphics::BufferID& GetInputLayoutForD3D() const
			{
				D_ASSERT(InputLayoutForD3D.IsValid());
				return InputLayoutForD3D;
			}


		private:

			struct FShaderObject
			{
				/// <summary>
				/// OPENGL : Shader Object
				///	DIRECTX : ID3DBlob
				/// </summary>
				dooms::graphics::BufferID ShaderObjectID;
					
				eShaderCompileStatus ShaderCompileStatus;

				FShaderObject();
				bool IsShaderObjectValid() const;
			};

			std::array<asset::FShaderTextData, GRAPHICS_PIPELINE_STAGE_COUNT> ShaderTextDatas;


			graphics::BufferID InputLayoutForD3D{};
			std::array<FShaderObject, GRAPHICS_PIPELINE_STAGE_COUNT> ShaderObjects;

			std::vector<RenderingUniformBufferProxy*> ContainedRenderingUniformBufferProxyList;

			bool CompileSpecificTypeShader(asset::FShaderTextData& ShaderText, const graphics::GraphicsAPI::eGraphicsPipeLineStage ShaderType, FShaderObject& ShaderObject);
			void CreateInputLayoutForD3D();
		};
	}
}