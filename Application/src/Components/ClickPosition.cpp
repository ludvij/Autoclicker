#include "ClickPosition.hpp"

Ui::Component::ClickPosition::ClickPosition(const std::string_view name, float height_percent, ImVec2 original_spacing)
	: IComponent(name)
	, m_height(height_percent)
	, m_sp(original_spacing)
{
}

void Ui::Component::ClickPosition::OnRender()
{
	const auto size = ImGui::GetWindowContentRegionMax() - ImGui::GetWindowContentRegionMin();
	const auto& style = ImGui::GetStyle();
	ImGui::Dummy({ 0, size.y * m_height });
	//ImGui::SetCursorPosY(size.y * .5f);
	/*

	if (ImGui::BeginChild("Click position", { 0, size.y * m_height }, ImGuiChildFlags_AlwaysUseWindowPadding))
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, m_sp);
		const auto c_size = ImGui::GetContentRegionAvail();
		const auto def = ImGui::GetCursorPos();
		ImGui::SeparatorText("Cursor position");
		ImVec2 r_size = {
			ImGui::CalcTextSize("Current location").x + style.ItemInnerSpacing.x + ImGui::GetFrameHeight(),
			ImGui::GetFrameHeight(),
		};
		r_size.x += style.ItemSpacing.x + ImGui::GetFrameHeight();
		r_size.x += style.ItemSpacing.x + ImGui::CalcTextSize("Pick location").x + style.FramePadding.x * 3;
		ImGui::Dummy(r_size);
		ImGui::SameLine();
		ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x / 2.f);
		{
			ImGui::LabelText("##input x", "X");
			ImGui::SameLine(0, 0);
			ImGui::LabelText("##input y", "Y");
			ImGui::PopItemWidth();
		}
		if (ImGui::RadioButton("Current location", !m_fixed))
		{
			m_fixed = false;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("##Current location", m_fixed))
		{
			m_fixed = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("Pick Location"))
		{

		}
		ImGui::SameLine();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		ImGui::InputInt2("##input pos", m_location);
		ImGui::PopStyleVar();
	}
	ImGui::EndChild();
	*/
}

void Ui::Component::ClickPosition::OnUpdate()
{
}

void Ui::Component::ClickPosition::Serialize(std::fstream& fs) const
{
	Fman::SerializeNumber(m_fixed);
	Fman::SerializeNumber(m_location[0]);
	Fman::SerializeNumber(m_location[1]);
}

void Ui::Component::ClickPosition::Deserialize(std::fstream& fs)
{
	Fman::DeserializeNumber(m_fixed);
	Fman::DeserializeNumber(m_location[0]);
	Fman::DeserializeNumber(m_location[1]);
}
