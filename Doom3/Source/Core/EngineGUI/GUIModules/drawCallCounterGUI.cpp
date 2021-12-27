#include "drawCallCounterGUI.h"

#include <imgui.h>
#include <Graphics/DebugGraphics/RenderingDebugger.h>

void dooms::ui::drawCallCounterGUI::Render()
{
	if (ImGui::Begin("DrawCall"))
	{
		ImGui::Text("DrawCall : %llu", dooms::graphics::RenderingDebugger::GetDrawCallCounter());
		ImGui::Text("FPS : %f", dooms::graphics::RenderingDebugger::GetFPS());
	}
}

