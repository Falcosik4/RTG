#pragma once


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "scene_object.hpp"

class Camera : public SceneObject {
public:
	Camera(float aspectRatio, float fov=45.0f, float nearPlane=0.01f, float farPlane=1000.0f)
		: SceneObject(), fov(fov), aspectRatio(aspectRatio), nearPlane(nearPlane), farPlane(farPlane) {}

	void setAspectRatio(float aAspectRatio) {
		aspectRatio = aAspectRatio;
	}

	glm::mat4 getViewMatrix() const {
		// Convert quaternion rotation to rotation matrix
		glm::mat4 rotationMat = glm::toMat4(glm::inverse(rotation));
		glm::mat4 view = rotationMat * glm::translate(glm::mat4(1.0f), position);
		return view;
	}

	glm::mat4 getProjectionMatrix() const {
		return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	}

	void lookAt(const glm::vec3& target, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f)) {
		std::cout << "--------------------------\n";
		printInfo(std::cout);
		std::cout << "++++++++++++++++++++++++++\n";
		glm::vec3 direction = glm::normalize(position - target);
		// Create a look at quaternion
		rotation = glm::quatLookAt(direction, up);
		printInfo(std::cout);
	}

	void orbit(const glm::vec2 &aAngles, const glm::vec3 aOrigin) {
		{
			glm::vec3 axis = getUpVector();

			float angle = glm::radians(aAngles.x);
			glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
			glm::vec4 newPos = rotationMatrix * glm::vec4(position, 1.0);

			std::cout << "--------------------------\n";
			printInfo(std::cout);
			std::cout << "++++++++++++++++++++++++++\n";

			position = newPos.xyz();
			lookAt(aOrigin, getUpVector());
		}
		{
			glm::vec3 axis = getRightVector();

			float angle = glm::radians(aAngles.y);
			glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
			glm::vec4 newPos = rotationMatrix * glm::vec4(position, 1.0);

			std::cout << "--------------------------\n";
			printInfo(std::cout);
			std::cout << "++++++++++++++++++++++++++\n";

			position = newPos.xyz();
			lookAt(aOrigin, getUpVector());
		}


		printInfo(std::cout);
	}

private:
	float fov;          // Field of view in radians
	float aspectRatio;  // Aspect ratio of the viewport
	float nearPlane;    // Near clipping plane
	float farPlane;     // Far clipping plane
};