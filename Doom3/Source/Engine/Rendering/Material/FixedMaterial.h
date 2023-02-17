#pragma once

#include <Core.h>
#include <SingleTon/Singleton.h>

namespace dooms
{
	namespace graphics
	{
		class Material;

		class DOOM_API D_CLASS FixedMaterial : public ISingleton<FixedMaterial>
		{

		private:

			Material* mFixedMaterial;

		public:

			FixedMaterial();

			bool GetIsFixedMaterialExist();
			const Material* GetFixedMaterial();
			void SetFixedMaterial(Material* const fixedMaterial);
			void ClearFixedMaterial();

		};
	}
}

