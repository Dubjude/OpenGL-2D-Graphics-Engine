#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include<stdint.h>

namespace mem
{

	class EBO
	{
	public:
		EBO(uint32_t* indices, size_t size);

		void Bind();
		void Unbind();
		void Delete();
		
	private:
		GLuint ID;
	};

}

#endif
