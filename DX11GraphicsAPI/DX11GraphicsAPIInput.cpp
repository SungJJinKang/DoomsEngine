#include "Input/GraphicsAPIInput.h"

#include <cassert>

#include <dinput.h>
#include <string.h>

#pragma comment(lib, "dinput8")
#pragma comment(lib, "dxguid")

#undef NEVER_HAPPEN
#ifdef _DEBUG
#define NEVER_HAPPEN assert(false)
#else
#define NEVER_HAPPEN __assume(0)
#endif

namespace dooms
{
	namespace input
	{
		namespace dx11
		{
			static IDirectInput8* m_pInput = nullptr;
			static IDirectInputDevice8* m_pKeyboard = nullptr;

#define KEY_COUNT 256
			static char KeyState[KEY_COUNT];


			static input::GraphicsAPIInput::CursorEnterCallback mCursorEnterCallback = nullptr;
			static input::GraphicsAPIInput::CursorPosition_Callback mCursorPosition_Callback = nullptr;
			static input::GraphicsAPIInput::Scroll_Callback mScroll_Callback = nullptr;
			static input::GraphicsAPIInput::Key_Callback mKey_Callback = nullptr;
			static input::GraphicsAPIInput::MouseButton_Callback mMouseButton_Callback = nullptr;

			FORCE_INLINE extern dooms::input::GraphicsAPIInput::eKEY_CODE Convert_GLKeyCode_To_eKeyCode(const unsigned int keyCode)
			{
				switch (keyCode)
				{
				case DIKEYBOARD_SPACE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SPACE;
				case DIKEYBOARD_APOSTROPHE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_APOSTROPHE;
				case DIKEYBOARD_COMMA:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_COMMA;
				case DIKEYBOARD_MINUS:
					return  dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_MINUS;
				case DIKEYBOARD_PERIOD:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PERIOD;
				case DIKEYBOARD_SLASH:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SLASH;
				case DIKEYBOARD_0:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_0;
				case DIKEYBOARD_1:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_1;
				case DIKEYBOARD_2:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_2;
				case DIKEYBOARD_3:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_3;
				case DIKEYBOARD_4:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_4;
				case DIKEYBOARD_5:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_5;
				case DIKEYBOARD_6:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_6;
				case DIKEYBOARD_7:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_7;
				case DIKEYBOARD_8:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_8;
				case DIKEYBOARD_9:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_9;
				case DIKEYBOARD_SEMICOLON:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SEMICOLON;
				case DIKEYBOARD_EQUALS:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_EQUAL;
				case DIKEYBOARD_A:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_A;
				case DIKEYBOARD_B:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_B;
				case DIKEYBOARD_C:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_C;
				case DIKEYBOARD_D:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_D;
				case DIKEYBOARD_E:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_E;
				case DIKEYBOARD_F:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F;
				case DIKEYBOARD_G:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_G;
				case DIKEYBOARD_H:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_H;
				case DIKEYBOARD_I:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_I;
				case DIKEYBOARD_J:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_J;
				case DIKEYBOARD_K:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_K;
				case DIKEYBOARD_L:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_L;
				case DIKEYBOARD_M:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_M;
				case DIKEYBOARD_N:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_N;
				case DIKEYBOARD_O:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_O;
				case DIKEYBOARD_P:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_P;
				case DIKEYBOARD_Q:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Q;
				case DIKEYBOARD_R:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_R;
				case DIKEYBOARD_S:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_S;
				case DIKEYBOARD_T:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_T;
				case DIKEYBOARD_U:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_U;
				case DIKEYBOARD_V:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_V;
				case DIKEYBOARD_W:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_W;
				case DIKEYBOARD_X:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_X;
				case DIKEYBOARD_Y:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Y;
				case DIKEYBOARD_Z:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Z;
				case DIKEYBOARD_LBRACKET:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_BRACKET;
				case DIKEYBOARD_BACKSLASH:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_BACKSLASH;
				case DIKEYBOARD_RBRACKET:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_BRACKET;
				case DIKEYBOARD_GRAVE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_GRAVE_ACCENT;
				/*
				case DIKEYBOARD_WORLD_1:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_WORLD_1;
				case DIKEYBOARD_WORLD_2:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_WORLD_2;
				*/
				case DIKEYBOARD_ESCAPE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_ESCAPE;
				case DIKEYBOARD_RETURN:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_ENTER;
				case DIKEYBOARD_TAB:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_TAB;
				case DIKEYBOARD_BACK:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_BACKSPACE;
				case DIKEYBOARD_INSERT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_INSERT;
				case DIKEYBOARD_DELETE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_DELETE;
				case DIKEYBOARD_RIGHT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT;
				case DIKEYBOARD_LEFT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT;
				case DIKEYBOARD_DOWN:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_DOWN;
				case DIKEYBOARD_UP:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_UP;
				case DIKEYBOARD_PRIOR:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAGE_UP;
				case DIKEYBOARD_NEXT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAGE_DOWN;
				case DIKEYBOARD_HOME:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_HOME;
				case DIKEYBOARD_END:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_END;
				case DIKEYBOARD_CAPITAL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_CAPS_LOCK;
				case DIKEYBOARD_SCROLL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SCROLL_LOCK;
				case DIKEYBOARD_NUMLOCK:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_NUM_LOCK;

				/*
				case DIKEYBOARD_PRINT_SCREEN:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PRINT_SCREEN;
				*/

				case DIKEYBOARD_PAUSE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAUSE;
				case DIKEYBOARD_F1:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F1;
				case DIKEYBOARD_F2:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F2;
				case DIKEYBOARD_F3:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F3;
				case DIKEYBOARD_F4:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F4;
				case DIKEYBOARD_F5:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F5;
				case DIKEYBOARD_F6:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F6;
				case DIKEYBOARD_F7:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F7;
				case DIKEYBOARD_F8:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F8;
				case DIKEYBOARD_F9:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F9;
				case DIKEYBOARD_F10:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F10;
				case DIKEYBOARD_F11:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F11;
				case DIKEYBOARD_F12:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F12;
				case DIKEYBOARD_F13:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F13;
				case DIKEYBOARD_F14:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F14;
				case DIKEYBOARD_F15:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F15;

				/*
				case DIKEYBOARD_F16:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F16;
				case DIKEYBOARD_F17:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F17;
				case DIKEYBOARD_F18:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F18;
				case DIKEYBOARD_F19:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F19;
				case DIKEYBOARD_F20:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F20;
				case DIKEYBOARD_F21:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F21;
				case DIKEYBOARD_F22:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F22;
				case DIKEYBOARD_F23:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F23;
				case DIKEYBOARD_F24:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F24;
				case DIKEYBOARD_F25:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F25;
				*/
				case DIKEYBOARD_NUMPAD0:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_0;
				case DIKEYBOARD_NUMPAD1:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_1;
				case DIKEYBOARD_NUMPAD2:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_2;
				case DIKEYBOARD_NUMPAD3:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_3;
				case DIKEYBOARD_NUMPAD4:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_4;
				case DIKEYBOARD_NUMPAD5:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_5;
				case DIKEYBOARD_NUMPAD6:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_6;
				case DIKEYBOARD_NUMPAD7:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_7;
				case DIKEYBOARD_NUMPAD8:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_8;
				case DIKEYBOARD_NUMPAD9:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_9;
				case DIKEYBOARD_DECIMAL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_DECIMAL;
				case DIKEYBOARD_DIVIDE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_DIVIDE;
				case DIKEYBOARD_MULTIPLY:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_MULTIPLY;
				case DIKEYBOARD_SUBTRACT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_SUBTRACT;
				case DIKEYBOARD_ADD:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_ADD;
				case DIKEYBOARD_NUMPADENTER:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_ENTER;
				case DIKEYBOARD_NUMPADEQUALS:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_EQUAL;
				case DIKEYBOARD_LSHIFT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_SHIFT;
				case DIKEYBOARD_LCONTROL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_CONTROL;
				case DIKEYBOARD_LMENU:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_ALT;

				/*
				case DIKEYBOARD_LEFT_SUPER:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_SUPER;
				*/

				case DIKEYBOARD_RSHIFT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_SHIFT;
				case DIKEYBOARD_RCONTROL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_CONTROL;
				case DIKEYBOARD_RMENU:

				/*
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_ALT;
				case DIKEYBOARD_RIGHT_SUPER:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_SUPER;
				case DIKEYBOARD_MENU:
				*/

					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_MENU;
				default:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::UNKNOWN;
				}
			}


			FORCE_INLINE extern unsigned int Convert_eKeyCode_To_GLKeyCode(const dooms::input::GraphicsAPIInput::eKEY_CODE keyCode)
			{
				switch (keyCode)
				{
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SPACE:
					return DIKEYBOARD_SPACE;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_APOSTROPHE:
					return DIKEYBOARD_APOSTROPHE;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_COMMA:
					return DIKEYBOARD_COMMA;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_MINUS:
					return DIKEYBOARD_MINUS;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PERIOD:
					return DIKEYBOARD_PERIOD;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SLASH:
					return DIKEYBOARD_SLASH;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_0:
					return DIKEYBOARD_0;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_1:
					return DIKEYBOARD_1;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_2:
					return DIKEYBOARD_2;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_3:
					return DIKEYBOARD_3;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_4:
					return DIKEYBOARD_4;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_5:
					return DIKEYBOARD_5;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_6:
					return DIKEYBOARD_6;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_7:
					return DIKEYBOARD_7;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_8:
					return DIKEYBOARD_8;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_9:
					return DIKEYBOARD_9;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SEMICOLON:
					return DIKEYBOARD_SEMICOLON;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_EQUAL:
					return DIKEYBOARD_EQUALS;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_A:
					return DIKEYBOARD_A;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_B:
					return DIKEYBOARD_B;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_C:
					return DIKEYBOARD_C;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_D:
					return DIKEYBOARD_D;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_E:
					return DIKEYBOARD_E;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F:
					return DIKEYBOARD_F;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_G:
					return DIKEYBOARD_G;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_H:
					return DIKEYBOARD_H;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_I:
					return DIKEYBOARD_I;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_J:
					return DIKEYBOARD_J;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_K:
					return DIKEYBOARD_K;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_L:
					return DIKEYBOARD_L;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_M:
					return DIKEYBOARD_M;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_N:
					return DIKEYBOARD_N;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_O:
					return DIKEYBOARD_O;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_P:
					return DIKEYBOARD_P;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Q:
					return DIKEYBOARD_Q;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_R:
					return DIKEYBOARD_R;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_S:
					return DIKEYBOARD_S;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_T:
					return DIKEYBOARD_T;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_U:
					return DIKEYBOARD_U;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_V:
					return DIKEYBOARD_V;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_W:
					return DIKEYBOARD_W;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_X:
					return DIKEYBOARD_X;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Y:
					return DIKEYBOARD_Y;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Z:
					return DIKEYBOARD_Z;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_BRACKET:
					return DIKEYBOARD_LBRACKET;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_BACKSLASH:
					return DIKEYBOARD_BACKSLASH;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_BRACKET:
					return DIKEYBOARD_RBRACKET;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_GRAVE_ACCENT:
					return DIKEYBOARD_GRAVE;

				/*
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_WORLD_1:
					return DIKEYBOARD_WORLD_1;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_WORLD_2:
					return DIKEYBOARD_WORLD_2;
					*/

				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_ESCAPE:
					return DIKEYBOARD_ESCAPE;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_ENTER:
					return DIKEYBOARD_RETURN;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_TAB:
					return DIKEYBOARD_TAB;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_BACKSPACE:
					return DIKEYBOARD_BACK;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_INSERT:
					return DIKEYBOARD_INSERT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_DELETE:
					return DIKEYBOARD_DELETE;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT:
					return DIKEYBOARD_RIGHT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT:
					return DIKEYBOARD_LEFT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_DOWN:
					return DIKEYBOARD_DOWN;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_UP:
					return DIKEYBOARD_UP;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAGE_UP:
					return DIKEYBOARD_PRIOR;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAGE_DOWN:
					return DIKEYBOARD_NEXT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_HOME:
					return DIKEYBOARD_HOME;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_END:
					return DIKEYBOARD_END;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_CAPS_LOCK:
					return DIKEYBOARD_CAPITAL;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SCROLL_LOCK:
					return DIKEYBOARD_SCROLL;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_NUM_LOCK:
					return DIKEYBOARD_NUMLOCK;

				/*
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PRINT_SCREEN:
					return DIKEYBOARD_PRINT_SCREEN;
					*/

				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAUSE:
					return DIKEYBOARD_PAUSE;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F1:
					return DIKEYBOARD_F1;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F2:
					return DIKEYBOARD_F2;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F3:
					return DIKEYBOARD_F3;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F4:
					return DIKEYBOARD_F4;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F5:
					return DIKEYBOARD_F5;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F6:
					return DIKEYBOARD_F6;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F7:
					return DIKEYBOARD_F7;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F8:
					return DIKEYBOARD_F8;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F9:
					return DIKEYBOARD_F9;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F10:
					return DIKEYBOARD_F10;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F11:
					return DIKEYBOARD_F11;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F12:
					return DIKEYBOARD_F12;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F13:
					return DIKEYBOARD_F13;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F14:
					return DIKEYBOARD_F14;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F15:
					return DIKEYBOARD_F15;

				/*
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F16:
					return DIKEYBOARD_F16;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F17:
					return DIKEYBOARD_F17;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F18:
					return DIKEYBOARD_F18;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F19:
					return DIKEYBOARD_F19;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F20:
					return DIKEYBOARD_F20;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F21:
					return DIKEYBOARD_F21;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F22:
					return DIKEYBOARD_F22;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F23:
					return DIKEYBOARD_F23;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F24:
					return DIKEYBOARD_F24;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F25:
					return DIKEYBOARD_F25;
				*/
					
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_0:
					return DIKEYBOARD_NUMPAD0;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_1:
					return DIKEYBOARD_NUMPAD1;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_2:
					return DIKEYBOARD_NUMPAD2;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_3:
					return DIKEYBOARD_NUMPAD3;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_4:
					return DIKEYBOARD_NUMPAD4;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_5:
					return DIKEYBOARD_NUMPAD5;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_6:
					return DIKEYBOARD_NUMPAD6;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_7:
					return DIKEYBOARD_NUMPAD7;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_8:
					return DIKEYBOARD_NUMPAD8;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_9:
					return DIKEYBOARD_NUMPAD9;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_DECIMAL:
					return DIKEYBOARD_DECIMAL;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_DIVIDE:
					return DIKEYBOARD_DIVIDE;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_MULTIPLY:
					return DIKEYBOARD_MULTIPLY;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_SUBTRACT:
					return DIKEYBOARD_SUBTRACT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_ADD:
					return DIKEYBOARD_ADD;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_ENTER:
					return DIKEYBOARD_NUMPADENTER;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_EQUAL:
					return DIKEYBOARD_NUMPADEQUALS;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_SHIFT:
					return DIKEYBOARD_LSHIFT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_CONTROL:
					return DIKEYBOARD_LCONTROL;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_ALT:
					return DIKEYBOARD_LMENU;

				/*
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_SUPER:
					return DIKEYBOARD_LEFT_SUPER;
					*/

				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_SHIFT:
					return DIKEYBOARD_RSHIFT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_CONTROL:
					return DIKEYBOARD_RCONTROL;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_ALT:
					return DIKEYBOARD_RMENU;

				/*
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_SUPER:
					return DIKEYBOARD_RIGHT_SUPER;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_MENU:
					return DIKEYBOARD_MENU;
				*/

				default:
					return DIKEYBOARD_UNLABELED;
				}
			}


			FORCE_INLINE extern unsigned int Convert_eMouseInput_To_GLFWMouseInput(const dooms::input::GraphicsAPIInput::eMoustInput mouseInput)
			{
				switch (mouseInput)
				{
				case dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_LEFT:
					return DIMOUSE_BUTTON0;
				case dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_RIGHT:
					return DIMOUSE_BUTTON1;
				case dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_MIDDLE:
					return DIMOUSE_BUTTON2;
				default:
					NEVER_HAPPEN;
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
					NEVER_HAPPEN;
				}
			}

			enum eCursorMode : unsigned int
			{
				CURSOR_MODE_NORMAL,
				CURSOR_MODE_HIDDEN,
				CURSOR_MODE_DISABLED,
			};

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
					NEVER_HAPPEN;
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


			extern void CursorPosition_Callback(GLFWwindow* window, double xpos, double ypos)
			{
				assert(input::dx11::mCursorPosition_Callback != nullptr);
				(*input::dx11::mCursorPosition_Callback)(xpos, ypos);
			}
			extern void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
			{
				assert(input::dx11::mScroll_Callback != nullptr);
				(*input::dx11::mScroll_Callback)(xoffset, yoffset);
			}
			extern void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				assert(input::dx11::mKey_Callback != nullptr);
				(*input::dx11::mKey_Callback)(input::dx11::Convert_GLKeyCode_To_eKeyCode(key), scancode, input::dx11::Convert_GLFWInputAction_To_eInputActionType(action), mods);
			}
			extern void MouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
			{
				assert(input::dx11::mMouseButton_Callback != nullptr);
				(*input::dx11::mMouseButton_Callback)(input::dx11::Convert_GLFWMouseInput_To_eMouseInput(button), input::dx11::Convert_GLFWInputAction_To_eInputActionType(action), mods);
			}
			extern void CursorEnterCallback(GLFWwindow* window, int entered)
			{
				assert(input::dx11::mCursorEnterCallback != nullptr);
				(*input::dx11::mCursorEnterCallback)((bool)entered);

				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				CursorPosition_Callback(window, xpos, ypos);
			}
		}


		DOOMS_ENGINE_GRAPHICS_API unsigned int InitializeGraphisAPIInput(void* const platformWindow)
		{
			if(platformWindow == 0)
			{
				return 1;
			}

			if(FAILED(DirectInput8Create(reinterpret_cast<HINSTANCE>(platformWindow), DIRECTINPUT_HEADER_VERSION, IID_IDirectInput8, (void **)dx11::m_pInput, nullptr)))
			{
				return 1;
			}

			if(FAILED(dx11::m_pInput->CreateDevice(GUID_SysKeyboard, &dx11::m_pKeyboard, nullptr)))
			{
				return 2;
			}

			if(FAILED(dx11::m_pKeyboard->SetDataFormat(&c_dfDIKeyboard)))
			{
				return 3;
			}

			if(FAILED(dx11::m_pKeyboard->Acquire()))
			{
				return 4;
			}


			GLFWwindow* const glfwWindow = reinterpret_cast<GLFWwindow*>(platformWindow);
			assert(glfwWindow != nullptr);

			glfwSetCursorEnterCallback(glfwWindow, &dooms::input::dx11::CursorEnterCallback);
			glfwSetCursorPosCallback(glfwWindow, &dooms::input::dx11::CursorPosition_Callback);
			glfwSetScrollCallback(glfwWindow, &dooms::input::dx11::Scroll_Callback);

			glfwSetKeyCallback(glfwWindow, &dooms::input::dx11::Key_Callback);
			glfwSetMouseButtonCallback(glfwWindow, &dooms::input::dx11::MouseButton_Callback);

			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int DeInitializeGraphisAPIInput()
		{
			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API void PollEvents()
		{
			dx11::m_pKeyboard->Poll();

			char keyCount[KEY_COUNT];
			HRESULT result = dx11::m_pKeyboard->GetDeviceState(KEY_COUNT, keyCount);
			if(FAILED(result))
			{
				if(result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
				{
					dx11::m_pKeyboard->Acquire();
				}
				else
				{
					return;
				}
			}

			memcpy(dx11::KeyState, keyCount, KEY_COUNT * sizeof(char));
		}

		DOOMS_ENGINE_GRAPHICS_API void SetCursorMode(void* const platformWindow, const GraphicsAPIInput::eCursorMode cursorMode)
		{
			glfwSetInputMode(reinterpret_cast<GLFWwindow*>(platformWindow), GLFW_CURSOR, input::dx11::GetGLCursorMode(cursorMode));
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
				const int glInputAction = glfwGetKey(reinterpret_cast<GLFWwindow*>(platformWindow), dx11::Convert_eKeyCode_To_GLKeyCode(keyCode));
				return dx11::Convert_GLFWInputAction_To_eInputActionType(glInputAction);
			}
			else
			{
				return input::GraphicsAPIInput::eInputActionType::RELEASE;
			}
		}

	}
}