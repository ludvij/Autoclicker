#ifndef COMPONENT_CLICK_INTERVAL_HEADER
#define COMPONENT_CLICK_INTERVAL_HEADER
#include "IComponent.hpp"

#include <imgui.h>

namespace Ui::Component
{
class ClickInterval : public IComponent
{
public:
	ClickInterval(const std::string_view name, float height_percent, ImVec2 original_spacing);

	// Inherited via IComponent
	virtual void OnCreate() override;
	virtual void OnRender() override;
	virtual void OnUpdate() override;
private:
	ImVec2 m_sp;
	int m_interval[4]{
		0,0,0,5
	};
	float m_height;

};
}
#endif