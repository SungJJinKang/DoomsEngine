#pragma once

#include <Core.h>
#include "FVertexBufferLayout.h"

namespace dooms
{
	namespace graphics
	{
		namespace drawState
		{
			/**
			 * \brief only used for OPENGL
			 */
			extern UINT64 BOUND_VERTEX_ARRAY_ID;

			/**
			 * \brief for OPENGL, Only first element is used
			 */
			extern UINT64 BOUND_VERTEX_BUFFER_ID[MAX_VERTEX_BUFFER_LAYOUT_COUNT];
			/**
			 * \brief INDEX ( ELEMENT BUFFER )
			 */
			extern UINT64 BOUND_INDEX_BUFFER_ID;
		}
	}
}
