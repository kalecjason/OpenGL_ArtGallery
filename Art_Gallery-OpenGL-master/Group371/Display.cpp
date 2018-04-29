#include "Display.h"
#include "RoomGen.h"
#include "Painting.h"


Display::Display(std::string title, int width, int height) {
	initGL(title, width, height);
	initGLBuffers();
	initTextures();
	initSharedData();
	initCamera();
	initDebugMeshes();

	std::vector<BoundingBox> boxes;

	RoomGen rooms(&lights);
	meshManager.addMesh(&rooms);
	glm::vec3 roomPos = rooms.getRandomRoomPosition();
	roomPos.y = Camera::HEIGHT;
	sharedData.camera->setPosition(roomPos);
	for (BoundingBox box : rooms.getBoundingBox()) {
		boxes.push_back(box);
	}

	sharedData.camera->collision_boxes = boxes;
	meshManager.computeMergedMesh();
}


Display::~Display() {
	//delete buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &DEBUG_VBO);
	glDeleteBuffers(1, &DEBUG_EBO);
	delete debugShader;
	
	glfwTerminate();
}

void Display::update() {

	// poll events from kb/mouse or other inputs
	glfwPollEvents();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// clear color buffer and depth
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Update the view matrix
	sharedData.transform->view = sharedData.camera->getViewMatrix();

	glBindVertexArray(VAO);
	
	if(sharedData.camera->debugModeEnabled)
		debugUpdate();


	// Pass our uniform data
	// Compute the cmt transform and pass to our shader
	glm::vec3 cameraPos = camera.getCameraPosition();

	



	shader->Use();
	glUniformMatrix4fv(transformUniform, 1, GL_FALSE, value_ptr(sharedData.transform->getTransform()));
	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, value_ptr(sharedData.transform->model));
	glUniform3f(cameraPositionUniform, cameraPos.x, cameraPos.y, cameraPos.z);

	sortNearest(lights, cameraPos);
	
	// Pass lights
	int fragmentLightIndex = 0;
	for (int i = 0; i < lights.size(); ++i) {
		// TODO filter out lights we dont need
		Light& light = lights[i];
		if (fragmentLightIndex > maxLights) {
			break; // We've reached  max lights in our shader
		}
		//if (abs(glm::distance(light.position , cameraPos)) < maxLightDistance) {
			glUniform3f(glGetUniformLocation(shader->Program, std::string("lights[").append(std::to_string(fragmentLightIndex) + "].position").c_str()), light.position.x, light.position.y, light.position.z);
			glUniform3f(glGetUniformLocation(shader->Program, std::string("lights[").append(std::to_string(fragmentLightIndex) + "].ambient").c_str()), light.ambient.r, light.ambient.g, light.ambient.b);
			glUniform3f(glGetUniformLocation(shader->Program, std::string("lights[").append(std::to_string(fragmentLightIndex) + "].diffuse").c_str()), light.diffuse.r, light.diffuse.g, light.diffuse.b);
			glUniform3f(glGetUniformLocation(shader->Program, std::string("lights[").append(std::to_string(fragmentLightIndex) + "].specular").c_str()), light.specular.r, light.specular.g, light.specular.b);
			glUniform3f(glGetUniformLocation(shader->Program, std::string("lights[").append(std::to_string(fragmentLightIndex) + "].position").c_str()), light.position.x, light.position.y, light.position.z);
			glUniform1f(glGetUniformLocation(shader->Program, std::string("lights[").append(std::to_string(fragmentLightIndex) + "].constant").c_str()), light.constant);
			glUniform1f(glGetUniformLocation(shader->Program, std::string("lights[").append(std::to_string(fragmentLightIndex) + "].linear").c_str()), light.linear);
			glUniform1f(glGetUniformLocation(shader->Program, std::string("lights[").append(std::to_string(fragmentLightIndex) + "].quadratic").c_str()), light.quadratic);
			fragmentLightIndex++;
		//}
		
	}

	

	// Pass textures
	//int i = 0;
	//for (std::pair<std::string, Texture>& texture : Texture::textures) {

	//	// Load the diffuse/normal/specular maps
	//	TextureMap* maps[] = { &texture.second.diffuseMap, &texture.second.normalMap, &texture.second.specularMap, &texture.second.heightMap };
	//	
	//	for (int j = 0; j < 4; j++) {
	//		TextureMap* map = maps[j];
	//		glActiveTexture(GL_TEXTURE0 + map->mapId - 1);
	//		glBindTexture(GL_TEXTURE_2D, map->mapId);
	//		int index = (i * 4) + j;
	//		glUniform1i(
	//			glGetUniformLocation(
	//				shader->Program, 
	//				std::string("textures[").append(std::to_string(index)).c_str() ),
	//			map->mapId - 1);
	//	}
	//	i++;
	//}
	for (std::pair<std::string, Texture>& texture : Texture::textures) {

		// Load the diffuse/normal/specular maps
		TextureMap* maps[] = { &texture.second.diffuseMap, &texture.second.normalMap, &texture.second.specularMap, &texture.second.heightMap };
		for (TextureMap* map : maps) {
			glActiveTexture(GL_TEXTURE0 + map->mapId - 1);
			glBindTexture(GL_TEXTURE_2D, map->mapId);
			std::string uni = std::string(textureToUniform(texture.first, map->mapType));
			glUniform1i(glGetUniformLocation(shader->Program, uni.c_str()), map->mapId - 1);

		}
	}
	



	// Draw the rest of our scene
	glBufferData(GL_ARRAY_BUFFER, meshManager.finalMesh.vertexBufferSize(), meshManager.finalMesh.getVertices().data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshManager.finalMesh.indexBufferSize(), meshManager.finalMesh.getIndices().data(), GL_DYNAMIC_DRAW);
	glDrawElements(GL_TRIANGLES, meshManager.finalMesh.getIndices().size(), GL_UNSIGNED_INT, 0);
	
	
	// swap the buffer (double buffer)
	glfwSwapBuffers(window);
}

bool Display::isClosed() {
	return glfwWindowShouldClose(window);
}

void Display::clear(float r, float g, float b, float a) {
	//clear screen
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::setShader(Shader* shader) {
	this->shader = shader;
	// Get the uniform locations only once when we set up the shader
	transformUniform = glGetUniformLocation(shader->Program, "transform");
	modelUniform = glGetUniformLocation(shader->Program, "model");
	cameraPositionUniform = glGetUniformLocation(shader->Program, "camera_position");
}

void Display::setHandler(GLFWCallbackHandler* handler) {
	this->handler = handler;
	this->handler->attachToWindow(window);
	if (this->handler->callback != NULL) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		// Set the initial width and height in the callback so we can respond to window resizes properly
		this->handler->callback->setLastWindowSize(width, height);
		// Set the shared data between the display and the callback
		this->handler->callback->setSharedData(&sharedData);
	}
}

void Display::initGL(std::string windowName, int width, int height) {
	windowWidth = width;
	windowHeight = height;
	// init glfw 
	glfwInit();

	// specify version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);

	// use core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// set resizeable
	glfwWindowHint(GLFW_RESIZABLE, true);

	// Create a glfw window and set its height and width
	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);

	// If we don't get a window, then it failed and we should terimnate and free the resources
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	// init glew and set experimental glew to true to allow for modern graphics techniques
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	// set our viewport to the size of the window
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Enable face culling
	// TODO: should we enable this?
	//glEnable(GL_CULL_FACE);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	//glPointSize(30);
}

void Display::initTextures() {

	std::string t1 = "wood7";
	// Load of all our textures here
	Texture texture1("textures/" + t1 + "/", t1, "png");
	texture1.uvWrap = glm::ivec2(GL_REPEAT, GL_REPEAT);
	texture1.maxFilter = GL_NEAREST;
	texture1.minFilter = GL_NEAREST;
	
	std::string t2 = "wall2";
	Texture texture2("textures/" + t2 + "/", t2, "jpg");
	texture2.uvWrap = glm::ivec2(GL_REPEAT, GL_REPEAT);
	texture2.maxFilter = GL_NEAREST;
	texture2.minFilter = GL_NEAREST;


	std::string t3 = "copper";
	Texture texture3("textures/" + t3 + "/", t3, "jpg");
	texture3.uvWrap = glm::ivec2(GL_REPEAT, GL_REPEAT);
	texture3.maxFilter = GL_NEAREST;
	texture3.minFilter = GL_NEAREST;

	std::string t4 = "marble";
	Texture texture4("textures/" + t4 + "/", t4, "jpg");
	texture4.uvWrap = glm::ivec2(GL_REPEAT, GL_REPEAT);
	texture4.maxFilter = GL_NEAREST;
	texture4.minFilter = GL_NEAREST;


	Texture::textures.push_back(std::pair<std::string, Texture>("floor", texture1));
	Texture::textures.push_back(std::pair<std::string, Texture>("wall", texture2));
	Texture::textures.push_back(std::pair<std::string, Texture>("copper", texture3));
	Texture::textures.push_back(std::pair<std::string, Texture>("pedestal", texture4));

	for (std::pair<std::string, Texture>& texture : Texture::textures) {
		// Load the diffuse/normal/specular/height maps
		TextureMap* maps[] = { &texture.second.diffuseMap, &texture.second.normalMap, &texture.second.specularMap, &texture.second.heightMap };
		for (TextureMap* map : maps) {
			glGenTextures(1, &(map->mapId));
			glBindTexture(GL_TEXTURE_2D, map->mapId);
			// Texture parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture.second.uvWrap.s);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture.second.uvWrap.t);
			// Texture filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture.second.minFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture.second.maxFilter);
			// Load image
			unsigned char* image = SOIL_load_image(map->mapFilename.c_str(), &texture.second.width, &texture.second.height, 0, SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.second.width, texture.second.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);
			// Free the image
			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		
	}

}

void Display::initCamera() {
	PerspectiveCameraParams params;
	params.yFov = 45.0f;
	params.aspectRatio = windowWidth / windowHeight;
	params.zNearPlane = 0.1;
	params.zFarPlane = 100.0;
	camera = Camera(params);
	
	
	sharedData.transform->model = glm::mat4();
	sharedData.transform->view = sharedData.camera->getViewMatrix();
	sharedData.transform->projection = sharedData.camera->getProjectionMatrix();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Display::initGLBuffers() {
	// set up vertex buffers
	// Generate the vertex array
	glGenVertexArrays(1, &VAO);
	// Bind vertex array to buffer
	glBindVertexArray(VAO);
	// Generate element buffer object
	glGenBuffers(1, &EBO);
	// Generate vertex buffer object
	glGenBuffers(1, &VBO);
	// bind vertex buffer object to buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// bind element buffer object to buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Generate element buffer object
	glGenBuffers(1, &DEBUG_EBO);
	// Generate vertex buffer object
	glGenBuffers(1, &DEBUG_VBO);
	// bind vertex buffer object to buffer
	glBindBuffer(GL_ARRAY_BUFFER, DEBUG_VBO);
	// bind element buffer object to buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, DEBUG_EBO);

	// Position attribute
	GLuint byteOffset = 0;
	// Position attribute
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)byteOffset);
	glEnableVertexAttribArray(0);

	byteOffset += sizeof(glm::vec4);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(byteOffset));
	glEnableVertexAttribArray(1);

	byteOffset += sizeof(glm::vec3);
	// ambient attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(byteOffset));
	glEnableVertexAttribArray(2);


	byteOffset += sizeof(glm::vec3);
	// diffuse attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(byteOffset));
	glEnableVertexAttribArray(3);

	byteOffset += sizeof(glm::vec3);
	// specular attribute
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(byteOffset));
	glEnableVertexAttribArray(4);

	byteOffset += sizeof(glm::vec3);
	// shininess attribute
	glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(byteOffset));
	glEnableVertexAttribArray(5);

	
	byteOffset += sizeof(GLfloat);
	// uv attribute
	glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(byteOffset));
	glEnableVertexAttribArray(6);


	byteOffset += sizeof(glm::vec2);
	// texture meta 
	glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(byteOffset));
	glEnableVertexAttribArray(7);

	byteOffset += sizeof(glm::ivec2);
	// texturemaps 
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(byteOffset));
	glEnableVertexAttribArray(8);

	byteOffset += sizeof(glm::ivec4);
	// tangent 
	glVertexAttribPointer(9, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(byteOffset));
	glEnableVertexAttribArray(9);

	byteOffset += sizeof(glm::vec3);
	// bit tangent
	glVertexAttribPointer(10, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(byteOffset));
	glEnableVertexAttribArray(10);

}

void Display::initSharedData() {
	sharedData.transform = &transform;
	sharedData.camera = &camera;
	sharedData.meshManager = &meshManager;
}

void Display::initDebugMeshes() {
	debugShader = new Shader("debug_shader.vert", "debug_shader.frag");;
	GridMesh grid;
	debugMeshManager.grid = grid;
	XYZAxis xyz;
	debugMeshManager.axes = xyz;
}

void Display::debugUpdate() {

	debugShader->Use();
	glUniformMatrix4fv(glGetUniformLocation(debugShader->Program, "transform"), 1, GL_FALSE, value_ptr(sharedData.transform->getTransform()));
	

	// Draw grid
	glBindBuffer(GL_ARRAY_BUFFER, DEBUG_VBO);
	glBufferData(GL_ARRAY_BUFFER, debugMeshManager.grid.vertexBufferSize(), debugMeshManager.grid.getVertices().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, DEBUG_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, debugMeshManager.grid.indexBufferSize(), debugMeshManager.grid.getIndices().data(), GL_STATIC_DRAW);
	glDrawElements(GL_LINES, debugMeshManager.grid.getIndices().size(), GL_UNSIGNED_INT, 0);

	// Draw axes
	glLineWidth(5);
	glBindBuffer(GL_ARRAY_BUFFER, DEBUG_VBO);
	glBufferData(GL_ARRAY_BUFFER, debugMeshManager.axes.vertexBufferSize(), debugMeshManager.axes.getVertices().data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, DEBUG_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, debugMeshManager.axes.indexBufferSize(), debugMeshManager.axes.getIndices().data(), GL_STATIC_DRAW);
	glDrawElements(GL_LINES, debugMeshManager.axes.getIndices().size(), GL_UNSIGNED_INT, 0);

	glLineWidth(1);
	
}

