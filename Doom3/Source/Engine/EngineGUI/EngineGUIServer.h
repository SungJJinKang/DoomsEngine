#pragma once

#include <vector>

#include <Core.h>
#include <Game/IGameFlow.h>
#include <Simple_SingleTon/Singleton.h>

#include "EngineGUIServer.reflection.h"
namespace dooms
{
	namespace ui
	{
		class EngineGUIModule;
		class D_CLASS EngineGUIServer : public IGameFlow, public ISingleton<EngineGUIServer>
		{
			GENERATE_BODY()

		private:

			D_PROPERTY()
			std::vector<EngineGUIModule*> mEngineGUIModules;

			void InitializeEngineGUIModules();
			bool InitializeImgui();
			bool DestroyImgui();

		public:

			D_PROPERTY()
			bool bmIsEngineGUIAvaliable;

			EngineGUIServer();
			~EngineGUIServer();

			void Init(const int argc, char* const* const argv) override;
			void Update() override;
			void OnEndOfFrame() override;
			

			void PreRender();
			void Render();
			void PostRender();

			bool GetIsEngineGUIAvaliable() const;
			bool& GetIsEngineGUIAvaliableRef();
		};
	}
}
