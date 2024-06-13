#ifndef COMPONENT_CLICK_POSITION_HEADER
#define COMPONENT_CLICK_POSITION_HEADER
#include "IComponent.hpp"

#include <imgui.h>

namespace Ui::Component
{
class ClickPosition : public IComponent
{
public:
	ClickPosition(const std::string_view name, float height_percent, ImVec2 original_spacing);

	// Inherited via IComponent
	virtual void OnRender() override;
	virtual void OnUpdate() override;
private:
	ImVec2 m_sp;
	int m_location[2]{
		0,0,
	};
	bool m_fixed{false};
	float m_height;

};
}
#endif