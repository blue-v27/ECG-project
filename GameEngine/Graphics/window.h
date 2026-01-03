#include <iostream>
#include <glew.h>
#include <glfw3.h>

#pragma once

#define MAX_KEYBOARD 512
#define MAX_MOUSE 8

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

class Window
{
	private:
		char* name;
		int width, height;
		GLFWwindow* window;

		int keys[MAX_KEYBOARD];
		int mouseButtons[MAX_MOUSE];
		double xpos;
		double ypos;
	
	public:
		Window(char* name, int width, int height);
		~Window();
		GLFWwindow* getWindow();

		void init();
		void update();
		void clear();

		void SetKey(int key, int action);
		void SetMouseButton(int button, int action);
		void setMousePos(double xpos, double ypos);
		void getMousePos(double &xpos, double &ypos);
		bool isPressed(int key);
		bool IsReleased(int key);
		bool isMousePressed(int button);

		bool IsMouseReleased(int button);

		void setMouseMode(int mode);

		int getWidth();
		int getHeight();
		void SetWidth();
		void GetWifth();
};