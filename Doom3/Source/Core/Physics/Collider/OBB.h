#pragma once

#include "../Core.h"
#include <Vector3.h>
#include "Collider.h"
#include <Matrix4x4.h>

namespace doom
{
	namespace physics
	{
		/// <summary>
		/// 
		/// </summary>
		class DOOM_API OBB : public Collider
		{
			FORCE_INLINE virtual void* data() final
			{
				return nullptr;
			}

			FORCE_INLINE virtual const void* data() const final
			{
				return nullptr;
			}
		};
	}
}