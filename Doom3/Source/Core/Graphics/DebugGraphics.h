#pragma once

#include <array>
#include <string>
#include <memory>

#include "../Math/LightMath_Cpp/Vector3.h"
#include "Buffer/Mesh.h"
#include "Material.h"
#include "Color.h"

namespace doom
{
	namespace graphics
	{
		
		struct Line
		{
			math::Vector3 startPoint;
			math::Vector3 endPoint;

			Line(const math::Vector3& sPoint, const math::Vector3& ePoint)
				: startPoint{ sPoint }, endPoint{ ePoint }
			{

			}
		};

		struct Triangle
		{
			math::Vector3 PointA;
			math::Vector3 PointB;
			math::Vector3 PointC;

			Triangle(const math::Vector3& A, const math::Vector3& B, const math::Vector3& C)
				: PointA{ A }, PointB{ B }, PointC{ C }
			{

			}
		};



		class Material;
		class Graphics_Server;
		class DebugGraphics : public ISingleton<DebugGraphics>
		{
			friend class Graphics_Server;

			
		private:

			static inline const std::string DEBUG_2D_SHADER{ "Debug2DShader.glsl" };
			static inline const std::string DEBUG_3D_SHADER{ "Debug3DShader.glsl" };

			static inline constexpr unsigned int DEBUG_2D_LINE_INDEX{ 0 };
			static inline constexpr unsigned int DEBUG_3D_LINE_INDEX{ 1 };
			static inline constexpr unsigned int DEBUG_2D_TRIANGLE_INDEX{ 2 };
			static inline constexpr unsigned int DEBUG_3D_TRIANGLE_INDEX{ 3 };

			static inline constexpr unsigned int MAX_DEBUG_VERTEX_COUNT{ 3000 * 2 + 300 * 3 }; // 24 * 1000byte -> 0.024mb
			Mesh mDebugMesh{};

			std::array<std::vector<Line>, ENUM_COLOR_COUNT> m2dLine;
			std::array<std::vector<Line>, ENUM_COLOR_COUNT> m3dLine;
			std::array<std::vector<Triangle>, ENUM_COLOR_COUNT> m2dTriangle;
			std::array<std::vector<Triangle>, ENUM_COLOR_COUNT> m3dTriangle;

			unsigned int mDebugMeshCount{ 0 };

			std::unique_ptr<Material> m2DMaterial;
			std::unique_ptr<Material> m3DMaterial;

			DebugGraphics();
			void DrawDebug();

			void Init();
			void Reset();

			Material* mDrawInstantlyMaterial{ nullptr };

			void DebugDraw2DLineInstantly(const math::Vector3& startNDCPos, const math::Vector3& endNDCPos, eColor color);
			void DebugDraw2DTriangleInstantly(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color);

		public:

			static inline bool mbDrawDebug{ true };
			static inline eColor mDefaultDebugColor{ eColor::White };

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
			void DebugDraw2DLine(const math::Vector3& startNDCPos, const math::Vector3& endNDCPos, eColor color, bool resizeByScreenRatio = true, bool drawInstantly = false);
	
			/// <summary>
			/// z value will be ignored
			/// pass -1 ~ 1 ( NDC pos )
			/// You Should pass triangle points ordered counter clockwise
			/// </summary>
			void DebugDraw2DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color, bool resizeByScreenRatio = true, bool drawInstantly = false);
			

			void SetDrawInstantlyMaterial(Material* material);

		};

		
	}
}



