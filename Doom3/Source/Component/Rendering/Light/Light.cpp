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

void doom::Light::SetIntensity(float intensity)
{
	mIntensity = intensity;
}

void doom::Light::SetIndirectMultiplier(float indirectMultiplier)
{
	mIndirectMultiplier = indirectMultiplier;
}

void doom::Light::SetColor(const math::Vector4& color)
{
	mColor = color;
}

float doom::Light::GetIntensity()
{
	return mIntensity;
}

float doom::Light::GetIndirectMultiplier()
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
