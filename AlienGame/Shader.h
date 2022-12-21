#include "Texture.h"

class Shader
{
protected:
	uint program;

public:
	Shader() : program(99999)
	{ }

	Shader(const char* vertexShaderLocation, const char* fragmentShaderLocation)
	{
		// File opening:
		char* vertexShaderSource = OpenFile(vertexShaderLocation);
		char* fragmentShaderSource = OpenFile(fragmentShaderLocation);
		if (vertexShaderSource == nullptr)
		{
			std::cout << "ERROR::SHADER::VERTEX DOES NOT EXIST\n";
			return;
		}
		if (fragmentShaderSource == nullptr)
		{
			std::cout << "ERROR::SHADER::FRAGMENT DOES NOT EXIST\n";
			return;
		}

		uint vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		delete vertexShaderSource;
		glCompileShader(vertexShader);
		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		uint fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		delete fragmentShaderSource;
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		program;
		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);
		glGetProgramiv(program, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Use()
	{
		glUseProgram(program);
	}

	void Delete()
	{
		glDeleteProgram(program);
	}

	void SetVec3(vec3 vector3, const char* name)
	{
		glUniform3f(glGetUniformLocation(program, name), vector3.x, vector3.y, vector3.z);
	}

	void SetMat4(glm::mat4 mat, const char* name)
	{
		glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void SetTex3D(Texture tex, const char* name)
	{
		glUniform1i(glGetUniformLocation(program, name), tex.position);
	}

	void SetInt(int i, const char* name)
	{
		glUniform1i(glGetUniformLocation(program, name), i);
	}

	void SetFloat(float f, const char* name)
	{
		glUniform1f(glGetUniformLocation(program, name), f);
	}
};