#ifndef GRAPHICS_INPUT_HEADER
#define GRAPHICS_INPUT_HEADER
#include <deque>
#include <functional>
#include <unordered_map>

#include <chrono>

#include <print>
#include <ranges>

#define INPUT_NOT_REPEATED(x)      if (x->IsRepeating()) return
#define INPUT_KEY_NOT_MODIFIED(x)  if (x->IsKeyModified()) return
#define INPUT_KEY_MODIFIED(x, ...) if (!x->IsKeyModified({__VA_ARGS__})) return
#define INPUT_REPEAT_AFTER(x, ms)  if (!x->CanRepeatAfter(ms)) return
#define INPUT_REPEAT_EVERY(x, ms)  if (!x->CanRepeatEvery(ms)) return

static constexpr inline auto enum_range = [](auto front, auto back)
	{
		return std::views::iota(std::to_underlying(front), std::to_underlying(back) + 1)
			| std::views::transform([](auto e)
				{
					return decltype( front )( e );
				});
	};

namespace Input
{
enum class Button
{
	NONE,
	FACE_DOWN,
	FACE_LEFT,
	FACE_UP,
	FACE_RIGHT,
	DPAD_UP,
	DPAD_DOWN,
	DPAD_LEFT,
	DPAD_RIGHT,
	START,
	SELECT,
	R1,
	//R2, this is an axis
	R3,
	L1,
	//L2, this is an axis
	L3,
	MISC,
	_END,
};

enum class Key
{
	NONE = std::to_underlying(Button::_END) + 1,
	// FUNCTION KEYS
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
	// NORMAL KEYS
	K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	// GENERAL KEYS
	CAPSLOCK, SPACE, TAB, ENTER, ESCAPE, BACK,
	// MODIFIERS
	LWIN, RWIN, LCTRL, RCTRL, LALT, RALT, LSHIFT, RSHIFT,
	// CURSOR CONTROL
	SCROLLLOCK, DELETE, INSERT, HOME, END, PAGEUP, PAGEDOWN, UP, DOWN, LEFT, RIGHT,
	// NUMPAD
	NUMLOCK, NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9,
	NPADD, NPSUB, NPDIV, NPMUL, NPENTER, NPPERIOD,
	// some headache keys
	PAUSE,

	OEM_1, OEM_2, OEM_3, OEM_4, OEM_5, OEM_6, OEM_7, OEM_10,
	OEM_PLUS, OEM_MINUS, OEM_PERIOD, OEM_COMMA,
	_END,
};

enum class MouseButton
{
	NONE = std::to_underlying(Key::_END) + 1,
	LEFT,
	MIDDLE,
	RIGHT,
	AUX_1,
	AUX_2,
	_END,
};

inline constexpr auto USE_MOUSE      = 0x01;
inline constexpr auto USE_CONTROLLER = 0x02;
inline constexpr auto USE_KEYBOARD   = 0x04;

const char* GetButtonName(Button b);
const char* GetKeyName(Key k);
const char* GetMouseButtonName(MouseButton m);
const char* GetName(size_t pos);

std::string GetButtonRepr(Button b);
std::string GetKeyRepr(Key k);
std::string GetMouseButtonRepr(MouseButton m);
std::string GetRepr(size_t pos);

size_t GetOffset(Button b);
size_t GetOffset(MouseButton b);
size_t GetOffset(Key b);

using ms_t = std::chrono::milliseconds;

class IInput
{
public:

	virtual ~IInput() = default;
	// get state of input devices
		// working nice in sdl
		// half baked in windows since gamepad requires xinput and I'm lazy
	virtual bool GetButton(Button b) const = 0;
	virtual bool GetMouseButton(MouseButton b) const = 0;
	virtual bool GetKey(Key k) const = 0;
	virtual bool IsDown(size_t pos) const;

	virtual float GetMouseX() const = 0;
	virtual float GetMouseY() const = 0;

	// send input
	virtual void SendButton(Button b) = 0;
	virtual void SendMouseButton(MouseButton m) = 0;
	virtual void SendKey(Key k) = 0;

	virtual void ReleaseButton(Button b) = 0;
	virtual void ReleaseMouseButton(MouseButton m) = 0;
	virtual void ReleaseKey(Key k) = 0;

	// an empty mod list will test all modifiers
	bool IsKeyModified(std::initializer_list<Key> modifiers={}) const;

	bool IsRepeating() const;
	bool IsKeyRepeating(Key k) const;
	bool IsButtonRepeating(Button b) const;
	bool IsMouseRepeating(MouseButton b) const;

	bool CanRepeatAfter(ms_t ms) const;
	bool CanRepeatKeyAfter(Key k, ms_t ms) const;
	bool CanRepeatButtonAfter(Button b, ms_t ms) const;
	bool CanRepeatMouseButtonAfter(MouseButton b, ms_t ms) const;

	bool CanRepeatEvery(ms_t ms);
	bool CanRepeatKeyEvery(Key k, ms_t ms);
	bool CanRepeatButtonEvery(Button b, ms_t ms);
	bool CanRepeatMouseButtonEvery(MouseButton b, ms_t ms);
	bool CanRepeatUnmappedEvery(ms_t ms);

	void ClearActions(Button button);
	void ClearActions(Key key);
	void ClearActions(MouseButton button);
	void ClearUnmappedActions();
	void ClearActions();

	void AddGamepadAction(Button b, const std::function<void(IInput*)>& action);
	void AddKeyboardAction(Key b, const std::function<void(IInput*)>& action);
	void AddMouseAction(MouseButton b, const std::function<void(IInput*)>& action);
	void AddAction(size_t pos, const std::function<void(IInput*)>& action);
	void AddUnmappedAction(const std::function<void(IInput*)>& action);

	void RunGamepadActions(Button b);
	void RunKeyboardActions(Key b);
	void RunMouseActions(MouseButton b);
	void RunUnmappedActions();

	void RunActions();
	void Update();

	virtual void ProcessEvents(void* event)
	{
	}

protected:
	virtual void platform_override() = 0;


private:
	void update_keyboard_state();
	void update_gamepad_state();
	void update_mouse_state();

	bool can_repeat_every_impl(size_t pos, ms_t ms);
	bool can_repeat_after_impl(size_t pos, ms_t ms) const;


protected:
	std::unordered_map<size_t, std::chrono::time_point<std::chrono::steady_clock>> m_active;
	// can't be a vector, has gaps
	std::unordered_map<size_t, size_t> m_time_repetitions;

	std::unordered_map<Button, std::deque<std::function<void(IInput*)>>> m_button_actions;
	std::unordered_map<MouseButton, std::deque<std::function<void(IInput*)>>> m_mouse_actions;
	std::unordered_map<Key, std::deque<std::function<void(IInput*)>>> m_key_actions;
	std::deque<std::function<void(IInput*)>> m_unmapped_actions;


	size_t m_current_action{ 0 };
	Button m_current_button{ 0 };
	MouseButton m_current_mouse_button{ 0 };
	bool m_unmapped{ false };
	bool m_has_unmapped{ false };

	Key m_current_key{ 0 };



};
}
#endif