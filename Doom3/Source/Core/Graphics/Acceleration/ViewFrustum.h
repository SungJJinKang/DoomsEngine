#pragma once

/*
#include "Core.h"
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix4x4.h>

namespace doom
{
	class Camera;
	class Renderer;

	namespace physics
	{
		class AABB3D;
		class Sphere;
	}

	namespace graphics
	{
		class ViewFrustum 
		{
			friend class Graphics_Server;
			friend class ::doom::Renderer;
			friend class ::doom::Camera;

		private:
			enum class ePlaneType
			{
				Left = 0,
				Right,
				Bottom,
				Top,
				Near,
				Far
			};

			/// <summary>
			/// normal : x, y, z
			/// distance : w
			/// </summary>
			math::Vector4 mPlanes[6];

			math::Vector3 mCameraPosition{};

			math::Vector3 mRightDirection{};
			math::Vector3 mUpDirection{};
			math::Vector3 mForwardDirection{};

			float mRatio{};
			float mTan{};
			float mTanHalf{};

			float mNearWidth{};
			float mNearHeight{};

			float mNearDistance{};
			float mFarDistance{};

			float mSphereFactorY{};
			float mSphereFactorX{};

			/// <summary>
				/// https://cgvr.informatik.uni-bremen.de/teaching/cg_literatur/lighthouse3d_view_frustum_culling/index.html
				/// </summary>
				/// <param name="viewProjectionMatrix"></param>
			void SetCamera(float fovInRadian, float ratio, float nearDistance, float farDistance);
			void UpdateLookAt(const math::Vector3& cameraPosition, const math::Vector3& forwardDirection, const math::Vector3& updirection);
			
			//use math::ExtractPlanesFromViewProjectionMatrix
			//void ExtractPlanesFromViewProjectionMatrix(const math::Matrix4x4& mvpMatrix, bool normalize);


		public:

			/// <summary>
			/// retrun true if intersect or inside in frustum
			/// </summary>
			/// <param name="aabb3D"></param>
			/// <returns></returns>
			bool IsInFrustum(const doom::physics::AABB3D& aabb3D);

			/// <summary>
			/// retrun true if intersect or inside in frustum
			/// </summary>
			/// <param name="sphere"></param>
			/// <returns></returns>
			bool IsInFrustum(const doom::physics::Sphere& sphere);

			/// <summary>
			/// retrun true if intersect or inside in frustum
			/// 
			/// https://cgvr.informatik.uni-bremen.de/teaching/cg_literatur/lighthouse3d_view_frustum_culling/index.html
			/// </summary>
			/// <param name="point"></param>
			/// <returns></returns>
			bool IsInFrustum(const math::Vector3& point);

			bool IsSphereVisible(Renderer* renderer);
			bool IsAABBVisible(Renderer* renderer);
		};
	}
	
}
*/