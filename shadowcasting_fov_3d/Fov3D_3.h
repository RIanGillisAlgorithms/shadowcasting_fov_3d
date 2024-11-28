#pragma once
#ifndef fov3d_3_h
#define fov3d_3_h

#include "Map3D.h"
#include "Point3D.h"
#include <queue>
#include "IanFrustum.h"


namespace world
{
	class Fov3D_3
	{
	public:
		Fov3D_3();
		~Fov3D_3();
		Fov3D_3(world::Map3D* map);

		void computeFov(dims::Point3D Origin, int MaxRadius, int CurTurn);

		void incrementY(dims::IanFrustum startFrustum, int StepsLeft, int CurTurn, bool PositiveDirection);
		void incrementX(dims::IanFrustum startFrustum, int StepsLeft, int CurTurn, bool PositiveDirection);
		void incrementZ(dims::IanFrustum startFrustum, int StepsLeft, int CurTurn, bool PositiveDirection);

		void determineBlockedTilesOfExpandedFrustum(dims::IanFrustum& startFrustum, int CurTurn);

		void setSeen(int X, int Y, int Z, int CurTurn);
		bool isOpaque(int X, int Y, int Z);

		world::Map3D* map;
	private:
		std::queue<int> blockedTileIndex;

	};
}

#endif
