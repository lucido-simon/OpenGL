
#include "glm/glm.hpp"


class Camera
{
protected:

	glm::vec3 position;
	glm::vec3 rotation;

	glm::mat4 cameraMatrix;


public:

	Camera();

	void computeViewMatrix();
	void computeViewMatrix(glm::vec3& position, glm::vec3& rotation);

	glm::mat4 getViewMatrix();
	glm::mat4 getViewMatrix(glm::vec3& position, glm::vec3& rotation);

	void translate(const glm::vec3& vector);
	void rotate(const glm::vec3& vector);

	void setPosition(const glm::vec3& vector);
	void setRotation(const glm::vec3& vector);

};

