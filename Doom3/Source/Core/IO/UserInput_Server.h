#pragma once

#include <array>

#include "../Core.h"
#include"../Game/IGameFlow.h"
#include"../API/OpenglAPI.h"
#include "../Graphics/Graphics_Server.h"
#include <Vector2.h>


#include <magic_enum.hpp>




namespace doom
{
	class GameCore;

	namespace userinput
	{

		enum eKEY_CODE : int
		{
			KEY_SPACE = GLFW_KEY_SPACE,
			KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE,
			KEY_COMMA = GLFW_KEY_COMMA,
			KEY_MINUS = GLFW_KEY_MINUS,
			KEY_PERIOD = GLFW_KEY_PERIOD,
			KEY_SLASH = GLFW_KEY_SLASH,
			KEY_0 = GLFW_KEY_0,
			KEY_1 = GLFW_KEY_1,
			KEY_2 = GLFW_KEY_2,
			KEY_3 = GLFW_KEY_3,
			KEY_4 = GLFW_KEY_4,
			KEY_5 = GLFW_KEY_5,
			KEY_6 = GLFW_KEY_6,
			KEY_7 = GLFW_KEY_7,
			KEY_8 = GLFW_KEY_8,
			KEY_9 = GLFW_KEY_9,
			KEY_SEMICOLON = GLFW_KEY_SEMICOLON,
			KEY_EQUAL = GLFW_KEY_EQUAL,
			KEY_A = GLFW_KEY_A,
			KEY_B = GLFW_KEY_B,
			KEY_C = GLFW_KEY_C,
			KEY_D = GLFW_KEY_D,
			KEY_E = GLFW_KEY_E,
			KEY_F = GLFW_KEY_F,
			KEY_G = GLFW_KEY_G,
			KEY_H = GLFW_KEY_H,
			KEY_I = GLFW_KEY_I,
			KEY_J = GLFW_KEY_J,
			KEY_K = GLFW_KEY_K,
			KEY_L = GLFW_KEY_L,
			KEY_M = GLFW_KEY_M,
			KEY_N = GLFW_KEY_N,
			KEY_O = GLFW_KEY_O,
			KEY_P = GLFW_KEY_P,
			KEY_Q = GLFW_KEY_Q,
			KEY_R = GLFW_KEY_R,
			KEY_S = GLFW_KEY_S,
			KEY_T = GLFW_KEY_T,
			KEY_U = GLFW_KEY_U,
			KEY_V = GLFW_KEY_V,
			KEY_W = GLFW_KEY_W,
			KEY_X = GLFW_KEY_X,
			KEY_Y = GLFW_KEY_Y,
			KEY_Z = GLFW_KEY_Z,
			KEY_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
			KEY_BACKSLASH = GLFW_KEY_BACKSLASH,
			KEY_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
			KEY_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
			KEY_WORLD_1 = GLFW_KEY_WORLD_1,
			KEY_WORLD_2 = GLFW_KEY_WORLD_2,
			KEY_ESCAPE = GLFW_KEY_ESCAPE,
			KEY_ENTER = GLFW_KEY_ENTER,
			KEY_TAB = GLFW_KEY_TAB,
			KEY_BACKSPACE = GLFW_KEY_BACKSPACE,
			KEY_INSERT = GLFW_KEY_INSERT,
			KEY_DELETE = GLFW_KEY_DELETE,
			KEY_RIGHT = GLFW_KEY_RIGHT,
			KEY_LEFT = GLFW_KEY_LEFT,
			KEY_DOWN = GLFW_KEY_DOWN,
			KEY_UP = GLFW_KEY_UP,
			KEY_PAGE_UP = GLFW_KEY_PAGE_UP,
			KEY_PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
			KEY_HOME = GLFW_KEY_HOME,
			KEY_END = GLFW_KEY_END,
			KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
			KEY_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
			KEY_NUM_LOCK = GLFW_KEY_NUM_LOCK,
			KEY_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
			KEY_PAUSE = GLFW_KEY_PAUSE,
			KEY_F1 = GLFW_KEY_F1,
			KEY_F2 = GLFW_KEY_F2,
			KEY_F3 = GLFW_KEY_F3,
			KEY_F4 = GLFW_KEY_F4,
			KEY_F5 = GLFW_KEY_F5,
			KEY_F6 = GLFW_KEY_F6,
			KEY_F7 = GLFW_KEY_F7,
			KEY_F8 = GLFW_KEY_F8,
			KEY_F9 = GLFW_KEY_F9,
			KEY_F10 = GLFW_KEY_F10,
			KEY_F11 = GLFW_KEY_F11,
			KEY_F12 = GLFW_KEY_F12,
			KEY_F13 = GLFW_KEY_F13,
			KEY_F14 = GLFW_KEY_F14,
			KEY_F15 = GLFW_KEY_F15,
			KEY_F16 = GLFW_KEY_F16,
			KEY_F17 = GLFW_KEY_F17,
			KEY_F18 = GLFW_KEY_F18,
			KEY_F19 = GLFW_KEY_F19,
			KEY_F20 = GLFW_KEY_F20,
			KEY_F21 = GLFW_KEY_F21,
			KEY_F22 = GLFW_KEY_F22,
			KEY_F23 = GLFW_KEY_F23,
			KEY_F24 = GLFW_KEY_F24,
			KEY_F25 = GLFW_KEY_F25,
			KEY_KP_0 = GLFW_KEY_KP_0,
			KEY_KP_1 = GLFW_KEY_KP_1,
			KEY_KP_2 = GLFW_KEY_KP_2,
			KEY_KP_3 = GLFW_KEY_KP_3,
			KEY_KP_4 = GLFW_KEY_KP_4,
			KEY_KP_5 = GLFW_KEY_KP_5,
			KEY_KP_6 = GLFW_KEY_KP_6,
			KEY_KP_7 = GLFW_KEY_KP_7,
			KEY_KP_8 = GLFW_KEY_KP_8,
			KEY_KP_9 = GLFW_KEY_KP_9,
			KEY_KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
			KEY_KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
			KEY_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
			KEY_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
			KEY_KP_ADD = GLFW_KEY_KP_ADD,
			KEY_KP_ENTER = GLFW_KEY_KP_ENTER,
			KEY_KP_EQUAL = GLFW_KEY_KP_EQUAL,
			KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
			KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
			KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT,
			KEY_LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
			KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
			KEY_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
			KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
			KEY_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
			KEY_MENU = GLFW_KEY_MENU,

		};

		enum eKeyState : int
		{
			NONE = 0,
			PRESS_DOWN,
			PRESSING,
			UP
		};


		inline constexpr eKEY_CODE FIRST_KEY_CODE{ magic_enum::enum_value<eKEY_CODE>(0) };
		inline constexpr eKEY_CODE LAST_KEY_CODE{ magic_enum::enum_value<eKEY_CODE>(magic_enum::enum_count<eKEY_CODE>() - 1) };


		enum eMouse_Button_Type : int
		{
			MOUST_BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
			MOUST_BUTTON_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
			MOUST_BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE
		};

		enum eMouse_Button_Action : int
		{
			PRESS = GLFW_PRESS,
			RELEASE = GLFW_RELEASE
		};

		/// <summary>
		/// https://www.glfw.org/docs/3.3/input_guide.html
		/// </summary>
		class UserInput_Server : public IGameFlow, public ISingleton<UserInput_Server>
		{
			friend class::doom::GameCore;

			

		private:

			static inline math::Vector2 mScrollOffset{};

			static inline std::array<bool, LAST_KEY_CODE - FIRST_KEY_CODE + 1> mKeyToggle{};
			static inline std::array<eKeyState, LAST_KEY_CODE - FIRST_KEY_CODE + 1> mKeyState{};

			/// <summary>
			/// Keys what was down at last frame
			/// </summary>
			static inline std::vector<int> mDownKeys{};
			/// <summary>
			/// Keys what was up at last frame
			/// </summary>
			static inline std::vector<int> mUpKeys{};
			void UpdateKeyStates();

			/// <summary>
			/// The callback functions receives the cursor position, measured in screen coordinates but relative to the top-left corner of the window content area. 
			/// In Opengl, Screen Point is relative to top-left corner
			/// So Top of Screen will return y value -1
			/// </summary>
			static inline math::Vector2  mCurrentCursorScreenPosition{};
			static inline math::Vector2  mCurrentCursorNDCPosition{};
			static inline math::Vector3  mCurrentCursorWorldPosition{};
			static void UpdateCurrentCursorScreenPosition();
		
			static inline math::Vector2  mDeltaCursorScreenPosition{};

			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;

			UserInput_Server();

			static void CursorEnterCallback(GLFWwindow* window, int entered);
			static void CursorPosition_Callback(GLFWwindow* window, double xpos, double ypos);
			static void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);
			static void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void MouseButton_Callback(GLFWwindow* window, int button, int action, int mods);

			static inline bool IsCursorOnScreenWindow{ true };
			static inline bool IsCursorLockedInScreen{ false };
			static inline bool IsCursorVisible{ true };
			static inline bool mScrollChangedAtPreviousFrame{ true };

			void UpdateCursorMode();
		public:

			[[nodiscard]] static bool GetKeyToggle(eKEY_CODE keyCode) noexcept
			{
				return UserInput_Server::mKeyToggle[keyCode - FIRST_KEY_CODE];
			}

			/// <summary>
			/// Key is being pressed ?
			/// </summary>
			/// <param name="keyCode"></param>
			/// <returns></returns>
			[[nodiscard]] static bool GetKey(eKEY_CODE keyCode) noexcept
			{
				return UserInput_Server::mKeyState[keyCode - FIRST_KEY_CODE] == eKeyState::PRESSING;
			}
			/// <summary>
			/// Key is Released ?
			/// </summary>
			/// <param name="keyCode"></param>
			/// <returns></returns>
			[[nodiscard]] static bool GetKeyUp(eKEY_CODE keyCode) noexcept
			{
				return UserInput_Server::mKeyState[keyCode - FIRST_KEY_CODE] == eKeyState::UP;
			}

			/// <summary>
			/// Key is pressed? ( not being pressed, if you want this use GetKey )
			/// TODO : 현재는 그냥 안누른 상태를 TRUE로 리턴한다
			/// TODO : 내가 원하는건 누르고 있다 안누른 그 순간을 TRUE로 리턴하는거다
			/// </summary>
			/// <param name="keyCode"></param>
			/// <returns></returns>
			[[nodiscard]] static bool GetKeyDown(eKEY_CODE keyCode) noexcept
			{
				return UserInput_Server::mKeyState[keyCode - FIRST_KEY_CODE] == eKeyState::PRESS_DOWN;
			}

		
			[[nodiscard]] static math::Vector2 GetCurrentMouseScreenPosition() noexcept
			{
				return UserInput_Server::mCurrentCursorScreenPosition;
			}
			[[nodiscard]] static math::Vector2 GetCurrentMouseNDCPosition() noexcept
			{
				return UserInput_Server::mCurrentCursorNDCPosition;
			}
			[[nodiscard]] static math::Vector3 GetCurrentMouseWorldPosition() noexcept
			{
				return UserInput_Server::mCurrentCursorWorldPosition;
			}

			/// <summary>
			/// Screen Position 
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] static double GetCurrentMouseScreenPositionX() noexcept
			{
				return UserInput_Server::mCurrentCursorScreenPosition.x;
			}
			/// <summary>
			/// Screen Position 
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] static double GetCurrentMouseScreenPositionY() noexcept
			{
				return UserInput_Server::mCurrentCursorScreenPosition.y;
			}


			[[nodiscard]] static math::Vector2 GetDeltaMouseScreenPosition() noexcept
			{
				return UserInput_Server::mDeltaCursorScreenPosition;
			}
			/// <summary>
			/// Delta
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] static double GetDeltaMouseScreenPositionX() noexcept
			{
				return UserInput_Server::mDeltaCursorScreenPosition.x;
			}
			/// <summary>
			/// Delta
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] static double GetDeltaMouseScreenPositionY() noexcept
			{
				return UserInput_Server::mDeltaCursorScreenPosition.y;
			}


			[[nodiscard]] static math::Vector2 GetMouseScrollOffset() noexcept
			{
				return UserInput_Server::mScrollOffset;
			}
			/// <summary>
			/// -1 ~ 1
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] static double GetMouseScrollOffsetX() noexcept
			{
				return UserInput_Server::mScrollOffset.x;
			}
			/// <summary>
			/// -1 ~ 1
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] static double GetMouseScrollOffsetY() noexcept
			{
				return UserInput_Server::mScrollOffset.y;
			}

			[[nodiscard]] static bool GetMouseButtonPress(eMouse_Button_Type mouse_button_type) noexcept
			{
				return glfwGetMouseButton(doom::graphics::Graphics_Server::Window, mouse_button_type) == eMouse_Button_Action::PRESS;
			}
			[[nodiscard]] static bool GetMouseButtonRelease(eMouse_Button_Type mouse_button_type) noexcept
			{
				return glfwGetMouseButton(doom::graphics::Graphics_Server::Window, mouse_button_type) == eMouse_Button_Action::RELEASE;
			}

			static bool GetIsCursorOnScreenWindow() noexcept
			{
				return UserInput_Server::IsCursorOnScreenWindow;
			}

			static void SetIsCursorVisible(bool isVisible) noexcept;
			static void SetIsCursorLockedInScreen(bool isLocked) noexcept;

			

		};

	}
}

using namespace doom::userinput;
using doom::userinput::eKEY_CODE;
using doom::userinput::eMouse_Button_Type;
using doom::userinput::eMouse_Button_Action;

