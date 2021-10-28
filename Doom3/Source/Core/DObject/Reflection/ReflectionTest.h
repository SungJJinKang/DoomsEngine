#pragma once

#include <cassert>

#include "clReflect/inc/clcpp/clcpp.h"
#include <cstring>
#include <fstream>
#include <ios>

#include <DObject/DObject.h>
#include "Macros/Path.h"
#include "Macros/Assert.h"

namespace clReflectTest
{

	class StdFile : public clcpp::IFile
	{
	public:
		StdFile(const char* filename)
		{
			mFileSteam.open(filename, std::ios_base::in | std::ios_base::binary);
			assert(mFileSteam.is_open() == true);
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


	inline extern volatile int test()
	{
		std::filesystem::path path = (doom::path::_GetCurrentPath() + "\\clReflectCompialationData.cppbin");
		
		StdFile file(path.generic_string().c_str());
		if (!file.IsOpen())
			throw std::runtime_error("Fail to Load Reflection Data File ( Looks that file doesn't exist )");

		Malloc allocator;
		clcpp::Database db;
		if (!db.Load(&file, &allocator, 0))
			throw std::runtime_error("Fail to Load Reflection Data");
		
		auto aName = db.GetName("doom::DObejct");
		auto aNamespace = db.GetName("doom");
		auto aType = db.GetType(aName.hash);
		auto namespace1 = db.GetGlobalNamespace();

		auto type = aType->AsClass();

		

		return 1;
	}
}
