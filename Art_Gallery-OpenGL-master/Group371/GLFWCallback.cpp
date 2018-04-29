#include "GLFWCallback.h"

GLFWCallback::GLFWCallback() {
};

GLFWCallback::~GLFWCallback() {
	
};

void GLFWCallback::setLastWindowSize(int width, int height) {
	this->lastWidth = width;
	this->lastHeight = height;
}

void GLFWCallback::setSharedData(SharedData* sharedData) {
	this->sharedData = sharedData;
}

void GLFWCallback::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	//toggles
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_LEFT_CONTROL: { ctrlPressed = true; break; }
		}
	}
	if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_LEFT_CONTROL: { ctrlPressed = false; break; }
		case GLFW_KEY_B: { sharedData->camera->debugModeEnabled = !sharedData->camera->debugModeEnabled; break; }
		}
	}

	if (action == GLFW_RELEASE || action == GLFW_REPEAT) {
		switch (key) {
			// wasd controls to move around, and r/f to fly up/down
			case GLFW_KEY_W: { sharedData->camera->moveForward(!ctrlPressed); break; }
			case GLFW_KEY_A: { sharedData->camera->moveLeft(!ctrlPressed); break; }
			case GLFW_KEY_S: { sharedData->camera->moveBackward(!ctrlPressed); break; }
			case GLFW_KEY_D: { sharedData->camera->moveRight(!ctrlPressed); break; }
			case GLFW_KEY_R: { sharedData->camera->moveUp(!ctrlPressed); break; }
			case GLFW_KEY_F: { sharedData->camera->moveDown(!ctrlPressed); break; }
			case GLFW_KEY_ESCAPE: { glfwSetWindowShouldClose(window, GL_TRUE); break; }
			default: { break; }
		}
	}
};

void GLFWCallback::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	lastMouseXpos = xpos;
	lastMouseYpos = ypos;
	sharedData->camera->updateMouse(glm::vec2(xpos, ypos));
};

void GLFWCallback::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {};

void GLFWCallback::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {};

void GLFWCallback::window_resize_callback(GLFWwindow* window, int width, int height) {
	// Update the viewport to the new width and height
	glViewport(0, 0, width, height);
	lastWidth = width;
	lastHeight = height;
	// Update the width/height aspect ratio to new width and height
	sharedData->transform->projection = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
};


