#include "UserInput_Server.h"

#include "../Core.h"
#include "../Graphics/Graphics_Server.h"

using namespace doom::userinput;


void UserInput_Server::CursorEnterCallback(GLFWwindow* window, int entered)
{
	UserInput_Server::IsCursorOnScreenWindow = entered;

	D_DEBUG_LOG({ "Mouse Cursor Enter?? : ", std::to_string(entered)}, eLogType::D_LOG);

	if (entered == true)
	{
		double xpos, ypos;
		glfwGetCursorPos(doom::graphics::Graphics_Server::Window, &xpos, &ypos);
		UserInput_Server::mCursorPositionX = xpos;
		UserInput_Server::mCursorPositionY = ypos;
	}
}


void UserInput_Server::CursorPosition_Callback(GLFWwindow* window, double xpos, double ypos)
{
	UserInput_Server::mDeltaCursorPositionX = xpos - UserInput_Server::mCursorPositionX;
	UserInput_Server::mDeltaCursorPositionY = ypos - UserInput_Server::mCursorPositionY;

	UserInput_Server::mCursorPositionX = xpos;
	UserInput_Server::mCursorPositionY = ypos;

	//D_DEBUG_LOG({ "Mouse Cursor Position : Pos X ( ", std::to_string(xpos), " ) , Pos Y ( ", std::to_string(ypos), " )" }, eLogType::D_LOG);
}


void UserInput_Server::Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
{
	UserInput_Server::mScrollOffsetX = xoffset;
	UserInput_Server::mScrollOffsetY = yoffset;
	UserInput_Server::mScrollChangedAtPreviousFrame = true;

	D_DEBUG_LOG({ "Mouse Scroll Callback  : Offset X ( ", std::to_string(xoffset), " ) , Offset Y ( ", std::to_string(yoffset), " )" }, eLogType::D_LOG);
}


void UserInput_Server::Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//D_DEBUG_LOG({ "Key Input Callback  :  ", std::to_string(key), "  ", std::to_string(action) }, eLogType::D_LOG);
}


void UserInput_Server::MouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
{
	D_DEBUG_LOG({ "Mouse Button Callback  :  ", std::to_string(button), "  ", std::to_string(action) }, eLogType::D_LOG);
}


void UserInput_Server::Init()
{
	glfwSetCursorEnterCallback(doom::graphics::Graphics_Server::Window, &(UserInput_Server::CursorEnterCallback));
	glfwSetCursorPosCallback(doom::graphics::Graphics_Server::Window, &(UserInput_Server::CursorPosition_Callback));
	glfwSetScrollCallback(doom::graphics::Graphics_Server::Window, &(UserInput_Server::Scroll_Callback));

#ifdef DEBUG_MODE
	glfwSetKeyCallback(doom::graphics::Graphics_Server::Window, &(UserInput_Server::Key_Callback));
	glfwSetMouseButtonCallback(doom::graphics::Graphics_Server::Window, &(UserInput_Server::MouseButton_Callback));
#endif

	UserInput_Server::SetIsCursorVisible(true);
	UserInput_Server::SetIsCursorLockedInScreen(false);
}

void UserInput_Server::Update()
{
	UserInput_Server::mDeltaCursorPositionX = 0;
	UserInput_Server::mDeltaCursorPositionY = 0;

	glfwPollEvents();

	if (UserInput_Server::mScrollChangedAtPreviousFrame == false)
	{
		UserInput_Server::mScrollOffsetX = 0;
		UserInput_Server::mScrollOffsetY = 0;
	}

	
}

void UserInput_Server::OnEndOfFrame()
{
	UserInput_Server::mScrollChangedAtPreviousFrame = false;

	//glfwPollEvents(); // this function should be called last
}


void UserInput_Server::UpdateCursorMode()
{
	if (UserInput_Server::IsCursorLockedInScreen == false && UserInput_Server::IsCursorVisible == true)
	{
		glfwSetInputMode(doom::graphics::Graphics_Server::Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (UserInput_Server::IsCursorLockedInScreen == false && UserInput_Server::IsCursorVisible == false)
	{
		glfwSetInputMode(doom::graphics::Graphics_Server::Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	else if (UserInput_Server::IsCursorLockedInScreen == true && UserInput_Server::IsCursorVisible == false)
	{
		glfwSetInputMode(doom::graphics::Graphics_Server::Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else if (UserInput_Server::IsCursorLockedInScreen == true && UserInput_Server::IsCursorVisible == true)
	{
		D_DEBUG_LOG("Undefined Cursor Mode, There is no mode that locked in screen and visible", eLogType::D_WARNING); // https://www.glfw.org/docs/3.3/input_guide.html
		glfwSetInputMode(doom::graphics::Graphics_Server::Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void UserInput_Server::SetIsCursorVisible(bool isVisible) noexcept
{
	UserInput_Server::GetSingleton()->IsCursorVisible = isVisible;
	UserInput_Server::GetSingleton()->UpdateCursorMode();
}

void UserInput_Server::SetIsCursorLockedInScreen(bool isLocked) noexcept
{
	UserInput_Server::GetSingleton()->IsCursorLockedInScreen = isLocked;
	UserInput_Server::GetSingleton()->UpdateCursorMode();
}

UserInput_Server::UserInput_Server()
{

}
