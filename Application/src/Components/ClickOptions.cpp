#include "ClickOptions.hpp"

Ui::Component::ClickOptions::ClickOptions(const std::string_view name, float height_percent, ImVec2 original_spacing)
	: IComponent(name)
	, m_height(height_percent)
	, m_sp(original_spacing)
{
}

void Ui::Component::ClickOptions::OnRender()
{
	const auto size = ImGui::GetContentRegionAvail();
	const auto w_2 = ( size.x ) / 2.0f;// - sp.x / 2.0f;
	if (ImGui::BeginChild("Click options", { w_2, size.y * .3f }, ImGuiChildFlags_AlwaysUseWindowPadding | ImGuiChildFlags_AutoResizeY))
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, m_sp);

		ImGui::SeparatorText("Click options");
		const char* button_preview = m_mouse_button[m_selected_button];
		const char* type_preview = m_mouse_click[m_selected_click];
		ImGui::SetNextItemWidth(-100);
		if (ImGui::BeginCombo("Mouse button", button_preview))
		{
			for (size_t i = 0; i < IM_ARRAYSIZE(m_mouse_button); i++)
			{
				const bool is_selected = m_selected_button == i;
				if (ImGui::Selectable(m_mouse_button[i], is_selected))
				{
					m_selected_button = i;
				}
				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
		ImGui::SetNextItemWidth(-100);

		if (ImGui::BeginCombo("Click type", type_preview))
		{
			for (size_t i = 0; i < IM_ARRAYSIZE(m_mouse_click); i++)
			{
				const bool is_selected = m_selected_click == i;
				if (ImGui::Selectable(m_mouse_click[i], is_selected))
				{
					m_selected_click = i;
				}
				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopStyleVar();
	}
	ImGui::EndChild();
	ImGui::SameLine(0, 0);
	if (ImGui::BeginChild("Click repeat", { w_2, size.y * .3f }, ImGuiChildFlags_AlwaysUseWindowPadding | ImGuiChildFlags_AutoResizeY))
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, m_sp);

		ImGui::SeparatorText("Click repeat");
		ImGui::PopStyleVar();
	}
	ImGui::EndChild();
}

void Ui::Component::ClickOptions::OnUpdate()
{
}
