#pragma once

#if defined(REFLECTION_ENABLED) && defined(__clcpp_parse__)

clcpp_reflect(int8_t);
clcpp_reflect(int16_t);
clcpp_reflect(int32_t);
clcpp_reflect(int64_t);
clcpp_reflect(INT32);
clcpp_reflect(uint8_t);
clcpp_reflect(uint16_t);
clcpp_reflect(uint32_t);
clcpp_reflect(uint64_t);
clcpp_reflect(intptr_t);
clcpp_reflect(uintptr_t);
clcpp_reflect(float);
clcpp_reflect(double);
clcpp_reflect(double);
clcpp_reflect(const char* const* const)
clcpp_reflect(const char* const*)
clcpp_reflect(const char* const)
clcpp_reflect(const char*)
clcpp_reflect(const char)
clcpp_reflect(char)
clcpp_reflect(char*)
clcpp_reflect(const char**)
clcpp_reflect(char**)
clcpp_reflect(std::unique_ptr)
clcpp_reflect(std::unique_ptr<uint32_t[]>)
clcpp_reflect(uint32_t[])
clcpp_reflect(std::string)
clcpp_reflect(std::vector)
clcpp_reflect(std::unordered_map)
clcpp_reflect(std::map)
clcpp_reflect(std::set)
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
D_NAMESPACE(dooms::userinput)
D_NAMESPACE(math)

#endif