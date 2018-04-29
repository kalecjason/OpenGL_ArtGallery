#pragma once

#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <vector>
#include "MVPTransform.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshManager.h"
#include <Windows.h>
#include <mmsystem.h>
#include <math.h>

// A simple container to hold all the data between the display and the input handler
// Since the input and the display share a lot of data, instead of passing individually, we'll just pass a struct that holds all of our data
struct SharedData {
	// The shared transform.
	MVPTransform* transform;
	// The shared camera
	Camera* camera;
	// The manager that handles all mesh operaions
	MeshManager* meshManager;

};


#endif // !SHARED_DATA_H
