#include "SDL2/SDL2Window.hpp"


#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_vulkan.h>
#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include <bit>
#include <cstdint>

namespace Window
{

static Event get_equivalent_event_from_sdl(uint32_t event)
{
	typedef Window::Event E;
	switch (event)
	{
	case SDL_WINDOWEVENT_RESIZED:      return E::RESIZED;
	case SDL_WINDOWEVENT_MINIMIZED:    return E::MINIMIZED;
	case SDL_WINDOWEVENT_RESTORED:     return E::RESTORED;
	case SDL_WINDOWEVENT_MAXIMIZED:    return E::MAXIMIZED;
	case SDL_WINDOWEVENT_CLOSE:        return E::CLOSE;
	case SDL_WINDOWEVENT_MOVED:        return E::MOVED;
	case SDL_WINDOWEVENT_LEAVE:        return E::FOCUS_LOST_MOUSE;
	case SDL_WINDOWEVENT_ENTER:        return E::FOCUS_GAIN_MOUSE;
	case SDL_WINDOWEVENT_FOCUS_LOST:   return E::FOCUS_LOST_KEYBOARD;
	case SDL_WINDOWEVENT_FOCUS_GAINED: return E::FOCUS_GAIN_KEYBOARD;
	default: return E::NONE;
	}
}

static SDL_WindowFlags get_equivalent_flag_from_sdl(Window::WindowFlags flag)
{
	uint32_t window_flags = 0;
	if (flag & Flags::BORDERLESS) window_flags |= SDL_WINDOW_BORDERLESS;
	if (flag & Flags::FULLSCREEN) window_flags |= SDL_WINDOW_FULLSCREEN;
	if (flag & Flags::RESIZABLE)  window_flags |= SDL_WINDOW_RESIZABLE;
	if (flag & Flags::MAXIMIZED)  window_flags |= SDL_WINDOW_MAXIMIZED;
	if (flag & Flags::MINIMIZED)  window_flags |= SDL_WINDOW_MINIMIZED;
	if (flag & Flags::OPENGL)     window_flags |= SDL_WINDOW_OPENGL;
	if (flag & Flags::VULKAN)     window_flags |= SDL_WINDOW_VULKAN;

	return static_cast<SDL_WindowFlags>( window_flags );
}


SDL2Window::SDL2Window(const std::string& title, int w, int h, WindowFlags flags)
{

	SDL_WindowFlags window_flags = get_equivalent_flag_from_sdl(flags);

	m_window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w,
		h,
		window_flags
	);
}

SDL2Window::~SDL2Window()
{
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

WindowExtent SDL2Window::GetDimensions() const
{
	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);

	return { w , h };
}

void SDL2Window::GetDimensions(int* w, int* h) const
{
	SDL_GetWindowSize(m_window, w, h);
}


VkSurfaceKHR SDL2Window::CreateVulkanSurface(VkInstance instance)
{
	VkSurfaceKHR surface;
	SDL_Vulkan_CreateSurface(m_window, instance, &surface);
	return surface;
}


uint32_t SDL2Window::GetWindowID()
{
	return SDL_GetWindowID(m_window);
}
void SDL2Window::InitImguiForVulkan()
{
	ImGui_ImplSDL2_InitForVulkan(m_window);
}
void SDL2Window::ShutdownImGuiWindow()
{
	ImGui_ImplSDL2_Shutdown();
}
void SDL2Window::ProcessEvents(void* event)
{
	SDL_Event* e = static_cast<SDL_Event*>( event );
	ImGui_ImplSDL2_ProcessEvent(e);
	if (e->type != SDL_WINDOWEVENT)
	{
		return;
	}

	Event my_event = get_equivalent_event_from_sdl(e->window.event);
	if (m_event_fn.contains(my_event))
	{
		m_event_fn.at(my_event)( this, event );
	}

}
void SDL2Window::BeginImGuiFrame()
{
	ImGui_ImplSDL2_NewFrame();
}
}