#pragma once
#include "../Core/CoreComponent/CoreComponent.h"
#include "../Core/Math/LightMath_Cpp/Quaternion.h"
#include "../Core/Math/LightMath_Cpp/Vector3.h"
#include "../Core/Math/LightMath_Cpp/Matrix4x4.h"

namespace doom
{
	enum class eSpace
	{
		World,
		Self
	};

	class Transform : public CoreComponent 
	{
	private:
		math::Matrix4x4 mModelMatrixCache;
		math::Matrix4x4 mLocalToWorldMatrix{ 1.0f };
		math::Matrix4x4 mWorldToLocalMatrix{ 1.0f };

		math::Vector3 mPosition;
		math::Quaternion mRotation;
		math::Vector3 mScale;
	public:

		void SetPosition(const math::Vector3& position);
		void SetRotation(const math::Quaternion& rotation);
		void SetScale(const math::Vector3& scale);
		math::Vector3 GetPosition();
		math::Quaternion GetRotation();
		math::Vector3 GetScale();

		math::Matrix4x4 GetModelMatrix();
		math::Matrix4x4 GetViewMatrix();

		constexpr math::Vector3 forward() const;
		constexpr math::Vector3 right() const;
		constexpr math::Vector3 up() const;

		constexpr void LookAt(const Transform& target, const math::Vector3& up);
		constexpr void Rotate(const math::Vector3& eulerAngles, const eSpace& relativeTo);
		constexpr void RotateAround(const math::Vector3& point, const math::Vector3& axis, float angle);

		constexpr math::Vector3 TransformDirection(const math::Vector3& direction) const;
		constexpr math::Vector3 TransformPoint(const math::Vector3& point) const;
		constexpr math::Vector3 TransformVector(const math::Vector3& vector) const;
		constexpr void Translate(const math::Vector3& translation, const eSpace& relativeTo);
	};

}