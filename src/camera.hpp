#ifndef CAMERA_H_P_P
#define CAMERA_H_P_P

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 getView() const;
private:
	glm::vec3 position_;
	glm::vec3 up_;
	glm::vec3 right_;
	glm::vec3 front_;
	float yaw_;
	float pitch_;
	float roll_;
};


#endif
