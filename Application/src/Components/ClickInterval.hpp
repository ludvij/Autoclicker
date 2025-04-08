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

	// Inherited via IComponent
	void Serialize(std::fstream& fs) const override;

	void Deserialize(std::fstream& fs) override;
private:
	ImVec2 m_sp;
	int m_interval[4]{
		0,0,0,20
	};
	float m_height;

	bool m_need_update{ true };


};
}
#endif