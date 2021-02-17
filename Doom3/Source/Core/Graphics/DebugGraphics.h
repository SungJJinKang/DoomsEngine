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

			static inline constexpr unsigned int MAX_DEBUG_LINE_COUNT{ 100 };
			Mesh mDebugMesh{};

			bool bmIs2dLineDataAdded{ false };
			std::array<std::vector<Line>, ENUM_COLOR_COUNT> m2dLine;
			bool bmIs3dLineDataAdded{ false };
			std::array<std::vector<Line>, ENUM_COLOR_COUNT> m3dLine;

			unsigned int mDebugMeshCount{ 0 };

			std::unique_ptr<Material> m2DMaterial;
			std::unique_ptr<Material> m3DMaterial;

			DebugGraphics();
			void DrawDebug();

			void Init();
			void Reset();
		public:

			/// <summary>
			/// Why limit color.
			/// if allow any color user want, we should draw line per color. This will make so many draw call
			/// </summary>
			/// <param name="startWorldPos"></param>
			/// <param name="endWorldPos"></param>
			/// <param name="color"></param>
			void DebugDraw3DLine(const math::Vector3& startWorldPos, const math::Vector3& endWorldPos, eColor color);
			/// <summary>
			/// z value will be ignored
			/// pass -1 ~ 1 ( NDC pos )
			/// </summary>
			/// <param name="startNDCPos">-1 ~ 1</param>
			/// <param name="endNDCPos">-1 ~ 1</param>
			/// <param name="color"></param>
			void DebugDraw2DLine(const math::Vector3& startNDCPos, const math::Vector3& endNDCPos, eColor color);
			void DebugDrawSphere(const math::Vector3& centerWorldPos, float radius, eColor color);


			

		};

		
	}
}



