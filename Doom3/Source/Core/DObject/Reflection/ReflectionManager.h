#pragma once

#include <Core.h>

#include "ReflectionUtility.h"

#include "ReflectionManager.reflection.h"
namespace dooms
{
	namespace reflection
	{

		class DOOM_API D_CLASS ReflectionManager : public DObject, public ISingleton<ReflectionManager>
		{
			GENERATE_BODY()	
			

		private:

			bool isInitialized = false;
			
			utility::Malloc allocator;
			clcpp::Database mReflectionDatabase;

		public:

			inline static const char* const DEFAULT_CLREFLECT_BINARY_DATA_FILE_NAME_PREFIX = "clReflectCompialationData";

			ReflectionManager();
			~ReflectionManager() override;
			ReflectionManager(const ReflectionManager&) = delete;
			ReflectionManager(ReflectionManager&&) noexcept = delete;
			ReflectionManager& operator=(const ReflectionManager&) = delete;
			ReflectionManager& operator=(ReflectionManager&&) noexcept = delete;

			std::string GetReflectionBinaryDataFileName() const;

			bool UnLoadReflectionBinaryDataFile();
			bool LoadReflectionBinaryDataFile();

			void Initialize();

			bool GetIsReflectionEnabled() const;
			void SetIsReflectionEnabled(const bool isEnabled);
			bool GetIsReflectionDatabaseLoaded() const;
		};


	}
}
