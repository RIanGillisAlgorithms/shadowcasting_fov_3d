#pragma once
#ifndef point3d_h
#define point3d_h

namespace dims
{
	//simple Point3D class
	class Point3D
	{
	public:
		Point3D();
		~Point3D();
		Point3D(int x, int y, int z);

		int x;
		int y;
		int z;

		void Set(int X, int Y, int Z);
	};
}

#endif
