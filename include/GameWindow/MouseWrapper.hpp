#pragma once

#include <array>
#include "GLFW/glfw3.h"
#include "KeyboardWrapper.hpp"
#include <chrono>

namespace doo
{
	enum class MouseButton : int
	{
		FrontThumb = GLFW_MOUSE_BUTTON_4,
		BackThumb = GLFW_MOUSE_BUTTON_5,
		to_be_defined_6 = GLFW_MOUSE_BUTTON_6,
		to_be_defined_7 = GLFW_MOUSE_BUTTON_7,
		to_be_defined_8 = GLFW_MOUSE_BUTTON_8,
		Left = GLFW_MOUSE_BUTTON_1,
		Right = GLFW_MOUSE_BUTTON_2,
		Middle = GLFW_MOUSE_BUTTON_3
	};

	struct DPoint
	{
		double X, Y;
	};

	struct MouseInputEventArgs : InputEventArgs
	{
		MouseInputEventArgs(DPoint p_mousePos, MouseButton p_button, int p_mods)
			: InputEventArgs(p_mods), MousePosition(p_mousePos), Button(p_button)
		{
		}

		DPoint MousePosition;
		MouseButton Button;
	};

	struct MouseMoveEventArgs
	{
		DPoint MousePosition;
	};

	STATIC_VAR(static_MouseWrapper, s_currentMouse);

	class MouseWrapper : static_MouseWrapper<MouseWrapper*>
	{
	public:
		friend class Game;
		MouseWrapper() = default;

		MouseWrapper(GLFWwindow* p_window) : m_window(p_window)
		{
		}

		bool IsMouseButtonDown(MouseButton p_button) const
		{
			return glfwGetMouseButton(m_window, static_cast<int>(p_button)) == GLFW_PRESS;
		}

		bool IsMouseButtonUp(MouseButton p_button) const
		{
			return glfwGetMouseButton(m_window, static_cast<int>(p_button)) == GLFW_RELEASE;
		}

	private:
		static void init(GLFWwindow* p_window, MouseWrapper* p_mouse)
		{
			glfwSetMouseButtonCallback(p_window, &mainMouseInputEventEntry);
			glfwSetCursorEnterCallback(p_window, &mainMouseEnterEventEntry);
			glfwSetCursorPosCallback(p_window, &mainMouseMoveEventEntry);
			s_currentMouse = p_mouse;
		}

		static void mainMouseInputEventEntry(GLFWwindow* p_window, int p_mouseButton, int p_action, int p_mods)
		{
			DPoint mousePos;
			glfwGetCursorPos(p_window, &mousePos.X, &mousePos.Y);
			MouseButton mb = static_cast<MouseButton>(p_mouseButton);
			const MouseInputEventArgs args = {mousePos, mb, p_mods};
			s_currentMouse->handleMouseInputEvent(p_action, args);
		}

		static void mainMouseEnterEventEntry(GLFWwindow*, int p_within)
		{
			if (p_within) s_currentMouse->handleMouseEnterEvent();
			else s_currentMouse->handleMouseLeaveEvent();
		}

		static void mainMouseMoveEventEntry(GLFWwindow*, double p_x, double p_y)
		{
			s_currentMouse->handleMouseMoveEvent({{p_x,p_y}});
		}

		void handleMouseMoveEvent(const MouseMoveEventArgs& p_args) const
		{
			MouseMove(p_args);
		}

		void handleMouseEnterEvent() const { MouseEnterWindow(); }
		void handleMouseLeaveEvent() const { MouseLeaveWindow(); }

		void handleMouseInputEvent(int p_action, const MouseInputEventArgs& p_args) const
		{
			int mbc = static_cast<int>(p_args.Button);
			if (p_action == GLFW_PRESS) MouseButtonDown(p_args);
			else MouseButtonUp(p_args);
		}


	public:
		Event<const MouseMoveEventArgs&> MouseMove;
		Event<const MouseInputEventArgs&> MouseButtonDown;
		Event<const MouseInputEventArgs&> MouseButtonUp;
		Event<> MouseEnterWindow;
		Event<> MouseLeaveWindow;

	private:
		GLFWwindow* m_window;
	};
}
