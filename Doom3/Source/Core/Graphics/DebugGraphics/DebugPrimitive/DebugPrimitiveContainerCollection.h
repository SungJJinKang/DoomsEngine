#pragma once

#include <vector>
#include "DebugPrimitive2DLineContainer.h"
#include "DebugPrimitive2DPointContainer.h"
#include "DebugPrimitive2DTriangleContainer.h"
#include "DebugPrimitive3DLineContainer.h"
#include "DebugPrimitive3DPointContainer.h"
#include "DebugPrimitive3DTriangleContainer.h"


namespace dooms
{
	namespace graphics
	{
		struct DebugPrimitiveContainerCollection
		{
			DebugPrimitive2DLineContainer _DebugPrimitive2DLineContainer;
			DebugPrimitive2DPointContainer _DebugPrimitive2DPointContainer;
			DebugPrimitive2DTriangleContainer _DebugPrimitive2DTriangleContainer;

			DebugPrimitive3DLineContainer _DebugPrimitive3DLineContainer;
			DebugPrimitive3DPointContainer _DebugPrimitive3DPointContainer;
			DebugPrimitive3DTriangleContainer _DebugPrimitive3DTriangleContainer;

			const std::vector<DebugPrimitiveContainer*> DebugPrimitiveContainers
			{
				&_DebugPrimitive2DLineContainer,
				&_DebugPrimitive2DPointContainer,
				&_DebugPrimitive2DTriangleContainer,
				&_DebugPrimitive3DLineContainer,
				&_DebugPrimitive3DPointContainer,
				&_DebugPrimitive3DTriangleContainer
			};
		};
	}
}