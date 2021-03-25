#pragma once

namespace doom
{
	namespace graphics
	{
		class ICulling
		{

		protected:
			/// <summary>
			/// Using acceleration structure(BVH, KDTree), We can precompute rendered object is isvisible
			/// When ancester isn't visible, descents of that node is all invisible
			/// </summary>
			virtual void PreComputeCulling() = 0;

		};
	}
}