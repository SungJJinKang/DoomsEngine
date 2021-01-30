#include "GameFlow.h"

#include "../Graphics/Graphics.h"

void doom::GameFlow::Init()
{
}

void doom::GameFlow::Loop()

{
	if (!glfwWindowShouldClose(graphics::Graphics::Window))
	{
		graphics::Graphics::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		graphics::Graphics::Clear(graphics::Graphics::eClearMask::COLOR_BUFFER_BIT, graphics::Graphics::eClearMask::DEPTH_BUFFER_BIT);



		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(graphics::Graphics::Window);
		glfwPollEvents();

		return;
	}
	else
	{
		D_DEBUG_LOG("Terminate glfw");
		glfwTerminate();

		return;
	}
}
