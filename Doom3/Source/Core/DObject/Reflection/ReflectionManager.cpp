#include "ReflectionManager.h"

#include "Game/ConfigData.h"
#include <UI/PrintText.h>

#include "clReflectHelper.h"
#include "ReflectionTest.h"
#include "ReflectionUtility.h"

doom::reflection::ReflectionManager::ReflectionManager()
{
}

doom::reflection::ReflectionManager::~ReflectionManager()
{
	UnLoadReflectionBinaryDataFile();
}

std::string doom::reflection::ReflectionManager::GetReflectionBinaryDataFileName() const
{
	std::string reflectionBinaryDataFileName = DEFAULT_CLREFLECT_BINARY_DATA_FILE_NAME_PREFIX;

	reflectionBinaryDataFileName.append("_");

#if defined(DEBUG_MODE)
	reflectionBinaryDataFileName.append("Debug");
#elif defined(RELEASE_MODE)
	reflectionBinaryDataFileName.append("Release");
#endif

	reflectionBinaryDataFileName.append("_");

#if defined(OS_WIN64)
	reflectionBinaryDataFileName.append("x64");
#elif defined(OS_WIN32)
	reflectionBinaryDataFileName.append("Win32");
#endif

	return reflectionBinaryDataFileName;
}

bool doom::reflection::ReflectionManager::UnLoadReflectionBinaryDataFile()
{
	bool isSuccessToUnload = false;
	if(mReflectionDatabase.IsLoaded() == true)
	{
		mReflectionDatabase.~Database();
		doom::ui::PrintText("Success to UnLoad Reflection Database");

		isSuccessToUnload = true;
	}

	return isSuccessToUnload;
}

bool doom::reflection::ReflectionManager::LoadReflectionBinaryDataFile()
{
	bool isSuccess = true;

	const std::filesystem::path reflectionBinaryDataPath = (doom::path::_GetCurrentPath(GetReflectionBinaryDataFileName()));

	utility::StdFile file(reflectionBinaryDataPath.generic_string().c_str());
	if (file.IsOpen() == false)
	{
		doom::ui::PrintText
		(
			"Fail to Load Reflection Data File ( Looks that file doesn't exist ) ( File path : $0 )",
			reflectionBinaryDataPath.c_str()
		);
		D_ASSERT_LOG
		(
			false,
			"Fail to Load Reflection Data File ( Looks that file doesn't exist ) ( File path : $0 )",
			reflectionBinaryDataPath.c_str()
		);

		isSuccess = false;
	}

	if(isSuccess == true)
	{
		utility::Malloc allocator;
		if (mReflectionDatabase.Load(&file, &allocator, 0) == false)
		{
			doom::ui::PrintText
			(
				"Fail to Load Reflection Data ( Reflection Data File path : %s )",
				reflectionBinaryDataPath.c_str()
			);
			D_ASSERT_LOG
			(
				false,
				"Fail to Load Reflection Data ( Reflection Data File path : %s )",
				reflectionBinaryDataPath.c_str()
			);

			isSuccess = false;
		}
	}
	
	if(isSuccess == true)
	{
		doom::ui::PrintText("Success to Load Reflection Database");
	}

	return isSuccess;
}

void doom::reflection::ReflectionManager::Initialize()
{
	if (GetIsReflectionEnabled() == true)
	{;
		const bool isSuccess = doom::clReflectHelper::Generate_clReflect_BinaryReflectionData();
		D_ASSERT_LOG(isSuccess == true, "Fail to Generate Reflection Data using clRefect");

		LoadReflectionBinaryDataFile();
	}
	else
	{
		doom::ui::PrintText("Reflection is disabled. Check Config.ini");
	}
}

bool doom::reflection::ReflectionManager::GetIsReflectionEnabled() const
{
	return ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("SYSTEM", "ENABLED_REFLECTION");
}

void doom::reflection::ReflectionManager::SetIsReflectionEnabled(const bool isEnabled)
{
	ConfigData::GetSingleton()->GetConfigData().InsertVariable("SYSTEM", "ENABLED_REFLECTION", isEnabled);
}

bool doom::reflection::ReflectionManager::GetIsReflectionDatabaseLoaded() const
{
	return mReflectionDatabase.IsLoaded();
}
