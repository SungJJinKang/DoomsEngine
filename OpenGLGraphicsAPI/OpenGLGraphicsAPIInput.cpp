#include "Input/GraphicsAPIInput.h"

#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GraphicsAPI.h"
#include "Input/GraphicsAPIInput.h"

#undef NEVER_HAPPEN
#ifdef _DEBUG
#define NEVER_HAPPEN assert(false)
#else
#define NEVER_HAPPEN __assume(0)
#endif


namespace dooms
{
	namespace graphics
	{
		namespace opengl
		{
			inline extern unsigned int GetGLKeyCode(const GraphicsAPIInput::eKEY_CODE keyCode)
			{
				switch (keyCode)
				{
				case GraphicsAPIInput::KEY_SPACE:
					return GLFW_KEY_SPACE;
				case GraphicsAPIInput::KEY_APOSTROPHE:
					return GLFW_KEY_APOSTROPHE;
				case GraphicsAPIInput::KEY_COMMA:
					return GLFW_KEY_COMMA;
				case GraphicsAPIInput::KEY_MINUS:
					return GLFW_KEY_MINUS;
				case GraphicsAPIInput::KEY_PERIOD:
					return GLFW_KEY_PERIOD;
				case GraphicsAPIInput::KEY_SLASH:
					return GLFW_KEY_SLASH;
				case GraphicsAPIInput::KEY_0:
					return GLFW_KEY_0;
				case GraphicsAPIInput::KEY_1:
					return GLFW_KEY_1;
				case GraphicsAPIInput::KEY_2:
					return GLFW_KEY_2;
				case GraphicsAPIInput::KEY_3:
					return GLFW_KEY_3;
				case GraphicsAPIInput::KEY_4:
					return GLFW_KEY_4;
				case GraphicsAPIInput::KEY_5:
					return GLFW_KEY_5;
				case GraphicsAPIInput::KEY_6:
					return GLFW_KEY_6;
				case GraphicsAPIInput::KEY_7:
					return GLFW_KEY_7;
				case GraphicsAPIInput::KEY_8:
					return GLFW_KEY_8;
				case GraphicsAPIInput::KEY_9:
					return GLFW_KEY_9;
				case GraphicsAPIInput::KEY_SEMICOLON:
					return GLFW_KEY_SEMICOLON;
				case GraphicsAPIInput::KEY_EQUAL:
					return GLFW_KEY_EQUAL;
				case GraphicsAPIInput::KEY_A:
					return GLFW_KEY_A;
				case GraphicsAPIInput::KEY_B:
					return GLFW_KEY_B;
				case GraphicsAPIInput::KEY_C:
					return GLFW_KEY_C;
				case GraphicsAPIInput::KEY_D:
					return GLFW_KEY_D;
				case GraphicsAPIInput::KEY_E:
					return GLFW_KEY_E;
				case GraphicsAPIInput::KEY_F:
					return GLFW_KEY_F;
				case GraphicsAPIInput::KEY_G:
					return GLFW_KEY_G;
				case GraphicsAPIInput::KEY_H:
					return GLFW_KEY_H;
				case GraphicsAPIInput::KEY_I:
					return GLFW_KEY_I;
				case GraphicsAPIInput::KEY_J:
					return GLFW_KEY_J;
				case GraphicsAPIInput::KEY_K:
					return GLFW_KEY_K;
				case GraphicsAPIInput::KEY_L:
					return GLFW_KEY_L;
				case GraphicsAPIInput::KEY_M:
					return GLFW_KEY_M;
				case GraphicsAPIInput::KEY_N:
					return GLFW_KEY_N;
				case GraphicsAPIInput::KEY_O:
					return GLFW_KEY_O;
				case GraphicsAPIInput::KEY_P:
					return GLFW_KEY_P;
				case GraphicsAPIInput::KEY_Q:
					return GLFW_KEY_Q;
				case GraphicsAPIInput::KEY_R:
					return GLFW_KEY_R;
				case GraphicsAPIInput::KEY_S:
					return GLFW_KEY_S;
				case GraphicsAPIInput::KEY_T:
					return GLFW_KEY_T;
				case GraphicsAPIInput::KEY_U:
					return GLFW_KEY_U;
				case GraphicsAPIInput::KEY_V:
					return GLFW_KEY_V;
				case GraphicsAPIInput::KEY_W:
					return GLFW_KEY_W;
				case GraphicsAPIInput::KEY_X:
					return GLFW_KEY_X;
				case GraphicsAPIInput::KEY_Y:
					return GLFW_KEY_Y;
				case GraphicsAPIInput::KEY_Z:
					return GLFW_KEY_Z;
				case GraphicsAPIInput::KEY_LEFT_BRACKET:
					return GLFW_KEY_LEFT_BRACKET;
				case GraphicsAPIInput::KEY_BACKSLASH:
					return GLFW_KEY_BACKSLASH;
				case GraphicsAPIInput::KEY_RIGHT_BRACKET:
					return GLFW_KEY_RIGHT_BRACKET;
				case GraphicsAPIInput::KEY_GRAVE_ACCENT:
					return GLFW_KEY_GRAVE_ACCENT;
				case GraphicsAPIInput::KEY_WORLD_1:
					return GLFW_KEY_WORLD_1;
				case GraphicsAPIInput::KEY_WORLD_2:
					return GLFW_KEY_WORLD_2;
				case GraphicsAPIInput::KEY_ESCAPE:
					return GLFW_KEY_ESCAPE;
				case GraphicsAPIInput::KEY_ENTER:
					return GLFW_KEY_ENTER;
				case GraphicsAPIInput::KEY_TAB:
					return GLFW_KEY_TAB;
				case GraphicsAPIInput::KEY_BACKSPACE:
					return GLFW_KEY_BACKSPACE;
				case GraphicsAPIInput::KEY_INSERT:
					return GLFW_KEY_INSERT;
				case GraphicsAPIInput::KEY_DELETE:
					return GLFW_KEY_DELETE;
				case GraphicsAPIInput::KEY_RIGHT:
					return GLFW_KEY_RIGHT;
				case GraphicsAPIInput::KEY_LEFT:
					return GLFW_KEY_LEFT;
				case GraphicsAPIInput::KEY_DOWN:
					return GLFW_KEY_DOWN;
				case GraphicsAPIInput::KEY_UP:
					return GLFW_KEY_UP;
				case GraphicsAPIInput::KEY_PAGE_UP:
					return GLFW_KEY_PAGE_UP;
				case GraphicsAPIInput::KEY_PAGE_DOWN:
					return GLFW_KEY_PAGE_DOWN;
				case GraphicsAPIInput::KEY_HOME:
					return GLFW_KEY_HOME;
				case GraphicsAPIInput::KEY_END:
					return GLFW_KEY_END;
				case GraphicsAPIInput::KEY_CAPS_LOCK:
					return GLFW_KEY_CAPS_LOCK;
				case GraphicsAPIInput::KEY_SCROLL_LOCK:
					return GLFW_KEY_SCROLL_LOCK;
				case GraphicsAPIInput::KEY_NUM_LOCK:
					return GLFW_KEY_NUM_LOCK;
				case GraphicsAPIInput::KEY_PRINT_SCREEN:
					return GLFW_KEY_PRINT_SCREEN;
				case GraphicsAPIInput::KEY_PAUSE:
					return GLFW_KEY_PAUSE;
				case GraphicsAPIInput::KEY_F1:
					return GLFW_KEY_F1;
				case GraphicsAPIInput::KEY_F2:
					return GLFW_KEY_F2;
				case GraphicsAPIInput::KEY_F3:
					return GLFW_KEY_F3;
				case GraphicsAPIInput::KEY_F4:
					return GLFW_KEY_F4;
				case GraphicsAPIInput::KEY_F5:
					return GLFW_KEY_F5;
				case GraphicsAPIInput::KEY_F6:
					return GLFW_KEY_F6;
				case GraphicsAPIInput::KEY_F7:
					return GLFW_KEY_F7;
				case GraphicsAPIInput::KEY_F8:
					return GLFW_KEY_F8;
				case GraphicsAPIInput::KEY_F9:
					return GLFW_KEY_F9;
				case GraphicsAPIInput::KEY_F10:
					return GLFW_KEY_F10;
				case GraphicsAPIInput::KEY_F11:
					return GLFW_KEY_F11;
				case GraphicsAPIInput::KEY_F12:
					return GLFW_KEY_F12;
				case GraphicsAPIInput::KEY_F13:
					return GLFW_KEY_F13;
				case GraphicsAPIInput::KEY_F14:
					return GLFW_KEY_F14;
				case GraphicsAPIInput::KEY_F15:
					return GLFW_KEY_F15;
				case GraphicsAPIInput::KEY_F16:
					return GLFW_KEY_F16;
				case GraphicsAPIInput::KEY_F17:
					return GLFW_KEY_F17;
				case GraphicsAPIInput::KEY_F18:
					return GLFW_KEY_F18;
				case GraphicsAPIInput::KEY_F19:
					return GLFW_KEY_F19;
				case GraphicsAPIInput::KEY_F20:
					return GLFW_KEY_F20;
				case GraphicsAPIInput::KEY_F21:
					return GLFW_KEY_F21;
				case GraphicsAPIInput::KEY_F22:
					return GLFW_KEY_F22;
				case GraphicsAPIInput::KEY_F23:
					return GLFW_KEY_F23;
				case GraphicsAPIInput::KEY_F24:
					return GLFW_KEY_F24;
				case GraphicsAPIInput::KEY_F25:
					return GLFW_KEY_F25;
				case GraphicsAPIInput::KEY_KP_0:
					return GLFW_KEY_KP_0;
				case GraphicsAPIInput::KEY_KP_1:
					return GLFW_KEY_KP_1;
				case GraphicsAPIInput::KEY_KP_2:
					return GLFW_KEY_KP_2;
				case GraphicsAPIInput::KEY_KP_3:
					return GLFW_KEY_KP_3;
				case GraphicsAPIInput::KEY_KP_4:
					return GLFW_KEY_KP_4;
				case GraphicsAPIInput::KEY_KP_5:
					return GLFW_KEY_KP_5;
				case GraphicsAPIInput::KEY_KP_6:
					return GLFW_KEY_KP_6;
				case GraphicsAPIInput::KEY_KP_7:
					return GLFW_KEY_KP_7;
				case GraphicsAPIInput::KEY_KP_8:
					return GLFW_KEY_KP_8;
				case GraphicsAPIInput::KEY_KP_9:
					return GLFW_KEY_KP_9;
				case GraphicsAPIInput::KEY_KP_DECIMAL:
					return GLFW_KEY_KP_DECIMAL;
				case GraphicsAPIInput::KEY_KP_DIVIDE:
					return GLFW_KEY_KP_DIVIDE;
				case GraphicsAPIInput::KEY_KP_MULTIPLY:
					return GLFW_KEY_KP_MULTIPLY;
				case GraphicsAPIInput::KEY_KP_SUBTRACT:
					return GLFW_KEY_KP_SUBTRACT;
				case GraphicsAPIInput::KEY_KP_ADD:
					return GLFW_KEY_KP_ADD;
				case GraphicsAPIInput::KEY_KP_ENTER:
					return GLFW_KEY_KP_ENTER;
				case GraphicsAPIInput::KEY_KP_EQUAL:
					return GLFW_KEY_KP_EQUAL;
				case GraphicsAPIInput::KEY_LEFT_SHIFT:
					return GLFW_KEY_LEFT_SHIFT;
				case GraphicsAPIInput::KEY_LEFT_CONTROL:
					return GLFW_KEY_LEFT_CONTROL;
				case GraphicsAPIInput::KEY_LEFT_ALT:
					return GLFW_KEY_LEFT_ALT;
				case GraphicsAPIInput::KEY_LEFT_SUPER:
					return GLFW_KEY_LEFT_SUPER;
				case GraphicsAPIInput::KEY_RIGHT_SHIFT:
					return GLFW_KEY_RIGHT_SHIFT;
				case GraphicsAPIInput::KEY_RIGHT_CONTROL:
					return GLFW_KEY_RIGHT_CONTROL;
				case GraphicsAPIInput::KEY_RIGHT_ALT:
					return GLFW_KEY_RIGHT_ALT;
				case GraphicsAPIInput::KEY_RIGHT_SUPER:
					return GLFW_KEY_RIGHT_SUPER;
				case GraphicsAPIInput::KEY_MENU:
					return GLFW_KEY_MENU;
				default:
					NEVER_HAPPEN;
					return 0;
				}
			}


			inline extern unsigned int GetGLMoustInput(const GraphicsAPIInput::eMoustInput mouseInput)
			{
				switch (mouseInput)
				{
				case GraphicsAPIInput::MOUSE_BUTTON_LEFT:
					return GLFW_MOUSE_BUTTON_LEFT;
				case GraphicsAPIInput::MOUSE_BUTTON_RIGHT:
					return GLFW_MOUSE_BUTTON_RIGHT;
				case GraphicsAPIInput::MOUSE_BUTTON_MIDDLE:
					return GLFW_MOUSE_BUTTON_MIDDLE;
				default:
					NEVER_HAPPEN;
					return 0;
				}
			}

			enum eCursorMode : unsigned int
			{
				CURSOR_MODE_NORMAL,
				CURSOR_MODE_HIDDEN,
				CURSOR_MODE_DISABLED,
			};

			inline extern unsigned int GetGLCursorMode(const GraphicsAPIInput::eCursorMode cursorMode)
			{
				switch (cursorMode)
				{
				case GraphicsAPIInput::CURSOR_MODE_NORMAL:
					return GLFW_CURSOR_NORMAL;
				case GraphicsAPIInput::CURSOR_MODE_HIDDEN: 
					return GLFW_CURSOR_HIDDEN;
				case GraphicsAPIInput::CURSOR_MODE_DISABLED: 
					return GLFW_CURSOR_DISABLED;
				default:
					NEVER_HAPPEN;
					return 0;
				}
			}

			
			extern void CursorPosition_Callback(GLFWwindow* window, double xpos, double ypos)
			{
				assert(GraphicsAPIInput::mCursorPosition_Callback != nullptr);
				(*GraphicsAPIInput::mCursorPosition_Callback)(xpos, ypos);
			}
			extern void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
			{
				assert(GraphicsAPIInput::mScroll_Callback != nullptr);
				(*GraphicsAPIInput::mScroll_Callback)(xoffset, yoffset);
			}
			extern void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				assert(GraphicsAPIInput::mKey_Callback != nullptr);
				(*GraphicsAPIInput::mKey_Callback)(key, scancode, action, mods);
			}
			extern void MouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
			{
				assert(GraphicsAPIInput::mMouseButton_Callback != nullptr);
				(*GraphicsAPIInput::mMouseButton_Callback)(button, action, mods);
			}
			extern void CursorEnterCallback(GLFWwindow* window, int entered)
			{
				assert(GraphicsAPIInput::mCursorEnterCallback != nullptr);
				(*GraphicsAPIInput::mCursorEnterCallback)(entered);

				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				CursorPosition_Callback(window, xpos, ypos);
			}
		}
	}
}

unsigned int dooms::graphics::GraphicsAPIInput::Initialize()
{
	GLFWwindow* const glfwWindow = reinterpret_cast<GLFWwindow*>(dooms::graphics::GraphicsAPI::GetPlatformWindow());

	glfwSetCursorEnterCallback(glfwWindow, &dooms::graphics::opengl::CursorEnterCallback);
	glfwSetCursorPosCallback(glfwWindow, &dooms::graphics::opengl::CursorPosition_Callback);
	glfwSetScrollCallback(glfwWindow, &dooms::graphics::opengl::Scroll_Callback);

	glfwSetKeyCallback(glfwWindow, &dooms::graphics::opengl::Key_Callback);
	glfwSetMouseButtonCallback(glfwWindow, &dooms::graphics::opengl::MouseButton_Callback);

	return 0;
}

unsigned int dooms::graphics::GraphicsAPIInput::DeInitialize()
{
	return 0;
}

void dooms::graphics::GraphicsAPIInput::PollEvents()
{
	glfwPollEvents();
}

void dooms::graphics::GraphicsAPIInput::SetCursorMode(const eCursorMode cursorMode)
{
	glfwSetInputMode(reinterpret_cast<GLFWwindow*>(GraphicsAPI::GetPlatformWindow()), GLFW_CURSOR, opengl::GetGLCursorMode(cursorMode));
}

dooms::graphics::GraphicsAPIInput::eMouseButtonMode dooms::graphics::GraphicsAPIInput::ConvertRawValueToMouseButtonMode(const int mode)
{
	if(mode == GLFW_PRESS)
	{
		return eMouseButtonMode::PRESS;
	}
	else if(mode == GLFW_RELEASE)
	{
		return eMouseButtonMode::RELEASE;
	}
	else
	{
		NEVER_HAPPEN;
		return eMouseButtonMode::RELEASE;
	}
}
