#pragma once

namespace dooms
{
	namespace graphics
	{
		class GraphicsAPIInput;
		class __declspec(dllexport) GraphicsAPI
		{
		private:

			GraphicsAPIInput* mGraphicsAPIInputManager;

		public:

			using DEBUG_FUNCTION = void (*)(const char* const debugMessage);
			inline static DEBUG_FUNCTION* mDEBUG_FUNCTION = nullptr;
			
			static void Initialize();
			static void DeInitialize();
			static void SwapBuffer();

			static void SetVSync(const bool isEnabled);
		};
	}
}


