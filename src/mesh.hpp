#ifndef MESH_H_P_P
#define MESH_H_P_P

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>


#ifdef __linux__
	#include <GL/glew.h>
	#include <SFML/OpenGL.hpp>
#else
	#include <OpenGL/gl3.h>
#endif


#include <SFML/System.hpp>

// while using clang - error "GLM_GTX_hash requires C++11 standard librar...
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

struct Vertex {
	glm::vec3 position;

	// used in loadMesh to make sure only unique vertices are used
	bool operator==(const Vertex& rhs) const {
		return position == rhs.position;
	}
};

// used in loadMesh to make sure only vertices meshes are used
namespace std {
	template<> struct hash<Vertex> {
		size_t operator()(Vertex const& vertex) const {
			return (hash<glm::vec3>()(vertex.position));
		}
	};
}

class Mesh {
public:
	// calls loadMesh
	Mesh(const std::string &pathToObj);
	// frees the graphics memory
	~Mesh();

	// uses tiny_obj_loader to extract the vertex position and index data
	void loadMesh(const std::string &pathToObj);
	// takes the extracted vertex positions and index positions and loads them into
	// graphic memory
	void loadToGLBuffers();

	// returns the handle opengl uses to the vertex array object
	unsigned int getVAO() const;
	size_t getVertexCount() const;
	// used in glDrawElements to draw that many vertices
	size_t getIndexCount() const;
	// returns a void*(because that is what opengl wants) to the first index
	const void* getIndicesData() const;

	// used in gameObjectfactory to make see if the path has aleady been used
	std::string getPathToModel() const;
private:
	std::string pathToModel_;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	// vertex array object
	unsigned int VAO;
	// vertex buffer object stores the postitions
	unsigned int VBO;
	// element buffer object stores the indices
	unsigned int EBO;
};

#endif


