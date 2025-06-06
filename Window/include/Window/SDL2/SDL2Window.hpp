#ifndef GRAPHICS_WINDOW_SDL_WINDOW_HEADER
#define GRAPHICS_WINDOW_SDL_WINDOW_HEADER

#include "../Window.hpp"
#include <string_view>

struct SDL_Window;
namespace Window
{



class SDL2Window : public IWindow
{
	using NativeType = SDL_Window;
public:
	SDL2Window(const std::string& title, int w, int h, WindowFlags flags);
	virtual ~SDL2Window() override;

	virtual WindowExtent GetDimensions() const override;
	virtual void GetDimensions(int* w, int* h) const override;

	virtual VkSurfaceKHR CreateVulkanSurface(VkInstance instance) override;

	virtual uint32_t GetWindowID() override;


	virtual void InitImguiForVulkan() override;


	// Inherited via IWindow
	void ShutdownImGuiWindow() override;

	// Inherited via IWindow
	void ProcessEvents(void* event) override;

	// Inherited via IWindow
	void BeginImGuiFrame() override;
private:
	NativeType* m_window;
};
}
#endif //!GRAPHICS_WINDOW_SDL_WINDOW_HEADER