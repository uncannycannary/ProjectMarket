#pragma once
#include "Vertex.h"

class Polygon
{
public:
	Polygon(const Vertex& initVertex1 = Vertex(), const Vertex& initVertex2 = Vertex(), const Vertex& initVertex3 = Vertex());
	~Polygon();
	void Set(const Vertex& initVertex1 = Vertex(), const Vertex& initVertex2 = Vertex(), const Vertex& initVertex3 = Vertex());
	void CalculateNormal();
	bool NormalIsFacing(const Vertex& vert) const;
	bool OppositeNormalIsFacing(const Vertex& vert);
	Vertex const* ReturnFirstVertex() const;
	Vertex const* ReturnSecondVertex() const;
	Vertex const* ReturnLastVertex() const;
	void GetBounds(float*const returnFurthestLeft, float*const returnFurthestRight, float*const returnFurthestDown, float*const returnFurthestUp, float*const returnFurthestBack, float*const returnFurthestFront);
	const Vector3& GetNormal() const;
	static unsigned ReturnNumOfNonVertVariables();
	void MoveAlongNormalBy(const float displacement);
	Polygon Flipped();
private:
	Vertex vertex1, vertex2, vertex3;
	Vector3 normal;
};