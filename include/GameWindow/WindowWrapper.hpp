#pragma once

#include <string>
#include "GLFW/glfw3.h"
#include "Event.hpp"
#include "GameProperties.hpp"
#include <cassert>


#define STATIC_VAR(className, varName)\
template <typename T>\
struct className \
{\
	static T varName ;\
};\
template <typename T>\
T className <T>:: varName


namespace doo
{
	struct Point
	{
		int X, Y;
	};

	struct Size
	{
		friend bool operator==(const Size& p_lhs, const Size& p_rhs)
		{
			return p_lhs.Width == p_rhs.Width
				&& p_lhs.Height == p_rhs.Height;
		}

		friend bool operator!=(const Size& p_lhs, const Size& p_rhs)
		{
			return !(p_lhs == p_rhs);
		}



		int Width, Height;
	};

	struct SizeChangedEventArgs
	{
		Size NewSize;
	};

	struct PosChangedEventArgs
	{
		Point NewPos;
	};

	struct FocusChangedEventArgs
	{
		bool IsFocused;
	};


	STATIC_VAR(static_WindowWrapper, s_currentWindow);

	class WindowWrapper : static_WindowWrapper<WindowWrapper*>
	{
	public:
		friend class Game;
		WindowWrapper() = default;

		WindowWrapper(GLFWwindow* p_window, GLFWmonitor* p_monitor, GLFWvidmode p_vidmode, Size p_size, Point p_pos, WindowMode p_mode) : 
																								  m_window(p_window),
		                                                                                          m_monitor(p_monitor),
		                                                                                          m_vidmode(p_vidmode),
																								  currentMode(p_mode),
																								  m_windowedResSize(p_size),		
																								  m_windowedPos(p_pos)
		{
			SetWindowMode(currentMode);
			SetVSYNC(0);
		}

		void SetWindowMode(WindowMode mode)
		{
			currentMode = mode;
			switch (mode)
			{
			case WindowMode::Windowed: 
				glfwSetWindowMonitor(m_window, nullptr, m_windowedPos.X, m_windowedPos.Y, m_windowedResSize.Width, m_windowedResSize.Height, m_vidmode.refreshRate);
				break;
			case WindowMode::Fullscreen: 
				glfwSetWindowMonitor(m_window, nullptr, 0, 0, m_windowedResSize.Width, m_windowedResSize.Height, m_vidmode.refreshRate);
				break;
			case WindowMode::HighestResolutionFullscreen: 
				glfwSetWindowMonitor(m_window, m_monitor, 0, 0, m_vidmode.width, m_vidmode.height, m_vidmode.refreshRate);
				break;
			default: assert(0==1);
			}
		}

		void SetRefreshRate(int herz)
		{
			m_vidmode.refreshRate = herz;
			SetWindowMode(currentMode);
		}

		void SetVSYNC(int amount = 0)
		{
			glfwSwapInterval(amount);
		}

		void SetResolutionSize(Size p_resSize)
		{
			m_windowedResSize = p_resSize;
			SetWindowMode(currentMode);
		}

		void SetMonitorSizeAsResolutionSize()
		{
			m_windowedResSize = GetMonitorSize();
			SetWindowMode(currentMode);
		}
		
		void SetPos(Point p_newPos )
		{
			m_windowedPos = p_newPos;
			SetWindowMode(currentMode);
		}

		void SetTitle(const std::string& p_title)
		{
			glfwSetWindowTitle(m_window, p_title.c_str());
		}

		Size GetMonitorSize() const
		{
			return {m_vidmode.width,m_vidmode.height};
		}

		Point GetPos() const
		{
			int x, y;
			glfwGetWindowPos(m_window, &x, &y);
			return {x,y};
		}


		Size GetResolutionSize() const
		{
			int x, y;
			glfwGetWindowSize(m_window, &x, &y);
			return {x,y};
		}

		bool ShouldClose() const
		{
			return (glfwWindowShouldClose(m_window));
		}
	public:
		Event<const SizeChangedEventArgs&> SizeChangedEvent;
		Event<const PosChangedEventArgs&>  PosChangedEvent;
		Event<const FocusChangedEventArgs&> FocusChangedEvent;

	private:
		// TODO: Implement functionality so that when switching between fullscreen and windowed mode, the window stays where it should be. 
		static void init(GLFWwindow* p_window, WindowWrapper* p_windowWrapper)
		{
			s_currentWindow = p_windowWrapper;			
			glfwSetWindowSizeCallback(p_window, [](GLFWwindow*, int width, int height)
			{
				assert(s_currentWindow != nullptr);
				SizeChangedEventArgs args{ {width,height} };
				s_currentWindow->SizeChangedEvent(args);
			});

			glfwSetWindowPosCallback(p_window, [](GLFWwindow*, int x, int y)
			{
				assert(s_currentWindow != nullptr);
				PosChangedEventArgs args{ { x,y } };
				s_currentWindow->PosChangedEvent(args);
			});

			glfwSetWindowFocusCallback(p_window, [](GLFWwindow*, int isFocused)
			{
				assert(s_currentWindow != nullptr);
				FocusChangedEventArgs args{ isFocused };
				s_currentWindow->FocusChangedEvent(args);
			});

			
		}

	private:
				
		GLFWwindow* m_window;
		GLFWmonitor* m_monitor;
		GLFWvidmode m_vidmode;

		WindowMode currentMode;
		Size m_windowedResSize;
		Point m_windowedPos;
	};
}
