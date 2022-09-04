#pragma once

#include <Core.h>

#include <array>

#include <Rendering/Buffer/BufferID.h>
#include <Rendering/Scene/FVertexBufferLayout.h>
#include <Rendering/Buffer/eVertexArrayFlag.h>
#include <Collider/Sphere.h>
#include <Collider/AABB.h>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>

namespace dooms
{
	namespace graphics
	{
		enum class eDrawType
		{
			DRAW,
			DRAW_INDEXED
		};
		
		struct FDrawCommand
		{
			UINT64 DrawCommandIndexInRenderScene;

			eDrawType DrawType;

			graphics::GraphicsAPI::ePrimitiveType PrimitiveType;

			/// <summary>
			/// DX11 bind this buffer
			/// </summary>
			BufferID VertexDataBuffer;
			BufferID ElementBufferObjectID;

			/// <summary>
			///	DX11 doesn't have this concept. it just bind VertexDataBuffer
			///
			/// OpenGL bind this buffer
			/// </summary>
			BufferID VertexArrayObjectID;

			UINT64 VertexCount;
			UINT64 IndiceCount;

			UINT32 VertexArrayFlag;
			UINT32 TotalStride;
			UINT32 VertexBufferLayoutCount;

			std::array<FVertexBufferLayout, VERTEX_ARRAY_FLAG_COUNT> VertexBufferLayouts;
			
			FDrawCommand(const int*)
			{}

			void Draw();
			void BindVertexArrayObject();
			void BindVertexBufferObject();
			void BindIndexBufferObject();
		};
	}
}

