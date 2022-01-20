#include "Window.h"

#include "glad/glad.c"
#include <iostream>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "IndexBuffer.h"

int main()
{
	wand::Window window;

	// Vertices for a rectangle in the middle of the window (counterclockwise)
	float vertices[]
	{
		// POSITION				// COLOR
		-0.5f, -0.5f, 0.0f,		0.5f, 0.0f, 0.5f, 1.0f,		// bottom left corner
		 0.5f, -0.5f, 0.0f,		0.5f, 0.0f, 0.5f, 1.0f,		// bottom right corner
		 0.5f,  0.5f, 0.0f,		0.5f, 0.0f, 0.5f, 1.0f,		// top right corner
		-0.5f,  0.5f, 0.0f,		0.5f, 0.0f, 0.5f, 1.0f		// top left corner
	};

	// Indices for two triangles with 2 common vertices
	const unsigned int INDEX_COUNT = 6;
	unsigned int indices[INDEX_COUNT]
	{
		0, 1, 2,	// bottom right triangle
		2, 3, 0		// top left triangle
	};

	wand::VertexArray vao;
	wand::VertexBuffer vbo(vertices, sizeof(vertices));
	wand::VertexLayout* layout = new wand::VertexLayout();
	layout->Add<float>(3);
	layout->Add<float>(4);
	vbo.AddLayout(layout);
	vao.Config(vbo);
	wand::IndexBuffer ibo(indices, INDEX_COUNT);

	const char* vertShaderSource =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"out vec4 vColor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(position, 1.0);\n"
		"	vColor = color;\n"	
		"}\n";
	const char* fragShaderSource =
		"#version 330 core\n"
		"\n"
		"in vec4 vColor;\n"
		"out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = vColor;\n"
		"}\n";

	unsigned int programId = glCreateProgram();
	unsigned int vertShaderId = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertShaderId, 1, &vertShaderSource, nullptr);
	glShaderSource(fragShaderId, 1, &fragShaderSource, nullptr);

	glCompileShader(vertShaderId);
	glCompileShader(fragShaderId);

	glAttachShader(programId, vertShaderId);
	glAttachShader(programId, fragShaderId);

	glDeleteShader(vertShaderId);
	glDeleteShader(fragShaderId);

	glLinkProgram(programId);
	glUseProgram(programId);

	while (!window.IsClosed())
	{
		glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);

		window.Update();
	}

	glDeleteProgram(programId);

	return 0;
}
