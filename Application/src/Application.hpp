#ifndef GRAPHICS_APPLICATION_HEADER
#define GRAPHICS_APPLICATION_HEADER

#include "Components/IComponent.hpp"
#include <Input/Input.hpp>
#include <Sprite.hpp>
#include <Window/Window.hpp>

#include <functional>
#include <memory>
#include <string>

#include <map>

struct ImFont;
struct SDL_Window;

using ms_t = std::chrono::milliseconds;

namespace Ui
{
struct Configuration
{
	std::string name = "AutoClicker";
	uint32_t w = 600;
	uint32_t h = 600;
};



class Application
{
public:
	ms_t interval{};
	Input::MouseButton mouse_button;
	bool clicking{ false };

public:
	Application(const Configuration& config = Configuration());
	~Application();

	static Application& Get();

	static double GetDelta();

	void Error(const char* name, std::string_view msg);

	void SetInterval(const int* interval);

	static void SetUpdate(bool set);

	template<typename T, class... Args>
	void AddComponent(const std::string_view name, Args... args) requires( std::derived_from<T, Component::IComponent> )
	{
		std::shared_ptr<T> comp = std::make_shared<T>(name, std::forward<Args>(args)...);
		comp->OnCreate();
		m_components.insert({ comp->name, comp });
	}

	void AddComponent(const std::shared_ptr<Component::IComponent>& component);

	void RemoveComponent(const std::string_view name);

	void Close();

	void Run();

private:
	void init();
	void init_input_actions();
	void init_windowevent_actions();
	void shutdown();

	void main_loop();

	void event_loop();

	void draw_ui();
	void draw_application();
	void update();

	void clear_deleted_components();



private:
	bool m_should_quit{ false };
	bool m_stop_rendering{ false };
	Configuration m_config;


	std::map<std::string_view, std::shared_ptr<Component::IComponent>> m_components;
	// this only exists so I can forbid recreation of some components


	std::unique_ptr<Input::IInput> m_input;
	std::shared_ptr<Window::IWindow> m_window;


	double m_delta{};

	bool m_can_update{ true };

};

}

#endif

