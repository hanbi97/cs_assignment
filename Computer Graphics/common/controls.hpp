#ifndef CONTROLS_HPP
#define CONTROLS_HPP

bool parachute();
bool launched();
bool getRestart();
void setParachute(bool);
float getEnergy();
void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif