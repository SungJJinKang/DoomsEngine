#include "clReflectHelper.h"

#if CURRENT_CPP_VERSION == CPP_98_VERSION
#define CPP_VERSION_COMPILER_OPTION_FOR_CLANG "-std=c++98"
#elif CURRENT_CPP_VERSION == CPP_11_VERSION
#define CPP_VERSION_COMPILER_OPTION_FOR_CLANG "-std=c++11"
#elif CURRENT_CPP_VERSION == CPP_14_VERSION
#define CPP_VERSION_COMPILER_OPTION_FOR_CLANG "-std=c++14"
#elif CURRENT_CPP_VERSION == CPP_17_VERSION
#define CPP_VERSION_COMPILER_OPTION_FOR_CLANG "-std=c++17"
#elif CURRENT_CPP_VERSION == CPP_20_VERSION 
#define CPP_VERSION_COMPILER_OPTION_FOR_CLANG "-std=c++20"
#endif


inline static const char* clReflectAdditionalCompilerOptions
#if defined(__GNUC__)  || defined( __clang__)
= "-fno-rtti";
#elif defined(_MSC_VER)
= "-fdiagnostics-format=msvc -fms-extensions -fms-compatibility -mms-bitfields -fdelayed-template-parsing -fno-rtti";
#endif      // -fms-extensions is important!!

std::string doom::clReflectHelper::Generate_clReflectAdditionalCompilerOptions()
{
	std::string clReflectAdditionalCompilerOptionsString = clReflectAdditionalCompilerOptions;
	clReflectAdditionalCompilerOptionsString.append(" ");
	clReflectAdditionalCompilerOptionsString.append(CPP_VERSION_COMPILER_OPTION_FOR_CLANG);


	return clReflectAdditionalCompilerOptionsString;
}
