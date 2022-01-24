#pragma once

namespace wand
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertShader, const std::string& fragShader);
		~ShaderProgram();

		void Bind() const;
		void Unbind() const;

	private:
		const std::string SHADER_PATH;
		unsigned int mId;

		unsigned int CreateProgram(const std::string& vertShaderPath, const std::string& fragShaderPath);
		unsigned int CompileShader(unsigned int shaderType, const std::string& shaderPath) const;
		void DebugShader(unsigned int shaderType, unsigned int shaderId) const;
	};
}
