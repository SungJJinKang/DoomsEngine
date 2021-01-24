#pragma once

#ifdef DEBUG_MODE

#if defined(_WIN32) || defined(_WIN64)
#define CURRENTPATH "C:/Doom3FromScratch/Doom3/"
#elif __APPLE__
#define CURRENTPATH /Users/sungjinkang/openglstudy/glfwStudys/
#endif

#else
#endif

#define GET_RELATIVE_PATH(x) CURRENTPATH x

#define ASSET_FOLDER_DIRECTORY GET_RELATIVE_PATH("Assets/")