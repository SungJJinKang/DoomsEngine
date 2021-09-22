#pragma once


namespace doom
{
	namespace graphics
	{
		class Material;

		class FixedMaterial
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

