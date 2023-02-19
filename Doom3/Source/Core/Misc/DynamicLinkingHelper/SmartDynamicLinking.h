#pragma once

#include <Core.h>

#include <memory>
#include <mutex>
#include <unordered_map>

#include <DirectXTex.h>
#include <excpt.h>



#include "SmartDynamicLinking.reflection.h"
namespace dooms
{
	struct DOOM_API D_STRUCT DynamicLinkingLibrary
	{
		GENERATE_BODY_DynamicLinkingLibrary()

		static std::mutex LoadUnLoadDLLMutexs;

		std::string mLibraryPath;
		void* mLibrary;

		DynamicLinkingLibrary(const std::string& libraryPath);
		DynamicLinkingLibrary(const std::string& libraryPath, const unsigned long dwFlags);
		~DynamicLinkingLibrary();

		void* LoadDynamicLinkingLibrary(const unsigned long dwFlags);
		bool UnloadDynamicLinkingLibrary();
		bool IsLoaded() const;
	};

	class DOOM_API D_CLASS SmartDynamicLinking
	{
		GENERATE_BODY()
			
	private:

		std::shared_ptr<DynamicLinkingLibrary> mDynamicLinkingLibrary;

		std::unordered_map<std::string, void*> ProcAddressCache;

		void* _GetProcAddress(const char* const functionName);
		
	public :

		SmartDynamicLinking();
		SmartDynamicLinking(const std::string& libraryPath);
		~SmartDynamicLinking();

		SmartDynamicLinking(const SmartDynamicLinking&);
		SmartDynamicLinking(SmartDynamicLinking&& sDynamicLinking) noexcept;
		SmartDynamicLinking& operator=(const SmartDynamicLinking&);
		SmartDynamicLinking& operator=(SmartDynamicLinking&& sDynamicLinking) noexcept;

		bool LoadDynamicLinkingLibrary(const std::string& libraryPath);
		void ReleaseDynamicLinkingLibrary();
		bool IsDynamicLibraryLoaded() const;

		template <typename... Args>
		bool CallFunction(const char* functionName, Args&&... args);

		template <typename RETURN_TYPE, typename... Args>
		bool CallFunctionWithReturn(const char* functionName, RETURN_TYPE& returnValue, Args&&... args);
	};


	template <typename ... Args>
	bool SmartDynamicLinking::CallFunction(const char* const functionName, Args&&... args)
	{
		typedef void(__cdecl* functionType)(Args...);

		functionType function = reinterpret_cast<functionType>(_GetProcAddress(functionName));

		bool IsSuccess = false;
		if (function != nullptr)
		{
			try
			{
				function(std::forward<Args>(args)...);
				IsSuccess = true;
			}
			catch (const std::exception& ex) {
				D_ASSERT_LOG(false, "exception from csharp function ( %s )", ex.what());
				D_RELEASE_LOG(eLogType::D_LOG, "exception from csharp function ( %s )", ex.what());
			}
			catch (const std::string& ex) {
				D_ASSERT_LOG(false, "exception from csharp function ( %s )", ex.c_str());
				D_RELEASE_LOG(eLogType::D_LOG, "exception from csharp function ( %s )", ex.c_str());
			}
			catch (...) {
				D_ASSERT_LOG(false, "exception from csharp function");
				D_RELEASE_LOG(eLogType::D_LOG, "exception from csharp function");
			}

		}

		return IsSuccess;
	}

	int filter(unsigned int code, struct _EXCEPTION_POINTERS* ptr);


	template <typename RETURN_TYPE, typename ... Args>
	bool SmartDynamicLinking::CallFunctionWithReturn(const char* const functionName, RETURN_TYPE& returnValue, Args&&... args)
	{
		typedef RETURN_TYPE(__cdecl* functionType)(Args...);

		functionType function = reinterpret_cast<functionType>(_GetProcAddress(functionName));

		bool IsSuccess = false;
		if(function != nullptr)
		{
			__try
			{
				returnValue = function(std::forward<Args>(args)...);
				IsSuccess = true;
			}
			__except (filter(GetExceptionCode(), GetExceptionInformation()))
			{
				//... yey!
			}
			
			
		}

		return IsSuccess;
	}
}

