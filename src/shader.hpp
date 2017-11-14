#ifndef SHADER_H_P_P
#define SHADER_H_P_P

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader {
public:
	Shader(const std::string &pathToVertSource, const std::string &pathToFragSource);
	~Shader();

	unsigned int getShaderProgram() const;
	void use() const;
	void setUniformMat4(const std::string &name, const glm::mat4 &mat) const;
private:
	std::vector<const char *> getSourceFromFile(const std::string &pathToShaderSource) const;
	unsigned int compileShader(const std::string &pathToShaderSource, GLenum shaderType) const;
	void buildProgram(const std::string &pathToVertexSource, const std::string &pathToFragmentSource);

	unsigned int shaderProgram_;
};

#endif
