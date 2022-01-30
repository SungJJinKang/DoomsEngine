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
				SV_Target3,
				UNKNOWN
			};

			eHlslSemantic ConvertStringToeHlslSemantic(const std::string& typeStr);

			enum class eShaderVariableType
			{
				FLOAT1,
				FLOAT2,
				FLOAT3,
				FLOAT4,
				MAT2X2,
				MAT3X3,
				MAT4X4,
				INT1,
				INT2,
				INT3,
				INT4,
				UNKNOWN
			};

			eShaderVariableType ConvertStringToeShaderVariableType(const std::string& typeStr);

			struct D_STRUCT ShaderInputType
			{
				D_PROPERTY()
				UINT32 mID;

				D_PROPERTY()
				std::string mName;

				D_PROPERTY()
				UINT32 mLocation;

				D_PROPERTY()
				eHlslSemantic mSemanticType;

				D_PROPERTY()
				UINT32 mSemanticIndex;

				D_PROPERTY()
				eShaderVariableType mType;
			};

			struct D_STRUCT ShaderOutputType
			{
				D_PROPERTY()
				UINT32 mID;

				D_PROPERTY()
				std::string mName;

				D_PROPERTY()
				UINT32 mLocation;
			};

			struct D_STRUCT UniformBufferMember
			{
				D_PROPERTY()
				std::string mName;

				D_PROPERTY()
				eShaderVariableType mType;

				D_PROPERTY()
				UINT32 mOffset;

				D_PROPERTY()
				UINT32 mSize;

				D_PROPERTY()
				UINT32 mArrayLength;
			};

			struct D_STRUCT UniformBuffer // OPENGL : Uniform Buffer, DirectX : ConstantBuffer
			{
				D_PROPERTY()
				UINT32 mID;

				D_PROPERTY()
				std::string mName;

				D_PROPERTY()
				UINT32 mSet;

				D_PROPERTY()
				UINT32 mBindingPoint;

				D_PROPERTY()
				UINT32 mBlockSize;

				D_PROPERTY()
				std::vector<UniformBufferMember> mMembers;
			};

			struct D_STRUCT ShaderReflectionData
			{
				bool mIsGenerated = false;
				dooms::graphics::GraphicsAPI::eGraphicsAPIType mTargetGraphicsAPIType;
				std::string mProfileVersion;
				std::string ShaderReflectionDataFileName;
				dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage mShaderType;

				std::vector<ShaderInputType> mInputVariables;
				std::vector<ShaderOutputType> mOutputVariables;
				std::vector<UniformBuffer> mUniformBuffers;
				
				void Clear();
			};

			ShaderReflectionData ParseShaderReflectionStringText(const std::string& reflectionDataJsonText);
		}
	}
}

