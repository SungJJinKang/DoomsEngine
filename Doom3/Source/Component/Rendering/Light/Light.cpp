#include "Light.h"

void doom::Light::InitComponent()
{
	this->CreateTransformDirtyReceiver();
	this->AddLocalDirtyToTransformDirtyReceiver(bmIsLightUboDirty);
}

void doom::Light::UpdateComponent()
{

}

void doom::Light::OnEndOfFrame_Component()
{

}

void doom::Light::SetIntensity(float intensity)
{
	this->mIntensity = intensity;
}

void doom::Light::SetIndirectMultiplier(float indirectMultiplier)
{
	this->mIndirectMultiplier = indirectMultiplier;
}

void doom::Light::SetColor(const math::Vector4& color)
{
	this->mColor = color;
}

float doom::Light::GetIntensity()
{
	return this->mIntensity;
}

float doom::Light::GetIndirectMultiplier()
{
	return this->mIndirectMultiplier;
}

math::Vector4 doom::Light::GetColor()
{
	return this->mColor;
}

math::Vector4 doom::Light::GetRadiance()
{
	return this->mColor * this->mIntensity;
}

const math::Vector4& doom::Light::GetColor() const
{
	return this->mColor;
}
