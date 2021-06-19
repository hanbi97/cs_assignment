#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "common/shader.hpp"
#include "common/controls.hpp"
#include <iostream>

using namespace glm;
using namespace std;

#define G 9.8f
#define EPS 1e-8

GLFWwindow* window;
GLfloat *makeCircleVertexData(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides);
GLfloat *makeCylinderVertexData(GLfloat x, GLfloat y, GLfloat z, GLfloat height, GLfloat radius, GLint numberOfSides);
GLfloat *makeConeVertexData(GLfloat x, GLfloat y, GLfloat z, GLfloat height, GLfloat radius, GLint numberOfSides);

mat4 I = mat4(1.0f);
bool isRocketInitialized = false;
bool isFinished = false;
bool pstart = false;
glm::vec3 v(0.0f);
glm::vec3 tail(0.0f, 0.0f, 60.0f);
glm::vec3 direction(0.2f, 1.0f, 0.0f);
float alpha = 0.3f;
float beta = 0.01f;
float dt = 0.1f;

glm::mat4 getRotationMatrix(glm::vec3 direction) {
	direction = glm::normalize(direction);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 axis = cross(up, direction);

	float cosine_val = dot(direction, up);

	// parallel case
	if (cosine_val < -1 + EPS) {
		return eulerAngleYXZ(0.0f, radians(180.0f), 0.0f);
	}

	float s = sqrt((1 + cosine_val) * 2);
	float s_inv = 1 / s;

	return glm::mat4(quat(
		s * 0.5f,
		axis.x * s_inv,
		axis.y * s_inv,
		axis.z * s_inv
	));
}

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Rocket_12171607", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	//night skyy
	glClearColor(0.0f, 0.0f ,81.0f / 255.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	/*-----------arrays-----------*/
	//ground
	static const GLfloat ground_data[] = {
		-10000.0f,0.0f,10000.0f,
		10000.0f,0.0f,10000.0f,
		-10000.0f,0.0f,-10000.0f,

		10000.0f,0.0f,10000.0f,
		-10000.0f,0.0f,-10000.0f,
		10000.0f,0.0f,-10000.0f,

		10000.0f,0.0f,0.0f,
		-10000.0f,0.0f,0.0f,
		-10000.0f,-10000.0f,0.0f,

		10000.0f,0.0f,0.0f,
		-10000.0f,-10000.0f,0.0f,
		10000.0f,-10000.0f,0.0f
	};

	static const GLfloat ground_color_data[] = {
		26.0f / 255.0f, 121.0f / 255.0f, 19.0f / 255.0f,
		26.0f / 255.0f, 121.0f / 255.0f, 19.0f / 255.0f,
		26.0f / 255.0f, 121.0f / 255.0f, 19.0f / 255.0f,

		26.0f / 255.0f, 121.0f / 255.0f, 19.0f / 255.0f,
		26.0f / 255.0f, 121.0f / 255.0f, 19.0f / 255.0f,
		26.0f / 255.0f, 121.0f / 255.0f, 19.0f / 255.0f,

		26.0f / 255.0f, 121.0f / 255.0f, 19.0f / 255.0f,
		26.0f / 255.0f, 121.0f / 255.0f, 19.0f / 255.0f,
		26.0f / 255.0f, 121.0f / 255.0f, 19.0f / 255.0f,

		26.0f / 255.0f, 121.0f / 255.0f, 19.0f / 255.0f,
		26.0f / 255.0f, 121.0f / 255.0f, 19.0f / 255.0f,
		26.0f / 255.0f, 121.0f / 255.0f, 19.0f / 255.0f
	};

	//rocketbody
	GLfloat *cylinder_data = makeCylinderVertexData(0, 0, 60, 6, 2, 36);
	static  GLfloat cylinder_color_data[1296];
	for (int i = 0; i < 1296; i++) {
		cylinder_color_data[i] = 153.0 / 255.0f;
	}

	//rocketwing
	static const GLfloat wing_data[] = {
		2.0f, 3.0f, 60.0f,
		2.0f, 0.0f, 60.5f,
		4.0f, 0.0f, 60.0f,

		2.0f, 3.0f, 60.0f,
		2.0f, 0.0f, 59.5f,
		4.0f, 0.0f, 60.0f,

		-2.0f, 3.0f, 60.0f,
		-2.0f, 0.0f, 60.5f,
		-4.0f, 0.0f, 60.0f,

		-2.0f, 3.0f, 60.0f,
		-2.0f, 0.0f, 59.5f,
		-4.0f, 0.0f, 60.0f
	};
	static  GLfloat wing_color_data[36];
	for (int i = 0; i < 36; i++) {
		wing_color_data[i] = 99.0 / 255.0f;
	}

	//rockethead
	GLfloat *head_data = makeConeVertexData(0, 6, 60, 3, 2, 36);
	static GLfloat head_color_data[324];
	for (int i = 0; i < 324; i++) {
		head_color_data[i] = 116.0f / 255.0f;
	}

	//parachutebody
	GLfloat *parachutebody_data = makeConeVertexData(0, -9, 60, -5, 10, 36);
	static GLfloat parachutebody_color_data[324];
	for (int i = 0; i < 48; i++) {
		if (i % 3 == 0) {
			parachutebody_color_data[i] = 1.0f;
		}
		else if (i % 3 == 1) {
			parachutebody_color_data[i] = 0.0f;
		}
		else if (i % 3 == 2) {
			parachutebody_color_data[i] = 0.0f;
		}
	}
	for (int i = 48; i < 96; i++) {
		if (i % 3 == 0) {
			parachutebody_color_data[i] = 1.0f;
		}
		else if (i % 3 == 1) {
			parachutebody_color_data[i] = 94.0f / 255.0f;
		}
		else if (i % 3 == 2) {
			parachutebody_color_data[i] = 0.0f;
		}
	}
	for (int i = 96; i < 144; i++) {
		if (i % 3 == 0) {
			parachutebody_color_data[i] = 1.0f;
		}
		else if (i % 3 == 1) {
			parachutebody_color_data[i] = 228.0f / 255.0f;
		}
		else if (i % 3 == 2) {
			parachutebody_color_data[i] = 0.0f;
		}
	}
	for (int i = 144; i < 192; i++) {
		if (i % 3 == 0) {
			parachutebody_color_data[i] = 29.0f / 255.0f;
		}
		else if (i % 3 == 1) {
			parachutebody_color_data[i] = 219.0f / 255.0f;
		}
		else if (i % 3 == 2) {
			parachutebody_color_data[i] = 22.0f / 255.0f;
		}
	}
	for (int i = 192; i < 240; i++) {
		if (i % 3 == 0) {
			parachutebody_color_data[i] = 0.0f;
		}
		else if (i % 3 == 1) {
			parachutebody_color_data[i] = 84.0f / 255.0f;
		}
		else if (i % 3 == 2) {
			parachutebody_color_data[i] = 1.0f;
		}
	}
	for (int i = 240; i < 288; i++) {
		if (i % 3 == 0) {
			parachutebody_color_data[i] = 0.0f;
		}
		else if (i % 3 == 1) {
			parachutebody_color_data[i] = 0.0f;
		}
		else if (i % 3 == 2) {
			parachutebody_color_data[i] = 219.0f / 255.0f;
		}
	}
	for (int i = 288; i < 324; i++) {
		if (i % 3 == 0) {
			parachutebody_color_data[i] = 95.0f / 255.0f;
		}
		else if (i % 3 == 1) {
			parachutebody_color_data[i] = 0.0f;
		}
		else if (i % 3 == 2) {
			parachutebody_color_data[i] = 1.0f;
		}
	}

	//parachutelines
	GLfloat *parachuteline_data = makeConeVertexData(0, -9, 60, 10, 10, 36);
	static GLfloat parachuteline_color_data[324];
	
	//moon
	GLfloat *sun_data = makeCircleVertexData(-4, 55, 110, 4, 36);
	static GLfloat sun_color_data[37 * 3];
	for (int i = 0; i < 111; i++) {
		if (i % 3 == 0) {
			sun_color_data[i] = 250.0f / 255.0f;
		}
		else if (i % 3 == 1) {
			sun_color_data[i] = 237.0f / 255.0f;
		}
		else if (i % 3 == 2) {
			sun_color_data[i] = 125.0f / 255.0f;
		}
	}


	/*--------------------------------------------------------------------------*/
	GLuint ground;
	glGenBuffers(1, &ground);
	glBindBuffer(GL_ARRAY_BUFFER, ground);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ground_data), ground_data, GL_STATIC_DRAW);

	GLuint groundcolor;
	glGenBuffers(1, &groundcolor);
	glBindBuffer(GL_ARRAY_BUFFER, groundcolor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ground_color_data), ground_color_data, GL_STATIC_DRAW);

	GLuint rocketbody;
	glGenBuffers(1, &rocketbody);
	glBindBuffer(GL_ARRAY_BUFFER, rocketbody);
	glBufferData(GL_ARRAY_BUFFER, 36 * 18 * sizeof(GLfloat), cylinder_data, GL_STATIC_DRAW);

	GLuint rocketbodycolor;
	glGenBuffers(1, &rocketbodycolor);
	glBindBuffer(GL_ARRAY_BUFFER, rocketbodycolor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cylinder_color_data), cylinder_color_data, GL_STATIC_DRAW);

	GLuint rocketwing;
	glGenBuffers(1, &rocketwing);
	glBindBuffer(GL_ARRAY_BUFFER, rocketwing);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wing_data), wing_data, GL_STATIC_DRAW);

	GLuint rocketwingcolor;
	glGenBuffers(1, &rocketwingcolor);
	glBindBuffer(GL_ARRAY_BUFFER, rocketwingcolor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wing_color_data), wing_color_data, GL_STATIC_DRAW);

	GLuint rockethead;
	glGenBuffers(1, &rockethead);
	glBindBuffer(GL_ARRAY_BUFFER, rockethead);
	glBufferData(GL_ARRAY_BUFFER, 36 * 9 * sizeof(GLfloat), head_data, GL_STATIC_DRAW);

	GLuint rocketheadcolor;
	glGenBuffers(1, &rocketheadcolor);
	glBindBuffer(GL_ARRAY_BUFFER, rocketheadcolor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(head_color_data), head_color_data, GL_STATIC_DRAW);

	GLuint parachutebody;
	glGenBuffers(1, &parachutebody);
	glBindBuffer(GL_ARRAY_BUFFER, parachutebody);
	glBufferData(GL_ARRAY_BUFFER, 36 * 9 * sizeof(GLfloat), parachutebody_data, GL_STATIC_DRAW);

	GLuint parachutebodycolor;
	glGenBuffers(1, &parachutebodycolor);
	glBindBuffer(GL_ARRAY_BUFFER, parachutebodycolor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(parachutebody_color_data), parachutebody_color_data, GL_STATIC_DRAW);

	GLuint parachuteline;
	glGenBuffers(1, &parachuteline);
	glBindBuffer(GL_ARRAY_BUFFER, parachuteline);
	glBufferData(GL_ARRAY_BUFFER, 36 * 9 * sizeof(GLfloat), parachuteline_data, GL_STATIC_DRAW);

	GLuint parachutelinecolor;
	glGenBuffers(1, &parachutelinecolor);
	glBindBuffer(GL_ARRAY_BUFFER, parachutelinecolor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(parachuteline_color_data), parachuteline_color_data, GL_STATIC_DRAW);
	
	GLuint sun;
	glGenBuffers(1, &sun);
	glBindBuffer(GL_ARRAY_BUFFER, sun);
	glBufferData(GL_ARRAY_BUFFER, 37*3*sizeof(GLfloat), sun_data, GL_STATIC_DRAW);

	GLuint suncolor;
	glGenBuffers(1, &suncolor);
	glBindBuffer(GL_ARRAY_BUFFER, suncolor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sun_color_data), sun_color_data, GL_STATIC_DRAW);

	do {

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		glm::vec3 new_direction(direction);

		if (launched() && !isFinished) {
			if (!isRocketInitialized) {
				// initialization
				isRocketInitialized = true;
				direction = glm::normalize(direction);
				float energy = getEnergy();
				v = direction * energy * alpha;
			}

			// apply gravity
			v[1] -= G * beta;

			// move
			glm::vec3 dp = v * dt;
			tail += dp;
			glm::vec3 head = tail + direction * 6.0f;
			new_direction = glm::normalize(v);
	
			if (parachute()&&direction[1]<0) {
				pstart = true;
				v[1] -= (G * beta+0.1);
			}
			// finished
			if (head[1] <= 0) {
				float rollbackRatio = -1 * head[1] / dp[1];
				tail -= (v * dt) * rollbackRatio;
				v = glm::vec3(0.0f);
				head[1] = 0.0f;
				isFinished = true;
				setParachute(false);
			}
		}

		glm::mat4 Transform = translate(I, tail) * getRotationMatrix(direction);
		glm::mat4 Rocket = ProjectionMatrix * ViewMatrix * ModelMatrix * Transform;
		direction = new_direction;

		/*-----ground-------*/
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, ground);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, groundcolor);
		glVertexAttribPointer(
			1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, 2 * 3 * 2);

		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, sun);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, suncolor);
		glVertexAttribPointer(
			1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 37*3);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		/*-------------------------------------------------------------*/

		//rocket
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Rocket[0][0]);
		/*-----rockethead-----*/
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, rockethead);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, rocketheadcolor);
		glVertexAttribPointer(
			1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, 36 * 9);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		/*-------------------------------------------------------------*/

		/*-----body-------*/
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, rocketbody);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, rocketbodycolor);
		glVertexAttribPointer(
			1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 36 * 18 * 2); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		/*-------------------------------------------------------------*/

		/*------rocketwing-----------*/
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, rocketwing);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, rocketwingcolor);
		glVertexAttribPointer(
			1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, 3 * 4);

		glDisable(GL_CULL_FACE);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		/*-------------------------------------------------------------*/

		/*------------------------parachute--------------------------*/
		if (parachute()&&pstart) {
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, parachutebody);
			glVertexAttribPointer(
				0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, parachutebodycolor);
			glVertexAttribPointer(
				1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			glDrawArrays(GL_TRIANGLE_FAN, 0, 36 * 9);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, parachuteline);
			glVertexAttribPointer(
				0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, parachutelinecolor);
			glVertexAttribPointer(
				1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			glDrawArrays(GL_LINES, 0, 36 * 9);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
		}
		/*-----------------------------------------------------------*/

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteBuffers(1, &ground);
	glDeleteBuffers(1, &groundcolor);

	glDeleteBuffers(1, &rocketbody);
	glDeleteBuffers(1, &rocketbodycolor);

	glDeleteBuffers(1, &rocketwing);
	glDeleteBuffers(1, &rocketwingcolor);

	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
		glfwTerminate();
	
	return 0;
}

GLfloat *makeCircleVertexData(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides)
{
	GLint numberOfVertices = numberOfSides + 1;

	GLfloat doublePi = 2.0f * 3.141592f;

	GLfloat *circleVerticesX = new GLfloat[numberOfVertices];
	GLfloat *circleVerticesY = new GLfloat[numberOfVertices];
	GLfloat *circleVerticesZ = new GLfloat[numberOfVertices];

	for (int i = 0; i < numberOfVertices; i++)
	{
		circleVerticesX[i] = x + (radius * cos(i * doublePi / numberOfSides));
		circleVerticesY[i] = y + (radius * sin(i * doublePi / numberOfSides));
		circleVerticesZ[i] = z;
	}
	GLfloat *allCircleVertices = new GLfloat[numberOfVertices * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	return allCircleVertices;
}

GLfloat* makeConeVertexData(GLfloat x, GLfloat y, GLfloat z, GLfloat height, GLfloat radius, GLint numberOfSides) {
	GLint numberOfVertices = numberOfSides + 1;
	GLfloat doublePi = 2.0f * 3.141592f;
	GLfloat* circleVerticesX = new GLfloat[numberOfVertices * 3];
	GLfloat* circleVerticesY = new GLfloat[numberOfVertices * 3];
	GLfloat* circleVerticesZ = new GLfloat[numberOfVertices * 3];

	for (int i = 0; i < numberOfVertices; i++) {
		circleVerticesX[(i * 3) + 0] = x + (radius * cos(i * doublePi / numberOfSides));
		circleVerticesY[(i * 3) + 0] = y;
		circleVerticesZ[(i * 3) + 0] = z + (radius * sin(i * doublePi / numberOfSides));
		circleVerticesX[(i * 3) + 1] = x;
		circleVerticesY[(i * 3) + 1] = y + height;
		circleVerticesZ[(i * 3) + 1] = z;
		circleVerticesX[(i * 3) + 2] = x + (radius * cos((i + 1) * doublePi / numberOfSides));
		circleVerticesY[(i * 3) + 2] = y;
		circleVerticesZ[(i * 3) + 2] = z + (radius * sin((i + 1) * doublePi / numberOfSides));
	}
	GLfloat * allCylinderVertices = new GLfloat[numberOfVertices * 9];

	for (int i = 0; i < numberOfVertices * 3; i++) {
		allCylinderVertices[(i * 3) + 0] = circleVerticesX[i];
		allCylinderVertices[(i * 3) + 1] = circleVerticesY[i];
		allCylinderVertices[(i * 3) + 2] = circleVerticesZ[i];
	}
	return allCylinderVertices;
}
GLfloat *makeCylinderVertexData(GLfloat x, GLfloat y, GLfloat z, GLfloat height, GLfloat radius, GLint numberOfSides)
{
	GLint numberOfVertices = numberOfSides;

	GLfloat doublePi = 2.0f * 3.141592f;

	GLfloat *circleVerticesX = new GLfloat[numberOfVertices * 6];
	GLfloat *circleVerticesY = new GLfloat[numberOfVertices * 6];
	GLfloat *circleVerticesZ = new GLfloat[numberOfVertices * 6];

	for (int i = 0; i < numberOfVertices; i++)
	{
		circleVerticesX[(i * 6)] = x + (radius * cos(i * doublePi / numberOfSides));
		circleVerticesY[(i * 6)] = y;
		circleVerticesZ[(i * 6)] = z + (radius * sin(i * doublePi / numberOfSides));

		circleVerticesX[(i * 6) + 1] = x + (radius * cos((i + 1) * doublePi / numberOfSides));
		circleVerticesY[(i * 6) + 1] = y;
		circleVerticesZ[(i * 6) + 1] = z + (radius * sin((i + 1) * doublePi / numberOfSides));

		circleVerticesX[(i * 6) + 2] = x + (radius * cos(i * doublePi / numberOfSides));
		circleVerticesY[(i * 6) + 2] = y + height;
		circleVerticesZ[(i * 6) + 2] = z + (radius * sin(i * doublePi / numberOfSides));

		circleVerticesX[(i * 6) + 3] = x + (radius * cos(i * doublePi / numberOfSides));
		circleVerticesY[(i * 6) + 3] = y + height;
		circleVerticesZ[(i * 6) + 3] = z + (radius * sin(i * doublePi / numberOfSides));

		circleVerticesX[(i * 6) + 4] = x + (radius * cos((i + 1) * doublePi / numberOfSides));
		circleVerticesY[(i * 6) + 4] = y + height;
		circleVerticesZ[(i * 6) + 4] = z + (radius * sin((i + 1) * doublePi / numberOfSides));

		circleVerticesX[(i * 6) + 5] = x + (radius * cos((i + 1) * doublePi / numberOfSides));
		circleVerticesY[(i * 6) + 5] = y;
		circleVerticesZ[(i * 6) + 5] = z + (radius * sin((i + 1) * doublePi / numberOfSides));
	}
	GLfloat *allCircleVertices = new GLfloat[numberOfVertices * 18];

	for (int i = 0; i < numberOfVertices * 6; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	return allCircleVertices;
}