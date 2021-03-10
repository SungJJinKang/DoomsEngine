#pragma once

#ifdef DEBUG_MODE
#include "../Logger/Logger.h"
#define D_DEBUG_LOG(...)  doom::logger::Logger::Log(##__VA_ARGS__)

#define D_DEBUG_DRAW_2D_LINE(...)  doom::logger::Logger::Draw2DLine(##__VA_ARGS__)
#define D_DEBUG_DRAW_3D_LINE(...)  doom::logger::Logger::Draw3DLine(##__VA_ARGS__)

#define D_DEBUG_DRAW_2D_TRIANGLE(...)  doom::logger::Logger::Draw2DTriangle(##__VA_ARGS__)
#define D_DEBUG_DRAW_3D_TRIANGLE(...)  doom::logger::Logger::Draw3DTriangle(##__VA_ARGS__)
#else
#define D_DEBUG_LOG(...)

#define D_DEBUG_DRAW_2D_LINE(...)
#define D_DEBUG_DRAW_3D_LINE(...)

#define D_DEBUG_DRAW_2D_TRIANGLE(...)
#define D_DEBUG_DRAW_3D_TRIANGLE(...)
#endif
