#include "Application.hpp"

#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <print>
#include <ranges>
#include <vector>

#include "Components/ClickConfirm.hpp"
#include "Components/ClickInterval.hpp"
#include "Components/ClickOptions.hpp"
#include "Components/ClickPosition.hpp"
#include "Components/CloseDialog.hpp"
#include "Components/IComponent.hpp"

#include <Input/win32/Win32Input.hpp>
#include <Window/win32/Win32Window.hpp>	

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
	m_window = std::make_shared<Window::Win32Window>(m_config.name, m_config.w, m_config.h, Window::Flags::VULKAN);
	m_input = std::make_unique<Input::WindowsInput>();

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

void Application::SetInterval(const int* p_interval)
{
	const int h  = p_interval[0];
	const int m  = p_interval[1];
	const int s  = p_interval[2];
	const int ms = p_interval[3];

	interval = h * 1h + m * 1min + s * 1s + ms * 1ms;
	std::println("Set duration: {:%T}", interval);
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

	AddComponent<Component::ClickInterval>("0 Click interval", .2f, ImGui::GetStyle().ItemSpacing);
	AddComponent<Component::ClickOptions>("1 Click options", .3f, ImGui::GetStyle().ItemSpacing);
	AddComponent<Component::ClickPosition>("2 Click position", .2f, ImGui::GetStyle().ItemSpacing);
	AddComponent<Component::ClickConfirm>("3 Click confirm", .3f, ImGui::GetStyle().ItemSpacing);

	init_input_actions();
	init_windowevent_actions();
}


void Application::init_input_actions()
{
	typedef Input::Key K;
	typedef Input::MouseButton M;
	typedef Input::Button B;

	m_input->AddMouseAction(M::AUX_1, [&](Input::IInput* i)
		{
			INPUT_NOT_REPEATED(i);

			clicking = !clicking;
		});
	m_input->AddUnmappedAction([&](Input::IInput* i)
		{
			if (!clicking)
			{
				return;
			}
			INPUT_REPEAT_EVERY(i, interval);

			i->SendMouseButton(mouse_button);
		});
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
	//m_window->AddEventFunction(E::CLOSE, [&](Window::IWindow* i, void* event)
	//	{
	//		MSG* msg = static_cast<MSG*>( event );
	//		if (msg->hwnd == static_cast<HWND>( i->GetWindowID() ))
	//		{
	//			m_should_quit = true;
	//		}
	//	});
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
	static uint32_t frame=0;
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
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			m_should_quit = true;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		m_window->ProcessEvents(&msg);
		m_input->ProcessEvents(&msg);

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

