#pragma once

#include <Core.h>

#include <fstream>

#include "clReflect_automation/clReflect/inc/clcpp/clcpp.h"

namespace dooms
{
	namespace reflection
	{
		namespace utility
		{
			class StdFile : public clcpp::IFile
			{
			public:
				StdFile(const std::filesystem::path& path);

				~StdFile();

				bool IsOpen() const;

				bool Read(void* dest, clcpp::size_type size) override;

			private:
				std::ifstream mFileSteam;
			};


			class Malloc : public clcpp::IAllocator
			{
				void* Alloc(clcpp::size_type size) override;

				void Free(void* ptr) override;
			};
		}
	}
}

