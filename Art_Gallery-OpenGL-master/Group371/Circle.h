#ifndef CIRCLE_H
#define CIRCLE_H


#include  "Mesh.h"

class Circle : public Mesh {
public:
	static const int DEFAULT_SIDES;
	Circle();
	Circle(int sides);
	~Circle();
};

#endif // !CIRCLE_H
