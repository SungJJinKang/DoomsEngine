#pragma once

#include <Core.h>

namespace dooms
{
	namespace graphics
	{
		class ICulling : public DObject
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