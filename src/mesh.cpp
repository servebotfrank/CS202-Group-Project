#include "mesh.hpp"

Mesh::Mesh(const std::string &pathToObj)
: vertices(0), indices(0), VAO{0}, VBO{0}, EBO{0} {
	loadMesh(pathToObj);
	loadToGLBuffers();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::loadMesh(const std::string &pathToObj) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	// load model data into tinyobj structures
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, pathToObj.c_str())) {
		throw std::runtime_error(err);
	}

	std::unordered_map<Vertex, uint32_t> uniqueVertices;

	for(const auto &shape : shapes) {
		for(const auto &index : shape.mesh.indices) {
			Vertex vertex = {};

			vertex.position = glm::vec3(
				attrib.vertices[static_cast<size_t>(3 * index.vertex_index + 0)],
				attrib.vertices[static_cast<size_t>(3 * index.vertex_index + 1)],
				attrib.vertices[static_cast<size_t>(3 * index.vertex_index + 2)]
			);
			// add normals, texture coordinates, or other per vertex data here

			// add only add unique verticies
			if(uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = vertices.size();
				vertices.push_back(vertex);
			}

			indices.push_back(uniqueVertices[vertex]);
		}
	}
}
void Mesh::loadToGLBuffers() {
	// create opengl array and buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the vertex array object
	glBindVertexArray(VAO);

	// set the vertex buffer object data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);

	// set the element buffer object data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices.front(), GL_STATIC_DRAW);

	// set attirbute 0 to be the vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// unbind vertex array
	glBindVertexArray(0);
}

unsigned int Mesh::getVAO() const {
	return VAO;
}
size_t Mesh::getVertexCount() const {
	return vertices.size();
}
size_t Mesh::getIndexCount() const {
	return indices.size();
}



