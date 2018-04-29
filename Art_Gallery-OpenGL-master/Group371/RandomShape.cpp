#include "RandomShape.h"

// Outside faces are culled
RandomShape::RandomShape() 
{
	//Get a Mesh (Supershaped)
	Mesh m;
	m = Superform();

	//normalize values to size 1
	float xSize = m.maxXYZ.x - m.minXYZ.x;
	float ySize = m.maxXYZ.y - m.minXYZ.y;
	float zSize = m.maxXYZ.z - m.minXYZ.z;
	Mesh normalizedMesh;
	for (Vertex v : m.getVertices()) {
		normalizedMesh.addVertex(Vertex(glm::vec3(v.position.x / xSize, v.position.y / ySize, v.position.z / zSize)));
	}
	
	//center our vertices
	float xCenter = 0.5f - normalizedMesh.maxXYZ.x;
	float yCenter = 0.5f - normalizedMesh.maxXYZ.y;
	float zCenter = 0.5f - normalizedMesh.maxXYZ.z;
	std::vector<Vertex> verts;
	for (Vertex v : normalizedMesh.getVertices()) {
		verts.push_back(Vertex(glm::vec3(v.position.x + xCenter, v.position.y + yCenter, v.position.z + zCenter)));
	}

	setVertices(verts);
	setIndices(m.getIndices());
	Material material = randomMaterial();
	setMaterial(material);
}
Mesh RandomShape::Superform()
{
	//Object that will hold the final shape.
	Mesh mesh;

	// Superformula variables
	float a = 1.0f;
	float b = 1.0f;
	float m1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50.0f));
	float m2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50.0f));
	float n1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50.0f));
	float n2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50.0f));
	float n3 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50.0f));

	//8 to 20
	const int size = 8 + rand() % 12;

	//Cartesian Planes Coordinates
	float x, y, z;

	//Object that will hold the xyz
	Vertex vertex;

	// Draw the superformula using Spherical(Polar) Coordinates using Pi values
	const float PI = 3.1415926f;
	const float HALF_PI = PI / 2.0f;

	//Loop Angle on Theta - Θ 
	for (int i = 0; i <= size; i++)
	{
		// Map the latitude Theta - Θ 
		float latitude = map(i, 0, size, -HALF_PI, HALF_PI);

		//Loop Angle on Phi - Φ
		for (int j = 0; j < size; j++)
		{
			// Map the longitude Phi - Θ 
			float longitude = map(j, 0, size, -PI, PI);

			//Get the Two Superformulas to go from 2D to 3D.
			float r1 = superformula(a, b, m1, m2, n1, n2, n3, longitude);
			float r2 = superformula(a, b, m1, m2, n1, n2, n3, latitude);

			// Convert from Spherical (Polar) to Cartesian 3D coordinates.
			x = r1 * cos(longitude) * r2 * cos(latitude);
			y = r1 * sin(longitude) * r2 * cos(latitude);
			z = r2 * sin(latitude);

			// Make a Vertex out of the coordinates and add them to the mesh.
			vertex = glm::vec3(x, y, z);

			//std::cout << "X: " << vertex.position.x << " Y: " << vertex.position.y << " Z: " << vertex.position.z << std::endl;

			// Add the vertex to the mesh.
			mesh.addVertex(vertex);
		}
	}
	//Compute the indices for the Supershape.
	for (int i = 0; i < (size*size) - (size) - 1; i++)
	{
		mesh.addIndices(glm::vec3(i + 1, i + (size)+1, i + (size)));
		mesh.addIndices(glm::vec3(i, i + 1, i + (size)));
	}
	return mesh;
}
// The Superformula (Johan Gielis's) https://en.wikipedia.org/wiki/Superformula
float RandomShape::superformula(float a, float b, float m1, float m2, float n1, float n2, float n3, float angle)
{
	return (pow(
				(pow(
					abs(cos(m1*angle / 4.0f) / a)
				, (n2)) + 
				pow(
					abs(sin(m2*angle / 4.0f) / b)
				, (n3)))
			, (-1.0f / n1)));
}
// Mapping function for floats.
float RandomShape::map(float value, float istart, float istop, float ostart, float ostop)
{
	return (ostart + (ostop - ostart) * ((value - istart) / (istop - istart)));
}