#include "ClickConfirm.hpp"

#include <Application.hpp>

Ui::Component::ClickConfirm::ClickConfirm(const std::string_view name, float height_percent, ImVec2 original_spacing)
	: IComponent(name)
	, m_height(height_percent)
	, m_sp(original_spacing)
{
}

void Ui::Component::ClickConfirm::OnCreate()
{
	m_need_update = true;
}

void Ui::Component::ClickConfirm::OnRender()
{
	const auto& style = ImGui::GetStyle();
	const auto size = ImGui::GetWindowContentRegionMax() - ImGui::GetWindowContentRegionMin();
	if (ImGui::BeginChild("Click confirm", { 0, size.y * m_height }, ImGuiChildFlags_AlwaysUseWindowPadding))
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, m_sp);
		const auto c_size = ImGui::GetContentRegionAvail();
		const ImVec2 b_size = c_size / 2.0f - style.ItemSpacing;
		if (ImGui::Button("Change hotkey", b_size))
		{

		}
		if (ImGui::Button(Application::Get().clicking ? "Stop" : "Start", { -1,-1 }))
		{
			Application::Get().clicking = !Application::Get().clicking;
		}
		ImGui::PopStyleVar();
	}
	ImGui::EndChild();
}

void Ui::Component::ClickConfirm::OnUpdate()
{
	if (!m_need_update)
	{
		return;
	}
	m_need_update = false;

	Application::Get().SetTrigger(Input::GetOffset(Input::MouseButton::AUX_1));
	m_current_trigger = Input::GetOffset(Input::MouseButton::AUX_1);
}

void Ui::Component::ClickConfirm::Serialize(std::fstream& fs) const
{
	Fman::SerializeNumber(m_current_trigger);
}

void Ui::Component::ClickConfirm::Deserialize(std::fstream& fs)
{
	Fman::DeserializeNumber(m_current_trigger);
	m_need_update = true;
}
