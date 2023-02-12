#include "ReflectionManager.h"

#include "EngineConfigurationData/ConfigData.h"
#include <EngineGUI/PrintText.h>

#include "clReflectHelper.h"
#include "ReflectionUtility.h"

#include "ReflectionType/ToString.h"

#include "ReflectionType/DClass.h"

#ifdef DEBUG_MODE
#include "Test/ReflectionTest.h"
#endif

void dooms::reflection::ReflectionManager::CacheReflectionTypeDatas()
{
	// This is for multithreaded gc

	{
		unsigned int reflectedTypeCount;
		const clcpp::Type** const reflectedTypes = mReflectionDatabase.GetTypes(reflectedTypeCount);
		for (unsigned int i = 0; i < reflectedTypeCount; i++)
		{
			DType dType{ reflectedTypes[i] };
			dType.GetIsDerivedFromDObject();

			if (reflectedTypes[i]->kind == clcpp::Primitive::KIND_CLASS)
			{
				DClass dClass{ reflectedTypes[i]->AsClass() };

				dClass.GetDFunctionList();
				dClass.GetDFieldList();
			}
		}
	}

	
	
}

dooms::reflection::ReflectionManager::ReflectionManager()
	: mAllocatorForLoadingReflectionData(), mReflectionDatabase()
{
}

dooms::reflection::ReflectionManager::~ReflectionManager()
{
	UnLoadReflectionBinaryDataFile();
}

std::string dooms::reflection::ReflectionManager::GetReflectionBinaryDataFileName() const
{
	std::string reflectionBinaryDataFileName = ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("SYSTEM", "REFLECTION_BINARY_FILE_NAME");

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

	const std::filesystem::path reflectionBinaryDataPath = std::filesystem::u8path(dooms::path::_GetCurrentPath(GetReflectionBinaryDataFileName()));

	utility::StdFile file(reflectionBinaryDataPath);
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
		if (mReflectionDatabase.Load(&file, &mAllocatorForLoadingReflectionData, 0) == false)
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
	{
#if GENERATE_REFLECTION_DATA
		if(ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("SYSTEM", "GENERATE_REFLECTION_DATA") == true)
		{
			D_ASSERT(dooms::clReflectHelper::IsExistProjectFile());
			const bool isSuccess = dooms::clReflectHelper::Generate_clReflect_BinaryReflectionData();
			D_ASSERT_LOG(isSuccess == true, "Fail to Generate Reflection Data using clRefect");
		}
#endif
		
		LoadReflectionBinaryDataFile();

		dooms::reflection::InitReflectionToString();

#ifdef DEBUG_MODE
		clReflectTest::test(mReflectionDatabase);
#endif
		CacheReflectionTypeDatas();
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
	ConfigurationValueManager::GetConfigurationValueManager()->GetTCvar<bool>("SYSTEM", "ENABLED_REFLECTION")->SetValue(isEnabled);
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

clcpp::Name dooms::reflection::ReflectionManager::GetclcppName(const char* const name) const
{
	D_ASSERT(GetIsReflectionDatabaseLoaded() == true);
	return GetclcppDatabase().GetName(name);
}

UINT32 dooms::reflection::ReflectionManager::GetclcppNameHash(const char* const name) const
{
	D_ASSERT(GetIsReflectionDatabaseLoaded() == true);
	return GetclcppName(name).hash;
}

const clcpp::Type* dooms::reflection::ReflectionManager::GetclcppType(const char* const name) const
{
	return GetclcppType(GetclcppNameHash(name));
}

const clcpp::Type* dooms::reflection::ReflectionManager::GetclcppType(const UINT32 nameHash) const
{
	D_ASSERT(nameHash != 0);

	const clcpp::Type* const clcppType = GetclcppDatabase().GetType(nameHash);
	D_ASSERT(clcppType != nullptr);

	return clcppType;
}
