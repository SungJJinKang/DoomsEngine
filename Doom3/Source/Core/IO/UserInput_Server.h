#pragma once

#include <array>

#include "../Core.h"
#include"../Game/IGameFlow.h"
#include "KEY_Code.h"
#include <Vector2.h>
#include <Vector3.h>






#include "UserInput_Server.reflection.h"
namespace dooms
{
	class GameCore;

	D_NAMESPACE(dooms::userinput)
	namespace userinput
	{
		
		enum class D_ENUM eKeyState : INT32
		{
			NONE = 0,
			PRESS_DOWN,
			PRESSING,
			UP
		};
		
		inline constexpr extern dooms::graphics::GraphicsAPIInput::eKEY_CODE FIRST_KEY_CODE = graphics::GraphicsAPIInput::eKEY_CODE::KEY_SPACE;;
		inline constexpr extern graphics::GraphicsAPIInput::eKEY_CODE LAST_KEY_CODE = graphics::GraphicsAPIInput::eKEY_CODE::KEY_MENU;;
		

		enum class D_ENUM eMouse_Button_Action : INT32
		{
			NONE,
			PRESSING,
			DOWN,
			RELEASE	
		};

		inline constexpr extern dooms::graphics::GraphicsAPIInput::eMoustInput FIRST_MOUSE_BUTTON_TYPE = dooms::graphics::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_LEFT;
		inline constexpr extern dooms::graphics::GraphicsAPIInput::eMoustInput LAST_MOUSE_BUTTON_TYPE = dooms::graphics::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_MIDDLE;

		
		/// <summary>
		/// https://www.glfw.org/docs/3.3/input_guide.html
		/// </summary>
		class DOOM_API D_CLASS UserInput_Server : public IGameFlow, public ISingleton<UserInput_Server>
		{
			GENERATE_BODY()
			

		private:

			static inline math::Vector2 mScrollOffset{nullptr};

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
			static inline math::Vector2  mCurrentCursorScreenPosition{ nullptr };
			static inline math::Vector2  mCurrentCursorNDCPosition{ nullptr };
			static inline math::Vector3  mCurrentCursorWorldPosition{ nullptr };
			static void UpdateCurrentCursorScreenPosition();
		
			static inline math::Vector2  mDeltaCursorScreenPosition{ nullptr };

		

		

			

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

			NO_DISCARD FORCE_INLINE static bool GetKeyToggle(dooms::graphics::GraphicsAPIInput::eKEY_CODE keyCode) noexcept
			{
				return UserInput_Server::mKeyToggle[static_cast<INT32>(keyCode) - static_cast<INT32>(FIRST_KEY_CODE)];
			}

			/// <summary>
			/// Key is being pressed ?
			/// </summary>
			/// <param name="keyCode"></param>
			/// <returns></returns>
			NO_DISCARD FORCE_INLINE static bool GetKey(dooms::graphics::GraphicsAPIInput::eKEY_CODE keyCode) noexcept
			{
				return UserInput_Server::mKeyState[static_cast<INT32>(keyCode) - static_cast<INT32>(FIRST_KEY_CODE)] == eKeyState::PRESSING;
			}
			/// <summary>
			/// Key is Released ?
			/// </summary>
			/// <param name="keyCode"></param>
			/// <returns></returns>
			NO_DISCARD FORCE_INLINE static bool GetKeyUp(dooms::graphics::GraphicsAPIInput::eKEY_CODE keyCode) noexcept
			{
				return UserInput_Server::mKeyState[static_cast<INT32>(keyCode) - static_cast<INT32>(FIRST_KEY_CODE)] == eKeyState::UP;
			}

			NO_DISCARD FORCE_INLINE static bool GetKeyDown(dooms::graphics::GraphicsAPIInput::eKEY_CODE keyCode) noexcept
			{
				return UserInput_Server::mKeyState[static_cast<INT32>(keyCode) - static_cast<INT32>(FIRST_KEY_CODE)] == eKeyState::PRESS_DOWN;
			}

		
			NO_DISCARD FORCE_INLINE static math::Vector2 GetCurrentMouseScreenPosition() noexcept
			{
				return UserInput_Server::mCurrentCursorScreenPosition;
			}
			NO_DISCARD FORCE_INLINE static math::Vector2 GetCurrentMouseNDCPosition() noexcept
			{
				return UserInput_Server::mCurrentCursorNDCPosition;
			}
			NO_DISCARD FORCE_INLINE static math::Vector3 GetCurrentMouseWorldPosition() noexcept
			{
				return UserInput_Server::mCurrentCursorWorldPosition;
			}

			/// <summary>
			/// Screen Position 
			/// </summary>
			/// <returns></returns>
			NO_DISCARD FORCE_INLINE static FLOAT32 GetCurrentMouseScreenPositionX() noexcept
			{
				return UserInput_Server::mCurrentCursorScreenPosition.x;
			}
			/// <summary>
			/// Screen Position 
			/// </summary>
			/// <returns></returns>
			NO_DISCARD FORCE_INLINE static FLOAT32 GetCurrentMouseScreenPositionY() noexcept
			{
				return UserInput_Server::mCurrentCursorScreenPosition.y;
			}


			NO_DISCARD FORCE_INLINE static math::Vector2 GetDeltaMouseScreenPosition() noexcept
			{
				return UserInput_Server::mDeltaCursorScreenPosition;
			}
			/// <summary>
			/// Delta
			/// </summary>
			/// <returns></returns>
			NO_DISCARD FORCE_INLINE static FLOAT32 GetDeltaMouseScreenPositionX() noexcept
			{
				return UserInput_Server::mDeltaCursorScreenPosition.x;
			}
			/// <summary>
			/// Delta
			/// </summary>
			/// <returns></returns>
			NO_DISCARD FORCE_INLINE static FLOAT32 GetDeltaMouseScreenPositionY() noexcept
			{
				return UserInput_Server::mDeltaCursorScreenPosition.y;
			}


			NO_DISCARD FORCE_INLINE static math::Vector2 GetMouseScrollOffset() noexcept
			{
				return UserInput_Server::mScrollOffset;
			}
			/// <summary>
			/// -1 ~ 1
			/// </summary>
			/// <returns></returns>
			NO_DISCARD FORCE_INLINE static FLOAT32 GetMouseScrollOffsetX() noexcept
			{
				return UserInput_Server::mScrollOffset.x;
			}
			/// <summary>
			/// -1 ~ 1
			/// </summary>
			/// <returns></returns>
			NO_DISCARD FORCE_INLINE static FLOAT32 GetMouseScrollOffsetY() noexcept
			{
				return UserInput_Server::mScrollOffset.y;
			}

			NO_DISCARD FORCE_INLINE static bool GetMouseButtonPressing(dooms::graphics::GraphicsAPIInput::eMoustInput mouse_button_type) noexcept
			{
				return UserInput_Server::mMouseButtonState[static_cast<INT32>(mouse_button_type)] == eMouse_Button_Action::PRESSING;
			}
			NO_DISCARD FORCE_INLINE static bool GetMouseButtonDown(dooms::graphics::GraphicsAPIInput::eMoustInput mouse_button_type) noexcept
			{
				return UserInput_Server::mMouseButtonState[static_cast<INT32>(mouse_button_type)] == eMouse_Button_Action::DOWN;
			}
			NO_DISCARD FORCE_INLINE static bool GetMouseButtonRelease(dooms::graphics::GraphicsAPIInput::eMoustInput mouse_button_type) noexcept
			{
				return UserInput_Server::mMouseButtonState[static_cast<INT32>(mouse_button_type)] == eMouse_Button_Action::RELEASE;
			}

			FORCE_INLINE static bool GetIsCursorOnScreenWindow() noexcept
			{
				return UserInput_Server::IsCursorOnScreenWindow;
			}

			static void SetIsCursorVisible(bool isVisible) noexcept;
			static void SetIsCursorLockedInScreen(bool isLocked) noexcept;

			
			static void CursorEnterCallback(INT32 entered);
			static void CursorPosition_Callback(FLOAT64 xpos, FLOAT64 ypos);
			static void Scroll_Callback(FLOAT64 xoffset, FLOAT64 yoffset);
			static void Key_Callback(INT32 key, INT32 scancode, INT32 action, INT32 mods);
			static void MouseButton_Callback(INT32 button, INT32 action, INT32 mods);
		};

	}
}

using namespace dooms::userinput;
using dooms::userinput::eMouse_Button_Action;

