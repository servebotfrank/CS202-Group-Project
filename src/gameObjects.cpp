#include "gameObjects.hpp"

GameObject::GameObject(
	std::shared_ptr<Mesh> mesh,
	std::shared_ptr<Shader> shader,
	const glm::vec3 &initialPosition,
	std::shared_ptr<std::vector<double>> elevations) :
	mesh_(mesh),
	shader_(shader),
	modelTransform_{},
	dynamicObject_{glm::vec2(initialPosition[0], initialPosition[1]), elevations},
	width_{1}, height_{1} {
	setPosition(initialPosition);
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
void GameObject::setUniformVec3(const std::string &name, const glm::vec3 &vec3) const {
	shader_->setUniformVec3(name, vec3);
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

glm::vec3 GameObject::getPosition() const {
	return glm::vec3(modelTransform_[3][0], modelTransform_[3][1], modelTransform_[3][2]);
}
float GameObject::getXPosition() const {
	return modelTransform_[3][0];
}
float GameObject::getYPosition() const {
	return modelTransform_[3][1];
}
float GameObject::getZPosition() const {
	return modelTransform_[3][2];
}
void GameObject::setPosition(double xPos, double yPos) {
	modelTransform_[3][0] = xPos;
	modelTransform_[3][1] = yPos;
}
void GameObject::setPosition(const glm::vec3 &position) {
	modelTransform_[3][0] = position[0];
	modelTransform_[3][1] = position[1];
	modelTransform_[3][2] = position[2];
}
float GameObject::getWidth() const {
	return width_;
}
void GameObject::setWidth(float width) {
	width_ = width;
}
float GameObject::getHeight() const {
	return height_;
}
void GameObject::setHeight(float height) {
	height_ = height;
}

void GameObject::setCollisionTarget(const std::shared_ptr<GameObject> &collidingWith) {
	collidingWith_ = collidingWith;
	isColliding_ = true;
}
void GameObject::setCollision(bool isColliding) {
	isColliding_ = isColliding;
}
std::shared_ptr<GameObject> GameObject::getCollisionTarget() const {
	return collidingWith_;
}
bool GameObject::getCollisionState() const {
	return isColliding_;
}

void GameObject::faceLeft() {
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	// extracts information from the 4x4 modelTransform_ data member
	glm::decompose(modelTransform_, scale, rotation, translation, skew, perspective);

	rotation = glm::conjugate(rotation);
	if(rotation.y >= 0) {
		// rotate the model about the y axis(vertical axis) by pi radians(180 deg)
		modelTransform_ = glm::rotate(modelTransform_, (float)M_PI, glm::vec3(0.0f, 1.0f, 0.0f));
	}
}
void GameObject::faceRight() {
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	// extracts information from the 4x4 modelTransform_ data member
	glm::decompose(modelTransform_, scale, rotation, translation, skew, perspective);

	rotation = glm::conjugate(rotation);
	if(rotation.y < 0) {
		// rotate the model about the y axis(vertical axis) by pi radians(180 deg)
		modelTransform_ = glm::rotate(modelTransform_, (float)M_PI, glm::vec3(0.0f, 1.0f, 0.0f));
	}
}
bool GameObject::getDirection() {
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	// extracts information from the 4x4 modelTransform_ data member
	glm::decompose(modelTransform_, scale, rotation, translation, skew, perspective);

	rotation = glm::conjugate(rotation);
	if(rotation.y >= 0) {
		return true;
	}
	return false;
}
Dynamic_object& GameObject::getDynamicObject() {
	return dynamicObject_;
}






Platform::Platform(
	std::shared_ptr<Mesh> mesh,
	std::shared_ptr<Shader> shader,
	const glm::vec3 &initialPosition,
	std::shared_ptr<std::vector<double>> elevations)
	: GameObject{mesh, shader, initialPosition, elevations} {}

void Platform::draw(const glm::mat4 &perspective, const glm::mat4 &view, const sf::Time &elapsed) const {
	// tells opengl to use the shader program stored in the GameObject base class there is also a pointer to it in GameObject factory
	glUseProgram(getShaderProgram());

	// the viewport transform is built into gl which transforms from
	// clip space to screen space
	// transforms the vertices from view space to clip space
	setUniformMat4("projection", perspective);
	// transforms the vertices from world space to view space
	setUniformMat4("view", view);
	// transforms the vertices from local space to world space
	setUniformMat4("model", getModelTransform());

	// sets the color to grey/green
	setUniformVec3("color", glm::vec3(0.1f, 0.2f, 0.2f));

	// tells gl to use this objects mesh's vertex array object
	glBindVertexArray(getVAO());
	// tells gl to draw the vertex array object using the corrispoding index buffer
	glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);
}
void Platform::updatePhysics() {

}
std::string Platform::getDescription() const {
	return "Platform";
}
GameObjectTypes Platform::getType() const {
	return GameObjectTypes::PLATFORM;
}




Player::Player(
	std::shared_ptr<Mesh> mesh,
	std::shared_ptr<Shader> shader,
	const glm::vec3 &initialPosition,
	std::shared_ptr<std::vector<double>> elevations)
	: GameObject{mesh, shader, initialPosition, elevations} {}

void Player::draw(const glm::mat4 &perspective, const glm::mat4 &view, const sf::Time &elapsed) const {
	glUseProgram(getShaderProgram());

	setUniformMat4("projection", perspective);
	setUniformMat4("view", view);
	setUniformMat4("model", getModelTransform());

	setUniformVec3("color", glm::vec3(0.2f, 0.3f, 0.9f));

	glBindVertexArray(getVAO());
	glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);
}
void Player::updatePhysics() {
	getDynamicObject().incrementPosition(getCollisionState(), getCollisionTarget());
	setPosition(getDynamicObject().getXPosition(), getDynamicObject().getYPosition());
}
std::string Player::getDescription() const {
	return "Player";
}
GameObjectTypes Player::getType() const {
	return GameObjectTypes::PLAYER;
}






Enemy::Enemy(
	std::shared_ptr<Mesh> mesh,
	std::shared_ptr<Shader> shader,
	const glm::vec3 &initialPosition,
	std::shared_ptr<std::vector<double>> elevations)
	: GameObject{mesh, shader, initialPosition, elevations} {}

void Enemy::draw(const glm::mat4 &perspective, const glm::mat4 &view, const sf::Time &elapsed) const {
	glUseProgram(getShaderProgram());

	setUniformMat4("projection", perspective);
	setUniformMat4("view", view);
	setUniformMat4("model", getModelTransform());

	float red = sin(elapsed.asSeconds()/0.5f)/2.0 + 0.5f;
	setUniformVec3("color", glm::vec3(red, 0.0f, 0.0f));

	glBindVertexArray(getVAO());
	glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);
}
void Enemy::updatePhysics() {

}
std::string Enemy::getDescription() const {
	return "enemy";
}
GameObjectTypes Enemy::getType() const {
	return GameObjectTypes::ENEMY;
}

