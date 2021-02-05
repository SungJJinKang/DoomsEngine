#include "GameFlow.h"

#include "../Graphics/Graphics.h"

void doom::GameFlow::Init()
{
}

void doom::GameFlow::Loop()
{
	
	if (!glfwWindowShouldClose(graphics::Graphics::Window))
	{
		D_START_PROFILING("Rendering A Frame", eProfileLayers::GPU);
		doom::graphics::Graphics::Loop();
		D_END_PROFILING("Rendering A Frame");

		return;
	}
	else
	{
		D_DEBUG_LOG("Terminate glfw");
		glfwTerminate();

		return;
	}
	
}
