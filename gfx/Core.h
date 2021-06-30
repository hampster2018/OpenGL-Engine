#pragma once
#include "glew.h"
#include "glfw3.h"
#include "glfw3native.h"
#include <stdio.h>

typedef uint32_t uint;

namespace gfx
{

	struct Color
	{
		float r = 0.f, g = 0.f, b = 0.f;
	};

	struct WindowOptions
	{
		bool resizable = false;
		Color clear = {};
	};

	struct OpenGLInstance
	{
		GLFWwindow* window;

		bool IsRunning() const { return !glfwWindowShouldClose(window); }
	};

	static OpenGLInstance init(uint width, uint height, const char* title, 
		const WindowOptions& options = {})
	{

		if (!glfwInit())
		{
			printf("Failed to initialize GLFW, aborting...\n");
			glfwTerminate();
			return { nullptr };
		}


		glfwWindowHint(GLFW_RESIZABLE, options.resizable);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


		GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwMakeContextCurrent(window);

		if (!window)
		{
			printf("Window creation failed, aborting... \n");
			glfwTerminate();
			return { nullptr };
		}


		glewExperimental = GL_TRUE;
		if (glewInit())
		{
			printf("Failed to initialize window, aborting...\n");
			glfwDestroyWindow(window);
			glfwTerminate();
			return { nullptr };
		}


		glClearColor(options.clear.r, options.clear.g, options.clear.b, 1.f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
		glfwSetWindowSizeCallback(window, [](GLFWwindow* w, int width, int height)
			{ glViewport(0, 0, width, height); });

		return { window };
	}
	static void end(OpenGLInstance& instance)
	{
		glfwDestroyWindow(instance.window);
		glfwTerminate();
	}
}