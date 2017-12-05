#ifndef SHADER_H_P_P
#define SHADER_H_P_P

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#ifdef __linux__
	#include <GL/glew.h>
	#include <SFML/OpenGL.hpp>
#else
	#include <OpenGL/gl3.h>
#endif

#include <SFML/System.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader {
public:
	// compiles and links the shaders
	Shader(const std::string &pathToVertSource, const std::string &pathToFragSource);
	// frees the graphics memory used by the shader
	~Shader();

	// get the gl handle for the shader
	unsigned int getShaderProgram() const;
	void use() const;

	// load various types of uniforms into the shader
	void setUniformBool(const std::string &name, bool val) const;
	void setUniformByte(const std::string &name, unsigned char val) const;
	void setUniformInt16(const std::string &name, int16_t val) const;
	void setUniformInt32(const std::string &name, int32_t val) const;
	void setUniformInt64(const std::string &name, int64_t val) const;
	void setUniformFloat(const std::string &name, float val) const;
	void setUniformDouble(const std::string &name, double val) const;
	void setUniformMat2(const std::string &name, const glm::mat2 &mat) const;
	void setUniformMat3(const std::string &name, const glm::mat3 &mat) const;
	void setUniformMat4(const std::string &name, const glm::mat4 &mat) const;
	void setUniformVec2(const std::string &name, const glm::vec2 &vec) const;
	void setUniformVec3(const std::string &name, const glm::vec3 &vec) const;
	void setUniformVec4(const std::string &name, const glm::vec4 &vec) const;
//	void setUniformTexture(const std::string &name, const) const;

	// used by the GameObjectFactory to check if the shader has already been made
	std::string getPathToVertexSource() const;
	std::string getPathToFragSource() const;
private:
	// reads the data from a shaderSource file(.vert of .frag)
	// returns the handl gl uses for the compiled shader either a vertex or fragmentshader
	unsigned int compileShader(const std::string &pathToShaderSource, GLenum shaderType) const;
	// links a vertex and fragment shader
	void buildProgram(const std::string &pathToVertexSource, const std::string &pathToFragmentSource);

	std::string pathToVertexSource_;
	std::string pathToFragSource_;
	// the handle used by gl
	unsigned int shaderProgram_;
};

#endif
