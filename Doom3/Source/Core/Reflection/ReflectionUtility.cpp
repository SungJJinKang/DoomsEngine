#include "ReflectionUtility.h"

dooms::reflection::utility::StdFile::StdFile(const char* filename)
{
	mFileSteam.open(filename, std::ios_base::in | std::ios_base::binary);
	D_ASSERT(mFileSteam.is_open() == true);
}

dooms::reflection::utility::StdFile::~StdFile()
{
	if (mFileSteam.is_open() == true)
	{
		mFileSteam.close();
	}
}

bool dooms::reflection::utility::StdFile::IsOpen() const
{
	return mFileSteam.is_open();
}

bool dooms::reflection::utility::StdFile::Read(void* dest, clcpp::size_type size)
{
	return static_cast<bool>(mFileSteam.read(static_cast<char*>(dest), size));
}

void* dooms::reflection::utility::Malloc::Alloc(clcpp::size_type size)
{
	return malloc(size);
}

void dooms::reflection::utility::Malloc::Free(void* ptr)
{
	free(ptr);
}
