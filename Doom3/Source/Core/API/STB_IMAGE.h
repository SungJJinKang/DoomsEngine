#pragma once



#ifdef BUILD_MODE // BUILD_VERSION
#define STBI_ASSERT // disable stb assert
#else

#endif
#include "../../../dependency/stb/stb_image.h"