#include "window.h"

Window::Window(char* name, int width, int height)
{
	this -> name = name;
	this -> width = width;
	this -> height = height;
	init();

	for (int i = 0; i < MAX_KEYBOARD; i++)
	{
		this->keys[i] = false;
	}

	for (int i = 0; i < MAX_MOUSE; i++)
	{
		this->mouseButtons[i] = false;
	}
}

Window::~Window()
{
	glfwTerminate();
}

void Window::init()
{
	if (!glfwInit())
	{
		std::cout << "Error initializing glfw!" << std::endl;
	}
	else
	{
		std::cout << "Successfully initializing glfw!" << std::endl;
	}

	window = glfwCreateWindow(width, height, name, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create a GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	//callbacks for user input
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowUserPointer(window, this);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);



	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error initializing glew!" << std::endl;
	}
	else
	{
		std::cout << "Successfully initializing glew!" << std::endl;
	}

	std::cout << "Open GL " << glGetString(GL_VERSION) << std::endl;
}

void Window::update()
{
	glfwPollEvents();
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSwapBuffers(window);
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLFWwindow* Window::getWindow()
{
	return window;
}

int Window::getWidth()
{
	return width;
}

int Window::getHeight()
{
	return height;
}

void Window::SetKey(int key, int action)
{
	if(action == GLFW_PRESS)
		this -> keys[key] = GLFW_PRESS;

	if (action == GLFW_RELEASE)
	{
		if (this->keys[key] == GLFW_PRESS)
			keys[key] = -1;
		else
			keys[key] = 0;
	}
}

void Window::SetMouseButton(int button, int action)
{
	if (action == GLFW_PRESS)
		this->mouseButtons[button] = GLFW_PRESS;

	if (action == GLFW_RELEASE)
	{
		if (this->mouseButtons[button] == GLFW_PRESS)
			mouseButtons[button] = -1;
		else
			mouseButtons[button] = 0;
	}
}

void Window::setMousePos(double xpos, double ypos)
{
	this->xpos = xpos;
	this->ypos = ypos;
}

void Window::getMousePos(double &xpos, double &ypos)
{
	xpos = this->xpos;
	ypos = this->ypos;
}

//Handling key pressed
bool Window::isPressed(int key)
{
	return keys[key] == GLFW_PRESS;
}

bool Window::IsReleased(int key)
{
	if (keys[key] == -1)
	{
		keys[key] = 0;
		return true;
	};

	return false;
}
//Handling mouse buttons pressed
bool Window::isMousePressed(int button)
{
	return mouseButtons[button] == GLFW_PRESS;
}

bool Window::IsMouseReleased(int button)
{
	if (mouseButtons[button] == -1)
	{
		mouseButtons[button] = 0;
		return true;
	};

	return false;
}

//Handling keyboard actions
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* wind = (Window*) glfwGetWindowUserPointer(window);

	wind->SetKey(key, action);
}

//Handling mouse actions
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Window* wind = (Window*)glfwGetWindowUserPointer(window);

	wind->SetMouseButton(button, action);
}

//Handling cursor position
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Window* wind = (Window*)glfwGetWindowUserPointer(window);
	wind->setMousePos(xpos, ypos);
}
