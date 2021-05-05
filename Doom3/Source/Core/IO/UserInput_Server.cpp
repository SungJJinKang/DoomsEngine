#include "UserInput_Server.h"

#include "../Core.h"
#include "../Graphics/Graphics_Server.h"
#include "../Game/ConfigData.h"
#include <Rendering/Camera.h>
#include <Vector3.h>
using namespace doom::userinput;


void UserInput_Server::CursorEnterCallback(GLFWwindow* window, int entered)
{
	UserInput_Server::IsCursorOnScreenWindow = entered;

	D_DEBUG_LOG({ "Mouse Cursor Enter?? : ", std::to_string(entered)}, eLogType::D_LOG);

	if (entered != 0)
	{
		double xpos, ypos;
		glfwGetCursorPos(doom::graphics::Graphics_Server::Window, &xpos, &ypos);
		doom::userinput::UserInput_Server::mCurrentCursorScreenPosition.x = static_cast<float>(xpos);
		doom::userinput::UserInput_Server::mCurrentCursorScreenPosition.y = static_cast<float>(ypos);
	}
}


void UserInput_Server::CursorPosition_Callback(GLFWwindow* window, double xpos, double ypos)
{
	UserInput_Server::mDeltaCursorScreenPosition.x = static_cast<float>(xpos) - UserInput_Server::mCurrentCursorScreenPosition.x;
	UserInput_Server::mDeltaCursorScreenPosition.y = static_cast<float>(ypos) - UserInput_Server::mCurrentCursorScreenPosition.y;

	doom::userinput::UserInput_Server::mCurrentCursorScreenPosition.x = static_cast<float>(xpos);
	doom::userinput::UserInput_Server::mCurrentCursorScreenPosition.y = static_cast<float>(ypos);
	//D_DEBUG_LOG({ "Mouse Cursor Position : Pos X ( ", std::to_string(xpos), " ) , Pos Y ( ", std::to_string(ypos), " )" }, eLogType::D_LOG);
}


void UserInput_Server::Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
{
	UserInput_Server::mScrollOffset.x = static_cast<float>(xoffset);
	UserInput_Server::mScrollOffset.y = static_cast<float>(yoffset);
	UserInput_Server::mScrollChangedAtPreviousFrame = true;

	D_DEBUG_LOG({ "Mouse Scroll Callback  : Offset X ( ", std::to_string(xoffset), " ) , Offset Y ( ", std::to_string(yoffset), " )" }, eLogType::D_LOG);
}


void UserInput_Server::Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key < static_cast<int>(FIRST_KEY_CODE) || key > static_cast<int>(LAST_KEY_CODE))
	{
		return;
	}

	if (action == GLFW_PRESS)
	{
		UserInput_Server::mKeyState[key - static_cast<int>(FIRST_KEY_CODE)] = eKeyState::PRESS_DOWN;
		UserInput_Server::mDownKeys.push_back(key);
	}
	else if (action == GLFW_RELEASE)
	{
		UserInput_Server::mKeyState[key - static_cast<int>(FIRST_KEY_CODE)] = eKeyState::UP;
		UserInput_Server::mKeyToggle[key - static_cast<int>(FIRST_KEY_CODE)] = !UserInput_Server::mKeyToggle[key - static_cast<int>(FIRST_KEY_CODE)];
		UserInput_Server::mUpKeys.push_back(key);
	}

	//D_DEBUG_LOG({ "Key Input Callback  :  ", std::to_string(key), "  ", std::to_string(action) }, eLogType::D_LOG);
}


void doom::userinput::UserInput_Server::UpdateKeyStates()
{
	for (auto upKey : UserInput_Server::mUpKeys)
	{
		UserInput_Server::mKeyState[upKey - static_cast<int>(FIRST_KEY_CODE)] = eKeyState::NONE;
	}

	for (auto downKey : UserInput_Server::mDownKeys)
	{
		UserInput_Server::mKeyState[downKey - static_cast<int>(FIRST_KEY_CODE)] = eKeyState::PRESSING;
	}

	UserInput_Server::mUpKeys.clear();
	UserInput_Server::mDownKeys.clear();
}

void doom::userinput::UserInput_Server::UpdateMouseButtonStates()
{
	for (unsigned int i = 0; i < UserInput_Server::mMouseButtonState.size(); i++)
	{
		if (UserInput_Server::mMouseButtonState[i] == eMouse_Button_Action::RELEASE)
		{
			UserInput_Server::mMouseButtonState[i] = eMouse_Button_Action::NONE;
		}
		else if (UserInput_Server::mMouseButtonState[i] == eMouse_Button_Action::DOWN)
		{
			UserInput_Server::mMouseButtonState[i] = eMouse_Button_Action::PRESSING;
		}
	}
}

void UserInput_Server::MouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		UserInput_Server::mMouseButtonState[button - static_cast<int>(FIRST_MOUSE_BUTTON_TYPE)] = eMouse_Button_Action::DOWN;
	}
	else if (action == GLFW_RELEASE)
	{
		UserInput_Server::mMouseButtonState[button - static_cast<int>(FIRST_MOUSE_BUTTON_TYPE)] = eMouse_Button_Action::RELEASE;
	}
}


void doom::userinput::UserInput_Server::UpdateCurrentCursorScreenPosition()
{
	doom::userinput::UserInput_Server::mCurrentCursorNDCPosition = Camera::GetMainCamera()->ScreenToNDCPoint(doom::userinput::UserInput_Server::mCurrentCursorScreenPosition);

	//math::Vector3 ndcPoint{ doom::userinput::UserInput_Server::mCurrentCursorNDCPosition.x, doom::userinput::UserInput_Server::mCurrentCursorNDCPosition.y, 0 };
	doom::userinput::UserInput_Server::mCurrentCursorWorldPosition = Camera::GetMainCamera()->NDCToWorldPoint(doom::userinput::UserInput_Server::mCurrentCursorNDCPosition);
	//D_DEBUG_LOG(doom::userinput::UserInput_Server::mCurrentCursorWorldPosition.toString());
}


void UserInput_Server::Init()
{
	glfwSetCursorEnterCallback(doom::graphics::Graphics_Server::Window, &(UserInput_Server::CursorEnterCallback));
	glfwSetCursorPosCallback(doom::graphics::Graphics_Server::Window, &(UserInput_Server::CursorPosition_Callback));
	glfwSetScrollCallback(doom::graphics::Graphics_Server::Window, &(UserInput_Server::Scroll_Callback));

	glfwSetKeyCallback(doom::graphics::Graphics_Server::Window, &(UserInput_Server::Key_Callback));
	glfwSetMouseButtonCallback(doom::graphics::Graphics_Server::Window, &(UserInput_Server::MouseButton_Callback));

	UserInput_Server::SetIsCursorVisible(ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("USERINPUT", "CURSOR_IS_VISIBLE"));
	UserInput_Server::SetIsCursorLockedInScreen(ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("USERINPUT", "CURSOR_LOCKED_IN_SCREEN"));
}

void UserInput_Server::Update()
{
	UserInput_Server::mDeltaCursorScreenPosition.x = 0;
	UserInput_Server::mDeltaCursorScreenPosition.y = 0;

	this->UpdateKeyStates();
	this->UpdateMouseButtonStates();
	glfwPollEvents();

	if (UserInput_Server::mScrollChangedAtPreviousFrame == false)
	{
		UserInput_Server::mScrollOffset.x = 0;
		UserInput_Server::mScrollOffset.y = 0;
	}

	this->UpdateCurrentCursorScreenPosition();
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
