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
			
			utility::Malloc allocator;
			clcpp::Database mReflectionDatabase;

		public:
			
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

			const clcpp::Database& GetclcppDatabase() const;

			clcpp::Name GetclcppName(const char* const name) const;
			UINT32 GetclcppNameHash(const char* const name) const;

			const clcpp::Type* GetclcppType(const char* const name) const;
			const clcpp::Type* GetclcppType(const UINT32 nameHash) const;
		};


	}
}
