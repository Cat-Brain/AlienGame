#include "Mesh.h"

Inputs inputs;
bool firstMouse;

class Window
{
private:
	int lastTitleUpdate = 0;
	int frameCount;
	bool fullscreened = false;
public:
	GLFWwindow* window;
	glm::mat4 perspective, view;
	int width = 600, height = 600;
	vec3 playerPos = vec3(0);

	bool Start()
	{
		std::cout << "0.1\n";
		firstMouse = true;
		if (glfwInit() == GL_FALSE)
		{
			std::cout << "Failed to initialize GLFW\n";
			return false;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		std::cout << "0.2\n";

		window = glfwCreateWindow(width, height, "Alien game!", NULL, NULL);
		std::cout << "0.3\n";
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window\n";
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD\n";
			return false;
		}

		glViewport(0, 0, width, width);

		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		perspective = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.01f, 100.0f);
		view = glm::translate(glm::mat4(1), -playerPos);
		return true;
	}

	void Update(float deltaTime)
	{
		inputs.mouseDelta = vec2(0.0f);
		glfwSwapBuffers(window);
		glfwSwapInterval(1);
		glfwPollEvents();
		glfwGetWindowSize(window, &width, &height);
		if (tTime - lastTitleUpdate > 1.0f)
		{
			glfwSetWindowTitle(window, (std::string("Alien game! FPS = ") + std::to_string(frameCount)).c_str());
			lastTitleUpdate = int(tTime);
			frameCount = 0;
		}
		else frameCount++;
		perspective = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.01f, 100.0f);
		inputs.Update(window);
		if (inputs.f.pressed)
		{
			if (fullscreened)
				glfwRestoreWindow(window);
			else
				glfwMaximizeWindow(window);
			fullscreened = !fullscreened;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void End()
	{
		glfwTerminate();
	}

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (firstMouse)
		{
			inputs.mousePos = { xpos, ypos };
			firstMouse = false;
		}

		inputs.mouseDelta.x = xpos - inputs.mousePos.x;
		inputs.mouseDelta.y = inputs.mousePos.y - ypos;
		inputs.mousePos.x = xpos;
		inputs.mousePos.y = ypos;
	}
};