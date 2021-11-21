#pragma once

#include <Core.h>
#include <IO/UserInput_Server.h>
#include <EngineGUI/PrintText.h>

//auto t_start = std::chrono::high_resolution_clock::now();
//auto t_end = std::chrono::high_resolution_clock::now();
//FLOAT64 elapsed_time_ms = std::chrono::duration<FLOAT64, std::milli>(t_end - t_start).count();
//dooms::ui::PrintText("elapsed tick count : %lf", elapsed_time_ms);


#ifndef AB_TEST_PROFILING

#define AB_TEST_PROFILING(TEST_TAG, AB_CHANGE_KEY, FUNC1, FUNC2)																								\
{																																\
	static bool is1Func = true;																									\
	if (dooms::userinput::UserInput_Server::GetKeyUp(AB_CHANGE_KEY))																\
	{																															\
		is1Func = !is1Func;																										\
																																\
		if (is1Func == true)																									\
		{																														\
			dooms::ui::PrintText("AB TEST ( %s, %d ) - FUNC1", __FILE__, __LINE__);												\
		}																														\
		else																													\
		{																														\
			dooms::ui::PrintText("AB TEST ( %s, %d ) - FUNC2", __FILE__, __LINE__);												\
		}																														\
	}																															\
	D_START_PROFILING_IN_RELEASE(TEST_TAG);																						\
	if (is1Func == true)																										\
	{																															\
		FUNC1;																													\
	}																															\
	else																														\
	{																															\
		FUNC2;																													\
	}																															\
	D_END_PROFILING_IN_RELEASE(TEST_TAG);																						\
}																																\

#endif
