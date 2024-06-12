#ifndef GRAPHICS_WINDOW_HEADER
#define GRAPHICS_WINDOW_HEADER

#include <functional>
#include <unordered_map>
#include <vulkan/vulkan.h>

namespace Window
{

struct WindowExtent
{
	int w;
	int h;
};

enum class Event
{
	NONE,
	RESIZED,
	MINIMIZED,
	RESTORED,
	MAXIMIZED,
	CLOSE,
	MOVED,
	FOCUS_LOST_MOUSE,
	FOCUS_GAIN_MOUSE,
	FOCUS_LOST_KEYBOARD,
	FOCUS_GAIN_KEYBOARD,
};

using WindowFlags = uint32_t;
namespace Flags
{
static constexpr WindowFlags RESIZABLE  = 0x0000'0001;
static constexpr WindowFlags FULLSCREEN = 0x0000'0002;
static constexpr WindowFlags BORDERLESS = 0x0000'0004;
static constexpr WindowFlags MINIMIZED  = 0x0000'0008;
static constexpr WindowFlags MAXIMIZED  = 0x0000'0010;
static constexpr WindowFlags VULKAN     = 0x0000'0020;
static constexpr WindowFlags OPENGL     = 0x0000'0040;
}

class IWindow
{
public:
	virtual ~IWindow() = default;

	virtual WindowExtent GetDimensions() const = 0;
	virtual void GetDimensions(int* w, int* h) const = 0;

	virtual VkSurfaceKHR CreateVulkanSurface(VkInstance instance) = 0;

	virtual uint32_t GetWindowID() = 0;

	// imgui functions
	virtual void InitImguiForVulkan() = 0;
	virtual void ShutdownImGuiWindow() = 0;

	virtual void BeginImGuiFrame() = 0;

	void AddEventFunction(Event e, const std::function<void(IWindow*, void*)>& fn);

	virtual void ProcessEvents(void* event) = 0;


protected:
	std::unordered_map <Event, std::function<void(IWindow*, void*)>> m_event_fn;
};
}

#endif