#include "MeshManager.h"

MeshManager::MeshManager() {
	verticeCount = 0;
	indiceCount = 0;
}
MeshManager::~MeshManager() {
}

void MeshManager::addMesh(Mesh* m) {
	// Add the mesh to our array
	meshes.push_back(m);
	// Update the reserve count for the vertices and indices
	verticeCount += m->vertices.size();
	indiceCount += m->indices.size();
}
void MeshManager::addMesh(Mesh m) {
	// Add the mesh to our array
	meshcopies.push_back(m);
	// Update the reserve count for the vertices and indices
	verticeCount += m.vertices.size();
	indiceCount += m.indices.size();
}

void MeshManager::removeMesh(Mesh* m) {
	//TODO: improve
	//copy current meshes
	std::vector<Mesh*> oldMeshes;
	for (std::vector<Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it) {
		oldMeshes.push_back(*it);
	}
	std::vector<Mesh> oldMeshcopies;
	for (std::vector<Mesh>::iterator it = meshcopies.begin(); it != meshcopies.end(); ++it) {
		oldMeshcopies.push_back(*it);
	}

	//clear current meshes
	clearMeshes();

	//re-add all meshes except that to remove.
	for (std::vector<Mesh*>::iterator it = oldMeshes.begin(); it != oldMeshes.end(); ++it) {
		if (m != *it) {
			addMesh(*it);
		}
	}
	//TODO: all meshes with the same value of the one passed by address are removed, fix
	for (std::vector<Mesh>::iterator it = oldMeshcopies.begin(); it != oldMeshcopies.end(); ++it) {
		if (*m != *it) {
			addMesh(*it);
		}
	}
}

void MeshManager::clearMeshes() {
	meshes.clear();
	meshcopies.clear();
	verticeCount = 0;
	indiceCount = 0;
}

void MeshManager::computeMergedMesh() {
	//reset saved meshes
	finalMesh.vertices.clear();
	finalMesh.indices.clear();

	// Reserve space for our vertices
	finalMesh.vertices.reserve(verticeCount);
	finalMesh.indices.reserve(indiceCount);
	int offset = 0;
	for (Mesh* m : meshes) {
		// Copy vertices
		for (Vertex v : m->vertices) {
			finalMesh.vertices.push_back(v);
		}

		// Copy indices
		for (int i : m->indices) {
			finalMesh.indices.push_back(offset + i);
		}
		offset += m->vertices.size();
	}
}
void MeshManager::computeMergedMeshCopies() {
	//reset saved meshes
	finalMesh.vertices.clear();
	finalMesh.indices.clear();

	// Reserve space for our vertices
	finalMesh.vertices.reserve(verticeCount);
	finalMesh.indices.reserve(indiceCount);
	int offset = 0;
	for (Mesh m : meshcopies) {
		// Copy vertices
		for (Vertex v : m.vertices) {
			finalMesh.vertices.push_back(v);
		}

		// Copy indices
		for (int i : m.indices) {
			finalMesh.indices.push_back(offset + i);
		}
		offset += m.vertices.size();
	}
}
