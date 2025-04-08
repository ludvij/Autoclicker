#include "Application.hpp"
#include "ClickInterval.hpp"

Ui::Component::ClickInterval::ClickInterval(const std::string_view name, float height_percent, ImVec2 original_spacing)
	: IComponent(name)
	, m_sp(original_spacing)
	, m_height(height_percent)
{
}

void Ui::Component::ClickInterval::OnCreate()
{
	m_need_update = true;
}

void Ui::Component::ClickInterval::OnRender()
{
	const auto size = ImGui::GetWindowContentRegionMax() - ImGui::GetWindowContentRegionMin();
	if (ImGui::BeginChild("Click interval", { 0, size.y * m_height }, ImGuiChildFlags_AlwaysUseWindowPadding))
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
		if (ImGui::InputInt4("##interval", m_interval))
		{
			m_need_update = true;
		}
		ImGui::PopStyleVar();
	}
	ImGui::EndChild();
}

void Ui::Component::ClickInterval::OnUpdate()
{
	if (!m_need_update)
	{
		return;
	}
	m_need_update = false;
	Application::Get().SetInterval(m_interval);
}

void Ui::Component::ClickInterval::Serialize(std::fstream& fs) const
{
	Fman::SerializeNumber(m_interval[0]);
	Fman::SerializeNumber(m_interval[1]);
	Fman::SerializeNumber(m_interval[2]);
	Fman::SerializeNumber(m_interval[3]);
}

void Ui::Component::ClickInterval::Deserialize(std::fstream& fs)
{
	Fman::DeserializeNumber(m_interval[0]);
	Fman::DeserializeNumber(m_interval[1]);
	Fman::DeserializeNumber(m_interval[2]);
	Fman::DeserializeNumber(m_interval[3]);

	m_need_update = true;

}
