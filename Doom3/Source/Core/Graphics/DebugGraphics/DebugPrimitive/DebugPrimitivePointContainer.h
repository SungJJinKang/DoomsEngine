#pragma once


#include "DebugPrimitiveContainer.h"

namespace dooms
{
	namespace graphics
	{
		class DebugPrimitivePointContainer : public DebugPrimitiveContainer
		{

		protected:

			UINT32 GetVertexCountPerPrimitive() const override;
			UINT32 GetComponentCountPerPrimitive() const override;

		public:

			bool Is3DPrimitive() const = 0;
			ePrimitiveType GetPrimitiveType() const override;

			void AddColoredPointData
			(
				const math::Vector3 point,
				const eColor color
			);


			void AddColoredPointData
			(
				const math::Vector3 point,
				const math::Vector4 color
			);
		};
	}
}


