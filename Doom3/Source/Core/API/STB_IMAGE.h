#pragma once



#ifdef RELEASE_MODE // BUILD_VERSION
#define STBI_ASSERT // disable stb assert
#else

#endif
#include <stb_image.h>
#include <stb_dxt.h>