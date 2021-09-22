#include "FixedMaterial.h"

#include "Material.h"

doom::graphics::Material* doom::graphics::FixedMaterial::mFixedMaterial = nullptr;

bool doom::graphics::FixedMaterial::GetIsFixedMaterialExist()
{
	return FixedMaterial::mFixedMaterial != nullptr;
}

const doom::graphics::Material* doom::graphics::FixedMaterial::GetFixedMaterial()
{
	return mFixedMaterial;
}

void doom::graphics::FixedMaterial::SetFixedMaterial(Material* const fixedMaterial)
{
	ClearFixedMaterial();
	fixedMaterial->UseProgram();
	FixedMaterial::mFixedMaterial = fixedMaterial;
}

void doom::graphics::FixedMaterial::ClearFixedMaterial()
{
	FixedMaterial::mFixedMaterial = nullptr;
}
