#include "win32/Win32Input.hpp"


// does not work, :(
static int get_windows_button_equivalent(Input::Button b)
{
	typedef Input::Button B;
	switch (b)
	{
	case B::NONE:	    return 0;
	case B::FACE_DOWN:  return VK_GAMEPAD_A;
	case B::FACE_LEFT:  return VK_GAMEPAD_X;
	case B::FACE_UP:    return VK_GAMEPAD_Y;
	case B::FACE_RIGHT: return VK_GAMEPAD_B;
	case B::DPAD_UP:    return VK_GAMEPAD_DPAD_UP;
	case B::DPAD_DOWN:  return VK_GAMEPAD_DPAD_DOWN;
	case B::DPAD_LEFT:  return VK_GAMEPAD_DPAD_LEFT;
	case B::DPAD_RIGHT: return VK_GAMEPAD_DPAD_RIGHT;
	case B::START:	    return 0;
	case B::SELECT:	    return 0;
	case B::R1:		    return VK_GAMEPAD_RIGHT_SHOULDER;
	case B::R3:		    return VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON;
	case B::L1:		    return VK_GAMEPAD_LEFT_SHOULDER;
	case B::L3:		    return VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON;
	case B::MISC:       return VK_GAMEPAD_MENU;
	default:            return get_windows_button_equivalent(B::NONE);
	}
}

static int get_windows_mouse_button_equivalent(Input::MouseButton m)
{
	typedef Input::MouseButton M;
	switch (m)
	{
	case M::NONE:		 return 0;
	case M::LEFT:		 return VK_LBUTTON;
	case M::MIDDLE:		 return VK_MBUTTON;
	case M::RIGHT:		 return VK_RBUTTON;
	case M::AUX_1:		 return VK_XBUTTON1;
	case M::AUX_2:		 return VK_XBUTTON2;
	default:             return get_windows_mouse_button_equivalent(M::NONE);
	}
}

static int get_windows_key_equivalent(Input::Key k)
{
	typedef Input::Key K;
	switch (k)
	{
	case K::NONE:       return 0;
	case K::F1:         return VK_F1;
	case K::F2:         return VK_F2;
	case K::F3:         return VK_F3;
	case K::F4:         return VK_F4;
	case K::F5:         return VK_F5;
	case K::F6:         return VK_F6;
	case K::F7:         return VK_F7;
	case K::F8:         return VK_F8;
	case K::F9:         return VK_F9;
	case K::F10:        return VK_F10;
	case K::F11:        return VK_F11;
	case K::F12:        return VK_F12;
	case K::F13:        return VK_F13;
	case K::F14:        return VK_F14;
	case K::F15:        return VK_F15;
	case K::F16:        return VK_F16;
	case K::F17:        return VK_F17;
	case K::F18:        return VK_F18;
	case K::F19:        return VK_F19;
	case K::F20:        return VK_F20;
	case K::F21:        return VK_F21;
	case K::F22:        return VK_F22;
	case K::F23:        return VK_F23;
	case K::F24:        return VK_F24;
	case K::K0:         return '0';
	case K::K1:         return '1';
	case K::K2:         return '2';
	case K::K3:         return '3';
	case K::K4:         return '4';
	case K::K5:         return '5';
	case K::K6:         return '6';
	case K::K7:         return '7';
	case K::K8:         return '8';
	case K::K9:         return '9';
	case K::A:          return 'A';
	case K::B:          return 'B';
	case K::C:          return 'C';
	case K::D:          return 'D';
	case K::E:          return 'E';
	case K::F:          return 'F';
	case K::G:          return 'G';
	case K::H:          return 'H';
	case K::I:          return 'I';
	case K::J:          return 'J';
	case K::K:          return 'K';
	case K::L:          return 'L';
	case K::M:          return 'M';
	case K::N:          return 'N';
	case K::O:          return 'O';
	case K::P:          return 'P';
	case K::Q:          return 'Q';
	case K::R:          return 'R';
	case K::S:          return 'S';
	case K::T:          return 'T';
	case K::U:          return 'U';
	case K::V:          return 'V';
	case K::W:          return 'W';
	case K::X:          return 'X';
	case K::Y:          return 'Y';
	case K::Z:          return 'Z';
	case K::CAPSLOCK:   return VK_CAPITAL;
	case K::SPACE:      return VK_SPACE;
	case K::TAB:        return VK_TAB;
	case K::ENTER:      return VK_RETURN;
	case K::ESCAPE:     return VK_ESCAPE;
	case K::BACK:       return VK_BACK;
	case K::LWIN:       return VK_LWIN;
	case K::RWIN:       return VK_RWIN;
	case K::LCTRL:      return VK_LCONTROL;
	case K::RCTRL:      return VK_RCONTROL;
	case K::LALT:       return VK_LMENU;
	case K::RALT:       return VK_RMENU;
	case K::LSHIFT:     return VK_LSHIFT;
	case K::RSHIFT:     return VK_RSHIFT;
	case K::SCROLLLOCK: return VK_SCROLL;
	#ifdef DELETE
	#undef DELETE
	case K::DELETE:     return VK_DELETE;
	#define DELETE  (0x00010000L)
	#else
	case K::DELETE:     return VK_DELETE;
	#endif
	case K::INSERT:     return VK_INSERT;
	case K::HOME:       return VK_HOME;
	case K::END:        return VK_END;
	case K::PAGEUP:     return VK_NEXT;
	case K::PAGEDOWN:   return VK_PRIOR;
	case K::UP:         return VK_UP;
	case K::DOWN:       return VK_DOWN;
	case K::LEFT:       return VK_LEFT;
	case K::RIGHT:      return VK_RIGHT;
	case K::NUMLOCK:    return VK_NUMLOCK;
	case K::NP0:        return VK_NUMPAD0;
	case K::NP1:        return VK_NUMPAD1;
	case K::NP2:        return VK_NUMPAD2;
	case K::NP3:        return VK_NUMPAD3;
	case K::NP4:        return VK_NUMPAD4;
	case K::NP5:        return VK_NUMPAD5;
	case K::NP6:        return VK_NUMPAD6;
	case K::NP7:        return VK_NUMPAD7;
	case K::NP8:        return VK_NUMPAD8;
	case K::NP9:        return VK_NUMPAD9;
	case K::NPADD:      return VK_ADD;
	case K::NPSUB:      return VK_SUBTRACT;
	case K::NPDIV:      return VK_DIVIDE;
	case K::NPMUL:      return VK_MULTIPLY;
	case K::NPENTER:    return VK_RETURN;
	case K::NPPERIOD:   return VK_DECIMAL;
	case K::OEM_1:      return VK_OEM_1;
	case K::OEM_2:      return VK_OEM_2;
	case K::OEM_3:      return VK_OEM_3;
	case K::OEM_4:      return VK_OEM_4;
	case K::OEM_5:      return VK_OEM_5;
	case K::OEM_6:      return VK_OEM_6;
	case K::OEM_7:      return VK_OEM_7;
	case K::OEM_10:     return VK_OEM_102;
	case K::OEM_PLUS:   return VK_OEM_PLUS;
	case K::OEM_MINUS:  return VK_OEM_MINUS;
	case K::OEM_PERIOD: return VK_OEM_PERIOD;
	case K::OEM_COMMA:  return VK_OEM_COMMA;
	default:            return get_windows_key_equivalent(K::NONE);
	}
}

Input::WindowsInput::WindowsInput()
{
}

Input::WindowsInput::~WindowsInput()
{
}

bool Input::WindowsInput::GetButton(Button b) const
{
	return false;
}

bool Input::WindowsInput::GetKey(Key k) const
{
	return m_key_state[get_windows_key_equivalent(k)];
}


void Input::WindowsInput::platform_override()
{
	// get mouse pos
	if (GetCursorPos(&m_mouse_pos) == 0)
	{
		throw std::runtime_error("Could not get mouse position");
	}
	// get keys
	for (size_t i = 0; i < 256; i++)
	{
		m_key_state[i] = ( GetAsyncKeyState((int)i) & 0x8000 ) == 0x8000;
	}
}

void Input::WindowsInput::SendButton(Button b)
{
}

void Input::WindowsInput::SendMouseButton(MouseButton m)
{
	auto equiv = get_windows_mouse_button_equivalent(m);
	INPUT in;
	in.type = INPUT_MOUSE;
	in.mi.dx = 0;
	in.mi.dy = 0;
	in.mi.time = 0;
	in.mi.mouseData = 0;
	in.mi.dwExtraInfo = 0;
	switch (equiv)
	{
	case VK_XBUTTON1:
	{
		in.mi.dwFlags = MOUSEEVENTF_XDOWN;
		in.mi.mouseData = XBUTTON1;
		break;
	}
	case VK_XBUTTON2:
	{
		in.mi.dwFlags = MOUSEEVENTF_XDOWN;
		in.mi.mouseData = XBUTTON2;
		break;
	}
	case VK_LBUTTON: in.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;   break;
	case VK_RBUTTON: in.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;  break;
	case VK_MBUTTON: in.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN; break;
	default: return;
	}
	SendInput(1, &in, sizeof in);
}

void Input::WindowsInput::SendKey(Key k)
{
	auto equiv = get_windows_key_equivalent(k);
	//auto scan = MapVirtualKeyA(equiv, MAPVK_VK_TO_VSC);
	INPUT in;
	in.type = INPUT_KEYBOARD;
	in.ki.wVk = equiv;
	in.ki.wScan = 0;
	in.ki.time = 0;
	in.ki.dwExtraInfo = 0;
	in.ki.dwFlags = 0;

	SendInput(1, &in, sizeof in);

}

void Input::WindowsInput::ReleaseButton(Button b)
{
}

void Input::WindowsInput::ReleaseMouseButton(MouseButton m)
{
	auto equiv = get_windows_mouse_button_equivalent(m);
	INPUT in;
	in.type = INPUT_MOUSE;
	in.mi.dx = 0;
	in.mi.dy = 0;
	in.mi.time = 0;
	in.mi.mouseData = 0;
	in.mi.dwExtraInfo = 0;
	switch (equiv)
	{
	case VK_XBUTTON1:
	{
		in.mi.dwFlags = MOUSEEVENTF_XUP;
		in.mi.mouseData = XBUTTON1;
		break;
	}
	case VK_XBUTTON2:
	{
		in.mi.dwFlags = MOUSEEVENTF_XUP;
		in.mi.mouseData = XBUTTON2;
		break;
	}
	case VK_LBUTTON: in.mi.dwFlags = MOUSEEVENTF_LEFTUP;   break;
	case VK_RBUTTON: in.mi.dwFlags = MOUSEEVENTF_RIGHTUP;  break;
	case VK_MBUTTON: in.mi.dwFlags = MOUSEEVENTF_MIDDLEUP; break;
	default: return;
	}
	SendInput(1, &in, sizeof in);
}

void Input::WindowsInput::ReleaseKey(Key k)
{
}

bool Input::WindowsInput::GetMouseButton(MouseButton b) const
{
	return m_key_state[get_windows_mouse_button_equivalent(b)];
}


float Input::WindowsInput::GetMouseX() const
{
	return static_cast<float>( m_mouse_pos.x );
}

float Input::WindowsInput::GetMouseY() const
{
	return static_cast<float>( m_mouse_pos.y );
}


std::string Input::GetButtonRepr(Input::Button b)
{
	return GetButtonName(b);
}
std::string Input::GetKeyRepr(Input::Key k)
{
	char buf[32];
	auto vk = get_windows_key_equivalent(k);
	auto scan = MapVirtualKeyA(vk, MAPVK_VK_TO_VSC);
	GetKeyNameTextA(scan << 16, buf, 32);

	return std::string(buf);
}
std::string Input::GetMouseButtonRepr(Input::MouseButton m)
{
	return GetMouseButtonName(m);

}
