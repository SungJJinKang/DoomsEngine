#pragma once



#ifdef BUILD_MODE // BUILD_VERSION
#define STBI_ASSERT // disable stb assert
#else

#endif
#include "../thirdparty/stb_image.h"