#pragma once

#ifdef DEBUG_MODE
#include "../Logger/Logger.h"
#define D_DEBUG_LOG(...)  doom::logger::Debug::Log(##__VA_ARGS__)

#define D_DEBUG_DRAW_2D_LINE(...)  doom::logger::Debug::Draw2DLine(##__VA_ARGS__)
#define D_DEBUG_DRAW_3D_LINE(...)  doom::logger::Debug::Draw3DLine(##__VA_ARGS__)

#define D_DEBUG_DRAW_2D_TRIANGLE(...)  doom::logger::Debug::Draw2DTriangle(##__VA_ARGS__)
#define D_DEBUG_DRAW_3D_TRIANGLE(...)  doom::logger::Debug::Draw3DTriangle(##__VA_ARGS__)
#else
#define D_DEBUG_LOG(...)

#define D_DEBUG_DRAW_2D_LINE(...)  
#define D_DEBUG_DRAW_3D_LINE(...)  

#define D_DEBUG_DRAW_2D_TRIANGLE(...)  
#define D_DEBUG_DRAW_3D_TRIANGLE(...)  
#endif
