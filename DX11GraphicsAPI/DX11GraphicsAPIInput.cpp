#include "DX11GraphicsAPIInput.h"

#include "Input/GraphicsAPIInput.h"

#include <cassert>

#include "InputHelper/Keyboard.h"
#include "InputHelper/Mouse.h"

#undef ASSUME_ZERO
#ifdef _DEBUG
#define ASSUME_ZERO assert(false)
#else
#define ASSUME_ZERO __assume(0)
#endif

namespace dooms
{
	namespace input
	{
		namespace dx11
		{
			static std::unique_ptr<DirectX::Mouse> DX11Mouse{};
			static void ConstructDX11MouseIfRequired()
			{
				if(static_cast<bool>(DX11Mouse) == false)
				{
					dx11::DX11Mouse = std::make_unique<DirectX::Mouse>();
				}
			}
			static std::unique_ptr<DirectX::Keyboard> DX11Keyboard{};
			static void ConstructDX11KeyboardIfRequired()
			{
				if (static_cast<bool>(DX11Keyboard) == false)
				{
					dx11::DX11Keyboard = std::make_unique<DirectX::Keyboard>();
				}
			}
			static HWND DX11HWND = NULL;

			static input::GraphicsAPIInput::CursorEnterCallback mCursorEnterCallback = nullptr;
			static input::GraphicsAPIInput::CursorPosition_Callback mCursorPosition_Callback = nullptr;
			static input::GraphicsAPIInput::Scroll_Callback mScroll_Callback = nullptr;
			static input::GraphicsAPIInput::Key_Callback mKey_Callback = nullptr;
			static input::GraphicsAPIInput::MouseButton_Callback mMouseButton_Callback = nullptr;


			FORCE_INLINE extern dooms::input::GraphicsAPIInput::eKEY_CODE Convert_VirtualKey_To_eKeyCode(const unsigned int virtualKeyCode)
			{
				switch (virtualKeyCode)
				{
				case VK_SPACE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SPACE;

				/*
				case DIKEYBOARD_APOSTROPHE: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_APOSTROPHE;
					*/

				case VK_OEM_COMMA:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_COMMA;
				case VK_OEM_MINUS:
					return  dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_MINUS;
				case VK_OEM_PERIOD:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PERIOD;

				/*
				case DIKEYBOARD_SLASH:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SLASH;
					*/

				case 0x30:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_0;
				case 0x31:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_1;
				case 0x32:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_2;
				case 0x33:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_3;
				case 0x34:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_4;
				case 0x35:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_5;
				case 0x36:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_6;
				case 0x37:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_7;
				case 0x38:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_8;
				case 0x39:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_9;

				/*
				case DIKEYBOARD_SEMICOLON:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SEMICOLON;
				case DIKEYBOARD_EQUALS:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_EQUAL;
					*/

				case 0x41:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_A;
				case 0x42:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_B;
				case 0x43:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_C;
				case 0x44:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_D;
				case 0x45:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_E;
				case 0x46:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F;
				case 0x47:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_G;
				case 0x48:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_H;
				case 0x49:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_I;
				case 0x4A:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_J;
				case 0x4B:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_K;
				case 0x4C:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_L;
				case 0x4D:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_M;
				case 0x4E:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_N;
				case 0x4F:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_O;
				case 0x50:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_P;
				case 0x51:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Q;
				case 0x52:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_R;
				case 0x53:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_S;
				case 0x54:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_T;
				case 0x55:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_U;
				case 0x56:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_V;
				case 0x57:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_W;
				case 0x58:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_X;
				case 0x59:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Y;
				case 0x5A:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Z;
				//case VK_LEFT_:
				//	return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_BRACKET;

				/*
				case DIKEYBOARD_BACKSLASH:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_BACKSLASH;
					*/

				//case VK_OEM_:
				//	return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_BRACKET;

				/*
				case DIKEYBOARD_GRAVE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_GRAVE_ACCENT;
				case DIKEYBOARD_WORLD_1: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_WORLD_1;
				case DIKEYBOARD_WORLD_2:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_WORLD_2;
					*/

				case VK_ESCAPE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_ESCAPE;
				case VK_RETURN:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_ENTER;
				case VK_TAB:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_TAB;
				case VK_BACK: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_BACKSPACE;
				case VK_INSERT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_INSERT;
				case VK_DELETE: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_DELETE;
				case VK_RIGHT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT;
				case VK_LEFT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT;
				case VK_DOWN:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_DOWN;
				case VK_UP: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_UP;
				case VK_PRIOR:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAGE_UP;
				case VK_NEXT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAGE_DOWN;
				case VK_HOME:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_HOME;
				case VK_END:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_END;
				case VK_CAPITAL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_CAPS_LOCK;
				case VK_SCROLL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SCROLL_LOCK;
				case VK_NUMLOCK: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_NUM_LOCK;
				case VK_PRINT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PRINT_SCREEN;
				case VK_PAUSE: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAUSE;
				case VK_F1:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F1;
				case VK_F2:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F2;
				case VK_F3:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F3;
				case VK_F4:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F4;
				case VK_F5:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F5;
				case VK_F6:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F6;
				case VK_F7:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F7;
				case VK_F8:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F8;
				case VK_F9:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F9;
				case VK_F10:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F10;
				case VK_F11:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F11;
				case VK_F12:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F12;
				case VK_F13:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F13;
				case VK_F14:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F14;
				case VK_F15:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F15;
				case VK_F16:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F16;
				case VK_F17:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F17;
				case VK_F18:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F18;
				case VK_F19:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F19;
				case VK_F20:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F20;
				case VK_F21:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F21;
				case VK_F22:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F22;
				case VK_F23:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F23;
				case VK_F24:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F25;
				case VK_NUMPAD0: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_0;
				case VK_NUMPAD1:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_1;
				case VK_NUMPAD2:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_2;
				case VK_NUMPAD3:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_3;
				case VK_NUMPAD4:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_4;
				case VK_NUMPAD5:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_5;
				case VK_NUMPAD6:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_6;
				case VK_NUMPAD7:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_7;
				case VK_NUMPAD8:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_8;
				case VK_NUMPAD9:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_9;
				case VK_DECIMAL: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_DECIMAL;
				case VK_DIVIDE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_DIVIDE;
				case VK_MULTIPLY: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_MULTIPLY;
				case VK_SUBTRACT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_SUBTRACT;
				case VK_ADD: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_ADD;

				/*
				case DIKEYBOARD_NUMPADENTER:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_ENTER;
				case DIKEYBOARD_NUMPADEQUALS:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_EQUAL;
					*/

				case VK_LSHIFT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_SHIFT;
				case VK_LCONTROL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_CONTROL;
				case VK_MENU:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_ALT;

				/*
				case VK_su: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_SUPER;
					*/

				case VK_RSHIFT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_SHIFT;
				case VK_RCONTROL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_CONTROL;
				//case VK_MENU:
				//	return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_ALT;

				/*
				case VK_RightAlt: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_SUPER;
				case DIKEYBOARD_MENU: 
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_MENU;
					*/

				default:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::UNKNOWN;
				}
			}

			
			
			FORCE_INLINE extern DirectX::Keyboard::Keys Convert_eKeyCode_To_DX11KeyCode(const dooms::input::GraphicsAPIInput::eKEY_CODE keyCode)
			{
				switch (keyCode)
				{
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SPACE:
					return DirectX::Keyboard::Keys::Space;

				/*
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_APOSTROPHE:
					return DIKEYBOARD_APOSTROPHE;
					*/

				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_COMMA:
					return DirectX::Keyboard::Keys::OemComma;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_MINUS:
					return DirectX::Keyboard::Keys::OemMinus; 
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PERIOD:
					return DirectX::Keyboard::Keys::OemPeriod;

				/*
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SLASH:
					return DIKEYBOARD_SLASH;
					*/

				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_0:
					return DirectX::Keyboard::Keys::D0;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_1:
					return DirectX::Keyboard::Keys::D1;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_2:
					return DirectX::Keyboard::Keys::D2;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_3:
					return DirectX::Keyboard::Keys::D3;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_4:
					return DirectX::Keyboard::Keys::D4;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_5:
					return DirectX::Keyboard::Keys::D5;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_6:
					return DirectX::Keyboard::Keys::D6;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_7:
					return DirectX::Keyboard::Keys::D7;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_8:
					return DirectX::Keyboard::Keys::D8;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_9:
					return DirectX::Keyboard::Keys::D9;

				/*
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SEMICOLON:
					return DIKEYBOARD_SEMICOLON;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_EQUAL:
					return DIKEYBOARD_EQUALS;
					*/

				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_A:
					return DirectX::Keyboard::Keys::A;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_B:
					return DirectX::Keyboard::Keys::B;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_C:
					return DirectX::Keyboard::Keys::C;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_D:
					return DirectX::Keyboard::Keys::D;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_E:
					return DirectX::Keyboard::Keys::E;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F:
					return DirectX::Keyboard::Keys::F;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_G:
					return DirectX::Keyboard::Keys::G;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_H:
					return DirectX::Keyboard::Keys::H;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_I:
					return DirectX::Keyboard::Keys::I;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_J:
					return DirectX::Keyboard::Keys::J;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_K:
					return DirectX::Keyboard::Keys::K;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_L:
					return DirectX::Keyboard::Keys::L;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_M:
					return DirectX::Keyboard::Keys::M;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_N:
					return DirectX::Keyboard::Keys::N;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_O:
					return DirectX::Keyboard::Keys::O;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_P:
					return DirectX::Keyboard::Keys::P;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Q:
					return DirectX::Keyboard::Keys::Q;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_R:
					return DirectX::Keyboard::Keys::R;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_S:
					return DirectX::Keyboard::Keys::S;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_T:
					return DirectX::Keyboard::Keys::T;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_U:
					return DirectX::Keyboard::Keys::U;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_V:
					return DirectX::Keyboard::Keys::V;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_W:
					return DirectX::Keyboard::Keys::W;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_X:
					return DirectX::Keyboard::Keys::X;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Y:
					return DirectX::Keyboard::Keys::Y;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Z:
					return DirectX::Keyboard::Keys::Z;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_BRACKET:
					return DirectX::Keyboard::Keys::OemOpenBrackets;

				/*
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_BACKSLASH:
					return DIKEYBOARD_BACKSLASH;
					*/

				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_BRACKET:
					return DirectX::Keyboard::Keys::OemCloseBrackets;

				/*
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_GRAVE_ACCENT:
					return DIKEYBOARD_GRAVE;
					*/

				
				/*
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_WORLD_1:
					return DIKEYBOARD_WORLD_1;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_WORLD_2:
					return DIKEYBOARD_WORLD_2; 
					*/
					
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_ESCAPE:
					return DirectX::Keyboard::Keys::Escape;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_ENTER:
					return DirectX::Keyboard::Keys::Enter;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_TAB:
					return DirectX::Keyboard::Keys::Tab; 
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_BACKSPACE:
					return DirectX::Keyboard::Keys::Back;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_INSERT:
					return DirectX::Keyboard::Keys::Insert; 
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_DELETE:
					return DirectX::Keyboard::Keys::Delete;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT:
					return DirectX::Keyboard::Keys::Right;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT:
					return DirectX::Keyboard::Keys::Left; 
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_DOWN:
					return DirectX::Keyboard::Keys::Down;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_UP:
					return DirectX::Keyboard::Keys::Up;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAGE_UP:
					return DirectX::Keyboard::Keys::PageUp;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAGE_DOWN:
					return DirectX::Keyboard::Keys::PageDown;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_HOME:
					return DirectX::Keyboard::Keys::Home; 
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_END:
					return DirectX::Keyboard::Keys::End;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_CAPS_LOCK:
					return DirectX::Keyboard::Keys::CapsLock; 
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SCROLL_LOCK:
					return DirectX::Keyboard::Keys::Scroll;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_NUM_LOCK:
					return DirectX::Keyboard::Keys::NumLock;
					
				
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PRINT_SCREEN:
					return DirectX::Keyboard::Keys::PrintScreen; 
					
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAUSE:
					return DirectX::Keyboard::Keys::Pause;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F1:
					return DirectX::Keyboard::Keys::F1;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F2:
					return DirectX::Keyboard::Keys::F2;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F3:
					return DirectX::Keyboard::Keys::F3;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F4:
					return DirectX::Keyboard::Keys::F4;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F5:
					return DirectX::Keyboard::Keys::F5;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F6:
					return DirectX::Keyboard::Keys::F6;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F7:
					return DirectX::Keyboard::Keys::F7;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F8:
					return DirectX::Keyboard::Keys::F8;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F9:
					return DirectX::Keyboard::Keys::F9;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F10:
					return DirectX::Keyboard::Keys::F10;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F11:
					return DirectX::Keyboard::Keys::F11;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F12:
					return DirectX::Keyboard::Keys::F12;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F13:
					return DirectX::Keyboard::Keys::F13;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F14:
					return DirectX::Keyboard::Keys::F14;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F15:
					return DirectX::Keyboard::Keys::F15;

				
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F16:
					return DirectX::Keyboard::Keys::F16;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F17:
					return DirectX::Keyboard::Keys::F17;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F18:
					return DirectX::Keyboard::Keys::F18;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F19:
					return DirectX::Keyboard::Keys::F19;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F20:
					return DirectX::Keyboard::Keys::F20;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F21:
					return DirectX::Keyboard::Keys::F21;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F22:
					return DirectX::Keyboard::Keys::F22;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F23:
					return DirectX::Keyboard::Keys::F23;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F24:
					return DirectX::Keyboard::Keys::F24;
				
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_0:
					return DirectX::Keyboard::Keys::NumPad0;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_1:
					return DirectX::Keyboard::Keys::NumPad1;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_2:
					return DirectX::Keyboard::Keys::NumPad2;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_3:
					return DirectX::Keyboard::Keys::NumPad3;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_4:
					return DirectX::Keyboard::Keys::NumPad4;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_5:
					return DirectX::Keyboard::Keys::NumPad5;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_6:
					return DirectX::Keyboard::Keys::NumPad6;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_7:
					return DirectX::Keyboard::Keys::NumPad7;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_8:
					return DirectX::Keyboard::Keys::NumPad8;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_9:
					return DirectX::Keyboard::Keys::NumPad9;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_DECIMAL:
					return DirectX::Keyboard::Keys::Decimal;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_DIVIDE:
					return DirectX::Keyboard::Keys::Divide; 
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_MULTIPLY:
					return DirectX::Keyboard::Keys::Multiply;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_SUBTRACT:
					return DirectX::Keyboard::Keys::Subtract; 
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_ADD:
					return DirectX::Keyboard::Keys::Add;

				/*
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_ENTER:
					return DIKEYBOARD_NUMPADENTER;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_EQUAL:
					return DIKEYBOARD_NUMPADEQUALS;
					*/

				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_SHIFT:
					return DirectX::Keyboard::Keys::LeftShift;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_CONTROL:
					return DirectX::Keyboard::Keys::LeftControl;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_ALT:
					return DirectX::Keyboard::Keys::LeftAlt;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_SUPER:
					return DirectX::Keyboard::Keys::LeftAlt;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_SHIFT:
					return DirectX::Keyboard::Keys::RightShift;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_CONTROL:
					return DirectX::Keyboard::Keys::RightControl;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_ALT:
					return DirectX::Keyboard::Keys::RightAlt;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_SUPER:
					return DirectX::Keyboard::Keys::RightAlt;
				/*
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_MENU:
					return DIKEYBOARD_MENU;
				default:
					return DIKEYBOARD_UNLABELED;
				*/

				default:
					assert(0);
					return (DirectX::Keyboard::Keys)-1;
				}
			}
			

			LRESULT _WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
			{
				if (!static_cast<bool>(dx11::DX11Mouse) || !static_cast<bool>(dx11::DX11Keyboard))
				{
					return 0;
				}

				switch (msg)
				{
					/*
					// WM_ACTIVATE is sent when the window is activated or deactivated.
					// We pause the game when the window is deactivated and unpause it
					// when it becomes active.
				case WM_ACTIVATE:
					if (LOWORD(wParam) == WA_INACTIVE)
					{
						m_AppPaused = true;
						m_Timer.Stop();
					}
					else
					{
						m_AppPaused = false;
						m_Timer.Start();
					}
					return 0;

					// WM_SIZE is sent when the user resizes the window.
				case WM_SIZE:
					// Save the new client area dimensions.
					m_ClientWidth = LOWORD(lParam);
					m_ClientHeight = HIWORD(lParam);
					if (m_pd3dDevice)
					{
						if (wParam == SIZE_MINIMIZED)
						{
							m_AppPaused = true;
							m_Minimized = true;
							m_Maximized = false;
						}
						else if (wParam == SIZE_MAXIMIZED)
						{
							m_AppPaused = false;
							m_Minimized = false;
							m_Maximized = true;
							OnResize();
						}
						else if (wParam == SIZE_RESTORED)
						{

							// Restoring from minimized state?
							if (m_Minimized)
							{
								m_AppPaused = false;
								m_Minimized = false;
								OnResize();
							}

							// Restoring from maximized state?
							else if (m_Maximized)
							{
								m_AppPaused = false;
								m_Maximized = false;
								OnResize();
							}
							else if (m_Resizing)
							{
								// If user is dragging the resize bars, we do not resize
								// the buffers here because as the user continuously
								// drags the resize bars, a stream of WM_SIZE messages are
								// sent to the window, and it would be pointless (and slow)
								// to resize for each WM_SIZE message received from dragging
								// the resize bars.  So instead, we reset after the user is
								// done resizing the window and releases the resize bars, which
								// sends a WM_EXITSIZEMOVE message.
							}
							else // API call such as SetWindowPos or m_pSwapChain->SetFullscreenState.
							{
								OnResize();
							}
						}
					}
					return 0;

					// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
				case WM_ENTERSIZEMOVE:
					m_AppPaused = true;
					m_Resizing = true;
					m_Timer.Stop();
					return 0;

					// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
					// Here we reset everything based on the new window dimensions.
				case WM_EXITSIZEMOVE:
					m_AppPaused = false;
					m_Resizing = false;
					m_Timer.Start();
					OnResize();
					return 0;
					*/

					// The WM_MENUCHAR message is sent when a menu is active and the user presses 
					// a key that does not correspond to any mnemonic or accelerator key. 
				case WM_MENUCHAR:
					// Don't beep when we alt-enter.
					return MAKELRESULT(0, MNC_CLOSE);

					// Catch this message so to prevent the window from becoming too small.
				case WM_GETMINMAXINFO:
					((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
					((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
					return 0;

					// 监测这些键盘/鼠标事件
				case WM_INPUT:
				case WM_LBUTTONDOWN:
				case WM_MBUTTONDOWN:
				case WM_RBUTTONDOWN:
				case WM_XBUTTONDOWN:
				case WM_LBUTTONUP:
				case WM_MBUTTONUP:
				case WM_RBUTTONUP:
				case WM_XBUTTONUP:

					dx11::DX11Mouse->ProcessMessage(msg, wParam, lParam);
					const DirectX::Mouse::State currentState = dx11::DX11Mouse->GetState();


					mMouseButton_Callback
					(
						dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_LEFT,
						(currentState.leftButton == true) ? dooms::input::GraphicsAPIInput::eInputActionType::PRESS : dooms::input::GraphicsAPIInput::eInputActionType::RELEASE,
						0 /* unused */
					);
					mMouseButton_Callback
					(
						dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_MIDDLE,
						(currentState.middleButton == true) ? dooms::input::GraphicsAPIInput::eInputActionType::PRESS : dooms::input::GraphicsAPIInput::eInputActionType::RELEASE,
						0 /* unused */
					);
					mMouseButton_Callback
					(
						dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_RIGHT,
						(currentState.rightButton == true) ? dooms::input::GraphicsAPIInput::eInputActionType::PRESS : dooms::input::GraphicsAPIInput::eInputActionType::RELEASE,
						0 /* unused */
					);

					return 0;

				case WM_MOUSEWHEEL:
					dx11::DX11Mouse->ProcessMessage(msg, wParam, lParam);
					const DirectX::Mouse::State _currentState = dx11::DX11Mouse->GetState();
					mScroll_Callback(0, _currentState.scrollWheelValue);
					return 0;

				case WM_MOUSEHOVER:
					dx11::DX11Mouse->ProcessMessage(msg, wParam, lParam);

					const DirectX::Mouse::State __currentState = dx11::DX11Mouse->GetState();
					mCursorPosition_Callback(__currentState.x, __currentState.y);
					mCursorEnterCallback(true);
					return 0;

				case WM_MOUSEMOVE:
					dx11::DX11Mouse->ProcessMessage(msg, wParam, lParam);

					const DirectX::Mouse::State ___currentState = dx11::DX11Mouse->GetState();
					mCursorPosition_Callback(___currentState.x, ___currentState.y);
					return 0;


				case WM_KEYDOWN:
				case WM_SYSKEYDOWN:
				case WM_KEYUP:
				case WM_SYSKEYUP:
				{
					const DirectX::Keyboard::KeyStateChange keyStateChange = dx11::DX11Keyboard->ProcessMessage(msg, wParam, lParam);

					mKey_Callback
					(
						Convert_VirtualKey_To_eKeyCode(keyStateChange.mVirtualKey),
						0, /* unused */
						(keyStateChange.mIsDown) == true ? dooms::input::GraphicsAPIInput::eInputActionType::PRESS : dooms::input::GraphicsAPIInput::eInputActionType::RELEASE,
						0 /* unused */
					);
					return 0;
				}

				case WM_ACTIVATEAPP:
					dx11::DX11Mouse->ProcessMessage(msg, wParam, lParam);
					dx11::DX11Keyboard->ProcessMessage(msg, wParam, lParam);

					const DirectX::Mouse::State ____currentState = dx11::DX11Mouse->GetState();
					mCursorPosition_Callback(____currentState.x, ____currentState.y);
					return 0;

				default:

					return 0;
				}

				return 0;
			}

			/*
			FORCE_INLINE extern unsigned int Convert_eMouseInput_To_GLFWMouseInput(const dooms::input::GraphicsAPIInput::eMoustInput mouseInput)
			{
				switch (mouseInput)
				{
				case dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_LEFT:
					return DirectX::Mouse::ButtonStateTracker::ButtonState:;
				case dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_RIGHT:
					return DIMOUSE_BUTTON1;
				case dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_MIDDLE:
					return DIMOUSE_BUTTON2;
				default:
					ASSUME_ZERO;
					return 0;
				}
			}

			FORCE_INLINE extern dooms::input::GraphicsAPIInput::eMoustInput Convert_GLFWMouseInput_To_eMouseInput(const unsigned int glfwMouseInput)
			{
				switch (glfwMouseInput)
				{
				case DIMOUSE_BUTTON0:
					return dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_LEFT;
				case DIMOUSE_BUTTON1:
					return dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_RIGHT;
				case DIMOUSE_BUTTON2:
					return dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_MIDDLE;
				default:
					ASSUME_ZERO;
				}
			}
			*/

			enum eCursorMode : unsigned int
			{
				CURSOR_MODE_NORMAL,
				CURSOR_MODE_HIDDEN,
				CURSOR_MODE_DISABLED,
			};

			
			/*
			FORCE_INLINE extern unsigned int GetGLCursorMode(const dooms::input::GraphicsAPIInput::eCursorMode cursorMode)
			{
				switch (cursorMode)
				{
				case dooms::input::GraphicsAPIInput::eCursorMode::CURSOR_MODE_NORMAL:
					return GLFW_CURSOR_NORMAL;
				case dooms::input::GraphicsAPIInput::eCursorMode::CURSOR_MODE_HIDDEN:
					return GLFW_CURSOR_HIDDEN;
				case dooms::input::GraphicsAPIInput::eCursorMode::CURSOR_MODE_DISABLED:
					return GLFW_CURSOR_DISABLED;
				default:
					ASSUME_ZERO;
					return 0;
				}
			}

			FORCE_INLINE extern input::GraphicsAPIInput::eInputActionType Convert_GLFWInputAction_To_eInputActionType(const unsigned int action)
			{
				switch (action)
				{
				case 0x80:
					return input::GraphicsAPIInput::eInputActionType::PRESS;

				case GLFW_RELEASE:
					return input::GraphicsAPIInput::eInputActionType::RELEASE;

				case GLFW_REPEAT:
					return input::GraphicsAPIInput::eInputActionType::REPEAT;
				}
			}
			*/
			
		}


		
		DOOMS_ENGINE_GRAPHICS_API unsigned int InitializeGraphisAPIInput(void* const platformWindow)
		{
			assert(platformWindow != 0);
			if(platformWindow == 0)
			{
				return 1;
			}

			dx11::DX11HWND = reinterpret_cast<HWND>(platformWindow);

			dx11::ConstructDX11MouseIfRequired();
			dx11::ConstructDX11KeyboardIfRequired();

			dx11::DX11Mouse->SetWindow(reinterpret_cast<HWND>(platformWindow));
			dx11::DX11Mouse->SetMode(DirectX::Mouse::Mode::MODE_ABSOLUTE);
			
			/*
			glfwSetCursorEnterCallback(glfwWindow, &dooms::input::dx11::CursorEnterCallback);
			glfwSetCursorPosCallback(glfwWindow, &dooms::input::dx11::CursorPosition_Callback);
			glfwSetScrollCallback(glfwWindow, &dooms::input::dx11::Scroll_Callback);

			glfwSetKeyCallback(glfwWindow, &dooms::input::dx11::Key_Callback);
			glfwSetMouseButtonCallback(glfwWindow, &dooms::input::dx11::MouseButton_Callback);
			*/

			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int DeInitializeGraphisAPIInput()
		{
			dx11::DX11Mouse.reset();
			dx11::DX11Keyboard.reset();

			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API void PollEvents()
		{
			MSG msg = { 0 };
			while (WM_QUIT != msg.message)
			{
				if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					break;
				}
			}
		}

		DOOMS_ENGINE_GRAPHICS_API void SetCursorMode(void* const platformWindow, const GraphicsAPIInput::eCursorMode cursorMode)
		{
			dx11::ConstructDX11MouseIfRequired();

			switch (cursorMode)
			{
			case GraphicsAPIInput::SHOW_CURSOR_UNLOCK_CURSOR_FROM_WINDOW: 
				dx11::DX11Mouse->SetVisible(true);
				ClipCursor(NULL);
				break;

			case GraphicsAPIInput::HIDE_CURSOR_UNLOCK_CURSOR_FROM_WINDOW: 
				dx11::DX11Mouse->SetVisible(false);
				ClipCursor(NULL);
				break;

			case GraphicsAPIInput::HIDE_CURSOR_LOCK_CURSOR_ON_WINDOW: 
				dx11::DX11Mouse->SetVisible(false);
				RECT rect;
				GetWindowRect(dx11::DX11HWND, &rect);
				ClipCursor(&rect);
				break;

			default:
				ASSUME_ZERO;
			}
			
			
			
		}


		DOOMS_ENGINE_GRAPHICS_API void SetCursorEnterCallback(input::GraphicsAPIInput::CursorEnterCallback cursorEnterCallback)
		{
			input::dx11::mCursorEnterCallback = cursorEnterCallback;
		}

		DOOMS_ENGINE_GRAPHICS_API void SetCursorPosition_Callback
		(
			input::GraphicsAPIInput::CursorPosition_Callback cursorPosition_Callback
		)
		{
			input::dx11::mCursorPosition_Callback = cursorPosition_Callback;
		}

		DOOMS_ENGINE_GRAPHICS_API void SetScroll_Callback(input::GraphicsAPIInput::Scroll_Callback scroll_Callback)
		{
			input::dx11::mScroll_Callback = scroll_Callback;
		}

		DOOMS_ENGINE_GRAPHICS_API void SetKey_Callback(input::GraphicsAPIInput::Key_Callback key_Callback)
		{
			input::dx11::mKey_Callback = key_Callback;
		}

		DOOMS_ENGINE_GRAPHICS_API void SetMouseButton_Callback(input::GraphicsAPIInput::MouseButton_Callback mouseButton_Callback)
		{
			input::dx11::mMouseButton_Callback = mouseButton_Callback;
		}

		DOOMS_ENGINE_GRAPHICS_API input::GraphicsAPIInput::eInputActionType GetKeyCurrentAction(void* const platformWindow, const input::GraphicsAPIInput::eKEY_CODE keyCode)
		{
			if (keyCode != input::GraphicsAPIInput::eKEY_CODE::UNKNOWN)
			{
				if(dx11::DX11Keyboard->GetState().IsKeyDown(dx11::Convert_eKeyCode_To_DX11KeyCode(keyCode)))
				{
					return input::GraphicsAPIInput::eInputActionType::PRESS;
				}
				else
				{
					return input::GraphicsAPIInput::eInputActionType::RELEASE;
				}
			}
			else
			{
				return input::GraphicsAPIInput::eInputActionType::RELEASE;
			}
		}
		

	}
}