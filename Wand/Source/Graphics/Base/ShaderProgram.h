#pragma once

#include "glm/glm.hpp"

namespace wand
{
	class ShaderProgram
	{
	public:
		ShaderProgram(std::string shaderPath, std::string vertShader, std::string fragShader);
		~ShaderProgram();

		// Set the value of a single float in the shader
		void SetUniform1f(const std::string& name, float value);
		// Set the value of an integer array in the shader
		void SetUniform1iv(const std::string& name, int count, const int* arr);
		// Set the value of a 4x4 matrix in the shader
		void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
		int GetUniformLocation(const std::string& name);

		void Bind() const;
		void Unbind() const;

	private:
		unsigned int mId;
		std::unordered_map<std::string, int> mUniformLocations;

		unsigned int CreateProgram(const std::string& vertShaderPath, const std::string& fragShaderPath);
		unsigned int CompileShader(unsigned int shaderType, const std::string& shaderPath) const;
		void DebugShader(unsigned int shaderType, unsigned int shaderId) const;
	};
}
