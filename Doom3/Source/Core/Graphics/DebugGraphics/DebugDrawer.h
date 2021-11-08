#pragma once

#include <Core.h>
#include "../Graphics_Core.h"


#ifdef DEBUG_DRAWER


#include <array>
#include <string>
#include <memory>

#include "../../Math/LightMath_Cpp/Vector3.h"
#include "../Buffer/Mesh.h"
#include "../Material/Material.h"
#include "../Color.h"

#include "../PrimitiveType/PrimitiveLine.h"
#include "../PrimitiveType/PrimitiveTriangle.h"

namespace dooms
{
	namespace graphics
	{
		class Material;
		class Graphics_Server;
		class DOOM_API D_CLASS DebugDrawer : public DObject, public ISingleton<DebugDrawer>
		{
			DOBJECT_CLASS_BODY(DebugDrawer, eDOBJECT_ClassFlags::NonCopyable)
				DOBJECT_CLASS_BASE_CHAIN(DObject)
		private:

			static inline const std::string DEBUG_2D_SHADER{ "Debug2DShader.glsl" };
			static inline const std::string DEBUG_3D_SHADER{ "Debug3DShader.glsl" };

			static inline constexpr UINT32 DEBUG_2D_LINE_INDEX{ 0 };
			static inline constexpr UINT32 DEBUG_3D_LINE_INDEX{ 1 };
			static inline constexpr UINT32 DEBUG_2D_TRIANGLE_INDEX{ 2 };
			static inline constexpr UINT32 DEBUG_3D_TRIANGLE_INDEX{ 3 };
			
			static inline constexpr UINT32 MAX_DEBUG_VERTEX_COUNT{ 20000000 };
			
			bool bmIsVertexDataSendToGPUAtCurrentFrame{ false };
			
			Mesh mDebugMesh{};

			std::array<std::vector<PrimitiveLine>, ENUM_COLOR_COUNT> m2dLine;
			std::array<std::vector<PrimitiveLine>, ENUM_COLOR_COUNT> m3dLine;
			std::array<std::vector<PrimitiveTriangle>, ENUM_COLOR_COUNT> m2dTriangle;
			std::array<std::vector<PrimitiveTriangle>, ENUM_COLOR_COUNT> m3dTriangle;

			UINT32 mDebugMeshCount{ 0 };

			std::unique_ptr<Material> m2DMaterial;
			std::unique_ptr<Material> m3DMaterial;

			


			Material* mDrawInstantlyMaterial{ nullptr };

			/// <summary>
			/// Don't call this directly, use DebugDraw2DLine
			/// </summary>
			/// <param name="startNDCPos"></param>
			/// <param name="endNDCPos"></param>
			/// <param name="color"></param>
			void DebugDraw2DLineInstantly(const math::Vector3& startNDCPos, const math::Vector3& endNDCPos, eColor color);
			/// <summary>
			/// Don't call this directly, use DebugDraw2DTriangle
			/// </summary>
			/// <param name="pointA"></param>
			/// <param name="pointB"></param>
			/// <param name="pointC"></param>
			/// <param name="color"></param>
			void DebugDraw2DTriangleInstantly(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color);

		public:

			void SetIsVertexDataSendToGPUAtCurrentFrame(const bool isSet);
			bool GetIsVertexDataSendToGPUAtCurrentFrame() const;
			
			DebugDrawer();

			/// <summary>
			/// Why limit color.
			/// if allow any color user want, we should draw line per color. This will make so many draw call
			/// </summary>
			/// <param name="startWorldPos"></param>
			/// <param name="endWorldPos"></param>
			/// <param name="color"></param>
			void DebugDraw3DLine(const math::Vector3& startWorldPos, const math::Vector3& endWorldPos, eColor color, bool drawInstantly = false);
			/// <summary>
			/// You Should pass triangle points ordered counter clockwise
			/// </summary>
			void DebugDraw3DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color, bool drawInstantly = false);

			/// <summary>
			/// z value will be ignored
			/// pass -1 ~ 1 ( NDC pos )
			/// </summary>
			/// <param name="startNDCPos">-1 ~ 1</param>
			/// <param name="endNDCPos">-1 ~ 1</param>
			/// <param name="color"></param>
			void DebugDraw2DLine(const math::Vector3& startNDCPos, const math::Vector3& endNDCPos, eColor color, bool drawInstantly = false);
	
			/// <summary>
			/// z value will be ignored
			/// pass -1 ~ 1 ( NDC pos )
			/// You Should pass triangle points ordered counter clockwise
			/// </summary>
			void DebugDraw2DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color, bool drawInstantly = false);
			
			void SetDrawInstantlyMaterial(Material* material);


			void Init();
			void Update();
			void Reset();

			void BufferVertexDataToGPU();
			void Draw();
		};

		
	}
}


#endif