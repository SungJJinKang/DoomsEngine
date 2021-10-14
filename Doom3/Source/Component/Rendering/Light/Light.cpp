#include "Light.h"

void doom::Light::InitComponent()
{
	AddLocalDirtyToTransformDirtyReceiver(bmIsLightUboDirty);
}

void doom::Light::UpdateComponent()
{

}

void doom::Light::OnEndOfFrame_Component()
{

}

doom::Light::~Light()
{
}

void doom::Light::SetIntensity(FLOAT32 intensity)
{
	mIntensity = intensity;
}

void doom::Light::SetIndirectMultiplier(FLOAT32 indirectMultiplier)
{
	mIndirectMultiplier = indirectMultiplier;
}

void doom::Light::SetColor(const math::Vector4& color)
{
	mColor = color;
}

FLOAT32 doom::Light::GetIntensity()
{
	return mIntensity;
}

FLOAT32 doom::Light::GetIndirectMultiplier()
{
	return mIndirectMultiplier;
}

math::Vector4 doom::Light::GetColor()
{
	return mColor;
}

math::Vector4 doom::Light::GetRadiance()
{
	return mColor * mIntensity;
}

const math::Vector4& doom::Light::GetColor() const
{
	return mColor;
}
