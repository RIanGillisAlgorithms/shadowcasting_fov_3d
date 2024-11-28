#pragma once
#ifndef tile3d_h
#define tile3d_h

#include "Point3D.h"

namespace world
{
	enum class SeenStatus
	{
		Unseen
		, Seen
		, Remembered
	};

	//simple Tile3D class
	class Tile3D
	{
	public:
		Tile3D();
		~Tile3D();

		bool isOpaque;
		int seenTurn;

		void initTile(bool IsOpaque = false);
		void setSeen(int TurnSeen);
		SeenStatus getSeenStatus(int CurrentTurn);
	};
}

#endif
