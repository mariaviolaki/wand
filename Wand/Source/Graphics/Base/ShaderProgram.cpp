#include "WandPCH.h"
#include "ShaderProgram.h"
#include "glad/glad.h"
#include "Utils/Utils.h"
#include "Utils/Logger.h"

namespace wand
{
	ShaderProgram::ShaderProgram(std::string shaderPath, std::string vertShader, std::string fragShader)
	{
		mId = CreateProgram(shaderPath + vertShader, shaderPath + fragShader);
		glUseProgram(mId);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(mId);
	}

	void ShaderProgram::SetUniform1f(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void ShaderProgram::SetUniform1iv(const std::string& name, int count, const int* arr)
	{
		glUniform1iv(GetUniformLocation(name), count, arr);
	}

	void ShaderProgram::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	int ShaderProgram::GetUniformLocation(const std::string& name)
	{
		// Check is the location is already saved
		if (mUniformLocations.find(name) != mUniformLocations.end())
			return mUniformLocations[name];

		// Find the uniform location in the shader program
		int location = glGetUniformLocation(mId, name.c_str());
		mUniformLocations[name] = location;

		if (location == -1)
			Logger::EngineLog("ShaderProgram", "Uniform '" + name + "' not found or not set correctly.\n");

		return location;
	}

	void ShaderProgram::Bind() const
	{
		glUseProgram(mId);
	}

	void ShaderProgram::Unbind() const
	{
		glUseProgram(0);
	}

	unsigned int ShaderProgram::CreateProgram(const std::string& vertShaderPath, const std::string& fragShaderPath)
	{
		// Create an id for the program and the shaders
		unsigned int programId = glCreateProgram();
		unsigned int vertShaderId = CompileShader(GL_VERTEX_SHADER, vertShaderPath);
		unsigned int fragShaderId = CompileShader(GL_FRAGMENT_SHADER, fragShaderPath);

		// Link the shaders in a single program
		glAttachShader(programId, vertShaderId);
		glAttachShader(programId, fragShaderId);
		glLinkProgram(programId);

		// Delete shaders since they are no longer needed
		glDeleteShader(vertShaderId);
		glDeleteShader(fragShaderId);

		return programId;
	}

	unsigned int ShaderProgram::CompileShader(unsigned int shaderType, const std::string& shaderPath) const
	{
		// Create a specific type of shader and assign it an id
		unsigned int shaderId = glCreateShader(shaderType);

		// Get the contents of the shader file
		std::string shaderSource = Utils::ReadFile(shaderPath);
		const char* shaderSourceC = shaderSource.c_str();

		// Link the shader with the appropriate source code
		glShaderSource(shaderId, 1, &shaderSourceC, nullptr);
		glCompileShader(shaderId);
		DebugShader(shaderType, shaderId);

		return shaderId;
	}

	void ShaderProgram::DebugShader(unsigned int shaderType, unsigned int shaderId) const
	{
		// Get the shader's compilation status
		int compiled;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);

		// If there were compilation errors
		if (compiled != GL_TRUE)
		{
			// Get the length of the error message
			int length;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

			// Get the error message
			char* message = new char[length];
			glGetShaderInfoLog(shaderId, length, &length, message);

			// Display the error message for the appropriate shader
			if (shaderType == GL_VERTEX_SHADER)
				Logger::EngineLog("ShaderProgram", "Vertex ");
			else if (shaderType == GL_FRAGMENT_SHADER)
				Logger::EngineLog("ShaderProgram", "Fragment ");
			Logger::Log("Shader compilation error: " + std::string(message));

			// Free memory for the error message
			delete[] message;
		}
	}
}
