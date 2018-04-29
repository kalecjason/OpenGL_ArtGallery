#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H


#include <vector>
#include "Mesh.h"

// A simple class to manage a grouping of meshes
// You can add multiple meshes together, then compute the merged mesh
// to get the all the meshes as a single mesh
class MeshManager {
public:
	MeshManager();
	~MeshManager();
	void addMesh(Mesh* m);
	void addMesh(Mesh m);
	void removeMesh(Mesh* m);
	void clearMeshes();
	void computeMergedMesh();
	void computeMergedMeshCopies();
	Mesh finalMesh;
	std::vector<Mesh*> meshes;
	std::vector<Mesh> meshcopies;
private:
	int verticeCount;
	int indiceCount;
};


class DebugMeshManager : public MeshManager {
public:
	GridMesh grid;
	Mesh axes;
private:
	int verticeCount;
	int indiceCount;
};

#endif // !MESH_MANAGER_H