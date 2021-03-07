#pragma once

#include <Doom_Core.h>

#include "../../Core/Physics/Collider/Ray.h"
#include "../../Core/Physics/Collider/Plane.h"
#include "../../Core/Physics/Collider/Line.h"
#include "../../Core/Physics/Collider/AABB.h"
#include "../../Core/Physics/Collider/Circle2D.h"
#include "../../Core/Physics/Collider/Sphere.h"
namespace doom
{
	class TestComponent : public PlainComponent
	{
	private:
		doom::physics::Line line{ math::Vector3(0.0f), math::Vector3(10.0f, 10.0f, 10.0f) };
		doom::physics::Plane plane{ 10, math::Vector3(-2.0f, 0.0f, 0.0f) };
		doom::physics::AABB3D aabb{math::Vector3(20.0f), math::Vector3(25.0f)};
		doom::physics::Sphere sphere{math::Vector3(-15.0f, 0.0f, 0.0f), 5.0f };
		doom::physics::Circle2D circle2d{ math::Vector2{0}, 0.5f };
	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
