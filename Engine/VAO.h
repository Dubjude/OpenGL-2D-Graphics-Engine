#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"
#include<stdint.h>

namespace mem
{
	class VAO
	{
	public:
		VAO() {}
		void init();

		void LinkAttrib(VBO& VBO, uint32_t layout, uint32_t numComponents, uint32_t type, size_t stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();

		uint32_t getID() { return ID; }

	private:
		uint32_t ID;
	};
}

#endif 
