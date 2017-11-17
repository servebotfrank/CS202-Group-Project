#include "shader.hpp"

Shader::Shader(const std::string &pathToVertSource, const std::string &pathToFragSource)
	: pathToVertexSource_{pathToVertSource}, pathToFragSource_{pathToFragSource}, shaderProgram_{0} {
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
void Shader::setUniformBool(const std::string &name, bool val) const {
	glUniform1i(glGetUniformLocation(shaderProgram_, name.c_str()), static_cast<int>(val)); 
}
void Shader::setUniformInt(const std::string &name, int32_t val) const {
	glUniform1i(glGetUniformLocation(shaderProgram_, name.c_str()), val); 
}
void Shader::setUniformFloat(const std::string &name, float val) const {
	glUniform1f(glGetUniformLocation(shaderProgram_, name.c_str()), val); 
}
void Shader::setUniformMat2(const std::string &name, const glm::mat2 &mat) const {
	glUniformMatrix2fv(glGetUniformLocation(shaderProgram_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setUniformMat3(const std::string &name, const glm::mat3 &mat) const {
	glUniformMatrix3fv(glGetUniformLocation(shaderProgram_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setUniformMat4(const std::string &name, const glm::mat4 &mat) const {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setUniformVec2(const std::string &name, const glm::vec2 &vec) const {
	glUniform2fv(glGetUniformLocation(shaderProgram_, name.c_str()), 2, &vec[0]);
}
void Shader::setUniformVec3(const std::string &name, const glm::vec3 &vec) const {
	glUniform3fv(glGetUniformLocation(shaderProgram_, name.c_str()), 3, &vec[0]);
}
void Shader::setUniformVec4(const std::string &name, const glm::vec4 &vec) const {
	glUniform3fv(glGetUniformLocation(shaderProgram_, name.c_str()), 4, &vec[0]);
}

std::string Shader::getPathToVertexSource() const {
	return pathToVertexSource_;
}
std::string Shader::getPathToFragSource() const {
	return pathToFragSource_;
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
		throw std::runtime_error("Error::fstream() failed to open file");
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
