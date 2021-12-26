#pragma once

#include "DebugPrimitiveContainer.h"

namespace dooms
{
	namespace graphics
	{
		class DebugPrimitiveTriangleContainer : public DebugPrimitiveContainer
		{

		protected:

			UINT32 GetVertexCountPerPrimitive() const override;
			UINT32 GetComponentCountPerPrimitive() const override;

		public:

			bool Is3DPrimitive() const = 0;
			ePrimitiveType GetPrimitiveType() const override;

			void AddColoredTriangleData
			(
				const math::Vector3 point1,
				const math::Vector3 point2,
				const math::Vector3 point3,
				const eColor color
			);


			void AddColoredTriangleData
			(
				const math::Vector3 point1,
				const math::Vector3 point2,
				const math::Vector3 point3,
				const math::Vector4 color
			);
		};
	}
}

