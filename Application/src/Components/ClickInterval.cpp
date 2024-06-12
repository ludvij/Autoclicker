#include "ClickInterval.hpp"

Ui::Component::ClickInterval::ClickInterval(const std::string_view name, float height_percent, ImVec2 original_spacing)
	: IComponent(name)
	, m_sp(original_spacing)
	, m_height(height_percent)
{
}

void Ui::Component::ClickInterval::OnRender()
{
	const auto size = ImGui::GetContentRegionAvail();
	if (ImGui::BeginChild("Click interval", { 0, size.y * m_height }, ImGuiChildFlags_AlwaysUseWindowPadding | ImGuiChildFlags_AutoResizeY))
	{
		auto c_size = ImGui::GetContentRegionAvail();
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, m_sp);
		ImGui::SeparatorText("Click interval");
		ImGui::PushItemWidth(c_size.x / 4.0f);
		{
			ImGui::LabelText("##Hours", "Hours"); ImGui::SameLine(0, 0);
			ImGui::LabelText("##Minutes", "Minutes"); ImGui::SameLine(0, 0);
			ImGui::LabelText("##Seconds", "Seconds"); ImGui::SameLine(0, 0);
			ImGui::LabelText("##Milliseconds", "Milliseconds");
		}
		ImGui::PopItemWidth();
		ImGui::SetNextItemWidth(-FLT_MIN);
		ImGui::InputInt4("##interval", m_interval);
		ImGui::PopStyleVar();
	}
	ImGui::EndChild();
}

void Ui::Component::ClickInterval::OnUpdate()
{
}
