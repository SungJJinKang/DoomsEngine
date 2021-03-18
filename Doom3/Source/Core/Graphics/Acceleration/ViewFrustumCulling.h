#pragma once

#include "Core.h"
#include "utility/BVH/BVH.h"

#include <Matrix4x4.h>

#include "Simple_SingleTon/Singleton.h"

#include "Collider/AABB.h"
#include "Collider/Sphere.h"


#define VIEWFRUSTUM_BVH_MAX_NODE_COUNT 30000

namespace doom
{
	class Camera;
	class Renderer;

	namespace graphics
	{
		/// <summary>
		/// View Frustum Culling Implementation
		/// 
		/// reference : https://cgvr.informatik.uni-bremen.de/teaching/cg_literatur/lighthouse3d_view_frustum_culling/index.html
		/// 
		/// 
		/// Study this github : https://gist.github.com/podgorskiy/e698d18879588ada9014768e3e82a644 
		/// ...
		/// 
		/// AVX, SSE 사용하자, 멀티스레드 사용 X
		/// 
		/// Do something for accelerate View Frustum Culling
		/// KD트리는 렌더링 성능이 가장 좋지만 동적인 물체에 좋지 않다.
		/// BVH는 성능은 좀 떨어지지만, 동적인 물체에 대응이 가능하다.
		/// BVH는 KD트리를 포함한다고 볼 수 있다.
		/// https://blog.hybrid3d.dev/2019-03-22-raytracing-kdtree-bvh
		/// </summary>
		class ViewFrustumCulling : public ISingleton<ViewFrustumCulling>
		{
			friend class Graphics_Server;
			friend class ::doom::Renderer;
			friend class ::doom::Camera;

		private:
			BVHSphere mBVHSphere { VIEWFRUSTUM_BVH_MAX_NODE_COUNT };
			

			enum class ePlaneType
			{
				Left = 0,
				Right,
				Bottom,
				Top,
				Near,
				Far
			};

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
			
		public:

			/// <summary>
			/// retrun true if intersect or inside in frustum
			/// </summary>
			/// <param name="aabb3D"></param>
			/// <returns></returns>
			bool IsInFrustum(const physics::AABB3D& aabb3D);

			/// <summary>
			/// retrun true if intersect or inside in frustum
			/// </summary>
			/// <param name="sphere"></param>
			/// <returns></returns>
			bool IsInFrustum(const physics::Sphere& sphere);
			bool IsInFrustumWithBVH(const physics::Sphere& sphere);
			/// <summary>
			/// retrun true if intersect or inside in frustum
			/// 
			/// https://cgvr.informatik.uni-bremen.de/teaching/cg_literatur/lighthouse3d_view_frustum_culling/index.html
			/// </summary>
			/// <param name="point"></param>
			/// <returns></returns>
			bool IsInFrustum(const math::Vector3& point);

			bool IsVisible(Renderer* renderer);

			/// <summary>
			/// Travel BVH recursively, set IsVisible Value
			/// if Ancester sphere isn't visible, desesters is all invisible
			/// </summary>
			void PreUpdateBVH();
		};
	}
}

