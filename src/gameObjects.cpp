#include "gameObjects.hpp"

GameObject::GameObject(
	const std::string &pathToObj,
	const std::string &pathToVertSource,
	const std::string &pathToFragSource) : modelTransform_{} {

	mesh_ = std::make_unique<Mesh>(pathToObj);
	shader_ = std::make_unique<Shader>(pathToVertSource, pathToFragSource);
}
unsigned int GameObject::getShaderProgram() const {
	return shader_->getShaderProgram();
}
unsigned int GameObject::getVAO() const {
	return mesh_->getVAO();
}
size_t GameObject::getVertexCount() const {
	return mesh_->getVertexCount();
}
size_t GameObject::getIndexCount() const {
	return mesh_->getIndexCount();
}
glm::mat4 GameObject::getModelTransform() const {
	return modelTransform_;
}
void GameObject::setUniformMat4(const std::string &name, const glm::mat4 &mat4) const {
	shader_->setUniformMat4(name, mat4);
}
void* GameObject::getIndiciesData() const {
	return mesh_->indices.data();
}
void GameObject::setModelTransform(const glm::mat4 &transform) {
	modelTransform_ = transform;
}


Platform::Platform(
	const std::string &pathToObj,
	const std::string &pathToVertSource,
	const std::string &pathToFragSource)
	: GameObject{pathToObj, pathToVertSource, pathToFragSource} {

}
void Platform::draw(const glm::mat4 &perspective, const glm::mat4 &view) const {
	glUseProgram(getShaderProgram());
	setUniformMat4("projection", perspective);
	setUniformMat4("view", view);
	setUniformMat4("model", getModelTransform());

	glBindVertexArray(getVAO());
	glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);
}
void Platform::updatePhysics() {
	setModelTransform( glm::rotate(getModelTransform(), (float)std::exp(-6), glm::vec3(0.0f, 1.0f, 0.0f)) );
}

