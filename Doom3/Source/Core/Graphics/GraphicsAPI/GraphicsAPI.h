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

			GraphicsAPI();

			void Initialize();
			void DeInitialize();
			void SwapBuffer();
		};
	}
}


