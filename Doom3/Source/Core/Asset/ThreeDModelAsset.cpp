#include "ThreeDModelAsset.h"

#include <type_traits>

static_assert(std::is_standard_layout_v<doom::MeshVertexData>);
