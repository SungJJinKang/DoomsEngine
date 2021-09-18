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

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
