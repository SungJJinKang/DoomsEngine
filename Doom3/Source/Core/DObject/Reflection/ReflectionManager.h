#pragma once

#include <Core.h>

namespace dooms
{
	namespace reflection
	{

		class ReflectionManager : public ISingleton<ReflectionManager>
		{

		private:

			bool isInitialized = false;

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