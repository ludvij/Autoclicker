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
	virtual void OnRender() override;
	virtual void OnUpdate() override;
private:
	ImVec2 m_sp;
	float m_height;

};
}
#endif