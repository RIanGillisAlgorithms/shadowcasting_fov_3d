#pragma once
#ifndef slope2d_h
#define slope2d_h

#include "Point3D.h"


namespace dims
{
	class Slope2D
	{
	public:
		Slope2D();
		~Slope2D();
		Slope2D(int Primary, int Secondary);

		int primary;
		int secondary;
		int remainder;

		void Set(int Primary, int Secondary, int Remainder = 0);

		int IncrementPrimary(bool IsNegative);
	};
}

#endif
