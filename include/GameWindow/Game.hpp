#pragma once

#include <stdexcept>
#include <chrono>
#include "KeyboardWrapper.hpp"
#include "MouseWrapper.hpp"
#include "GLFW/glfw3.h"
#include "TimeWrapper.hpp"
#include "WindowWrapper.hpp"
#include "GLFW/glfw3.h"
#include <stdexcept>
#include <chrono>
#include "GameProperties.hpp"


namespace doo
{
	class Game
	{
	protected:
		virtual GameProperties PreContextCreation() = 0;
		virtual void Update() = 0;

		virtual void PostContextCreation()
		{
		}

		virtual void LoadContent()
		{
		}

		virtual void Shutdown()
		{
		}

		virtual void UnloadContent()
		{
		}

	public:
		Game()
		{
			if (!glfwInit())
				throw std::runtime_error("glfw init failed");
		}


		virtual ~Game()
		{
			glfwDestroyWindow(Window.m_window);
		}

		int Run()
		{
			const GameProperties props = PreContextCreation();
			setupWindow(props);
			setupKeyboard();
			setupMouse();
			PostContextCreation();
			LoadContent();

			while (!Window.ShouldClose())
			{
				Time.startRecording();
				Update();
				glfwSwapBuffers(Window.m_window);
				glfwPollEvents();
				Time.stopRecording();
			}
			UnloadContent();
			Shutdown();
			return 0;
		}

	private:
		void setupWindow(const GameProperties& p_props)
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, p_props.Major);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, p_props.Minor);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			GLFWwindow* window = glfwCreateWindow(1, 1, p_props.Title, nullptr, nullptr);
			if (window == nullptr)
				throw std::runtime_error("window couldn't be created");
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* vmode = glfwGetVideoMode(monitor);

			int w, h;
			if (p_props.ResolutionWidth <= 0 || p_props.ResolutionHeight <= 0) { w = vmode->width; h = vmode->height; }
			else { w = p_props.ResolutionWidth; h = p_props.ResolutionHeight; }
			Window = { window, monitor,*vmode,{ w,h },{ p_props.WindowPosX,p_props.WindowPosY },p_props.Mode };
			WindowWrapper::init(Window.m_window, &Window);
		}
		void setupMouse()
		{
			assert(Window.m_window != nullptr);
			Mouse = { Window.m_window };
			MouseWrapper::init(Window.m_window, &Mouse);
		}
		void setupKeyboard()
		{
			assert(Window.m_window != nullptr);
			Keyboard = { Window.m_window };
			KeyboardWrapper::init(Window.m_window, &Keyboard);
		}

	protected:
		WindowWrapper Window;
		KeyboardWrapper Keyboard;
		MouseWrapper Mouse;
		TimeWrapper Time;
	};
}
