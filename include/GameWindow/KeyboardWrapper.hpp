#pragma once

#include "Event.hpp"
#include "WindowWrapper.hpp"
#include "GLFW/glfw3.h"
#include <cassert>
#include <iostream>

namespace doo
{
	enum class KeyCode : int
	{
		Space = GLFW_KEY_SPACE,
		Apostrophe = GLFW_KEY_APOSTROPHE,
		Comma = GLFW_KEY_COMMA,
		Minus = GLFW_KEY_MINUS,
		Period = GLFW_KEY_PERIOD,
		Slash = GLFW_KEY_SLASH,
		_0 = GLFW_KEY_0,
		_1 = GLFW_KEY_1,
		_2 = GLFW_KEY_2,
		_8 = GLFW_KEY_8,
		_3 = GLFW_KEY_3,
		_4 = GLFW_KEY_4,
		_5 = GLFW_KEY_5,
		_6 = GLFW_KEY_6,
		_7 = GLFW_KEY_7,
		_9 = GLFW_KEY_9,
		Semicolon = GLFW_KEY_SEMICOLON,
		Equal = GLFW_KEY_EQUAL,
		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		Q = GLFW_KEY_Q,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		V = GLFW_KEY_V,
		W = GLFW_KEY_W,
		X = GLFW_KEY_X,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,
		LeftBracket = GLFW_KEY_LEFT_BRACKET,
		Backslash = GLFW_KEY_BACKSLASH,
		RightBracket = GLFW_KEY_RIGHT_BRACKET,
		GraveAccent = GLFW_KEY_GRAVE_ACCENT,
		World_1 = GLFW_KEY_WORLD_1,
		World_2 = GLFW_KEY_WORLD_2,
		Escape = GLFW_KEY_ESCAPE,
		Enter = GLFW_KEY_ENTER,
		Tab = GLFW_KEY_TAB,
		Backspace = GLFW_KEY_BACKSPACE,
		Insert = GLFW_KEY_INSERT,
		Delete = GLFW_KEY_DELETE,
		Right = GLFW_KEY_RIGHT,
		Left = GLFW_KEY_LEFT,
		Down = GLFW_KEY_DOWN,
		Up = GLFW_KEY_UP,
		PageUp = GLFW_KEY_PAGE_UP,
		PageDown = GLFW_KEY_PAGE_DOWN,
		Home = GLFW_KEY_HOME,
		End = GLFW_KEY_END,
		CapsLock = GLFW_KEY_CAPS_LOCK,
		ScrollLock = GLFW_KEY_SCROLL_LOCK,
		NumLock = GLFW_KEY_NUM_LOCK,
		PrintScreen = GLFW_KEY_PRINT_SCREEN,
		Pause = GLFW_KEY_PAUSE,
		F1 = GLFW_KEY_F1,
		F2 = GLFW_KEY_F2,
		F3 = GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12,
		F13 = GLFW_KEY_F13,
		F14 = GLFW_KEY_F14,
		F15 = GLFW_KEY_F15,
		F16 = GLFW_KEY_F16,
		F17 = GLFW_KEY_F17,
		F18 = GLFW_KEY_F18,
		F19 = GLFW_KEY_F19,
		F20 = GLFW_KEY_F20,
		F21 = GLFW_KEY_F21,
		F22 = GLFW_KEY_F22,
		F23 = GLFW_KEY_F23,
		F24 = GLFW_KEY_F24,
		F25 = GLFW_KEY_F25,
		Kp_0 = GLFW_KEY_KP_0,
		Kp_1 = GLFW_KEY_KP_1,
		Kp_2 = GLFW_KEY_KP_2,
		Kp_3 = GLFW_KEY_KP_3,
		Kp_4 = GLFW_KEY_KP_4,
		Kp_5 = GLFW_KEY_KP_5,
		Kp_6 = GLFW_KEY_KP_6,
		Kp_7 = GLFW_KEY_KP_7,
		Kp_8 = GLFW_KEY_KP_8,
		Kp_9 = GLFW_KEY_KP_9,
		Kp_Decimal = GLFW_KEY_KP_DECIMAL,
		Kp_Divide = GLFW_KEY_KP_DIVIDE,
		Kp_Multiply = GLFW_KEY_KP_MULTIPLY,
		Kp_Subtract = GLFW_KEY_KP_SUBTRACT,
		Kp_Add = GLFW_KEY_KP_ADD,
		Kp_Enter = GLFW_KEY_KP_ENTER,
		Kp_Equal = GLFW_KEY_KP_EQUAL,
		LeftShift = GLFW_KEY_LEFT_SHIFT,
		LeftControl = GLFW_KEY_LEFT_CONTROL,
		LeftAlt = GLFW_KEY_LEFT_ALT,
		LeftSuper = GLFW_KEY_LEFT_SUPER,
		RightShift = GLFW_KEY_RIGHT_SHIFT,
		RightControl = GLFW_KEY_RIGHT_CONTROL,
		RightAlt = GLFW_KEY_RIGHT_ALT,
		RightSuper = GLFW_KEY_RIGHT_SUPER,
		Menu = GLFW_KEY_MENU,
		Unkown = GLFW_KEY_UNKNOWN
	};

	enum class Modifier : int
	{
		Shift = GLFW_MOD_SHIFT,
		Control = GLFW_MOD_CONTROL,
		Alt = GLFW_MOD_ALT,
		Super = GLFW_MOD_SUPER,
		None = -1
	};

	struct InputEventArgs
	{
		explicit InputEventArgs(int p_mods) : m_mods(p_mods)
		{
		}

		bool IsModifierDown(Modifier p_mod) const
		{
			int modKey = static_cast<int>(p_mod);
			return m_mods & modKey;
		}

	private:
		int m_mods;
	};

	struct KeyboardInputEventArgs : InputEventArgs
	{
		KeyboardInputEventArgs(KeyCode p_key, int p_scancode, int p_mods)
			: InputEventArgs(p_mods),
			  Key(p_key),
			  Scancode(p_scancode)

		{
		}

		KeyCode Key;
		int Scancode;
	};

	struct CharInputEventArgs : InputEventArgs
	{
		CharInputEventArgs(unsigned int unicode, int p_mods) : InputEventArgs(p_mods), Unicode(unicode){}
		unsigned int Unicode;
	};

	STATIC_VAR(static_KeyboardWrapper, s_currentKeyboard);

	//TODO: Sticky keys? see glfw ref.
	class KeyboardWrapper : static_KeyboardWrapper<KeyboardWrapper*>
	{
	public:
		friend class Game;
		KeyboardWrapper() = default;

		KeyboardWrapper(GLFWwindow* p_window) : m_window(p_window)
		{
		}

		bool IsKeyDown(KeyCode p_key) const
		{
			return glfwGetKey(m_window, static_cast<int>(p_key)) == GLFW_PRESS;
		}

		bool IsKeyPressed(KeyCode p_key) const
		{
			return glfwGetKey(m_window, static_cast<int>(p_key)) == GLFW_REPEAT;
		}

		bool IsKeyUp(KeyCode p_key) const
		{
			return glfwGetKey(m_window, static_cast<int>(p_key)) == GLFW_RELEASE;
		}

		const char* GetKeyName(KeyCode p_key, int p_scancode) const
		{
			return glfwGetKeyName(static_cast<int>(p_key), p_scancode);
		}

	public: 
		Event<const KeyboardInputEventArgs&> KeyDown;
		Event<const KeyboardInputEventArgs&> KeyUp;
		Event<const KeyboardInputEventArgs&> KeyRepeat;
		Event<const CharInputEventArgs&> CharInput;


	private:
		void handleKeyboardInputEvents(int p_action, const KeyboardInputEventArgs& p_args) const
		{
			switch (p_action)
			{
			case GLFW_PRESS: KeyDown(p_args);
				break;
			case GLFW_RELEASE: KeyUp(p_args);
				break;
			case GLFW_REPEAT: KeyRepeat(p_args);
				break;
			default: assert(1 == 0);
			}
		}

		void handleCharInputEvent(const CharInputEventArgs& args) const
		{
			CharInput(args);
		}

		static void init(GLFWwindow* p_window, KeyboardWrapper* p_keyboard)
		{
			glfwSetKeyCallback(p_window, [](GLFWwindow*, int p_key, int p_scancode, int p_action, int p_mods)
			{
				assert(s_currentKeyboard != nullptr);
				KeyboardInputEventArgs args{ static_cast<KeyCode>(p_key), p_scancode, p_mods };
				s_currentKeyboard->handleKeyboardInputEvents(p_action, args);
			});

			glfwSetCharModsCallback(p_window, [](GLFWwindow*, unsigned int p_unicode, int p_mods)
			{
				assert(s_currentKeyboard != nullptr);
				CharInputEventArgs args(p_unicode, p_mods);
				s_currentKeyboard->handleCharInputEvent(args);

			});

			s_currentKeyboard = p_keyboard;
		}



	private:
		GLFWwindow* m_window;
	};



	//doo::KeyboardWrapper* doo::KeyboardWrapper::s_currentKeyboard = nullptr;

}
