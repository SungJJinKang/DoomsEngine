#include "DrawCallCounterGUI.h"

#include "imgui/imgui.h"
#include <Rendering//RenderingDebugger/RenderingDebugger.h>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>

void dooms::ui::DrawCallCounterGUI::Init()
{
	Base::Init();
}

void dooms::ui::DrawCallCounterGUI::Render()
{
	if (ImGui::Begin("DrawCall"))
	{
		ImGui::Text("DrawCall : %u", dooms::graphics::GraphicsAPI::GetDrawCall());
		ImGui::Text("FPS : %f", dooms::graphics::RenderingDebugger::GetSingleton()->GetFPS());
	}
	ImGui::End();
}
