#pragma once

#include <vector>

namespace dooms
{
	namespace graphics
	{
		// DirectX / OpenGL(Vulkan) concepts mapping chart
		// https://computergraphics.stackexchange.com/questions/4422/directx-openglvulkan-concepts-mapping-chart/4432

		enum class eGraphicsAPIType
		{
			GraphicsAPIType_NONE,
			OpenGL,
			DX11
			
		};

		class GraphicsAPIInput;
		class __declspec(dllexport) GraphicsAPI
		{
		private:

			static GraphicsAPIInput* mGraphicsAPIInputManager;
			inline static eGraphicsAPIType mGraphicsAPIType = eGraphicsAPIType::GraphicsAPIType_NONE;

		public:

			using DEBUG_FUNCTION = void (*)(const char* const debugMessage);
			inline static DEBUG_FUNCTION* mDEBUG_FUNCTION = nullptr;

			static void SetGraphicsAPIType(const eGraphicsAPIType graphicsAPIType);
			static eGraphicsAPIType GetGraphicsAPIType();

			enum eBufferBitType : unsigned int
			{
				COLOR_BUFFER, // = GL_COLOR_BUFFER_BIT,
				DEPTH_BUFFER, // = GL_DEPTH_BUFFER_BIT,
				DEPTH_STENCIL_BUFFER // = GL_STENCIL_BUFFER_BIT
			};

			enum eBufferType : unsigned int
			{
				COLOR, // = GL_COLOR_BUFFER_BIT,
				DEPTH, // = GL_DEPTH_BUFFER_BIT,
				DEPTH_STENCIL // = GL_STENCIL_BUFFER_BIT
			};

			enum eBufferMode : unsigned int
			{
				FRONT_LEFT, // = GL_FRONT_LEFT,
				FRONT_RIGHT, // = GL_FRONT_RIGHT,
				BACK_LEFT, // = GL_BACK_LEFT,
				BACK_RIGHT, // = GL_BACK_RIGHT,
				FRONT, // = GL_FRONT,
				BACK, // = GL_BACK,
				LEFT, // = GL_LEFT,
				RIGHT, // = GL_RIGHT,
				COLOR_ATTACHMENT0, // = GL_COLOR_ATTACHMENT0,
				COLOR_ATTACHMENT1, // = GL_COLOR_ATTACHMENT1,
				COLOR_ATTACHMENT2, // = GL_COLOR_ATTACHMENT2,
				COLOR_ATTACHMENT3, // = GL_COLOR_ATTACHMENT3,
				COLOR_ATTACHMENT4, // = GL_COLOR_ATTACHMENT4,
				COLOR_ATTACHMENT5, // = GL_COLOR_ATTACHMENT5,
				COLOR_ATTACHMENT6, // = GL_COLOR_ATTACHMENT6,
				COLOR_ATTACHMENT7, // = GL_COLOR_ATTACHMENT7,
				COLOR_ATTACHMENT8, // = GL_COLOR_ATTACHMENT8,
				COLOR_ATTACHMENT9, // = GL_COLOR_ATTACHMENT9,
				COLOR_ATTACHMENT10 // = GL_COLOR_ATTACHMENT10,
			};

			enum eBufferAttachmentType : unsigned int
			{
				ATTACHMENT_COLOR0, // = GL_COLOR_BUFFER_BIT,
				ATTACHMENT_COLOR1, // = GL_COLOR_BUFFER_BIT,
				ATTACHMENT_COLOR2, // = GL_COLOR_BUFFER_BIT,
				ATTACHMENT_COLOR3, // = GL_COLOR_BUFFER_BIT,
				ATTACHMENT_DEPTH, // = GL_DEPTH_BUFFER_BIT,
				ATTACHMENT_DEPTH_STENCIL //= GL_STENCIL_BUFFER_BIT
			};

			enum eTextureInternalFormat : unsigned int
			{
				RGBA16F,
				DEPTH_COMPONENT,
				DEPTH24_STENCIL8
			};
			
			enum eBindFrameBufferTarget : unsigned int
			{
				DRAW_FRAMEBUFFER,
				READ_FRAMEBUFFER,
				FRAMEBUFFER
			};

			enum ePrimitiveType : unsigned int
			{
				POINTS, //= GL_POINTS,
				//LINE_STRIP = GL_LINE_STRIP,
				//LINE_LOOP = GL_LINE_LOOP,
				LINES, //= GL_LINES,
				//LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
				//LINES_ADJACENCY = GL_LINES_ADJACENCY,
				//TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
				//TRIANGLE_FAN = GL_TRIANGLE_FAN,
				TRIANGLES, //= GL_TRIANGLES,
				//TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
				//TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
				//PATCHES = GL_PATCHES,
				NONE = 0XFFFF
			};

			enum eBufferTarget : unsigned int
			{
				ARRAY_BUFFER,
				ELEMENT_ARRAY_BUFFER,
				DRAW_INDIRECT_BUFFER,
				TEXTURE_BUFFER,
				UNIFORM_BUFFER,
			};

			static unsigned int Initialize();
			static unsigned int DeInitialize();
			static void SwapBuffer();

			static void SetVSync(const bool isEnabled);

			static void WriteBuffer(const GraphicsAPI::eBufferMode bufferMode);
			static void WriteBuffers(const unsigned int count, const std::vector<GraphicsAPI::eBufferMode> bufferModes);
			static void ReadBuffer(const GraphicsAPI::eBufferMode bufferMode);

			static void ClearColor(const float r, const float g, const float b, const float a);
			static void ClearColor(const float* const colors);
			static void ClearBuffer(const unsigned int clearMaskBits);
			static void ClearBuffer(const eBufferBitType clearMask);
			static void ClearBuffer(const eBufferBitType clearMask1, const eBufferBitType clearMask2);
			static void ClearBuffer(const eBufferBitType clearMask1, const eBufferBitType clearMask2, const eBufferBitType clearMask3);
			static void ClearSpecificBuffer(const eBufferType bufferType, const unsigned int drawBufferIndex, const float r, const float g, const float b, const float a);
			static void ClearSpecificBuffer(const eBufferType bufferType, const unsigned int drawBufferIndex, const float* const colors);

			static std::vector<unsigned int> GenerateBuffer(const unsigned int count);
			static void DestroyBuffer(const unsigned int bufferID);
			static std::vector<unsigned int> CreateBuffers(const unsigned int bufferCount);
			static void DestroyBuffers(const std::vector<unsigned int>& buffers);
			static std::vector<unsigned int> CreateVertexArrayObject(const unsigned int count);
			static void DestroyVertexArrayObject(const std::vector<unsigned int>& vertexArrayObjects);
			static void BindVertexArrayObject(const unsigned int vertexArrayObject);
			static void UnBindVertexArrayObject();
			static void AllocateBufferMemory
			(
				const eBufferTarget bufferTarget,
				const unsigned int bufferSize, // in bytes
				const void* const initialData
			);
			static void EnableVertexAttributeArrayIndex
			(
				const unsigned int vertexAttributeIndex
			);
			static void DefineVertexAttributeLayout
			(
				const unsigned int vertexAttributeIndex,
				const unsigned int componentNumber,
				const unsigned int stride,
				const unsigned int offset
			);

			static void BindBuffer
			(
				const unsigned int bufferObject,
				const eBufferTarget bindBufferTarget
			);
			static void UnBindBuffer
			(
				const eBufferTarget bindBufferTarget
			);
			static void BindBufferToIndexedBuffer
			(
				const eBufferTarget bindBufferTarget,
				const unsigned int bindingPoint,
				const unsigned int bufferObject
			);

			static void UpdateDataToBuffer
			(
				const eBufferTarget bindFrameBufferTarget,
				const unsigned int offset,
				const unsigned int dataSize,
				const void* const data
			);

			static void BindFrameBuffer
			(
				const unsigned int frameBufferObject,
				const eBindFrameBufferTarget bindFrameBufferTarget
			);
			static void BindRenderBuffer(const unsigned int renderBufferObject);

			static std::vector<unsigned int> CreateRenderBufferObject(const unsigned int renderBufferCount);
			static void AllocateRenderBufferMemory
			(
				const unsigned int renderBufferObject,
				const eTextureInternalFormat textureInternalFormat,
				const unsigned int width, const unsigned height,
				const unsigned int multiSample
			);
			static void AttachRenderBufferToFrameBuffer
			(
				const unsigned int renderBufferObject,
				const unsigned int frameBufferObject,
				const eBufferAttachmentType bufferType
			);

		

			static void Draw
			(
				const ePrimitiveType primitiveType,
				const unsigned int vertexCount,
				const unsigned int startVertexLocation = 0
			);
			static void DrawIndexed
			(
				const ePrimitiveType primitiveType, 
				const unsigned int indiceCount,
				const void* const indices = 0
			);

			static unsigned int CreateMaterial();
			static void DestroyMaterial(const unsigned int materialObject);
			/**
			 * \brief 
			 * \param materialObject 
			 * \return If success, return true
			 */
			static bool LinkMaterial(const unsigned int materialObject);
			static void BindMaterial(const unsigned int materialObject);

			enum eShaderType : unsigned int
			{
				ShaderType_None,
				Vertex,
				Fragment,
				Geometry
			};

			static unsigned int CreateShaderObject(const eShaderType shaderType);
			static void DestroyShaderObject(const unsigned int shaderObject);
			static void CompileShader(const unsigned int shaderObject, const char* const shaderText);
			static void CompileShaders(const unsigned int shaderObject, const unsigned int shaderCount, const char* const * const shaderTexts);

			static void AttachShaderToMaterial(const unsigned int materialObject, const unsigned int shaderObject);
			
			static void UpdateConstantBuffer_bool1(const int constantBufferID, const bool value1);
			static void UpdateConstantBuffer_bool2(const int constantBufferID, const bool value1, const bool value2);
			static void UpdateConstantBuffer_bool3(const int constantBufferID, const bool value1, const bool value2, const bool value3);
			static void UpdateConstantBuffer_bool4(const int constantBufferID, const bool value1, const bool value2, const bool value3, const bool value4);

			static void UpdateConstantBuffer_int1(const int constantBufferID, const int value1);
			static void UpdateConstantBuffer_int2(const int constantBufferID, const int value1, const int value2);
			static void UpdateConstantBuffer_int3(const int constantBufferID, const int value1, const int value2, const int value3);
			static void UpdateConstantBuffer_int4(const int constantBufferID, const int value1, const int value2, const int value3, const int value4);

			static void UpdateConstantBuffer_float1(const int constantBufferID, const float value1);
			static void UpdateConstantBuffer_float2(const int constantBufferID, const float value1, const float value2);
			static void UpdateConstantBuffer_float3(const int constantBufferID, const float value1, const float value2, const float value3);
			static void UpdateConstantBuffer_float4(const int constantBufferID, const float value1, const float value2, const float value3, const float value4);

			static void UpdateConstantBuffer_mat2x2f(const int constantBufferID, const float* const matrix);
			static void UpdateConstantBuffer_mat3x3f(const int constantBufferID, const float* const matrix);
			static void UpdateConstantBuffer_mat4x4f(const int constantBufferID, const float* const matrix);


			enum eTextureType : unsigned int
			{
				TextureType_NONE, // = 0,
				DIFFUSE, // = 1,
				SPECULAR, // = 2,
				AMBIENT, // = 3,
				EMISSIVE, // = 4,
				HEIGHT, // = 5,
				NORMALS, // = 6,
				SHININESS, // = 7,
				OPACITY, // = 8,
				DISPLACEMENT, // = 9,
				LIGHTMAP, // = 10,
				REFLECTION, // = 11,
				BASE_COLOR, // = 12,
				NORMAL_CAMERA, // = 13,
				EMISSION_COLOR, // = 14,
				METALNESS, // = 15,
				DIFFUSE_ROUGHNESS, // = 16,
				AMBIENT_OCCLUSION, // = 17,
				UNKNOWN //= 18,
			};

			enum eTextureBindTarget : unsigned int
			{
				TextureBindTarget_NONE, // = 0,
				TEXTURE_1D, // = GL_TEXTURE_1D,
				TEXTURE_2D, // = GL_TEXTURE_2D,
				TEXTURE_3D, // = GL_TEXTURE_3D,
				TEXTURE_1D_ARRAY, // = GL_TEXTURE_1D_ARRAY,
				TEXTURE_2D_ARRAY, // = GL_TEXTURE_2D_ARRAY,
				TEXTURE_RECTANGLE, // = GL_TEXTURE_RECTANGLE,
				TEXTURE_CUBE_MAP, // = GL_TEXTURE_CUBE_MAP,
				TEXTURE_CUBE_MAP_ARRAY, // = GL_TEXTURE_CUBE_MAP_ARRAY,
				_TEXTURE_BUFFER, // = GL_TEXTURE_BUFFER,
				TEXTURE_2D_MULTISAMPLE, // = GL_TEXTURE_2D_MULTISAMPLE,
				TEXTURE_2D_MULTISAMPLE_ARRAY, // = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
			};
		};
	}
}


