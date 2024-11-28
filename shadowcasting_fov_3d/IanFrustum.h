#pragma once
#ifndef IanFrustum_h
#define IanFrustum_h

#include "Point3D.h"
#include "Slope2D.h"


namespace dims
{
	class IanFrustum
	{
	public:
		IanFrustum();
		~IanFrustum();
		IanFrustum(dims::Point3D Origin, dims::Point3D BottomLeftLoc, dims::Point3D TopRightLoc);

		//the origin - this never changes
		dims::Point3D origin;
		// the bottom left location of the currently visible view frustum
		dims::Point3D bottomLeftLoc;
		// the top right location of the currently visible view frustum
		dims::Point3D topRightLoc;

		// the up slope of the current view frustum	
		// (if y, the z-positive)
		// (if x, the z-positive)
		// (if z, the y-positive)
		dims::Slope2D up;
		// the down slope of the current view frustum
		// (if y, the z-negative)
		// (if x, the z-negative)
		// (if z, the y-negative)
		dims::Slope2D down;
		// the left slope of the current view frustum
		// (if y, the x-negative)
		// (if x, the y-negative)
		// (if z, the x-negative)
		dims::Slope2D left;
		// the right slope of the current view frustum
		// (if y, the x-positive)
		// (if x, the y-positive)
		// (if z, the x-positive)
		dims::Slope2D right;

		void determineSlopesY(bool Up, bool Down, bool Left, bool Right);
		void determineSlopesX(bool Up, bool Down, bool Left, bool Right);
		void determineSlopesZ(bool Up, bool Down, bool Left, bool Right);
		void incrementY(bool Positive);
		void incrementX(bool Positive);
		void incrementZ(bool Positive);
	};
}

#endif
