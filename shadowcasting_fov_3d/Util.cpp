#include "Util.h"

namespace util
{
	frustum_sectioning_lookup_2d fLookup;

	frustum_sectioning_lookup_2d::frustum_sectioning_lookup_2d()
	{

	}

	frustum_sectioning_lookup_2d::~frustum_sectioning_lookup_2d()
	{

	}

	/// <summary>
	/// Attempt to consolidate adjacent tiles into a single rectangular frustum. This algorithm can be optimized (cached results, expand rectangles in the z/ y direction etc).
	/// </summary>
	/// <param name="startFrustum"></param>
	/// <param name="blockedIndex"></param>
	/// <returns></returns>
	std::list<dims::IanFrustum> frustum_sectioning_lookup_2d::divideFrustumY(dims::IanFrustum startFrustum, std::list<int>& blockedIndex)
	{
		std::list<dims::IanFrustum> toReturn;
		dims::IanFrustum firstFrustum = dims::IanFrustum(startFrustum.origin, startFrustum.bottomLeftLoc, startFrustum.topRightLoc);
		firstFrustum.up = startFrustum.up;
		firstFrustum.down = startFrustum.down;
		firstFrustum.left = startFrustum.left;
		firstFrustum.right = startFrustum.right;

		dims::Point3D curLoc = firstFrustum.bottomLeftLoc;
		//start in the bot left and go to the top right
		int curIdx = 0;
		bool frustumStarted = false;
		bool encounterdBlock = false;
		for (int piy = startFrustum.bottomLeftLoc.y; piy <= startFrustum.topRightLoc.y; piy++)			
		{
			for (int piz = startFrustum.bottomLeftLoc.z; piz <= startFrustum.topRightLoc.z; piz++)
			{
				for (int pix = startFrustum.bottomLeftLoc.x; pix <= startFrustum.topRightLoc.x; pix++)
				{
					if (blockedIndex.size() > 0 && blockedIndex.front() == curIdx)
					{
						encounterdBlock = true;
						blockedIndex.pop_front();

						//if we have started a frustum, then we need to close it
						if (frustumStarted)
						{							
							toReturn.push_back(firstFrustum);
							frustumStarted = false;
						}
					}
					else
					{
						if (!frustumStarted)
						{
							frustumStarted = true;
							firstFrustum.origin = startFrustum.origin;
							firstFrustum.bottomLeftLoc = curLoc;
							firstFrustum.topRightLoc = curLoc; 		
						}
						else
						{
							firstFrustum.topRightLoc = curLoc;
						}
					}
					curLoc.x++;
					curIdx++;
				}

				if (frustumStarted)
				{
					toReturn.push_back(firstFrustum);
					frustumStarted = false;
				}
				curLoc.x = startFrustum.bottomLeftLoc.x;
				curLoc.z++;
			}
		}
		return toReturn;
	}

	std::list<dims::IanFrustum> frustum_sectioning_lookup_2d::divideFrustumX(dims::IanFrustum startFrustum, std::list<int>& blockedIndex)
	{
		std::list<dims::IanFrustum> toReturn;
		dims::IanFrustum firstFrustum = dims::IanFrustum(startFrustum.origin, startFrustum.bottomLeftLoc, startFrustum.topRightLoc);
		firstFrustum.up = startFrustum.up;
		firstFrustum.down = startFrustum.down;
		firstFrustum.left = startFrustum.left;
		firstFrustum.right = startFrustum.right;

		dims::Point3D curLoc = firstFrustum.bottomLeftLoc;
		//start in the bot left and go to the top right
		int curIdx = 0;
		bool frustumStarted = false;
		bool encounterdBlock = false;
		for (int pix = startFrustum.bottomLeftLoc.x; pix <= startFrustum.topRightLoc.x; pix++)
		{
			for (int piz = startFrustum.bottomLeftLoc.z; piz <= startFrustum.topRightLoc.z; piz++)
			{
				for (int piy = startFrustum.bottomLeftLoc.y; piy <= startFrustum.topRightLoc.y; piy++)
				{
					if (blockedIndex.size() > 0 && blockedIndex.front() == curIdx)
					{
						encounterdBlock = true;
						blockedIndex.pop_front();

						//if we have started a frustum, then we need to close it
						if (frustumStarted)
						{						
							toReturn.push_back(firstFrustum);
							frustumStarted = false;
						}
					}
					else
					{
						if (!frustumStarted)
						{
							frustumStarted = true;
							firstFrustum.origin = startFrustum.origin;
							firstFrustum.bottomLeftLoc = curLoc;
							firstFrustum.topRightLoc = curLoc;
						}
						else
						{
							firstFrustum.topRightLoc = curLoc;
						}
					}
					curLoc.y++;
					curIdx++;
				}

				if (frustumStarted)
				{
					toReturn.push_back(firstFrustum);
					frustumStarted = false;
				}
				curLoc.y = startFrustum.bottomLeftLoc.y;
				curLoc.z++;
			}
		}
		return toReturn;
	}

	std::list<dims::IanFrustum> frustum_sectioning_lookup_2d::divideFrustumZ(dims::IanFrustum startFrustum, std::list<int>& blockedIndex)
	{
		std::list<dims::IanFrustum> toReturn;
		dims::IanFrustum firstFrustum = dims::IanFrustum(startFrustum.origin, startFrustum.bottomLeftLoc, startFrustum.topRightLoc);
		firstFrustum.up = startFrustum.up;
		firstFrustum.down = startFrustum.down;
		firstFrustum.left = startFrustum.left;
		firstFrustum.right = startFrustum.right;

		dims::Point3D curLoc = firstFrustum.bottomLeftLoc;
		//start in the bot left and go to the top right
		int curIdx = 0;
		bool frustumStarted = false;
		bool encounterdBlock = false;
		for (int piz = startFrustum.bottomLeftLoc.z; piz <= startFrustum.topRightLoc.z; piz++)
		{
			for (int piy = startFrustum.bottomLeftLoc.y; piy <= startFrustum.topRightLoc.y; piy++)
			{
				for (int pix = startFrustum.bottomLeftLoc.x; pix <= startFrustum.topRightLoc.x; pix++)
				{
					if (blockedIndex.size() > 0 && blockedIndex.front() == curIdx)
					{
						encounterdBlock = true;
						blockedIndex.pop_front();

						//if we have started a frustum, then we need to close it
						if (frustumStarted)
						{							
							toReturn.push_back(firstFrustum);
							frustumStarted = false;
						}
					}
					else
					{
						if (!frustumStarted)
						{
							frustumStarted = true;
							firstFrustum.origin = startFrustum.origin;
							firstFrustum.bottomLeftLoc = curLoc;
							firstFrustum.topRightLoc = curLoc;
						}
						else
						{
							firstFrustum.topRightLoc = curLoc;
						}
					}
					curLoc.x++;
					curIdx++;
				}

				if (frustumStarted)
				{
					toReturn.push_back(firstFrustum);
					frustumStarted = false;
				}
				curLoc.x = startFrustum.bottomLeftLoc.x;
				curLoc.y++;
			}
		}
		return toReturn;
	}
}

