#pragma once

#include <vector>
#include <utility>

#include <Vector3.h>

#include <Core.h>
#include "Simple_SingleTon/Singleton.h"
#include "../Culling.h"
#include "utility/BVH/BVH.h"




namespace doom
{
	class Renderer;
	namespace graphics
	{
	

		/// <summary>
		/// https://docs.unrealengine.com/en-US/RenderingAndGraphics/VisibilityCulling/CullDistanceVolume/index.html
		/// </summary>
		class DOOM_API CullDistance : public ICulling, ISingleton<CullDistance>
		{
			friend class Graphics_Server;

			struct CullDistanceData
			{
				int mVolumeSphereRadius;
				int mCullDistance;
				float mCullDistanceSqr;
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
			
			math::Vector3 mCameraPosition{};

			void AddCullDistance(int volumeSphereRadius, int cullDistance);
			void RemoveCullDistance(int volumeSphereSize, int cullDistance);
			void RemoveCullDistance(int index);

			float PickCullDistanceSqr(float sphereRadius);

			void Initialize();
			/// <summary>
			/// 
			/// </summary>

			void OnStartDraw();

			//void OnEndFrame();

			// void doom::graphics::CullDistance::OnEndFrame()
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
