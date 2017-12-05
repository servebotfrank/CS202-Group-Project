#ifndef CAMERA_H_P_P
#define CAMERA_H_P_P

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	// constructor for the camera Class, initializes data members in the 
	// initializer list
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f));

	// returns a 4x4 matrix that is used in the vertex shader
	// the matrix is used for the transformation from world space to view space
	glm::mat4 getView() const;

	// gets the position of the camera
	glm::vec3 getPosition() const;

	// sets the position of the camera - used in the main event loop and is 
	// used to have the camera follow the player
	void setPosition(const glm::vec3 &newPosition);
private:
	// data members 		initialized to
	glm::vec3 position_; // pos
	glm::vec3 up_; 		 // 0.0f,1.0f,0.0f 		y axis
	glm::vec3 right_; 	 // 1.0f,0.0f,0.0f 		x axis 	not used
	glm::vec3 front_;	 // 0.0f,0.0f,-1.0f 	z axis into the screen
	float yaw_; 		 // -90 	not used
	float pitch_; 		 // 0 		not used
	float roll_; 		 // 0 		not used
};


#endif
