#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "utility.h"

namespace mem
{

	struct ShaderSource
	{
		std::string vertexSource;
		std::string fragmentSource;
	};

	class Shader
	{
	public:
		unsigned int ID;
		Shader() {}

		void LinkShader(const std::string& shaderFile);

		void Activate();
		void Delete();

		void setBool(const std::string& name, bool value);
		void setInt(const std::string& name, int value);
		void setFloat(const std::string& name, float value);

		void setList(const std::string& name, int size, int value[]);

		void setVec2v(const std::string& name, const glm::vec2& value);
		void setVec2(const std::string& name, float x, float y);
		void setVec3v(const std::string& name, const glm::vec3& value);
		void setVec3(const std::string& name, float x, float y, float z);
		void setVec4v(const std::string& name, const glm::vec4& value);
		void setVec4(const std::string& name, float x, float y, float z, float w);

		void setMat2(const std::string& name, const glm::mat2& mat);
		void setMat3(const std::string& name, const glm::mat3& mat);
		void setMat4(const std::string& name, glm::mat4 value);

		void setSamplerArray(const std::string& name, int* value, int lenght);

	private:
		ShaderSource readShader(const std::string& shaderFile);
	};

}

#endif
