#pragma once

#include <array>

#include "../Core.h"
#include"../Game/IGameFlow.h"
#include"../API/OpenglAPI.h"
#include "KEY_Code.h"
#include "../Graphics/Graphics_Server.h"
#include <Vector2.h>







namespace doom
{
	class GameCore;

	namespace userinput
	{
		
		enum class eKeyState : INT32
		{
			NONE = 0,
			PRESS_DOWN,
			PRESSING,
			UP
		};
		
		inline constexpr extern eKEY_CODE FIRST_KEY_CODE = doom::userinput::eKEY_CODE::KEY_SPACE;;
		inline constexpr extern eKEY_CODE LAST_KEY_CODE = doom::userinput::eKEY_CODE::KEY_MENU;;


		enum class eMouse_Button_Type : INT32
		{
			MOUST_BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
			MOUST_BUTTON_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
			MOUST_BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE
		};
		

		enum class eMouse_Button_Action : INT32
		{
			NONE,
			PRESSING,
			DOWN,
			RELEASE	
		};

		inline constexpr extern eMouse_Button_Type FIRST_MOUSE_BUTTON_TYPE = eMouse_Button_Type::MOUST_BUTTON_LEFT;
		inline constexpr extern eMouse_Button_Type LAST_MOUSE_BUTTON_TYPE = eMouse_Button_Type::MOUST_BUTTON_MIDDLE;

		
		/// <summary>
		/// https://www.glfw.org/docs/3.3/input_guide.html
		/// </summary>
		class DOOM_API UserInput_Server : public IGameFlow, public ISingleton<UserInput_Server>
		{
			DOBJECT_CLASS_BODY(UserInput_Server, doom::eDOBJECT_ClassFlags::NonCopyable);

		private:

			static inline math::Vector2 mScrollOffset{};

			static inline std::array<bool, static_cast<INT32>(LAST_KEY_CODE) - static_cast<INT32>(FIRST_KEY_CODE) + 1> mKeyToggle{};
			static inline std::array<eKeyState, static_cast<INT32>(LAST_KEY_CODE) - static_cast<INT32>(FIRST_KEY_CODE) + 1> mKeyState{};

			/// <summary>
			/// Keys what was down at last frame
			/// </summary>
			static inline std::vector<INT32> mDownKeys{};
			/// <summary>
			/// Keys what was up at last frame
			/// </summary>
			static inline std::vector<INT32> mUpKeys{};
			void UpdateKeyStates();

			static inline std::array<eMouse_Button_Action, static_cast<INT32>(LAST_MOUSE_BUTTON_TYPE) - static_cast<INT32>(FIRST_MOUSE_BUTTON_TYPE) + 1> mMouseButtonState{};
			void UpdateMouseButtonStates();
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

		

		

			static void CursorEnterCallback(GLFWwindow* window, INT32 entered);
			static void CursorPosition_Callback(GLFWwindow* window, FLOAT64 xpos, FLOAT64 ypos);
			static void Scroll_Callback(GLFWwindow* window, FLOAT64 xoffset, FLOAT64 yoffset);
			static void Key_Callback(GLFWwindow* window, INT32 key, INT32 scancode, INT32 action, INT32 mods);
			static void MouseButton_Callback(GLFWwindow* window, INT32 button, INT32 action, INT32 mods);

			static inline bool IsCursorOnScreenWindow{ true };
			static inline bool IsCursorLockedInScreen{ false };
			static inline bool IsCursorVisible{ true };
			static inline bool mScrollChangedAtPreviousFrame{ true };

			void UpdateCursorMode();

		public:

			UserInput_Server();

			virtual void Init() final;
			virtual void Update() final;
			virtual void OnEndOfFrame() final;

			[[nodiscard]] FORCE_INLINE static bool GetKeyToggle(eKEY_CODE keyCode) noexcept
			{
				return UserInput_Server::mKeyToggle[static_cast<INT32>(keyCode) - static_cast<INT32>(FIRST_KEY_CODE)];
			}

			/// <summary>
			/// Key is being pressed ?
			/// </summary>
			/// <param name="keyCode"></param>
			/// <returns></returns>
			[[nodiscard]] FORCE_INLINE static bool GetKey(eKEY_CODE keyCode) noexcept
			{
				return UserInput_Server::mKeyState[static_cast<INT32>(keyCode) - static_cast<INT32>(FIRST_KEY_CODE)] == eKeyState::PRESSING;
			}
			/// <summary>
			/// Key is Released ?
			/// </summary>
			/// <param name="keyCode"></param>
			/// <returns></returns>
			[[nodiscard]] FORCE_INLINE static bool GetKeyUp(eKEY_CODE keyCode) noexcept
			{
				return UserInput_Server::mKeyState[static_cast<INT32>(keyCode) - static_cast<INT32>(FIRST_KEY_CODE)] == eKeyState::UP;
			}

			/// <summary>
			/// Key is pressed? ( not being pressed, if you want this use GetKey )
			/// TODO : 현재는 그냥 안누른 상태를 TRUE로 리턴한다
			/// TODO : 내가 원하는건 누르고 있다 안누른 그 순간을 TRUE로 리턴하는거다
			/// </summary>
			/// <param name="keyCode"></param>
			/// <returns></returns>
			[[nodiscard]] FORCE_INLINE static bool GetKeyDown(eKEY_CODE keyCode) noexcept
			{
				return UserInput_Server::mKeyState[static_cast<INT32>(keyCode) - static_cast<INT32>(FIRST_KEY_CODE)] == eKeyState::PRESS_DOWN;
			}

		
			[[nodiscard]] FORCE_INLINE static math::Vector2 GetCurrentMouseScreenPosition() noexcept
			{
				return UserInput_Server::mCurrentCursorScreenPosition;
			}
			[[nodiscard]] FORCE_INLINE static math::Vector2 GetCurrentMouseNDCPosition() noexcept
			{
				return UserInput_Server::mCurrentCursorNDCPosition;
			}
			[[nodiscard]] FORCE_INLINE static math::Vector3 GetCurrentMouseWorldPosition() noexcept
			{
				return UserInput_Server::mCurrentCursorWorldPosition;
			}

			/// <summary>
			/// Screen Position 
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] FORCE_INLINE static FLOAT32 GetCurrentMouseScreenPositionX() noexcept
			{
				return UserInput_Server::mCurrentCursorScreenPosition.x;
			}
			/// <summary>
			/// Screen Position 
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] FORCE_INLINE static FLOAT32 GetCurrentMouseScreenPositionY() noexcept
			{
				return UserInput_Server::mCurrentCursorScreenPosition.y;
			}


			[[nodiscard]] FORCE_INLINE static math::Vector2 GetDeltaMouseScreenPosition() noexcept
			{
				return UserInput_Server::mDeltaCursorScreenPosition;
			}
			/// <summary>
			/// Delta
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] FORCE_INLINE static FLOAT32 GetDeltaMouseScreenPositionX() noexcept
			{
				return UserInput_Server::mDeltaCursorScreenPosition.x;
			}
			/// <summary>
			/// Delta
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] FORCE_INLINE static FLOAT32 GetDeltaMouseScreenPositionY() noexcept
			{
				return UserInput_Server::mDeltaCursorScreenPosition.y;
			}


			[[nodiscard]] FORCE_INLINE static math::Vector2 GetMouseScrollOffset() noexcept
			{
				return UserInput_Server::mScrollOffset;
			}
			/// <summary>
			/// -1 ~ 1
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] FORCE_INLINE static FLOAT32 GetMouseScrollOffsetX() noexcept
			{
				return UserInput_Server::mScrollOffset.x;
			}
			/// <summary>
			/// -1 ~ 1
			/// </summary>
			/// <returns></returns>
			[[nodiscard]] FORCE_INLINE static FLOAT32 GetMouseScrollOffsetY() noexcept
			{
				return UserInput_Server::mScrollOffset.y;
			}

			[[nodiscard]] FORCE_INLINE static bool GetMouseButtonPressing(eMouse_Button_Type mouse_button_type) noexcept
			{
				return UserInput_Server::mMouseButtonState[static_cast<INT32>(mouse_button_type)] == eMouse_Button_Action::PRESSING;
			}
			[[nodiscard]] FORCE_INLINE static bool GetMouseButtonDown(eMouse_Button_Type mouse_button_type) noexcept
			{
				return UserInput_Server::mMouseButtonState[static_cast<INT32>(mouse_button_type)] == eMouse_Button_Action::DOWN;
			}
			[[nodiscard]] FORCE_INLINE static bool GetMouseButtonRelease(eMouse_Button_Type mouse_button_type) noexcept
			{
				return UserInput_Server::mMouseButtonState[static_cast<INT32>(mouse_button_type)] == eMouse_Button_Action::RELEASE;
			}

			FORCE_INLINE static bool GetIsCursorOnScreenWindow() noexcept
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

