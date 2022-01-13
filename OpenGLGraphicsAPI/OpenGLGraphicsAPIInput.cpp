#include "Input/GraphicsAPIInput.h"

#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


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
		namespace opengl
		{
			static input::GraphicsAPIInput::CursorEnterCallback mCursorEnterCallback = nullptr;
			static input::GraphicsAPIInput::CursorPosition_Callback mCursorPosition_Callback = nullptr;
			static input::GraphicsAPIInput::Scroll_Callback mScroll_Callback = nullptr;
			static input::GraphicsAPIInput::Key_Callback mKey_Callback = nullptr;
			static input::GraphicsAPIInput::MouseButton_Callback mMouseButton_Callback = nullptr;

			FORCE_INLINE extern dooms::input::GraphicsAPIInput::eKEY_CODE Convert_GLKeyCode_To_eKeyCode(const unsigned int keyCode)
			{
				switch (keyCode)
				{
				case GLFW_KEY_SPACE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SPACE;
				case GLFW_KEY_APOSTROPHE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_APOSTROPHE;
				case GLFW_KEY_COMMA:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_COMMA;
				case GLFW_KEY_MINUS:
					return  dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_MINUS;
				case GLFW_KEY_PERIOD:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PERIOD;
				case GLFW_KEY_SLASH:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SLASH;
				case GLFW_KEY_0:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_0;
				case GLFW_KEY_1:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_1;
				case GLFW_KEY_2:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_2;
				case GLFW_KEY_3:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_3;
				case GLFW_KEY_4:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_4;
				case GLFW_KEY_5:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_5;
				case GLFW_KEY_6:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_6;
				case GLFW_KEY_7:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_7;
				case GLFW_KEY_8:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_8;
				case GLFW_KEY_9:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_9;
				case GLFW_KEY_SEMICOLON:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SEMICOLON;
				case GLFW_KEY_EQUAL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_EQUAL;
				case GLFW_KEY_A:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_A;
				case GLFW_KEY_B:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_B;
				case GLFW_KEY_C:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_C;
				case GLFW_KEY_D:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_D;
				case GLFW_KEY_E:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_E;
				case GLFW_KEY_F:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F;
				case GLFW_KEY_G:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_G;
				case GLFW_KEY_H:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_H;
				case GLFW_KEY_I:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_I;
				case GLFW_KEY_J:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_J;
				case GLFW_KEY_K:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_K;
				case GLFW_KEY_L:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_L;
				case GLFW_KEY_M:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_M;
				case GLFW_KEY_N:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_N;
				case GLFW_KEY_O:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_O;
				case GLFW_KEY_P:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_P;
				case GLFW_KEY_Q:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Q;
				case GLFW_KEY_R:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_R;
				case GLFW_KEY_S:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_S;
				case GLFW_KEY_T:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_T;
				case GLFW_KEY_U:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_U;
				case GLFW_KEY_V:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_V;
				case GLFW_KEY_W:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_W;
				case GLFW_KEY_X:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_X;
				case GLFW_KEY_Y:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Y;
				case GLFW_KEY_Z:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Z;
				case GLFW_KEY_LEFT_BRACKET:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_BRACKET;
				case GLFW_KEY_BACKSLASH:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_BACKSLASH;
				case GLFW_KEY_RIGHT_BRACKET:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_BRACKET;
				case GLFW_KEY_GRAVE_ACCENT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_GRAVE_ACCENT;
				case GLFW_KEY_WORLD_1:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_WORLD_1;
				case GLFW_KEY_WORLD_2:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_WORLD_2;
				case GLFW_KEY_ESCAPE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_ESCAPE;
				case GLFW_KEY_ENTER:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_ENTER;
				case GLFW_KEY_TAB:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_TAB;
				case GLFW_KEY_BACKSPACE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_BACKSPACE;
				case GLFW_KEY_INSERT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_INSERT;
				case GLFW_KEY_DELETE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_DELETE;
				case GLFW_KEY_RIGHT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT;
				case GLFW_KEY_LEFT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT;
				case GLFW_KEY_DOWN:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_DOWN;
				case GLFW_KEY_UP:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_UP;
				case GLFW_KEY_PAGE_UP:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAGE_UP;
				case GLFW_KEY_PAGE_DOWN:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAGE_DOWN;
				case GLFW_KEY_HOME:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_HOME;
				case GLFW_KEY_END:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_END;
				case GLFW_KEY_CAPS_LOCK:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_CAPS_LOCK;
				case GLFW_KEY_SCROLL_LOCK:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SCROLL_LOCK;
				case GLFW_KEY_NUM_LOCK:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_NUM_LOCK;
				case GLFW_KEY_PRINT_SCREEN:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PRINT_SCREEN;
				case GLFW_KEY_PAUSE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAUSE;
				case GLFW_KEY_F1:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F1;
				case GLFW_KEY_F2:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F2;
				case GLFW_KEY_F3:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F3;
				case GLFW_KEY_F4:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F4;
				case GLFW_KEY_F5:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F5;
				case GLFW_KEY_F6:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F6;
				case GLFW_KEY_F7:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F7;
				case GLFW_KEY_F8:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F8;
				case GLFW_KEY_F9:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F9;
				case GLFW_KEY_F10:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F10;
				case GLFW_KEY_F11:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F11;
				case GLFW_KEY_F12:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F12;
				case GLFW_KEY_F13:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F13;
				case GLFW_KEY_F14:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F14;
				case GLFW_KEY_F15:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F15;
				case GLFW_KEY_F16:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F16;
				case GLFW_KEY_F17:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F17;
				case GLFW_KEY_F18:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F18;
				case GLFW_KEY_F19:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F19;
				case GLFW_KEY_F20:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F20;
				case GLFW_KEY_F21:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F21;
				case GLFW_KEY_F22:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F22;
				case GLFW_KEY_F23:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F23;
				case GLFW_KEY_F24:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F24;
				case GLFW_KEY_F25:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F25;
				case GLFW_KEY_KP_0:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_0;
				case GLFW_KEY_KP_1:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_1;
				case GLFW_KEY_KP_2:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_2;
				case GLFW_KEY_KP_3:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_3;
				case GLFW_KEY_KP_4:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_4;
				case GLFW_KEY_KP_5:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_5;
				case GLFW_KEY_KP_6:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_6;
				case GLFW_KEY_KP_7:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_7;
				case GLFW_KEY_KP_8:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_8;
				case GLFW_KEY_KP_9:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_9;
				case GLFW_KEY_KP_DECIMAL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_DECIMAL;
				case GLFW_KEY_KP_DIVIDE:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_DIVIDE;
				case GLFW_KEY_KP_MULTIPLY:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_MULTIPLY;
				case GLFW_KEY_KP_SUBTRACT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_SUBTRACT;
				case GLFW_KEY_KP_ADD:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_ADD;
				case GLFW_KEY_KP_ENTER:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_ENTER;
				case GLFW_KEY_KP_EQUAL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_EQUAL;
				case GLFW_KEY_LEFT_SHIFT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_SHIFT;
				case GLFW_KEY_LEFT_CONTROL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_CONTROL;
				case GLFW_KEY_LEFT_ALT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_ALT;
				case GLFW_KEY_LEFT_SUPER:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_SUPER;
				case GLFW_KEY_RIGHT_SHIFT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_SHIFT;
				case GLFW_KEY_RIGHT_CONTROL:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_CONTROL;
				case GLFW_KEY_RIGHT_ALT:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_ALT;
				case GLFW_KEY_RIGHT_SUPER:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_SUPER;
				case GLFW_KEY_MENU:
					return dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_MENU;
				default:
					NEVER_HAPPEN;
				}
			}


			FORCE_INLINE extern unsigned int Convert_eKeyCode_To_GLKeyCode(const dooms::input::GraphicsAPIInput::eKEY_CODE keyCode)
			{
				switch (keyCode)
				{
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SPACE:
					return GLFW_KEY_SPACE;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_APOSTROPHE:
					return GLFW_KEY_APOSTROPHE;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_COMMA:
					return GLFW_KEY_COMMA;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_MINUS:
					return GLFW_KEY_MINUS;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PERIOD:
					return GLFW_KEY_PERIOD;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SLASH:
					return GLFW_KEY_SLASH;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_0:
					return GLFW_KEY_0;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_1:
					return GLFW_KEY_1;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_2:
					return GLFW_KEY_2;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_3:
					return GLFW_KEY_3;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_4:
					return GLFW_KEY_4;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_5:
					return GLFW_KEY_5;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_6:
					return GLFW_KEY_6;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_7:
					return GLFW_KEY_7;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_8:
					return GLFW_KEY_8;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_9:
					return GLFW_KEY_9;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SEMICOLON:
					return GLFW_KEY_SEMICOLON;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_EQUAL:
					return GLFW_KEY_EQUAL;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_A:
					return GLFW_KEY_A;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_B:
					return GLFW_KEY_B;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_C:
					return GLFW_KEY_C;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_D:
					return GLFW_KEY_D;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_E:
					return GLFW_KEY_E;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F:
					return GLFW_KEY_F;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_G:
					return GLFW_KEY_G;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_H:
					return GLFW_KEY_H;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_I:
					return GLFW_KEY_I;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_J:
					return GLFW_KEY_J;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_K:
					return GLFW_KEY_K;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_L:
					return GLFW_KEY_L;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_M:
					return GLFW_KEY_M;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_N:
					return GLFW_KEY_N;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_O:
					return GLFW_KEY_O;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_P:
					return GLFW_KEY_P;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Q:
					return GLFW_KEY_Q;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_R:
					return GLFW_KEY_R;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_S:
					return GLFW_KEY_S;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_T:
					return GLFW_KEY_T;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_U:
					return GLFW_KEY_U;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_V:
					return GLFW_KEY_V;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_W:
					return GLFW_KEY_W;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_X:
					return GLFW_KEY_X;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Y:
					return GLFW_KEY_Y;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_Z:
					return GLFW_KEY_Z;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_BRACKET:
					return GLFW_KEY_LEFT_BRACKET;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_BACKSLASH:
					return GLFW_KEY_BACKSLASH;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_BRACKET:
					return GLFW_KEY_RIGHT_BRACKET;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_GRAVE_ACCENT:
					return GLFW_KEY_GRAVE_ACCENT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_WORLD_1:
					return GLFW_KEY_WORLD_1;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_WORLD_2:
					return GLFW_KEY_WORLD_2;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_ESCAPE:
					return GLFW_KEY_ESCAPE;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_ENTER:
					return GLFW_KEY_ENTER;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_TAB:
					return GLFW_KEY_TAB;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_BACKSPACE:
					return GLFW_KEY_BACKSPACE;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_INSERT:
					return GLFW_KEY_INSERT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_DELETE:
					return GLFW_KEY_DELETE;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT:
					return GLFW_KEY_RIGHT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT:
					return GLFW_KEY_LEFT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_DOWN:
					return GLFW_KEY_DOWN;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_UP:
					return GLFW_KEY_UP;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAGE_UP:
					return GLFW_KEY_PAGE_UP;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAGE_DOWN:
					return GLFW_KEY_PAGE_DOWN;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_HOME:
					return GLFW_KEY_HOME;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_END:
					return GLFW_KEY_END;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_CAPS_LOCK:
					return GLFW_KEY_CAPS_LOCK;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_SCROLL_LOCK:
					return GLFW_KEY_SCROLL_LOCK;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_NUM_LOCK:
					return GLFW_KEY_NUM_LOCK;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PRINT_SCREEN:
					return GLFW_KEY_PRINT_SCREEN;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_PAUSE:
					return GLFW_KEY_PAUSE;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F1:
					return GLFW_KEY_F1;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F2:
					return GLFW_KEY_F2;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F3:
					return GLFW_KEY_F3;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F4:
					return GLFW_KEY_F4;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F5:
					return GLFW_KEY_F5;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F6:
					return GLFW_KEY_F6;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F7:
					return GLFW_KEY_F7;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F8:
					return GLFW_KEY_F8;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F9:
					return GLFW_KEY_F9;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F10:
					return GLFW_KEY_F10;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F11:
					return GLFW_KEY_F11;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F12:
					return GLFW_KEY_F12;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F13:
					return GLFW_KEY_F13;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F14:
					return GLFW_KEY_F14;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F15:
					return GLFW_KEY_F15;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F16:
					return GLFW_KEY_F16;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F17:
					return GLFW_KEY_F17;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F18:
					return GLFW_KEY_F18;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F19:
					return GLFW_KEY_F19;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F20:
					return GLFW_KEY_F20;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F21:
					return GLFW_KEY_F21;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F22:
					return GLFW_KEY_F22;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F23:
					return GLFW_KEY_F23;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F24:
					return GLFW_KEY_F24;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_F25:
					return GLFW_KEY_F25;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_0:
					return GLFW_KEY_KP_0;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_1:
					return GLFW_KEY_KP_1;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_2:
					return GLFW_KEY_KP_2;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_3:
					return GLFW_KEY_KP_3;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_4:
					return GLFW_KEY_KP_4;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_5:
					return GLFW_KEY_KP_5;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_6:
					return GLFW_KEY_KP_6;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_7:
					return GLFW_KEY_KP_7;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_8:
					return GLFW_KEY_KP_8;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_9:
					return GLFW_KEY_KP_9;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_DECIMAL:
					return GLFW_KEY_KP_DECIMAL;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_DIVIDE:
					return GLFW_KEY_KP_DIVIDE;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_MULTIPLY:
					return GLFW_KEY_KP_MULTIPLY;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_SUBTRACT:
					return GLFW_KEY_KP_SUBTRACT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_ADD:
					return GLFW_KEY_KP_ADD;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_ENTER:
					return GLFW_KEY_KP_ENTER;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_KP_EQUAL:
					return GLFW_KEY_KP_EQUAL;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_SHIFT:
					return GLFW_KEY_LEFT_SHIFT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_CONTROL:
					return GLFW_KEY_LEFT_CONTROL;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_ALT:
					return GLFW_KEY_LEFT_ALT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_LEFT_SUPER:
					return GLFW_KEY_LEFT_SUPER;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_SHIFT:
					return GLFW_KEY_RIGHT_SHIFT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_CONTROL:
					return GLFW_KEY_RIGHT_CONTROL;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_ALT:
					return GLFW_KEY_RIGHT_ALT;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_RIGHT_SUPER:
					return GLFW_KEY_RIGHT_SUPER;
				case dooms::input::GraphicsAPIInput::eKEY_CODE::KEY_MENU:
					return GLFW_KEY_MENU;
				default:
					NEVER_HAPPEN;
					return 0;
				}
			}


			FORCE_INLINE extern unsigned int Convert_eMouseInput_To_GLFWMouseInput(const dooms::input::GraphicsAPIInput::eMoustInput mouseInput)
			{
				switch (mouseInput)
				{
				case dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_LEFT:
					return GLFW_MOUSE_BUTTON_LEFT;
				case dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_RIGHT:
					return GLFW_MOUSE_BUTTON_RIGHT;
				case dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_MIDDLE:
					return GLFW_MOUSE_BUTTON_MIDDLE;
				default:
					NEVER_HAPPEN;
					return 0;
				}
			}

			FORCE_INLINE extern dooms::input::GraphicsAPIInput::eMoustInput Convert_GLFWMouseInput_To_eMouseInput(const unsigned int glfwMouseInput)
			{
				switch (glfwMouseInput)
				{
				case GLFW_MOUSE_BUTTON_LEFT:
					return dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_LEFT;
				case GLFW_MOUSE_BUTTON_RIGHT:
					return dooms::input::GraphicsAPIInput::eMoustInput::MOUSE_BUTTON_RIGHT;
				case GLFW_MOUSE_BUTTON_MIDDLE:
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
				case GLFW_PRESS:
					return input::GraphicsAPIInput::eInputActionType::PRESS;

				case GLFW_RELEASE:
					return input::GraphicsAPIInput::eInputActionType::RELEASE;

				case GLFW_REPEAT:
					return input::GraphicsAPIInput::eInputActionType::REPEAT;
				}
			}


			extern void CursorPosition_Callback(GLFWwindow* window, double xpos, double ypos)
			{
				assert(input::opengl::mCursorPosition_Callback != nullptr);
				(*input::opengl::mCursorPosition_Callback)(xpos, ypos);
			}
			extern void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
			{
				assert(input::opengl::mScroll_Callback != nullptr);
				(*input::opengl::mScroll_Callback)(xoffset, yoffset);
			}
			extern void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				assert(input::opengl::mKey_Callback != nullptr);
				(*input::opengl::mKey_Callback)(input::opengl::Convert_GLKeyCode_To_eKeyCode(key), scancode, input::opengl::Convert_GLFWInputAction_To_eInputActionType(action), mods);
			}
			extern void MouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
			{
				assert(input::opengl::mMouseButton_Callback != nullptr);
				(*input::opengl::mMouseButton_Callback)(input::opengl::Convert_GLFWMouseInput_To_eMouseInput(button), input::opengl::Convert_GLFWInputAction_To_eInputActionType(action), mods);
			}
			extern void CursorEnterCallback(GLFWwindow* window, int entered)
			{
				assert(input::opengl::mCursorEnterCallback != nullptr);
				(*input::opengl::mCursorEnterCallback)((bool)entered);

				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				CursorPosition_Callback(window, xpos, ypos);
			}
		}


		DOOMS_ENGINE_GRAPHICS_API unsigned int InitializeGraphisAPIInput(void* const platformWindow)
		{
			GLFWwindow* const glfwWindow = reinterpret_cast<GLFWwindow*>(platformWindow);
			assert(glfwWindow != nullptr);

			glfwSetCursorEnterCallback(glfwWindow, &dooms::input::opengl::CursorEnterCallback);
			glfwSetCursorPosCallback(glfwWindow, &dooms::input::opengl::CursorPosition_Callback);
			glfwSetScrollCallback(glfwWindow, &dooms::input::opengl::Scroll_Callback);

			glfwSetKeyCallback(glfwWindow, &dooms::input::opengl::Key_Callback);
			glfwSetMouseButtonCallback(glfwWindow, &dooms::input::opengl::MouseButton_Callback);

			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int DeInitializeGraphisAPIInput()
		{
			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API void PollEvents()
		{
			glfwPollEvents();
		}

		DOOMS_ENGINE_GRAPHICS_API void SetCursorMode(void* const platformWindow, const GraphicsAPIInput::eCursorMode cursorMode)
		{
			glfwSetInputMode(reinterpret_cast<GLFWwindow*>(platformWindow), GLFW_CURSOR, input::opengl::GetGLCursorMode(cursorMode));
		}


		DOOMS_ENGINE_GRAPHICS_API void SetCursorEnterCallback(input::GraphicsAPIInput::CursorEnterCallback cursorEnterCallback)
		{
			input::opengl::mCursorEnterCallback = cursorEnterCallback;
		}

		DOOMS_ENGINE_GRAPHICS_API void SetCursorPosition_Callback
		(
			input::GraphicsAPIInput::CursorPosition_Callback cursorPosition_Callback
		)
		{
			input::opengl::mCursorPosition_Callback = cursorPosition_Callback;
		}

		DOOMS_ENGINE_GRAPHICS_API void SetScroll_Callback(input::GraphicsAPIInput::Scroll_Callback scroll_Callback)
		{
			input::opengl::mScroll_Callback = scroll_Callback;
		}

		DOOMS_ENGINE_GRAPHICS_API void SetKey_Callback(input::GraphicsAPIInput::Key_Callback key_Callback)
		{
			input::opengl::mKey_Callback = key_Callback;
		}

		DOOMS_ENGINE_GRAPHICS_API void SetMouseButton_Callback(input::GraphicsAPIInput::MouseButton_Callback mouseButton_Callback)
		{
			input::opengl::mMouseButton_Callback = mouseButton_Callback;
		}

	}
}
