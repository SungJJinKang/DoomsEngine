#pragma once



#ifdef BUILD_VERSION // BUILD_VERSION
#define STBI_ASSERT // disable stb assert
#else

#endif
#include "../thirdparty/stb_image.h"