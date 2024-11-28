#include "IanFrustum.h"

namespace dims
{
	IanFrustum::IanFrustum()
	{

	}

	IanFrustum::IanFrustum(dims::Point3D Origin, dims::Point3D BottomLeftLoc, dims::Point3D TopRightLoc)
	{
		origin = Origin;
		bottomLeftLoc = BottomLeftLoc;
		topRightLoc = TopRightLoc;
	}

	void IanFrustum::determineSlopesY(bool Up, bool Down, bool Left, bool Right)
	{
		if (Up)
		{
			//the slope from the primary axis (y) is doubled
			//the slope from the secondary axis (z) is doubled, then incremented by 1
			// this is to simulate sub-tile accuracy:
			//	the origin occurs from the exact center of the tile 
			//	the slope is determined by the middle of the tile edge
			// 
			// 
			//		* Origin at the center of tile (2,0)
			//		* Starts at slope (1,-1) & (1,1)
			//		* Slope (1,-1) continues, traveling through the center of tile (1,1) and (0,2)	
			//		* Slope (1,1) is blocked at tile (3,1)
			//		* Blocking tiles are considered to be diamond-shaped
			//		* New slope is (2,1)
			//			one down from the origin is the border between (2,0) and (2,1)
			//			two down from the origin is the center of (2,1)
			//			one right from there is the center of (2,1), on the border between (2,1) and (3,1) - the "point" of the diamond-shaped blocking tile 
			// 
			//		   0	 1     2     3     4
			//		------*-----*-----*-----*-----*
			//		|     |     |     |     |	  |
			//	0	|     |     | /*\ |     |     |
			//		|     |     |/   \|     |	  |		  
			//		------*-----*-----*-----*-----*
			//		|     |    /|     |/###\|	  |
			//	1	|     |  -  |     *#####|     |
			//		|     |/    |     |\###/|	  |		  
			//		------*-----*-----*-|---*-----*
			//		|    /|     |     | \   |	  |
			//	2	|  -  |     |     |  *  |     |
			//		|/    |     |     |  |  |     |		  
			//		------*-----*-----*---\-*-----*
			up.Set((topRightLoc.y - origin.y) + (topRightLoc.y - origin.y)
				, (topRightLoc.z - origin.z) + (topRightLoc.z - origin.z));	
				//always increment by one if up-slope (to represent the half-tile offset)
				up.secondary++;
		}
		if (Down)
		{
			down.Set((bottomLeftLoc.y - origin.y) + (bottomLeftLoc.y - origin.y)
				, (bottomLeftLoc.z - origin.z) + (bottomLeftLoc.z - origin.z));
				//always decrement by one if down-slope (to represent the half-tile offset)
				down.secondary--;
		}
		if (Left) {
			left.Set((bottomLeftLoc.y - origin.y) + (bottomLeftLoc.y - origin.y)
				, (bottomLeftLoc.x - origin.x) + (bottomLeftLoc.x - origin.x));
				left.secondary--;
		}
		if (Right) {
			right.Set((topRightLoc.y - origin.y) + (topRightLoc.y - origin.y)
				, (topRightLoc.x - origin.x) + (topRightLoc.x - origin.x));
				right.secondary++;
		}
	}

	void IanFrustum::determineSlopesX(bool Up, bool Down, bool Left, bool Right)
	{
		if (Up)
		{
			up.Set((topRightLoc.x - origin.x) + (topRightLoc.x - origin.x)
				, (topRightLoc.z - origin.z) + (topRightLoc.z - origin.z));
			up.secondary++;
		}
		if (Down)
		{
			down.Set((bottomLeftLoc.x - origin.x) + (bottomLeftLoc.x - origin.x)
				, (bottomLeftLoc.z - origin.z) + (bottomLeftLoc.z - origin.z));
			down.secondary--;
		}
		if (Left) {
			left.Set((bottomLeftLoc.x - origin.x) + (bottomLeftLoc.x - origin.x)
				, (bottomLeftLoc.y - origin.y) + (bottomLeftLoc.y - origin.y));
			left.secondary--;
		}
		if (Right) {
			right.Set((topRightLoc.x - origin.x) + (topRightLoc.x - origin.x)
				, (topRightLoc.y - origin.y) + (topRightLoc.y - origin.y));
			right.secondary++;
		}
	}

	void IanFrustum::determineSlopesZ(bool Up, bool Down, bool Left, bool Right)
	{
		if (Up)
		{
			up.Set((topRightLoc.z - origin.z) + (topRightLoc.z - origin.z)
				, (topRightLoc.y - origin.y) + (topRightLoc.y - origin.y));
			up.secondary++;
		}
		if (Down)
		{
			down.Set((bottomLeftLoc.z - origin.z) + (bottomLeftLoc.z - origin.z)
				, (bottomLeftLoc.y - origin.y) + (bottomLeftLoc.y - origin.y));
			down.secondary--;
		}
		if (Left) {
			left.Set((bottomLeftLoc.z - origin.z) + (bottomLeftLoc.z - origin.z)
				, (bottomLeftLoc.x - origin.x) + (bottomLeftLoc.x - origin.x));
			left.secondary--;
		}
		if (Right) {
			right.Set((topRightLoc.z - origin.z) + (topRightLoc.z - origin.z)
				, (topRightLoc.x - origin.x) + (topRightLoc.x - origin.x));
			right.secondary++;
		}
	}

	void IanFrustum::incrementY(bool Positive)
	{
		//we are viewing in the y-direction, so we always take 1 step
		if (Positive)
		{
			bottomLeftLoc.y++;
			topRightLoc.y++;
		}
		else
		{
			bottomLeftLoc.y--;
			topRightLoc.y--;
		}
		//use the slope and current remainder to determine if the view frustum increments in the secondary direction
		bottomLeftLoc.z += down.IncrementPrimary(down.secondary > 0);
		topRightLoc.z += up.IncrementPrimary(up.secondary < 0);
		bottomLeftLoc.x += left.IncrementPrimary(left.secondary > 0);
		topRightLoc.x += right.IncrementPrimary(right.secondary < 0);
	}

	void IanFrustum::incrementX(bool Positive)
	{
		if (Positive)
		{
			bottomLeftLoc.x++;
			topRightLoc.x++;
		}
		else
		{
			bottomLeftLoc.x--;
			topRightLoc.x--;
		}
		bottomLeftLoc.z += down.IncrementPrimary(down.secondary > 0);
		topRightLoc.z += up.IncrementPrimary(up.secondary < 0);
		bottomLeftLoc.y += left.IncrementPrimary(left.secondary > 0);
		topRightLoc.y += right.IncrementPrimary(right.secondary < 0);
	}

	void IanFrustum::incrementZ(bool Positive)
	{
		if (Positive)
		{
			bottomLeftLoc.z++;
			topRightLoc.z++;
		}
		else
		{
			bottomLeftLoc.z--;
			topRightLoc.z--;
		}
		bottomLeftLoc.y += down.IncrementPrimary(down.secondary > 0);
		topRightLoc.y += up.IncrementPrimary(up.secondary < 0);
		bottomLeftLoc.x += left.IncrementPrimary(left.secondary > 0);
		topRightLoc.x += right.IncrementPrimary(right.secondary < 0);
	}

	IanFrustum::~IanFrustum()
	{

	}
}

