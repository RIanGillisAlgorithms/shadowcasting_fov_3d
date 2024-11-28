#include "Fov3D_3.h"
#include "IanFrustum.h"
#include "Util.h"

namespace world
{
	Fov3D_3::Fov3D_3()
	{
		this->map = nullptr;
	}

	Fov3D_3::~Fov3D_3()
	{

	}

	Fov3D_3::Fov3D_3(Map3D* map)
	{
		this->map = map;
	}

	/// <summary>
	/// Entry point
	/// </summary>
	/// <param name="Origin">The shadow-casting origin</param>
	/// <param name="MaxRadius">The limits of vision</param>
	/// <param name="CurTurn">Used to determine the tiles that are currently seen vs remembered</param>
	void Fov3D_3::computeFov(dims::Point3D Origin, int MaxRadius, int CurTurn)
	{
		//origin is always visible
		setSeen(Origin.x, Origin.y, Origin.z, CurTurn);

		//frustum starts at Origin, with viewFrustum taking in Origin with diagonal slope
		dims::IanFrustum startFrustum = dims::IanFrustum(Origin, Origin, Origin);
		startFrustum.up.Set(1, 1);
		startFrustum.down.Set(1, -1);
		startFrustum.left.Set(1, -1);
		startFrustum.right.Set(1, 1);

		//y
		incrementY(startFrustum, MaxRadius, CurTurn, true);
		//x 
		incrementX(startFrustum, MaxRadius, CurTurn, true);
		//z 
		incrementZ(startFrustum, MaxRadius, CurTurn, true);
		
		//negative slope
		startFrustum.up.Set(-1, 1);
		startFrustum.down.Set(-1, -1);
		startFrustum.left.Set(-1, -1);
		startFrustum.right.Set(-1, 1);

		//y negative
		incrementY(startFrustum, MaxRadius, CurTurn, false);
		//x negative
		incrementX(startFrustum, MaxRadius, CurTurn, false);
		//z negative
		incrementZ(startFrustum, MaxRadius, CurTurn, false);
	}

	/// <summary>
	/// Increment the provided frustum along the primary axis (y)
	///	Determine blocking tiles
	/// Create new rectangular viewing frustums if blocking tiles encountered
	/// Increment the provided frustum along the primary axis (y)
	/// </summary>
	/// <param name="startFrustum"></param>
	/// <param name="StepsLeft"></param>
	/// <param name="CurTurn"></param>
	/// <param name="PositiveDirection"></param>
	void Fov3D_3::incrementY(dims::IanFrustum startFrustum, int StepsLeft, int CurTurn, bool PositiveDirection)
	{
		//increment the view frustum in the direction we are looking
		startFrustum.incrementY(PositiveDirection);
		//store all of the tiles that will block view in this direction in the blockedTileIndex list
		determineBlockedTilesOfExpandedFrustum(startFrustum, CurTurn);
		//ensure we have not reached the limits of vision
		if (StepsLeft > 0)
		{
			if (blockedTileIndex.size() > 0)
			{
				//break up into smaller rectangles
				auto newFrustums = util::fLookup.divideFrustumY(startFrustum, blockedTileIndex);
				//The frustum has either stayed the same (Expanded at the rate of the 4 slopes) or been broken up into smaller frustums (or was blocked completely)
				for (auto frustum : newFrustums)
				{	   
					//Should any of the slopes be recalculated? Or should they inherit from startFrustum?
					bool up = frustum.topRightLoc.z != startFrustum.topRightLoc.z;
					bool down = frustum.bottomLeftLoc.z != startFrustum.bottomLeftLoc.z;
					bool left = frustum.bottomLeftLoc.x != startFrustum.bottomLeftLoc.x;
					bool right = frustum.topRightLoc.x != startFrustum.topRightLoc.x;
					//Recalculate any slopes that shouldn't be inherited
					frustum.determineSlopesY(up
						, down
						, left
						, right);

					//expand the new frustum now that we know the 4 slopes
					incrementY(frustum, StepsLeft - 1, CurTurn, PositiveDirection);
				}
			}
			else
			{
				//continue to expand the same frustum
				incrementY(startFrustum, StepsLeft - 1, CurTurn, PositiveDirection);
			}
		}

	}

	void Fov3D_3::incrementX(dims::IanFrustum startFrustum, int StepsLeft, int CurTurn, bool PositiveDirection)
	{
		//increment the view frustum in the direction we are looking
		startFrustum.incrementX(PositiveDirection);
		determineBlockedTilesOfExpandedFrustum(startFrustum, CurTurn);
		if (StepsLeft > 0)
		{
			if (blockedTileIndex.size() > 0)
			{
				//break up into smaller rectangles
				auto newFrustums = util::fLookup.divideFrustumX(startFrustum, blockedTileIndex);
				for (auto frustum : newFrustums)
				{
					bool up = frustum.topRightLoc.z != startFrustum.topRightLoc.z;
					bool down = frustum.bottomLeftLoc.z != startFrustum.bottomLeftLoc.z;
					bool left = frustum.bottomLeftLoc.y != startFrustum.bottomLeftLoc.y;
					bool right = frustum.topRightLoc.y != startFrustum.topRightLoc.y;
					frustum.determineSlopesX(up
						, down
						, left
						, right);

					incrementX(frustum, StepsLeft - 1, CurTurn, PositiveDirection);
				}
			}
			else
			{
				incrementX(startFrustum, StepsLeft - 1, CurTurn, PositiveDirection);
			}
		}
	}

	void Fov3D_3::incrementZ(dims::IanFrustum startFrustum, int StepsLeft, int CurTurn, bool PositiveDirection)
	{
		//increment the view frustum in the direction we are looking
		startFrustum.incrementZ(PositiveDirection);
		determineBlockedTilesOfExpandedFrustum(startFrustum, CurTurn);
		if (StepsLeft > 0)
		{
			if (blockedTileIndex.size() > 0)
			{
				//break up into smaller rectangles
				auto newFrustums = util::fLookup.divideFrustumZ(startFrustum, blockedTileIndex);
				for (auto frustum : newFrustums)
				{
					bool up = frustum.topRightLoc.y != startFrustum.topRightLoc.y;
					bool down = frustum.bottomLeftLoc.y != startFrustum.bottomLeftLoc.y;
					bool left = frustum.bottomLeftLoc.x != startFrustum.bottomLeftLoc.x;
					bool right = frustum.topRightLoc.x != startFrustum.topRightLoc.x;
					frustum.determineSlopesZ(up
						, down
						, left
						, right);

					incrementZ(frustum, StepsLeft - 1, CurTurn, PositiveDirection);
				}
			}
			else
			{
				incrementZ(startFrustum, StepsLeft - 1, CurTurn, PositiveDirection);
			}
		}
	}

	/// <summary>
	/// Iterate over the newly visible locations within the frustum, set seen and record if it blocks
	/// </summary>
	/// <param name="startFrustum"></param>
	/// <param name="CurTurn"></param>
	/// <returns></returns>
	void Fov3D_3::determineBlockedTilesOfExpandedFrustum(dims::IanFrustum& startFrustum, int CurTurn)
	{
		blockedTileIndex.clear();

		int idx = 0;
		//now check the new tile, looping from bottomleft to topright
		for (int piz = startFrustum.bottomLeftLoc.z; piz <= startFrustum.topRightLoc.z; piz++)
		{
			for (int piy = startFrustum.bottomLeftLoc.y; piy <= startFrustum.topRightLoc.y; piy++)
			{
				for (int pix = startFrustum.bottomLeftLoc.x; pix <= startFrustum.topRightLoc.x; pix++,
					//also increment the idx
					idx++)
				{
					if (pix < 0 || piy < 0 || piz < 0 || pix >= map->dimensions.x || piy >= map->dimensions.y || piz >= map->dimensions.z)
					{
						//out-of-bounds
						continue;
					}

					setSeen(pix, piy, piz, CurTurn);

					if (map->isOpaque(pix, piy, piz))
					{
						blockedTileIndex.push_back(idx);
					}
				}
			}
		}
	}

	void Fov3D_3::setSeen(int X, int Y, int Z, int CurTurn)
	{
		int idx = map->getIndex(X, Y, Z);
		if (idx != -1)
		{
			map->tiles[idx].setSeen(CurTurn);
		}
	}

	bool Fov3D_3::isOpaque(int X, int Y, int Z)
	{
		return map->isOpaque(X, Y, Z);
	}
}