#include "DrawState.h"

UINT64 dooms::graphics::drawState::BOUND_VERTEX_ARRAY_ID{ (UINT64)-1 };
UINT64 dooms::graphics::drawState::BOUND_VERTEX_BUFFER_ID[MAX_VERTEX_BUFFER_LAYOUT_COUNT]{ (UINT64)-1 };
UINT64 dooms::graphics::drawState::BOUND_INDEX_BUFFER_ID{ (UINT64)-1 };
