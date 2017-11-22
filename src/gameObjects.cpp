#include "gameObjects.hpp"

GameObject::GameObject(
	std::shared_ptr<Mesh> mesh,
	std::shared_ptr<Shader> shader,
	std::vector<double> elevation) :
	mesh_(mesh),
	shader_(shader),
	modelTransform_{},
	dynamicObject_{elevation} {}

GameObject::GameObject(
	const std::string &pathToObj,
	const std::string &pathToVertSource,
	const std::string &pathToFragSource,
	std::vector<double> elevation) :
	mesh_{std::make_shared<Mesh>(pathToObj)},
	shader_{std::make_shared<Shader>(pathToVertSource, pathToFragSource)},
	modelTransform_{},
	dynamicObject_{elevation} {}

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
glm::vec3 GameObject::getPosition() const {
	return glm::vec3(modelTransform_[3][0], modelTransform_[3][1], modelTransform_[3][2]);
}
void GameObject::setPosition(double xPos, double yPos) {
	modelTransform_[3][0] = xPos;
	modelTransform_[3][1] = yPos;
}
void GameObject::setUniformMat4(const std::string &name, const glm::mat4 &mat4) const {
	shader_->setUniformMat4(name, mat4);
}
const void* GameObject::getIndiciesData() const {
	return mesh_->getIndicesData();
}
void GameObject::setModelTransform(const glm::mat4 &transform) {
	modelTransform_ = transform;
}
void GameObject::translate(const glm::vec3 &difference) {
	modelTransform_ = glm::translate(modelTransform_, difference);
}
void GameObject::faceLeft() {
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(modelTransform_, scale, rotation, translation, skew, perspective);

	rotation = glm::conjugate(rotation);
	if(rotation.y > 0) {
		modelTransform_ = glm::rotate(modelTransform_, (float)M_PI, glm::vec3(0.0f, 1.0f, 0.0f));
	}
}
void GameObject::faceRight() {
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(modelTransform_, scale, rotation, translation, skew, perspective);

	rotation = glm::conjugate(rotation);
	if(rotation.y <= 0) {
		modelTransform_ = glm::rotate(modelTransform_, (float)M_PI, glm::vec3(0.0f, 1.0f, 0.0f));
	}
}
Dynamic_object& GameObject::getDynamicObject() {
	return dynamicObject_;
}





Platform::Platform(
	std::shared_ptr<Mesh> mesh,
	std::shared_ptr<Shader> shader,
	std::vector<double> elevation )
	: GameObject{mesh, shader, elevation} {}

Platform::Platform(
	const std::string &pathToObj,
	const std::string &pathToVertSource,
	const std::string &pathToFragSource,
	std::vector<double> elevation)
	: GameObject{pathToObj, pathToVertSource, pathToFragSource, elevation} {}


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

Player::Player(
	std::shared_ptr<Mesh> mesh,
	std::shared_ptr<Shader> shader,
	std::vector<double> elevation )
	: GameObject{mesh, shader, elevation} {}

Player::Player(
	const std::string &pathToObj,
	const std::string &pathToVertSource,
	const std::string &pathToFragSource,
	std::vector<double> elevation)
	: GameObject{pathToObj, pathToVertSource, pathToFragSource, elevation} {}

	
void Player::draw(const glm::mat4 &perspective, const glm::mat4 &view) const {
	glUseProgram(getShaderProgram());

	setUniformMat4("projection", perspective);
	setUniformMat4("view", view);
	setUniformMat4("model", getModelTransform());

	glBindVertexArray(getVAO());
	glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);
}
void Player::updatePhysics() {
	getDynamicObject().incrementPosition();
	setPosition(getDynamicObject().getXPosition(), getDynamicObject().getYPosition());
}
/*
void Player::updatePhysics(char &direction) {
	if(direction == 'r')
	{
			setModelTransform( glm::translate(getModelTransform(), glm::vec3(0.0f, 1.0f, 0.0f)) );
	} else if(direction == 'l')
	{
			setModelTransform( glm::translate(getModelTransform(), glm::vec3(0.0f, -1.0f, 0.0f)) );
	} else
	{}
	*/
