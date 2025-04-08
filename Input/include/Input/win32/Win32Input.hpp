#ifndef GRAPHICS_WINDOWS_INPUT_HEADER
#define GRAPHICS_WINDOWS_INPUT_HEADER
#include "../Input.hpp"

#include <Windows.h>

namespace Input
{
class WindowsInput : public IInput
{
public:
	WindowsInput();
	virtual ~WindowsInput() override;
	// Inherited via IInput
	virtual bool GetButton(Button b) const override;
	virtual bool GetKey(Key k) const override;
	virtual bool GetMouseButton(MouseButton b) const override;
	virtual float GetMouseX() const override;
	virtual float GetMouseY() const override;

	virtual void SendButton(Button b) override;
	virtual void SendMouseButton(MouseButton m) override;
	virtual void SendKey(Key k) override;

	virtual void ReleaseButton(Button b) override;
	virtual void ReleaseMouseButton(MouseButton m) override;
	virtual void ReleaseKey(Key k) override;

private:

protected:
	virtual void platform_override() override;

private:
	bool m_key_state[256]{};
	POINT m_mouse_pos{};


	// Inherited via IInput


};
}
#endif//!GRAPHICS_WINDOWS_INPUT_HEADER