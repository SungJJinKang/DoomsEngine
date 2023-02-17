#pragma once

#include <array>
#include <string>
#include <memory>
#include <mutex>

#include <Core.h>
#include <Rendering/Buffer/Mesh.h>
#include <Rendering/Material/Material.h>
#include <Graphics/Color.h>
#include "../RenderingDebuggerModule.h"
#include <SingleTon/Singleton.h>
#include "../../DebugPrimitive/DebugPrimitiveContainerCollection.h"

#include "DebugDrawer.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class Material;
		class Graphics_Server;
		class DOOM_API D_CLASS DebugDrawer : public RenderingDebuggerModule, public ISingleton<DebugDrawer>
		{
			GENERATE_BODY()
				
		private:

			static const std::string DEBUG_2D_SHADER;
			static const std::string DEBUG_3D_SHADER;

			D_PROPERTY()
			bool bmIsVertexDataSendToGPUAtCurrentFrame;

			std::mutex mMextex;

			D_PROPERTY()
			Mesh mDebugMesh;

			D_PROPERTY()
			UINT32 mDebugMeshCount;

			D_PROPERTY()
			std::unique_ptr<Material> m2DMaterial;

			D_PROPERTY()
			std::unique_ptr<Material> m3DMaterial;

			D_PROPERTY()
			DebugPrimitiveContainerCollection mDebugPrimitiveContainers;

			D_PROPERTY()
			Material* mDrawInstantlyMaterial;

			void BufferVertexDataToGPU();
			void Draw();

			
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
			void DebugDraw2DPoint(const math::Vector3& point, eColor color);
			void DebugDraw2DPoint(const math::Vector3& point, const math::Vector4 color);

			/// <summary>
			/// Why limit color.
			/// if allow any color user want, we should draw line per color. This will make so many draw call
			/// </summary>
			/// <param name="startWorldPos"></param>
			/// <param name="endWorldPos"></param>
			/// <param name="color"></param>
			void DebugDraw3DPoint(const math::Vector3& point, eColor color);

			/// <summary>
			/// Why limit color.
			/// if allow any color user want, we should draw line per color. This will make so many draw call
			/// </summary>
			/// <param name="startWorldPos"></param>
			/// <param name="endWorldPos"></param>
			/// <param name="color"></param>
			void DebugDraw3DLine(const math::Vector3& startWorldPos, const math::Vector3& endWorldPos, eColor color);
			/// <summary>
			/// You Should pass triangle points ordered counter clockwise
			/// </summary>
			void DebugDraw3DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color);
			void DebugDraw3DSphere(const math::Vector3& center, const float radius, const eColor color);

			/// <summary>
			/// z value will be ignored
			/// pass -1 ~ 1 ( NDC pos )
			/// </summary>
			/// <param name="startNDCPos">-1 ~ 1</param>
			/// <param name="endNDCPos">-1 ~ 1</param>
			/// <param name="color"></param>
			void DebugDraw2DLine(const math::Vector3& startNDCPos, const math::Vector3& endNDCPos, eColor color);
	
			/// <summary>
			/// z value will be ignored
			/// pass -1 ~ 1 ( NDC pos )
			/// You Should pass triangle points ordered counter clockwise
			/// </summary>
			void DebugDraw2DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color);
			void DebugDraw2DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, const math::Vector4 color);
			void DebugDraw2DBox(const math::Vector3& leftBottom, const math::Vector3& rightTop, eColor color);
			void DebugDraw2DBox(const math::Vector3& leftBottom, const math::Vector3& rightTop, math::Vector4 color);
			//void DebugDraw2DTriangleScreenSpace(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color);
			
			void SetDrawInstantlyMaterial(Material* material);

			void Initialize() override;
			void PreRender() override;
			void Render() override;
			void LateRender() override;
			void PostRender() override;
			const char* GetRenderingDebuggerModuleName() override;
		};

		
	}
}