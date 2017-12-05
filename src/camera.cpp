#include "camera.hpp"

Camera::Camera(glm::vec3 pos) : position_{pos}, up_{0.0f,1.0f,0.0f}, right_{1.0f,0.0f,0.0f}, front_{0.0f,0.0f,-1.0f}, yaw_{-90.0f}, pitch_{0.0f}, roll_{0.0f} {

}

glm::mat4 Camera::getView() const {
	return glm::lookAt(position_, position_ + front_, up_);
}

glm::vec3 Camera::getPosition() const {
	return position_;
}

void Camera::setPosition(const glm::vec3 &newPosition) {
	position_ = newPosition;
}
