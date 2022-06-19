#pragma once

#include <Core.h>

#include <array>
#include <atomic>

#include <Graphics/Graphics_Core.h>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include "RenderingProxy.h"
#include <Rendering/Buffer/BufferID.h>
#include <Rendering/Proxy/RenderingUniformBufferObjectViewProxy.h>
#include <Misc/eStatus.h>

namespace dooms
{
	namespace graphics
	{
		class UniformBufferObject;
		class RenderingTextureProxy;
		class RenderingTextureViewProxy;
		class RenderingShaderProxy;
		class RenderingUniformBufferObjectViewProxy;

		class RenderingMaterialProxy : public RenderingProxy
		{

		public:

			struct FRenderingMaterialProxyInitializer
			{
				
			};
			void InitRenderingMaterialProxyInitializer(FRenderingMaterialProxyInitializer& Initializer);

			FORCE_INLINE RenderingUniformBufferObjectViewProxy* GetRenderingUniformBufferObjectViewProxyFromUBOIndex(const size_t UBOIndex)
			{
				RenderingUniformBufferObjectViewProxy* TargetUBOViewProxy = nullptr;
				D_ASSERT(UBOIndex < TargetRenderingUniformBufferObjectViewProxyList.size());

				if (UBOIndex < TargetRenderingUniformBufferObjectViewProxyList.size())
				{
					TargetUBOViewProxy = TargetRenderingUniformBufferObjectViewProxyList[UBOIndex];
				}

				return TargetUBOViewProxy;
			}
			RenderingUniformBufferObjectViewProxy* GetRenderingUniformBufferObjectViewProxyFromUBOName(const char* const uniformBufferObjectName);

			void BindMaterial();
			void UnBindMaterial();

			void CreateMaterialObjectIfNotExist();
			void DestroyMaterialObjectIfExist();
			void DestroyShaderFromMaterial(const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage ShaderType);

			void SetShaderProxy(dooms::graphics::RenderingShaderProxy* const ShaderProxy);
			void SetShaderProxy(dooms::graphics::RenderingShaderProxy* const ShaderProxy, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage ShaderType);
			void SetShaderProxy(const std::array<dooms::graphics::RenderingShaderProxy*, GRAPHICS_PIPELINE_STAGE_COUNT>& ShaderProxyList);
			
			void AddTexture
			(
				const UINT32 BindingPoint, 
				const RenderingTextureProxy* const TextureProxy,
				const graphics::GraphicsAPI::eGraphicsPipeLineStage DefaultTargetGraphicsPipeLineStage
			);

			eStatus GetMaterialStatus() const;

			RenderingUniformBufferObjectViewProxy* GetUniformBufferObjectViewFromUBOName(const char* const UBOName) const;

			const RenderingTextureViewProxy* GetTextureView(const size_t Index) const;
			size_t GetTextureViewCount() const;

			UINT64 GetMaterialHashValue() const;
			static bool Equal(const RenderingMaterialProxy* const lhs, const RenderingMaterialProxy* const rhs);

		private:

			static UINT64 BOUND_SHADER_ID[GRAPHICS_PIPELINE_STAGE_COUNT];
			static UINT64 BOUND_INPUT_LAYOUT_ID;

			UINT64 MaterialHashValue;
			eStatus MaterialStatus;

			/// <summary>
			/// Used for OpenGL
			///	If Current Graphics API is DirectX, this varaible set to random uuid ( this is for overlap check )
			/// </summary>
			BufferID ProgramIDForOpenGL;
			std::array<dooms::graphics::RenderingShaderProxy*, GRAPHICS_PIPELINE_STAGE_COUNT> AttachedShaderProxyList{ nullptr };

			/// <summary>
			/// Only used for DirectX
			/// </summary>
			std::array<BufferID, GRAPHICS_PIPELINE_STAGE_COUNT> PipeLineShaderView;
			std::vector<const RenderingTextureViewProxy*> TargetTextureViewProxyList;
			std::vector<RenderingUniformBufferObjectViewProxy*> TargetRenderingUniformBufferObjectViewProxyList;

			void AttachShaderProxyToMaterialProxy(dooms::graphics::RenderingShaderProxy* const ShaderProxy, const dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage ShaderType);
			RenderingUniformBufferObjectViewProxy* AddRenderingUniformBufferObjectViewProxy(RenderingUniformBufferProxy* const UBOProxy, const GraphicsAPI::eGraphicsPipeLineStage TargetPipeLineStage);

			void PoolMaterialHashValue();
		};
	}
}

