#include "CullDistance.h"

#include <Rendering/Camera.h>
#include <Transform.h>
#include <Rendering/Renderer/Renderer.h>
#include <Utility.h>

#include "Game/ConfigData.h"


void dooms::graphics::CullDistance::AddCullDistance(INT32 volumeSphereRadius, INT32 cullDistance)
{
	D_ASSERT(volumeSphereRadius >= 0 && cullDistance >= 0);

	CullDistanceData cullDistanceData{};
	cullDistanceData.mVolumeSphereRadius = volumeSphereRadius;

	if (cullDistance != 0)
	{
		cullDistanceData.mCullDistance = cullDistance;
		cullDistanceData.mCullDistanceSqr = static_cast<FLOAT32>(cullDistance * cullDistance);
	}
	else
	{ // 0 mean max
		cullDistanceData.mCullDistance = math::infinity<INT32>();
		cullDistanceData.mCullDistanceSqr = math::infinity<FLOAT32>();
	}


	INT32 index = 0;
	for (INT32 i = 0; i < mCullDistanceSetting.size(); i++)
	{
		if (mCullDistanceSetting[i].mVolumeSphereRadius > volumeSphereRadius)
		{
			index = i + 1;
		}
	}

	mCullDistanceSetting.insert(mCullDistanceSetting.begin() + index, cullDistanceData);
}

void dooms::graphics::CullDistance::RemoveCullDistance(INT32 volumeSphereRadius, INT32 cullDistance)
{
	D_ASSERT(volumeSphereRadius >= 0 && cullDistance >= 0);

	INT32 index = 0;
	for (INT32 i = 0; i < mCullDistanceSetting.size(); i++)
	{
		if (mCullDistanceSetting[i].mVolumeSphereRadius == volumeSphereRadius && mCullDistanceSetting[i].mCullDistance == cullDistance)
		{
			index = i;
			break;
		}
	}

	mCullDistanceSetting.erase(mCullDistanceSetting.begin() + index);
}

FLOAT32 dooms::graphics::CullDistance::PickCullDistanceSqr(FLOAT32 sphereRadius)
{
	INT32 radius = static_cast<INT32>(sphereRadius);
	D_ASSERT(radius >= 0);

	INT32 mingap{ math::infinity<INT32>() };
	FLOAT32 cullDistanceSqr{ math::infinity<FLOAT32>() };
	for (INT32 i = 0; i < mCullDistanceSetting.size(); i++)
	{
		INT32 gap = std::abs(mCullDistanceSetting[i].mVolumeSphereRadius - radius);
		if (gap < mingap)
		{
			mingap = gap;
			cullDistanceSqr = mCullDistanceSetting[i].mCullDistanceSqr;
		}
	}
	return cullDistanceSqr;
}

void dooms::graphics::CullDistance::Initialize()
{
	std::string radiusKeyStr{ "CULL_DISTANCE0_VOLUME_RADIUS" };
	std::string distanceKeyStr{ "CULL_DISTANCE0_VOLUME_DISTANCE" };
	std::string distanceSqrKeyStr{ "CULL_DISTANCE0_VOLUME_DISTANCE_SQR" };

	const IniData& data = ConfigData::GetSingleton()->GetConfigData();
	for (INT32 i = 1; i < 10; i++)
	{
		char a[2];
		_itoa_s(i, a, 2, 10);

		radiusKeyStr[13] = a[0];
		if(data.IsValueExist("Graphics", radiusKeyStr) == true)
		{
			INT32 radius = data.GetValue<INT32>("Graphics", radiusKeyStr);

			distanceKeyStr[13] = a[0];
			distanceSqrKeyStr[13] = a[0];

			if (data.IsValueExist("Graphics", distanceKeyStr) == true)
			{
				INT32 distance = data.GetValue<INT32>("Graphics", distanceKeyStr);
				AddCullDistance(radius, distance);
			}
			else if (data.IsValueExist("Graphics", distanceSqrKeyStr) == true)
			{
				FLOAT32 distanceSqr = data.GetValue<FLOAT32>("Graphics", distanceSqrKeyStr);
				AddCullDistance(radius, static_cast<INT32>(std::sqrt(distanceSqr)));
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

void dooms::graphics::CullDistance::OnStartDraw()
{
	mCameraPosition = Camera::GetMainCamera()->GetTransform()->GetPosition();
}

bool dooms::graphics::CullDistance::GetIsVisible(Renderer* renderer)
{
	FLOAT32 distanceSqr = (renderer->GetTransform()->GetPosition() - mCameraPosition).sqrMagnitude();

	FLOAT32 cullDistance = PickCullDistanceSqr(renderer->BVH_AABB3D_Node_Object::GetWorldCollider()->GetDiagonarLineLength());

	return distanceSqr < cullDistance;
}

void dooms::graphics::CullDistance::PreComputeCulling()
{
}

void dooms::graphics::CullDistance::RemoveCullDistance(INT32 index)
{
	D_ASSERT(mCullDistanceSetting.size() > index);
	mCullDistanceSetting.erase(mCullDistanceSetting.begin() + index);
}

// void dooms::graphics::CullDistance::SetIsDrawed(bool isDrawed)
// {
// 
// }
