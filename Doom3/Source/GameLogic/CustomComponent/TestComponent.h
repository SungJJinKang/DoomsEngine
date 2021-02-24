#pragma once

#include <Doom_Core.h>

#include "../../Core/Physics/Ray.h"
#include "../../Core/Physics/Plane.h"
#include "../../Core/Physics/Line.h"
#include "../../Core/Physics/AABB.h"
#include "../../Core/Physics/Circle2D.h"
#include "../../Core/Physics/Sphere.h"
namespace doom
{
	class TestComponent : public PlainComponent
	{
	private:
		doom::physics::Line line{ math::Vector3(0.0f), math::Vector3(10.0f, 10.0f, 10.0f) };
		doom::physics::Plane plane{ 1, math::Vector3(1.0f, 0.0f, 0.0f) };
		doom::physics::AABB3D aabb{math::Vector3(0.0f), math::Vector3(5.0f, 5.0f, 5.0f)};
		doom::physics::Sphere sphere{math::Vector3(0.0f), 0.5f };
		doom::physics::Circle2D circle2d{ math::Vector2{0}, 0.5f };
	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
