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

	if(IsValid(fixedMaterial))
	{
		fixedMaterial->BindMaterial();
	}
	
	mFixedMaterial = fixedMaterial;
}

void dooms::graphics::FixedMaterial::ClearFixedMaterial()
{
	if(IsValid(mFixedMaterial))
	{
		mFixedMaterial->UnBindMaterial();
	}

	mFixedMaterial = nullptr;
}
