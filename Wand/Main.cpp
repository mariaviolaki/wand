#include "Window.h"

#include "glad/glad.c"
#include <iostream>
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexLayout.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/ShaderProgram.h"

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

	wand::ShaderProgram program("Standard.vert", "Standard.frag");
	program.Bind();

	while (!window.IsClosed())
	{
		glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);

		window.Update();
	}

	return 0;
}
