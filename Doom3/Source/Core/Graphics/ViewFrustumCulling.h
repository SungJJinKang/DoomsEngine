#pragma once
#include "utility/BVH/BVH.h"

#define VIEWFRUSTUM_BVH_MAX_NODE_COUNT 1000

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
		/// 
		/// KD트리는 렌더링 성능이 가장 좋지만 동적인 물체에 좋지 않다.
		/// BVH는 성능은 좀 떨어지지만, 동적인 물체에 대응이 가능하다.
		/// BVH는 KD트리를 포함한다고 볼 수 있다.
		/// https://blog.hybrid3d.dev/2019-03-22-raytracing-kdtree-bvh
		/// </summary>
		class ViewFrustumCulling
		{
			friend class Graphics_Server;
			friend class ::doom::Renderer;

		private:
			BVH3D mViewFrustumBVH{ VIEWFRUSTUM_BVH_MAX_NODE_COUNT };
			void DebugDraw();
		public:
		};
	}
}

