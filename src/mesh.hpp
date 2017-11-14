#ifndef MESH_H_P_P
#define MESH_H_P_P

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <GL/glew.h>

#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

struct Vertex {
	glm::vec3 position;

	bool operator==(const Vertex& rhs) const {
		return position == rhs.position;
	}
};

namespace std {
	template<> struct hash<Vertex> {
		size_t operator()(Vertex const& vertex) const {
			return (hash<glm::vec3>()(vertex.position));
		}
	};
}

struct Mesh {
	Mesh(const std::string &pathToObj);
	~Mesh();

	void loadMesh(const std::string &pathToObj);
	void loadToGLBuffers();

	unsigned int getVAO() const;
	size_t getVertexCount() const;
	size_t getIndexCount() const;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};

#endif


