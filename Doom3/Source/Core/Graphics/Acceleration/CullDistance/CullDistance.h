#pragma once

#include <vector>

#include <Vector3.h>

#include <Core.h>
#include "Simple_SingleTon/Singleton.h"
#include "../Culling.h"
#include "utility/BVH/BVH.h"




namespace dooms
{
	class Renderer;
	namespace graphics
	{
	

		/// <summary>
		/// https://docs.unrealengine.com/en-US/RenderingAndGraphics/VisibilityCulling/CullDistanceVolume/index.html
		/// </summary>
		class DOOM_API D_CLASS CullDistance : public ICulling, public ISingleton<CullDistance>
		{
			friend class Graphics_Server;

			struct CullDistanceData
			{
				INT32 mVolumeSphereRadius;
				INT32 mCullDistance;
				FLOAT32 mCullDistanceSqr;
			};

		private:
			/// <summary>
			/// First Element : Sphere Volume Size
			/// Second Element : Cull Distance
			/// 
			/// If try to render one object,
			/// This system pick element having first element closest to Object's Render Sphere radius.
			/// If distance from camera to obejct is larger than second element, it will culled
			/// </summary>
			std::vector<CullDistanceData> mCullDistanceSetting{};
			bool bmIsCullDistanceSettingDirty{ true };
			
			math::Vector3 mCameraPosition{ nullptr };

			void AddCullDistance(INT32 volumeSphereRadius, INT32 cullDistance);
			void RemoveCullDistance(INT32 volumeSphereSize, INT32 cullDistance);
			void RemoveCullDistance(INT32 index);

			FLOAT32 PickCullDistanceSqr(FLOAT32 sphereRadius);

			void Initialize();
			/// <summary>
			/// 
			/// </summary>

			void OnStartDraw();

			//void OnEndFrame();

			// void dooms::graphics::CullDistance::OnEndFrame()
			// {
			// 
			// }
			bool GetIsVisible(Renderer* renderer);


			// Inherited via ICulling
			virtual void PreComputeCulling() override;

			/*void SetIsDrawed(bool isDrawed);*/
		};


	}
}
