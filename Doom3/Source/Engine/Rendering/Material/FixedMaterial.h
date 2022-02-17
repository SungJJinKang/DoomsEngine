#pragma once

#include <Core.h>

namespace dooms
{
	namespace graphics
	{
		class Material;

		class DOOM_API D_CLASS FixedMaterial
		{

		private:

			static Material* mFixedMaterial;

		public:

			static bool GetIsFixedMaterialExist();
			static const Material* GetFixedMaterial();
			static void SetFixedMaterial(Material* const fixedMaterial);
			static void ClearFixedMaterial();

		};
	}
}

