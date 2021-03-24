#pragma once

#include <vector>
#include <utility>

#include <Vector3.h>

#include "Simple_SingleTon/Singleton.h"

namespace doom
{
	class Renderer;
	namespace graphics
	{
	

		/// <summary>
		/// https://docs.unrealengine.com/en-US/RenderingAndGraphics/VisibilityCulling/CullDistanceVolume/index.html
		/// </summary>
		class CullDistance : ISingleton<CullDistance>
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

			float PickCullDistanceSqr(int sphereRadius);

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

			/*void SetIsDrawed(bool isDrawed);*/
		};


	}
}
