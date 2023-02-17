#include "Transform.h"

#include <sstream>

#include <Scene/Entity.h>

void dooms::Transform::SetPosition()
{
	SetPosition(mPosition);
}

void dooms::Transform::SetRotation()
{
	SetRotation(mRotation);
}

void dooms::Transform::SetScale()
{
	SetScale(mScale);
}

void dooms::Transform::InitComponent()
{
	SetPosition(mPosition);
	SetRotation(mRotation);
	SetScale(mScale);
}

void dooms::Transform::UpdateComponent()
{
}

void dooms::Transform::OnEndOfFrame_Component()
{
	
	mLastFramePosition = mPosition;
}

void dooms::Transform::OnDestroy()
{
	
}

void dooms::Transform::OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField)
{
	Base::OnChangedByGUI(dFieldOfChangedField);

	if(std::strcmp(dFieldOfChangedField.GetFieldName(), "mTransformCoreData") == 0)
	{
		SetPosition();
	}
	else if (std::strcmp(dFieldOfChangedField.GetFieldName(), "mScale") == 0)
	{
		SetScale();
	}
	else if (std::strcmp(dFieldOfChangedField.GetFieldName(), "mRotation") == 0)
	{
		SetRotation();
	}

}


bool dooms::Transform::IsEntityMovable() const
{
	return GetOwnerEntity()->GetEntityMobility() != eEntityMobility::Static;
}

dooms::Transform::Transform(): mLastFramePosition{ 0.0f }
{
	// 			SetPosition(mPosition);
	// 			SetRotation(mRotation);
	// 			SetScale(mScale);
}

std::string dooms::Transform::ToString()
{
	std::stringstream sStream;
	sStream << "Position : ";
	sStream << mPosition[0];
	sStream << ' ';
	sStream << mPosition[1];
	sStream << ' ';
	sStream << mPosition[2];
	sStream << '\n';
	sStream << "Rotation : ";
	auto rotEuler = math::Quaternion::QuaternionToEulerAngle(mRotation);
	sStream << math::RADIAN_TO_DEGREE * rotEuler.x;
	sStream << ' ';
	sStream << math::RADIAN_TO_DEGREE * rotEuler.y;
	sStream << ' ';
	sStream << math::RADIAN_TO_DEGREE * rotEuler.z;
	sStream << ' ';
	sStream << '\n';
	sStream << "Scale : ";
	sStream << mScale[0];
	sStream << ' ';
	sStream << mScale[1];
	sStream << ' ';
	sStream << mScale[2];
	sStream << '\n';
	return sStream.str();
}

void dooms::Transform::LookAt(const Transform& target, const math::Vector3& up)
{
	D_ASSERT(IsEntityMovable());

	if (IsEntityMovable())
	{
		SetRotation(static_cast<math::Quaternion>(math::lookAt(mPosition, target.mPosition, up)));
	}
}

void dooms::Transform::LookAt(const math::Vector3& targetPoint, const math::Vector3& up)
{
	D_ASSERT(IsEntityMovable());

	if (IsEntityMovable())
	{
		SetRotation(static_cast<math::Quaternion>(math::lookAt(mPosition, targetPoint, up)));
	}
}

void dooms::Transform::Rotate(const math::Quaternion& quat, const eSpace& relativeTo)
{
	D_ASSERT(IsEntityMovable());

	if (IsEntityMovable())
	{
		if (relativeTo == eSpace::Self)
		{
			SetRotation(mRotation * quat);
		}
		else if (relativeTo == eSpace::World)
		{
			SetRotation(quat * mRotation);
		}
	}
}

void dooms::Transform::Rotate(const math::Vector3& eulerAngles, const eSpace& relativeTo)
{
	D_ASSERT(IsEntityMovable());

	if (IsEntityMovable())
	{
		if (relativeTo == eSpace::Self)
		{
			SetRotation(mRotation * math::Quaternion(eulerAngles));
		}
		else if (relativeTo == eSpace::World)
		{
			SetRotation(math::Quaternion(eulerAngles) * mRotation);
		}
	}
}

void dooms::Transform::RotateAround(const math::Vector3& centerPoint, const math::Vector3& axis, const FLOAT32 angle)
{
	D_ASSERT(IsEntityMovable());

	if (IsEntityMovable())
	{
		math::Vector3 worldPos = GetPosition();
		const math::Quaternion q = math::Quaternion::angleAxis(angle, axis);
		math::Vector3 dif = worldPos - centerPoint;
		dif = q * dif;
		worldPos = centerPoint + dif;
		SetPosition(worldPos);

		SetRotation(math::Quaternion(angle * static_cast<FLOAT32>(math::DEGREE_TO_RADIAN), axis));
	}
}


