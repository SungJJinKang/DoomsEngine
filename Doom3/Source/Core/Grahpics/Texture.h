#pragma once

#include <unordered_map>

#include "../Core.h"
#include "../API/OpenglAPI.h"


namespace Doom
{
	/// <summary>
	/// reference : https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
	/// </summary>
	class Texture
	{
	private:

	protected:
		unsigned int id;
		
	public:
		enum class TargetTexture {
			NONE = 0,
			DIFFUSE = 1,
			SPECULAR = 2,
			AMBIENT = 3,
			EMISSIVE = 4,
			HEIGHT = 5,
			NORMALS = 6,
			SHININESS = 7,
			OPACITY = 8,
			DISPLACEMENT = 9,
			LIGHTMAP = 10,
			REFLECTION = 11,
			BASE_COLOR = 12,
			NORMAL_CAMERA = 13,
			EMISSION_COLOR = 14,
			METALNESS = 15,
			DIFFUSE_ROUGHNESS = 16,
			AMBIENT_OCCLUSION = 17,
			UNKNOWN = 18,
		};

		enum class BindTarget
		{
			TEXTURE_1D = GL_TEXTURE_1D,
			TEXTURE_2D = GL_TEXTURE_2D,
			TEXTURE_3D = GL_TEXTURE_3D,
			TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
			TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
			TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
			TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
			TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
			TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
			TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
			TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
		};

		enum class TargetTexture
		{
			TEXTURE_2D = GL_TEXTURE_2D, 
			PROXY_TEXTURE_2D = GL_PROXY_TEXTURE_2D,
			TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
			PROXY_TEXTURE_1D_ARRAY = GL_PROXY_TEXTURE_1D_ARRAY,
			TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
			PROXY_TEXTURE_RECTANGLE = GL_PROXY_TEXTURE_RECTANGLE,
			TEXTURE_CUBE_MAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			TEXTURE_CUBE_MAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			TEXTURE_CUBE_MAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			TEXTURE_CUBE_MAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			TEXTURE_CUBE_MAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			TEXTURE_CUBE_MAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			PROXY_TEXTURE_CUBE_MAP = GL_PROXY_TEXTURE_CUBE_MAP
		};

		enum class PixelData_DataFormat
		{
			RED = GL_RED,
			RG = GL_RG,
			RGB = GL_RGB,
			BGR = GL_BGR,
			RGBA = GL_RGBA,
			BGRA = GL_BGRA,
			RED_INTEGER = GL_RED_INTEGER,
			RG_INTEGER = GL_RG_INTEGER,
			RGB_INTEGER = GL_RGB_INTEGER,
			BGR_INTEGER = GL_BGR_INTEGER,
			RGBA_INTEGER = GL_RGBA_INTEGER,
			BGRA_INTEGER = GL_BGRA_INTEGER,
			STENCIL_INDEX = GL_STENCIL_INDEX,
			DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
			DEPTH_STENCIL = GL_DEPTH_STENCIL
		};

		enum class PixelData_DataType
		{
			UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
			BYTE = GL_BYTE,
			UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
			SHORT = GL_SHORT,
			UNSIGNED_INT = GL_UNSIGNED_INT,
			INT = GL_INT,
			HALF_FLOAT = GL_HALF_FLOAT,
			FLOAT = GL_FLOAT,
			UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
			UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
			UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
			UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
			UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
			UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
			UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
			UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
			UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
			UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
			UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
			UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
		};
		
		Texture(unsigned int width, unsigned int height, TargetTexture textureType);
		virtual ~Texture();


		static unsigned int BoundId;

		const unsigned int Width;
		const unsigned int Height;
		const TargetTexture _TargetTexture;
		const BindTarget _BindTarget;
			 
		static std::unordered_map<BindTarget, unsigned int> BoundId;

		void BindTexture();
		void UnBindTexture();
		void ActiveTexture(unsigned int index);
		void ResetTexture();
		void TexImage2D(
			TargetTexture target,
			int level,
			int internalformat,
			int width,
			int height,
			int border,
			PixelData_DataFormat format,
			PixelData_DataType type,
			const void* data
		);
	};
}
