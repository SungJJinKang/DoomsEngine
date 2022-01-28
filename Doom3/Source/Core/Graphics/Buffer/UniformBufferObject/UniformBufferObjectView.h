#pragma once

#include <Core.h>

#include <string>
#include <unordered_map>

#include <Graphics/GraphicsAPI/GraphicsAPI.h>

#include "UniformBufferObjectView.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class UniformBufferObject;
		class Material;

		class DOOM_API D_CLASS  UniformBufferObjectView : public DObject
		{
			GENERATE_BODY()

		private:

			D_PROPERTY()
			Material* mTargetMaterial;

			D_PROPERTY()
			UniformBufferObject* mTargetUniformBufferObject;

			/// <summary>
			/// Cache element of uniform block's aligned offset
			/// </summary>
			std::unordered_map<std::string, UINT32> mUniformVariableOffsetCache{};

			D_PROPERTY()
			UINT32 mDefaultBindingPoint;
			D_PROPERTY()
			GraphicsAPI::eGraphicsPipeLineStage mDefaultTargetPipeLineStage;

		public:


			UniformBufferObjectView
			(
				Material* const targetMaterial,
				UniformBufferObject* const targetUBO,
				const UINT32 defaultBindingPoint,
				const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage
			);


			UniformBufferObjectView(const UniformBufferObjectView&) = default;
			UniformBufferObjectView(UniformBufferObjectView&&) noexcept = default;
			UniformBufferObjectView& operator=(const UniformBufferObjectView&) = default;
			UniformBufferObjectView& operator=(UniformBufferObjectView&&) noexcept = default;


			UINT32 UpdateUniformVariableOffsetCache(const char* const targetUniformVariableName);
			UINT32 GetOrUpdateUniformVaraibleOffsetInUniformBlock(const char* const targetUniformVariableName);
			
			void UpadteLocalBuffer
			(
				const void* sourceData,
				const UINT32 sizeOfSourceData,
				const char* const targetUniformVariableName
			);

			
			void BindUniformBufferObject() const noexcept;

			void BindUniformBufferObject(const UINT32 bindingPoint, const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage) const noexcept;

			Material* GetTargetMaterial() const;
			UniformBufferObject* GetTargetUniformBufferObject() const;

		};

	}
}
