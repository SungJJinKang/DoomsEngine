#pragma once

#include <vector>
#include <string>

#include <Core.h>

#include <Graphics/GraphicsAPI/GraphicsAPI.h>

namespace dooms
{
	namespace asset
	{
		namespace shaderReflectionDataParser
		{
			enum class eHlslSemantic
			{
				POSITION,
				NORMAL,
				TEXCOORD0,
				TEXCOORD1,
				TEXCOORD2,
				TEXCOORD3,
				TEXCOORD4,
				TEXCOORD5,
				TEXCOORD6,
				TEXCOORD7,
				COLOR0,
				COLOR1,
				COLOR2,
				COLOR3,
				TANGENT,
				BINORMAL,
				BLENDINDICES,
				BLENDWEIGHT,
				SV_Target0,
				SV_Target1,
				SV_Target2,
				SV_Target3
			};

			enum class eShaderVariableType
			{
				FLOAT1,
				FLOAT2,
				FLOAT3,
				FLOAT4,
				MAT3X4,
				MAT4X3,
				MAT3X3,
				MAT4X4,
				INT1,
				INT2,
				INT3,
				INT4
			};

			struct ShaderInputOutput
			{
				UINT32 mID;
				std::string mName;
				UINT32 mLocation;
				eHlslSemantic mSemanticType;
				UINT32 mSemanticIndex;
				eShaderVariableType mType;
			};

			struct UniformBufferMember
			{
				std::string mName;
				eShaderVariableType mType;
				UINT32 mOffset;
				UINT32 mSize;
			};

			struct UniformBuffer // OPENGL : Uniform Buffer, DirectX : ConstantBuffer
			{
				UINT32 mID;
				std::string mName;
				UINT32 mSet;
				UINT32 mBindingPoint;
				UINT32 mSize;
				std::vector<UniformBufferMember> mMembers;
			};

			struct ShaderReflectionData
			{
				dooms::graphics::GraphicsAPI::eGraphicsAPIType mTargetGraphicsAPIType;
				std::string mSHaderVersion;
				std::string ShaderReflectionDataFileName;
				dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage mShaderType;

				std::vector<ShaderInputOutput> mInputVariables;
				std::vector<ShaderInputOutput> mOutputVariables;
				std::vector<UniformBuffer> mUniformBuffers;
			};
		}
	}
}

