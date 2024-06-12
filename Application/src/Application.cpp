#include "Application.hpp"

#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <print>
#include <ranges>
#include <vector>

#include <SDL.h>

#include "Components/ClickInterval.hpp"
#include "Components/ClickOptions.hpp"
#include "Components/CloseDialog.hpp"
#include "Components/IComponent.hpp"

#include <Input/SDL2/SDL2Input.hpp>
#include <Window/SDL2/SDL2Window.hpp>	

#include <FileManager/FileManager.hpp>

#include <RendererAPI.hpp>


using namespace std::chrono_literals;

namespace Ui
{
Application* s_instance;

Application::Application(const Configuration& config)
	: m_config(config)
{
	s_instance = this;
	m_window = std::make_shared<Window::SDL2Window>(m_config.name, m_config.w, m_config.h, Window::Flags::VULKAN);
	m_input = std::make_unique<Input::SDL2Input>();

	init();

}

Application::~Application()
{
	shutdown();
	s_instance = nullptr;
}

Application& Application::Get()
{
	return *s_instance;
}

double Application::GetDelta()
{
	return Get().m_delta;
}

void Application::Error(const char* name, std::string_view msg)
{
	AddComponent<Component::CloseDialog>(name, msg, false);
}


void Application::SetUpdate(bool set)
{
	Get().m_can_update = set;
}

void Application::init()
{
	//Fman::PushFolder("clicker_swap");
	//Fman::SetRoot();


	Renderer::Init(m_window, true);
	auto& io = ImGui::GetIO();
	io.IniFilename = NULL;//Fman::AllocateFileName("imgui.ini");

	AddComponent<Component::ClickInterval>("Click interval", .2f, ImGui::GetStyle().ItemSpacing);
	AddComponent<Component::ClickOptions>("Click options", .3f, ImGui::GetStyle().ItemSpacing);

	init_button_actions();
	init_keyboard_actions();
	init_windowevent_actions();
}

void Application::init_button_actions()
{


}

void Application::init_keyboard_actions()
{
	typedef Input::Key K;
}

void Application::init_windowevent_actions()
{
	typedef Window::Event E;
	m_window->AddEventFunction(E::RESIZED, [&](Window::IWindow* i, void* event)
		{
			Renderer::RequestResize();
		});
	m_window->AddEventFunction(E::MINIMIZED, [&](Window::IWindow* i, void* event)
		{
			m_stop_rendering = true;
		});
	m_window->AddEventFunction(E::RESTORED, [&](Window::IWindow* i, void* event)
		{
			m_stop_rendering = false;
		});
	m_window->AddEventFunction(E::CLOSE, [&](Window::IWindow* i, void* event)
		{
			auto e = static_cast<SDL_Event*>( event );
			if (e->window.windowID == i->GetWindowID())
			{
				m_should_quit = true;
			}
		});
}

void Application::shutdown()
{
	m_components.clear();
}


void Application::AddComponent(const std::shared_ptr<Component::IComponent>& component)
{
	m_components.insert({ component->name, component });
	component->OnCreate();
}

void Application::RemoveComponent(const std::string_view id)
{
	m_components[id]->removed = true;
}


void Application::Run()
{
	main_loop();
}

void Application::Close()
{
	m_should_quit = true;
}

void Application::main_loop()
{
	while (!m_should_quit)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		event_loop();

		if (m_stop_rendering)
		{
			continue;
		}
		Renderer::Resize();
		if (m_can_update)
		{
			update();
		}

		clear_deleted_components();
		draw_application();

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>( end - begin );
		m_delta = static_cast<double>( duration.count() ) / 1e6;
	}
}
void Application::event_loop()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_should_quit = true;
			break;
		default:
			break;
		}
		m_window->ProcessEvents(&event);
		m_input->ProcessEvents(&event);
	}

	m_input->Update();

}

void Application::draw_ui()
{
	m_window->BeginImGuiFrame();
	Renderer::BeginImGuiFrame();

	ImGui::NewFrame();
	// preparing window
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos({ viewport->WorkPos.x, viewport->WorkPos.y });
	ImGui::SetNextWindowSize({ viewport->WorkSize.x, viewport->WorkSize.y });
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGuiWindowFlags w_flags =
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus;
	ImGui::Begin("Window", nullptr, w_flags);
	ImGui::PopStyleVar(2);
	//
	const auto sp = ImGui::GetStyle().ItemSpacing;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });

	const auto pad = ImGui::GetStyle().FramePadding;
	const auto size = ImGui::GetContentRegionAvail();

	for (const auto& [k, v] : m_components)
	{
		v->OnRender();
	}
	ImGui::PopStyleVar();
	ImGui::End();

	ImGui::Render();
	// Update and Render additional Platform Windows
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}
void Application::draw_application()
{
	draw_ui();

	Renderer::Draw();
}
void Application::update()
{
	for (const auto& [k, v] : m_components)
	{
		v->OnUpdate();
	}

}
void Application::clear_deleted_components()
{
	std::list<std::string_view> deleter;
	for (const auto& [k, v] : m_components)
	{
		if (v->removed)
		{
			deleter.push_back(k);
		}
	}

	for (const auto& del : deleter)
	{
		m_components.erase(del);
	}
}

}

