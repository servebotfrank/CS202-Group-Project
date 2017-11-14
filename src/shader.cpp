#include "shader.hpp"

Shader::Shader(const std::string &pathToVertSource, const std::string &pathToFragSource)
	: shaderProgram_{0} {
	buildProgram(pathToVertSource, pathToFragSource);
}
Shader::~Shader() {
	glDeleteProgram(shaderProgram_);
}

unsigned int Shader::getShaderProgram() const {
	return shaderProgram_;
}
void Shader::use() const {
	glUseProgram(shaderProgram_);
}
void Shader::setUniformMat4(const std::string &name, const glm::mat4 &mat4) const {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram_, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
}
unsigned int Shader::compileShader(const std::string &pathToShaderSource, GLenum shaderType) const {
	unsigned int shader = 0;
	switch(shaderType) {
		case GL_VERTEX_SHADER:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case GL_FRAGMENT_SHADER:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		default:
			throw std::runtime_error("Error::compileShader() unknown shaderType");
			break;
	}

	std::fstream fs(pathToShaderSource.c_str(), std::ios::in);
	if(!fs) {
		throw std::runtime_error("fstream() failed to open file");
	}

	{
		std::stringstream ss;
		ss << fs.rdbuf();
		fs.close();
		std::string source = ss.str();
		const char * formatedSource = source.c_str();
		glShaderSource(shader, 1, &formatedSource, 0);
		glCompileShader(shader);
	}

	int success = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(success == GL_FALSE) {
		char err[512];
		glGetShaderInfoLog(shader, 512, NULL, err);
		std::string errMsg("ERROR::SHADER::");
		switch(shaderType) {
			case GL_VERTEX_SHADER:
				errMsg += "VERTEX::";
				break;
			case GL_FRAGMENT_SHADER:
				errMsg += "FRAGMENT::";
				break;
		}
		errMsg += "COMPILATION_FAILED::";
		errMsg += err;
		throw std::runtime_error(errMsg);
	}

	return shader;
}
void Shader::buildProgram(const std::string &pathToVertexSource, const std::string &pathToFragmentSource) {
	shaderProgram_ = glCreateProgram();

	auto vertexShader = compileShader(pathToVertexSource, GL_VERTEX_SHADER);
	glAttachShader(shaderProgram_, vertexShader);
	auto fragmentShader = compileShader(pathToFragmentSource, GL_FRAGMENT_SHADER);
	glAttachShader(shaderProgram_, fragmentShader);

	glLinkProgram(shaderProgram_);

	int success = GL_FALSE;
	glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		char err[512];
		glGetProgramInfoLog(shaderProgram_, 512, NULL, err);
		std::string errMsg{"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"};
		errMsg += err;
		errMsg += "\n";
		throw std::runtime_error(errMsg);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
