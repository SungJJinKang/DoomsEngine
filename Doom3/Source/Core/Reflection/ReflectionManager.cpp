#include "ReflectionManager.h"

#include "Game/ConfigData.h"
#include <UI/PrintText.h>

#include "clReflectHelper.h"
#include "ReflectionUtility.h"

#include "ReflectionType/ToString.h"

#ifdef DEBUG_MODE
#include "Test/ReflectionTest.h"
#endif

dooms::reflection::ReflectionManager::ReflectionManager()
	: allocator(), mReflectionDatabase()
{
}

dooms::reflection::ReflectionManager::~ReflectionManager()
{
	UnLoadReflectionBinaryDataFile();
}

std::string dooms::reflection::ReflectionManager::GetReflectionBinaryDataFileName() const
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

	reflectionBinaryDataFileName.append(".cppbin");

	return reflectionBinaryDataFileName;
}

bool dooms::reflection::ReflectionManager::UnLoadReflectionBinaryDataFile()
{
	bool isSuccessToUnload = false;
	if(mReflectionDatabase.IsLoaded() == true)
	{
		mReflectionDatabase.UnLoad();
		dooms::ui::PrintText("Success to UnLoad Reflection Database");

		isSuccessToUnload = true;
	}

	return isSuccessToUnload;
}

bool dooms::reflection::ReflectionManager::LoadReflectionBinaryDataFile()
{
	bool isSuccess = true;

	const std::filesystem::path reflectionBinaryDataPath = (dooms::path::_GetCurrentPath(GetReflectionBinaryDataFileName()));

	utility::StdFile file(reflectionBinaryDataPath.generic_string().c_str());
	if (file.IsOpen() == false)
	{
		dooms::ui::PrintText
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
		if (mReflectionDatabase.Load(&file, &allocator, 0) == false)
		{
			dooms::ui::PrintText
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
		dooms::ui::PrintText("Success to Load Reflection Database");
	}

	return isSuccess;
}

void dooms::reflection::ReflectionManager::Initialize()
{
	if (GetIsReflectionEnabled() == true)
	{;
		if(ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("SYSTEM", "GENERATE_REFLECTION_DATA") == true)
		{
			const bool isSuccess = dooms::clReflectHelper::Generate_clReflect_BinaryReflectionData();
			D_ASSERT_LOG(isSuccess == true, "Fail to Generate Reflection Data using clRefect");
		}
		
		LoadReflectionBinaryDataFile();

		dooms::reflection::InitReflectionToString();

#ifdef DEBUG_MODE
		clReflectTest::test(mReflectionDatabase);
#endif

	}
	else
	{
		dooms::ui::PrintText("Reflection is disabled. Check Config.ini");
	}
}

bool dooms::reflection::ReflectionManager::GetIsReflectionEnabled() const
{
	return ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("SYSTEM", "ENABLED_REFLECTION");
}

void dooms::reflection::ReflectionManager::SetIsReflectionEnabled(const bool isEnabled)
{
	ConfigData::GetSingleton()->GetConfigData().InsertVariable("SYSTEM", "ENABLED_REFLECTION", isEnabled);
}

bool dooms::reflection::ReflectionManager::GetIsReflectionDatabaseLoaded() const
{
	return mReflectionDatabase.IsLoaded();
}

const clcpp::Database& dooms::reflection::ReflectionManager::GetclcppDatabase() const
{
	D_ASSERT(GetIsReflectionDatabaseLoaded() == true);

	return mReflectionDatabase;
}

clcpp::Name dooms::reflection::ReflectionManager::GetclcppName(const char* const name)
{
	D_ASSERT(GetIsReflectionDatabaseLoaded() == true);
	return GetclcppDatabase().GetName(name);
}

UINT32 dooms::reflection::ReflectionManager::GetclcppNameHash(const char* const name)
{
	D_ASSERT(GetIsReflectionDatabaseLoaded() == true);
	return GetclcppName(name).hash;
}
