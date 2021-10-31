#pragma once

#include <Core.h>
#include <DirectXTex.h>
#include <excpt.h>

#include <UI/PrintText.h>

namespace doom
{
	class SmartCSharpLibrary
	{

		std::string mCSharpLibraryPath;
		void* mLibrary;

	private:

		void* _GetProcAddress(const char* const functionName);

	public :

		SmartCSharpLibrary(const std::string& csharpLibraryPath);
		~SmartCSharpLibrary();

		SmartCSharpLibrary(const SmartCSharpLibrary&) = default;
		SmartCSharpLibrary(SmartCSharpLibrary&& _SmartCSharpLibrary) noexcept;
		SmartCSharpLibrary& operator=(const SmartCSharpLibrary&) = default;
		SmartCSharpLibrary& operator=(SmartCSharpLibrary&& _SmartCSharpLibrary) noexcept;

		template <typename... Args>
		bool CallFunction(const char* functionName, Args&&... args);

		template <typename RETURN_TYPE, typename... Args>
		bool CallFunctionWithReturn(const char* functionName, RETURN_TYPE& returnValue, Args&&... args);
	};


	template <typename ... Args>
	bool SmartCSharpLibrary::CallFunction(const char* const functionName, Args&&... args)
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
				doom::ui::PrintText("exception from csharp function ( %s )", ex.what());
			}
			catch (const std::string& ex) {
				D_ASSERT_LOG(false, "exception from csharp function ( %s )", ex.c_str());
				doom::ui::PrintText("exception from csharp function ( %s )", ex.c_str());
			}
			catch (...) {
				D_ASSERT_LOG(false, "exception from csharp function");
				doom::ui::PrintText("exception from csharp function");
			}

		}

		return IsSuccess;
	}

	int filter(unsigned int code, struct _EXCEPTION_POINTERS* ptr);


	template <typename RETURN_TYPE, typename ... Args>
	bool SmartCSharpLibrary::CallFunctionWithReturn(const char* const functionName, RETURN_TYPE& returnValue, Args&&... args)
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

