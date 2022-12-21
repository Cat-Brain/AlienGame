#include "Shader.h"

class Mesh
{
public:
	virtual void Update() { }
	virtual void End() { }
};

class Mesh1 : public Mesh
{
public:
	uint vao, vbo;
	uint vertCount;

	Mesh1(float* vertices, uint vertSize, GLenum usage = GL_STATIC_DRAW) :
		Mesh(), vertCount(vertSize / (sizeof(float) * 3))
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, usage);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	virtual void Update()
	{
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
	}

	virtual void End()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}
};

class Mesh2 : public Mesh
{
public:
	uint vao, vbo, ebo;
	uint vertCount, indCount;

	Mesh2(float* vertices, uint vertSize, uint* indices, uint indSize, GLenum usage = GL_STATIC_DRAW) :
		Mesh(), vertCount(vertSize / (sizeof(float) * 3)), indCount(indSize / sizeof(uint))
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, usage);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, indices, usage);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void Update() override
	{
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, indCount, GL_UNSIGNED_INT, 0);
	}

	void End() override
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
	}
};