#include "UserInput_Server.h"


#include "../Core.h"
#include "../EngineConfigurationData/ConfigData.h"

#include <Rendering/Camera.h>
#include <Vector3.h>

#include "Graphics/GraphicsAPI/GraphicsAPI.h"
#include "Graphics/GraphicsAPI/Input/GraphicsAPIInput.h"


void UserInput_Server::CursorEnterCallback(bool isEntered)
{
	UserInput_Server::IsCursorOnScreenWindow = isEntered;

	//D_DEBUG_LOG(eLogType::D_LOG, "Mouse Cursor Enter : %d", isEntered);

}



void UserInput_Server::CursorPosition_Callback(FLOAT64 xpos, FLOAT64 ypos)
{
	UserInput_Server::mDeltaCursorScreenPosition.x = static_cast<FLOAT32>(xpos) - UserInput_Server::mCurrentCursorScreenPosition.x;
	UserInput_Server::mDeltaCursorScreenPosition.y = static_cast<FLOAT32>(ypos) - UserInput_Server::mCurrentCursorScreenPosition.y;

	dooms::userinput::UserInput_Server::mCurrentCursorScreenPosition.x = static_cast<FLOAT32>(xpos);
	dooms::userinput::UserInput_Server::mCurrentCursorScreenPosition.y = static_cast<FLOAT32>(ypos);

	//D_DEBUG_LOG(eLogType::D_LOG, "Cursor Screen Position: %f %f", xpos, ypos);
	//D_DEBUG_LOG(eLogType::D_LOG, "Delta Cursor Screen Position: %f %f", UserInput_Server::mDeltaCursorScreenPosition.x, UserInput_Server::mDeltaCursorScreenPosition.y);
}


void UserInput_Server::Scroll_Callback(FLOAT64 xoffset, FLOAT64 yoffset)
{
	UserInput_Server::mScrollOffset.x = static_cast<FLOAT32>(xoffset);
	UserInput_Server::mScrollOffset.y = static_cast<FLOAT32>(yoffset);
	UserInput_Server::mScrollChangedAtPreviousFrame = true;

	//D_DEBUG_LOG(eLogType::D_LOG, "Mouse Scroll Callback  : Offset X ( %f ), Offset Y ( %f )", xoffset, yoffset);
}


void UserInput_Server::Key_Callback(dooms::input::GraphicsAPIInput::eKEY_CODE key, INT32 scancode, dooms::input::GraphicsAPIInput::eInputActionType action, INT32 mods)
{
	if (key != dooms::input::GraphicsAPIInput::eKEY_CODE::UNKNOWN)
	{
		const eKeyState currentKeyState = UserInput_Server::mKeyState[key - static_cast<INT32>(FIRST_KEY_CODE)];

		switch (action)
		{
		case dooms::input::GraphicsAPIInput::PRESS:
			if(currentKeyState == eKeyState::PRESS_DOWN)
			{
				UserInput_Server::mKeyState[key - static_cast<INT32>(FIRST_KEY_CODE)] = eKeyState::PRESSING;
				//D_DEBUG_LOG(eLogType::D_LOG, "PRESSING");
			}
			else
			{
				UserInput_Server::mKeyState[key - static_cast<INT32>(FIRST_KEY_CODE)] = eKeyState::PRESS_DOWN;
				//D_DEBUG_LOG(eLogType::D_LOG, "PRESS_DOWN");
			}
			break;

		case dooms::input::GraphicsAPIInput::REPEAT:
			UserInput_Server::mKeyState[key - static_cast<INT32>(FIRST_KEY_CODE)] = eKeyState::PRESSING;
			//D_DEBUG_LOG(eLogType::D_LOG, "PRESSING");
			break;

		case dooms::input::GraphicsAPIInput::RELEASE:
			UserInput_Server::mKeyState[key - static_cast<INT32>(FIRST_KEY_CODE)] = eKeyState::UP;
			UserInput_Server::mKeyToggle[key - static_cast<INT32>(FIRST_KEY_CODE)] = !UserInput_Server::mKeyToggle[key - static_cast<INT32>(FIRST_KEY_CODE)];
			UserInput_Server::mUpKeys.push_back(key);
			//D_DEBUG_LOG(eLogType::D_LOG, "UP");
			break;
		}
	}
}


void UserInput_Server::MouseButton_Callback(dooms::input::GraphicsAPIInput::eMoustInput button, dooms::input::GraphicsAPIInput::eInputActionType action, INT32 mods)
{
	switch (action)
	{
	case dooms::input::GraphicsAPIInput::PRESS:
		UserInput_Server::mMouseButtonState[button - static_cast<INT32>(FIRST_MOUSE_BUTTON_TYPE)] = eMouse_Button_Action::DOWN;
		break;

	case dooms::input::GraphicsAPIInput::RELEASE:
		UserInput_Server::mMouseButtonState[button - static_cast<INT32>(FIRST_MOUSE_BUTTON_TYPE)] = eMouse_Button_Action::RELEASE;
		break;

	default:
		NEVER_HAPPEN;
	}
}

void dooms::userinput::UserInput_Server::UpdateKeyStates()
{
	for (auto upKey : UserInput_Server::mUpKeys)
	{
		UserInput_Server::mKeyState[upKey - static_cast<INT32>(FIRST_KEY_CODE)] = eKeyState::NONE;
	}

	/*
	for (auto downKey : UserInput_Server::mDownKeys)
	{
		const input::GraphicsAPIInput::eInputActionType keyAction = dooms::input::GraphicsAPIInput::GetKeyCurrentAction(dooms::graphics::GraphicsAPI::GetPlatformWindow(), downKey);

		switch (keyAction)
		{
			case input::GraphicsAPIInput::PRESS:
				UserInput_Server::mKeyState[downKey - static_cast<INT32>(FIRST_KEY_CODE)] = eKeyState::PRESSING;
				break;
			case input::GraphicsAPIInput::RELEASE:
					UserInput_Server::mKeyState[downKey - static_cast<INT32>(FIRST_KEY_CODE)] = eKeyState::NONE;
					break;
			case input::GraphicsAPIInput::REPEAT:
				UserInput_Server::mKeyState[downKey - static_cast<INT32>(FIRST_KEY_CODE)] = eKeyState::PRESSING;
				break;
			default:
				D_ASSERT(false);
		}
		
	}
	UserInput_Server::mDownKeys.clear();
	*/

	UserInput_Server::mUpKeys.clear();
}

void dooms::userinput::UserInput_Server::UpdateMouseButtonStates()
{
	for (UINT32 i = 0; i < UserInput_Server::mMouseButtonState.size(); i++)
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



void dooms::userinput::UserInput_Server::UpdateCurrentCursorScreenPosition()
{
	if(Camera::GetMainCamera() != nullptr)
	{
		dooms::userinput::UserInput_Server::mCurrentCursorNDCPosition = Camera::GetMainCamera()->ScreenToNDCPoint(math::Vector3{ dooms::userinput::UserInput_Server::mCurrentCursorScreenPosition });

		//math::Vector3 ndcPoint{ dooms::userinput::UserInput_Server::mCurrentCursorNDCPosition.x, dooms::userinput::UserInput_Server::mCurrentCursorNDCPosition.y, 0 };
		dooms::userinput::UserInput_Server::mCurrentCursorWorldPosition = Camera::GetMainCamera()->NDCToWorldPoint(math::Vector3{ dooms::userinput::UserInput_Server::mCurrentCursorNDCPosition });

	}
}

void UserInput_Server::Update()
{}

void UserInput_Server::Init(const int argc, char* const* const argv)
{
	UserInput_Server::SetIsCursorVisible(ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("USERINPUT", "CURSOR_IS_VISIBLE"));
	UserInput_Server::SetIsCursorLockedInScreen(ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("USERINPUT", "CURSOR_LOCKED_IN_SCREEN"));

	dooms::input::GraphicsAPIInput::SetCursorEnterCallback(UserInput_Server::CursorEnterCallback);
	dooms::input::GraphicsAPIInput::SetCursorPosition_Callback(UserInput_Server::CursorPosition_Callback);
	dooms::input::GraphicsAPIInput::SetScroll_Callback(UserInput_Server::Scroll_Callback);
	dooms::input::GraphicsAPIInput::SetKey_Callback(UserInput_Server::Key_Callback);
	dooms::input::GraphicsAPIInput::SetMouseButton_Callback(UserInput_Server::MouseButton_Callback);
}

void UserInput_Server::ResetCursorPosition()
{
	UserInput_Server::mDeltaCursorScreenPosition.x = 0;
	UserInput_Server::mDeltaCursorScreenPosition.y = 0;

	UserInput_Server::mScrollOffset.x = 0;
	UserInput_Server::mScrollOffset.y = 0;
}

void UserInput_Server::UpdateInput()
{

	ResetCursorPosition();

	UpdateKeyStates();

	dooms::input::GraphicsAPIInput::PollEvents();
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
		dooms::input::GraphicsAPIInput::SetCursorMode(dooms::graphics::GraphicsAPI::GetPlatformWindow(), dooms::input::GraphicsAPIInput::eCursorMode::SHOW_CURSOR_UNLOCK_CURSOR_FROM_WINDOW);
	}
	else if (UserInput_Server::IsCursorLockedInScreen == false && UserInput_Server::IsCursorVisible == false)
	{
		dooms::input::GraphicsAPIInput::SetCursorMode(dooms::graphics::GraphicsAPI::GetPlatformWindow(), dooms::input::GraphicsAPIInput::eCursorMode::HIDE_CURSOR_UNLOCK_CURSOR_FROM_WINDOW);
	}
	else if (UserInput_Server::IsCursorLockedInScreen == true && UserInput_Server::IsCursorVisible == false)
	{
		dooms::input::GraphicsAPIInput::SetCursorMode(dooms::graphics::GraphicsAPI::GetPlatformWindow(), dooms::input::GraphicsAPIInput::eCursorMode::HIDE_CURSOR_LOCK_CURSOR_ON_WINDOW);
	}
	else if (UserInput_Server::IsCursorLockedInScreen == true && UserInput_Server::IsCursorVisible == true)
	{
		D_DEBUG_LOG(eLogType::D_WARNING, "Undefined Cursor Mode, There is no mode that locked in screen and visible"); // https://www.glfw.org/docs/3.3/input_guide.html
		dooms::input::GraphicsAPIInput::SetCursorMode(dooms::graphics::GraphicsAPI::GetPlatformWindow(), dooms::input::GraphicsAPIInput::eCursorMode::HIDE_CURSOR_LOCK_CURSOR_ON_WINDOW);
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
