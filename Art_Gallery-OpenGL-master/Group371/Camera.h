#ifndef CAMERA_H
#define CAMERA_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "RoomGen.h"
#include <vector>
#include <Windows.h>
#include <mmsystem.h>

// Camera parameters for a perspective camera
struct PerspectiveCameraParams {
	float yFov;
	float aspectRatio;
	float zNearPlane;
	float zFarPlane;
};

class Camera {
public:
	Camera(); // defaults to perspective
	Camera(PerspectiveCameraParams params);
	~Camera();

	// The camera's movement speed when moving through the world
	static const float CAMERA_SPEED;
	// The camera's rotation speed when moving around the mouse
	static const float LOOK_AROUND_SPEED;
	// The camera's fixed height of the player
	static const float HEIGHT;
	// The camera's speed boost when in no-clip mode.
	static const float SPEED_BOOST;

	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();

	// Set the camera's current position in the world
	void setPosition(glm::vec3 position);
	// Move toward the camera's view direction
	void moveForward(bool checkCollision);
	// Move away the camera's view direction
	void moveBackward(bool checkCollision);
	// Move toward the camera's strafe direction. Strafe left from the view direction
	void moveLeft(bool checkCollision);
	// Move away the camera's strafe direction. Strafe right from the view direction
	void moveRight(bool checkCollision);
	// Move toward the camera's up direction. Flys up.
	void moveUp(bool checkCollision);
	// Move away from the camera's up direction. Flys down.
	void moveDown(bool checkCollision);
	// Update camera's positions of the the mouse's current position on the screen
	void updateMouse(glm::vec2&);
	// The current position of where the camera is placed in this world
	const glm::vec3& getCameraPosition() const;
	// Plays footstep noise
	void playFootSteps(bool checkCollision);
	
	//collision boxes to check for collision detection
	std::vector<BoundingBox> collision_boxes;
	//show debug grid
	bool debugModeEnabled = false;

private:
	void init(PerspectiveCameraParams params);

	glm::vec3 checkCollisions(glm::vec3 direction);
	// The current params for our camera
	PerspectiveCameraParams cameraParams;
	// The old positions of the mouse cursor
	glm::vec2 oldMousePos;
	// The current position of our camera in the world
	glm::vec3 position;
	// the directon the camera is looking at
	glm::vec3 viewDirection;
	// the direction perpendicular to the viewDirecton
	glm::vec3 strafeDirection; 
	// the direction that is perpendicular to both the view and strafe direction
	glm::vec3 upDirection;
	
};

#endif // !CAMERA_H