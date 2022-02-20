#include "FixedMaterial.h"

#include "Material.h"

dooms::graphics::FixedMaterial::FixedMaterial()
	: mFixedMaterial(nullptr)
{
}

bool dooms::graphics::FixedMaterial::GetIsFixedMaterialExist()
{
	return FixedMaterial::mFixedMaterial != nullptr;
}

const dooms::graphics::Material* dooms::graphics::FixedMaterial::GetFixedMaterial()
{
	return mFixedMaterial;
}

void dooms::graphics::FixedMaterial::SetFixedMaterial(Material* const fixedMaterial)
{
	ClearFixedMaterial();
	fixedMaterial->BindMaterial();
	FixedMaterial::mFixedMaterial = fixedMaterial;
}

void dooms::graphics::FixedMaterial::ClearFixedMaterial()
{
	FixedMaterial::mFixedMaterial = nullptr;
}
