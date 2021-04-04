#include "CullDistance.h"

#include <algorithm>

#include <Rendering/Camera.h>
#include <Transform.h>
#include <Rendering/Renderer/Renderer.h>
#include <Utility.h>

#include "Game/ConfigData.h"


void doom::graphics::CullDistance::AddCullDistance(int volumeSphereRadius, int cullDistance)
{
	D_ASSERT(volumeSphereRadius >= 0 && cullDistance >= 0);

	CullDistanceData cullDistanceData{};
	cullDistanceData.mVolumeSphereRadius = volumeSphereRadius;

	if (cullDistance != 0)
	{
		cullDistanceData.mCullDistance = cullDistance;
		cullDistanceData.mCullDistanceSqr = static_cast<float>(cullDistance * cullDistance);
	}
	else
	{ // 0 mean max
		cullDistanceData.mCullDistance = math::infinity<int>();
		cullDistanceData.mCullDistanceSqr = math::infinity<float>();
	}


	int index = 0;
	for (int i = 0; i < this->mCullDistanceSetting.size(); i++)
	{
		if (this->mCullDistanceSetting[i].mVolumeSphereRadius > volumeSphereRadius)
		{
			index = i + 1;
		}
	}

	this->mCullDistanceSetting.insert(this->mCullDistanceSetting.begin() + index, cullDistanceData);
}

void doom::graphics::CullDistance::RemoveCullDistance(int volumeSphereRadius, int cullDistance)
{
	D_ASSERT(volumeSphereRadius >= 0 && cullDistance >= 0);

	int index = 0;
	for (int i = 0; i < this->mCullDistanceSetting.size(); i++)
	{
		if (this->mCullDistanceSetting[i].mVolumeSphereRadius == volumeSphereRadius && this->mCullDistanceSetting[i].mCullDistance == cullDistance)
		{
			index = i;
			break;
		}
	}

	this->mCullDistanceSetting.erase(this->mCullDistanceSetting.begin() + index);
}

float doom::graphics::CullDistance::PickCullDistanceSqr(float sphereRadius)
{
	int radius = static_cast<int>(sphereRadius);
	D_ASSERT(radius >= 0);

	int mingap{ math::infinity<int>() };
	float cullDistanceSqr{ math::infinity<float>() };
	for (int i = 0; i < this->mCullDistanceSetting.size(); i++)
	{
		int gap = math::abs(this->mCullDistanceSetting[i].mVolumeSphereRadius - radius);
		if (gap < mingap)
		{
			mingap = gap;
			cullDistanceSqr = this->mCullDistanceSetting[i].mCullDistanceSqr;
		}
	}
	return cullDistanceSqr;
}

void doom::graphics::CullDistance::Initialize()
{
	std::string radiusKeyStr{ "CULL_DISTANCE0_VOLUME_RADIUS" };
	std::string distanceKeyStr{ "CULL_DISTANCE0_VOLUME_DISTANCE" };
	std::string distanceSqrKeyStr{ "CULL_DISTANCE0_VOLUME_DISTANCE_SQR" };

	const IniData& data = ConfigData::GetSingleton()->GetConfigData();
	for (int i = 1; i < 10; i++)
	{
		char a[2];
		_itoa_s(i, a, 2, 10);

		radiusKeyStr[13] = a[0];
		if(data.IsValueExist("Graphics", radiusKeyStr) == true)
		{
			int radius = data.GetValue<int>("Graphics", radiusKeyStr);

			distanceKeyStr[13] = a[0];
			distanceSqrKeyStr[13] = a[0];

			if (data.IsValueExist("Graphics", distanceKeyStr) == true)
			{
				int distance = data.GetValue<int>("Graphics", distanceKeyStr);
				this->AddCullDistance(radius, distance);
			}
			else if (data.IsValueExist("Graphics", distanceSqrKeyStr) == true)
			{
				float distanceSqr = data.GetValue<float>("Graphics", distanceSqrKeyStr);
				this->AddCullDistance(radius, static_cast<int>(math::sqrt(distanceSqr)));
			}
			else
			{
				NEVER_HAPPEN;
			}
		}
		else
		{
			break;
		}
	}
}

void doom::graphics::CullDistance::OnStartDraw()
{
	this->mCameraPosition = Camera::GetMainCamera()->GetTransform()->GetPosition();
}

bool doom::graphics::CullDistance::GetIsVisible(Renderer* renderer)
{
	float distanceSqr = (renderer->GetTransform()->GetPosition() - this->mCameraPosition).sqrMagnitude();

	float cullDistance = this->PickCullDistanceSqr(renderer->BVH_Sphere_Node_Object::GetWorldColliderCacheByReference()->mRadius);

	return distanceSqr < cullDistance;
}

void doom::graphics::CullDistance::PreComputeCulling()
{
}

void doom::graphics::CullDistance::RemoveCullDistance(int index)
{
	D_ASSERT(this->mCullDistanceSetting.size() > index);
	this->mCullDistanceSetting.erase(this->mCullDistanceSetting.begin() + index);
}

// void doom::graphics::CullDistance::SetIsDrawed(bool isDrawed)
// {
// 
// }
