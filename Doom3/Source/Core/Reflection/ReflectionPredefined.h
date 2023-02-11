#pragma once

#include <TypeDef.h>

#if (REFLECTION_ENABLED && defined(__clcpp_parse__))

D_REFLECT_ALL(bool);
D_REFLECT_ALL(INT8);
D_REFLECT_ALL(INT16);
D_REFLECT_ALL(INT32);
D_REFLECT_ALL(INT64);
D_REFLECT_ALL(UINT8);
D_REFLECT_ALL(UINT16);
D_REFLECT_ALL(UINT32);
D_REFLECT_ALL(UINT64);
D_REFLECT_ALL(intptr_t);
D_REFLECT_ALL(uintptr_t);
D_REFLECT_ALL(float);
D_REFLECT_ALL(double);
D_REFLECT_ALL(const char* const* const)
D_REFLECT_ALL(const char* const*)
D_REFLECT_ALL(const char* const)
D_REFLECT_ALL(const char*)
D_REFLECT_ALL(const char)
D_REFLECT_ALL(char)
D_REFLECT_ALL(unsigned char)
D_REFLECT_ALL(char*)
D_REFLECT_ALL(const char**)
D_REFLECT_ALL(char**)
D_REFLECT_ALL(std::unique_ptr)
D_REFLECT_ALL(dooms::graphics::PicktureInPickture)
D_REFLECT_ALL(std::unique_ptr<dooms::graphics::PicktureInPickture>)
D_REFLECT_ALL(std::shared_ptr)
D_REFLECT_ALL(std::unique_ptr<uint32_t[]>)
D_REFLECT_ALL(uint32_t[])
D_REFLECT_ALL(std::string)
D_REFLECT_ALL(std::vector)
D_REFLECT_ALL(std::unordered_map)
D_REFLECT_ALL(std::map)
D_REFLECT_ALL(std::set)
D_NAMESPACE(dooms)
D_NAMESPACE(dooms::graphics)
D_NAMESPACE(dooms::random)
D_NAMESPACE(dooms::asset)
D_NAMESPACE(dooms::assetImporter)
D_NAMESPACE(dooms::assetExporter)
D_NAMESPACE(dooms::reflection)
D_NAMESPACE(dooms::resource)
D_NAMESPACE(dooms::physics)
D_NAMESPACE(dooms::time)
D_NAMESPACE(dooms::ui)
D_NAMESPACE(dooms::logger)
D_NAMESPACE(dooms::memory)
D_NAMESPACE(dooms::userinput)
D_NAMESPACE(dooms::plugin)
D_NAMESPACE(dooms::thread)
D_REFLECT_ALL(dooms::reflection)

#endif