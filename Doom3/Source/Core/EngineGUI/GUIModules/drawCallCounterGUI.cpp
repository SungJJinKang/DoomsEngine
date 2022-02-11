#include "drawCallCounterGUI.h"

#include <imgui.h>
#include <Graphics/RenderingDebugger/RenderingDebugger.h>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>

void dooms::ui::drawCallCounterGUI::Render()
{
	if (ImGui::Begin("DrawCall"))
	{
		ImGui::Text("DrawCall : %u", dooms::graphics::GraphicsAPI::GetDrawCall());
		ImGui::Text("FPS : %f", dooms::graphics::RenderingDebugger::GetSingleton()->GetFPS());
	}
	ImGui::End();
}

