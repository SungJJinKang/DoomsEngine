#include "LogGUI.h"

#include <Core.h>

#include "imgui.h"
#include "Logger/eLogType.h"
#include "Logger/Logger.h"
#include "Logger/LoggerSetting.h"
#include <magic_enum.hpp>

#define E_LOG_STRING_BUFFER 15

namespace dooms::ui::logGUI
{
	static std::array<char[E_LOG_STRING_BUFFER], magic_enum::enum_count<dooms::logger::eLogType>()> eLogString{};
}


void dooms::ui::LogGUI::RenderMenuBar()
{
	{
		bool isStop = !IsEnabled;
		if (ImGui::Checkbox("Stop Logging", &isStop))
		{
			IsEnabled = !isStop;
		}
	}


	{
		ImGui::SameLine(0, 15);

		ImGui::Text(" | ");

		ImGui::SameLine(0, 15);

		bool breakWhenError = logger::BREAK_WHEN_ERROR;
		if (ImGui::Checkbox("Break When Error", &breakWhenError))
		{
			logger::BREAK_WHEN_ERROR = breakWhenError;
		}
	}



	{
		ImGui::SameLine(0, 15);

		ImGui::Text(" | ");

		ImGui::SameLine(0, 15);

		auto current_item = magic_enum::enum_index<dooms::logger::eLogType>(static_cast<dooms::logger::eLogType>(dooms::logger::MAX_DEBUG_LEVEL));

		size_t currentItemIndex = current_item.has_value() ? current_item.value() : 0;

		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::PushItemWidth(120);

		if (ImGui::BeginCombo("MAX LOG LEVEL", logGUI::eLogString[currentItemIndex], ImGuiComboFlags_NoArrowButton))
		{
			for (int n = 0; n < magic_enum::enum_count<dooms::logger::eLogType>(); n++)
			{
				bool is_selected = (currentItemIndex == n);

				if (ImGui::Selectable(logGUI::eLogString[n], is_selected))
				{
					currentItemIndex = n;
					dooms::logger::MAX_DEBUG_LEVEL = magic_enum::enum_value<dooms::logger::eLogType>(currentItemIndex);
				}

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();

				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
	}

	{
		ImGui::SameLine(0, 15);

		ImGui::Text(" | ");

		ImGui::SameLine(0, 15);

		auto current_item = magic_enum::enum_index<dooms::logger::eLogType>(static_cast<dooms::logger::eLogType>(dooms::logger::MIN_DEBUG_LEVEL));

		size_t currentItemIndex = current_item.has_value() ? current_item.value() : 0;

		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::PushItemWidth(120);

		if (ImGui::BeginCombo("MIN LOG LEVEL", logGUI::eLogString[currentItemIndex], ImGuiComboFlags_NoArrowButton))
		{
			for (int n = 0; n < magic_enum::enum_count<dooms::logger::eLogType>(); n++)
			{
				bool is_selected = (currentItemIndex == n);

				if (ImGui::Selectable(logGUI::eLogString[n], is_selected))
				{
					currentItemIndex = n;
					dooms::logger::MIN_DEBUG_LEVEL = magic_enum::enum_value<dooms::logger::eLogType>(currentItemIndex);
				}

				if (is_selected)
				{

					ImGui::SetItemDefaultFocus();

				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
	}
}

void dooms::ui::LogGUI::Init()
{
	Base::Init();

	for (size_t i = 0; i < magic_enum::enum_count<dooms::logger::eLogType>(); i++)
	{
		std::string_view enumName = magic_enum::enum_name<dooms::logger::eLogType>(magic_enum::enum_value<dooms::logger::eLogType>(i));

		D_ASSERT(enumName.size() < E_LOG_STRING_BUFFER);

		std::memcpy(logGUI::eLogString[i], enumName.data(), enumName.size());
		logGUI::eLogString[i][enumName.size()] = '\0';
	}
	
	for (size_t i = 0; i < GUI_LOG_BUFFER_COUNT; i++)
	{
		LogBuffer[i][0] = '\0';
	}
}

void dooms::ui::LogGUI::Render()
{
	if (ImGui::Begin("Log"))
	{
		RenderMenuBar();

		const long logIndex = LogIndex % GUI_LOG_BUFFER_COUNT;

		for (long index = logIndex - 1; index >= 0; index--)
		{
			if (LogBuffer[index][0] != '\0')
			{
				ImGui::Text("%s", LogBuffer[index]);
			}
		}

		for (long index = GUI_LOG_BUFFER_COUNT - 1; index >= logIndex; index--)
		{
			if (LogBuffer[index][0] != '\0')
			{
				ImGui::Text("%s", LogBuffer[index]);
			}
		}
	}

	ImGui::End();
}


long dooms::ui::LogGUI::IncrementLogIndex()
{
	long index = LogIndex++;

	return index % GUI_LOG_BUFFER_COUNT;
}







