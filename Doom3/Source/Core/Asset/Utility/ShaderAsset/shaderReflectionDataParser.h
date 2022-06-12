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
				UINT1,
				UINT2,
				UINT3,
				UINT4,
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
				std::string mSemanticType;

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
				UINT64 mOffset;

				D_PROPERTY()
				UINT64 mSize;

				D_PROPERTY()
				UINT64 mArrayLength;
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
				UINT64 mBlockSize;

				D_PROPERTY()
				std::vector<UniformBufferMember> mMembers;
			};

			enum class D_ENUM eTextureDimensionType
			{
				DIMENSION_1D,
				DIMENSION_2D,
				DIMENSION_3D,
				DIMENSION_CUBE
			};

			struct D_STRUCT TextureData // OPENGL : Uniform Buffer, DirectX : ConstantBuffer
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
				eTextureDimensionType mDimension;

				D_PROPERTY()
				std::string mFormat;
			};

			struct D_STRUCT ShaderReflectionData
			{
				bool mIsGenerated = false;
				dooms::graphics::GraphicsAPI::eGraphicsAPIType TargetGraphicsAPIType;
				std::string mProfileVersion;
				std::string ShaderReflectionDataFileName;
				dooms::graphics::GraphicsAPI::eGraphicsPipeLineStage mShaderType;

				std::vector<ShaderInputType> mInputVariables;
				std::vector<ShaderOutputType> mOutputVariables;
				std::vector<UniformBuffer> mUniformBuffers;
				std::vector<TextureData> mTextureDatas;
				
				void Clear();
			};

			ShaderReflectionData ParseShaderReflectionStringText(const std::string& reflectionDataJsonText);
		}
	}
}

