#include "Camera.h"

// TODO: fiddle around with these values until it feels nice
const float Camera::CAMERA_SPEED = 0.15f;
const float Camera::LOOK_AROUND_SPEED = 0.0025f;
const float Camera::HEIGHT = -RoomGen::ROOM_HEIGHT / 2.0f + 0.8225f;
const float Camera::SPEED_BOOST = 3.5f;

Camera::Camera() {
	PerspectiveCameraParams defaultParams;
	defaultParams.yFov = 45.0f;
	defaultParams.aspectRatio = 1;
	defaultParams.zNearPlane = 0.1f;
	defaultParams.zFarPlane = 100.0f;
	init(defaultParams);
}

Camera::Camera(PerspectiveCameraParams params) {
	init(params);
}

Camera::~Camera() {

}

void Camera::init(PerspectiveCameraParams params) {
	cameraParams = params;
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
	strafeDirection = glm::cross(viewDirection, upDirection);
}

glm::mat4 Camera::getProjectionMatrix() {
	return glm::perspective(cameraParams.yFov, cameraParams.aspectRatio, cameraParams.zNearPlane, cameraParams.zFarPlane);
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + viewDirection, upDirection);
}

void Camera::setPosition(glm::vec3 position) {
	this->position = position;
}

void Camera::moveForward(bool checkCollision) {
	playFootSteps(checkCollision);
	
	glm::vec3 dir = CAMERA_SPEED * glm::vec3(viewDirection.x, !checkCollision ? viewDirection.y : 0, viewDirection.z);
	position += checkCollision ? checkCollisions(dir) : dir*SPEED_BOOST;
	if (checkCollision) {
		position.y = HEIGHT;
	}
}

void Camera::moveBackward(bool checkCollision) {
	playFootSteps(checkCollision);
	glm::vec3 dir = CAMERA_SPEED * -glm::vec3(viewDirection.x, !checkCollision ? viewDirection.y : 0, viewDirection.z);
	position += checkCollision ? checkCollisions(dir) : dir*SPEED_BOOST;
	if (checkCollision) {
		position.y = HEIGHT;
	}
}

void Camera::moveLeft(bool checkCollision) {
	playFootSteps(checkCollision);
	glm::vec3 dir = CAMERA_SPEED * -strafeDirection;
	position += checkCollision ? checkCollisions(dir) : dir*SPEED_BOOST;
}

void Camera::moveRight(bool checkCollision) {
	playFootSteps(checkCollision);
	glm::vec3 dir = CAMERA_SPEED * strafeDirection;
	position += checkCollision ? checkCollisions(dir) : dir*SPEED_BOOST;
}
void Camera::moveUp(bool checkCollision) {
	glm::vec3 dir = CAMERA_SPEED * upDirection;
	position += checkCollision ? checkCollisions(dir) : dir*SPEED_BOOST;
}

void Camera::moveDown(bool checkCollision) {
	glm::vec3 dir = CAMERA_SPEED * -upDirection;
	position += checkCollision ? checkCollisions(dir) : dir*SPEED_BOOST;
}

void Camera::updateMouse(glm::vec2& newPos) {
	glm::vec2 mouseDelta = newPos - oldMousePos;
	strafeDirection = glm::cross(viewDirection, upDirection);
	glm::mat4 rotationXY = glm::rotate(glm::mat4(), -mouseDelta.x * LOOK_AROUND_SPEED, upDirection) * glm::rotate(glm::mat4(), -mouseDelta.y * LOOK_AROUND_SPEED, strafeDirection);
	viewDirection = glm::mat3(rotationXY) * viewDirection;
	oldMousePos = newPos;
}

const glm::vec3& Camera::getCameraPosition() const {
	return position;
}

glm::vec3 Camera::checkCollisions(glm::vec3 direction) {
	glm::vec3 newPos = position + direction;
	for (BoundingBox box : collision_boxes) {
		if ((newPos.x >= box.min.x && newPos.x <= box.max.x) &&
			(newPos.y >= box.min.y && newPos.y <= box.max.y) &&
			(newPos.z >= box.min.z && newPos.z <= box.max.z))
		{
			if (box.max.x < position.x || box.min.x > position.x) {
				direction.x = 0;
			}
			else if (box.max.z < position.z || box.min.z > position.z) {
				direction.z = 0;
			}
			else if (box.max.y < position.y || box.min.y > position.y) {
				direction.y = 0;
			}
		}
	}

	return direction;
}

void Camera::playFootSteps(bool checkCollision){ 
	if (!checkCollision)
		return;
	else if ((fmod(glfwGetTime(), 1) > 2 && fmod(glfwGetTime(), 1) < 0.24) || (fmod(glfwGetTime(), 1) > 0.73 && fmod(glfwGetTime(), 1) < 0.77))
		PlaySound(TEXT("footstep.wav"), NULL, SND_ASYNC | SND_FILENAME);
}