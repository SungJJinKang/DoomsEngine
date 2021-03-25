#pragma once

#include "Core.h"
#include "Simple_SingleTon/Singleton.h"

#include "utility/BVH/BVH.h"
#include "Culling.h"

#define VIEWFRUSTUM_BVH_MAX_NODE_COUNT 30000

namespace doom
{
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
		class ViewFrustumCulling : public ICulling, public ISingleton<ViewFrustumCulling>
		{
			friend class ::doom::Renderer;
			friend class Graphics_Server;

		private:
			BVHSphere mBVHSphere { VIEWFRUSTUM_BVH_MAX_NODE_COUNT };
			

			bool IsInFrustumWithBVH(const physics::Sphere& sphere);
			/// <summary>
		
			/// <summary>
			/// Travel BVH recursively, set IsVisible Value
			/// if Ancester sphere isn't visible, desesters is all invisible
			/// </summary>
			virtual void PreComputeCulling() override;
		};
	}
}

