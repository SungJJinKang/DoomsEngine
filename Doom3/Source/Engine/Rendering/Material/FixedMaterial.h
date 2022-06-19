#pragma once

#include <Core.h>
#include <Simple_SingleTon/Singleton.h>

namespace dooms
{
	namespace graphics
	{
		class Material;

		class FixedMaterial
		{

		public:
			
			static void SetFixedMaterial(Material* const InFixedMaterial);
			static void ClearFixedMaterial();

		};
	}
}

