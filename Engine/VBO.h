#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>
#include<stdint.h>

namespace mem
{
	class VBO
	{
	public:
		VBO(const void* vertices, size_t size);

		void Bind();
		void Unbind();
		void Delete();

		uint32_t getID() { return ID; }
	
	private:
		uint32_t ID;
	};
}

#endif 
