#include"VAO.h"

namespace mem
{

	void VAO::init()
	{
		glGenVertexArrays(1, &ID);
	}

	void VAO::LinkAttrib(VBO& VBO, uint32_t layout, uint32_t numComponents, uint32_t type, size_t stride, void* offset)
	{
		VBO.Bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		VBO.Unbind();
	}

	void VAO::Bind()
	{
		glBindVertexArray(ID);
	}

	void VAO::Unbind()
	{
		glBindVertexArray(0);
	}

	void VAO::Delete()
	{
		glDeleteVertexArrays(1, &ID);
	}
}