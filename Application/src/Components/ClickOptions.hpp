#ifndef COMPONENT_CLICK_OPTIONS_HEADER
#define COMPONENT_CLICK_OPTIONS_HEADER
#include "IComponent.hpp"
#include <imgui.h>
namespace Ui::Component
{

class ClickOptions : public IComponent
{
public:
	ClickOptions(const std::string_view name, float height_percent, ImVec2 original_spacing);
	// Inherited via IComponent
	virtual void OnCreate() override;
	virtual void OnRender() override;
	virtual void OnUpdate() override;


	// Inherited via IComponent
	void Serialize(std::fstream& fs) const override;
	void Deserialize(std::fstream& fs) override;

private:
	ImVec2 m_sp;
	const char* m_mouse_button[3]{
		"Left",
		"Right",
		"Middle",
	};
	const char* m_mouse_click[2]{
		"Single",
		"Double",
	};

	size_t m_selected_button{ 0 };
	size_t m_selected_click{ 0 };
	float m_height;

	bool m_need_update{ true };

};

}
#endif