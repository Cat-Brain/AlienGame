#include "Player.h"

class Game : public Window
{
public:
	bool isRunning;
	std::vector<Entity*> entities;
	Shader defaultShader;
	Mesh* cube;
	float lastTime;

	Game()
	{
		Run();
	}

	void Run()
	{
		if(!Start()) return;

		isRunning = true;
		while (isRunning)
			Update();

		End();
	}

	bool Start()
	{
		std::cout << "0\n";
		if(!Window::Start()) return false;
		entities = std::vector<Entity*>();
		std::cout << "1\n";
		defaultShader = Shader("DefaultDiffuseVert.txt", "DefaultDiffuseFrag.txt");
		std::cout << "2\n";

		float cubeVertices[] = {
			 0.5f,  0.5f, -0.5f, 0.0f, 0.0f,-1.0f, // 2
			 0.5f, -0.5f, -0.5f, 0.0f, 0.0f,-1.0f, // 1
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,-1.0f, // 0
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,-1.0f, // 0
			-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,-1.0f, // 3
			 0.5f,  0.5f, -0.5f, 0.0f, 0.0f,-1.0f, // 2

			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // 4
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // 5
			 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // 6
			 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // 6
			-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // 7
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // 4

			-0.5f,  0.5f,  0.5f,-1.0f, 0.0f, 0.0f, // 7
			-0.5f,  0.5f, -0.5f,-1.0f, 0.0f, 0.0f, // 3
			-0.5f, -0.5f, -0.5f,-1.0f, 0.0f, 0.0f, // 0
			-0.5f, -0.5f, -0.5f,-1.0f, 0.0f, 0.0f, // 0
			-0.5f, -0.5f,  0.5f,-1.0f, 0.0f, 0.0f, // 4
			-0.5f,  0.5f,  0.5f,-1.0f, 0.0f, 0.0f, // 7

			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 1
			 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 2
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 6
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 6
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 5
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 1

			-0.5f, -0.5f, -0.5f, 0.0f,-1.0f, 0.0f, // 0
			 0.5f, -0.5f, -0.5f, 0.0f,-1.0f, 0.0f, // 1
			 0.5f, -0.5f,  0.5f, 0.0f,-1.0f, 0.0f, // 5
			 0.5f, -0.5f,  0.5f, 0.0f,-1.0f, 0.0f, // 5
			-0.5f, -0.5f,  0.5f, 0.0f,-1.0f, 0.0f, // 4
			-0.5f, -0.5f, -0.5f, 0.0f,-1.0f, 0.0f, // 0

			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // 6
			 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 2
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 3
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 3
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // 7
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // 6
		};

		cube = new Mesh1(cubeVertices, sizeof(cubeVertices));
		entities.push_back(new Player(3.0f, 0.1f));

		int width = 16, height = 16, depth = 16;
		unsigned char* data = new unsigned char[16384];
		uint index = 0;
		for (int x = 0; x < width; x++)
			for (int y = 0; y < height; y++)
				for (int z = 0; z < depth; z++)
				{
					data[index] = rand() % 256;
					index++;
					data[index] = rand() % 256;
					index++;
					data[index] = rand() % 256;
					index++;
					data[index] = rand() % 2 * 255;
					index++;
				}

		entities.push_back(new Chunk(data, &defaultShader, cube, { 0.0f, 0.0f, -32.0f }, glm::vec3(0), 16.0f));

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		
		lastTime = glfwGetTime();
		return true;
	}
	
	void Update()
	{
		float deltaTime = glfwGetTime() - lastTime;
		tTime += deltaTime;
		lastTime = glfwGetTime();
		ProcessInput();

		Window::Update(deltaTime);
		for (Entity* entity : entities)
			entity->Update(this, deltaTime);

		for (Entity* entity : entities)
			entity->DUpdate(this, deltaTime);

		isRunning &= ~glfwWindowShouldClose(window);

	}

	void End()
	{
		defaultShader.Delete();
		cube->End();
		Window::End();
	}
	
	void ProcessInput()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
};