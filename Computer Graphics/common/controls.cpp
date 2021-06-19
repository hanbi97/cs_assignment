#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "controls.hpp"

#define CRITERIA 40
extern GLFWwindow* window;
extern bool isFinished;
extern glm::vec3 v;


using namespace glm;
using namespace std;

bool isParachute = false;
bool isPressed = false;
bool isLaunched = false;
bool isRestart = false;
float energy = 0.0;

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::mat4 getViewMatrix() {
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}
// Initial position : on +Z
glm::vec3 position = glm::vec3(38, 3, 200);
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.2f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

bool parachute() {
	return isParachute;
}

bool launched() {
	return isLaunched;
}
bool getRestart() {
	return isRestart;
}
float getEnergy() {
	return energy;
}


void setParachute(bool p) {
	isParachute = p;
}

void computeMatricesFromInputs() {

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * float(768 / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 origindirection(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, origindirection);

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		position += origindirection * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= origindirection * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
	}
	
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		isPressed = true;
		energy += 0.2;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE) {
		if (isPressed == true) {
			isLaunched = true;
			if (energy < CRITERIA) {
				isParachute = false;
			}
			else if (energy >= CRITERIA) {
				isParachute = true;
				if (energy > 45) {
					energy = 45;
				}
			}
		}
	}
	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

						   // Projection matrix : 45?Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

	if (isLaunched && !isFinished &&isParachute==true) {
		verticalAngle = 0.8f;
		position = vec3(41, 13, 170);
	}
	else if (isLaunched && isFinished&&isParachute) {
		verticalAngle = 0.2f;
		position = vec3(80, 3, 200);
	}
	else if (isLaunched && isFinished&&!isParachute) {
		verticalAngle = 0.2f;
		position = vec3(38, 3, 200);
	}
	// Camera matrix
		ViewMatrix = glm::lookAt(
			position,           // Camera is here
			position + origindirection, // and looks here : at the same position, plus "direction"
			up                  // Head is up (set to 0,-1,0 to look upside-down)
		);
	
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}



