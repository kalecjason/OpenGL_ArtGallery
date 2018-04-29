#ifndef CONE_H
#define CONE_H


#include "Mesh.h"

class Cone : public Mesh {
public:
	static const int DEFAULT_SIDES;
	Cone();
	Cone(int sides);
	~Cone();
};

#endif // !CONE_H