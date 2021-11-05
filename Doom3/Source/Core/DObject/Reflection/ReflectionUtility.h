#pragma once

#include <Core.h>

#include <fstream>

#include "clReflect_automation/clReflect/inc/clcpp/clcpp.h"

namespace doom
{
	namespace reflection
	{
		namespace utility
		{
			class StdFile : public clcpp::IFile
			{
			public:
				StdFile(const char* filename)
				{
					mFileSteam.open(filename, std::ios_base::in | std::ios_base::binary);
					D_ASSERT(mFileSteam.is_open() == true);
				}

				~StdFile()
				{
					if (mFileSteam.is_open() == true)
					{
						mFileSteam.close();
					}
				}

				bool IsOpen() const
				{
					return mFileSteam.is_open();
				}

				bool Read(void* dest, clcpp::size_type size)
				{
					return static_cast<bool>(mFileSteam.read(static_cast<char*>(dest), size));
				}

			private:
				std::ifstream mFileSteam;
			};


			class Malloc : public clcpp::IAllocator
			{
				void* Alloc(clcpp::size_type size)
				{
					return malloc(size);
				}
				void Free(void* ptr)
				{
					free(ptr);
				}
			};
		}
	}
}

