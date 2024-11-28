#include "Tile3D.h"

namespace world
{
	Tile3D::Tile3D()
	{
		seenTurn = -1;
		initTile(false);
	}

	void Tile3D::initTile(bool IsOpaque)
	{
		isOpaque = IsOpaque;
	}

	void Tile3D::setSeen(int TurnSeen)
	{
		seenTurn = TurnSeen;
	}

	world::SeenStatus Tile3D::getSeenStatus(int CurrentTurn)
	{
		if (seenTurn == CurrentTurn)
		{
			return world::SeenStatus::Seen;
		}
		else if (seenTurn >= 0)
		{
			return world::SeenStatus::Remembered;
		}
		else
		{
			return world::SeenStatus::Unseen;
		}
	}

	Tile3D::~Tile3D()
	{

	}
}

