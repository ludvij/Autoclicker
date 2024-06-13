#include "Input.hpp"

#include <ranges>

using time_clk = std::chrono::steady_clock;

namespace Input
{

static constexpr auto begin_input = std::to_underlying(Button::NONE);
static constexpr auto end_input   = std::to_underlying(MouseButton::AUX_2);

const char* GetButtonName(Button b)
{
	switch (b)
	{
	case Input::Button::FACE_DOWN:  return "FACE_DOWN";
	case Input::Button::FACE_LEFT:  return "FACE_LEFT";
	case Input::Button::FACE_UP:    return "FACE_UP";
	case Input::Button::FACE_RIGHT: return "FACE_RIGHT";
	case Input::Button::DPAD_UP:    return "DPAD_UP";
	case Input::Button::DPAD_DOWN:  return "DPAD_DOWN";
	case Input::Button::DPAD_LEFT:  return "DPAD_LEFT";
	case Input::Button::DPAD_RIGHT: return "DPAD_RIGHT";
	case Input::Button::START:      return "START";
	case Input::Button::SELECT:     return "SELECT";
	case Input::Button::R1:         return "R1";
	case Input::Button::R3:         return "R3";
	case Input::Button::L1:         return "L1";
	case Input::Button::L3:         return "L3";
	case Input::Button::MISC:       return "MISC";
	default:                        return "INVALID";
	}
}

const char* GetKeyName(Key k)
{
	switch (k)
	{
	case Input::Key::NONE:           return "NONE";
	case Input::Key::F1:             return "F1";
	case Input::Key::F2:             return "F2";
	case Input::Key::F3:             return "F3";
	case Input::Key::F4:             return "F4";
	case Input::Key::F5:             return "F5";
	case Input::Key::F6:             return "F6";
	case Input::Key::F7:             return "F7";
	case Input::Key::F8:             return "F8";
	case Input::Key::F9:             return "F9";
	case Input::Key::F10:            return "F10";
	case Input::Key::F11:            return "F11";
	case Input::Key::F12:            return "F12";
	case Input::Key::F13:            return "F13";
	case Input::Key::F14:            return "F14";
	case Input::Key::F15:            return "F15";
	case Input::Key::F16:            return "F16";
	case Input::Key::F17:            return "F17";
	case Input::Key::F18:            return "F18";
	case Input::Key::F19:            return "F19";
	case Input::Key::F20:            return "F20";
	case Input::Key::F21:            return "F21";
	case Input::Key::F22:            return "F22";
	case Input::Key::F23:            return "F23";
	case Input::Key::F24:            return "F24";
	case Input::Key::K0:             return "0";
	case Input::Key::K1:             return "1";
	case Input::Key::K2:             return "2";
	case Input::Key::K3:             return "3";
	case Input::Key::K4:             return "4";
	case Input::Key::K5:             return "5";
	case Input::Key::K6:             return "6";
	case Input::Key::K7:             return "7";
	case Input::Key::K8:             return "8";
	case Input::Key::K9:             return "9";
	case Input::Key::A:              return "A";
	case Input::Key::B:              return "B";
	case Input::Key::C:              return "C";
	case Input::Key::D:              return "D";
	case Input::Key::E:              return "E";
	case Input::Key::F:              return "F";
	case Input::Key::G:              return "G";
	case Input::Key::H:              return "H";
	case Input::Key::I:              return "I";
	case Input::Key::J:              return "J";
	case Input::Key::K:              return "K";
	case Input::Key::L:              return "L";
	case Input::Key::M:              return "M";
	case Input::Key::N:              return "N";
	case Input::Key::O:              return "O";
	case Input::Key::P:              return "P";
	case Input::Key::Q:              return "Q";
	case Input::Key::R:              return "R";
	case Input::Key::S:              return "S";
	case Input::Key::T:              return "T";
	case Input::Key::U:              return "U";
	case Input::Key::V:              return "V";
	case Input::Key::W:              return "W";
	case Input::Key::X:              return "X";
	case Input::Key::Y:              return "Y";
	case Input::Key::Z:              return "Z";
	case Input::Key::CAPSLOCK:       return "CAPSLOCK";
	case Input::Key::SPACE:          return "SPACE";
	case Input::Key::TAB:            return "TAB";
	case Input::Key::ENTER:          return "ENTER";
	case Input::Key::ESCAPE:         return "ESCAPE";
	case Input::Key::BACK:           return "BACK";
	case Input::Key::LWIN:           return "LWIN";
	case Input::Key::RWIN:           return "RWIN";
	case Input::Key::LCTRL:          return "LCTRL";
	case Input::Key::RCTRL:          return "RCTRL";
	case Input::Key::LALT:           return "LALT";
	case Input::Key::RALT:           return "RALT";
	case Input::Key::LSHIFT:         return "LSHIFT";
	case Input::Key::RSHIFT:         return "RSHIFT";
	case Input::Key::SCROLLLOCK:     return "SCROLLLOCK";
	case Input::Key::DELETE:         return "DELETE";
	case Input::Key::INSERT:         return "INSERT";
	case Input::Key::HOME:           return "HOME";
	case Input::Key::END:            return "END";
	case Input::Key::PAGEUP:         return "PAGEUP";
	case Input::Key::PAGEDOWN:       return "PAGEDOWN";
	case Input::Key::UP:             return "UP";
	case Input::Key::DOWN:           return "DOWN";
	case Input::Key::LEFT:           return "LEFT";
	case Input::Key::RIGHT:          return "RIGHT";
	case Input::Key::NUMLOCK:        return "NUMLOCK";
	case Input::Key::NP0:            return "NP_0";
	case Input::Key::NP1:            return "NP_1";
	case Input::Key::NP2:            return "NP_2";
	case Input::Key::NP3:            return "NP_3";
	case Input::Key::NP4:            return "NP_4";
	case Input::Key::NP5:            return "NP_5";
	case Input::Key::NP6:            return "NP_6";
	case Input::Key::NP7:            return "NP_7";
	case Input::Key::NP8:            return "NP_8";
	case Input::Key::NP9:            return "NP_9";
	case Input::Key::NPADD:          return "NP_ADD";
	case Input::Key::NPSUB:          return "NP_SUB";
	case Input::Key::NPDIV:          return "NP_DIV";
	case Input::Key::NPMUL:          return "NP_MUL";
	case Input::Key::NPENTER:        return "NP_ENTER";
	case Input::Key::NPPERIOD:       return "NP_PERIOD";
	case Input::Key::OEM_1:          return "OEM_1";
	case Input::Key::OEM_2:          return "OEM_2";
	case Input::Key::OEM_3:          return "OEM_3";
	case Input::Key::OEM_4:          return "OEM_4";
	case Input::Key::OEM_5:          return "OEM_5";
	case Input::Key::OEM_6:          return "OEM_6";
	case Input::Key::OEM_7:          return "OEM_7";
	case Input::Key::OEM_10:         return "OEM_10";
	case Input::Key::OEM_MINUS:      return "OEM_MINUS";
	case Input::Key::OEM_PLUS:       return "OEM_EPLUS";
	case Input::Key::OEM_COMMA:      return "OEM_COMMA";
	case Input::Key::OEM_PERIOD:     return "OEM_PERIOD";
	default:                         return "INVALID";
	}
}




bool IInput::IsKeyModified(std::initializer_list<Key> modifiers/*={}*/) const
{
	if (modifiers.size() == 0)
	{
		for (const auto mod : enum_range(Key::LWIN, Key::RSHIFT))
		{
			if (GetKey(mod)) return true;
		}
	}
	else
	{
		for (const auto mod : modifiers)
		{
			if (GetKey(mod)) return true;
		}
	}
	return false;
}

bool IInput::IsRepeating() const
{
	return
		IsKeyRepeating(m_current_key) ||
		IsButtonRepeating(m_current_button) ||
		IsMouseRepeating(m_current_mouse_button);
}
bool IInput::IsKeyRepeating(Key k) const
{
	const size_t pos = std::to_underlying(k);
	return m_active.contains(pos);
}
bool IInput::IsButtonRepeating(Button b) const
{
	const size_t pos = std::to_underlying(b);
	return m_active.contains(pos);
}
bool IInput::IsMouseRepeating(MouseButton b) const
{
	const size_t pos = std::to_underlying(b);
	return m_active.contains(pos);
}
bool IInput::CanRepeatAfter(const ms_t ms) const
{
	if (m_current_button != Button::NONE)
	{
		return CanRepeatButtonAfter(m_current_button, ms);
	}
	else if (m_current_key != Key::NONE)
	{
		return CanRepeatKeyAfter(m_current_key, ms);
	}
	else if (m_current_mouse_button != MouseButton::NONE)
	{
		return CanRepeatMouseButtonAfter(m_current_mouse_button, ms);
	}
	return true;
}
bool IInput::CanRepeatKeyAfter(Key k, const ms_t ms) const
{
	const size_t pos = std::to_underlying(k);
	return can_repeat_after_impl(pos, ms);
}
bool IInput::CanRepeatButtonAfter(Button b, const ms_t ms) const
{
	const size_t pos = std::to_underlying(b);
	return can_repeat_after_impl(pos, ms);
}
bool IInput::CanRepeatMouseButtonAfter(MouseButton b, ms_t ms) const
{
	const size_t pos = std::to_underlying(b);
	return can_repeat_after_impl(pos, ms);
}
bool IInput::CanRepeatEvery(ms_t ms)
{
	if (m_current_button != Button::NONE)
	{
		return CanRepeatButtonEvery(m_current_button, ms);
	}
	else if (m_current_key != Key::NONE)
	{
		return CanRepeatKeyEvery(m_current_key, ms);
	}
	else if (m_current_mouse_button != MouseButton::NONE)
	{
		return CanRepeatMouseButtonEvery(m_current_mouse_button, ms);
	}
	else if (m_unmapped == true)
	{
		return CanRepeatUnmappedEvery(ms);
	}
	return true;
}
bool IInput::CanRepeatKeyEvery(Key k, ms_t ms)
{
	const size_t pos = std::to_underlying(k);
	return can_repeat_every_impl(pos, ms);
}
bool IInput::CanRepeatButtonEvery(Button b, ms_t ms)
{
	const size_t pos = std::to_underlying(b);
	return can_repeat_every_impl(pos, ms);
}
bool IInput::CanRepeatMouseButtonEvery(MouseButton b, ms_t ms)
{
	const size_t pos = std::to_underlying(b);
	return can_repeat_every_impl(pos, ms);
}
bool IInput::CanRepeatUnmappedEvery(ms_t ms)
{
	const size_t pos = static_cast<size_t>( end_input + 1 );
	return can_repeat_every_impl(pos, ms);
}
void IInput::ClearActions(Button button)
{
	m_button_actions.at(button).clear();
}

void IInput::ClearActions(Key key)
{
	m_key_actions.at(key).clear();
}

void IInput::ClearActions(MouseButton mouse_button)
{
	m_mouse_actions.at(mouse_button).clear();
}

void IInput::ClearUnmappedActions()
{
	m_unmapped_actions.clear();
	m_has_unmapped = false;
	m_active.erase(static_cast<size_t>( end_input + 1 ));
}

void IInput::ClearActions()
{
	m_button_actions.clear();
	m_key_actions.clear();
	m_mouse_actions.clear();

	ClearUnmappedActions();
}

void IInput::AddGamepadAction(Button b, const std::function<void(IInput*)>& action)
{
	m_button_actions[b].push_back(action);
	m_time_repetitions.clear();
}

void IInput::AddKeyboardAction(Key b, const std::function<void(IInput*)>& action)
{
	m_key_actions[b].push_back(action);
	m_time_repetitions.clear();
}

void IInput::AddMouseAction(MouseButton b, const std::function<void(IInput*)>& action)
{
	m_mouse_actions[b].push_back(action);
	m_time_repetitions.clear();
}

void IInput::AddUnmappedAction(const std::function<void(IInput*)>& action)
{
	m_unmapped_actions.push_back(action);
	if (m_has_unmapped == false)
	{
		m_active.insert({ end_input + 1, time_clk::now() });
	}
	m_has_unmapped = true;
}

void IInput::RunGamepadActions(Button b)
{
	if (!GetButton(b))
	{
		return;
	}
	m_current_button = b;
	for (const auto& action : m_button_actions[b])
	{
		action(this);
		m_current_action++;
	}
	m_current_button = Button::NONE;
}

void IInput::RunKeyboardActions(Key k)
{
	if (!GetKey(k))
	{
		return;
	}
	m_current_key = k;
	for (const auto& action : m_key_actions[k])
	{
		action(this);
		m_current_action++;
	}
	m_current_key = Key::NONE;

}

void IInput::RunMouseActions(MouseButton b)
{
	if (!GetMouseButton(b))
	{
		return;
	}
	m_current_mouse_button = b;
	for (const auto& action : m_mouse_actions[b])
	{
		action(this);
		m_current_action++;
	}
	m_current_mouse_button = MouseButton::NONE;
}

void IInput::RunUnmappedActions()
{
	m_unmapped = true;
	for (const auto& k : m_unmapped_actions)
	{
		k(this);
	}
	m_unmapped = false;
}

void IInput::RunActions()
{
	m_current_action = 0;
	for (const auto& [k, v] : m_button_actions)
	{
		RunGamepadActions(k);
	}
	for (const auto& [k, v] : m_key_actions)
	{
		RunKeyboardActions(k);
	}
	for (const auto& [k, v] : m_mouse_actions)
	{
		RunMouseActions(k);
	}
	RunUnmappedActions();
}

void IInput::Update()
{
	platform_override();

	RunActions();
	update_gamepad_state();
	update_keyboard_state();
	update_mouse_state();
}

void IInput::update_keyboard_state()
{
	for (const auto key : enum_range(Key::F1, Key::OEM_COMMA))
	{
		const size_t pos = std::to_underlying(key);
		if (GetKey(key) && !m_active.contains(pos))
		{
			m_active.insert({ pos, time_clk::now() });
		}
		if (!GetKey(key) && m_active.contains(pos))
		{
			m_active.erase(pos);
		}
	}
}

void IInput::update_gamepad_state()
{
	for (const auto button : enum_range(Button::FACE_DOWN, Button::MISC))
	{
		const size_t pos = std::to_underlying(button);
		if (GetButton(button) && !m_active.contains(pos))
		{
			m_active.insert({ pos, time_clk::now() });
		}
		if (!GetButton(button) && m_active.contains(pos))
		{
			m_active.erase(pos);
		}
	}
}
void IInput::update_mouse_state()
{
	for (const auto button : enum_range(MouseButton::LEFT, MouseButton::AUX_2))
	{
		const size_t pos = std::to_underlying(button);
		if (GetMouseButton(button) && !m_active.contains(pos))
		{
			m_active.insert({ pos, time_clk::now() });
		}
		if (!GetMouseButton(button) && m_active.contains(pos))
		{
			m_active.erase(pos);
		}
	}
}
bool IInput::can_repeat_every_impl(size_t pos, ms_t ms)
{
	if (m_active.contains(pos))
	{
		if (!m_time_repetitions.contains(m_current_action))
		{
			m_time_repetitions.insert({ m_current_action, 0 });
		}
		auto reps = m_time_repetitions.at(m_current_action);
		const auto now = time_clk::now();
		const auto diff = std::chrono::duration_cast<ms_t>( now - m_active.at(pos) );
		const size_t actual_diffs = diff / ms;
		if (actual_diffs != reps)
		{
			m_time_repetitions[m_current_action] = actual_diffs;
			return true;
		}
		return false;
	}
	return true;
}
bool IInput::can_repeat_after_impl(size_t pos, ms_t ms) const
{
	if (m_active.contains(pos))
	{
		const auto now = time_clk::now();
		const auto diff = std::chrono::duration_cast<ms_t>( now - m_active.at(pos) );
		return ms < diff;
	}
	return true;
}
}