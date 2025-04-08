#ifndef COMPONENT_CLICK_CONFIRM_HEADER
#define COMPONENT_CLICK_CONFIRM_HEADER
#include "IComponent.hpp"

#include <imgui.h>

namespace Ui::Component
{
class ClickConfirm : public IComponent
{
public:
	ClickConfirm(const std::string_view name, float height_percent, ImVec2 original_spacing);

	// Inherited via IComponent
	virtual void OnCreate() override;
	virtual void OnRender() override;
	virtual void OnUpdate() override;

	// Inherited via IComponent
	void Serialize(std::fstream& fs) const override;

	void Deserialize(std::fstream& fs) override;


private:
	ImVec2 m_sp;
	float m_height;
	size_t m_current_trigger{};

	bool m_need_update{ true };

};
}
#endif