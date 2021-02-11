#include "UserInput_Server.h"

#include "../Core.h"
#include "../Graphics/Graphics_Server.h"

using namespace doom::userinput;


void UserInput_Server::CursurPosition_Callback(GLFWwindow* window, double xpos, double ypos)
{
	auto userinput_server = UserInput_Server::GetSingleton();

	userinput_server->mCursorPositionX = xpos;
	userinput_server->mCursorPositionY = ypos;

	D_DEBUG_LOG({ "Mouse Cursor Position : Pos X ( ", std::to_string(xpos), " ) , Pos Y ( ", std::to_string(ypos), " )" }, eLogType::D_LOG);
}


void UserInput_Server::Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
{
	auto userinput_server = UserInput_Server::GetSingleton();

	userinput_server->mScrollOffsetX = xoffset;
	userinput_server->mScrollOffsetY = yoffset;
	userinput_server->mScrollChangedAtPreviousFrame = true;

	D_DEBUG_LOG({ "Mouse Scroll Callback  : Offset X ( ", std::to_string(xoffset), " ) , Offset Y ( ", std::to_string(yoffset), " )" }, eLogType::D_LOG);
}


void UserInput_Server::Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	D_DEBUG_LOG({ "Key Input Callback  :  ", std::to_string(key), "  ", std::to_string(action) }, eLogType::D_LOG);
}


void UserInput_Server::MouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
{
	D_DEBUG_LOG({ "Mouse Button Callback  :  ", std::to_string(button), "  ", std::to_string(action) }, eLogType::D_LOG);
}


void UserInput_Server::Init()
{
	glfwSetCursorPosCallback(doom::graphics::Graphics_Server::Window, &(UserInput_Server::CursurPosition_Callback));
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
	if (this->mScrollChangedAtPreviousFrame == false)
	{
		this->mScrollOffsetX = 0;
		this->mScrollOffsetY = 0;
	}

	
}

void UserInput_Server::OnEndOfFrame()
{
	UserInput_Server::mScrollChangedAtPreviousFrame = false;

	glfwPollEvents(); // this function should be called last
}


void UserInput_Server::UpdateCursorMode()
{
	if (this->IsCursorLockedInScreen == false && this->IsCursorVisible == true)
	{
		glfwSetInputMode(doom::graphics::Graphics_Server::Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (this->IsCursorLockedInScreen == false && this->IsCursorVisible == false)
	{
		glfwSetInputMode(doom::graphics::Graphics_Server::Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	else if (this->IsCursorLockedInScreen == true && this->IsCursorVisible == false)
	{
		glfwSetInputMode(doom::graphics::Graphics_Server::Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else if (this->IsCursorLockedInScreen == true && this->IsCursorVisible == true)
	{
		D_DEBUG_LOG("Undefined Cursor Mode, There is no mode that locked in screen and visible", eLogType::D_WARNING); // https://www.glfw.org/docs/3.3/input_guide.html
		glfwSetInputMode(doom::graphics::Graphics_Server::Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void UserInput_Server::SetIsCursorVisible(bool isVisible)
{
	UserInput_Server::GetSingleton()->IsCursorVisible = isVisible;
	UserInput_Server::GetSingleton()->UpdateCursorMode();
}

void UserInput_Server::SetIsCursorLockedInScreen(bool isLocked)
{
	UserInput_Server::GetSingleton()->IsCursorLockedInScreen = isLocked;
	UserInput_Server::GetSingleton()->UpdateCursorMode();
}

UserInput_Server::UserInput_Server()
{

}
