#pragma once

#include <Core.h>
#include <IO/UserInput_Server.h>
#include <UI/PrintText.h>

//auto t_start = std::chrono::high_resolution_clock::now();
//auto t_end = std::chrono::high_resolution_clock::now();
//double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
//doom::ui::PrintText("elapsed tick count : %lf", elapsed_time_ms);


#ifndef AB_TEST

#define AB_TEST(KEY, FUNC1, FUNC2)																								\
{																																\
	static bool is1Func = true;																									\
	if (doom::userinput::UserInput_Server::GetKeyUp(KEY))																		\
	{																															\
		is1Func = !is1Func;																										\
																																\
		if (is1Func == true)																									\
		{																														\
			doom::ui::PrintText("AB TEST ( %s, %d ) - FUNC1", __FILE__, __LINE__);												\
		}																														\
		else																													\
		{																														\
			doom::ui::PrintText("AB TEST ( %s, %d ) - FUNC2", __FILE__, __LINE__);												\
		}																														\
	}																															\
	auto t_start = std::chrono::high_resolution_clock::now();																	\
	if (is1Func == true)																										\
	{																															\
		FUNC1;																													\
	}																															\
	else																														\
	{																															\
		FUNC2;																													\
	}																															\
	auto t_end = std::chrono::high_resolution_clock::now();																		\
	double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();								\
	doom::ui::PrintText("AB TEST ( %s )- Time ( millisecond ) : %lf", (is1Func == true ? "FUNC1" : "FUNC2"), elapsed_time_ms);	\
}																																\

#endif
