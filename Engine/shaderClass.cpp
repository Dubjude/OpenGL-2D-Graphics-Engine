#include"shaderClass.h"

namespace mem
{
	ShaderSource Shader::readShader(const std::string& shaderFile)
	{
		std::ifstream stream(shaderFile);

		enum class ShaderType
		{
			NONE = -1, VERTEX, FRAGMENT
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("VERTEX") != std::string::npos)
				{
					type = ShaderType::VERTEX;
				}
				else if (line.find("FRAGMENT") != std::string::npos)
				{
					type = ShaderType::FRAGMENT;
				}
			}
			else
			{
				ss[(int)type] << line << '\n';
			}
		}

		if (type == ShaderType::FRAGMENT)
			return { ss[0].str(), ss[1].str() };
		else
			print("Failed to load shader");
	}

	void Shader::LinkShader(const std::string& shaderFile)
	{
		ShaderSource source = readShader(shaderFile);
		std::string vertexCode = source.vertexSource;
		std::string fragmentCode = source.fragmentSource;

		const char* vertexSource = vertexCode.c_str();
		const char* fragmentSource = fragmentCode.c_str();

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);

		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		/*
		print("--------------------------------VERTEX-------------------------------------------------");
		print(vertexCode);
		print("--------------------------------FRAGMENT-----------------------------------------------");
		print(fragmentCode);
		print("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
		*/
	}

	void Shader::Activate()
	{
		glUseProgram(ID);
	}

	void Shader::Delete()
	{
		glDeleteProgram(ID);
	}

	void Shader::setBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void Shader::setInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void Shader::setFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void Shader::setList(const std::string& name, int size, int value[])
	{
		glUniform1iv(glGetUniformLocation(ID, name.c_str()), size, value);
	}

	void Shader::setVec2v(const std::string& name, const glm::vec2& value)
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	void Shader::setVec2(const std::string& name, float x, float y)
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}

	void Shader::setVec3v(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	void Shader::setVec3(const std::string& name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	void Shader::setVec4v(const std::string& name, const glm::vec4& value)
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}

	void Shader::setMat2(const std::string& name, const glm::mat2& mat)
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::setMat3(const std::string& name, const glm::mat3& mat)
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::setMat4(const std::string& name, glm::mat4 value)
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::setSamplerArray(const std::string& name, int* value, int lenght)
	{
		glUniform1iv(glGetUniformLocation(ID, name.c_str()), lenght, value);
	}
}