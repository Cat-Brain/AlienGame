#include "Entity.h"

class Game : public Window
{
public:
	bool isRunning;
	std::vector<Entity*> entities;
	Shader shader1, shader2;
	Mesh* mesh1, *mesh2;

	Game()
	{
		Run();
	}

	void Run()
	{
		Start();

		isRunning = true;
		while (isRunning)
			Update();

		End();
	}

	void Start()
	{
		Window::Start();
		entities = std::vector<Entity*>();
		shader1 = Shader("DefaultDiffuseVert.txt", "DefaultDiffuseFrag.txt");
		shader2 = Shader("DefaultDiffuseVert.txt", "DefaultDiffuseFrag2.txt");
		float vertices1[] = {
			// first triangle
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f,  // top left 
			 0.5f,  0.5f, 0.0f,  // top right
			// second triangle
			-0.5f, -0.5f, 0.0f,  // bottom left
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f  // bottom right
		};
		float vertices2[] = {
			-1.0f, -1.0f, 0.0f,  // bottom left
			-1.0f,  0.0f, 0.0f,  // top left 
			 0.0f,  0.0f, 0.0f,  // top right
			 0.0f, -1.0f, 0.0f,  // bottom right
		};
		uint indices[] = {
			0, 1, 2,
			0, 2, 3
		};
		mesh1 = new Mesh1(vertices1, sizeof(vertices1));
		mesh2 = new Mesh2(vertices2, sizeof(vertices2), indices, sizeof(indices));
		entities.push_back(new Entity(&shader1, mesh1));
		entities.push_back(new Entity(&shader2, mesh2));
	}
	
	void Update()
	{
		ProcessInput();

		Window::Update();
		for (Entity* entity : entities)
			entity->Update(this);

		isRunning &= !glfwWindowShouldClose(window);
	}

	void End()
	{
		shader1.Delete();
		shader2.Delete();
		mesh1->End();
		mesh2->End();
		Window::End();
	}
	
	void ProcessInput()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
};