#pragma once
#include "../Core.h"



#include <assimp/Importer.hpp>

#ifdef ASSIMP_DETAIL
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Exporter.hpp>
#endif

#if defined(DEBUG_MODE) && defined(ASSIMP_DETAIL)
#include <assimp/DefaultLogger.hpp>
#endif
