#include "Point3D.h"

namespace dims
{
	Point3D::Point3D()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Point3D::Point3D(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Point3D::Set(int X, int Y, int Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	Point3D::~Point3D()
	{

	}
}

