#include "GameFlow.h"

#include "../Grahpics/Graphics.h"

void Doom::GameFlow::Init()
{
	Graphics::Init();
}

void Doom::GameFlow::Loop()

{
	if (!glfwWindowShouldClose(Graphics::Window))
	{
		Graphics::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		Graphics::Clear(Graphics::ClearMask::COLOR_BUFFER_BIT, Graphics::ClearMask::DEPTH_BUFFER_BIT);



		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(Graphics::Window);
		glfwPollEvents();

		return;
	}
	else
	{
		DEBUG_LOG("Terminate glfw");
		glfwTerminate();

		return;
	}
}
